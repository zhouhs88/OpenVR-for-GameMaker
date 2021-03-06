
#pragma once

// openvr.h
//========= Copyright Valve Corporation ============//
// Dynamically generated file. Do not modify this file directly.

#ifndef _OPENVR_API
#define _OPENVR_API

#include <stdint.h>



// vrtypes.h
#ifndef _INCLUDE_VRTYPES_H
#define _INCLUDE_VRTYPES_H

namespace vr
{

#if defined(__linux__) || defined(__APPLE__)
    // The 32-bit version of gcc has the alignment requirement for uint64 and double set to
    // 4 meaning that even with #pragma pack(8) these types will only be four-byte aligned.
    // The 64-bit version of gcc has the alignment requirement for these types set to
    // 8 meaning that unless we use #pragma pack(4) our structures will get bigger.
    // The 64-bit structure packing has to match the 32-bit structure packing for each platform.
    #pragma pack( push, 4 )
#else
    #pragma pack( push, 8 )
#endif

typedef void* glSharedTextureHandle_t;
typedef int32_t glInt_t;
typedef uint32_t glUInt_t;

// right-handed system
// +y is up
// +x is to the right
// -z is going away from you
// Distance unit is  meters
struct HmdMatrix34_t
{
    float m[3][4];
};

struct HmdMatrix44_t
{
    float m[4][4];
};

struct HmdVector3_t
{
    float v[3];
};

struct HmdVector4_t
{
    float v[4];
};

struct HmdVector3d_t
{
    double v[3];
};

struct HmdVector2_t
{
    float v[2];
};

struct HmdQuaternion_t
{
    double w, x, y, z;
};

struct HmdColor_t
{
    float r, g, b, a;
};

struct HmdQuad_t
{
    HmdVector3_t vCorners[ 4 ];
};

struct HmdRect2_t
{
    HmdVector2_t vTopLeft;
    HmdVector2_t vBottomRight;
};

/** Used to return the post-distortion UVs for each color channel.
* UVs range from 0 to 1 with 0,0 in the upper left corner of the
* source render target. The 0,0 to 1,1 range covers a single eye. */
struct DistortionCoordinates_t
{
    float rfRed[2];
    float rfGreen[2];
    float rfBlue[2];
};

enum EVREye
{
    Eye_Left = 0,
    Eye_Right = 1
};

enum EGraphicsAPIConvention
{
    API_DirectX = 0, // Normalized Z goes from 0 at the viewer to 1 at the far clip plane
    API_OpenGL = 1,  // Normalized Z goes from 1 at the viewer to -1 at the far clip plane
};

enum EColorSpace
{
    ColorSpace_Auto = 0,    // Assumes 'gamma' for 8-bit per component formats, otherwise 'linear'.  This mirrors the DXGI formats which have _SRGB variants.
    ColorSpace_Gamma = 1,   // Texture data can be displayed directly on the display without any conversion (a.k.a. display native format).
    ColorSpace_Linear = 2,  // Same as gamma but has been converted to a linear representation using DXGI's sRGB conversion algorithm.
};

struct Texture_t
{
    void* handle; // Native d3d texture pointer or GL texture id.
    EGraphicsAPIConvention eType;
    EColorSpace eColorSpace;
};

enum ETrackingResult
{
    TrackingResult_Uninitialized            = 1,

    TrackingResult_Calibrating_InProgress   = 100,
    TrackingResult_Calibrating_OutOfRange   = 101,

    TrackingResult_Running_OK               = 200,
    TrackingResult_Running_OutOfRange       = 201,
};

static const uint32_t k_unTrackingStringSize = 32;
static const uint32_t k_unMaxDriverDebugResponseSize = 32768;

/** Used to pass device IDs to API calls */
typedef uint32_t TrackedDeviceIndex_t;
static const uint32_t k_unTrackedDeviceIndex_Hmd = 0;
static const uint32_t k_unMaxTrackedDeviceCount = 16;
static const uint32_t k_unTrackedDeviceIndexOther = 0xFFFFFFFE;
static const uint32_t k_unTrackedDeviceIndexInvalid = 0xFFFFFFFF;

/** Describes what kind of object is being tracked at a given ID */
enum ETrackedDeviceClass
{
    TrackedDeviceClass_Invalid = 0,             // the ID was not valid.
    TrackedDeviceClass_HMD = 1,                 // Head-Mounted Displays
    TrackedDeviceClass_Controller = 2,          // Tracked controllers
    TrackedDeviceClass_TrackingReference = 4,   // Camera and base stations that serve as tracking reference points

    TrackedDeviceClass_Other = 1000,
};


/** Describes what specific role associated with a tracked device */
enum ETrackedControllerRole
{
    TrackedControllerRole_Invalid = 0,                  // Invalid value for controller type
    TrackedControllerRole_LeftHand = 1,                 // Tracked device associated with the left hand
    TrackedControllerRole_RightHand = 2,                // Tracked device associated with the right hand
};


/** describes a single pose for a tracked object */
struct TrackedDevicePose_t
{
    HmdMatrix34_t mDeviceToAbsoluteTracking;
    HmdVector3_t vVelocity;             // velocity in tracker space in m/s
    HmdVector3_t vAngularVelocity;      // angular velocity in radians/s (?)
    ETrackingResult eTrackingResult;
    bool bPoseIsValid;

    // This indicates that there is a device connected for this spot in the pose array.
    // It could go from true to false if the user unplugs the device.
    bool bDeviceIsConnected;
};

/** Identifies which style of tracking origin the application wants to use
* for the poses it is requesting */
enum ETrackingUniverseOrigin
{
    TrackingUniverseSeated = 0,     // Poses are provided relative to the seated zero pose
    TrackingUniverseStanding = 1,   // Poses are provided relative to the safe bounds configured by the user
    TrackingUniverseRawAndUncalibrated = 2, // Poses are provided in the coordinate system defined by the driver. You probably don't want this one.
};


/** Each entry in this enum represents a property that can be retrieved about a
* tracked device. Many fields are only valid for one ETrackedDeviceClass. */
enum ETrackedDeviceProperty
{
    // general properties that apply to all device classes
    Prop_TrackingSystemName_String              = 1000,
    Prop_ModelNumber_String                     = 1001,
    Prop_SerialNumber_String                    = 1002,
    Prop_RenderModelName_String                 = 1003,
    Prop_WillDriftInYaw_Bool                    = 1004,
    Prop_ManufacturerName_String                = 1005,
    Prop_TrackingFirmwareVersion_String         = 1006,
    Prop_HardwareRevision_String                = 1007,
    Prop_AllWirelessDongleDescriptions_String   = 1008,
    Prop_ConnectedWirelessDongle_String         = 1009,
    Prop_DeviceIsWireless_Bool                  = 1010,
    Prop_DeviceIsCharging_Bool                  = 1011,
    Prop_DeviceBatteryPercentage_Float          = 1012, // 0 is empty, 1 is full
    Prop_StatusDisplayTransform_Matrix34        = 1013,
    Prop_Firmware_UpdateAvailable_Bool          = 1014,
    Prop_Firmware_ManualUpdate_Bool             = 1015,
    Prop_Firmware_ManualUpdateURL_String        = 1016,
    Prop_HardwareRevision_Uint64                = 1017,
    Prop_FirmwareVersion_Uint64                 = 1018,
    Prop_FPGAVersion_Uint64                     = 1019,
    Prop_VRCVersion_Uint64                      = 1020,
    Prop_RadioVersion_Uint64                    = 1021,
    Prop_DongleVersion_Uint64                   = 1022,
    Prop_BlockServerShutdown_Bool               = 1023,
    Prop_CanUnifyCoordinateSystemWithHmd_Bool   = 1024,
    Prop_ContainsProximitySensor_Bool           = 1025,
    Prop_DeviceProvidesBatteryStatus_Bool       = 1026,
    Prop_DeviceCanPowerOff_Bool                 = 1027,
    Prop_Firmware_ProgrammingTarget_String      = 1028,
    Prop_DeviceClass_Int32                      = 1029,
    Prop_HasCamera_Bool                         = 1030,
    Prop_DriverVersion_String                   = 1031,
    Prop_Firmware_ForceUpdateRequired_Bool      = 1032,

    // Properties that are unique to TrackedDeviceClass_HMD
    Prop_ReportsTimeSinceVSync_Bool             = 2000,
    Prop_SecondsFromVsyncToPhotons_Float        = 2001,
    Prop_DisplayFrequency_Float                 = 2002,
    Prop_UserIpdMeters_Float                    = 2003,
    Prop_CurrentUniverseId_Uint64               = 2004,
    Prop_PreviousUniverseId_Uint64              = 2005,
    Prop_DisplayFirmwareVersion_Uint64          = 2006,
    Prop_IsOnDesktop_Bool                       = 2007,
    Prop_DisplayMCType_Int32                    = 2008,
    Prop_DisplayMCOffset_Float                  = 2009,
    Prop_DisplayMCScale_Float                   = 2010,
    Prop_EdidVendorID_Int32                     = 2011,
    Prop_DisplayMCImageLeft_String              = 2012,
    Prop_DisplayMCImageRight_String             = 2013,
    Prop_DisplayGCBlackClamp_Float              = 2014,
    Prop_EdidProductID_Int32                    = 2015,
    Prop_CameraToHeadTransform_Matrix34         = 2016,
    Prop_DisplayGCType_Int32                    = 2017,
    Prop_DisplayGCOffset_Float                  = 2018,
    Prop_DisplayGCScale_Float                   = 2019,
    Prop_DisplayGCPrescale_Float                = 2020,
    Prop_DisplayGCImage_String                  = 2021,
    Prop_LensCenterLeftU_Float                  = 2022,
    Prop_LensCenterLeftV_Float                  = 2023,
    Prop_LensCenterRightU_Float                 = 2024,
    Prop_LensCenterRightV_Float                 = 2025,
    Prop_UserHeadToEyeDepthMeters_Float         = 2026,
    Prop_CameraFirmwareVersion_Uint64           = 2027,
    Prop_CameraFirmwareDescription_String       = 2028,
    Prop_DisplayFPGAVersion_Uint64              = 2029,
    Prop_DisplayBootloaderVersion_Uint64        = 2030,
    Prop_DisplayHardwareVersion_Uint64          = 2031,
    Prop_AudioFirmwareVersion_Uint64            = 2032,
    Prop_CameraCompatibilityMode_Int32          = 2033,
    Prop_ScreenshotHorizontalFieldOfViewDegrees_Float = 2034,
    Prop_ScreenshotVerticalFieldOfViewDegrees_Float = 2035,

    // Properties that are unique to TrackedDeviceClass_Controller
    Prop_AttachedDeviceId_String                = 3000,
    Prop_SupportedButtons_Uint64                = 3001,
    Prop_Axis0Type_Int32                        = 3002, // Return value is of type EVRControllerAxisType
    Prop_Axis1Type_Int32                        = 3003, // Return value is of type EVRControllerAxisType
    Prop_Axis2Type_Int32                        = 3004, // Return value is of type EVRControllerAxisType
    Prop_Axis3Type_Int32                        = 3005, // Return value is of type EVRControllerAxisType
    Prop_Axis4Type_Int32                        = 3006, // Return value is of type EVRControllerAxisType

    // Properties that are unique to TrackedDeviceClass_TrackingReference
    Prop_FieldOfViewLeftDegrees_Float           = 4000,
    Prop_FieldOfViewRightDegrees_Float          = 4001,
    Prop_FieldOfViewTopDegrees_Float            = 4002,
    Prop_FieldOfViewBottomDegrees_Float         = 4003,
    Prop_TrackingRangeMinimumMeters_Float       = 4004,
    Prop_TrackingRangeMaximumMeters_Float       = 4005,
    Prop_ModeLabel_String                       = 4006,

    // Vendors are free to expose private debug data in this reserved region
    Prop_VendorSpecific_Reserved_Start          = 10000,
    Prop_VendorSpecific_Reserved_End            = 10999,
};

/** No string property will ever be longer than this length */
static const uint32_t k_unMaxPropertyStringSize = 32 * 1024;

/** Used to return errors that occur when reading properties. */
enum ETrackedPropertyError
{
    TrackedProp_Success                     = 0,
    TrackedProp_WrongDataType               = 1,
    TrackedProp_WrongDeviceClass            = 2,
    TrackedProp_BufferTooSmall              = 3,
    TrackedProp_UnknownProperty             = 4,
    TrackedProp_InvalidDevice               = 5,
    TrackedProp_CouldNotContactServer       = 6,
    TrackedProp_ValueNotProvidedByDevice    = 7,
    TrackedProp_StringExceedsMaximumLength  = 8,
    TrackedProp_NotYetAvailable             = 9, // The property value isn't known yet, but is expected soon. Call again later.
};

/** Allows the application to control what part of the provided texture will be used in the
* frame buffer. */
struct VRTextureBounds_t
{
    float uMin, vMin;
    float uMax, vMax;
};


/** Allows the applicaiton to control how scene textures are used by the compositor when calling Submit. */
enum EVRSubmitFlags
{
    // Simple render path. App submits rendered left and right eye images with no lens distortion correction applied.
    Submit_Default = 0x00,

    // App submits final left and right eye images with lens distortion already applied (lens distortion makes the images appear
    // barrel distorted with chromatic aberration correction applied). The app would have used the data returned by
    // vr::IVRSystem::ComputeDistortion() to apply the correct distortion to the rendered images before calling Submit().
    Submit_LensDistortionAlreadyApplied = 0x01,

    // If the texture pointer passed in is actually a renderbuffer (e.g. for MSAA in OpenGL) then set this flag.
    Submit_GlRenderBuffer = 0x02,

    // If you application receives a screenshot request, submit with this flag to let the compositor this submission
    // is in the response to the screenshot
    Submit_Screenshot = 0x04
};


/** Status of the overall system or tracked objects */
enum EVRState
{
    VRState_Undefined = -1,
    VRState_Off = 0,
    VRState_Searching = 1,
    VRState_Searching_Alert = 2,
    VRState_Ready = 3,
    VRState_Ready_Alert = 4,
    VRState_NotReady = 5,
    VRState_Standby = 6,
};

/** The types of events that could be posted (and what the parameters mean for each event type) */
enum EVREventType
{
    VREvent_None = 0,

    VREvent_TrackedDeviceActivated      = 100,
    VREvent_TrackedDeviceDeactivated    = 101,
    VREvent_TrackedDeviceUpdated        = 102,
    VREvent_TrackedDeviceUserInteractionStarted     = 103,
    VREvent_TrackedDeviceUserInteractionEnded   = 104,
    VREvent_IpdChanged                  = 105,
    VREvent_EnterStandbyMode            = 106,
    VREvent_LeaveStandbyMode            = 107,
    VREvent_TrackedDeviceRoleChanged    = 108,

    VREvent_ButtonPress                 = 200, // data is controller
    VREvent_ButtonUnpress               = 201, // data is controller
    VREvent_ButtonTouch                 = 202, // data is controller
    VREvent_ButtonUntouch               = 203, // data is controller

    VREvent_MouseMove                   = 300, // data is mouse
    VREvent_MouseButtonDown             = 301, // data is mouse
    VREvent_MouseButtonUp               = 302, // data is mouse
    VREvent_FocusEnter                  = 303, // data is overlay
    VREvent_FocusLeave                  = 304, // data is overlay
    VREvent_Scroll                      = 305, // data is mouse
    VREvent_TouchPadMove                = 306, // data is mouse

    VREvent_InputFocusCaptured          = 400, // data is process DEPRECATED
    VREvent_InputFocusReleased          = 401, // data is process DEPRECATED
    VREvent_SceneFocusLost              = 402, // data is process
    VREvent_SceneFocusGained            = 403, // data is process
    VREvent_SceneApplicationChanged     = 404, // data is process - The App actually drawing the scene changed (usually to or from the compositor)
    VREvent_SceneFocusChanged           = 405, // data is process - New app got access to draw the scene
    VREvent_InputFocusChanged           = 406, // data is process

    VREvent_HideRenderModels            = 410, // Sent to the scene application to request hiding render models temporarily
    VREvent_ShowRenderModels            = 411, // Sent to the scene application to request restoring render model visibility

    VREvent_OverlayShown                = 500,
    VREvent_OverlayHidden               = 501,
    VREvent_DashboardActivated      = 502,
    VREvent_DashboardDeactivated    = 503,
    VREvent_DashboardThumbSelected  = 504, // Sent to the overlay manager - data is overlay
    VREvent_DashboardRequested      = 505, // Sent to the overlay manager - data is overlay
    VREvent_ResetDashboard          = 506, // Send to the overlay manager
    VREvent_RenderToast             = 507, // Send to the dashboard to render a toast - data is the notification ID
    VREvent_ImageLoaded             = 508, // Sent to overlays when a SetOverlayRaw or SetOverlayFromFile call finishes loading
    VREvent_ShowKeyboard = 509, // Sent to keyboard renderer in the dashboard to invoke it
    VREvent_HideKeyboard = 510, // Sent to keyboard renderer in the dashboard to hide it
    VREvent_OverlayGamepadFocusGained       = 511, // Sent to an overlay when IVROverlay::SetFocusOverlay is called on it
    VREvent_OverlayGamepadFocusLost = 512, // Send to an overlay when it previously had focus and IVROverlay::SetFocusOverlay is called on something else
    VREvent_OverlaySharedTextureChanged = 513,
    VREvent_DashboardGuideButtonDown = 514,
    VREvent_DashboardGuideButtonUp = 515,
    VREvent_ScreenshotTriggered = 516, // Screenshot button combo was pressed, Dashboard should request a screenshot

    // Screenshot API
    VREvent_RequestScreenshot = 520, // Sent by vrclient application to compositor to take a screenshot
    VREvent_ScreenshotTaken = 521, // Sent by compositor to the application that the screenshot has been taken
    VREvent_ScreenshotFailed = 522, // Sent by compositor to the application that the screenshot failed to be taken

    VREvent_Notification_Shown              = 600,
    VREvent_Notification_Hidden             = 601,
    VREvent_Notification_BeginInteraction   = 602,
    VREvent_Notification_Destroyed          = 603,

    VREvent_Quit                        = 700, // data is process
    VREvent_ProcessQuit                 = 701, // data is process
    VREvent_QuitAborted_UserPrompt      = 702, // data is process
    VREvent_QuitAcknowledged            = 703, // data is process
    VREvent_DriverRequestedQuit         = 704, // The driver has requested that SteamVR shut down

    VREvent_ChaperoneDataHasChanged     = 800,
    VREvent_ChaperoneUniverseHasChanged = 801,
    VREvent_ChaperoneTempDataHasChanged = 802,
    VREvent_ChaperoneSettingsHaveChanged = 803,
    VREvent_SeatedZeroPoseReset         = 804,

    VREvent_AudioSettingsHaveChanged    = 820,

    VREvent_BackgroundSettingHasChanged = 850,
    VREvent_CameraSettingsHaveChanged   = 851,
    VREvent_ReprojectionSettingHasChanged = 852,
    VREvent_ModelSkinSettingsHaveChanged = 853,
    VREvent_EnvironmentSettingsHaveChanged = 854,

    VREvent_StatusUpdate                = 900,

    VREvent_MCImageUpdated              = 1000,

    VREvent_FirmwareUpdateStarted   = 1100,
    VREvent_FirmwareUpdateFinished  = 1101,

    VREvent_KeyboardClosed              = 1200,
    VREvent_KeyboardCharInput           = 1201,
    VREvent_KeyboardDone                = 1202, // Sent when DONE button clicked on keyboard

    VREvent_ApplicationTransitionStarted    = 1300,
    VREvent_ApplicationTransitionAborted    = 1301,
    VREvent_ApplicationTransitionNewAppStarted = 1302,
    VREvent_ApplicationListUpdated          = 1303,

    VREvent_Compositor_MirrorWindowShown    = 1400,
    VREvent_Compositor_MirrorWindowHidden   = 1401,
    VREvent_Compositor_ChaperoneBoundsShown = 1410,
    VREvent_Compositor_ChaperoneBoundsHidden = 1411,

    VREvent_TrackedCamera_StartVideoStream  = 1500,
    VREvent_TrackedCamera_StopVideoStream   = 1501,
    VREvent_TrackedCamera_PauseVideoStream  = 1502,
    VREvent_TrackedCamera_ResumeVideoStream = 1503,

    VREvent_PerformanceTest_EnableCapture = 1600,
    VREvent_PerformanceTest_DisableCapture = 1601,
    VREvent_PerformanceTest_FidelityLevel = 1602,

    // Vendors are free to expose private events in this reserved region
    VREvent_VendorSpecific_Reserved_Start = 10000,
    VREvent_VendorSpecific_Reserved_End = 19999,
};


/** Level of Hmd activity */
enum EDeviceActivityLevel
{
    k_EDeviceActivityLevel_Unknown = -1,
    k_EDeviceActivityLevel_Idle = 0,
    k_EDeviceActivityLevel_UserInteraction = 1,
    k_EDeviceActivityLevel_UserInteraction_Timeout = 2,
    k_EDeviceActivityLevel_Standby = 3,
};


/** VR controller button and axis IDs */
enum EVRButtonId
{
    k_EButton_System            = 0,
    k_EButton_ApplicationMenu   = 1,
    k_EButton_Grip              = 2,
    k_EButton_DPad_Left         = 3,
    k_EButton_DPad_Up           = 4,
    k_EButton_DPad_Right        = 5,
    k_EButton_DPad_Down         = 6,
    k_EButton_A                 = 7,

    k_EButton_Axis0             = 32,
    k_EButton_Axis1             = 33,
    k_EButton_Axis2             = 34,
    k_EButton_Axis3             = 35,
    k_EButton_Axis4             = 36,

    // aliases for well known controllers
    k_EButton_SteamVR_Touchpad  = k_EButton_Axis0,
    k_EButton_SteamVR_Trigger   = k_EButton_Axis1,

    k_EButton_Dashboard_Back    = k_EButton_Grip,

    k_EButton_Max               = 64
};

inline uint64_t ButtonMaskFromId( EVRButtonId id ) { return 1ull << id; }

/** used for controller button events */
struct VREvent_Controller_t
{
    uint32_t button; // EVRButtonId enum
};


/** used for simulated mouse events in overlay space */
enum EVRMouseButton
{
    VRMouseButton_Left                  = 0x0001,
    VRMouseButton_Right                 = 0x0002,
    VRMouseButton_Middle                = 0x0004,
};


/** used for simulated mouse events in overlay space */
struct VREvent_Mouse_t
{
    float x, y; // co-ords are in GL space, bottom left of the texture is 0,0
    uint32_t button; // EVRMouseButton enum
};

/** used for simulated mouse wheel scroll in overlay space */
struct VREvent_Scroll_t
{
    float xdelta, ydelta; // movement in fraction of the pad traversed since last delta, 1.0 for a full swipe
    uint32_t repeatCount;
};

/** when in mouse input mode you can receive data from the touchpad, these events are only sent if the users finger
   is on the touchpad (or just released from it)
**/
struct VREvent_TouchPadMove_t
{
    // true if the users finger is detected on the touch pad
    bool bFingerDown;

    // How long the finger has been down in seconds
    float flSecondsFingerDown;

    // These values indicate the starting finger position (so you can do some basic swipe stuff)
    float fValueXFirst;
    float fValueYFirst;

    // This is the raw sampled coordinate without deadzoning
    float fValueXRaw;
    float fValueYRaw;
};

/** notification related events. Details will still change at this point */
struct VREvent_Notification_t
{
    uint64_t ulUserValue;
    uint32_t notificationId;
};

/** Used for events about processes */
struct VREvent_Process_t
{
    uint32_t pid;
    uint32_t oldPid;
    bool bForced;
};


/** Used for a few events about overlays */
struct VREvent_Overlay_t
{
    uint64_t overlayHandle;
};


/** Used for a few events about overlays */
struct VREvent_Status_t
{
    uint32_t statusState; // EVRState enum
};

/** Used for keyboard events **/
struct VREvent_Keyboard_t
{
    char cNewInput[8];  // Up to 11 bytes of new input
    uint64_t uUserValue;    // Possible flags about the new input
};

struct VREvent_Ipd_t
{
    float ipdMeters;
};

struct VREvent_Chaperone_t
{
    uint64_t m_nPreviousUniverse;
    uint64_t m_nCurrentUniverse;
};

/** Not actually used for any events */
struct VREvent_Reserved_t
{
    uint64_t reserved0;
    uint64_t reserved1;
};

struct VREvent_PerformanceTest_t
{
    uint32_t m_nFidelityLevel;
};

struct VREvent_SeatedZeroPoseReset_t
{
    bool bResetBySystemMenu;
};

/** If you change this you must manually update openvr_interop.cs.py */
typedef union
{
    VREvent_Reserved_t reserved;
    VREvent_Controller_t controller;
    VREvent_Mouse_t mouse;
    VREvent_Scroll_t scroll;
    VREvent_Process_t process;
    VREvent_Notification_t notification;
    VREvent_Overlay_t overlay;
    VREvent_Status_t status;
    VREvent_Keyboard_t keyboard;
    VREvent_Ipd_t ipd;
    VREvent_Chaperone_t chaperone;
    VREvent_PerformanceTest_t performanceTest;
    VREvent_TouchPadMove_t touchPadMove;
    VREvent_SeatedZeroPoseReset_t seatedZeroPoseReset;
} VREvent_Data_t;

/** An event posted by the server to all running applications */
struct VREvent_t
{
    uint32_t eventType; // EVREventType enum
    TrackedDeviceIndex_t trackedDeviceIndex;
    float eventAgeSeconds;
    // event data must be the end of the struct as its size is variable
    VREvent_Data_t data;
};


/** The mesh to draw into the stencil (or depth) buffer to perform
* early stencil (or depth) kills of pixels that will never appear on the HMD.
* This mesh draws on all the pixels that will be hidden after distortion.
*
* If the HMD does not provide a visible area mesh pVertexData will be
* NULL and unTriangleCount will be 0. */
struct HiddenAreaMesh_t
{
    const HmdVector2_t *pVertexData;
    uint32_t unTriangleCount;
};


/** Identifies what kind of axis is on the controller at index n. Read this type
* with pVRSystem->Get( nControllerDeviceIndex, Prop_Axis0Type_Int32 + n );
*/
enum EVRControllerAxisType
{
    k_eControllerAxis_None = 0,
    k_eControllerAxis_TrackPad = 1,
    k_eControllerAxis_Joystick = 2,
    k_eControllerAxis_Trigger = 3, // Analog trigger data is in the X axis
};


/** contains information about one axis on the controller */
struct VRControllerAxis_t
{
    float x; // Ranges from -1.0 to 1.0 for joysticks and track pads. Ranges from 0.0 to 1.0 for triggers were 0 is fully released.
    float y; // Ranges from -1.0 to 1.0 for joysticks and track pads. Is always 0.0 for triggers.
};


/** the number of axes in the controller state */
static const uint32_t k_unControllerStateAxisCount = 5;


/** Holds all the state of a controller at one moment in time. */
struct VRControllerState001_t
{
    // If packet num matches that on your prior call, then the controller state hasn't been changed since
    // your last call and there is no need to process it
    uint32_t unPacketNum;

    // bit flags for each of the buttons. Use ButtonMaskFromId to turn an ID into a mask
    uint64_t ulButtonPressed;
    uint64_t ulButtonTouched;

    // Axis data for the controller's analog inputs
    VRControllerAxis_t rAxis[ k_unControllerStateAxisCount ];
};


typedef VRControllerState001_t VRControllerState_t;


/** determines how to provide output to the application of various event processing functions. */
enum EVRControllerEventOutputType
{
    ControllerEventOutput_OSEvents = 0,
    ControllerEventOutput_VREvents = 1,
};



/** Collision Bounds Style */
enum ECollisionBoundsStyle
{
    COLLISION_BOUNDS_STYLE_BEGINNER = 0,
    COLLISION_BOUNDS_STYLE_INTERMEDIATE,
    COLLISION_BOUNDS_STYLE_SQUARES,
    COLLISION_BOUNDS_STYLE_ADVANCED,
    COLLISION_BOUNDS_STYLE_NONE,

    COLLISION_BOUNDS_STYLE_COUNT
};

/** Allows the application to customize how the overlay appears in the compositor */
struct Compositor_OverlaySettings
{
    uint32_t size; // sizeof(Compositor_OverlaySettings)
    bool curved, antialias;
    float scale, distance, alpha;
    float uOffset, vOffset, uScale, vScale;
    float gridDivs, gridWidth, gridScale;
    HmdMatrix44_t transform;
};

/** used to refer to a single VR overlay */
typedef uint64_t VROverlayHandle_t;

static const VROverlayHandle_t k_ulOverlayHandleInvalid = 0;

/** Errors that can occur around VR overlays */
enum EVROverlayError
{
    VROverlayError_None                 = 0,

    VROverlayError_UnknownOverlay       = 10,
    VROverlayError_InvalidHandle        = 11,
    VROverlayError_PermissionDenied     = 12,
    VROverlayError_OverlayLimitExceeded = 13, // No more overlays could be created because the maximum number already exist
    VROverlayError_WrongVisibilityType  = 14,
    VROverlayError_KeyTooLong           = 15,
    VROverlayError_NameTooLong          = 16,
    VROverlayError_KeyInUse             = 17,
    VROverlayError_WrongTransformType   = 18,
    VROverlayError_InvalidTrackedDevice = 19,
    VROverlayError_InvalidParameter     = 20,
    VROverlayError_ThumbnailCantBeDestroyed = 21,
    VROverlayError_ArrayTooSmall        = 22,
    VROverlayError_RequestFailed        = 23,
    VROverlayError_InvalidTexture       = 24,
    VROverlayError_UnableToLoadFile     = 25,
    VROVerlayError_KeyboardAlreadyInUse = 26,
    VROverlayError_NoNeighbor           = 27,
};

/** enum values to pass in to VR_Init to identify whether the application will
* draw a 3D scene. */
enum EVRApplicationType
{
    VRApplication_Other = 0,        // Some other kind of application that isn't covered by the other entries
    VRApplication_Scene = 1,        // Application will submit 3D frames
    VRApplication_Overlay = 2,      // Application only interacts with overlays
    VRApplication_Background = 3,   // Application should not start SteamVR if it's not already running, and should not
                                    // keep it running if everything else quits.
    VRApplication_Utility = 4,      // Init should not try to load any drivers. The application needs access to utility
                                    // interfaces (like IVRSettings and IVRApplications) but not hardware.
    VRApplication_VRMonitor = 5,    // Reserved for vrmonitor
};


/** error codes for firmware */
enum EVRFirmwareError
{
    VRFirmwareError_None = 0,
    VRFirmwareError_Success = 1,
    VRFirmwareError_Fail = 2,
};


/** error codes for notifications */
enum EVRNotificationError
{
    VRNotificationError_OK = 0,
    VRNotificationError_InvalidNotificationId = 100,
    VRNotificationError_NotificationQueueFull = 101,
    VRNotificationError_InvalidOverlayHandle = 102,
    VRNotificationError_SystemWithUserValueAlreadyExists = 103,
};


/** error codes returned by Vr_Init */

// Please add adequate error description to https://developer.valvesoftware.com/w/index.php?title=Category:SteamVRHelp
enum EVRInitError
{
    VRInitError_None    = 0,
    VRInitError_Unknown = 1,

    VRInitError_Init_InstallationNotFound       = 100,
    VRInitError_Init_InstallationCorrupt        = 101,
    VRInitError_Init_VRClientDLLNotFound        = 102,
    VRInitError_Init_FileNotFound               = 103,
    VRInitError_Init_FactoryNotFound            = 104,
    VRInitError_Init_InterfaceNotFound          = 105,
    VRInitError_Init_InvalidInterface           = 106,
    VRInitError_Init_UserConfigDirectoryInvalid = 107,
    VRInitError_Init_HmdNotFound                = 108,
    VRInitError_Init_NotInitialized             = 109,
    VRInitError_Init_PathRegistryNotFound       = 110,
    VRInitError_Init_NoConfigPath               = 111,
    VRInitError_Init_NoLogPath                  = 112,
    VRInitError_Init_PathRegistryNotWritable    = 113,
    VRInitError_Init_AppInfoInitFailed          = 114,
    VRInitError_Init_Retry                      = 115, // Used internally to cause retries to vrserver
    VRInitError_Init_InitCanceledByUser         = 116, // The calling application should silently exit. The user canceled app startup
    VRInitError_Init_AnotherAppLaunching        = 117,
    VRInitError_Init_SettingsInitFailed         = 118,
    VRInitError_Init_ShuttingDown               = 119,
    VRInitError_Init_TooManyObjects             = 120,
    VRInitError_Init_NoServerForBackgroundApp   = 121,
    VRInitError_Init_NotSupportedWithCompositor = 122,
    VRInitError_Init_NotAvailableToUtilityApps  = 123,
    VRInitError_Init_Internal                   = 124,

    VRInitError_Driver_Failed               = 200,
    VRInitError_Driver_Unknown              = 201,
    VRInitError_Driver_HmdUnknown           = 202,
    VRInitError_Driver_NotLoaded            = 203,
    VRInitError_Driver_RuntimeOutOfDate     = 204,
    VRInitError_Driver_HmdInUse             = 205,
    VRInitError_Driver_NotCalibrated        = 206,
    VRInitError_Driver_CalibrationInvalid   = 207,
    VRInitError_Driver_HmdDisplayNotFound   = 208,

    VRInitError_IPC_ServerInitFailed        = 300,
    VRInitError_IPC_ConnectFailed           = 301,
    VRInitError_IPC_SharedStateInitFailed   = 302,
    VRInitError_IPC_CompositorInitFailed    = 303,
    VRInitError_IPC_MutexInitFailed         = 304,
    VRInitError_IPC_Failed                  = 305,

    VRInitError_Compositor_Failed                   = 400,
    VRInitError_Compositor_D3D11HardwareRequired    = 401,
    VRInitError_Compositor_FirmwareRequiresUpdate   = 402,

    VRInitError_VendorSpecific_UnableToConnectToOculusRuntime = 1000,

    VRInitError_VendorSpecific_HmdFound_CantOpenDevice              = 1101,
    VRInitError_VendorSpecific_HmdFound_UnableToRequestConfigStart  = 1102,
    VRInitError_VendorSpecific_HmdFound_NoStoredConfig              = 1103,
    VRInitError_VendorSpecific_HmdFound_ConfigTooBig                = 1104,
    VRInitError_VendorSpecific_HmdFound_ConfigTooSmall              = 1105,
    VRInitError_VendorSpecific_HmdFound_UnableToInitZLib            = 1106,
    VRInitError_VendorSpecific_HmdFound_CantReadFirmwareVersion     = 1107,
    VRInitError_VendorSpecific_HmdFound_UnableToSendUserDataStart   = 1108,
    VRInitError_VendorSpecific_HmdFound_UnableToGetUserDataStart    = 1109,
    VRInitError_VendorSpecific_HmdFound_UnableToGetUserDataNext     = 1110,
    VRInitError_VendorSpecific_HmdFound_UserDataAddressRange        = 1111,
    VRInitError_VendorSpecific_HmdFound_UserDataError               = 1112,
    VRInitError_VendorSpecific_HmdFound_ConfigFailedSanityCheck     = 1113,

    VRInitError_Steam_SteamInstallationNotFound = 2000,
};

enum EVRScreenshotType
{
    VRScreenshotType_None = 0,
    VRScreenshotType_Mono = 1, // left eye only
    VRScreenshotType_Stereo = 2,
    VRScreenshotType_Cubemap = 3,
    VRScreenshotType_StereoPanorama = 4
};

enum EVRTrackedCameraError
{
    VRTrackedCameraError_None                       = 0,
    VRTrackedCameraError_OperationFailed            = 100,
    VRTrackedCameraError_InvalidHandle              = 101,
    VRTrackedCameraError_InvalidFrameHeaderVersion  = 102,
    VRTrackedCameraError_OutOfHandles               = 103,
    VRTrackedCameraError_IPCFailure                 = 104,
    VRTrackedCameraError_NotSupportedForThisDevice  = 105,
    VRTrackedCameraError_SharedMemoryFailure        = 106,
    VRTrackedCameraError_FrameBufferingFailure      = 107,
    VRTrackedCameraError_StreamSetupFailure         = 108,
    VRTrackedCameraError_InvalidGLTextureId         = 109,
    VRTrackedCameraError_InvalidSharedTextureHandle = 110,
    VRTrackedCameraError_FailedToGetGLTextureId     = 111,
    VRTrackedCameraError_SharedTextureFailure       = 112,
    VRTrackedCameraError_NoFrameAvailable           = 113,
    VRTrackedCameraError_InvalidArgument            = 114,
    VRTrackedCameraError_InvalidFrameBufferSize     = 115,
};

enum EVRTrackedCameraFrameType
{
    VRTrackedCameraFrameType_Distorted = 0,         // This is the camera video frame size in pixels, still distorted.
    VRTrackedCameraFrameType_Undistorted,           // In pixels, an undistorted inscribed rectangle region without invalid regions. This size is subject to changes shortly.
    VRTrackedCameraFrameType_MaximumUndistorted,    // In pixels, maximum undistorted with invalid regions. Non zero alpha component identifies valid regions.
    MAX_CAMERA_FRAME_TYPES
};

typedef void* TrackedCameraHandle_t;
#define INVALID_TRACKED_CAMERA_HANDLE   ((vr::TrackedCameraHandle_t)0)

struct CameraVideoStreamFrameHeader_t
{
    EVRTrackedCameraFrameType eFrameType;

    uint32_t nWidth;
    uint32_t nHeight;
    uint32_t nBytesPerPixel;

    uint32_t nFrameSequence;

    TrackedDevicePose_t standingTrackedDevicePose;
};

#pragma pack( pop )

// figure out how to import from the VR API dll
#if defined(_WIN32)

#ifdef VR_API_EXPORT
#define VR_INTERFACE extern "C" __declspec( dllexport )
#else
#define VR_INTERFACE extern "C" __declspec( dllimport )
#endif

#elif defined(GNUC) || defined(COMPILER_GCC) || defined(__APPLE__)

#ifdef VR_API_EXPORT
#define VR_INTERFACE extern "C" __attribute__((visibility("default")))
#else
#define VR_INTERFACE extern "C"
#endif

#else
#error "Unsupported Platform."
#endif


#if defined( _WIN32 )
#define VR_CALLTYPE __cdecl
#else
#define VR_CALLTYPE
#endif

} // namespace vr

#endif // _INCLUDE_VRTYPES_H


// vrannotation.h
#ifdef API_GEN
# define VR_CLANG_ATTR(ATTR) __attribute__((annotate( ATTR )))
#else
# define VR_CLANG_ATTR(ATTR)
#endif

#define VR_METHOD_DESC(DESC) VR_CLANG_ATTR( "desc:" #DESC ";" )
#define VR_IGNOREATTR() VR_CLANG_ATTR( "ignore" )
#define VR_OUT_STRUCT() VR_CLANG_ATTR( "out_struct: ;" )
#define VR_OUT_STRING() VR_CLANG_ATTR( "out_string: ;" )
#define VR_OUT_ARRAY_CALL(COUNTER,FUNCTION,PARAMS) VR_CLANG_ATTR( "out_array_call:" #COUNTER "," #FUNCTION "," #PARAMS ";" )
#define VR_OUT_ARRAY_COUNT(COUNTER) VR_CLANG_ATTR( "out_array_count:" #COUNTER ";" )
#define VR_ARRAY_COUNT(COUNTER) VR_CLANG_ATTR( "array_count:" #COUNTER ";" )
#define VR_ARRAY_COUNT_D(COUNTER, DESC) VR_CLANG_ATTR( "array_count:" #COUNTER ";desc:" #DESC )
#define VR_BUFFER_COUNT(COUNTER) VR_CLANG_ATTR( "buffer_count:" #COUNTER ";" )
#define VR_OUT_BUFFER_COUNT(COUNTER) VR_CLANG_ATTR( "out_buffer_count:" #COUNTER ";" )
#define VR_OUT_STRING_COUNT(COUNTER) VR_CLANG_ATTR( "out_string_count:" #COUNTER ";" )

// ivrsystem.h
namespace vr
{

struct VR_IVRSystem_FnTable
{
    void (__stdcall *GetRecommendedRenderTargetSize)( uint32_t *pnWidth, uint32_t *pnHeight );
    HmdMatrix44_t (__stdcall *GetProjectionMatrix)( EVREye eEye, float fNearZ, float fFarZ, EGraphicsAPIConvention eProjType );
    void (__stdcall *GetProjectionRaw)( EVREye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom );
    DistortionCoordinates_t (__stdcall *ComputeDistortion)( EVREye eEye, float fU, float fV );
    HmdMatrix34_t (__stdcall *GetEyeToHeadTransform)( EVREye eEye );
    bool (__stdcall *GetTimeSinceLastVsync)( float *pfSecondsSinceLastVsync, uint64_t *pulFrameCounter );
    int32_t (__stdcall *GetD3D9AdapterIndex)();
    void (__stdcall *GetDXGIOutputInfo)( int32_t *pnAdapterIndex );
    bool (__stdcall *IsDisplayOnDesktop)();
    bool (__stdcall *SetDisplayVisibility)( bool bIsVisibleOnDesktop );
    void (__stdcall *GetDeviceToAbsoluteTrackingPose)( ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow,  TrackedDevicePose_t *pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount );
    void (__stdcall *ResetSeatedZeroPose)();
    HmdMatrix34_t (__stdcall *GetSeatedZeroPoseToStandingAbsoluteTrackingPose)();
    HmdMatrix34_t (__stdcall *GetRawZeroPoseToStandingAbsoluteTrackingPose)();
    uint32_t (__stdcall *GetSortedTrackedDeviceIndicesOfClass)( ETrackedDeviceClass eTrackedDeviceClass,  vr::TrackedDeviceIndex_t *punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex);
    EDeviceActivityLevel (__stdcall *GetTrackedDeviceActivityLevel)( vr::TrackedDeviceIndex_t unDeviceId );
    void (__stdcall *ApplyTransform)( TrackedDevicePose_t *pOutputPose, const TrackedDevicePose_t *pTrackedDevicePose, const HmdMatrix34_t *pTransform );
    vr::TrackedDeviceIndex_t (__stdcall *GetTrackedDeviceIndexForControllerRole)( vr::ETrackedControllerRole unDeviceType );
    vr::ETrackedControllerRole (__stdcall *GetControllerRoleForTrackedDeviceIndex)( vr::TrackedDeviceIndex_t unDeviceIndex );
    ETrackedDeviceClass (__stdcall *GetTrackedDeviceClass)( vr::TrackedDeviceIndex_t unDeviceIndex );
    bool (__stdcall *IsTrackedDeviceConnected)( vr::TrackedDeviceIndex_t unDeviceIndex );
    bool (__stdcall *GetBoolTrackedDeviceProperty)( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError);
    float (__stdcall *GetFloatTrackedDeviceProperty)( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError);
    int32_t (__stdcall *GetInt32TrackedDeviceProperty)( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError);
    uint64_t (__stdcall *GetUint64TrackedDeviceProperty)( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError);
    HmdMatrix34_t (__stdcall *GetMatrix34TrackedDeviceProperty)( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError);
    uint32_t (__stdcall *GetStringTrackedDeviceProperty)( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop,  char *pchValue, uint32_t unBufferSize, ETrackedPropertyError *pError);
    const char *(__stdcall *GetPropErrorNameFromEnum)( ETrackedPropertyError error );
    bool (__stdcall *PollNextEvent)( VREvent_t *pEvent, uint32_t uncbVREvent );
    bool (__stdcall *PollNextEventWithPose)( ETrackingUniverseOrigin eOrigin, VREvent_t *pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t *pTrackedDevicePose );
    const char *(__stdcall *GetEventTypeNameFromEnum)( EVREventType eType );
    HiddenAreaMesh_t (__stdcall *GetHiddenAreaMesh)( EVREye eEye );
    bool (__stdcall *GetControllerState)( vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t *pControllerState );
    bool (__stdcall *GetControllerStateWithPose)( ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t *pControllerState, TrackedDevicePose_t *pTrackedDevicePose );
    void (__stdcall *TriggerHapticPulse)( vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec );
    const char *(__stdcall *GetButtonIdNameFromEnum)( EVRButtonId eButtonId );
    const char *(__stdcall *GetControllerAxisTypeNameFromEnum)( EVRControllerAxisType eAxisType );
    bool (__stdcall *CaptureInputFocus)();
    void (__stdcall *ReleaseInputFocus)();
    bool (__stdcall *IsInputFocusCapturedByAnotherProcess)();
    uint32_t (__stdcall *DriverDebugRequest)( vr::TrackedDeviceIndex_t unDeviceIndex, const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize );
    vr::EVRFirmwareError (__stdcall *PerformFirmwareUpdate)( vr::TrackedDeviceIndex_t unDeviceIndex );
    void (__stdcall *AcknowledgeQuit_Exiting)();
    void (__stdcall *AcknowledgeQuit_UserPrompt)();
};

class IVRSystem
{
    VR_IVRSystem_FnTable _table;
public:


    // ------------------------------------
    // Display Methods
    // ------------------------------------

    /** Suggested size for the intermediate render target that the distortion pulls from. */
    void GetRecommendedRenderTargetSize( uint32_t *pnWidth, uint32_t *pnHeight ) { _table.GetRecommendedRenderTargetSize(pnWidth, pnHeight); }

    /** The projection matrix for the specified eye */
    HmdMatrix44_t GetProjectionMatrix( EVREye eEye, float fNearZ, float fFarZ, EGraphicsAPIConvention eProjType ) { return _table.GetProjectionMatrix(eEye, fNearZ, fFarZ, eProjType); }

    /** The components necessary to build your own projection matrix in case your
    * application is doing something fancy like infinite Z */
    void GetProjectionRaw( EVREye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom ) { _table.GetProjectionRaw(eEye, pfLeft, pfRight, pfTop, pfBottom); }

    /** Returns the result of the distortion function for the specified eye and input UVs. UVs go from 0,0 in
    * the upper left of that eye's viewport and 1,1 in the lower right of that eye's viewport. */
    DistortionCoordinates_t ComputeDistortion( EVREye eEye, float fU, float fV ) { return _table.ComputeDistortion(eEye, fU, fV); }

    /** Returns the transform from eye space to the head space. Eye space is the per-eye flavor of head
    * space that provides stereo disparity. Instead of Model * View * Projection the sequence is Model * View * Eye^-1 * Projection.
    * Normally View and Eye^-1 will be multiplied together and treated as View in your application.
    */
    HmdMatrix34_t GetEyeToHeadTransform( EVREye eEye ) { return _table.GetEyeToHeadTransform(eEye); }

    /** Returns the number of elapsed seconds since the last recorded vsync event. This
    *   will come from a vsync timer event in the timer if possible or from the application-reported
    *   time if that is not available. If no vsync times are available the function will
    *   return zero for vsync time and frame counter and return false from the method. */
    bool GetTimeSinceLastVsync( float *pfSecondsSinceLastVsync, uint64_t *pulFrameCounter ) { return _table.GetTimeSinceLastVsync(pfSecondsSinceLastVsync, pulFrameCounter); }

    /** [D3D9 Only]
    * Returns the adapter index that the user should pass into CreateDevice to set up D3D9 in such
    * a way that it can go full screen exclusive on the HMD. Returns -1 if there was an error.
    */
    int32_t GetD3D9AdapterIndex() { return _table.GetD3D9AdapterIndex(); }

    /** [D3D10/11 Only]
    * Returns the adapter index and output index that the user should pass into EnumAdapters and EnumOutputs
    * to create the device and swap chain in DX10 and DX11. If an error occurs both indices will be set to -1.
    */
    void GetDXGIOutputInfo( int32_t *pnAdapterIndex ) { _table.GetDXGIOutputInfo(pnAdapterIndex); }

    // ------------------------------------
    // Display Mode methods
    // ------------------------------------

    /** Use to determine if the headset display is part of the desktop (i.e. extended) or hidden (i.e. direct mode). */
    bool IsDisplayOnDesktop() { return _table.IsDisplayOnDesktop(); }

    /** Set the display visibility (true = extended, false = direct mode).  Return value of true indicates that the change was successful. */
    bool SetDisplayVisibility( bool bIsVisibleOnDesktop ) { return _table.SetDisplayVisibility(bIsVisibleOnDesktop); }

    // ------------------------------------
    // Tracking Methods
    // ------------------------------------

    /** The pose that the tracker thinks that the HMD will be in at the specified number of seconds into the
    * future. Pass 0 to get the state at the instant the method is called. Most of the time the application should
    * calculate the time until the photons will be emitted from the display and pass that time into the method.
    *
    * This is roughly analogous to the inverse of the view matrix in most applications, though
    * many games will need to do some additional rotation or translation on top of the rotation
    * and translation provided by the head pose.
    *
    * For devices where bPoseIsValid is true the application can use the pose to position the device
    * in question. The provided array can be any size up to k_unMaxTrackedDeviceCount.
    *
    * Seated experiences should call this method with TrackingUniverseSeated and receive poses relative
    * to the seated zero pose. Standing experiences should call this method with TrackingUniverseStanding
    * and receive poses relative to the Chaperone Play Area. TrackingUniverseRawAndUncalibrated should
    * probably not be used unless the application is the Chaperone calibration tool itself, but will provide
    * poses relative to the hardware-specific coordinate system in the driver.
    */
    void GetDeviceToAbsoluteTrackingPose( ETrackingUniverseOrigin eOrigin, float fPredictedSecondsToPhotonsFromNow, VR_ARRAY_COUNT(unTrackedDevicePoseArrayCount) TrackedDevicePose_t *pTrackedDevicePoseArray, uint32_t unTrackedDevicePoseArrayCount ) { _table.GetDeviceToAbsoluteTrackingPose(eOrigin, fPredictedSecondsToPhotonsFromNow, pTrackedDevicePoseArray, unTrackedDevicePoseArrayCount); }

    /** Sets the zero pose for the seated tracker coordinate system to the current position and yaw of the HMD. After
    * ResetSeatedZeroPose all GetDeviceToAbsoluteTrackingPose calls that pass TrackingUniverseSeated as the origin
    * will be relative to this new zero pose. The new zero coordinate system will not change the fact that the Y axis
    * is up in the real world, so the next pose returned from GetDeviceToAbsoluteTrackingPose after a call to
    * ResetSeatedZeroPose may not be exactly an identity matrix.
    *
    * NOTE: This function overrides the user's previously saved seated zero pose and should only be called as the result of a user action.
    * Users are also able to set their seated zero pose via the OpenVR Dashboard.
    **/
    void ResetSeatedZeroPose() { _table.ResetSeatedZeroPose(); }

    /** Returns the transform from the seated zero pose to the standing absolute tracking system. This allows
    * applications to represent the seated origin to used or transform object positions from one coordinate
    * system to the other.
    *
    * The seated origin may or may not be inside the Play Area or Collision Bounds returned by IVRChaperone. Its position
    * depends on what the user has set from the Dashboard settings and previous calls to ResetSeatedZeroPose. */
    HmdMatrix34_t GetSeatedZeroPoseToStandingAbsoluteTrackingPose() { return _table.GetSeatedZeroPoseToStandingAbsoluteTrackingPose(); }

    /** Returns the transform from the tracking origin to the standing absolute tracking system. This allows
    * applications to convert from raw tracking space to the calibrated standing coordinate system. */
    HmdMatrix34_t GetRawZeroPoseToStandingAbsoluteTrackingPose() { return _table.GetRawZeroPoseToStandingAbsoluteTrackingPose(); }

    /** Get a sorted array of device indices of a given class of tracked devices (e.g. controllers).  Devices are sorted right to left
    * relative to the specified tracked device (default: hmd -- pass in -1 for absolute tracking space).  Returns the number of devices
    * in the list, or the size of the array needed if not large enough. */
    uint32_t GetSortedTrackedDeviceIndicesOfClass( ETrackedDeviceClass eTrackedDeviceClass, VR_ARRAY_COUNT(unTrackedDeviceIndexArrayCount) vr::TrackedDeviceIndex_t *punTrackedDeviceIndexArray, uint32_t unTrackedDeviceIndexArrayCount, vr::TrackedDeviceIndex_t unRelativeToTrackedDeviceIndex = k_unTrackedDeviceIndex_Hmd ) { return _table.GetSortedTrackedDeviceIndicesOfClass(eTrackedDeviceClass, punTrackedDeviceIndexArray, unTrackedDeviceIndexArrayCount, unRelativeToTrackedDeviceIndex); }

    /** Returns the level of activity on the device. */
    EDeviceActivityLevel GetTrackedDeviceActivityLevel( vr::TrackedDeviceIndex_t unDeviceId ) { return _table.GetTrackedDeviceActivityLevel(unDeviceId); }

    /** Convenience utility to apply the specified transform to the specified pose.
    *   This properly transforms all pose components, including velocity and angular velocity
    */
    void ApplyTransform( TrackedDevicePose_t *pOutputPose, const TrackedDevicePose_t *pTrackedDevicePose, const HmdMatrix34_t *pTransform ) { _table.ApplyTransform(pOutputPose, pTrackedDevicePose, pTransform); }

    /** Returns the device index associated with a specific role, for example the left hand or the right hand. */
    vr::TrackedDeviceIndex_t GetTrackedDeviceIndexForControllerRole( vr::ETrackedControllerRole unDeviceType ) { return _table.GetTrackedDeviceIndexForControllerRole(unDeviceType); }

    /** Returns the controller type associated with a device index. */
    vr::ETrackedControllerRole GetControllerRoleForTrackedDeviceIndex( vr::TrackedDeviceIndex_t unDeviceIndex ) { return _table.GetControllerRoleForTrackedDeviceIndex(unDeviceIndex); }

    // ------------------------------------
    // Property methods
    // ------------------------------------

    /** Returns the device class of a tracked device. If there has not been a device connected in this slot
    * since the application started this function will return TrackedDevice_Invalid. For previous detected
    * devices the function will return the previously observed device class.
    *
    * To determine which devices exist on the system, just loop from 0 to k_unMaxTrackedDeviceCount and check
    * the device class. Every device with something other than TrackedDevice_Invalid is associated with an
    * actual tracked device. */
    ETrackedDeviceClass GetTrackedDeviceClass( vr::TrackedDeviceIndex_t unDeviceIndex ) { return _table.GetTrackedDeviceClass(unDeviceIndex); }

    /** Returns true if there is a device connected in this slot. */
    bool IsTrackedDeviceConnected( vr::TrackedDeviceIndex_t unDeviceIndex ) { return _table.IsTrackedDeviceConnected(unDeviceIndex); }

    /** Returns a bool property. If the device index is not valid or the property is not a bool type this function will return false. */
    bool GetBoolTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError = 0L ) { return _table.GetBoolTrackedDeviceProperty(unDeviceIndex, prop, pError); }

    /** Returns a float property. If the device index is not valid or the property is not a float type this function will return 0. */
    float GetFloatTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError = 0L ) { return _table.GetFloatTrackedDeviceProperty(unDeviceIndex, prop, pError); }

    /** Returns an int property. If the device index is not valid or the property is not a int type this function will return 0. */
    int32_t GetInt32TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError = 0L ) { return _table.GetInt32TrackedDeviceProperty(unDeviceIndex, prop, pError); }

    /** Returns a uint64 property. If the device index is not valid or the property is not a uint64 type this function will return 0. */
    uint64_t GetUint64TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError = 0L ) { return _table.GetUint64TrackedDeviceProperty(unDeviceIndex, prop, pError); }

    /** Returns a matrix property. If the device index is not valid or the property is not a matrix type, this function will return identity. */
    HmdMatrix34_t GetMatrix34TrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, ETrackedPropertyError *pError = 0L ) { return _table.GetMatrix34TrackedDeviceProperty(unDeviceIndex, prop, pError); }

    /** Returns a string property. If the device index is not valid or the property is not a string type this function will
    * return 0. Otherwise it returns the length of the number of bytes necessary to hold this string including the trailing
    * null. Strings will generally fit in buffers of k_unTrackingStringSize characters. */
    uint32_t GetStringTrackedDeviceProperty( vr::TrackedDeviceIndex_t unDeviceIndex, ETrackedDeviceProperty prop, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, ETrackedPropertyError *pError = 0L ) { return _table.GetStringTrackedDeviceProperty(unDeviceIndex, prop, pchValue, unBufferSize, pError); }

    /** returns a string that corresponds with the specified property error. The string will be the name
    * of the error enum value for all valid error codes */
    const char *GetPropErrorNameFromEnum( ETrackedPropertyError error ) { return _table.GetPropErrorNameFromEnum(error); }

    // ------------------------------------
    // Event methods
    // ------------------------------------

    /** Returns true and fills the event with the next event on the queue if there is one. If there are no events
    * this method returns false. uncbVREvent should be the size in bytes of the VREvent_t struct */
    bool PollNextEvent( VREvent_t *pEvent, uint32_t uncbVREvent ) { return _table.PollNextEvent(pEvent, uncbVREvent); }

    /** Returns true and fills the event with the next event on the queue if there is one. If there are no events
    * this method returns false. Fills in the pose of the associated tracked device in the provided pose struct.
    * This pose will always be older than the call to this function and should not be used to render the device.
    uncbVREvent should be the size in bytes of the VREvent_t struct */
    bool PollNextEventWithPose( ETrackingUniverseOrigin eOrigin, VREvent_t *pEvent, uint32_t uncbVREvent, vr::TrackedDevicePose_t *pTrackedDevicePose ) { return _table.PollNextEventWithPose(eOrigin, pEvent, uncbVREvent, pTrackedDevicePose); }

    /** returns the name of an EVREvent enum value */
    const char *GetEventTypeNameFromEnum( EVREventType eType ) { return _table.GetEventTypeNameFromEnum(eType); }

    // ------------------------------------
    // Rendering helper methods
    // ------------------------------------

    /** Returns the stencil mesh information for the current HMD. If this HMD does not have a stencil mesh the vertex data and count will be
    * NULL and 0 respectively. This mesh is meant to be rendered into the stencil buffer (or into the depth buffer setting nearz) before rendering
    * each eye's view. The pixels covered by this mesh will never be seen by the user after the lens distortion is applied and based on visibility to the panels.
    * This will improve perf by letting the GPU early-reject pixels the user will never see before running the pixel shader.
    * NOTE: Render this mesh with backface culling disabled since the winding order of the vertices can be different per-HMD or per-eye.
    */
    HiddenAreaMesh_t GetHiddenAreaMesh( EVREye eEye ) { return _table.GetHiddenAreaMesh(eEye); }


    // ------------------------------------
    // Controller methods
    // ------------------------------------

    /** Fills the supplied struct with the current state of the controller. Returns false if the controller index
    * is invalid. */
    bool GetControllerState( vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t *pControllerState ) { return _table.GetControllerState(unControllerDeviceIndex, pControllerState); }

    /** fills the supplied struct with the current state of the controller and the provided pose with the pose of
    * the controller when the controller state was updated most recently. Use this form if you need a precise controller
    * pose as input to your application when the user presses or releases a button. */
    bool GetControllerStateWithPose( ETrackingUniverseOrigin eOrigin, vr::TrackedDeviceIndex_t unControllerDeviceIndex, vr::VRControllerState_t *pControllerState, TrackedDevicePose_t *pTrackedDevicePose ) { return _table.GetControllerStateWithPose(eOrigin, unControllerDeviceIndex, pControllerState, pTrackedDevicePose); }

    /** Trigger a single haptic pulse on a controller. After this call the application may not trigger another haptic pulse on this controller
    * and axis combination for 5ms. */
    void TriggerHapticPulse( vr::TrackedDeviceIndex_t unControllerDeviceIndex, uint32_t unAxisId, unsigned short usDurationMicroSec ) { _table.TriggerHapticPulse(unControllerDeviceIndex, unAxisId, usDurationMicroSec); }

    /** returns the name of an EVRButtonId enum value */
    const char *GetButtonIdNameFromEnum( EVRButtonId eButtonId ) { return _table.GetButtonIdNameFromEnum(eButtonId); }

    /** returns the name of an EVRControllerAxisType enum value */
    const char *GetControllerAxisTypeNameFromEnum( EVRControllerAxisType eAxisType ) { return _table.GetControllerAxisTypeNameFromEnum(eAxisType); }

    /** Tells OpenVR that this process wants exclusive access to controller button states and button events. Other apps will be notified that
    * they have lost input focus with a VREvent_InputFocusCaptured event. Returns false if input focus could not be captured for
    * some reason. */
    bool CaptureInputFocus() { return _table.CaptureInputFocus(); }

    /** Tells OpenVR that this process no longer wants exclusive access to button states and button events. Other apps will be notified
    * that input focus has been released with a VREvent_InputFocusReleased event. */
    void ReleaseInputFocus() { _table.ReleaseInputFocus(); }

    /** Returns true if input focus is captured by another process. */
    bool IsInputFocusCapturedByAnotherProcess() { return _table.IsInputFocusCapturedByAnotherProcess(); }

    // ------------------------------------
    // Debug Methods
    // ------------------------------------

    /** Sends a request to the driver for the specified device and returns the response. The maximum response size is 32k,
    * but this method can be called with a smaller buffer. If the response exceeds the size of the buffer, it is truncated.
    * The size of the response including its terminating null is returned. */
    uint32_t DriverDebugRequest( vr::TrackedDeviceIndex_t unDeviceIndex, const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize ) { return _table.DriverDebugRequest(unDeviceIndex, pchRequest, pchResponseBuffer, unResponseBufferSize); }


    // ------------------------------------
    // Firmware methods
    // ------------------------------------

    /** Performs the actual firmware update if applicable.
     * The following events will be sent, if VRFirmwareError_None was returned: VREvent_FirmwareUpdateStarted, VREvent_FirmwareUpdateFinished
     * Use the properties Prop_Firmware_UpdateAvailable_Bool, Prop_Firmware_ManualUpdate_Bool, and Prop_Firmware_ManualUpdateURL_String
     * to figure our whether a firmware update is available, and to figure out whether its a manual update
     * Prop_Firmware_ManualUpdateURL_String should point to an URL describing the manual update process */
    vr::EVRFirmwareError PerformFirmwareUpdate( vr::TrackedDeviceIndex_t unDeviceIndex ) { return _table.PerformFirmwareUpdate(unDeviceIndex); }


    // ------------------------------------
    // Application life cycle methods
    // ------------------------------------

    /** Call this to acknowledge to the system that VREvent_Quit has been received and that the process is exiting.
    * This extends the timeout until the process is killed. */
    void AcknowledgeQuit_Exiting() { _table.AcknowledgeQuit_Exiting(); }

    /** Call this to tell the system that the user is being prompted to save data. This
    * halts the timeout and dismisses the dashboard (if it was up). Applications should be sure to actually
    * prompt the user to save and then exit afterward, otherwise the user will be left in a confusing state. */
    void AcknowledgeQuit_UserPrompt() { _table.AcknowledgeQuit_UserPrompt(); }

};

static const char * const IVRSystem_Version = "FnTable:IVRSystem_012";

}


// ivrapplications.h
namespace vr
{

    /** Used for all errors reported by the IVRApplications interface */
    enum EVRApplicationError
    {
        VRApplicationError_None = 0,

        VRApplicationError_AppKeyAlreadyExists = 100,   // Only one application can use any given key
        VRApplicationError_NoManifest = 101,            // the running application does not have a manifest
        VRApplicationError_NoApplication = 102,         // No application is running
        VRApplicationError_InvalidIndex = 103,
        VRApplicationError_UnknownApplication = 104,    // the application could not be found
        VRApplicationError_IPCFailed = 105,             // An IPC failure caused the request to fail
        VRApplicationError_ApplicationAlreadyRunning = 106,
        VRApplicationError_InvalidManifest = 107,
        VRApplicationError_InvalidApplication = 108,
        VRApplicationError_LaunchFailed = 109,          // the process didn't start
        VRApplicationError_ApplicationAlreadyStarting = 110, // the system was already starting the same application
        VRApplicationError_LaunchInProgress = 111,      // The system was already starting a different application
        VRApplicationError_OldApplicationQuitting = 112,
        VRApplicationError_TransitionAborted = 113,
        VRApplicationError_IsTemplate = 114, // error when you try to call LaunchApplication() on a template type app (use LaunchTemplateApplication)

        VRApplicationError_BufferTooSmall = 200,        // The provided buffer was too small to fit the requested data
        VRApplicationError_PropertyNotSet = 201,        // The requested property was not set
        VRApplicationError_UnknownProperty = 202,
        VRApplicationError_InvalidParameter = 203,
    };

    /** The maximum length of an application key */
    static const uint32_t k_unMaxApplicationKeyLength = 128;

    /** these are the properties available on applications. */
    enum EVRApplicationProperty
    {
        VRApplicationProperty_Name_String               = 0,

        VRApplicationProperty_LaunchType_String         = 11,
        VRApplicationProperty_WorkingDirectory_String   = 12,
        VRApplicationProperty_BinaryPath_String         = 13,
        VRApplicationProperty_Arguments_String          = 14,
        VRApplicationProperty_URL_String                = 15,

        VRApplicationProperty_Description_String        = 50,
        VRApplicationProperty_NewsURL_String            = 51,
        VRApplicationProperty_ImagePath_String          = 52,
        VRApplicationProperty_Source_String             = 53,

        VRApplicationProperty_IsDashboardOverlay_Bool   = 60,
        VRApplicationProperty_IsTemplate_Bool           = 61,
        VRApplicationProperty_IsInstanced_Bool          = 62,

        VRApplicationProperty_LastLaunchTime_Uint64     = 70,
    };

    /** These are states the scene application startup process will go through. */
    enum EVRApplicationTransitionState
    {
        VRApplicationTransition_None = 0,

        VRApplicationTransition_OldAppQuitSent = 10,
        VRApplicationTransition_WaitingForExternalLaunch = 11,

        VRApplicationTransition_NewAppLaunched = 20,
    };

    struct AppOverrideKeys_t
    {
        const char *pchKey;
        const char *pchValue;
    };

    struct VR_IVRApplications_FnTable
    {
        EVRApplicationError (__stdcall *AddApplicationManifest)( const char *pchApplicationManifestFullPath, bool bTemporary);
        EVRApplicationError (__stdcall *RemoveApplicationManifest)( const char *pchApplicationManifestFullPath );
        bool (__stdcall *IsApplicationInstalled)( const char *pchAppKey );
        uint32_t (__stdcall *GetApplicationCount)();
        EVRApplicationError (__stdcall *GetApplicationKeyByIndex)( uint32_t unApplicationIndex, char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen );
        EVRApplicationError (__stdcall *GetApplicationKeyByProcessId)( uint32_t unProcessId, char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen );
        EVRApplicationError (__stdcall *LaunchApplication)( const char *pchAppKey );
        EVRApplicationError (__stdcall *LaunchTemplateApplication)( const char *pchTemplateAppKey, const char *pchNewAppKey,  const AppOverrideKeys_t *pKeys, uint32_t unKeys );
        EVRApplicationError (__stdcall *LaunchDashboardOverlay)( const char *pchAppKey );
        bool (__stdcall *CancelApplicationLaunch)( const char *pchAppKey );
        EVRApplicationError (__stdcall *IdentifyApplication)( uint32_t unProcessId, const char *pchAppKey );
        uint32_t (__stdcall *GetApplicationProcessId)( const char *pchAppKey );
        const char *(__stdcall *GetApplicationsErrorNameFromEnum)( EVRApplicationError error );
        uint32_t (__stdcall *GetApplicationPropertyString)( const char *pchAppKey, EVRApplicationProperty eProperty, char *pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, EVRApplicationError *peError);
        bool (__stdcall *GetApplicationPropertyBool)( const char *pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError *peError);
        uint64_t (__stdcall *GetApplicationPropertyUint64)( const char *pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError *peError);
        EVRApplicationError (__stdcall *SetApplicationAutoLaunch)( const char *pchAppKey, bool bAutoLaunch );
        bool (__stdcall *GetApplicationAutoLaunch)( const char *pchAppKey );
        EVRApplicationError (__stdcall *GetStartingApplication)( char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen );
        EVRApplicationTransitionState (__stdcall *GetTransitionState)();
        EVRApplicationError (__stdcall *PerformApplicationPrelaunchCheck)( const char *pchAppKey );
        const char *(__stdcall *GetApplicationsTransitionStateNameFromEnum)( EVRApplicationTransitionState state );
        bool (__stdcall *IsQuitUserPromptRequested)();
        EVRApplicationError (__stdcall *LaunchInternalProcess)( const char *pchBinaryPath, const char *pchArguments, const char *pchWorkingDirectory );
    };

    class IVRApplications
    {
        VR_IVRApplications_FnTable _table;
    public:

        // ---------------  Application management  --------------- //

        /** Adds an application manifest to the list to load when building the list of installed applications.
        * Temporary manifests are not automatically loaded */
        EVRApplicationError AddApplicationManifest( const char *pchApplicationManifestFullPath, bool bTemporary = false ) { return _table.AddApplicationManifest(pchApplicationManifestFullPath, bTemporary); }

        /** Removes an application manifest from the list to load when building the list of installed applications. */
        EVRApplicationError RemoveApplicationManifest( const char *pchApplicationManifestFullPath ) { return _table.RemoveApplicationManifest(pchApplicationManifestFullPath); }

        /** Returns true if an application is installed */
        bool IsApplicationInstalled( const char *pchAppKey ) { return _table.IsApplicationInstalled(pchAppKey); }

        /** Returns the number of applications available in the list */
        uint32_t GetApplicationCount() { return _table.GetApplicationCount(); }

        /** Returns the key of the specified application. The index is at least 0 and is less than the return
        * value of GetApplicationCount(). The buffer should be at least k_unMaxApplicationKeyLength in order to
        * fit the key. */
        EVRApplicationError GetApplicationKeyByIndex( uint32_t unApplicationIndex, char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen ) { return _table.GetApplicationKeyByIndex(unApplicationIndex, pchAppKeyBuffer, unAppKeyBufferLen); }

        /** Returns the key of the application for the specified Process Id. The buffer should be at least
        * k_unMaxApplicationKeyLength in order to fit the key. */
        EVRApplicationError GetApplicationKeyByProcessId( uint32_t unProcessId, char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen ) { return _table.GetApplicationKeyByProcessId(unProcessId, pchAppKeyBuffer, unAppKeyBufferLen); }

        /** Launches the application. The existing scene application will exit and then the new application will start.
        * This call is not valid for dashboard overlay applications. */
        EVRApplicationError LaunchApplication( const char *pchAppKey ) { return _table.LaunchApplication(pchAppKey); }

        /** Launches an instance of an application of type template, with its app key being pchNewAppKey (which must be unique) and optionally override sections
        * from the manifest file via AppOverrideKeys_t
        */
        EVRApplicationError LaunchTemplateApplication( const char *pchTemplateAppKey, const char *pchNewAppKey, VR_ARRAY_COUNT( unKeys ) const AppOverrideKeys_t *pKeys, uint32_t unKeys ) { return _table.LaunchTemplateApplication(pchTemplateAppKey, pchNewAppKey, pKeys, unKeys); }

        /** Launches the dashboard overlay application if it is not already running. This call is only valid for
        * dashboard overlay applications. */
        EVRApplicationError LaunchDashboardOverlay( const char *pchAppKey ) { return _table.LaunchDashboardOverlay(pchAppKey); }

        /** Cancel a pending launch for an application */
        bool CancelApplicationLaunch( const char *pchAppKey ) { return _table.CancelApplicationLaunch(pchAppKey); }

        /** Identifies a running application. OpenVR can't always tell which process started in response
        * to a URL. This function allows a URL handler (or the process itself) to identify the app key
        * for the now running application. Passing a process ID of 0 identifies the calling process.
        * The application must be one that's known to the system via a call to AddApplicationManifest. */
        EVRApplicationError IdentifyApplication( uint32_t unProcessId, const char *pchAppKey ) { return _table.IdentifyApplication(unProcessId, pchAppKey); }

        /** Returns the process ID for an application. Return 0 if the application was not found or is not running. */
        uint32_t GetApplicationProcessId( const char *pchAppKey ) { return _table.GetApplicationProcessId(pchAppKey); }

        /** Returns a string for an applications error */
        const char *GetApplicationsErrorNameFromEnum( EVRApplicationError error ) { return _table.GetApplicationsErrorNameFromEnum(error); }

        // ---------------  Application properties  --------------- //

        /** Returns a value for an application property. The required buffer size to fit this value will be returned. */
        uint32_t GetApplicationPropertyString( const char *pchAppKey, EVRApplicationProperty eProperty, char *pchPropertyValueBuffer, uint32_t unPropertyValueBufferLen, EVRApplicationError *peError = nullptr ) { return _table.GetApplicationPropertyString(pchAppKey, eProperty, pchPropertyValueBuffer, unPropertyValueBufferLen, peError); }

        /** Returns a bool value for an application property. Returns false in all error cases. */
        bool GetApplicationPropertyBool( const char *pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError *peError = nullptr ) { return _table.GetApplicationPropertyBool(pchAppKey, eProperty, peError); }

        /** Returns a uint64 value for an application property. Returns 0 in all error cases. */
        uint64_t GetApplicationPropertyUint64( const char *pchAppKey, EVRApplicationProperty eProperty, EVRApplicationError *peError = nullptr ) { return _table.GetApplicationPropertyUint64(pchAppKey, eProperty, peError); }

        /** Sets the application auto-launch flag. This is only valid for applications which return true for VRApplicationProperty_IsDashboardOverlay_Bool. */
        EVRApplicationError SetApplicationAutoLaunch( const char *pchAppKey, bool bAutoLaunch ) { return _table.SetApplicationAutoLaunch(pchAppKey, bAutoLaunch); }

        /** Gets the application auto-launch flag. This is only valid for applications which return true for VRApplicationProperty_IsDashboardOverlay_Bool. */
        bool GetApplicationAutoLaunch( const char *pchAppKey ) { return _table.GetApplicationAutoLaunch(pchAppKey); }

        // ---------------  Transition methods --------------- //

        /** Returns the app key for the application that is starting up */
        EVRApplicationError GetStartingApplication( char *pchAppKeyBuffer, uint32_t unAppKeyBufferLen ) { return _table.GetStartingApplication(pchAppKeyBuffer, unAppKeyBufferLen); }

        /** Returns the application transition state */
        EVRApplicationTransitionState GetTransitionState() { return _table.GetTransitionState(); }

        /** Returns errors that would prevent the specified application from launching immediately. Calling this function will
        * cause the current scene application to quit, so only call it when you are actually about to launch something else.
        * What the caller should do about these failures depends on the failure:
        *   VRApplicationError_OldApplicationQuitting - An existing application has been told to quit. Wait for a VREvent_ProcessQuit
        *                                               and try again.
        *   VRApplicationError_ApplicationAlreadyStarting - This application is already starting. This is a permanent failure.
        *   VRApplicationError_LaunchInProgress       - A different application is already starting. This is a permanent failure.
        *   VRApplicationError_None                   - Go ahead and launch. Everything is clear.
        */
        EVRApplicationError PerformApplicationPrelaunchCheck( const char *pchAppKey ) { return _table.PerformApplicationPrelaunchCheck(pchAppKey); }

        /** Returns a string for an application transition state */
        const char *GetApplicationsTransitionStateNameFromEnum( EVRApplicationTransitionState state ) { return _table.GetApplicationsTransitionStateNameFromEnum(state); }

        /** Returns true if the outgoing scene app has requested a save prompt before exiting */
        bool IsQuitUserPromptRequested() { return _table.IsQuitUserPromptRequested(); }

        /** Starts a subprocess within the calling application. This
        * suppresses all application transition UI and automatically identifies the new executable
        * as part of the same application. On success the calling process should exit immediately.
        * If working directory is NULL or "" the directory portion of the binary path will be
        * the working directory. */
        EVRApplicationError LaunchInternalProcess( const char *pchBinaryPath, const char *pchArguments, const char *pchWorkingDirectory ) { return _table.LaunchInternalProcess(pchBinaryPath, pchArguments, pchWorkingDirectory); }
    };

    static const char * const IVRApplications_Version = "FnTable:IVRApplications_005";

} // namespace vr

// ivrsettings.h
namespace vr
{
    enum EVRSettingsError
    {
        VRSettingsError_None = 0,
        VRSettingsError_IPCFailed = 1,
        VRSettingsError_WriteFailed = 2,
        VRSettingsError_ReadFailed = 3,
    };

    // The maximum length of a settings key
    static const uint32_t k_unMaxSettingsKeyLength = 128;

    struct VR_IVRSettings_FnTable
    {
        const char *(__stdcall *GetSettingsErrorNameFromEnum)( EVRSettingsError eError );
        bool (__stdcall *Sync)( bool bForce, EVRSettingsError *peError);
        bool (__stdcall *GetBool)( const char *pchSection, const char *pchSettingsKey, bool bDefaultValue, EVRSettingsError *peError);
        void (__stdcall *SetBool)( const char *pchSection, const char *pchSettingsKey, bool bValue, EVRSettingsError *peError);
        int32_t (__stdcall *GetInt32)( const char *pchSection, const char *pchSettingsKey, int32_t nDefaultValue, EVRSettingsError *peError);
        void (__stdcall *SetInt32)( const char *pchSection, const char *pchSettingsKey, int32_t nValue, EVRSettingsError *peError);
        float (__stdcall *GetFloat)( const char *pchSection, const char *pchSettingsKey, float flDefaultValue, EVRSettingsError *peError);
        void (__stdcall *SetFloat)( const char *pchSection, const char *pchSettingsKey, float flValue, EVRSettingsError *peError);
        void (__stdcall *GetString)( const char *pchSection, const char *pchSettingsKey, char *pchValue, uint32_t unValueLen, const char *pchDefaultValue, EVRSettingsError *peError);
        void (__stdcall *SetString)( const char *pchSection, const char *pchSettingsKey, const char *pchValue, EVRSettingsError *peError);
        void (__stdcall *RemoveSection)( const char *pchSection, EVRSettingsError *peError);
        void (__stdcall *RemoveKeyInSection)( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError);
    };

    class IVRSettings
    {
        VR_IVRSettings_FnTable _table;
    public:
        const char *GetSettingsErrorNameFromEnum( EVRSettingsError eError ) { return _table.GetSettingsErrorNameFromEnum(eError); }

        // Returns true if file sync occurred (force or settings dirty)
        bool Sync( bool bForce = false, EVRSettingsError *peError = nullptr ) { return _table.Sync(bForce, peError); }

        bool GetBool( const char *pchSection, const char *pchSettingsKey, bool bDefaultValue, EVRSettingsError *peError = nullptr ) { return _table.GetBool(pchSection, pchSettingsKey, bDefaultValue, peError); }
        void SetBool( const char *pchSection, const char *pchSettingsKey, bool bValue, EVRSettingsError *peError = nullptr ) { _table.SetBool(pchSection, pchSettingsKey, bValue, peError); }
        int32_t GetInt32( const char *pchSection, const char *pchSettingsKey, int32_t nDefaultValue, EVRSettingsError *peError = nullptr ) { return _table.GetInt32(pchSection, pchSettingsKey, nDefaultValue, peError); }
        void SetInt32( const char *pchSection, const char *pchSettingsKey, int32_t nValue, EVRSettingsError *peError = nullptr ) { _table.SetInt32(pchSection, pchSettingsKey, nValue, peError); }
        float GetFloat( const char *pchSection, const char *pchSettingsKey, float flDefaultValue, EVRSettingsError *peError = nullptr ) { return _table.GetFloat(pchSection, pchSettingsKey, flDefaultValue, peError); }
        void SetFloat( const char *pchSection, const char *pchSettingsKey, float flValue, EVRSettingsError *peError = nullptr ) { _table.SetFloat(pchSection, pchSettingsKey, flValue, peError); }
        void GetString( const char *pchSection, const char *pchSettingsKey, char *pchValue, uint32_t unValueLen, const char *pchDefaultValue, EVRSettingsError *peError = nullptr ) { _table.GetString(pchSection, pchSettingsKey, pchValue, unValueLen, pchDefaultValue, peError); }
        void SetString( const char *pchSection, const char *pchSettingsKey, const char *pchValue, EVRSettingsError *peError = nullptr ) { _table.SetString(pchSection, pchSettingsKey, pchValue, peError); }

        void RemoveSection( const char *pchSection, EVRSettingsError *peError = nullptr ) { _table.RemoveSection(pchSection, peError); }
        void RemoveKeyInSection( const char *pchSection, const char *pchSettingsKey, EVRSettingsError *peError = nullptr ) { _table.RemoveKeyInSection(pchSection, pchSettingsKey, peError); }
    };

    //-----------------------------------------------------------------------------
    static const char * const IVRSettings_Version = "FnTable:IVRSettings_001";

    //-----------------------------------------------------------------------------
    // steamvr keys

    static const char * const k_pch_SteamVR_Section = "steamvr";
    static const char * const k_pch_SteamVR_RequireHmd_String = "requireHmd";
    static const char * const k_pch_SteamVR_ForcedDriverKey_String = "forcedDriver";
    static const char * const k_pch_SteamVR_ForcedHmdKey_String = "forcedHmd";
    static const char * const k_pch_SteamVR_DisplayDebug_Bool = "displayDebug";
    static const char * const k_pch_SteamVR_DebugProcessPipe_String = "debugProcessPipe";
    static const char * const k_pch_SteamVR_EnableDistortion_Bool = "enableDistortion";
    static const char * const k_pch_SteamVR_DisplayDebugX_Int32 = "displayDebugX";
    static const char * const k_pch_SteamVR_DisplayDebugY_Int32 = "displayDebugY";
    static const char * const k_pch_SteamVR_SendSystemButtonToAllApps_Bool= "sendSystemButtonToAllApps";
    static const char * const k_pch_SteamVR_LogLevel_Int32 = "loglevel";
    static const char * const k_pch_SteamVR_IPD_Float = "ipd";
    static const char * const k_pch_SteamVR_Background_String = "background";
    static const char * const k_pch_SteamVR_BackgroundCameraHeight_Float = "backgroundCameraHeight";
    static const char * const k_pch_SteamVR_BackgroundDomeRadius_Float = "backgroundDomeRadius";
    static const char * const k_pch_SteamVR_Environment_String = "environment";
    static const char * const k_pch_SteamVR_GridColor_String = "gridColor";
    static const char * const k_pch_SteamVR_PlayAreaColor_String = "playAreaColor";
    static const char * const k_pch_SteamVR_ShowStage_Bool = "showStage";
    static const char * const k_pch_SteamVR_ActivateMultipleDrivers_Bool = "activateMultipleDrivers";
    static const char * const k_pch_SteamVR_PowerOffOnExit_Bool = "powerOffOnExit";
    static const char * const k_pch_SteamVR_StandbyAppRunningTimeout_Float = "standbyAppRunningTimeout";
    static const char * const k_pch_SteamVR_StandbyNoAppTimeout_Float = "standbyNoAppTimeout";
    static const char * const k_pch_SteamVR_DirectMode_Bool = "directMode";
    static const char * const k_pch_SteamVR_DirectModeEdidVid_Int32 = "directModeEdidVid";
    static const char * const k_pch_SteamVR_DirectModeEdidPid_Int32 = "directModeEdidPid";
    static const char * const k_pch_SteamVR_UsingSpeakers_Bool = "usingSpeakers";
    static const char * const k_pch_SteamVR_SpeakersForwardYawOffsetDegrees_Float = "speakersForwardYawOffsetDegrees";
    static const char * const k_pch_SteamVR_BaseStationPowerManagement_Bool = "basestationPowerManagement";
    static const char * const k_pch_SteamVR_NeverKillProcesses_Bool = "neverKillProcesses";
    static const char * const k_pch_SteamVR_RenderTargetMultiplier_Float = "renderTargetMultiplier";
    static const char * const k_pch_SteamVR_AllowReprojection_Bool = "allowReprojection";

    //-----------------------------------------------------------------------------
    // lighthouse keys

    static const char * const k_pch_Lighthouse_Section = "driver_lighthouse";
    static const char * const k_pch_Lighthouse_DisableIMU_Bool = "disableimu";
    static const char * const k_pch_Lighthouse_UseDisambiguation_String = "usedisambiguation";
    static const char * const k_pch_Lighthouse_DisambiguationDebug_Int32 = "disambiguationdebug";

    static const char * const k_pch_Lighthouse_PrimaryBasestation_Int32 = "primarybasestation";
    static const char * const k_pch_Lighthouse_LighthouseName_String = "lighthousename";
    static const char * const k_pch_Lighthouse_MaxIncidenceAngleDegrees_Float = "maxincidenceangledegrees";
    static const char * const k_pch_Lighthouse_UseLighthouseDirect_Bool = "uselighthousedirect";
    static const char * const k_pch_Lighthouse_DBHistory_Bool = "dbhistory";

    //-----------------------------------------------------------------------------
    // null keys

    static const char * const k_pch_Null_Section = "driver_null";
    static const char * const k_pch_Null_EnableNullDriver_Bool = "enable";
    static const char * const k_pch_Null_SerialNumber_String = "serialNumber";
    static const char * const k_pch_Null_ModelNumber_String = "modelNumber";
    static const char * const k_pch_Null_WindowX_Int32 = "windowX";
    static const char * const k_pch_Null_WindowY_Int32 = "windowY";
    static const char * const k_pch_Null_WindowWidth_Int32 = "windowWidth";
    static const char * const k_pch_Null_WindowHeight_Int32 = "windowHeight";
    static const char * const k_pch_Null_RenderWidth_Int32 = "renderWidth";
    static const char * const k_pch_Null_RenderHeight_Int32 = "renderHeight";
    static const char * const k_pch_Null_SecondsFromVsyncToPhotons_Float = "secondsFromVsyncToPhotons";
    static const char * const k_pch_Null_DisplayFrequency_Float = "displayFrequency";

    //-----------------------------------------------------------------------------
    // user interface keys
    static const char * const k_pch_UserInterface_Section = "userinterface";
    static const char * const k_pch_UserInterface_StatusAlwaysOnTop_Bool = "StatusAlwaysOnTop";
    static const char * const k_pch_UserInterface_EnableScreenshots_Bool = "EnableScreenshots";

    //-----------------------------------------------------------------------------
    // notification keys
    static const char * const k_pch_Notifications_Section = "notifications";
    static const char * const k_pch_Notifications_DoNotDisturb_Bool = "DoNotDisturb";

    //-----------------------------------------------------------------------------
    // keyboard keys
    static const char * const k_pch_Keyboard_Section = "keyboard";
    static const char * const k_pch_Keyboard_TutorialCompletions = "TutorialCompletions";
    static const char * const k_pch_Keyboard_ScaleX = "ScaleX";
    static const char * const k_pch_Keyboard_ScaleY = "ScaleY";
    static const char * const k_pch_Keyboard_OffsetLeftX = "OffsetLeftX";
    static const char * const k_pch_Keyboard_OffsetRightX = "OffsetRightX";
    static const char * const k_pch_Keyboard_OffsetY = "OffsetY";
    static const char * const k_pch_Keyboard_Smoothing = "Smoothing";

    //-----------------------------------------------------------------------------
    // perf keys
    static const char * const k_pch_Perf_Section = "perfcheck";
    static const char * const k_pch_Perf_HeuristicActive_Bool = "heuristicActive";
    static const char * const k_pch_Perf_NotifyInHMD_Bool = "warnInHMD";
    static const char * const k_pch_Perf_NotifyOnlyOnce_Bool = "warnOnlyOnce";
    static const char * const k_pch_Perf_AllowTimingStore_Bool = "allowTimingStore";
    static const char * const k_pch_Perf_SaveTimingsOnExit_Bool = "saveTimingsOnExit";
    static const char * const k_pch_Perf_TestData_Float = "perfTestData";

    //-----------------------------------------------------------------------------
    // collision bounds keys
    static const char * const k_pch_CollisionBounds_Section = "collisionBounds";
    static const char * const k_pch_CollisionBounds_Style_Int32 = "CollisionBoundsStyle";
    static const char * const k_pch_CollisionBounds_GroundPerimeterOn_Bool = "CollisionBoundsGroundPerimeterOn";
    static const char * const k_pch_CollisionBounds_CenterMarkerOn_Bool = "CollisionBoundsCenterMarkerOn";
    static const char * const k_pch_CollisionBounds_PlaySpaceOn_Bool = "CollisionBoundsPlaySpaceOn";
    static const char * const k_pch_CollisionBounds_FadeDistance_Float = "CollisionBoundsFadeDistance";
    static const char * const k_pch_CollisionBounds_ColorGammaR_Int32 = "CollisionBoundsColorGammaR";
    static const char * const k_pch_CollisionBounds_ColorGammaG_Int32 = "CollisionBoundsColorGammaG";
    static const char * const k_pch_CollisionBounds_ColorGammaB_Int32 = "CollisionBoundsColorGammaB";
    static const char * const k_pch_CollisionBounds_ColorGammaA_Int32 = "CollisionBoundsColorGammaA";

    //-----------------------------------------------------------------------------
    // camera keys
    static const char * const k_pch_Camera_Section = "camera";
    static const char * const k_pch_Camera_EnableCamera_Bool = "enableCamera";
    static const char * const k_pch_Camera_EnableCameraInDashboard_Bool = "enableCameraInDashboard";
    static const char * const k_pch_Camera_EnableCameraForCollisionBounds_Bool = "enableCameraForCollisionBounds";
    static const char * const k_pch_Camera_EnableCameraForRoomView_Bool = "enableCameraForRoomView";
    static const char * const k_pch_Camera_BoundsColorGammaR_Int32 = "cameraBoundsColorGammaR";
    static const char * const k_pch_Camera_BoundsColorGammaG_Int32 = "cameraBoundsColorGammaG";
    static const char * const k_pch_Camera_BoundsColorGammaB_Int32 = "cameraBoundsColorGammaB";
    static const char * const k_pch_Camera_BoundsColorGammaA_Int32 = "cameraBoundsColorGammaA";

    //-----------------------------------------------------------------------------
    // audio keys
    static const char * const k_pch_audio_Section = "audio";
    static const char * const k_pch_audio_OnPlaybackDevice_String = "onPlaybackDevice";
    static const char * const k_pch_audio_OnRecordDevice_String = "onRecordDevice";
    static const char * const k_pch_audio_OnPlaybackMirrorDevice_String = "onPlaybackMirrorDevice";
    static const char * const k_pch_audio_OffPlaybackDevice_String = "offPlaybackDevice";
    static const char * const k_pch_audio_OffRecordDevice_String = "offRecordDevice";
    static const char * const k_pch_audio_VIVEHDMIGain = "viveHDMIGain";

    //-----------------------------------------------------------------------------
    // model skin keys
    static const char * const k_pch_modelskin_Section = "modelskins";

} // namespace vr

// ivrchaperone.h
namespace vr
{

#if defined(__linux__) || defined(__APPLE__)
    // The 32-bit version of gcc has the alignment requirement for uint64 and double set to
    // 4 meaning that even with #pragma pack(8) these types will only be four-byte aligned.
    // The 64-bit version of gcc has the alignment requirement for these types set to
    // 8 meaning that unless we use #pragma pack(4) our structures will get bigger.
    // The 64-bit structure packing has to match the 32-bit structure packing for each platform.
    #pragma pack( push, 4 )
#else
    #pragma pack( push, 8 )
#endif

enum ChaperoneCalibrationState
{
    // OK!
    ChaperoneCalibrationState_OK = 1,                                   // Chaperone is fully calibrated and working correctly

    // Warnings
    ChaperoneCalibrationState_Warning = 100,
    ChaperoneCalibrationState_Warning_BaseStationMayHaveMoved = 101,    // A base station thinks that it might have moved
    ChaperoneCalibrationState_Warning_BaseStationRemoved = 102,         // There are less base stations than when calibrated
    ChaperoneCalibrationState_Warning_SeatedBoundsInvalid = 103,        // Seated bounds haven't been calibrated for the current tracking center

    // Errors
    ChaperoneCalibrationState_Error = 200,                              // The UniverseID is invalid
    ChaperoneCalibrationState_Error_BaseStationUninitalized = 201,      // Tracking center hasn't be calibrated for at least one of the base stations
    ChaperoneCalibrationState_Error_BaseStationConflict = 202,          // Tracking center is calibrated, but base stations disagree on the tracking space
    ChaperoneCalibrationState_Error_PlayAreaInvalid = 203,              // Play Area hasn't been calibrated for the current tracking center
    ChaperoneCalibrationState_Error_CollisionBoundsInvalid = 204,       // Collision Bounds haven't been calibrated for the current tracking center
};


/** HIGH LEVEL TRACKING SPACE ASSUMPTIONS:
* 0,0,0 is the preferred standing area center.
* 0Y is the floor height.
* -Z is the preferred forward facing direction. */
struct VR_IVRChaperone_FnTable
{
    ChaperoneCalibrationState (__stdcall *GetCalibrationState)();
    bool (__stdcall *GetPlayAreaSize)( float *pSizeX, float *pSizeZ );
    bool (__stdcall *GetPlayAreaRect)( HmdQuad_t *rect );
    void (__stdcall *ReloadInfo)( void );
    void (__stdcall *SetSceneColor)( HmdColor_t color );
    void (__stdcall *GetBoundsColor)( HmdColor_t *pOutputColorArray, int nNumOutputColors, float flCollisionBoundsFadeDistance, HmdColor_t *pOutputCameraColor );
    bool (__stdcall *AreBoundsVisible)();
    void (__stdcall *ForceBoundsVisible)( bool bForce );
};

class IVRChaperone
{
    VR_IVRChaperone_FnTable _table;
public:

    /** Get the current state of Chaperone calibration. This state can change at any time during a session due to physical base station changes. **/
    ChaperoneCalibrationState GetCalibrationState() { return _table.GetCalibrationState(); }

    /** Returns the width and depth of the Play Area (formerly named Soft Bounds) in X and Z.
    * Tracking space center (0,0,0) is the center of the Play Area. **/
    bool GetPlayAreaSize( float *pSizeX, float *pSizeZ ) { return _table.GetPlayAreaSize(pSizeX, pSizeZ); }

    /** Returns the 4 corner positions of the Play Area (formerly named Soft Bounds).
    * Corners are in counter-clockwise order.
    * Standing center (0,0,0) is the center of the Play Area.
    * It's a rectangle.
    * 2 sides are parallel to the X axis and 2 sides are parallel to the Z axis.
    * Height of every corner is 0Y (on the floor). **/
    bool GetPlayAreaRect( HmdQuad_t *rect ) { return _table.GetPlayAreaRect(rect); }

    /** Reload Chaperone data from the .vrchap file on disk. */
    void ReloadInfo( void ) { _table.ReloadInfo(); }

    /** Optionally give the chaperone system a hit about the color and brightness in the scene **/
    void SetSceneColor( HmdColor_t color ) { _table.SetSceneColor(color); }

    /** Get the current chaperone bounds draw color and brightness **/
    void GetBoundsColor( HmdColor_t *pOutputColorArray, int nNumOutputColors, float flCollisionBoundsFadeDistance, HmdColor_t *pOutputCameraColor ) { _table.GetBoundsColor(pOutputColorArray, nNumOutputColors, flCollisionBoundsFadeDistance, pOutputCameraColor); }

    /** Determine whether the bounds are showing right now **/
    bool AreBoundsVisible() { return _table.AreBoundsVisible(); }

    /** Force the bounds to show, mostly for utilities **/
    void ForceBoundsVisible( bool bForce ) { _table.ForceBoundsVisible(bForce); }
};

static const char * const IVRChaperone_Version = "FnTable:IVRChaperone_003";

#pragma pack( pop )

}

// ivrchaperonesetup.h
namespace vr
{

enum EChaperoneConfigFile
{
    EChaperoneConfigFile_Live = 1,      // The live chaperone config, used by most applications and games
    EChaperoneConfigFile_Temp = 2,      // The temporary chaperone config, used to live-preview collision bounds in room setup
};

enum EChaperoneImportFlags
{
    EChaperoneImport_BoundsOnly = 0x0001,
};

/** Manages the working copy of the chaperone info. By default this will be the same as the
* live copy. Any changes made with this interface will stay in the working copy until
* CommitWorkingCopy() is called, at which point the working copy and the live copy will be
* the same again. */
struct VR_IVRChaperoneSetup_FnTable
{
    bool (__stdcall *CommitWorkingCopy)( EChaperoneConfigFile configFile );
    void (__stdcall *RevertWorkingCopy)();
    bool (__stdcall *GetWorkingPlayAreaSize)( float *pSizeX, float *pSizeZ );
    bool (__stdcall *GetWorkingPlayAreaRect)( HmdQuad_t *rect );
    bool (__stdcall *GetWorkingCollisionBoundsInfo)(  HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount );
    bool (__stdcall *GetLiveCollisionBoundsInfo)(  HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount );
    bool (__stdcall *GetWorkingSeatedZeroPoseToRawTrackingPose)( HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose );
    bool (__stdcall *GetWorkingStandingZeroPoseToRawTrackingPose)( HmdMatrix34_t *pmatStandingZeroPoseToRawTrackingPose );
    void (__stdcall *SetWorkingPlayAreaSize)( float sizeX, float sizeZ );
    void (__stdcall *SetWorkingCollisionBoundsInfo)(  HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount );
    void (__stdcall *SetWorkingSeatedZeroPoseToRawTrackingPose)( const HmdMatrix34_t *pMatSeatedZeroPoseToRawTrackingPose );
    void (__stdcall *SetWorkingStandingZeroPoseToRawTrackingPose)( const HmdMatrix34_t *pMatStandingZeroPoseToRawTrackingPose );
    void (__stdcall *ReloadFromDisk)( EChaperoneConfigFile configFile );
    bool (__stdcall *GetLiveSeatedZeroPoseToRawTrackingPose)( HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose );
    void (__stdcall *SetWorkingCollisionBoundsTagsInfo)(  uint8_t *pTagsBuffer, uint32_t unTagCount );
    bool (__stdcall *GetLiveCollisionBoundsTagsInfo)(  uint8_t *pTagsBuffer, uint32_t *punTagCount );
    bool (__stdcall *SetWorkingPhysicalBoundsInfo)(  HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount );
    bool (__stdcall *GetLivePhysicalBoundsInfo)(  HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount );
    bool (__stdcall *ExportLiveToBuffer)(  char *pBuffer, uint32_t *pnBufferLength );
    bool (__stdcall *ImportFromBufferToWorking)( const char *pBuffer, uint32_t nImportFlags );
};

class IVRChaperoneSetup
{
    VR_IVRChaperoneSetup_FnTable _table;
public:

    /** Saves the current working copy to disk */
    bool CommitWorkingCopy( EChaperoneConfigFile configFile ) { return _table.CommitWorkingCopy(configFile); }

    /** Reverts the working copy to match the live chaperone calibration.
    * To modify existing data this MUST be do WHILE getting a non-error ChaperoneCalibrationStatus.
    * Only after this should you do gets and sets on the existing data. */
    void RevertWorkingCopy() { _table.RevertWorkingCopy(); }

    /** Returns the width and depth of the Play Area (formerly named Soft Bounds) in X and Z from the working copy.
    * Tracking space center (0,0,0) is the center of the Play Area. */
    bool GetWorkingPlayAreaSize( float *pSizeX, float *pSizeZ ) { return _table.GetWorkingPlayAreaSize(pSizeX, pSizeZ); }

    /** Returns the 4 corner positions of the Play Area (formerly named Soft Bounds) from the working copy.
    * Corners are in clockwise order.
    * Tracking space center (0,0,0) is the center of the Play Area.
    * It's a rectangle.
    * 2 sides are parallel to the X axis and 2 sides are parallel to the Z axis.
    * Height of every corner is 0Y (on the floor). **/
    bool GetWorkingPlayAreaRect( HmdQuad_t *rect ) { return _table.GetWorkingPlayAreaRect(rect); }

    /** Returns the number of Quads if the buffer points to null. Otherwise it returns Quads
    * into the buffer up to the max specified from the working copy. */
    bool GetWorkingCollisionBoundsInfo( VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount ) { return _table.GetWorkingCollisionBoundsInfo(pQuadsBuffer, punQuadsCount); }

    /** Returns the number of Quads if the buffer points to null. Otherwise it returns Quads
    * into the buffer up to the max specified. */
    bool GetLiveCollisionBoundsInfo( VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount ) { return _table.GetLiveCollisionBoundsInfo(pQuadsBuffer, punQuadsCount); }

    /** Returns the preferred seated position from the working copy. */
    bool GetWorkingSeatedZeroPoseToRawTrackingPose( HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose ) { return _table.GetWorkingSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose); }

    /** Returns the standing origin from the working copy. */
    bool GetWorkingStandingZeroPoseToRawTrackingPose( HmdMatrix34_t *pmatStandingZeroPoseToRawTrackingPose ) { return _table.GetWorkingStandingZeroPoseToRawTrackingPose(pmatStandingZeroPoseToRawTrackingPose); }

    /** Sets the Play Area in the working copy. */
    void SetWorkingPlayAreaSize( float sizeX, float sizeZ ) { _table.SetWorkingPlayAreaSize(sizeX, sizeZ); }

    /** Sets the Collision Bounds in the working copy. */
    void SetWorkingCollisionBoundsInfo( VR_ARRAY_COUNT(unQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount ) { _table.SetWorkingCollisionBoundsInfo(pQuadsBuffer, unQuadsCount); }

    /** Sets the preferred seated position in the working copy. */
    void SetWorkingSeatedZeroPoseToRawTrackingPose( const HmdMatrix34_t *pMatSeatedZeroPoseToRawTrackingPose ) { _table.SetWorkingSeatedZeroPoseToRawTrackingPose(pMatSeatedZeroPoseToRawTrackingPose); }

    /** Sets the preferred standing position in the working copy. */
    void SetWorkingStandingZeroPoseToRawTrackingPose( const HmdMatrix34_t *pMatStandingZeroPoseToRawTrackingPose ) { _table.SetWorkingStandingZeroPoseToRawTrackingPose(pMatStandingZeroPoseToRawTrackingPose); }

    /** Tear everything down and reload it from the file on disk */
    void ReloadFromDisk( EChaperoneConfigFile configFile ) { _table.ReloadFromDisk(configFile); }

    /** Returns the preferred seated position. */
    bool GetLiveSeatedZeroPoseToRawTrackingPose( HmdMatrix34_t *pmatSeatedZeroPoseToRawTrackingPose ) { return _table.GetLiveSeatedZeroPoseToRawTrackingPose(pmatSeatedZeroPoseToRawTrackingPose); }

    void SetWorkingCollisionBoundsTagsInfo( VR_ARRAY_COUNT(unTagCount) uint8_t *pTagsBuffer, uint32_t unTagCount ) { _table.SetWorkingCollisionBoundsTagsInfo(pTagsBuffer, unTagCount); }
    bool GetLiveCollisionBoundsTagsInfo( VR_OUT_ARRAY_COUNT(punTagCount) uint8_t *pTagsBuffer, uint32_t *punTagCount ) { return _table.GetLiveCollisionBoundsTagsInfo(pTagsBuffer, punTagCount); }

    bool SetWorkingPhysicalBoundsInfo( VR_ARRAY_COUNT(unQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t unQuadsCount ) { return _table.SetWorkingPhysicalBoundsInfo(pQuadsBuffer, unQuadsCount); }
    bool GetLivePhysicalBoundsInfo( VR_OUT_ARRAY_COUNT(punQuadsCount) HmdQuad_t *pQuadsBuffer, uint32_t* punQuadsCount ) { return _table.GetLivePhysicalBoundsInfo(pQuadsBuffer, punQuadsCount); }

    bool ExportLiveToBuffer( VR_OUT_STRING() char *pBuffer, uint32_t *pnBufferLength ) { return _table.ExportLiveToBuffer(pBuffer, pnBufferLength); }
    bool ImportFromBufferToWorking( const char *pBuffer, uint32_t nImportFlags ) { return _table.ImportFromBufferToWorking(pBuffer, nImportFlags); }
};

static const char * const IVRChaperoneSetup_Version = "FnTable:IVRChaperoneSetup_005";


}

// ivrcompositor.h
namespace vr
{

#if defined(__linux__) || defined(__APPLE__)
    // The 32-bit version of gcc has the alignment requirement for uint64 and double set to
    // 4 meaning that even with #pragma pack(8) these types will only be four-byte aligned.
    // The 64-bit version of gcc has the alignment requirement for these types set to
    // 8 meaning that unless we use #pragma pack(4) our structures will get bigger.
    // The 64-bit structure packing has to match the 32-bit structure packing for each platform.
    #pragma pack( push, 4 )
#else
    #pragma pack( push, 8 )
#endif

/** Errors that can occur with the VR compositor */
enum EVRCompositorError
{
    VRCompositorError_None                      = 0,
    VRCompositorError_RequestFailed             = 1,
    VRCompositorError_IncompatibleVersion       = 100,
    VRCompositorError_DoNotHaveFocus            = 101,
    VRCompositorError_InvalidTexture            = 102,
    VRCompositorError_IsNotSceneApplication     = 103,
    VRCompositorError_TextureIsOnWrongDevice    = 104,
    VRCompositorError_TextureUsesUnsupportedFormat = 105,
    VRCompositorError_SharedTexturesNotSupported = 106,
    VRCompositorError_IndexOutOfRange           = 107,
    VRCompositorError_ScreenshotAlreadyInProgress = 108,
};

const uint32_t VRCompositor_ReprojectionReason_Cpu = 0x01;
const uint32_t VRCompositor_ReprojectionReason_Gpu = 0x02;

/** Provides a single frame's timing information to the app */
struct Compositor_FrameTiming
{
    uint32_t m_nSize; // Set to sizeof( Compositor_FrameTiming )
    uint32_t m_nFrameIndex;
    uint32_t m_nNumFramePresents; // number of times this frame was presented
    uint32_t m_nNumDroppedFrames; // number of additional times previous frame was scanned out

    /** Absolute time reference for comparing frames.  This aligns with the vsync that running start is relative to. */
    double m_flSystemTimeInSeconds;

    /** These times may include work from other processes due to OS scheduling.
    * The fewer packets of work these are broken up into, the less likely this will happen.
    * GPU work can be broken up by calling Flush.  This can sometimes be useful to get the GPU started
    * processing that work earlier in the frame. */
    float m_flSceneRenderGpuMs; // time spent rendering the scene
    float m_flTotalRenderGpuMs; // time between work submitted immediately after present (ideally vsync) until the end of compositor submitted work
    float m_flCompositorRenderGpuMs; // time spend performing distortion correction, rendering chaperone, overlays, etc.
    float m_flCompositorRenderCpuMs; // time spent on cpu submitting the above work for this frame
    float m_flCompositorIdleCpuMs; // time spent waiting for running start (application could have used this much more time)

    /** Miscellaneous measured intervals. */
    float m_flClientFrameIntervalMs; // time between calls to WaitGetPoses
    float m_flPresentCallCpuMs; // time blocked on call to present (usually 0.0, but can go long)
    float m_flWaitForPresentCpuMs; // time spent spin-waiting for frame index to change (not near-zero indicates wait object failure)
    float m_flSubmitFrameMs; // time spent in IVRCompositor::Submit (not near-zero indicates driver issue)

    /** The following are all relative to this frame's SystemTimeInSeconds */
    float m_flWaitGetPosesCalledMs;
    float m_flNewPosesReadyMs;
    float m_flNewFrameReadyMs; // second call to IVRCompositor::Submit
    float m_flCompositorUpdateStartMs;
    float m_flCompositorUpdateEndMs;
    float m_flCompositorRenderStartMs;

    vr::TrackedDevicePose_t m_HmdPose; // pose used by app to render this frame
    int32_t m_nFidelityLevel; // app reported value

    uint32_t m_nReprojectionFlags;
};

/** Cumulative stats for current application.  These are not cleared until a new app connects,
* but they do stop accumulating once the associated app disconnects. */
struct Compositor_CumulativeStats
{
    uint32_t m_nPid; // Process id associated with these stats (may no longer be running).
    uint32_t m_nNumFramePresents; // total number of times we called present (includes reprojected frames)
    uint32_t m_nNumDroppedFrames; // total number of times an old frame was re-scanned out (without reprojection)
    uint32_t m_nNumReprojectedFrames; // total number of times a frame was scanned out a second time with reprojection

    /** Values recorded at startup before application has fully faded in the first time. */
    uint32_t m_nNumFramePresentsOnStartup;
    uint32_t m_nNumDroppedFramesOnStartup;
    uint32_t m_nNumReprojectedFramesOnStartup;

    /** Applications may explicitly fade to the compositor.  This is usually to handle level transitions, and loading often causes
    * system wide hitches.  The following stats are collected during this period.  Does not include values recorded during startup. */
    uint32_t m_nNumLoading;
    uint32_t m_nNumFramePresentsLoading;
    uint32_t m_nNumDroppedFramesLoading;
    uint32_t m_nNumReprojectedFramesLoading;

    /** If we don't get a new frame from the app in less than 2.5 frames, then we assume the app has hung and start
    * fading back to the compositor.  The following stats are a result of this, and are a subset of those recorded above.
    * Does not include values recorded during start up or loading. */
    uint32_t m_nNumTimedOut;
    uint32_t m_nNumFramePresentsTimedOut;
    uint32_t m_nNumDroppedFramesTimedOut;
    uint32_t m_nNumReprojectedFramesTimedOut;
};

#pragma pack( pop )

/** Allows the application to interact with the compositor */
struct VR_IVRCompositor_FnTable
{
    void (__stdcall *SetTrackingSpace)( ETrackingUniverseOrigin eOrigin );
    ETrackingUniverseOrigin (__stdcall *GetTrackingSpace)();
    EVRCompositorError (__stdcall *WaitGetPoses)(  TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
         TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount );
    EVRCompositorError (__stdcall *GetLastPoses)(  TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
         TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount );
    EVRCompositorError (__stdcall *GetLastPoseForTrackedDeviceIndex)( TrackedDeviceIndex_t unDeviceIndex, TrackedDevicePose_t *pOutputPose, TrackedDevicePose_t *pOutputGamePose );
    EVRCompositorError (__stdcall *Submit)( EVREye eEye, const Texture_t *pTexture, const VRTextureBounds_t* pBounds, EVRSubmitFlags nSubmitFlags);
    void (__stdcall *ClearLastSubmittedFrame)();
    void (__stdcall *PostPresentHandoff)();
    bool (__stdcall *GetFrameTiming)( Compositor_FrameTiming *pTiming, uint32_t unFramesAgo);
    float (__stdcall *GetFrameTimeRemaining)();
    void (__stdcall *GetCumulativeStats)( Compositor_CumulativeStats *pStats, uint32_t nStatsSizeInBytes );
    void (__stdcall *FadeToColor)( float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground);
    void (__stdcall *FadeGrid)( float fSeconds, bool bFadeIn );
    EVRCompositorError (__stdcall *SetSkyboxOverride)(  const Texture_t *pTextures, uint32_t unTextureCount );
    void (__stdcall *ClearSkyboxOverride)();
    void (__stdcall *CompositorBringToFront)();
    void (__stdcall *CompositorGoToBack)();
    void (__stdcall *CompositorQuit)();
    bool (__stdcall *IsFullscreen)();
    uint32_t (__stdcall *GetCurrentSceneFocusProcess)();
    uint32_t (__stdcall *GetLastFrameRenderer)();
    bool (__stdcall *CanRenderScene)();
    void (__stdcall *ShowMirrorWindow)();
    void (__stdcall *HideMirrorWindow)();
    bool (__stdcall *IsMirrorWindowVisible)();
    void (__stdcall *CompositorDumpImages)();
    bool (__stdcall *ShouldAppRenderWithLowResources)();
    void (__stdcall *ForceInterleavedReprojectionOn)( bool bOverride );
    void (__stdcall *ForceReconnectProcess)();
    void (__stdcall *SuspendRendering)( bool bSuspend );
    vr::EVRCompositorError (__stdcall *RequestScreenshot)( vr::EVRScreenshotType type, const char *pchDestinationFileName, const char *pchVRDestinationFileName );
    vr::EVRScreenshotType (__stdcall *GetCurrentScreenshotType)();
    vr::EVRCompositorError (__stdcall *GetMirrorTextureD3D11)( vr::EVREye eEye, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView );
    vr::EVRCompositorError (__stdcall *GetMirrorTextureGL)( vr::EVREye eEye, vr::glUInt_t *pglTextureId, vr::glSharedTextureHandle_t *pglSharedTextureHandle );
    bool (__stdcall *ReleaseSharedGLTexture)( vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle );
    void (__stdcall *LockGLSharedTextureForAccess)( vr::glSharedTextureHandle_t glSharedTextureHandle );
    void (__stdcall *UnlockGLSharedTextureForAccess)( vr::glSharedTextureHandle_t glSharedTextureHandle );
};

class IVRCompositor
{
    VR_IVRCompositor_FnTable _table;
public:
    /** Sets tracking space returned by WaitGetPoses */
    void SetTrackingSpace( ETrackingUniverseOrigin eOrigin ) { _table.SetTrackingSpace(eOrigin); }

    /** Gets current tracking space returned by WaitGetPoses */
    ETrackingUniverseOrigin GetTrackingSpace() { return _table.GetTrackingSpace(); }

    /** Returns pose(s) to use to render scene (and optionally poses predicted two frames out for gameplay). */
    EVRCompositorError WaitGetPoses( VR_ARRAY_COUNT(unRenderPoseArrayCount) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
        VR_ARRAY_COUNT(unGamePoseArrayCount) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount ) { return _table.WaitGetPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }

    /** Get the last set of poses returned by WaitGetPoses. */
    EVRCompositorError GetLastPoses( VR_ARRAY_COUNT( unRenderPoseArrayCount ) TrackedDevicePose_t* pRenderPoseArray, uint32_t unRenderPoseArrayCount,
        VR_ARRAY_COUNT( unGamePoseArrayCount ) TrackedDevicePose_t* pGamePoseArray, uint32_t unGamePoseArrayCount ) { return _table.GetLastPoses(pRenderPoseArray, unRenderPoseArrayCount, pGamePoseArray, unGamePoseArrayCount); }

    /** Interface for accessing last set of poses returned by WaitGetPoses one at a time.
    * Returns VRCompositorError_IndexOutOfRange if unDeviceIndex not less than k_unMaxTrackedDeviceCount otherwise VRCompositorError_None.
    * It is okay to pass NULL for either pose if you only want one of the values. */
    EVRCompositorError GetLastPoseForTrackedDeviceIndex( TrackedDeviceIndex_t unDeviceIndex, TrackedDevicePose_t *pOutputPose, TrackedDevicePose_t *pOutputGamePose ) { return _table.GetLastPoseForTrackedDeviceIndex(unDeviceIndex, pOutputPose, pOutputGamePose); }

    /** Updated scene texture to display. If pBounds is NULL the entire texture will be used.  If called from an OpenGL app, consider adding a glFlush after
    * Submitting both frames to signal the driver to start processing, otherwise it may wait until the command buffer fills up, causing the app to miss frames.
    *
    * OpenGL dirty state:
    *   glBindTexture
    */
    EVRCompositorError Submit( EVREye eEye, const Texture_t *pTexture, const VRTextureBounds_t* pBounds = 0, EVRSubmitFlags nSubmitFlags = Submit_Default ) { return _table.Submit(eEye, pTexture, pBounds, nSubmitFlags); }

    /** Clears the frame that was sent with the last call to Submit. This will cause the
    * compositor to show the grid until Submit is called again. */
    void ClearLastSubmittedFrame() { _table.ClearLastSubmittedFrame(); }

    /** Call immediately after presenting your app's window (i.e. companion window) to unblock the compositor.
    * This is an optional call, which only needs to be used if you can't instead call WaitGetPoses immediately after Present.
    * For example, if your engine's render and game loop are not on separate threads, or blocking the render thread until 3ms before the next vsync would
    * introduce a deadlock of some sort.  This function tells the compositor that you have finished all rendering after having Submitted buffers for both
    * eyes, and it is free to start its rendering work.  This should only be called from the same thread you are rendering on. */
    void PostPresentHandoff() { _table.PostPresentHandoff(); }

    /** Returns true if timing data is filled it.  Sets oldest timing info if nFramesAgo is larger than the stored history.
    * Be sure to set timing.size = sizeof(Compositor_FrameTiming) on struct passed in before calling this function. */
    bool GetFrameTiming( Compositor_FrameTiming *pTiming, uint32_t unFramesAgo = 0 ) { return _table.GetFrameTiming(pTiming, unFramesAgo); }

    /** Returns the time in seconds left in the current (as identified by FrameTiming's frameIndex) frame.
    * Due to "running start", this value may roll over to the next frame before ever reaching 0.0. */
    float GetFrameTimeRemaining() { return _table.GetFrameTimeRemaining(); }

    /** Fills out stats accumulated for the last connected application.  Pass in sizeof( Compositor_CumulativeStats ) as second parameter. */
    void GetCumulativeStats( Compositor_CumulativeStats *pStats, uint32_t nStatsSizeInBytes ) { _table.GetCumulativeStats(pStats, nStatsSizeInBytes); }

    /** Fades the view on the HMD to the specified color. The fade will take fSeconds, and the color values are between
    * 0.0 and 1.0. This color is faded on top of the scene based on the alpha parameter. Removing the fade color instantly
    * would be FadeToColor( 0.0, 0.0, 0.0, 0.0, 0.0 ).  Values are in un-premultiplied alpha space. */
    void FadeToColor( float fSeconds, float fRed, float fGreen, float fBlue, float fAlpha, bool bBackground = false ) { _table.FadeToColor(fSeconds, fRed, fGreen, fBlue, fAlpha, bBackground); }

    /** Fading the Grid in or out in fSeconds */
    void FadeGrid( float fSeconds, bool bFadeIn ) { _table.FadeGrid(fSeconds, bFadeIn); }

    /** Override the skybox used in the compositor (e.g. for during level loads when the app can't feed scene images fast enough)
    * Order is Front, Back, Left, Right, Top, Bottom.  If only a single texture is passed, it is assumed in lat-long format.
    * If two are passed, it is assumed a lat-long stereo pair. */
    EVRCompositorError SetSkyboxOverride( VR_ARRAY_COUNT( unTextureCount ) const Texture_t *pTextures, uint32_t unTextureCount ) { return _table.SetSkyboxOverride(pTextures, unTextureCount); }

    /** Resets compositor skybox back to defaults. */
    void ClearSkyboxOverride() { _table.ClearSkyboxOverride(); }

    /** Brings the compositor window to the front. This is useful for covering any other window that may be on the HMD
    * and is obscuring the compositor window. */
    void CompositorBringToFront() { _table.CompositorBringToFront(); }

    /** Pushes the compositor window to the back. This is useful for allowing other applications to draw directly to the HMD. */
    void CompositorGoToBack() { _table.CompositorGoToBack(); }

    /** Tells the compositor process to clean up and exit. You do not need to call this function at shutdown. Under normal
    * circumstances the compositor will manage its own life cycle based on what applications are running. */
    void CompositorQuit() { _table.CompositorQuit(); }

    /** Return whether the compositor is fullscreen */
    bool IsFullscreen() { return _table.IsFullscreen(); }

    /** Returns the process ID of the process that is currently rendering the scene */
    uint32_t GetCurrentSceneFocusProcess() { return _table.GetCurrentSceneFocusProcess(); }

    /** Returns the process ID of the process that rendered the last frame (or 0 if the compositor itself rendered the frame.)
    * Returns 0 when fading out from an app and the app's process Id when fading into an app. */
    uint32_t GetLastFrameRenderer() { return _table.GetLastFrameRenderer(); }

    /** Returns true if the current process has the scene focus */
    bool CanRenderScene() { return _table.CanRenderScene(); }

    /** Creates a window on the primary monitor to display what is being shown in the headset. */
    void ShowMirrorWindow() { _table.ShowMirrorWindow(); }

    /** Closes the mirror window. */
    void HideMirrorWindow() { _table.HideMirrorWindow(); }

    /** Returns true if the mirror window is shown. */
    bool IsMirrorWindowVisible() { return _table.IsMirrorWindowVisible(); }

    /** Writes all images that the compositor knows about (including overlays) to a 'screenshots' folder in the SteamVR runtime root. */
    void CompositorDumpImages() { _table.CompositorDumpImages(); }

    /** Let an app know it should be rendering with low resources. */
    bool ShouldAppRenderWithLowResources() { return _table.ShouldAppRenderWithLowResources(); }

    /** Override interleaved reprojection logic to force on. */
    void ForceInterleavedReprojectionOn( bool bOverride ) { _table.ForceInterleavedReprojectionOn(bOverride); }

    /** Force reconnecting to the compositor process. */
    void ForceReconnectProcess() { _table.ForceReconnectProcess(); }

    /** Temporarily suspends rendering (useful for finer control over scene transitions). */
    void SuspendRendering( bool bSuspend ) { _table.SuspendRendering(bSuspend); }

    /** Request a screenshot of the requested type, application
     *  will get an event that the screen shot has started.  The
     *  application should turn off any stenciling and max out
     *  quality for the next frames and include the Screenshot flag
     *  when calling Submit so that the compositor knows the
     *  screenshot.  The application should keep the higher qualtity
     *  and submitted with the ScreenShot flag until gets a
     *  screenshot End event.  It can take several frames for a
     *  cubemap to be capture for example. The first file is a
     *  boring 2D view used for preview, the second is the actual
     *  capture of the requested type.  They are the same for
     *  VRScreenshotType_Mono */
    vr::EVRCompositorError RequestScreenshot( vr::EVRScreenshotType type, const char *pchDestinationFileName, const char *pchVRDestinationFileName ) { return _table.RequestScreenshot(type, pchDestinationFileName, pchVRDestinationFileName); }

    /** Returns the current screenshot type if a screenshot is currently being captured **/
    vr::EVRScreenshotType GetCurrentScreenshotType() { return _table.GetCurrentScreenshotType(); }

    /** Opens a shared D3D11 texture with the undistorted composited image for each eye. */
    vr::EVRCompositorError GetMirrorTextureD3D11( vr::EVREye eEye, void *pD3D11DeviceOrResource, void **ppD3D11ShaderResourceView ) { return _table.GetMirrorTextureD3D11(eEye, pD3D11DeviceOrResource, ppD3D11ShaderResourceView); }

    /** Access to mirror textures from OpenGL. */
    vr::EVRCompositorError GetMirrorTextureGL( vr::EVREye eEye, vr::glUInt_t *pglTextureId, vr::glSharedTextureHandle_t *pglSharedTextureHandle ) { return _table.GetMirrorTextureGL(eEye, pglTextureId, pglSharedTextureHandle); }
    bool ReleaseSharedGLTexture( vr::glUInt_t glTextureId, vr::glSharedTextureHandle_t glSharedTextureHandle ) { return _table.ReleaseSharedGLTexture(glTextureId, glSharedTextureHandle); }
    void LockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle ) { _table.LockGLSharedTextureForAccess(glSharedTextureHandle); }
    void UnlockGLSharedTextureForAccess( vr::glSharedTextureHandle_t glSharedTextureHandle ) { _table.UnlockGLSharedTextureForAccess(glSharedTextureHandle); }
};

static const char * const IVRCompositor_Version = "FnTable:IVRCompositor_015";

} // namespace vr



// ivrnotifications.h
namespace vr
{

#if defined(__linux__) || defined(__APPLE__)
    // The 32-bit version of gcc has the alignment requirement for uint64 and double set to
    // 4 meaning that even with #pragma pack(8) these types will only be four-byte aligned.
    // The 64-bit version of gcc has the alignment requirement for these types set to
    // 8 meaning that unless we use #pragma pack(4) our structures will get bigger.
    // The 64-bit structure packing has to match the 32-bit structure packing for each platform.
    #pragma pack( push, 4 )
#else
    #pragma pack( push, 8 )
#endif

// Used for passing graphic data
struct NotificationBitmap_t
{
    NotificationBitmap_t()
        : m_pImageData( nullptr )
        , m_nWidth( 0 )
        , m_nHeight( 0 )
        , m_nBytesPerPixel( 0 )
    {
    };

    void *m_pImageData;
    int32_t m_nWidth;
    int32_t m_nHeight;
    int32_t m_nBytesPerPixel;
};


/** Be aware that the notification type is used as 'priority' to pick the next notification */
enum EVRNotificationType
{
    /** Transient notifications are automatically hidden after a period of time set by the user.
    * They are used for things like information and chat messages that do not require user interaction. */
    EVRNotificationType_Transient = 0,

    /** Persistent notifications are shown to the user until they are hidden by calling RemoveNotification().
    * They are used for things like phone calls and alarms that require user interaction. */
    EVRNotificationType_Persistent = 1,

    /** System notifications are shown no matter what. It is expected, that the ulUserValue is used as ID.
     * If there is already a system notification in the queue with that ID it is not accepted into the queue
     * to prevent spamming with system notification */
    EVRNotificationType_Transient_SystemWithUserValue = 2,
};

enum EVRNotificationStyle
{
    /** Creates a notification with minimal external styling. */
    EVRNotificationStyle_None = 0,

    /** Used for notifications about overlay-level status. In Steam this is used for events like downloads completing. */
    EVRNotificationStyle_Application = 100,

    /** Used for notifications about contacts that are unknown or not available. In Steam this is used for friend invitations and offline friends. */
    EVRNotificationStyle_Contact_Disabled = 200,

    /** Used for notifications about contacts that are available but inactive. In Steam this is used for friends that are online but not playing a game. */
    EVRNotificationStyle_Contact_Enabled = 201,

    /** Used for notifications about contacts that are available and active. In Steam this is used for friends that are online and currently running a game. */
    EVRNotificationStyle_Contact_Active = 202,
};

static const uint32_t k_unNotificationTextMaxSize = 256;

typedef uint32_t VRNotificationId;



#pragma pack( pop )

/** Allows notification sources to interact with the VR system
    This current interface is not yet implemented. Do not use yet. */
struct VR_IVRNotifications_FnTable
{
    EVRNotificationError (__stdcall *CreateNotification)( VROverlayHandle_t ulOverlayHandle, uint64_t ulUserValue, EVRNotificationType type, const char *pchText, EVRNotificationStyle style, const NotificationBitmap_t *pImage, /* out */ VRNotificationId *pNotificationId );
    EVRNotificationError (__stdcall *RemoveNotification)( VRNotificationId notificationId );
};

class IVRNotifications
{
    VR_IVRNotifications_FnTable _table;
public:
    /** Create a notification and enqueue it to be shown to the user.
    * An overlay handle is required to create a notification, as otherwise it would be impossible for a user to act on it.
    * To create a two-line notification, use a line break ('\n') to split the text into two lines.
    * The pImage argument may be NULL, in which case the specified overlay's icon will be used instead. */
    EVRNotificationError CreateNotification( VROverlayHandle_t ulOverlayHandle, uint64_t ulUserValue, EVRNotificationType type, const char *pchText, EVRNotificationStyle style, const NotificationBitmap_t *pImage, /* out */ VRNotificationId *pNotificationId ) { return _table.CreateNotification(ulOverlayHandle, ulUserValue, type, pchText, style, pImage, pNotificationId); }

    /** Destroy a notification, hiding it first if it currently shown to the user. */
    EVRNotificationError RemoveNotification( VRNotificationId notificationId ) { return _table.RemoveNotification(notificationId); }

};

static const char * const IVRNotifications_Version = "FnTable:IVRNotifications_002";

} // namespace vr



// ivroverlay.h
namespace vr
{

    /** The maximum length of an overlay key in bytes, counting the terminating null character. */
    static const uint32_t k_unVROverlayMaxKeyLength = 128;

    /** The maximum length of an overlay name in bytes, counting the terminating null character. */
    static const uint32_t k_unVROverlayMaxNameLength = 128;

    /** The maximum number of overlays that can exist in the system at one time. */
    static const uint32_t k_unMaxOverlayCount = 32;

    /** Types of input supported by VR Overlays */
    enum VROverlayInputMethod
    {
        VROverlayInputMethod_None       = 0, // No input events will be generated automatically for this overlay
        VROverlayInputMethod_Mouse      = 1, // Tracked controllers will get mouse events automatically
    };

    /** Allows the caller to figure out which overlay transform getter to call. */
    enum VROverlayTransformType
    {
        VROverlayTransform_Absolute                 = 0,
        VROverlayTransform_TrackedDeviceRelative    = 1,
        VROverlayTransform_SystemOverlay            = 2,
        VROverlayTransform_TrackedComponent         = 3,
    };

    /** Overlay control settings */
    enum VROverlayFlags
    {
        VROverlayFlags_None         = 0,

        // The following only take effect when rendered using the high quality render path (see SetHighQualityOverlay).
        VROverlayFlags_Curved       = 1,
        VROverlayFlags_RGSS4X       = 2,

        // Set this flag on a dashboard overlay to prevent a tab from showing up for that overlay
        VROverlayFlags_NoDashboardTab = 3,

        // Set this flag on a dashboard that is able to deal with gamepad focus events
        VROverlayFlags_AcceptsGamepadEvents = 4,

        // Indicates that the overlay should dim/brighten to show gamepad focus
        VROverlayFlags_ShowGamepadFocus = 5,

        // When in VROverlayInputMethod_Mouse you can optionally enable sending VRScroll_t
        VROverlayFlags_SendVRScrollEvents = 6,
        VROverlayFlags_SendVRTouchpadEvents = 7,

        // If set this will render a vertical scroll wheel on the primary controller,
        //  only needed if not using VROverlayFlags_SendVRScrollEvents but you still want to represent a scroll wheel
        VROverlayFlags_ShowTouchPadScrollWheel = 8,

        // If this is set ownership and render access to the overlay are transferred
        // to the new scene process on a call to IVRApplications::LaunchInternalProcess
        VROverlayFlags_TransferOwnershipToInternalProcess = 9,

        // If set, renders 50% of the texture in each eye, side by side
        VROverlayFlags_SideBySide_Parallel = 10, // Texture is left/right
        VROverlayFlags_SideBySide_Crossed = 11, // Texture is crossed and right/left

        VROverlayFlags_Panorama = 12, // Texture is a panorama
        VROverlayFlags_StereoPanorama = 13, // Texture is a stereo panorama
    };

    struct VROverlayIntersectionParams_t
    {
        HmdVector3_t vSource;
        HmdVector3_t vDirection;
        ETrackingUniverseOrigin eOrigin;
    };

    struct VROverlayIntersectionResults_t
    {
        HmdVector3_t vPoint;
        HmdVector3_t vNormal;
        HmdVector2_t vUVs;
        float fDistance;
    };

    // Input modes for the Big Picture gamepad text entry
    enum EGamepadTextInputMode
    {
        k_EGamepadTextInputModeNormal = 0,
        k_EGamepadTextInputModePassword = 1,
        k_EGamepadTextInputModeSubmit = 2,
    };

    // Controls number of allowed lines for the Big Picture gamepad text entry
    enum EGamepadTextInputLineMode
    {
        k_EGamepadTextInputLineModeSingleLine = 0,
        k_EGamepadTextInputLineModeMultipleLines = 1
    };

    /** Directions for changing focus between overlays with the gamepad */
    enum EOverlayDirection
    {
        OverlayDirection_Up = 0,
        OverlayDirection_Down = 1,
        OverlayDirection_Left = 2,
        OverlayDirection_Right = 3,

        OverlayDirection_Count = 4,
    };

    struct VR_IVROverlay_FnTable
    {
        EVROverlayError (__stdcall *FindOverlay)( const char *pchOverlayKey, VROverlayHandle_t * pOverlayHandle );
        EVROverlayError (__stdcall *CreateOverlay)( const char *pchOverlayKey, const char *pchOverlayFriendlyName, VROverlayHandle_t * pOverlayHandle );
        EVROverlayError (__stdcall *DestroyOverlay)( VROverlayHandle_t ulOverlayHandle );
        EVROverlayError (__stdcall *SetHighQualityOverlay)( VROverlayHandle_t ulOverlayHandle );
        vr::VROverlayHandle_t (__stdcall *GetHighQualityOverlay)();
        uint32_t (__stdcall *GetOverlayKey)( VROverlayHandle_t ulOverlayHandle,  char *pchValue, uint32_t unBufferSize, EVROverlayError *pError);
        uint32_t (__stdcall *GetOverlayName)( VROverlayHandle_t ulOverlayHandle,  char *pchValue, uint32_t unBufferSize, EVROverlayError *pError);
        EVROverlayError (__stdcall *GetOverlayImageData)( VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unBufferSize, uint32_t *punWidth, uint32_t *punHeight );
        const char *(__stdcall *GetOverlayErrorNameFromEnum)( EVROverlayError error );
        EVROverlayError (__stdcall *SetOverlayRenderingPid)( VROverlayHandle_t ulOverlayHandle, uint32_t unPID );
        uint32_t (__stdcall *GetOverlayRenderingPid)( VROverlayHandle_t ulOverlayHandle );
        EVROverlayError (__stdcall *SetOverlayFlag)( VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled );
        EVROverlayError (__stdcall *GetOverlayFlag)( VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool *pbEnabled );
        EVROverlayError (__stdcall *SetOverlayColor)( VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue );
        EVROverlayError (__stdcall *GetOverlayColor)( VROverlayHandle_t ulOverlayHandle, float *pfRed, float *pfGreen, float *pfBlue );
        EVROverlayError (__stdcall *SetOverlayAlpha)( VROverlayHandle_t ulOverlayHandle, float fAlpha );
        EVROverlayError (__stdcall *GetOverlayAlpha)( VROverlayHandle_t ulOverlayHandle, float *pfAlpha );
        EVROverlayError (__stdcall *SetOverlayWidthInMeters)( VROverlayHandle_t ulOverlayHandle, float fWidthInMeters );
        EVROverlayError (__stdcall *GetOverlayWidthInMeters)( VROverlayHandle_t ulOverlayHandle, float *pfWidthInMeters );
        EVROverlayError (__stdcall *SetOverlayAutoCurveDistanceRangeInMeters)( VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters );
        EVROverlayError (__stdcall *GetOverlayAutoCurveDistanceRangeInMeters)( VROverlayHandle_t ulOverlayHandle, float *pfMinDistanceInMeters, float *pfMaxDistanceInMeters );
        EVROverlayError (__stdcall *SetOverlayTextureColorSpace)( VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace );
        EVROverlayError (__stdcall *GetOverlayTextureColorSpace)( VROverlayHandle_t ulOverlayHandle, EColorSpace *peTextureColorSpace );
        EVROverlayError (__stdcall *SetOverlayTextureBounds)( VROverlayHandle_t ulOverlayHandle, const VRTextureBounds_t *pOverlayTextureBounds );
        EVROverlayError (__stdcall *GetOverlayTextureBounds)( VROverlayHandle_t ulOverlayHandle, VRTextureBounds_t *pOverlayTextureBounds );
        EVROverlayError (__stdcall *GetOverlayTransformType)( VROverlayHandle_t ulOverlayHandle, VROverlayTransformType *peTransformType );
        EVROverlayError (__stdcall *SetOverlayTransformAbsolute)( VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToOverlayTransform );
        EVROverlayError (__stdcall *GetOverlayTransformAbsolute)( VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin *peTrackingOrigin, HmdMatrix34_t *pmatTrackingOriginToOverlayTransform );
        EVROverlayError (__stdcall *SetOverlayTransformTrackedDeviceRelative)( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unTrackedDevice, const HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform );
        EVROverlayError (__stdcall *GetOverlayTransformTrackedDeviceRelative)( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punTrackedDevice, HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform );
        EVROverlayError (__stdcall *SetOverlayTransformTrackedDeviceComponent)( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unDeviceIndex, const char *pchComponentName );
        EVROverlayError (__stdcall *GetOverlayTransformTrackedDeviceComponent)( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punDeviceIndex, char *pchComponentName, uint32_t unComponentNameSize );
        EVROverlayError (__stdcall *ShowOverlay)( VROverlayHandle_t ulOverlayHandle );
        EVROverlayError (__stdcall *HideOverlay)( VROverlayHandle_t ulOverlayHandle );
        bool (__stdcall *IsOverlayVisible)( VROverlayHandle_t ulOverlayHandle );
        EVROverlayError (__stdcall *GetTransformForOverlayCoordinates)( VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, HmdVector2_t coordinatesInOverlay, HmdMatrix34_t *pmatTransform );
        bool (__stdcall *PollNextOverlayEvent)( VROverlayHandle_t ulOverlayHandle, VREvent_t *pEvent, uint32_t uncbVREvent );
        EVROverlayError (__stdcall *GetOverlayInputMethod)( VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod *peInputMethod );
        EVROverlayError (__stdcall *SetOverlayInputMethod)( VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod eInputMethod );
        EVROverlayError (__stdcall *GetOverlayMouseScale)( VROverlayHandle_t ulOverlayHandle, HmdVector2_t *pvecMouseScale );
        EVROverlayError (__stdcall *SetOverlayMouseScale)( VROverlayHandle_t ulOverlayHandle, const HmdVector2_t *pvecMouseScale );
        bool (__stdcall *ComputeOverlayIntersection)( VROverlayHandle_t ulOverlayHandle, const VROverlayIntersectionParams_t *pParams, VROverlayIntersectionResults_t *pResults );
        bool (__stdcall *HandleControllerOverlayInteractionAsMouse)( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unControllerDeviceIndex );
        bool (__stdcall *IsHoverTargetOverlay)( VROverlayHandle_t ulOverlayHandle );
        vr::VROverlayHandle_t (__stdcall *GetGamepadFocusOverlay)();
        EVROverlayError (__stdcall *SetGamepadFocusOverlay)( VROverlayHandle_t ulNewFocusOverlay );
        EVROverlayError (__stdcall *SetOverlayNeighbor)( EOverlayDirection eDirection, VROverlayHandle_t ulFrom, VROverlayHandle_t ulTo );
        EVROverlayError (__stdcall *MoveGamepadFocusToNeighbor)( EOverlayDirection eDirection, VROverlayHandle_t ulFrom );
        EVROverlayError (__stdcall *SetOverlayTexture)( VROverlayHandle_t ulOverlayHandle, const Texture_t *pTexture );
        EVROverlayError (__stdcall *ClearOverlayTexture)( VROverlayHandle_t ulOverlayHandle );
        EVROverlayError (__stdcall *SetOverlayRaw)( VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth );
        EVROverlayError (__stdcall *SetOverlayFromFile)( VROverlayHandle_t ulOverlayHandle, const char *pchFilePath );
        EVROverlayError (__stdcall *GetOverlayTexture)( VROverlayHandle_t ulOverlayHandle, void **pNativeTextureHandle, void *pNativeTextureRef, uint32_t *pWidth, uint32_t *pHeight, uint32_t *pNativeFormat, EGraphicsAPIConvention *pAPI, EColorSpace *pColorSpace );
        EVROverlayError (__stdcall *ReleaseNativeOverlayHandle)( VROverlayHandle_t ulOverlayHandle, void *pNativeTextureHandle );
        EVROverlayError (__stdcall *GetOverlayTextureSize)( VROverlayHandle_t ulOverlayHandle, uint32_t *pWidth, uint32_t *pHeight );
        EVROverlayError (__stdcall *CreateDashboardOverlay)( const char *pchOverlayKey, const char *pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t *pThumbnailHandle );
        bool (__stdcall *IsDashboardVisible)();
        bool (__stdcall *IsActiveDashboardOverlay)( VROverlayHandle_t ulOverlayHandle );
        EVROverlayError (__stdcall *SetDashboardOverlaySceneProcess)( VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId );
        EVROverlayError (__stdcall *GetDashboardOverlaySceneProcess)( VROverlayHandle_t ulOverlayHandle, uint32_t *punProcessId );
        void (__stdcall *ShowDashboard)( const char *pchOverlayToShow );
        vr::TrackedDeviceIndex_t (__stdcall *GetPrimaryDashboardDevice)();
        EVROverlayError (__stdcall *ShowKeyboard)( EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode, uint64_t uUserValue );
        EVROverlayError (__stdcall *ShowKeyboardForOverlay)( VROverlayHandle_t ulOverlayHandle, EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode, uint64_t uUserValue );
        uint32_t (__stdcall *GetKeyboardText)(  char *pchText, uint32_t cchText );
        void (__stdcall *HideKeyboard)();
        void (__stdcall *SetKeyboardTransformAbsolute)( ETrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToKeyboardTransform );
        void (__stdcall *SetKeyboardPositionForOverlay)( VROverlayHandle_t ulOverlayHandle, HmdRect2_t avoidRect );
    };

    class IVROverlay
    {
        VR_IVROverlay_FnTable _table;
    public:

        // ---------------------------------------------
        // Overlay management methods
        // ---------------------------------------------

        /** Finds an existing overlay with the specified key. */
        EVROverlayError FindOverlay( const char *pchOverlayKey, VROverlayHandle_t * pOverlayHandle ) { return _table.FindOverlay(pchOverlayKey, pOverlayHandle); }

        /** Creates a new named overlay. All overlays start hidden and with default settings. */
        EVROverlayError CreateOverlay( const char *pchOverlayKey, const char *pchOverlayFriendlyName, VROverlayHandle_t * pOverlayHandle ) { return _table.CreateOverlay(pchOverlayKey, pchOverlayFriendlyName, pOverlayHandle); }

        /** Destroys the specified overlay. When an application calls VR_Shutdown all overlays created by that app are
        * automatically destroyed. */
        EVROverlayError DestroyOverlay( VROverlayHandle_t ulOverlayHandle ) { return _table.DestroyOverlay(ulOverlayHandle); }

        /** Specify which overlay to use the high quality render path.  This overlay will be composited in during the distortion pass which
        * results in it drawing on top of everything else, but also at a higher quality as it samples the source texture directly rather than
        * rasterizing into each eye's render texture first.  Because if this, only one of these is supported at any given time.  It is most useful
        * for overlays that are expected to take up most of the user's view (e.g. streaming video).
        * This mode does not support mouse input to your overlay. */
        EVROverlayError SetHighQualityOverlay( VROverlayHandle_t ulOverlayHandle ) { return _table.SetHighQualityOverlay(ulOverlayHandle); }

        /** Returns the overlay handle of the current overlay being rendered using the single high quality overlay render path.
        * Otherwise it will return k_ulOverlayHandleInvalid. */
        vr::VROverlayHandle_t GetHighQualityOverlay() { return _table.GetHighQualityOverlay(); }

        /** Fills the provided buffer with the string key of the overlay. Returns the size of buffer required to store the key, including
        * the terminating null character. k_unVROverlayMaxKeyLength will be enough bytes to fit the string. */
        uint32_t GetOverlayKey( VROverlayHandle_t ulOverlayHandle, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, EVROverlayError *pError = 0L ) { return _table.GetOverlayKey(ulOverlayHandle, pchValue, unBufferSize, pError); }

        /** Fills the provided buffer with the friendly name of the overlay. Returns the size of buffer required to store the key, including
        * the terminating null character. k_unVROverlayMaxNameLength will be enough bytes to fit the string. */
        uint32_t GetOverlayName( VROverlayHandle_t ulOverlayHandle, VR_OUT_STRING() char *pchValue, uint32_t unBufferSize, EVROverlayError *pError = 0L ) { return _table.GetOverlayName(ulOverlayHandle, pchValue, unBufferSize, pError); }

        /** Gets the raw image data from an overlay. Overlay image data is always returned as RGBA data, 4 bytes per pixel. If the buffer is not large enough, width and height
        * will be set and VROverlayError_ArrayTooSmall is returned. */
        EVROverlayError GetOverlayImageData( VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unBufferSize, uint32_t *punWidth, uint32_t *punHeight ) { return _table.GetOverlayImageData(ulOverlayHandle, pvBuffer, unBufferSize, punWidth, punHeight); }

        /** returns a string that corresponds with the specified overlay error. The string will be the name
        * of the error enum value for all valid error codes */
        const char *GetOverlayErrorNameFromEnum( EVROverlayError error ) { return _table.GetOverlayErrorNameFromEnum(error); }


        // ---------------------------------------------
        // Overlay rendering methods
        // ---------------------------------------------

        /** Sets the pid that is allowed to render to this overlay (the creator pid is always allow to render),
        *   by default this is the pid of the process that made the overlay */
        EVROverlayError SetOverlayRenderingPid( VROverlayHandle_t ulOverlayHandle, uint32_t unPID ) { return _table.SetOverlayRenderingPid(ulOverlayHandle, unPID); }

        /** Gets the pid that is allowed to render to this overlay */
        uint32_t GetOverlayRenderingPid( VROverlayHandle_t ulOverlayHandle ) { return _table.GetOverlayRenderingPid(ulOverlayHandle); }

        /** Specify flag setting for a given overlay */
        EVROverlayError SetOverlayFlag( VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool bEnabled ) { return _table.SetOverlayFlag(ulOverlayHandle, eOverlayFlag, bEnabled); }

        /** Sets flag setting for a given overlay */
        EVROverlayError GetOverlayFlag( VROverlayHandle_t ulOverlayHandle, VROverlayFlags eOverlayFlag, bool *pbEnabled ) { return _table.GetOverlayFlag(ulOverlayHandle, eOverlayFlag, pbEnabled); }

        /** Sets the color tint of the overlay quad. Use 0.0 to 1.0 per channel. */
        EVROverlayError SetOverlayColor( VROverlayHandle_t ulOverlayHandle, float fRed, float fGreen, float fBlue ) { return _table.SetOverlayColor(ulOverlayHandle, fRed, fGreen, fBlue); }

        /** Gets the color tint of the overlay quad. */
        EVROverlayError GetOverlayColor( VROverlayHandle_t ulOverlayHandle, float *pfRed, float *pfGreen, float *pfBlue ) { return _table.GetOverlayColor(ulOverlayHandle, pfRed, pfGreen, pfBlue); }

        /** Sets the alpha of the overlay quad. Use 1.0 for 100 percent opacity to 0.0 for 0 percent opacity. */
        EVROverlayError SetOverlayAlpha( VROverlayHandle_t ulOverlayHandle, float fAlpha ) { return _table.SetOverlayAlpha(ulOverlayHandle, fAlpha); }

        /** Gets the alpha of the overlay quad. By default overlays are rendering at 100 percent alpha (1.0). */
        EVROverlayError GetOverlayAlpha( VROverlayHandle_t ulOverlayHandle, float *pfAlpha ) { return _table.GetOverlayAlpha(ulOverlayHandle, pfAlpha); }

        /** Sets the width of the overlay quad in meters. By default overlays are rendered on a quad that is 1 meter across */
        EVROverlayError SetOverlayWidthInMeters( VROverlayHandle_t ulOverlayHandle, float fWidthInMeters ) { return _table.SetOverlayWidthInMeters(ulOverlayHandle, fWidthInMeters); }

        /** Returns the width of the overlay quad in meters. By default overlays are rendered on a quad that is 1 meter across */
        EVROverlayError GetOverlayWidthInMeters( VROverlayHandle_t ulOverlayHandle, float *pfWidthInMeters ) { return _table.GetOverlayWidthInMeters(ulOverlayHandle, pfWidthInMeters); }

        /** For high-quality curved overlays only, sets the distance range in meters from the overlay used to automatically curve
        * the surface around the viewer.  Min is distance is when the surface will be most curved.  Max is when least curved. */
        EVROverlayError SetOverlayAutoCurveDistanceRangeInMeters( VROverlayHandle_t ulOverlayHandle, float fMinDistanceInMeters, float fMaxDistanceInMeters ) { return _table.SetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, fMinDistanceInMeters, fMaxDistanceInMeters); }

        /** For high-quality curved overlays only, gets the distance range in meters from the overlay used to automatically curve
        * the surface around the viewer.  Min is distance is when the surface will be most curved.  Max is when least curved. */
        EVROverlayError GetOverlayAutoCurveDistanceRangeInMeters( VROverlayHandle_t ulOverlayHandle, float *pfMinDistanceInMeters, float *pfMaxDistanceInMeters ) { return _table.GetOverlayAutoCurveDistanceRangeInMeters(ulOverlayHandle, pfMinDistanceInMeters, pfMaxDistanceInMeters); }

        /** Sets the colorspace the overlay texture's data is in.  Defaults to 'auto'.
        * If the texture needs to be resolved, you should call SetOverlayTexture with the appropriate colorspace instead. */
        EVROverlayError SetOverlayTextureColorSpace( VROverlayHandle_t ulOverlayHandle, EColorSpace eTextureColorSpace ) { return _table.SetOverlayTextureColorSpace(ulOverlayHandle, eTextureColorSpace); }

        /** Gets the overlay's current colorspace setting. */
        EVROverlayError GetOverlayTextureColorSpace( VROverlayHandle_t ulOverlayHandle, EColorSpace *peTextureColorSpace ) { return _table.GetOverlayTextureColorSpace(ulOverlayHandle, peTextureColorSpace); }

        /** Sets the part of the texture to use for the overlay. UV Min is the upper left corner and UV Max is the lower right corner. */
        EVROverlayError SetOverlayTextureBounds( VROverlayHandle_t ulOverlayHandle, const VRTextureBounds_t *pOverlayTextureBounds ) { return _table.SetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }

        /** Gets the part of the texture to use for the overlay. UV Min is the upper left corner and UV Max is the lower right corner. */
        EVROverlayError GetOverlayTextureBounds( VROverlayHandle_t ulOverlayHandle, VRTextureBounds_t *pOverlayTextureBounds ) { return _table.GetOverlayTextureBounds(ulOverlayHandle, pOverlayTextureBounds); }

        /** Returns the transform type of this overlay. */
        EVROverlayError GetOverlayTransformType( VROverlayHandle_t ulOverlayHandle, VROverlayTransformType *peTransformType ) { return _table.GetOverlayTransformType(ulOverlayHandle, peTransformType); }

        /** Sets the transform to absolute tracking origin. */
        EVROverlayError SetOverlayTransformAbsolute( VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToOverlayTransform ) { return _table.SetOverlayTransformAbsolute(ulOverlayHandle, eTrackingOrigin, pmatTrackingOriginToOverlayTransform); }

        /** Gets the transform if it is absolute. Returns an error if the transform is some other type. */
        EVROverlayError GetOverlayTransformAbsolute( VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin *peTrackingOrigin, HmdMatrix34_t *pmatTrackingOriginToOverlayTransform ) { return _table.GetOverlayTransformAbsolute(ulOverlayHandle, peTrackingOrigin, pmatTrackingOriginToOverlayTransform); }

        /** Sets the transform to relative to the transform of the specified tracked device. */
        EVROverlayError SetOverlayTransformTrackedDeviceRelative( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unTrackedDevice, const HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform ) { return _table.SetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, unTrackedDevice, pmatTrackedDeviceToOverlayTransform); }

        /** Gets the transform if it is relative to a tracked device. Returns an error if the transform is some other type. */
        EVROverlayError GetOverlayTransformTrackedDeviceRelative( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punTrackedDevice, HmdMatrix34_t *pmatTrackedDeviceToOverlayTransform ) { return _table.GetOverlayTransformTrackedDeviceRelative(ulOverlayHandle, punTrackedDevice, pmatTrackedDeviceToOverlayTransform); }

        /** Sets the transform to draw the overlay on a rendermodel component mesh instead of a quad. This will only draw when the system is
        * drawing the device. Overlays with this transform type cannot receive mouse events. */
        EVROverlayError SetOverlayTransformTrackedDeviceComponent( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unDeviceIndex, const char *pchComponentName ) { return _table.SetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, unDeviceIndex, pchComponentName); }

        /** Gets the transform information when the overlay is rendering on a component. */
        EVROverlayError GetOverlayTransformTrackedDeviceComponent( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t *punDeviceIndex, char *pchComponentName, uint32_t unComponentNameSize ) { return _table.GetOverlayTransformTrackedDeviceComponent(ulOverlayHandle, punDeviceIndex, pchComponentName, unComponentNameSize); }

        /** Shows the VR overlay.  For dashboard overlays, only the Dashboard Manager is allowed to call this. */
        EVROverlayError ShowOverlay( VROverlayHandle_t ulOverlayHandle ) { return _table.ShowOverlay(ulOverlayHandle); }

        /** Hides the VR overlay.  For dashboard overlays, only the Dashboard Manager is allowed to call this. */
        EVROverlayError HideOverlay( VROverlayHandle_t ulOverlayHandle ) { return _table.HideOverlay(ulOverlayHandle); }

        /** Returns true if the overlay is visible. */
        bool IsOverlayVisible( VROverlayHandle_t ulOverlayHandle ) { return _table.IsOverlayVisible(ulOverlayHandle); }

        /** Get the transform in 3d space associated with a specific 2d point in the overlay's coordinate space (where 0,0 is the lower left). -Z points out of the overlay */
        EVROverlayError GetTransformForOverlayCoordinates( VROverlayHandle_t ulOverlayHandle, ETrackingUniverseOrigin eTrackingOrigin, HmdVector2_t coordinatesInOverlay, HmdMatrix34_t *pmatTransform ) { return _table.GetTransformForOverlayCoordinates(ulOverlayHandle, eTrackingOrigin, coordinatesInOverlay, pmatTransform); }

        // ---------------------------------------------
        // Overlay input methods
        // ---------------------------------------------

        /** Returns true and fills the event with the next event on the overlay's event queue, if there is one.
        * If there are no events this method returns false. uncbVREvent should be the size in bytes of the VREvent_t struct */
        bool PollNextOverlayEvent( VROverlayHandle_t ulOverlayHandle, VREvent_t *pEvent, uint32_t uncbVREvent ) { return _table.PollNextOverlayEvent(ulOverlayHandle, pEvent, uncbVREvent); }

        /** Returns the current input settings for the specified overlay. */
        EVROverlayError GetOverlayInputMethod( VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod *peInputMethod ) { return _table.GetOverlayInputMethod(ulOverlayHandle, peInputMethod); }

        /** Sets the input settings for the specified overlay. */
        EVROverlayError SetOverlayInputMethod( VROverlayHandle_t ulOverlayHandle, VROverlayInputMethod eInputMethod ) { return _table.SetOverlayInputMethod(ulOverlayHandle, eInputMethod); }

        /** Gets the mouse scaling factor that is used for mouse events. The actual texture may be a different size, but this is
        * typically the size of the underlying UI in pixels. */
        EVROverlayError GetOverlayMouseScale( VROverlayHandle_t ulOverlayHandle, HmdVector2_t *pvecMouseScale ) { return _table.GetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }

        /** Sets the mouse scaling factor that is used for mouse events. The actual texture may be a different size, but this is
        * typically the size of the underlying UI in pixels (not in world space). */
        EVROverlayError SetOverlayMouseScale( VROverlayHandle_t ulOverlayHandle, const HmdVector2_t *pvecMouseScale ) { return _table.SetOverlayMouseScale(ulOverlayHandle, pvecMouseScale); }

        /** Computes the overlay-space pixel coordinates of where the ray intersects the overlay with the
        * specified settings. Returns false if there is no intersection. */
        bool ComputeOverlayIntersection( VROverlayHandle_t ulOverlayHandle, const VROverlayIntersectionParams_t *pParams, VROverlayIntersectionResults_t *pResults ) { return _table.ComputeOverlayIntersection(ulOverlayHandle, pParams, pResults); }

        /** Processes mouse input from the specified controller as though it were a mouse pointed at a compositor overlay with the
        * specified settings. The controller is treated like a laser pointer on the -z axis. The point where the laser pointer would
        * intersect with the overlay is the mouse position, the trigger is left mouse, and the track pad is right mouse.
        *
        * Return true if the controller is pointed at the overlay and an event was generated. */
        bool HandleControllerOverlayInteractionAsMouse( VROverlayHandle_t ulOverlayHandle, TrackedDeviceIndex_t unControllerDeviceIndex ) { return _table.HandleControllerOverlayInteractionAsMouse(ulOverlayHandle, unControllerDeviceIndex); }

        /** Returns true if the specified overlay is the hover target. An overlay is the hover target when it is the last overlay "moused over"
        * by the virtual mouse pointer */
        bool IsHoverTargetOverlay( VROverlayHandle_t ulOverlayHandle ) { return _table.IsHoverTargetOverlay(ulOverlayHandle); }

        /** Returns the current Gamepad focus overlay */
        vr::VROverlayHandle_t GetGamepadFocusOverlay() { return _table.GetGamepadFocusOverlay(); }

        /** Sets the current Gamepad focus overlay */
        EVROverlayError SetGamepadFocusOverlay( VROverlayHandle_t ulNewFocusOverlay ) { return _table.SetGamepadFocusOverlay(ulNewFocusOverlay); }

        /** Sets an overlay's neighbor. This will also set the neighbor of the "to" overlay
        * to point back to the "from" overlay. If an overlay's neighbor is set to invalid both
        * ends will be cleared */
        EVROverlayError SetOverlayNeighbor( EOverlayDirection eDirection, VROverlayHandle_t ulFrom, VROverlayHandle_t ulTo ) { return _table.SetOverlayNeighbor(eDirection, ulFrom, ulTo); }

        /** Changes the Gamepad focus from one overlay to one of its neighbors. Returns VROverlayError_NoNeighbor if there is no
        * neighbor in that direction */
        EVROverlayError MoveGamepadFocusToNeighbor( EOverlayDirection eDirection, VROverlayHandle_t ulFrom ) { return _table.MoveGamepadFocusToNeighbor(eDirection, ulFrom); }

        // ---------------------------------------------
        // Overlay texture methods
        // ---------------------------------------------

        /** Texture to draw for the overlay. This function can only be called by the overlay's creator or renderer process (see SetOverlayRenderingPid) .
        *
        * OpenGL dirty state:
        *   glBindTexture
        */
        EVROverlayError SetOverlayTexture( VROverlayHandle_t ulOverlayHandle, const Texture_t *pTexture ) { return _table.SetOverlayTexture(ulOverlayHandle, pTexture); }

        /** Use this to tell the overlay system to release the texture set for this overlay. */
        EVROverlayError ClearOverlayTexture( VROverlayHandle_t ulOverlayHandle ) { return _table.ClearOverlayTexture(ulOverlayHandle); }

        /** Separate interface for providing the data as a stream of bytes, but there is an upper bound on data
        * that can be sent. This function can only be called by the overlay's renderer process. */
        EVROverlayError SetOverlayRaw( VROverlayHandle_t ulOverlayHandle, void *pvBuffer, uint32_t unWidth, uint32_t unHeight, uint32_t unDepth ) { return _table.SetOverlayRaw(ulOverlayHandle, pvBuffer, unWidth, unHeight, unDepth); }

        /** Separate interface for providing the image through a filename: can be png or jpg, and should not be bigger than 1920x1080.
        * This function can only be called by the overlay's renderer process */
        EVROverlayError SetOverlayFromFile( VROverlayHandle_t ulOverlayHandle, const char *pchFilePath ) { return _table.SetOverlayFromFile(ulOverlayHandle, pchFilePath); }

        /** Get the native texture handle/device for an overlay you have created.
        * On windows this handle will be a ID3D11ShaderResourceView with a ID3D11Texture2D bound.
        *
        * The texture will always be sized to match the backing texture you supplied in SetOverlayTexture above.
        *
        * You MUST call ReleaseNativeOverlayHandle() with pNativeTextureHandle once you are done with this texture.
        *
        * pNativeTextureHandle is an OUTPUT, it will be a pointer to a ID3D11ShaderResourceView *.
        * pNativeTextureRef is an INPUT and should be a ID3D11Resource *. The device used by pNativeTextureRef will be used to bind pNativeTextureHandle.
        */
        EVROverlayError GetOverlayTexture( VROverlayHandle_t ulOverlayHandle, void **pNativeTextureHandle, void *pNativeTextureRef, uint32_t *pWidth, uint32_t *pHeight, uint32_t *pNativeFormat, EGraphicsAPIConvention *pAPI, EColorSpace *pColorSpace ) { return _table.GetOverlayTexture(ulOverlayHandle, pNativeTextureHandle, pNativeTextureRef, pWidth, pHeight, pNativeFormat, pAPI, pColorSpace); }

        /** Release the pNativeTextureHandle provided from the GetOverlayTexture call, this allows the system to free the underlying GPU resources for this object,
        * so only do it once you stop rendering this texture.
        */
        EVROverlayError ReleaseNativeOverlayHandle( VROverlayHandle_t ulOverlayHandle, void *pNativeTextureHandle ) { return _table.ReleaseNativeOverlayHandle(ulOverlayHandle, pNativeTextureHandle); }

        /** Get the size of the overlay texture */
        EVROverlayError GetOverlayTextureSize( VROverlayHandle_t ulOverlayHandle, uint32_t *pWidth, uint32_t *pHeight ) { return _table.GetOverlayTextureSize(ulOverlayHandle, pWidth, pHeight); }

        // ----------------------------------------------
        // Dashboard Overlay Methods
        // ----------------------------------------------

        /** Creates a dashboard overlay and returns its handle */
        EVROverlayError CreateDashboardOverlay( const char *pchOverlayKey, const char *pchOverlayFriendlyName, VROverlayHandle_t * pMainHandle, VROverlayHandle_t *pThumbnailHandle ) { return _table.CreateDashboardOverlay(pchOverlayKey, pchOverlayFriendlyName, pMainHandle, pThumbnailHandle); }

        /** Returns true if the dashboard is visible */
        bool IsDashboardVisible() { return _table.IsDashboardVisible(); }

        /** returns true if the dashboard is visible and the specified overlay is the active system Overlay */
        bool IsActiveDashboardOverlay( VROverlayHandle_t ulOverlayHandle ) { return _table.IsActiveDashboardOverlay(ulOverlayHandle); }

        /** Sets the dashboard overlay to only appear when the specified process ID has scene focus */
        EVROverlayError SetDashboardOverlaySceneProcess( VROverlayHandle_t ulOverlayHandle, uint32_t unProcessId ) { return _table.SetDashboardOverlaySceneProcess(ulOverlayHandle, unProcessId); }

        /** Gets the process ID that this dashboard overlay requires to have scene focus */
        EVROverlayError GetDashboardOverlaySceneProcess( VROverlayHandle_t ulOverlayHandle, uint32_t *punProcessId ) { return _table.GetDashboardOverlaySceneProcess(ulOverlayHandle, punProcessId); }

        /** Shows the dashboard. */
        void ShowDashboard( const char *pchOverlayToShow ) { _table.ShowDashboard(pchOverlayToShow); }

        /** Returns the tracked device that has the laser pointer in the dashboard */
        vr::TrackedDeviceIndex_t GetPrimaryDashboardDevice() { return _table.GetPrimaryDashboardDevice(); }

        // ---------------------------------------------
        // Keyboard methods
        // ---------------------------------------------

        /** Show the virtual keyboard to accept input **/
        EVROverlayError ShowKeyboard( EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode, uint64_t uUserValue ) { return _table.ShowKeyboard(eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }

        EVROverlayError ShowKeyboardForOverlay( VROverlayHandle_t ulOverlayHandle, EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char *pchDescription, uint32_t unCharMax, const char *pchExistingText, bool bUseMinimalMode, uint64_t uUserValue ) { return _table.ShowKeyboardForOverlay(ulOverlayHandle, eInputMode, eLineInputMode, pchDescription, unCharMax, pchExistingText, bUseMinimalMode, uUserValue); }

        /** Get the text that was entered into the text input **/
        uint32_t GetKeyboardText( VR_OUT_STRING() char *pchText, uint32_t cchText ) { return _table.GetKeyboardText(pchText, cchText); }

        /** Hide the virtual keyboard **/
        void HideKeyboard() { _table.HideKeyboard(); }

        /** Set the position of the keyboard in world space **/
        void SetKeyboardTransformAbsolute( ETrackingUniverseOrigin eTrackingOrigin, const HmdMatrix34_t *pmatTrackingOriginToKeyboardTransform ) { _table.SetKeyboardTransformAbsolute(eTrackingOrigin, pmatTrackingOriginToKeyboardTransform); }

        /** Set the position of the keyboard in overlay space by telling it to avoid a rectangle in the overlay. Rectangle coords have (0,0) in the bottom left **/
        void SetKeyboardPositionForOverlay( VROverlayHandle_t ulOverlayHandle, HmdRect2_t avoidRect ) { _table.SetKeyboardPositionForOverlay(ulOverlayHandle, avoidRect); }

    };

    static const char * const IVROverlay_Version = "FnTable:IVROverlay_012";

} // namespace vr

// ivrrendermodels.h
namespace vr
{

static const char * const k_pch_Controller_Component_GDC2015 = "gdc2015";   // Canonical coordinate system of the gdc 2015 wired controller, provided for backwards compatibility
static const char * const k_pch_Controller_Component_Base = "base";         // For controllers with an unambiguous 'base'.
static const char * const k_pch_Controller_Component_Tip = "tip";           // For controllers with an unambiguous 'tip' (used for 'laser-pointing')
static const char * const k_pch_Controller_Component_HandGrip = "handgrip"; // Neutral, ambidextrous hand-pose when holding controller. On plane between neutrally posed index finger and thumb
static const char * const k_pch_Controller_Component_Status = "status";     // 1:1 aspect ratio status area, with canonical [0,1] uv mapping

#if defined(__linux__) || defined(__APPLE__)
// The 32-bit version of gcc has the alignment requirement for uint64 and double set to
// 4 meaning that even with #pragma pack(8) these types will only be four-byte aligned.
// The 64-bit version of gcc has the alignment requirement for these types set to
// 8 meaning that unless we use #pragma pack(4) our structures will get bigger.
// The 64-bit structure packing has to match the 32-bit structure packing for each platform.
#pragma pack( push, 4 )
#else
#pragma pack( push, 8 )
#endif

/** Errors that can occur with the VR compositor */
enum EVRRenderModelError
{
    VRRenderModelError_None = 0,
    VRRenderModelError_Loading = 100,
    VRRenderModelError_NotSupported = 200,
    VRRenderModelError_InvalidArg = 300,
    VRRenderModelError_InvalidModel = 301,
    VRRenderModelError_NoShapes = 302,
    VRRenderModelError_MultipleShapes = 303,
    VRRenderModelError_TooManyVertices = 304,
    VRRenderModelError_MultipleTextures = 305,
    VRRenderModelError_BufferTooSmall = 306,
    VRRenderModelError_NotEnoughNormals = 307,
    VRRenderModelError_NotEnoughTexCoords = 308,

    VRRenderModelError_InvalidTexture = 400,
};

typedef uint32_t VRComponentProperties;

enum EVRComponentProperty
{
    VRComponentProperty_IsStatic = (1 << 0),
    VRComponentProperty_IsVisible = (1 << 1),
    VRComponentProperty_IsTouched = (1 << 2),
    VRComponentProperty_IsPressed = (1 << 3),
    VRComponentProperty_IsScrolled = (1 << 4),
};

/** Describes state information about a render-model component, including transforms and other dynamic properties */
struct RenderModel_ComponentState_t
{
    HmdMatrix34_t mTrackingToComponentRenderModel;  // Transform required when drawing the component render model
    HmdMatrix34_t mTrackingToComponentLocal;        // Transform available for attaching to a local component coordinate system (-Z out from surface )
    VRComponentProperties uProperties;
};

/** A single vertex in a render model */
struct RenderModel_Vertex_t
{
    HmdVector3_t vPosition;     // position in meters in device space
    HmdVector3_t vNormal;
    float rfTextureCoord[2];
};

/** A texture map for use on a render model */
struct RenderModel_TextureMap_t
{
    uint16_t unWidth, unHeight; // width and height of the texture map in pixels
    const uint8_t *rubTextureMapData;   // Map texture data. All textures are RGBA with 8 bits per channel per pixel. Data size is width * height * 4ub
};

/**  Session unique texture identifier. Rendermodels which share the same texture will have the same id.
IDs <0 denote the texture is not present */

typedef int32_t TextureID_t;

const TextureID_t INVALID_TEXTURE_ID = -1;

struct RenderModel_t
{
    const RenderModel_Vertex_t *rVertexData;    // Vertex data for the mesh
    uint32_t unVertexCount;                     // Number of vertices in the vertex data
    const uint16_t *rIndexData;                 // Indices into the vertex data for each triangle
    uint32_t unTriangleCount;                   // Number of triangles in the mesh. Index count is 3 * TriangleCount
    TextureID_t diffuseTextureId;               // Session unique texture identifier. Rendermodels which share the same texture will have the same id. <0 == texture not present
};

struct RenderModel_ControllerMode_State_t
{
    bool bScrollWheelVisible; // is this controller currently set to be in a scroll wheel mode
};

#pragma pack( pop )

struct VR_IVRRenderModels_FnTable
{
    EVRRenderModelError (__stdcall *LoadRenderModel_Async)( const char *pchRenderModelName, RenderModel_t **ppRenderModel );
    void (__stdcall *FreeRenderModel)( RenderModel_t *pRenderModel );
    EVRRenderModelError (__stdcall *LoadTexture_Async)( TextureID_t textureId, RenderModel_TextureMap_t **ppTexture );
    void (__stdcall *FreeTexture)( RenderModel_TextureMap_t *pTexture );
    EVRRenderModelError (__stdcall *LoadTextureD3D11_Async)( TextureID_t textureId, void *pD3D11Device, void **ppD3D11Texture2D );
    EVRRenderModelError (__stdcall *LoadIntoTextureD3D11_Async)( TextureID_t textureId, void *pDstTexture );
    void (__stdcall *FreeTextureD3D11)( void *pD3D11Texture2D );
    uint32_t (__stdcall *GetRenderModelName)( uint32_t unRenderModelIndex,  char *pchRenderModelName, uint32_t unRenderModelNameLen );
    uint32_t (__stdcall *GetRenderModelCount)();
    uint32_t (__stdcall *GetComponentCount)( const char *pchRenderModelName );
    uint32_t (__stdcall *GetComponentName)( const char *pchRenderModelName, uint32_t unComponentIndex,  char *pchComponentName, uint32_t unComponentNameLen );
    uint64_t (__stdcall *GetComponentButtonMask)( const char *pchRenderModelName, const char *pchComponentName );
    uint32_t (__stdcall *GetComponentRenderModelName)( const char *pchRenderModelName, const char *pchComponentName,  char *pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen );
    bool (__stdcall *GetComponentState)( const char *pchRenderModelName, const char *pchComponentName, const vr::VRControllerState_t *pControllerState, const RenderModel_ControllerMode_State_t *pState, RenderModel_ComponentState_t *pComponentState );
    bool (__stdcall *RenderModelHasComponent)( const char *pchRenderModelName, const char *pchComponentName );
    uint32_t (__stdcall *GetRenderModelThumbnailURL)( const char *pchRenderModelName,  char *pchThumbnailURL, uint32_t unThumbnailURLLen, vr::EVRRenderModelError *peError );
    uint32_t (__stdcall *GetRenderModelOriginalPath)( const char *pchRenderModelName,  char *pchOriginalPath, uint32_t unOriginalPathLen, vr::EVRRenderModelError *peError );
    const char *(__stdcall *GetRenderModelErrorNameFromEnum)( vr::EVRRenderModelError error );
};

class IVRRenderModels
{
    VR_IVRRenderModels_FnTable _table;
public:

    /** Loads and returns a render model for use in the application. pchRenderModelName should be a render model name
    * from the Prop_RenderModelName_String property or an absolute path name to a render model on disk.
    *
    * The resulting render model is valid until VR_Shutdown() is called or until FreeRenderModel() is called. When the
    * application is finished with the render model it should call FreeRenderModel() to free the memory associated
    * with the model.
    *
    * The method returns VRRenderModelError_Loading while the render model is still being loaded.
    * The method returns VRRenderModelError_None once loaded successfully, otherwise will return an error. */
    EVRRenderModelError LoadRenderModel_Async( const char *pchRenderModelName, RenderModel_t **ppRenderModel ) { return _table.LoadRenderModel_Async(pchRenderModelName, ppRenderModel); }

    /** Frees a previously returned render model
    *   It is safe to call this on a null ptr. */
    void FreeRenderModel( RenderModel_t *pRenderModel ) { _table.FreeRenderModel(pRenderModel); }

    /** Loads and returns a texture for use in the application. */
    EVRRenderModelError LoadTexture_Async( TextureID_t textureId, RenderModel_TextureMap_t **ppTexture ) { return _table.LoadTexture_Async(textureId, ppTexture); }

    /** Frees a previously returned texture
    *   It is safe to call this on a null ptr. */
    void FreeTexture( RenderModel_TextureMap_t *pTexture ) { _table.FreeTexture(pTexture); }

    /** Creates a D3D11 texture and loads data into it. */
    EVRRenderModelError LoadTextureD3D11_Async( TextureID_t textureId, void *pD3D11Device, void **ppD3D11Texture2D ) { return _table.LoadTextureD3D11_Async(textureId, pD3D11Device, ppD3D11Texture2D); }

    /** Helper function to copy the bits into an existing texture. */
    EVRRenderModelError LoadIntoTextureD3D11_Async( TextureID_t textureId, void *pDstTexture ) { return _table.LoadIntoTextureD3D11_Async(textureId, pDstTexture); }

    /** Use this to free textures created with LoadTextureD3D11_Async instead of calling Release on them. */
    void FreeTextureD3D11( void *pD3D11Texture2D ) { _table.FreeTextureD3D11(pD3D11Texture2D); }

    /** Use this to get the names of available render models.  Index does not correlate to a tracked device index, but
    * is only used for iterating over all available render models.  If the index is out of range, this function will return 0.
    * Otherwise, it will return the size of the buffer required for the name. */
    uint32_t GetRenderModelName( uint32_t unRenderModelIndex, VR_OUT_STRING() char *pchRenderModelName, uint32_t unRenderModelNameLen ) { return _table.GetRenderModelName(unRenderModelIndex, pchRenderModelName, unRenderModelNameLen); }

    /** Returns the number of available render models. */
    uint32_t GetRenderModelCount() { return _table.GetRenderModelCount(); }


    /** Returns the number of components of the specified render model.
    *  Components are useful when client application wish to draw, label, or otherwise interact with components of tracked objects.
    *  Examples controller components:
    *   renderable things such as triggers, buttons
    *   non-renderable things which include coordinate systems such as 'tip', 'base', a neutral controller agnostic hand-pose
    *   If all controller components are enumerated and rendered, it will be equivalent to drawing the traditional render model
    *   Returns 0 if components not supported, >0 otherwise */
    uint32_t GetComponentCount( const char *pchRenderModelName ) { return _table.GetComponentCount(pchRenderModelName); }

    /** Use this to get the names of available components.  Index does not correlate to a tracked device index, but
    * is only used for iterating over all available components.  If the index is out of range, this function will return 0.
    * Otherwise, it will return the size of the buffer required for the name. */
    uint32_t GetComponentName( const char *pchRenderModelName, uint32_t unComponentIndex, VR_OUT_STRING( ) char *pchComponentName, uint32_t unComponentNameLen ) { return _table.GetComponentName(pchRenderModelName, unComponentIndex, pchComponentName, unComponentNameLen); }

    /** Get the button mask for all buttons associated with this component
    *   If no buttons (or axes) are associated with this component, return 0
    *   Note: multiple components may be associated with the same button. Ex: two grip buttons on a single controller.
    *   Note: A single component may be associated with multiple buttons. Ex: A trackpad which also provides "D-pad" functionality */
    uint64_t GetComponentButtonMask( const char *pchRenderModelName, const char *pchComponentName ) { return _table.GetComponentButtonMask(pchRenderModelName, pchComponentName); }

    /** Use this to get the render model name for the specified rendermode/component combination, to be passed to LoadRenderModel.
    * If the component name is out of range, this function will return 0.
    * Otherwise, it will return the size of the buffer required for the name. */
    uint32_t GetComponentRenderModelName( const char *pchRenderModelName, const char *pchComponentName, VR_OUT_STRING( ) char *pchComponentRenderModelName, uint32_t unComponentRenderModelNameLen ) { return _table.GetComponentRenderModelName(pchRenderModelName, pchComponentName, pchComponentRenderModelName, unComponentRenderModelNameLen); }

    /** Use this to query information about the component, as a function of the controller state.
    *
    * For dynamic controller components (ex: trigger) values will reflect component motions
    * For static components this will return a consistent value independent of the VRControllerState_t
    *
    * If the pchRenderModelName or pchComponentName is invalid, this will return false (and transforms will be set to identity).
    * Otherwise, return true
    * Note: For dynamic objects, visibility may be dynamic. (I.e., true/false will be returned based on controller state and controller mode state ) */
    bool GetComponentState( const char *pchRenderModelName, const char *pchComponentName, const vr::VRControllerState_t *pControllerState, const RenderModel_ControllerMode_State_t *pState, RenderModel_ComponentState_t *pComponentState ) { return _table.GetComponentState(pchRenderModelName, pchComponentName, pControllerState, pState, pComponentState); }

    /** Returns true if the render model has a component with the specified name */
    bool RenderModelHasComponent( const char *pchRenderModelName, const char *pchComponentName ) { return _table.RenderModelHasComponent(pchRenderModelName, pchComponentName); }

    /** Returns the URL of the thumbnail image for this rendermodel */
    uint32_t GetRenderModelThumbnailURL( const char *pchRenderModelName, VR_OUT_STRING() char *pchThumbnailURL, uint32_t unThumbnailURLLen, vr::EVRRenderModelError *peError ) { return _table.GetRenderModelThumbnailURL(pchRenderModelName, pchThumbnailURL, unThumbnailURLLen, peError); }

    /** Provides a render model path that will load the unskinned model if the model name provided has been replace by the user. If the model
    * hasn't been replaced the path value will still be a valid path to load the model. Pass this to LoadRenderModel_Async, etc. to load the
    * model. */
    uint32_t GetRenderModelOriginalPath( const char *pchRenderModelName, VR_OUT_STRING() char *pchOriginalPath, uint32_t unOriginalPathLen, vr::EVRRenderModelError *peError ) { return _table.GetRenderModelOriginalPath(pchRenderModelName, pchOriginalPath, unOriginalPathLen, peError); }

    /** Returns a string for a render model error */
    const char *GetRenderModelErrorNameFromEnum( vr::EVRRenderModelError error ) { return _table.GetRenderModelErrorNameFromEnum(error); }
};

static const char * const IVRRenderModels_Version = "FnTable:IVRRenderModels_005";

}


// ivrextendeddisplay.h
namespace vr
{

    /** NOTE: Use of this interface is not recommended in production applications. It will not work for displays which use
    * direct-to-display mode. It is also incompatible with the VR compositor and is not available when the compositor is running. */
    struct VR_IVRExtendedDisplay_FnTable
    {
        void (__stdcall *GetWindowBounds)( int32_t *pnX, int32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight );
        void (__stdcall *GetEyeOutputViewport)( EVREye eEye, uint32_t *pnX, uint32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight );
        void (__stdcall *GetDXGIOutputInfo)( int32_t *pnAdapterIndex, int32_t *pnAdapterOutputIndex );
    };

    class IVRExtendedDisplay
    {
        VR_IVRExtendedDisplay_FnTable _table;
    public:

        /** Size and position that the window needs to be on the VR display. */
        void GetWindowBounds( int32_t *pnX, int32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight ) { _table.GetWindowBounds(pnX, pnY, pnWidth, pnHeight); }

        /** Gets the viewport in the frame buffer to draw the output of the distortion into */
        void GetEyeOutputViewport( EVREye eEye, uint32_t *pnX, uint32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight ) { _table.GetEyeOutputViewport(eEye, pnX, pnY, pnWidth, pnHeight); }

        /** [D3D10/11 Only]
        * Returns the adapter index and output index that the user should pass into EnumAdapters and EnumOutputs
        * to create the device and swap chain in DX10 and DX11. If an error occurs both indices will be set to -1.
        */
        void GetDXGIOutputInfo( int32_t *pnAdapterIndex, int32_t *pnAdapterOutputIndex ) { _table.GetDXGIOutputInfo(pnAdapterIndex, pnAdapterOutputIndex); }

    };

    static const char * const IVRExtendedDisplay_Version = "FnTable:IVRExtendedDisplay_001";

}


// ivrtrackedcamera.h
namespace vr
{

struct VR_IVRTrackedCamera_FnTable
{
    const char *(__stdcall *GetCameraErrorNameFromEnum)( vr::EVRTrackedCameraError eCameraError );
    vr::EVRTrackedCameraError (__stdcall *HasCamera)( vr::TrackedDeviceIndex_t nDeviceIndex, bool *pHasCamera );
    vr::EVRTrackedCameraError (__stdcall *GetCameraFrameSize)( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, uint32_t *pnWidth, uint32_t *pnHeight, uint32_t *pnFrameBufferSize );
    vr::EVRTrackedCameraError (__stdcall *GetCameraIntrinisics)( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, vr::HmdVector2_t *pFocalLength, vr::HmdVector2_t *pCenter );
    vr::EVRTrackedCameraError (__stdcall *GetCameraProjection)( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, float flZNear, float flZFar, vr::HmdMatrix44_t *pProjection );
    vr::EVRTrackedCameraError (__stdcall *AcquireVideoStreamingService)( vr::TrackedDeviceIndex_t nDeviceIndex, vr::TrackedCameraHandle_t *pHandle );
    vr::EVRTrackedCameraError (__stdcall *ReleaseVideoStreamingService)( vr::TrackedCameraHandle_t hTrackedCamera );
    vr::EVRTrackedCameraError (__stdcall *GetVideoStreamFrameBuffer)( vr::TrackedCameraHandle_t hTrackedCamera, vr::EVRTrackedCameraFrameType eFrameType, void *pFrameBuffer, uint32_t nFrameBufferSize, vr::CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize );
};

class IVRTrackedCamera
{
    VR_IVRTrackedCamera_FnTable _table;
public:
    /** Returns a string for an error */
    const char *GetCameraErrorNameFromEnum( vr::EVRTrackedCameraError eCameraError ) { return _table.GetCameraErrorNameFromEnum(eCameraError); }

    /** For convenience, same as tracked property request Prop_HasCamera_Bool */
    vr::EVRTrackedCameraError HasCamera( vr::TrackedDeviceIndex_t nDeviceIndex, bool *pHasCamera ) { return _table.HasCamera(nDeviceIndex, pHasCamera); }

    /** Gets size of the image frame. */
    vr::EVRTrackedCameraError GetCameraFrameSize( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, uint32_t *pnWidth, uint32_t *pnHeight, uint32_t *pnFrameBufferSize ) { return _table.GetCameraFrameSize(nDeviceIndex, eFrameType, pnWidth, pnHeight, pnFrameBufferSize); }

    vr::EVRTrackedCameraError GetCameraIntrinisics( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, vr::HmdVector2_t *pFocalLength, vr::HmdVector2_t *pCenter ) { return _table.GetCameraIntrinisics(nDeviceIndex, eFrameType, pFocalLength, pCenter); }

    vr::EVRTrackedCameraError GetCameraProjection( vr::TrackedDeviceIndex_t nDeviceIndex, vr::EVRTrackedCameraFrameType eFrameType, float flZNear, float flZFar, vr::HmdMatrix44_t *pProjection ) { return _table.GetCameraProjection(nDeviceIndex, eFrameType, flZNear, flZFar, pProjection); }

    /** Acquiring streaming service permits video streaming for the caller. Releasing hints the system that video services do not need to be maintained for this client.
    * If the camera has not already been activated, a one time spin up may incur some auto exposure as well as initial streaming frame delays.
    * The camera should be considered a global resource accessible for shared consumption but not exclusive to any caller.
    * The camera may go inactive due to lack of active consumers or headset idleness. */
    vr::EVRTrackedCameraError AcquireVideoStreamingService( vr::TrackedDeviceIndex_t nDeviceIndex, vr::TrackedCameraHandle_t *pHandle ) { return _table.AcquireVideoStreamingService(nDeviceIndex, pHandle); }
    vr::EVRTrackedCameraError ReleaseVideoStreamingService( vr::TrackedCameraHandle_t hTrackedCamera ) { return _table.ReleaseVideoStreamingService(hTrackedCamera); }

    /** Copies the image frame into a caller's provided buffer. The image data is currently provided as RGBA data, 4 bytes per pixel.
    * A caller can provide null for the framebuffer or frameheader if not desired. Requesting the frame header first, followed by the frame buffer allows
    * the caller to determine if the frame as advanced per the frame header sequence.
    * If there is no frame available yet, due to initial camera spinup or re-activation, the error will be VRTrackedCameraError_NoFrameAvailable.
    * Ideally a caller should be polling at ~16ms intervals */
    vr::EVRTrackedCameraError GetVideoStreamFrameBuffer( vr::TrackedCameraHandle_t hTrackedCamera, vr::EVRTrackedCameraFrameType eFrameType, void *pFrameBuffer, uint32_t nFrameBufferSize, vr::CameraVideoStreamFrameHeader_t *pFrameHeader, uint32_t nFrameHeaderSize ) { return _table.GetVideoStreamFrameBuffer(hTrackedCamera, eFrameType, pFrameBuffer, nFrameBufferSize, pFrameHeader, nFrameHeaderSize); }
};

static const char * const IVRTrackedCamera_Version = "FnTable:IVRTrackedCamera_002";

} // namespace vr

// End

#endif // _OPENVR_API


namespace vr
{
    /** Finds the active installation of the VR API and initializes it. The provided path must be absolute
    * or relative to the current working directory. These are the local install versions of the equivalent
    * functions in steamvr.h and will work without a local Steam install.
    *
    * This path is to the "root" of the VR API install. That's the directory with
    * the "drivers" directory and a platform (i.e. "win32") directory in it, not the directory with the DLL itself.
    */
    inline IVRSystem *VR_Init( EVRInitError *peError, EVRApplicationType eApplicationType );

    /** unloads vrclient.dll. Any interface pointers from the interface are
    * invalid after this point */
    inline void VR_Shutdown();

    /** Returns true if there is an HMD attached. This check is as lightweight as possible and
    * can be called outside of VR_Init/VR_Shutdown. It should be used when an application wants
    * to know if initializing VR is a possibility but isn't ready to take that step yet.
    */
    VR_INTERFACE bool VR_CALLTYPE VR_IsHmdPresent();

    /** Returns true if the OpenVR runtime is installed. */
    VR_INTERFACE bool VR_CALLTYPE VR_IsRuntimeInstalled();

    /** Returns where the OpenVR runtime is installed. */
    VR_INTERFACE const char *VR_CALLTYPE VR_RuntimePath();

    /** Returns the name of the enum value for an EVRInitError. This function may be called outside of VR_Init()/VR_Shutdown(). */
    VR_INTERFACE const char *VR_CALLTYPE VR_GetVRInitErrorAsSymbol( EVRInitError error );

    /** Returns an english string for an EVRInitError. Applications should call VR_GetVRInitErrorAsSymbol instead and
    * use that as a key to look up their own localized error message. This function may be called outside of VR_Init()/VR_Shutdown(). */
    VR_INTERFACE const char *VR_CALLTYPE VR_GetVRInitErrorAsEnglishDescription( EVRInitError error );

    /** Returns the interface of the specified version. This method must be called after VR_Init. The
    * pointer returned is valid until VR_Shutdown is called.
    */
    VR_INTERFACE void *VR_CALLTYPE VR_GetGenericInterface( const char *pchInterfaceVersion, EVRInitError *peError );

    /** Returns whether the interface of the specified version exists.
    */
    VR_INTERFACE bool VR_CALLTYPE VR_IsInterfaceVersionValid( const char *pchInterfaceVersion );

    /** Returns a token that represents whether the VR interface handles need to be reloaded */
    VR_INTERFACE uint32_t VR_CALLTYPE VR_GetInitToken();

    // These typedefs allow old enum names from SDK 0.9.11 to be used in applications.
    // They will go away in the future.
    typedef EVRInitError HmdError;
    typedef EVREye Hmd_Eye;
    typedef EGraphicsAPIConvention GraphicsAPIConvention;
    typedef EColorSpace ColorSpace;
    typedef ETrackingResult HmdTrackingResult;
    typedef ETrackedDeviceClass TrackedDeviceClass;
    typedef ETrackingUniverseOrigin TrackingUniverseOrigin;
    typedef ETrackedDeviceProperty TrackedDeviceProperty;
    typedef ETrackedPropertyError TrackedPropertyError;
    typedef EVRSubmitFlags VRSubmitFlags_t;
    typedef EVRState VRState_t;
    typedef ECollisionBoundsStyle CollisionBoundsStyle_t;
    typedef EVROverlayError VROverlayError;
    typedef EVRFirmwareError VRFirmwareError;
    typedef EVRCompositorError VRCompositorError;

    inline uint32_t &VRToken()
    {
        static uint32_t token;
        return token;
    }

    class COpenVRContext
    {
    public:
        COpenVRContext() { Clear(); }
        void Clear();

        inline void CheckClear()
        {
            if ( VRToken() != VR_GetInitToken() )
            {
                Clear();
                VRToken() = VR_GetInitToken();
            }
        }

        IVRSystem *VRSystem()
        {
            CheckClear();
            if ( m_pVRSystem == nullptr )
            {
                EVRInitError eError;
                m_pVRSystem = ( IVRSystem * )VR_GetGenericInterface( IVRSystem_Version, &eError );
            }
            return m_pVRSystem;
        }
        IVRChaperone *VRChaperone()
        {
            CheckClear();
            if ( m_pVRChaperone == nullptr )
            {
                EVRInitError eError;
                m_pVRChaperone = ( IVRChaperone * )VR_GetGenericInterface( IVRChaperone_Version, &eError );
            }
            return m_pVRChaperone;
        }

        IVRChaperoneSetup *VRChaperoneSetup()
        {
            CheckClear();
            if ( m_pVRChaperoneSetup == nullptr )
            {
                EVRInitError eError;
                m_pVRChaperoneSetup = ( IVRChaperoneSetup * )VR_GetGenericInterface( IVRChaperoneSetup_Version, &eError );
            }
            return m_pVRChaperoneSetup;
        }

        IVRCompositor *VRCompositor()
        {
            CheckClear();
            if ( m_pVRCompositor == nullptr )
            {
                EVRInitError eError;
                m_pVRCompositor = ( IVRCompositor * )VR_GetGenericInterface( IVRCompositor_Version, &eError );
            }
            return m_pVRCompositor;
        }

        IVROverlay *VROverlay()
        {
            CheckClear();
            if ( m_pVROverlay == nullptr )
            {
                EVRInitError eError;
                m_pVROverlay = ( IVROverlay * )VR_GetGenericInterface( IVROverlay_Version, &eError );
            }
            return m_pVROverlay;
        }

        IVRRenderModels *VRRenderModels()
        {
            CheckClear();
            if ( m_pVRRenderModels == nullptr )
            {
                EVRInitError eError;
                m_pVRRenderModels = ( IVRRenderModels * )VR_GetGenericInterface( IVRRenderModels_Version, &eError );
            }
            return m_pVRRenderModels;
        }

        IVRExtendedDisplay *VRExtendedDisplay()
        {
            CheckClear();
            if ( m_pVRExtendedDisplay == nullptr )
            {
                EVRInitError eError;
                m_pVRExtendedDisplay = ( IVRExtendedDisplay * )VR_GetGenericInterface( IVRExtendedDisplay_Version, &eError );
            }
            return m_pVRExtendedDisplay;
        }

        IVRSettings *VRSettings()
        {
            CheckClear();
            if ( m_pVRSettings == nullptr )
            {
                EVRInitError eError;
                m_pVRSettings = ( IVRSettings * )VR_GetGenericInterface( IVRSettings_Version, &eError );
            }
            return m_pVRSettings;
        }

        IVRApplications *VRApplications()
        {
            CheckClear();
            if ( m_pVRApplications == nullptr )
            {
                EVRInitError eError;
                m_pVRApplications = ( IVRApplications * )VR_GetGenericInterface( IVRApplications_Version, &eError );
            }
            return m_pVRApplications;
        }

        IVRTrackedCamera *VRTrackedCamera()
        {
            CheckClear();
            if ( m_pVRTrackedCamera == nullptr )
            {
                EVRInitError eError;
                m_pVRTrackedCamera = ( IVRTrackedCamera * )VR_GetGenericInterface( IVRTrackedCamera_Version, &eError );
            }
            return m_pVRTrackedCamera;
        }

    private:
        IVRSystem           *m_pVRSystem;
        IVRChaperone        *m_pVRChaperone;
        IVRChaperoneSetup   *m_pVRChaperoneSetup;
        IVRCompositor       *m_pVRCompositor;
        IVROverlay          *m_pVROverlay;
        IVRRenderModels     *m_pVRRenderModels;
        IVRExtendedDisplay  *m_pVRExtendedDisplay;
        IVRSettings         *m_pVRSettings;
        IVRApplications     *m_pVRApplications;
        IVRTrackedCamera    *m_pVRTrackedCamera;
    };

    inline COpenVRContext &OpenVRInternal_ModuleContext()
    {
        static void *ctx[ sizeof( COpenVRContext ) / sizeof( void * ) ];
        return *( COpenVRContext * )ctx; // bypass zero-init constructor
    }

    inline IVRSystem *VR_CALLTYPE VRSystem() { return OpenVRInternal_ModuleContext().VRSystem(); }
    inline IVRChaperone *VR_CALLTYPE VRChaperone() { return OpenVRInternal_ModuleContext().VRChaperone(); }
    inline IVRChaperoneSetup *VR_CALLTYPE VRChaperoneSetup() { return OpenVRInternal_ModuleContext().VRChaperoneSetup(); }
    inline IVRCompositor *VR_CALLTYPE VRCompositor() { return OpenVRInternal_ModuleContext().VRCompositor(); }
    inline IVROverlay *VR_CALLTYPE VROverlay() { return OpenVRInternal_ModuleContext().VROverlay(); }
    inline IVRRenderModels *VR_CALLTYPE VRRenderModels() { return OpenVRInternal_ModuleContext().VRRenderModels(); }
    inline IVRApplications *VR_CALLTYPE VRApplications() { return OpenVRInternal_ModuleContext().VRApplications(); }
    inline IVRSettings *VR_CALLTYPE VRSettings() { return OpenVRInternal_ModuleContext().VRSettings(); }
    inline IVRExtendedDisplay *VR_CALLTYPE VRExtendedDisplay() { return OpenVRInternal_ModuleContext().VRExtendedDisplay(); }
    inline IVRTrackedCamera *VR_CALLTYPE VRTrackedCamera() { return OpenVRInternal_ModuleContext().VRTrackedCamera(); }

    inline void COpenVRContext::Clear()
    {
        m_pVRSystem = nullptr;
        m_pVRChaperone = nullptr;
        m_pVRChaperoneSetup = nullptr;
        m_pVRCompositor = nullptr;
        m_pVROverlay = nullptr;
        m_pVRRenderModels = nullptr;
        m_pVRExtendedDisplay = nullptr;
        m_pVRSettings = nullptr;
        m_pVRApplications = nullptr;
        m_pVRTrackedCamera = nullptr;
    }

    VR_INTERFACE uint32_t VR_CALLTYPE VR_InitInternal( EVRInitError *peError, EVRApplicationType eApplicationType );
    VR_INTERFACE void VR_CALLTYPE VR_ShutdownInternal();

    /** Finds the active installation of vrclient.dll and initializes it */
    inline IVRSystem *VR_Init( EVRInitError *peError, EVRApplicationType eApplicationType )
    {
        IVRSystem *pVRSystem = nullptr;

        EVRInitError eError;
        VRToken() = VR_InitInternal( &eError, eApplicationType );
        COpenVRContext &ctx = OpenVRInternal_ModuleContext();
        ctx.Clear();

        if ( eError == VRInitError_None )
        {
            if ( VR_IsInterfaceVersionValid( IVRSystem_Version ) )
            {
                pVRSystem = VRSystem();
            }
            else
            {
                VR_ShutdownInternal();
                eError = VRInitError_Init_InterfaceNotFound;
            }
        }

        if ( peError )
            *peError = eError;
        return pVRSystem;
    }

    /** unloads vrclient.dll. Any interface pointers from the interface are
    * invalid after this point */
    inline void VR_Shutdown()
    {
        VR_ShutdownInternal();
    }
}
