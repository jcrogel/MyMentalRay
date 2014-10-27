#include <math.h>
#include "shader.h"
#include "mi_shader_if.h"
#include <stdio.h>
#include <stdlib.h>

#include "MYMR_AmbientOcclusion.h"

extern "C" DLLEXPORT int MYMR_AmbientOcclusion_version(){
	return (1);
}

extern "C" DLLEXPORT miBoolean MYMR_AmbientOcclusion(
		miColor *result ,
		miState *state, 
		struct MYMR_AmbientOcclusion_p *paras)
{
	miUint samples = * mi_eval_integer(&paras->samples);
	miVector trace_direction;
	miUshort dimension = 2;
	int instance = 0, found=0;
	double amb_exp;
	
	double sample[dimension];
	//Try to get samples to random places monte carlo style
	while (mi_sample(sample,&instance,state,dimension,&samples)){
		// get the direction of the ray given the sample
		mi_reflection_dir_diffuse_x(&trace_direction,state,sample);
		if (mi_trace_probe(state, &trace_direction, &state->point)){
			found++;
		}
	}
	printf("%d %d\n",found,samples);
	amb_exp = 1.0 - ((double)found/(double)samples);
	printf("%f\n",amb_exp);
	result->r = result->g  = result->b = amb_exp;
	
	return miTRUE;
}
