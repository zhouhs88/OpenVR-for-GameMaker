///vr_generate_controller_model(index)
/*
    Generates a model for the specified controller and returns the
    vertex buffer if successful. If there was a problem, undefined will be returned.
    
    Note: If the controller is NOT turned on then this will fail! You MUST have a controller
    detected by the system for the model to be available to load.
    
    Argument0   -   index of controller (base 1)
    Returns     -   vertex buffer of model data (or undefined if error)
 */
 
if (!global.vive_isrunning)
    return undefined;
    
argument0 = real(argument0);
    
var __vertexCount = external_call(global.vive_external_getcontrollervertexcount, argument0);

    // Controller may not be detected or incorrect index:
if (__vertexCount == 0)
    return undefined;
    
    // (byte * vertices * data per vertex)
var __buffer = buffer_create(8 * __vertexCount * 8, buffer_fixed, 8);

if (!external_call(global.vive_external_loadcontrollermodel, argument0, buffer_get_address(__buffer)))
{
    buffer_delete(__buffer);
    return undefined;
}

var __vBuffer = vertex_create_buffer_from_buffer(__buffer, global.vive_bufferformat);
buffer_delete(__buffer);

return __vBuffer;
