#version 130
precision highp float;

in vec2 ex_TexMap;

uniform vec4 colorer;
uniform sampler2D tex;

void main(void) {
	vec4 map=texture2D( tex, ex_TexMap );
	if(map.a<0.2) discard;
	gl_FragColor=map;
	if(colorer.a>0){
		float max=gl_FragColor.r+gl_FragColor.g+gl_FragColor.b;
		max/=3;
		gl_FragColor=vec4(max,max,max,gl_FragColor.a)*colorer;
	}
}