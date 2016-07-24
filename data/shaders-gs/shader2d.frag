varying vec2 ex_TexMap;

uniform vec4 colorer;
uniform sampler2D tex;

void main(void) {
	vec4 map=texture2D( tex, ex_TexMap );
	if(map.a<0.2) discard;
	gl_FragColor=dye(map, colorer);
}
