#ifndef MYMRWATERMELON_H_
#define MYMRWATERMELON_H_

#endif /*MYMRWATERMELON_H_*/

struct MYMRWatermelon_o{
	miColor result;
	miColor diffuse_result;
	miColor spec_result;
	miColor refl_result;
};

struct MYMRWatermelon_p{
	miColor ambient;
	miColor diffuse;
	miColor specular;
	miScalar specular_exponent;
	miColor reflection;
	miScalar reflection_factor;
	miColor refraction;
	miScalar refraction_factor;
	miScalar ior;

};