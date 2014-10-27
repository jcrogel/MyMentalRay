/*
 *  MMR_AB_MonoChrome.h
 *  MyMMR_AB_MonoChrome
 *
 *  Created by Juan C Moreno on 3/21/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

typedef struct{
	miColor		InputColor;
	miScalar	RWeight;
	miScalar	GWeight;
	miScalar	BWeight;
	miScalar	Brightness;
} MMR_AB_MonoChrome_Params;

extern "C" {
	DLLEXPORT int MMR_AB_MonoChrome_version(void);

	DLLEXPORT miBoolean MMR_AB_MonoChrome( miColor *out_pResult, miState *state, 
			MMR_AB_MonoChrome_Params *in_pParams);

}
