#include <math.h>
#include "shader.h"
#include "mi_shader_if.h"
#include <stdio.h>
#include <stdlib.h>

#include "MYMR_Brick.h"

#define BRICKWIDTH  0.25
#define BRICKHEIGHT  0.08
#define MORTARTHICKNESS  0.01

#define BMWIDTH (*brickwidth+*mortarthickness)
#define BMHEIGHT (*brickHeight+*mortarthickness)
#define MWF (*mortarthickness*0.5/BMWIDTH)
#define MHF (*mortarthickness*0.5/BMHEIGHT)

#define RED_C .7
#define GREEN_C .3
#define BLUE_C .6
#define PERC .7 



extern "C" DLLEXPORT int MYMR_Brick_version(){
	return (1);
}

extern "C" DLLEXPORT miBoolean MYMR_Brick(
		miColor *result ,
		miState *state, 
		struct MYMR_Brick_p *paras)
{
	
	miScalar s = state->tex_list[0].x;
	miScalar t = state->tex_list[0].y;
	miColor* mortarColor_param, *brickColor_param;
	miScalar* brickwidth = mi_eval_scalar(&paras->brickWidth);
	miScalar* brickHeight = mi_eval_scalar(&paras->brickHeight);
	miScalar* mortarthickness = mi_eval_scalar(&paras->mortarThickness);
	
	miScalar ss,tt, sbrick,tbrick,w,h;
	miScalar scoord = s;
	miScalar tcoord = t;
	
	brickColor_param  = mi_eval_color(&paras->brickColor);
	mortarColor_param  = mi_eval_color(&paras->mortarColor);
	
	// Figure out the brick texture

	ss = scoord/BMWIDTH;
	tt = tcoord/BMHEIGHT;
	
	if(mod(tt*0.5,1)> 0.5) {
		ss += 0.5;
	}
	//printf("%f %f\n", u,v);
	sbrick = floor(ss);
	tbrick = floor(tt);
	
	ss -= sbrick;
	tt -= tbrick;
	
	w = step(MWF,ss) - step(1-MWF,ss);
	h = step(MHF,tt) - step(1-MHF,tt);
	
	// Noise on texture
	miScalar grainFactor = *mi_eval_scalar(&paras->grainFactor);
	
	
	miScalar brickPattern ;
	miColor *brickColor = (miColor *) malloc(sizeof(miColor));
	miColor *mortarColor = (miColor *) malloc(sizeof(miColor));
	
	//brickPattern=w*h*grain;
	brickPattern = w*h;
	
	//I'll use this later to create a displacement
	

	//
	//  Bump from mortar
	//
	
	miScalar sbump = smoothstep(0,MWF,ss) - smoothstep(1-MWF,1,ss);
	miScalar tbump = smoothstep(0,MHF,tt) - smoothstep(1-MHF,1,tt);
	miScalar mortarPattern = 1-(sbump * tbump);
	miScalar bumpval = remap(1-mortarPattern,0,1,.25,1); 
	
	

	mi_vector_to_object(state, &state->normal, &state->normal);
	
	state->normal.x += (bumpval);
	state->normal.y += (bumpval);
	
	mi_vector_from_object(state, &state->normal, &state->normal);
	mi_vector_normalize(&state->normal);

	
	miScalar grain = remap(brick_grain_noise(state, grainFactor),0,1,0.5,0.75); 
	miScalar mgrain = remap(mortar_grain_noise(state, grainFactor),0,1,0.5,0.75);
	// Colors
	
	mortarColor->r = mortarPattern*mortarColor_param->r*mgrain;
	mortarColor->g = mortarPattern*mortarColor_param->g*mgrain;
	mortarColor->b = mortarPattern*mortarColor_param->b*mgrain;
	
	brickColor->r=brickPattern*brickColor_param->r*grain;
	brickColor->g=brickPattern*brickColor_param->g*grain;
	brickColor->b=brickPattern*brickColor_param->b*grain;
	
	// BRDF
	miColor *diffuse_color = diffuse(state);
	
	result->r = diffuse_color->r*(brickColor->r+mortarColor->r);
	result->g = diffuse_color->g*(brickColor->g+mortarColor->g);
	result->b = diffuse_color->b*(brickColor->b+mortarColor->b);
	
	//result->r = mgrain;
	//result->g = mgrain;
	//result->b = mgrain;
	
	
	return miTRUE;
}



void brick_base_color(miColor *result, miColor *base,miState *state){
	
}



miScalar brick_grain_noise(miState *state, miScalar factor){
	miVector *p = &state->point;

	mi_vector_mul(p,10000*factor);
	
	miScalar noise = mi_unoise_3d(p);
	
	miScalar noisecolorchannel[3];
	noisecolorchannel[0] = RED_C*(1-PERC);
	noisecolorchannel[1] = RED_C;
	noisecolorchannel[2] = RED_C*(1+PERC);
	miScalar retval = mi_spline(noise,3,noisecolorchannel);

	return retval;
}

miScalar mortar_grain_noise(miState *state, miScalar factor){
	miVector *p = &state->point;

	mi_vector_mul(p,100000*factor);
		
	miScalar noise = mi_unoise_3d(p);
	
	miScalar noisecolorchannel[3];
	noisecolorchannel[0] = RED_C*(1-PERC);
	noisecolorchannel[1] = RED_C;
	noisecolorchannel[2] = RED_C*(1+PERC);
	miScalar retval = mi_spline(noise,3,noisecolorchannel);

	return retval;
}

miScalar remap(miScalar x, miScalar a1, miScalar b1, miScalar a2, miScalar b2){
	return(x*(b2-a2)-a1*b2+b1*a2)/(b1-a1);
}

miVector mymr_point_create(miScalar x, miScalar y, miScalar z){
	miVector result;
	result.x = x;
	result.y = y;
	result.z = z;
	return result;
}

miColor color_create(miScalar r, miScalar g,miScalar b){
	miColor result;
	result.r = r;
	result.g = g;
	result.b = b;
	return result;
}

miColor * diffuse(miState * state){
	miTag *light = (miTag *) malloc(sizeof(miTag *));
	
	int light_sample_count = 0;
	int light_count = 0;
	miScalar dot_normal_light;	
	miColor light_color;
	
	miColor *diffuse_out = (miColor *) malloc(sizeof(miColor *));
	miColor *sum = (miColor *) malloc(sizeof(miColor *));
	
	mi_inclusive_lightlist(&light_count, &light, state);
	
	diffuse_out->r = diffuse_out->g = diffuse_out->b = 0;
	
	for (mi::shader::LightIterator iter(state, light, light_count);
			     !iter.at_end(); ++iter) {
		
		light_sample_count = 0;
		sum->r = sum->g = sum->b = 0;
		
		while(iter->sample()){
			
			dot_normal_light = iter->get_dot_nl();
			
			iter->get_contribution(&light_color);

			sum->r += (dot_normal_light * light_color.r);
			sum->g += (dot_normal_light * light_color.g);
			sum->b += (dot_normal_light * light_color.b);
			
			light_sample_count++;
		}
		
		if (light_sample_count){
			diffuse_out->r += sum->r/light_sample_count;
			diffuse_out->g += sum->g/light_sample_count;
			diffuse_out->b += sum->b/light_sample_count;			
		}
		
	}

	return diffuse_out;
		
}

void multiply(miColor *a_color,  miColor *b_color, miColor *out_pResult){
	out_pResult->r = a_color->r*b_color->r;
	out_pResult->g = a_color->g*b_color->g;
	out_pResult->b = a_color->b*b_color->b;

	if (out_pResult->r<0){
		out_pResult->r = 0;
	}
	if (out_pResult->g<0){
		out_pResult->g = 0;
	}
	if (out_pResult->b<0){
		out_pResult->b = 0;
	}
}

miScalar smoothstep(miScalar a, miScalar b, miScalar x){
	if(x < a){
		return 0;
	}
	if (x>=b){
		return 1;
	}
	x = (x - a)/(b-a);
	
	return (x*x*(3-2*x));
}

miScalar step(miScalar a, miScalar x){
	return miScalar (x>=a);
}

miColor * mix( miColor * color0, miColor * color1, miScalar value , miColor * result) { 
	result->r = (1-value)*color0->r + value*color1->r;
	result->g = (1-value)*color0->g + value*color1->g;
	result->b = (1-value)*color0->b + value*color1->b;
	
	return result; 
} 

miScalar mod(miScalar a, miScalar b){
	int n = (int) a/b;
	a -= n*b;
	if(a<0) a+= b;
	return a;
}