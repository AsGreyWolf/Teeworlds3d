#version 120

varying vec2 ex_TexMap;
varying vec3 ex_Normal;
varying vec3 ex_ShadowTexMap;
varying float ex_logDepth;

uniform vec4 colorer;
uniform sampler2D tex;
uniform sampler2D shadow;
uniform float lighting;

float calcShadow(float z,vec2 pos,vec2 dx){
	vec4 shadowMap=texture2D(shadow, pos+dx);
	if (shadowMap.z  <  z){
		return 1.0;
	}
	return 0.0;
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
/* shadow calc*/
		if(ex_ShadowTexMap.x>=0.0 && ex_ShadowTexMap.x<=1.0 && ex_ShadowTexMap.y>=0.0 && ex_ShadowTexMap.y<=1.0){
				float r=rand(ex_TexMap.xy);
				vec2 shadowPos=ex_ShadowTexMap.xy+0.0005*vec2(r,r);
				vec2 dx=vec2(0.0005*r,0.0);
				vec2 dy=vec2(0.0,0.0005*r);
				float shadowIntensity=calcShadow(ex_ShadowTexMap.z, shadowPos,dx);
				shadowIntensity+=calcShadow( ex_ShadowTexMap.z, shadowPos,-dx);
				shadowIntensity+=calcShadow( ex_ShadowTexMap.z, shadowPos,dy);
				shadowIntensity+=calcShadow( ex_ShadowTexMap.z, shadowPos,-dy);
				shadowIntensity+=calcShadow( ex_ShadowTexMap.z, shadowPos,dx+dy);
				shadowIntensity+=calcShadow( ex_ShadowTexMap.z, shadowPos,dx-dy);
				shadowIntensity+=calcShadow( ex_ShadowTexMap.z, shadowPos,-dx+dy);
				shadowIntensity+=calcShadow( ex_ShadowTexMap.z, shadowPos,-dx-dy);
				shadowIntensity*=0.125;
				lightIntensity -= 0.25f*shadowIntensity;
		}
		lightIntensity=min(1.0,max(lightIntensity, 0.0));
		//gl_FragColor*=vec4(vec3(lightIntensity*0.8),1.0);
		gl_FragColor*=vec4(vec3(lightIntensity*0.5+0.5),1.0);
		gl_FragColor+=vec4(vec3(lightIntensity*0.5),0.0);
	}
	if(colorer.a>0){
		float max=gl_FragColor.r+gl_FragColor.g+gl_FragColor.b;
		max/=3;
		gl_FragColor=vec4(max,max,max,gl_FragColor.a)*colorer;
	}
	gl_FragDepth = log2(ex_logDepth) / log2(10000 + 1.0);
}
