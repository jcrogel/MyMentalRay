#include <math.h>
#include "shader.h"
#include <stdio.h>

struct MYMRPassManager_p{
	int		i_col;
	int		n_col;	
	miColor	col[1];	
};

extern "C" DLLEXPORT int MYMRPassManager_version(){
	return (1);
}

extern "C" DLLEXPORT miBoolean MYMRPassManager(
		miColor *result ,
		miState *state, 
		struct MYMRPassManager_p *paras)
{
	int n_col   = *mi_eval_integer(&paras->n_col);
	int i_col   = *mi_eval_integer(&paras->i_col);
	miColor *first;

	for (int n = 0; n < n_col; n++){
		miColor *color = mi_eval_color(paras->col + i_col + n);
		if( n==0)
			first = color;
		mi_fb_put(state, n, color);
	}

	*result = *first;

	return miTRUE;
}