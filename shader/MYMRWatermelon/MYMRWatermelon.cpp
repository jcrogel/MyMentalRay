#include <math.h>
#include "shader.h"
#include "mi_shader_if.h"
#include <stdio.h>
#include <stdlib.h>

#include "MYMRWatermelon.h"

extern "C" DLLEXPORT int MYMRWatermelon_version(){
	return (1);
}

extern "C" DLLEXPORT miBoolean MYMRWatermelon(
		struct MYMRWatermelon_o *resultStruct ,
		miState *state, 
		struct MYMRWatermelon_p *paras)
{

	return miTRUE;
}