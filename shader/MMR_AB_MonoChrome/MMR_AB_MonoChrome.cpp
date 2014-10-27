#include <math.h>
#include <shader.h>
#include <stdio.h>

#include "MMR_AB_MonoChrome.h"

int MMR_AB_MonoChrome_version(void){
	return 1;
}
	

DLLEXPORT miBoolean MMR_AB_MonoChrome( miColor * out_pResult, miState * state, 
		MMR_AB_MonoChrome_Params* in_pParams){
	miColor *input_color  = mi_eval_color(&(in_pParams->InputColor ));
	miScalar RWeight = in_pParams->RWeight;
	miScalar GWeight = in_pParams->GWeight;
	miScalar BWeight = in_pParams->BWeight;
	miScalar Brightness = in_pParams->Brightness;

	miScalar fValue = ((input_color->r*RWeight) + (input_color->g*GWeight) + 
	(input_color->b*BWeight));
	
	out_pResult->r  = fValue*Brightness;
	out_pResult->g  =  fValue*Brightness;
	out_pResult->b  =  fValue*Brightness;
	return miTRUE;
	
}
