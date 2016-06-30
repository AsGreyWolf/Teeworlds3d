varying vec2 ex_TexMap;

uniform sampler2D texture;

vec4 blur(vec2 pos, vec2 v) {
	vec3 texel_radius = vec3(v.xy, 5);
	float INV_SQRT_2PI_X3 = 1.1968268412042980338198381798031;
	float r = texel_radius.z;
	float exp_value = -4.5 / r / r;
	float sqrt_value = INV_SQRT_2PI_X3 / r;
	float sum = 0.0;
	vec4 value = vec4(0,0,0,0);
	float x = 1.0;
	while (x <= r) {
		float currentScale = exp(exp_value * x * x);
		sum += currentScale;
		vec2 dudv = texel_radius.xy * x;
		value +=
		    currentScale * (texture2D(texture, pos - dudv) + texture2D(texture, pos + dudv));
		x += 1.0;
	}
	float correction = 1.0 / sqrt_value - 2.0 * sum;
	value += texture2D(texture, pos) * correction;
	return value * sqrt_value;
}

void main(void) {
	gl_FragColor = blur(ex_TexMap,vec2(0.001,0.0));
}
