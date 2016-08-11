in vec2 ex_TexMap;
out vec4 gl_FragColor;
uniform vec3 camera;
uniform sampler2D colorMap;
uniform sampler2D positionMap;
uniform sampler2D normalMap;
uniform sampler2D shadowMap;
uniform mat4 shadowProjectionMatrix;

vec3 L = vec3(0.0, 0.0, 1.0);

float calcShadow(float z, vec2 pos) {
	vec4 shadowMap = texture(shadowMap, pos)*65535.0;
	if (shadowMap.z + 0.0001 < z) {
		return 1.0;
	}
	return 0.0;
}
float blurShadow(float z, vec2 pos, vec2 v) {
	vec3 texel_radius = vec3(v.xy, 5.0);
	float INV_SQRT_2PI_X3 = 1.1968268412042980338198381798031;
	float r = texel_radius.z;
	float exp_value = -4.5 / r / r;
	float sqrt_value = INV_SQRT_2PI_X3 / r;
	float sum = 0.0;
	float value = 0.0;
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
bool validNormal(vec3 normal){
	return normal.x != 0.0 || normal.y != 0.0 || normal.z != 0.0;
}
float outline(vec4 color,vec3 norm,vec3 position, vec2 dx){
	vec3 norm2 = texture(normalMap, ex_TexMap+dx).rgb;
	if(!validNormal(norm) || !validNormal(norm2))
		return 0.0;
	vec3 deltaPosition = position-texture(positionMap, ex_TexMap+dx).rgb;
	if(dot(norm,norm2)<0.4 || dot(deltaPosition,deltaPosition)>10000.0*10000.0)
		return 1.0;
	vec4 color2=texture(colorMap, ex_TexMap+dx);
	if(abs(color2.r - color.r) + abs(color2.g - color.g) + abs(color2.b - color.b) + abs(color2.a - color.a) > 0.1)
		return 1.0;
	return 0.0;
}

void main(void) {
	vec4 color = texture(colorMap, ex_TexMap);
	vec3 normal = texture(normalMap, ex_TexMap).rgb;
	vec3 position = texture(positionMap, ex_TexMap).rgb;
	/* outline calc */
	float dd = 1.0 / 1000.0;
	float outl = outline(color,normal,position,vec2(0.0, dd)) + outline(color,normal,position,vec2(0.0, -dd)) + outline(color,normal,position,vec2(dd, 0.0)) + outline(color,normal,position,vec2(-dd, 0.0));
	vec3 deltaPosition = position - camera;
	float depth = sqrt(dot(deltaPosition,deltaPosition)/10000.0);
	if (outl > 0.5)
		color.rgb -= vec3(1.0,1.0,1.0)  / depth * 4.0 / outl;
	if (validNormal(normal))
	{
		float lightIntensity = (dot(normal, L));
		/* shadow calc*/
		// if (position.x != 0.0 && position.y != 0.0 && position.z != 0.0) {
		// 	vec4 shadowmap = shadowProjectionMatrix * vec4(position,1.0);
		// 	shadowmap.x = shadowmap.x / (abs(shadowmap.x) + 0.3);
		// 	shadowmap.y = shadowmap.y / (abs(shadowmap.y) + 0.3);
		// 	shadowmap = biasMatrix * shadowmap;
		// 	shadowmap /= shadowmap.w;
		// 	if (shadowmap.x >= 0.0 && shadowmap.x <= 1.0 && shadowmap.y >= 0.0 &&
		// 	    shadowmap.y <= 1.0) {
		// 		float shadowIntensity = blurShadow(shadowmap.z, shadowmap.xy, vec2(0.001, 0.0));
		// 		shadowIntensity += blurShadow(shadowmap.z, shadowmap.xy, vec2(0.0007, 0.0007));
		// 		shadowIntensity += blurShadow(shadowmap.z, shadowmap.xy, vec2(0.0007, -0.0007));
		// 		lightIntensity -= 2.5 * shadowIntensity / 3.0 ;
		// 	}
		// }
		lightIntensity = clamp(lightIntensity, 0.0, 1.0);
		color *= vec4(vec3(lightIntensity * 0.25 + 0.5), 1.0); // diffuse & ambient
		color += vec4(vec3(lightIntensity * 0.25), 0.0); // discoloration
	}
	gl_FragColor = color;
}
