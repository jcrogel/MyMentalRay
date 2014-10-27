#ifndef MYMR_ALLUMINUM_H_
#define MYMR_ALLUMINUM_H_

#endif /*MYMR_ALLUMINUM_H_*/

struct MYMR_Alluminum_o{
	miColor result;
	miColor diffuse_result;
	miColor spec_result;
	miColor refl_result;
};

struct MYMR_Alluminum_p{
	miColor ambient;
	miColor diffuse;
	miColor specular;
	miScalar specular_exponent;
	miColor reflection;
	miScalar reflection_factor;
	//miColor refraction;
	//miScalar refraction_factor;
	//miScalar ior;

};

extern "C" {
	DLLEXPORT int MYMR_Alluminum_version(void);

	DLLEXPORT miBoolean MYMR_Alluminum( struct MYMR_Alluminum_o *, miState *, 
			struct MYMR_Alluminum_p *);
	
}

void do_diffuse_and_spec(miColor *,miState *,miColor *, miColor *,miScalar );

void do_reflections(miColor *,miState *,miColor *, miScalar );

void do_refractions(miColor *,miState *, miColor *, miScalar );

void calculate_ior(miState *,miScalar );