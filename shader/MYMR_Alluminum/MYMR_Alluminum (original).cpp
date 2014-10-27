#include <math.h>
#include "shader.h"
#include "mi_shader_if.h"
#include <stdio.h>
#include <stdlib.h>

#include "MYMR_Alluminum.h"

extern "C" DLLEXPORT int MYMR_Alluminum_version(){
	return (1);
}

extern "C" DLLEXPORT miBoolean MYMR_Alluminum(
		struct MYMR_Alluminum_o *resultStruct ,
		miState *state, 
		struct MYMR_Alluminum_p *paras)
{
	miScalar shiny = *mi_eval_scalar(&params->shiny);    
    int n_samples  = 2;
    int samples[2] = {50,1};
    miVector reflect_dir;
    miColor reflect_color;
    double sampled_dir[2];
    int level = state->reflection_level, sample_number = 0;
    miUint sample_count = samples[level >= n_samples ? n_samples - 1 : level];

    // glossy spec
    result->r = result->g = result->b = 0.0;
    while (mi_sample(sampled_dir, &sample_number, 
                     state, 2, &sample_count)) {
        mi_reflection_dir_glossy_x(&reflect_dir, state, shiny, 
                                   sampled_dir);
        if (!mi_trace_reflection(&reflect_color, state, &reflect_dir))
            mi_trace_environment(&reflect_color, state, &reflect_dir);
        miaux_add_color(result, &reflect_color);
    }
    miaux_scale_color(result, 1.0 / (double)sample_count);
    
    // glossy_percentage
    miaux_scale_color(result, .60);
    
    
    
    return miTRUE;
}
