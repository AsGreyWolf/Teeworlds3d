#version 120

varying vec2 ex_TexMap;

uniform vec4 colorer;
uniform sampler2D tex;

void main(void) {
	vec4 map=texture2D( tex, ex_TexMap);
	/*vec2 dx=vec2(0.0009f,0.0f);
	vec2 dy=vec2(0.0f,0.0009f);
	map=texture2D( tex, ex_TexMap)+
	texture2D( tex, ex_TexMap+dx )+
	texture2D( tex, ex_TexMap-dx )+
	texture2D( tex, ex_TexMap+dy )+
	texture2D( tex, ex_TexMap-dy )+
	texture2D( tex, ex_TexMap+dx+dy )+
	texture2D( tex, ex_TexMap+dx-dy )+
	texture2D( tex, ex_TexMap-dx+dy )+
	texture2D( tex, ex_TexMap-dx-dy );
	map*=1.0f/9.0f;*/
	if(map.a<0.2) discard;
	gl_FragColor=map;
	if(colorer.a>0){
		float max=gl_FragColor.r+gl_FragColor.g+gl_FragColor.b;
		max/=3;
		gl_FragColor=vec4(max,max,max,gl_FragColor.a)*colorer;
	}
}
