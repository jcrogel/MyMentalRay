
struct MYMR_Brick_p{
	miColor brickColor;
	miScalar brickWidth;
	miScalar brickHeight;
	miColor mortarColor;
	miScalar mortarThickness;
	miScalar grainFactor;
};

extern "C" {
	DLLEXPORT int MYMR_Brick_version(void);

	DLLEXPORT miBoolean MYMR_Brick_p( miColor *, miState *, 
			struct MYMR_Brick_p *);
	
}

void multiply(miColor *a_color,  miColor *b_color, miColor *out_pResult);

miColor * diffuse(miState * state);

miScalar smoothstep(miScalar a, miScalar b, miScalar x);

miScalar mod(miScalar a, miScalar b);

miScalar step(miScalar a, miScalar x);

miColor * mix( miColor * color0, miColor * color1, miScalar value , miColor * result);

miColor color_create(miScalar r, miScalar g,miScalar b);

miVector mymr_point_create(miScalar x, miScalar y, miScalar z);

miScalar brick_grain_noise(miState *state, miScalar factor);

miScalar remap(miScalar x, miScalar a1, miScalar b1, miScalar a2, miScalar b2);

miScalar mortar_grain_noise(miState *state, miScalar factor);

void brick_base_color(miColor *result, miColor *base,miState *state);