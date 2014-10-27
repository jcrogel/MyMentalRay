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
	
	//Param values
	miColor *specular = mi_eval_color(&paras->specular);
	miScalar specular_exponent = *mi_eval_scalar(&paras->specular_exponent);
	miColor *diffuse = mi_eval_color(&paras->diffuse);
	miColor *result = mi_eval_color(&resultStruct->result);
	
	//At least it should get the ambient color. I think that somehow ambient should be an ambient light or something....to be studied
	*result = *mi_eval_color(&paras->ambient);
		
	//Do lighting shit
	//Get all the lights
	do_diffuse_and_spec(result,state,diffuse,specular,specular_exponent);
	
	// Do the refraction stuff
	miScalar reflection_factor = *mi_eval_scalar(&paras->reflection_factor);
	miColor *reflection = mi_eval_color(&paras->reflection);
	do_reflections(result,state,reflection,reflection_factor);
	
	// Do the transparency stuff
	//miScalar refraction_factor = *mi_eval_scalar(&paras->refraction_factor);
	//miColor *refraction = mi_eval_color(&paras->refraction);
	//miScalar ior = *mi_eval_scalar(&paras->ior);
	//calculate_ior(state,ior);
	//printf("in:%f out:%f\n",state->ior,state->ior_in);
	//do_refractions(result,state,refraction,refraction_factor);
	
	//printf("\e[33mPost Red: %f\tGreen: %f\tBlue: %f\e[0m\n",result->r,result->g,result->b);

	return miTRUE;
}

void calculate_ior(miState *state,miScalar ior){
	
	miScalar *ior_in = (miScalar *) malloc(sizeof(miScalar *));
	miScalar *ior_out = (miScalar *) malloc(sizeof(miScalar *));
	
	miScalar *vacuum_ior =(miScalar *) malloc(sizeof(miScalar *));
	*vacuum_ior = 1.0;
	
	ior_in = &ior;
	ior_out = vacuum_ior;
	
	miState  *s =(miState *) malloc(sizeof(miState *));
	for (s = state; s != NULL; s = s->parent){
		if (s->material == state->material){
			ior_in = vacuum_ior;
			ior_out = &ior;
		}
	}
	
	state->ior = *ior_out;
	state->ior_in = *ior_in;
	//printf("Tag:%d \n",state->instance);
	//delete ior_in;
	//delete ior_out;
	//delete vacuum_ior;
	
	return;

}

void do_refractions(miColor *result,miState *state,miColor *refraction, miScalar factor){
	miVector *refraction_direction = (miVector *) malloc(sizeof(miVector *));
	miColor *refr =  (miColor *) malloc(sizeof(miColor *));
	miBoolean found = miFALSE;
	
	refr->r = refraction->r;
	refr->g = refraction->g;
	refr->b = refraction->b;
	
	//printf("refr:%d refraction:%d\n",&refr->r,&refraction->r);
	
	if (factor > 0){
		//miScalar *ior = mi_eval_scalar(&state->ior);
		miScalar f =1 - factor;
		result->r *= f;
		result->b *= f;
		result->g *= f;
		result->a = f;

		/*if(state->ior == 1.0 || state->ior==0.0  || state->ior_in==1.0 || state->ior_in==0.0){
			mi_trace_transparent(refr, state);
			printf(" %f %f %f\n",state->dir.x,state->dir.y,state->dir.z);
			found = miTRUE;
		}else{*/
			if(mi_refraction_dir(refraction_direction,state,state->ior_in,state->ior)){
				if( mi_trace_refraction(refr,state,refraction_direction)){
					//printf("Here2\n");
					found = miTRUE;
				}
				
			}else{
				if( mi_trace_environment(refr,state,refraction_direction)){
					//printf("Here3\n");
					found = miTRUE;
				}
			}
		//}
		if (found == miTRUE){
			result->r += factor * refr->r;
			result->g += factor * refr->g;
			result->b += factor * refr->b;
			result->a += factor * refr->a;
		}
		//printf("\e[34mDirection X: %f\tY: %f\tZ: %f\e[0m\n",refraction_direction->x,refraction_direction->y,refraction_direction->z);
		//printf("\e[32mDirection X: %f\tY: %f\tZ: %f\e[0m\n",refraction_direction->x,refraction_direction->y,refraction_direction->z);
		//mi_mem_release(refraction_direction);
		delete refraction_direction;
		delete refr;
		
	}
	
	return;
	
}

void do_reflections(miColor *result,miState *state,miColor *reflection, miScalar factor){
	
	miVector *reflection_direction = (miVector *) malloc(sizeof(miVector *));
	if (factor> 0){
		miScalar f =  1 - factor;
		result->r *= f;
		result->g *= f;
		result->b *= f;
		
		mi_reflection_dir(reflection_direction,state);
		if(mi_trace_reflection(reflection,state,reflection_direction) || 
				mi_trace_environment(reflection,state,reflection_direction)){
			result->r += factor * reflection->r;
			result->g += factor * reflection->g;
			result->b += factor * reflection->b;
		}
	}
	delete reflection_direction;
}

void do_diffuse_and_spec(miColor *result,miState *state,miColor *diffuse, miColor *specular,miScalar specular_exponent){	
	// Lights stuff
	miTag *light = (miTag *) malloc(sizeof(miTag *));
	
	int light_sample_count = 0;
	int light_count = 0;
	miScalar dot_normal_light;	
	miColor light_color;
	
	// TMP variables
	miColor sum;
	miVector light_direction;
	miScalar spec_amount;
	
	//resultValues
	miColor *diffuse_out = (miColor *) malloc(sizeof(miColor *));
	miColor *specular_out = (miColor *) malloc(sizeof(miColor *));
	
	mi_inclusive_lightlist(&light_count, &light, state);
	for (mi::shader::LightIterator iter(state, light, light_count);
			     !iter.at_end(); ++iter) {
			
		light_sample_count = 0;
		sum.r = sum.g = sum.b = 0;
		
		while(iter->sample()){
			
			dot_normal_light = iter->get_dot_nl();
			iter->get_contribution(&light_color);
			light_direction = iter->get_direction();
			miVector normal = state->normal;
			spec_amount = pow(mi_vector_dot(&normal,&light_direction),specular_exponent);
			diffuse_out->r = (dot_normal_light * diffuse->r * light_color.r);
			diffuse_out->g = (dot_normal_light * diffuse->g * light_color.g);
			diffuse_out->b = (dot_normal_light * diffuse->b * light_color.b);
			
			specular_out->r = (specular->r * light_color.r * spec_amount);
			specular_out->g = (specular->g * light_color.g * spec_amount);
			specular_out->b = (specular->b * light_color.b * spec_amount);
			
			sum.r += diffuse_out->r + specular_out->r;
			sum.g += diffuse_out->g + specular_out->g;
			sum.b += diffuse_out->b + specular_out->b;
			
			light_sample_count++;
		}
		
		if (light_sample_count){
			result->r += sum.r*(1.0/light_sample_count);
			result->g += sum.g*(1.0/light_sample_count);
			result->b += sum.b*(1.0/light_sample_count);
			
		}
		
	}
}
