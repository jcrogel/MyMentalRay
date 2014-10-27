#include <math.h>
#include <shader.h>
#include <stdio.h>

#include "FirstShader.h"

int FirstShader_version(void){
	return 1;
}
	

DLLEXPORT miBoolean FirstShader( miColor * out_pResult, miState * state, 
		FirstShader_Params* in_pParams){
	miColor *basecolor = mi_eval_color(&(in_pParams->BaseColor ));
	miInteger value = in_pParams->Value;
	
	float shift = (value/10.0);
	out_pResult->r  = basecolor->r+shift;
	out_pResult->g  = basecolor->g+shift;
	out_pResult->b  = basecolor->b+shift;
	printf("Result Color R value: %f G value: %f B value: %f\n", (float)out_pResult->r, 
			(float)out_pResult->g, (float)out_pResult->b);
	return miTRUE;
}
