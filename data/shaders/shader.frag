#version 120

varying vec2 ex_TexMap;
varying vec3 ex_Normal;
varying vec3 ex_ShadowTexMap;

uniform vec4 colorer;
uniform sampler2D tex;
uniform sampler2D shadow;
uniform float lighting;
float calcShadow(float z,vec2 pos,vec2 dx){
	vec4 shadowMap=texture(shadow, pos+dx);
	if (shadowMap.z-0.004f  <  z+0.02f){
		return 1.0f;
	}
	return 0.0f;
}
float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}
void main(void) {
	vec4 map=texture2D( tex, ex_TexMap );
	if(map.a<0.2) discard;
	
	gl_FragColor=map;
	if(lighting>0.5f){
		vec3 L=vec3(0,0,1);
		float lightIntensity =dot(ex_Normal, L)/2;
/* shadow calc
		if(ex_ShadowTexMap.x>=0.0f && ex_ShadowTexMap.x<=1.0f && ex_ShadowTexMap.y>=0.0f && ex_ShadowTexMap.y<=1.0f){
				vec2 shadowPos=ex_ShadowTexMap.xy+vec2(0.001f*rand(ex_ShadowTexMap.yx),0.001f*rand(ex_ShadowTexMap.xy));
				vec2 dx=vec2(0.0005f,0.0f);
				vec2 dy=vec2(0.0f,0.0005f);
				float shadowIntensity=calcShadow(ex_ShadowTexMap.z, shadowPos,dx);
				shadowIntensity+=calcShadow( ex_ShadowTexMap.z, shadowPos,-dx);
				shadowIntensity+=calcShadow( ex_ShadowTexMap.z, shadowPos,dy);
				shadowIntensity+=calcShadow( ex_ShadowTexMap.z, shadowPos,-dy);
				shadowIntensity+=calcShadow( ex_ShadowTexMap.z, shadowPos,dx+dy);
				shadowIntensity+=calcShadow( ex_ShadowTexMap.z, shadowPos,dx-dy);
				shadowIntensity+=calcShadow( ex_ShadowTexMap.z, shadowPos,-dx+dy);
				shadowIntensity+=calcShadow( ex_ShadowTexMap.z, shadowPos,-dx-dy);
				shadowIntensity*=0.125f;
				lightIntensity -= 0.25f*shadowIntensity;
		}*/
		lightIntensity=max(lightIntensity, 0.0f);
		gl_FragColor*=vec4(vec3(lightIntensity+0.5f),1.0f);
	}
	if(colorer.a>0){
		float max=gl_FragColor.r+gl_FragColor.g+gl_FragColor.b;
		max/=3;
		gl_FragColor=vec4(max,max,max,gl_FragColor.a)*colorer;
	}
}
