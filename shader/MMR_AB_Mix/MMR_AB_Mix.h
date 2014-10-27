/*
 *  MMR_AB_Mix.h
 *  MyMMR_AB_Mix
 *
 *  Created by Juan C Moreno on 3/21/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

typedef struct{
	miColor		AColor;
	miColor		BColor;
	miInteger	Mode;
} MMR_AB_Mix_Params;

extern "C" {
	DLLEXPORT int MMR_AB_Mix_version(void);

	DLLEXPORT miBoolean MMR_AB_Mix( miColor *out_pResult, miState *state, 
			MMR_AB_Mix_Params *in_pParams);
	
}

void doScreen(miColor *a_color,  miColor *b_color, miColor *out_pResult);
void divide(miColor *a_color,  miColor *b_color, miColor *out_pResult);
void multiply(miColor *a_color,  miColor *b_color, miColor *out_pResult);
void average(miColor *a_color,  miColor *b_color, miColor *out_pResult);
void doOver(miColor *a_color,  miColor *b_color, miColor *out_pResult);
void doUnder(miColor *a_color,  miColor *b_color, miColor *out_pResult);
void doCopy(miColor *a_color,  miColor *b_color, miColor *out_pResult);
void doMask(miColor *a_color,  miColor *b_color, miColor *out_pResult);
void doPlus(miColor *a_color,  miColor *b_color, miColor *out_pResult);
void doMinus(miColor *a_color,  miColor *b_color, miColor *out_pResult);
void doFrom(miColor *a_color,  miColor *b_color, miColor *out_pResult);
void doIn(miColor *a_color,  miColor *b_color, miColor *out_pResult);
void doOut(miColor *a_color,  miColor *b_color, miColor *out_pResult);
void doDifference(miColor *a_color,  miColor *b_color, miColor *out_pResult);
void doMin(miColor *a_color,  miColor *b_color, miColor *out_pResult);
void doMax(miColor *a_color,  miColor *b_color, miColor *out_pResult);
void doExclusion(miColor *a_color,  miColor *b_color, miColor *out_pResult);
void doMatte(miColor *a_color,  miColor *b_color, miColor *out_pResult);
void doDisjointOver(miColor *a_color,  miColor *b_color, miColor *out_pResult);
void doConjointOver(miColor *a_color,  miColor *b_color, miColor *out_pResult);
void doStencil(miColor *a_color,  miColor *b_color, miColor *out_pResult);
void doXor(miColor *a_color,  miColor *b_color, miColor *out_pResult);
void doAtop(miColor *a_color,  miColor *b_color, miColor *out_pResult);
void doGeometric(miColor *a_color,  miColor *b_color, miColor *out_pResult);
