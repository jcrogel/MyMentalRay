#include <math.h>
#include <shader.h>
#include <stdio.h>

#include "MMR_AB_Mix.h"

int MMR_AB_Mix_version(void){
	return 1;
}

void divide(miColor *a_color,  miColor *b_color, miColor *out_pResult){
	if (a_color->r>0 or b_color->r>0){
		out_pResult->r = a_color->r/b_color->r;
	} else {
		out_pResult->r = 0;
	}
	if (a_color->g>0 or b_color->g>0){
		out_pResult->g = a_color->g/b_color->g;
	} else {
		out_pResult->g = 0;
	}
	if (a_color->b>0 or b_color->b>0){
		out_pResult->b = a_color->b/b_color->b;
	} else {
		out_pResult->b = 0;
	}	
}

void doScreen(miColor *a_color,  miColor *b_color, miColor *out_pResult){
	out_pResult->r = (a_color->r+b_color->r)-(a_color->r*b_color->r);
	out_pResult->g = (a_color->r+b_color->g)-(a_color->r*b_color->g);
	out_pResult->b = (a_color->r+b_color->b)-(a_color->r*b_color->b);
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

void average(miColor *a_color,  miColor *b_color, miColor *out_pResult){
	out_pResult->r = (a_color->r+b_color->r)/2;
	out_pResult->g = (a_color->r+b_color->g)/2;
	out_pResult->b = (a_color->r+b_color->b)/2;
}

void doOver(miColor *a_color,  miColor *b_color, miColor *out_pResult){
	printf("JCMR %f",a_color->a);
	out_pResult->r = a_color->r+(b_color->r*(1-a_color->a));
	out_pResult->g = a_color->g+(b_color->g*(1-a_color->a));
	out_pResult->b = a_color->b+(b_color->b*(1-a_color->a));	
}

void doCopy(miColor *a_color,  miColor *b_color, miColor *out_pResult){
	out_pResult->r = a_color->r;
	out_pResult->g = a_color->g;
	out_pResult->b = a_color->b;
}

void doUnder(miColor *a_color,  miColor *b_color, miColor *out_pResult){
	out_pResult->r = (a_color->r*(1-b_color->a))+b_color->r;
	out_pResult->g = (a_color->g*(1-b_color->a))+b_color->g;
	out_pResult->b = (a_color->b*(1-b_color->a))+b_color->b;
}

void doMask(miColor *a_color,  miColor *b_color, miColor *out_pResult){
	out_pResult->r = (b_color->r*(a_color->a));
	out_pResult->g = (b_color->g*(a_color->a));
	out_pResult->b = (b_color->b*(a_color->a));
}

void doPlus(miColor *a_color,  miColor *b_color, miColor *out_pResult){
	out_pResult->r = (a_color->r+b_color->r);
	out_pResult->g = (a_color->g+b_color->g);
	out_pResult->b = (a_color->b+b_color->b);
}

void doMinus(miColor *a_color,  miColor *b_color, miColor *out_pResult){
	out_pResult->r = (a_color->r-b_color->r);
	out_pResult->g = (a_color->r-b_color->g);
	out_pResult->b = (a_color->r-b_color->b);
}

void doDifference(miColor *a_color,  miColor *b_color, miColor *out_pResult){
	out_pResult->r = fabs(a_color->r-b_color->r);
	out_pResult->g = fabs(a_color->r-b_color->g);
	out_pResult->b = fabs(a_color->r-b_color->b);
}

void doFrom(miColor *a_color,  miColor *b_color, miColor *out_pResult){
	out_pResult->r = (b_color->r-a_color->r);
	out_pResult->g = (b_color->g-a_color->g);
	out_pResult->b = (b_color->b-a_color->b);
}

void doIn(miColor *a_color,  miColor *b_color, miColor *out_pResult){
	out_pResult->r = (a_color->r*b_color->a);
	out_pResult->g = (a_color->g*b_color->a);
	out_pResult->b = (a_color->b*b_color->a);
}

void doOut(miColor *a_color,  miColor *b_color, miColor *out_pResult){
	out_pResult->r = (a_color->r*(1-b_color->a));
	out_pResult->g = (a_color->g*(1-b_color->a));
	out_pResult->b = (a_color->b*(1-b_color->a));
}

void doExclusion(miColor *a_color,  miColor *b_color, miColor *out_pResult){
	out_pResult->r = (a_color->r+b_color->r)-(2*a_color->r*b_color->r);
	out_pResult->g = (a_color->g+b_color->g)-(2*a_color->g*b_color->g);
	out_pResult->b = (a_color->b+b_color->b)-(2*a_color->b*b_color->b);
}

void doMin(miColor *a_color,  miColor *b_color, miColor *out_pResult){
	if (a_color->r<b_color->r){
		out_pResult->r = a_color->r;
	} else {
		out_pResult->r = b_color->r;
	}
	if (a_color->g<b_color->g){
		out_pResult->g = a_color->g;
	} else {
		out_pResult->g = b_color->g;
	}
	if (a_color->b<b_color->b){
		out_pResult->b = a_color->b;
	} else {
		out_pResult->b = b_color->b;
	}	
}

void doMax(miColor *a_color,  miColor *b_color, miColor *out_pResult){
	if (a_color->r>b_color->r){
		out_pResult->r = a_color->r;
	} else {
		out_pResult->r = b_color->r;
	}
	if (a_color->g>b_color->g){
		out_pResult->g = a_color->g;
	} else {
		out_pResult->g = b_color->g;
	}
	if (a_color->b>b_color->b){
		out_pResult->b = a_color->b;
	} else {
		out_pResult->b = b_color->b;
	}	
}

void overlay(miColor *a_color,  miColor *b_color, miColor *out_pResult){
	if(b_color->r < .5){
		out_pResult->r = a_color->r*b_color->r;
		if (out_pResult->r<0){
				out_pResult->r = 0;
		}
	}else{
		out_pResult->r = (a_color->r+b_color->r)-(a_color->r*b_color->r);
	}

	if(b_color->g < .5){
		out_pResult->g = a_color->g*b_color->g;
		if (out_pResult->g<0){
			out_pResult->g = 0;
		}
	}else{
		out_pResult->g = (a_color->g+b_color->g)-(a_color->g*b_color->g);
	}
	
	if(b_color->b < .5){
		out_pResult->b = a_color->b*b_color->b;
		if (out_pResult->b<0){
			out_pResult->b = 0;
		}
	}else{
		out_pResult->b = (a_color->b+b_color->b)-(a_color->b*b_color->b);
	}
}

void doMatte(miColor *a_color,  miColor *b_color, miColor *out_pResult){
	out_pResult->r = a_color->r *a_color->a + b_color->r*(1-a_color->a);
	out_pResult->r = a_color->g *a_color->a + b_color->g*(1-a_color->a);
	out_pResult->r = a_color->b *a_color->a + b_color->b*(1-a_color->a);
}

void doDisjointOver(miColor *a_color,  miColor *b_color, miColor *out_pResult){
	if(a_color->a + b_color->a < 1){
		out_pResult->r = a_color->r + b_color->r;
		out_pResult->g = a_color->g + b_color->g;
		out_pResult->b = a_color->b + b_color->b;
	}else{
		out_pResult->r = a_color->r+(b_color->r*((1-a_color->r)/b_color->r));
		out_pResult->g = a_color->g+(b_color->g*((1-a_color->g)/b_color->g));
		out_pResult->b = a_color->b+(b_color->b*((1-a_color->b)/b_color->b));
	}
}

void doConjointOver(miColor *a_color,  miColor *b_color, miColor *out_pResult){
	if(a_color->a + b_color->a < 1){
		out_pResult->r = a_color->r;
		out_pResult->g = a_color->g;
		out_pResult->b = a_color->b;
	}else{
		out_pResult->r = a_color->r+(b_color->r*(1-(a_color->a/b_color->a)));
		out_pResult->g = a_color->g+(b_color->g*(1-(a_color->a/b_color->a)));
		out_pResult->b = a_color->b+(b_color->b*(1-(a_color->a/b_color->a)));
	}
}

void doStencil(miColor *a_color,  miColor *b_color, miColor *out_pResult){
		out_pResult->r = b_color->r*(1-a_color->a);
		out_pResult->g = b_color->g*(1-a_color->a);
		out_pResult->b = b_color->b*(1-a_color->a);
}

void doXor(miColor *a_color,  miColor *b_color, miColor *out_pResult){
	out_pResult->r = a_color->r*(1-b_color->a)+ b_color->r*(1-a_color->a);
	out_pResult->g = a_color->g*(1-b_color->a)+ b_color->g*(1-a_color->a);
	out_pResult->b = a_color->b*(1-b_color->a)+ b_color->b*(1-a_color->a);
}

void doAtop(miColor *a_color,  miColor *b_color, miColor *out_pResult){
	out_pResult->r = a_color->r*b_color->a+ b_color->r*(1-a_color->a);
	out_pResult->g = a_color->g*b_color->a+ b_color->g*(1-a_color->a);
	out_pResult->b = a_color->b*b_color->a+ b_color->b*(1-a_color->a);	
}

void doGeometric(miColor *a_color,  miColor *b_color, miColor *out_pResult){
	out_pResult->r = (2*a_color->r*b_color->r) / (  a_color->r + b_color->r  );
	out_pResult->g = (2*a_color->g*b_color->g) / (  a_color->g + b_color->g  );
	out_pResult->b = (2*a_color->b*b_color->b) / (  a_color->b + b_color->b  );
}

void doColorDodge(miColor *a_color,  miColor *b_color, miColor *out_pResult){

}

DLLEXPORT miBoolean MMR_AB_Mix( miColor * out_pResult, miState * state, 
		MMR_AB_Mix_Params* in_pParams){
	miColor *a_color  = mi_eval_color(&(in_pParams->AColor ));
	miColor *b_color  = mi_eval_color(&(in_pParams->BColor ));
	miInteger  mode = in_pParams->Mode;

	switch(mode){
		case 0:
			//Over
			doOver(a_color,  b_color, out_pResult);
			break;
		case 1:
			//disjoint-over
			doDisjointOver(a_color,  b_color, out_pResult);
			break;
		case 2:
			//conjoint-over
			doConjointOver(a_color,  b_color, out_pResult);
			break;
		case 3:
			//matte
			doMatte(a_color,  b_color, out_pResult);
			break;
		case 4:
			//Copy
			doCopy(a_color,  b_color, out_pResult);
			break;
		case 5:
			//Under
			doUnder(a_color,  b_color, out_pResult);
			break;
		case 6:
			//Under
			doIn(a_color,  b_color, out_pResult);
			break;
		case 7:
			//Under
			doOut(a_color,  b_color, out_pResult);
			break;			
		case 8:
			//Mask
			doMask(a_color,  b_color, out_pResult);
			break;
		case 9:
			//Stencil
			doStencil(a_color,  b_color, out_pResult);
			break;
		case 10:
			//xor
			doXor(a_color,  b_color, out_pResult);
			break;
		case 11:
			//atop
			doAtop(a_color,  b_color, out_pResult);
			break;
		case 12:
			//Screen
			doScreen(a_color,  b_color, out_pResult);
			break;
		case 13:
			//Plus
			doPlus(a_color,  b_color, out_pResult);
			break;
		case 14:
			//Average
			average(a_color,  b_color, out_pResult);
			break;
		case 15:
			//Geometric
			doGeometric(a_color,  b_color, out_pResult);
			break;
		case 16:
			//Multiply
			multiply(a_color,  b_color, out_pResult);
			break;
		case 17:
			//Divide
			divide(a_color,  b_color, out_pResult);
			break;
		case 18:
			//Overlay
			overlay(a_color,  b_color, out_pResult);
			break;
		case 19:
			//Min
			doMin(a_color,  b_color, out_pResult);
			break;
		case 20:
			//Max
			doMax(a_color,  b_color, out_pResult);
			break;	
		case 21:
			//Color Dodge	
			doColorDodge(a_color,b_color,out_pResult);
			break;
		case 22:
			//Color Burn
			break;
		case 23:
			//Hard light	
			break;
		case 24:
			//Soft Light
			break;
		case 25:
			//Minus
			doMinus(a_color,  b_color, out_pResult);
			break;
		case 26:
			//From
			doFrom(a_color,  b_color, out_pResult);
			break;
		case 27:
			//Difference
			doDifference(a_color,  b_color, out_pResult);
			break;
		case 28:
			//Exclusion
			doExclusion(a_color,  b_color, out_pResult);
			break;
		default:
			return miFALSE;
		break;
	}
	return miTRUE;
	
}
