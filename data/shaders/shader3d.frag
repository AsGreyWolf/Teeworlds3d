varying vec4 ex_WorldPosition;
varying vec2 ex_TexMap;
varying vec3 ex_Normal;
varying float ex_logDepth;

uniform mat4 shadowProjectionMatrix;
uniform vec4 colorer;
uniform float lighting;
uniform sampler2D tex;
uniform sampler2D shadow;

vec3 L = vec3(0, 0, 1);

float calcShadow(float z, vec2 pos) {
	vec4 shadowMap = texture2D(shadow, pos);
	if (shadowMap.z + 0.0001 < z) {
		return 1.0;
	}
	return 0.0;
}
float blurShadow(float z, vec2 pos, vec2 v) {
	vec3 texel_radius = vec3(v.xy, 5);
	float INV_SQRT_2PI_X3 = 1.1968268412042980338198381798031;
	float r = texel_radius.z;
	float exp_value = -4.5 / r / r;
	float sqrt_value = INV_SQRT_2PI_X3 / r;
	float sum = 0.0;
	float value = 0;
	float x = 1.0;
	while (x <= r) {
		float currentScale = exp(exp_value * x * x);
		sum += currentScale;
		vec2 dudv = texel_radius.xy * x;
		value +=
		    currentScale * (calcShadow(z, pos - dudv) + calcShadow(z, pos + dudv));
		x += 1.0;
	}
	float correction = 1.0 / sqrt_value - 2.0 * sum;
	value += calcShadow(z, pos) * correction;
	return value * sqrt_value;
}
void main(void) {
	vec4 map = texture2D(tex, ex_TexMap);
	if (map.a < 0.2)
		discard;
	gl_FragData[0] = map;
	if (lighting > 0.5f) {
		float lightIntensity = (dot(ex_Normal, L));
		/* shadow calc*/
		vec4 shadowmap = shadowProjectionMatrix * ex_WorldPosition;
		shadowmap.x = shadowmap.x / (abs(shadowmap.x) + 0.3);
		shadowmap.y = shadowmap.y / (abs(shadowmap.y) + 0.3);
		shadowmap = biasMatrix * shadowmap;
		shadowmap /= shadowmap.w;
		if (shadowmap.x >= 0.0 && shadowmap.x <= 1.0 && shadowmap.y >= 0.0 &&
		    shadowmap.y <= 1.0) {
			float shadowIntensity =
			    blurShadow(shadowmap.z, shadowmap.xy, vec2(0.001, 0));
			shadowIntensity +=
			    blurShadow(shadowmap.z, shadowmap.xy, vec2(0.0007, 0.0007));
			shadowIntensity +=
			    blurShadow(shadowmap.z, shadowmap.xy, vec2(0.0007, -0.0007));
			lightIntensity -= 2.5 * shadowIntensity / 3;
		}
		lightIntensity = clamp(lightIntensity, 0.0, 1.0);
		gl_FragData[0] *= vec4(vec3(lightIntensity * 0.25 + 0.5), 1.0);
		gl_FragData[0] += vec4(vec3(lightIntensity * 0.25), 0.0);
	}
	gl_FragData[0] = dye(gl_FragData[0], colorer);
	gl_FragData[1] = gl_FragData[0];
	gl_FragDepth = unwrapDepth(ex_logDepth, 10000);
}
