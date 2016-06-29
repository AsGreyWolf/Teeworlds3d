varying vec2 ex_TexMap;

uniform sampler2D colorMap;
uniform sampler2D positionMap;
uniform sampler2D normalMap;
uniform sampler2D depthMap;
uniform sampler2D shadowMap;
uniform mat4 shadowProjectionMatrix;

vec3 L = vec3(0, 0, 1);

float calcShadow(float z, vec2 pos) {
	vec4 shadowMap = texture2D(shadowMap, pos);
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

float outline(float depth, vec3 norm, vec2 dx){
	if(dot(norm,texture2D(normalMap, ex_TexMap+dx).rgb)<0.7 || abs(depth-pow(10001,texture2D(depthMap, ex_TexMap+dx).r-1.0))>0.1)
		return 1.0;
	return 0.0;
}

void main(void) {
	vec4 color = texture2D(colorMap, ex_TexMap);
	vec3 normal = texture2D(normalMap, ex_TexMap).rgb;
	vec4 position = vec4(texture2D(positionMap, ex_TexMap).rgb,1.0);
	float depth = pow(10001,texture2D(depthMap, ex_TexMap).r-1.0);
	float dd=1.0/1000.0;
	if(outline(depth,normal,vec2(0,dd))+outline(depth,normal,vec2(0,-dd))+outline(depth,normal,vec2(dd,0))+outline(depth,normal,vec2(-dd,0))>0.5)
		color.rgb=vec3(0,0,0);
	{
		float lightIntensity = (dot(normal, L));
		/* shadow calc*/
		vec4 shadowmap = shadowProjectionMatrix * position;
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
		color *= vec4(vec3(lightIntensity * 0.25 + 0.5), 1.0); // diffuse & ambient
		color += vec4(vec3(lightIntensity * 0.25), 0.0); // discoloration
	}
	gl_FragColor = color;
}
