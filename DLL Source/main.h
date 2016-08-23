#ifndef __MAIN_H__
#define __MAIN_H__s

/**
    The Vive class acts as an interface between OpenVR and GameMaker. It handles the data conversions
    as needed and stores the states of the hardware.
 **/

using std::queue;
class Vive
{
    public:
                                Vive(uint32_t rWidth, uint32_t rHeight);
                                ~Vive();
        bool                    isFatalError() {return fatalError;};
        vr::EVRInitError        getInitError(){return initError;};
        vr::EVRCompositorError  getCompositorError(){return compError;};
        void                    updateTextures(void* lEye, void* rEye);
        void                    updateDisplay();
        void                    updatePoses();
        void                    getHMDMatrix(double* m);
        void                    getEyeProjection(bool leftEye, double zNear, double zFar, double* m);
        void                    getEyePosition(bool leftEye, double* m);
        void                    getControllerPosition(int index, double* m);
        uint8_t                 getControllerCount();
        void                    fadeGrid(float seconds, bool in){vr::VRCompositor() -> FadeGrid(seconds, in);};
        void                    fadeColor(float seconds, float r, float g, float b, float a){vr::VRCompositor() -> FadeToColor(seconds, r, g, b, a);};
        double                  getChaperoneState(){return vr::VRChaperone() -> GetCalibrationState();};
        int                     updateEvents();
        void                    getNextEventData(double* data);
        uint32_t                getControllerModelVertexCount(int index);
        bool                    loadControllerModel(int index, void* modelBuffer);
        void                    setModelLoading(bool load){deviceStartLoadingModels = load;};
        vr::IVRSystem*          getVrSystem(){return hmd;};

        double                  getRenderModelCount(){return (modelLoader == nullptr) ? -1 : modelLoader -> GetRenderModelCount();};



    private:

           // OpenGL :
        GLuint                  lTexture,
                                rTexture;

            // Virtual Reality:
        vr::EVRInitError        initError = vr::VRInitError_None;
        vr::EVRCompositorError  compError = vr::VRCompositorError_None;
        vr::IVRSystem*          hmd = nullptr;
        vr::TrackedDevicePose_t vrPoses[vr::k_unMaxTrackedDeviceCount];
        double**                deviceMatrices = nullptr;
        char*                   deviceClass = nullptr;
        bool*                   deviceModelLoaded = nullptr;
        vr::RenderModel_t**     deviceModel = nullptr;
        bool                    deviceStartLoadingModels = false;

        double*                 hmdMatrix = nullptr; // SHARED with deviceMatrices!
        uint32_t                rWidth,
                                rHeight;
        vr::IVRRenderModels*    modelLoader = nullptr;


            // SDL:
        SDL_Window*             sdlWindow = nullptr;
        SDL_GLContext           sdlContext = nullptr;

            // Misc:
        bool                    fatalError = false;
        uint8_t*                defaultTextureColor;
        void                    vrMatrixToGMMatrix(const vr::HmdMatrix34_t &vrM, double* gmM);
        void                    vrMatrixToGMMatrix(const vr::HmdMatrix44_t &vrM, double* gmM);
        queue<vr::VREvent_t>    eventQueue;

};

Vive::Vive(uint32_t rWidth, uint32_t rHeight)
{
    this -> rWidth = rWidth;
    this -> rHeight = rHeight;

        // Reset error state:
    initError = vr::VRInitError_None;

    // Attempt to initialize the SDL system:
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        initError = (vr::EVRInitError) 3; // Custom error
        fatalError = true;
        return;
    }

    // Attempt to start the VR system:
    hmd = vr::VR_Init(& (initError), vr::VRApplication_Scene);
    if (initError != vr::VRInitError_None)
    {
        fatalError = true;
        return;
    }

    // Attempt to start the compositor:
    if (!vr::VRCompositor())
    {
        initError = (vr::EVRInitError) 4; // Custom error
        fatalError = true;
        return;
    }

    modelLoader = new vr::IVRRenderModels();

    // Create SDL window (required for OpenGL Context):
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // Max OpenGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1); // Min OpenGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
    sdlWindow = SDL_CreateWindow("VR Mediator", 100, 100, 640, 360,
                                      SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);

    if (sdlWindow == nullptr)
    {
        initError = (vr::EVRInitError) 5; // Custom error
        fatalError = true;
        return;
    }

    // Create SDL context:
    sdlContext = SDL_GL_CreateContext(sdlWindow);
    if (sdlContext == nullptr)
    {
        initError = (vr::EVRInitError) 6; // Custom error
        fatalError = true;
        return;
    }

    // Start GLEW to permit rendering:
    glewExperimental = GL_TRUE; // Required for OpenGL 3+
    if (glewInit() != GLEW_OK)
    {
        initError = (vr::EVRInitError) 7; // Custom error
        fatalError = true;
        return;
    }
    glGetError(); // Clear GLEW errors from the system

    // Set up textures for each display:
        // Left eye:
    glGenTextures(1, &(lTexture));
    glBindTexture(GL_TEXTURE_2D, lTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, /*GL_RGBA8*/GL_SRGB8_ALPHA8, rWidth, rHeight, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, nullptr);

        // Right eye:
    glGenTextures(1, &(rTexture));
    glBindTexture(GL_TEXTURE_2D, rTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, /*GL_RGBA8*/GL_SRGB8_ALPHA8, rWidth, rHeight, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, nullptr);

    // Set up default device matrices:
    deviceMatrices = new double*[vr::k_unMaxTrackedDeviceCount];
    for (uint32_t i = 0; i < vr::k_unMaxTrackedDeviceCount; ++i)
        deviceMatrices[i] = new double[16];

    // Set up default device classes:
   deviceClass = new char[vr::k_unMaxTrackedDeviceCount];
    for (uint32_t i = 0; i < vr::k_unMaxTrackedDeviceCount; ++i)
        deviceClass[i] = '_'; // None

    // Set up a default render color for the textures:
    uint32_t _size = rWidth * rHeight * 4;
    defaultTextureColor = new uint8_t[_size];
    for (uint32_t i = 0; i < _size; i += 4)
    {
        // BGRA format:
        defaultTextureColor[i] = 24;        // B
        defaultTextureColor[i + 1] = 24;    // G
        defaultTextureColor[i + 2] = 24;    // R
        defaultTextureColor[i + 3] = 255;   // A
    }

    updateTextures(defaultTextureColor, defaultTextureColor);

    deviceModelLoaded = new bool[vr::k_unMaxTrackedDeviceCount];
    for (uint32_t i = 0; i < vr::k_unMaxTrackedDeviceCount; ++i)
        deviceModelLoaded[i] = false;

    deviceModel = new vr::RenderModel_t*[vr::k_unMaxTrackedDeviceCount];

}

Vive::~Vive()
{

    // Shut-down VR system:
    if (hmd != nullptr)
        vr::VR_Shutdown();
    hmd = nullptr;

    if (modelLoader != nullptr)
        delete modelLoader;
    modelLoader = nullptr;

    // Destroy substitute texture:
    if (defaultTextureColor != nullptr)
        delete defaultTextureColor;

    defaultTextureColor = nullptr;

    // Destroy textures:
    if (sdlContext != nullptr)
    {
        glDeleteTextures(1, &lTexture);
        glDeleteTextures(1, &rTexture);
    }
    sdlContext = nullptr;

    // Destroy SDL window:
    if (sdlWindow != nullptr)
    {
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
    }
    sdlWindow = nullptr;

    // Free all device matrices
    if (deviceMatrices != nullptr)
    {
        for (uint32_t i = 0; i < vr::k_unMaxTrackedDeviceCount; ++i)
            delete deviceMatrices[i];

        delete [] deviceMatrices;
    }
    deviceMatrices = nullptr;

    // Free all device class values:
    if (deviceClass != nullptr)
        delete deviceClass;


    // Free all device models:
    if (deviceModel != nullptr)
    {
        for (uint32_t i = 0; i < vr::k_unMaxTrackedDeviceCount; ++i)
        {
            if (deviceModelLoaded != nullptr && deviceModelLoaded[i] == true)
                modelLoader -> FreeRenderModel(deviceModel[i]);
            delete deviceModel[i];
        }

        delete [] deviceModel;
    }

    if (deviceModelLoaded != nullptr)
        delete deviceModelLoaded;

    deviceClass = nullptr;
}

//Store our updated render data into our output textures:
void Vive::updateTextures(void* lEye, void* rEye)
{
        // Left eye:
    glBindTexture(GL_TEXTURE_2D, lTexture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, rWidth, rHeight, GL_BGRA, GL_UNSIGNED_BYTE, lEye);

        // Right eye:
    glBindTexture(GL_TEXTURE_2D, rTexture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, rWidth, rHeight, GL_BGRA, GL_UNSIGNED_BYTE, rEye);
}

// Updates the events and returns how many there were:
int Vive::updateEvents(void)
{
    // Empty the queue:
    while (!eventQueue.empty())
        eventQueue.pop();

    vr::VREvent_t _event;
    while (hmd -> PollNextEvent(&_event, sizeof(_event)))
        eventQueue.push(_event);

    return eventQueue.size();
}

// Stores the data for the next event in the provided array.
// The next event will be REMOVED from the queue!
void Vive::getNextEventData(double* data)
{
    /** Data Format:
    0 - Event type
    1 - Event Data
        : Controller index if type controller
    2 - Seconds since event
    3 - Specific Data
        : Button / Axis ID if type button press / release from type controller
    **/


    // If no next event we don't do anything:
    if (eventQueue.empty())
    {
        data[0] = -1;
        return;
    }

    vr::VREvent_t _event = eventQueue.front();
    eventQueue.pop(); // Remove the element

    // Reference:
    // https://github.com/ValveSoftware/openvr/wiki/VREvent_t

    // Determine the type of event:
    switch (_event.eventType)
    {
        case vr::VREvent_ButtonPress:
            {
            data[0] = 0;
            // We assume that this is type CONTROLLER, so we scan for the
            // controller ID number (that GameMaker will use)
            double _controllerIndex = 1;
            for (unsigned int i = 0; i < _event.trackedDeviceIndex; ++i)
            {
                if (deviceClass[i] == 'c')
                    ++_controllerIndex;
            }
            data[1] = _controllerIndex;
            data[2] = _event.eventAgeSeconds;

            // Assuming a button was pressed on the controller, we check what
            // button:
            if (_event.data.controller.button == vr::k_EButton_ApplicationMenu)
                data[3] = 0.;

            else if (_event.data.controller.button == vr::k_EButton_Grip)
                data[3] = 1.;
                // -- STUB -- // Will need to find out touchpad data
            else if (_event.data.controller.button == vr::k_EButton_SteamVR_Touchpad)
                data[3] = 2.;
                // -- STUB -- // Will need to find out trigger data
            else if (_event.data.controller.button == vr::k_EButton_SteamVR_Trigger)
                data[3] = 3.;

            }
        break;

        case vr::VREvent_ButtonUnpress:
            {
            data[0] = 1;
            // We assume that this is type CONTROLLER, so we scan for the
            // controller ID number (that GameMaker will use)
            double _controllerIndex = 1;
            for (unsigned int i = 0; i < _event.trackedDeviceIndex; ++i)
            {
                if (deviceClass[i] == 'c')
                    ++_controllerIndex;
            }
            data[1] = _controllerIndex;
            data[2] = _event.eventAgeSeconds;

            // Assuming a button was pressed on the controller, we check what
            // button:
            if (_event.data.controller.button == vr::k_EButton_ApplicationMenu)
                data[3] = 0.;

            else if (_event.data.controller.button == vr::k_EButton_Grip)
                data[3] = 1.;
                // -- STUB -- // Will need to find out touchpad data
            else if (_event.data.controller.button == vr::k_EButton_SteamVR_Touchpad)
                data[3] = 2.;
                // -- STUB -- // Will need to find out trigger data
            else if (_event.data.controller.button == vr::k_EButton_SteamVR_Trigger)
                data[3] = 3.;

            }
        break;

        // There are MANY more events, but I may not implement them

        default:
            data[0] = -1; // UNKNOWN / ERROR
        break;
    }
}

// Push our texture data to the display:
void Vive::updateDisplay(void)
{
    compError = vr::VRCompositorError_None;

    glClearColor(0., 0., 0., 1.);
    glDisable(GL_MULTISAMPLE);

        // Push texture to left display:
    vr::Texture_t lET = {(void*) lTexture, vr::API_OpenGL, vr::ColorSpace_Gamma};
    compError = vr::VRCompositor() -> Submit(vr::Eye_Left, &lET);

        // Push texture to right display:
    vr::Texture_t rET = {(void*) rTexture, vr::API_OpenGL, vr::ColorSpace_Gamma};
    compError = vr::VRCompositor() -> Submit(vr::Eye_Right, &rET);

    glFlush();

    // Update matrices automatically:
    updatePoses();
}

// Update all the peripheral matrices
void Vive::updatePoses(void)
{
    // Load all poses into our array:
    vr::VRCompositor() -> WaitGetPoses(vrPoses, vr::k_unMaxTrackedDeviceCount, nullptr, 0);

    // Loop through all device "slots" to find the active poses:
    for (uint32_t i = 0; i < vr::k_unMaxTrackedDeviceCount; ++i)
    {
        if (vrPoses[i].bPoseIsValid)
        {
            // Store device positional matrix:
            vrMatrixToGMMatrix(vrPoses[i].mDeviceToAbsoluteTracking, deviceMatrices[i]);

            // Store the type of device:
            switch (hmd -> GetTrackedDeviceClass(i))
            {
                case vr::TrackedDeviceClass_Controller:
                    deviceClass[i] = 'c'; break;
                case vr::TrackedDeviceClass_HMD:
                    deviceClass[i] = 'h'; break;
                case vr::TrackedDeviceClass_TrackingReference:
                    deviceClass[i] = 't'; break;

                // Note: There are other classes, but we will sort them into "none"
                default:
                    deviceClass[i] = '_'; break;
            }

            // Free model if needed:
            if (deviceModelLoaded[i] && deviceClass[i] == 'c')
            {
                modelLoader -> FreeRenderModel(deviceModel[i]);
                deviceModelLoaded[i] = false;
            }

            // Load model if available:
            if (deviceStartLoadingModels && !deviceModelLoaded[i] && deviceClass[i] == 'c')
            {
                uint32_t _nameIndex = 0;
                /*for (uint32_t j = 0; j <= i; ++j)
                {
                    if (deviceClass[j] != '_')
                        ++_nameIndex;
                }*/
                    // Load name
                char* _name = new char[1024];
                uint32_t _nameSize = 0;
                    // -- STUB -- // Next line crashing system???
                _nameSize = modelLoader -> GetRenderModelName(_nameIndex, _name, 1024);

                if (_nameSize != 0)
                {
                    vr::EVRRenderModelError _error;

                    // Loop until done loading (or other error)
                    while ((_error = modelLoader -> LoadRenderModel_Async(_name, &(deviceModel[i]))) == vr::VRRenderModelError_Loading)
                        ;
                        // Successful:
                    if (_error == vr::VRRenderModelError_None)
                        deviceModelLoaded[i] = true;
                }

                delete _name;
            }
        }
        else
            deviceClass[i] = '_'; // None
    }

    // Store the HMD's matrix:
    // WARNING: Matrix must be INVERTED before use!
    if (vrPoses[vr::k_unTrackedDeviceIndex_Hmd].bPoseIsValid)
        hmdMatrix = deviceMatrices[vr::k_unTrackedDeviceIndex_Hmd];
}

// Converts a 3x4 matrix to a GameMaker readable format
void Vive::vrMatrixToGMMatrix(const vr::HmdMatrix34_t &vrM, double* gmM)
{
    gmM[0] =  vrM.m[0][0];
    gmM[1] =  vrM.m[1][0];
    gmM[2] =  vrM.m[2][0];
    gmM[3] =  0.;

    gmM[4] =  vrM.m[0][1];
    gmM[5] =  vrM.m[1][1];
    gmM[6] =  vrM.m[2][1];
    gmM[7] =  0.;

    gmM[8] =  vrM.m[0][2];
    gmM[9] =  vrM.m[1][2];
    gmM[10] = vrM.m[2][2];
    gmM[11] = 0.;

    gmM[12] = vrM.m[0][3];
    gmM[13] = vrM.m[1][3];
    gmM[14] = vrM.m[2][3];
    gmM[15] = 1.;
}

// Converts a 4x4 matrix to a GameMaker readable format
void Vive::vrMatrixToGMMatrix(const vr::HmdMatrix44_t &vrM, double* gmM)
{
    gmM[0] =  vrM.m[0][0];
    gmM[1] =  vrM.m[1][0];
    gmM[2] =  vrM.m[2][0];
    gmM[3] =  vrM.m[3][0];

    gmM[4] =  vrM.m[0][1];
    gmM[5] =  vrM.m[1][1];
    gmM[6] =  vrM.m[2][1];
    gmM[7] =  vrM.m[3][1];

    gmM[8] =  vrM.m[0][2];
    gmM[9] =  vrM.m[1][2];
    gmM[10] = vrM.m[2][2];
    gmM[11] = vrM.m[3][2];

    gmM[12] = vrM.m[0][3];
    gmM[13] = vrM.m[1][3];
    gmM[14] = vrM.m[2][3];
    gmM[15] = vrM.m[3][3];
}

// Retrieve the current matrix for the HMD
void Vive::getHMDMatrix(double* m)
{
    if (hmdMatrix == nullptr)
        return;

    for (uint8_t i = 0; i < 16; ++i)
        m[i] = hmdMatrix[i];
}

// Retrieve the current projection matrix for the specified eye:
void  Vive::getEyeProjection(bool leftEye, double zNear, double zFar, double* m)
{
    if (hmdMatrix == nullptr)
        return;

    vrMatrixToGMMatrix(hmd -> GetProjectionMatrix((leftEye)? vr::Eye_Left : vr::Eye_Right,
                                                  zNear, zFar, vr::API_DirectX), m);
}

// Retrieve the current view matrix for the specified eye:
void  Vive::getEyePosition(bool leftEye, double* m)
{
    if (hmdMatrix == nullptr)
        return;

    vrMatrixToGMMatrix(hmd -> GetEyeToHeadTransform((leftEye)? vr::Eye_Left : vr::Eye_Right), m);
}

// Return the number of controllers currently detected:
uint8_t Vive::getControllerCount()
{
    uint8_t c = 0;
    for (unsigned int i = 0; i < vr::k_unMaxTrackedDeviceCount; ++i)
    {
        if (deviceClass[i] == 'c')
            ++c;
    }

    return c;
}

// Return the matrix of the specified controller index. Nothing happens if the index doesn't exist
void Vive::getControllerPosition(int index, double* m)
{
    int indexCurrent = 1;
    for (unsigned int i = 0; i < vr::k_unMaxTrackedDeviceCount; ++i)
    {
        if (deviceClass[i] == 'c')
        {
            if (indexCurrent == index)
            {
                double* matrix = deviceMatrices[i];
                for (int j = 0; j < 16; ++j)
                    m[j] = matrix[j];
                break;
            }
            ++indexCurrent;
        }
    }
}

uint32_t    Vive::getControllerModelVertexCount(int index)
{
    int indexCurrent = 1;
    for (uint32_t i = 0; i < vr::k_unMaxTrackedDeviceCount; ++i)
    {
        if (deviceClass[i] == 'c')
        {
            if (indexCurrent == index)
            {
                // If we haven't loaded the model yet, we have 0 vertices
                if (!deviceModelLoaded[i])
                    return 0;

                // Grab the vertex data:
                return deviceModel[i] -> unVertexCount;
            }
            ++indexCurrent;
        }
    }

    // Incorrect index:
    return 0;
}

bool Vive::loadControllerModel(int index, void* modelBuffer)
{
    /* Buffer format is:
        Position [x,y,z]: float32
        Normal   [x,y,z]: float32
        UV       [u, v] : float32
     */
     int indexMain = -1,
         indexCurrent = 1;

        // Grab the proper array index:
    for (uint32_t i = 0; i < vr::k_unMaxTrackedDeviceCount; ++i)
    {
        if (deviceClass[i] == 'c')
        {
            if (indexCurrent == index)
            {
                indexMain = i;
                break;
            }
            ++indexCurrent;
        }
    }
    if (indexMain == -1)
        return false; // Failed to generate model
    float*  _buffer = (float*) modelBuffer;
    // Add each vertex and other data to the buffer:
    for (uint32_t i = 0; i < deviceModel[indexMain] -> unVertexCount; ++i)
    {
        const vr::RenderModel_Vertex_t* _vertex = deviceModel[indexMain] -> rVertexData;

        uint32_t i8 = i * 8;
            // Positional Data:
        _buffer[i8] =   _vertex -> vPosition.v[0];
        _buffer[++i8] = _vertex -> vPosition.v[1];
        _buffer[++i8] = _vertex -> vPosition.v[2];
            // Normal Data:
        _buffer[++i8] = _vertex -> vNormal.v[0];
        _buffer[++i8] = _vertex -> vNormal.v[1];
        _buffer[++i8] = _vertex -> vNormal.v[2];
            // UV Data:
        _buffer[++i8] = _vertex -> rfTextureCoord[0];
        _buffer[++i8] = _vertex -> rfTextureCoord[1];

    }

    return true;
}

#endif // __MAIN_H__
