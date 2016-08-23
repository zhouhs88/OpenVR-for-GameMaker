///vr_get_rendermodelcount()
/*
    Returns the number of models ready to be provided by the SteamVR system.
    
    Returns     -    number of models that can be accessed
 */
if (!global.vive_isrunning)
    return 0;
    
return external_call(global.vive_external_getrendermodelcount);
