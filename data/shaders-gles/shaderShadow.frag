in vec2 ex_TexMap;
out vec4 FragColor;

uniform sampler2D tex;

void main(void) {
	vec4 map = texture(tex, ex_TexMap);
	if (map.a < 0.2)
		discard;
	FragColor = vec4(map.xyz, map.a);
}
