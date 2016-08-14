///vr_load_dll_models()
/*
    Tells the DLL to try loading the 3D models for the controllers, HMD, and
    base stations. After this is set, any connected device now or in the future
    will have its model loaded automatically.
    
    This will take a step to complete. Once complete, you can load the models
    into GameMaker.
    
    Returns if successful
 */

if (!global.vive_isrunning)
    return false;
    
return external_call(global.vive_external_beginmodelload);
