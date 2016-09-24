in vec2 ex_TexMap;
out vec4 FragColor;

uniform vec4 colorer;
uniform sampler2D tex;
uniform float aspect;

void main(void) {
	vec4 map=texture( tex, ex_TexMap );
	if(map.a<0.2) discard;
	FragColor=dye(map, colorer);
}
