/*
 *  FirstShader.h
 *  MyFirstShader
 *
 *  Created by Juan C Moreno on 3/21/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

typedef struct{
	miColor		BaseColor;
	miColor		BackColor;
	miInteger	Value;
} FirstShader_Params;

extern "C" {
	DLLEXPORT int FirstShader_version(void);

	DLLEXPORT miBoolean FirstShader( miColor *out_pResult, miState *state, 
			FirstShader_Params *in_pParams);

}
