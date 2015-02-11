#version 120

varying vec2 ex_TexMap;
//varying vec3 ex_Pos;

uniform sampler2D tex;

void main(void) {
	vec4 map=texture2D( tex, ex_TexMap );
	if(map.a<0.2) discard;	
	gl_FragColor=vec4(map.xyz,map.a);
}
