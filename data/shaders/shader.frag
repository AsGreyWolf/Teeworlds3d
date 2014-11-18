#version 130

precision highp float;

in vec2 ex_TexMap;
in vec3 ex_Normal;

uniform vec4 colorer;
uniform sampler2D tex;
uniform float lighting;

void main(void) {
	vec4 map=texture2D( tex, ex_TexMap );
	if(map.a<0.2) discard;	
	gl_FragColor=map;
	if(lighting>0.5f){
		vec3 L =vec3(0,0,1);
		float lightIntensity = max(dot(ex_Normal, L)/2, 0.0f);
		gl_FragColor*=vec4(vec3(lightIntensity+0.5f),1.0f);
	}
	if(colorer.a>0){
		float max=gl_FragColor.r+gl_FragColor.g+gl_FragColor.b;
		max/=3;
		gl_FragColor=vec4(max,max,max,gl_FragColor.a)*colorer;
	}
}