#ifndef MYMR_AMBIENTOCCLUSION_H_
#define MYMR_AMBIENTOCCLUSION_H_

#endif /*MYMR_AMBIENTOCCLUSION_H_*/

struct MYMR_AmbientOcclusion_p{
	miUint samples;
};

extern "C" {
	DLLEXPORT int MYMR_AmbientOcclusion_version(void);

	DLLEXPORT miBoolean MYMR_AmbientOcclusion( miColor *, miState *, 
			struct MYMR_AmbientOcclusion_p *);
	
}