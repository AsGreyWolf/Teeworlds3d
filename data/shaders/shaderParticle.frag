#version 120

varying float ex_logDepth;

uniform vec4 colorer;
uniform sampler2D tex;

void main(void) {
	if(gl_PointCoord.x<0.0 || gl_PointCoord.x>1.0 || gl_PointCoord.y<0.0 || gl_PointCoord.y>1.0)
		discard;
	vec4 map=texture2D(tex, gl_PointCoord);
	if(map.a<0.2) discard;
	gl_FragColor=map;
	if(colorer.a>0){
		float max=gl_FragColor.r+gl_FragColor.g+gl_FragColor.b;
		max/=3;
		gl_FragColor=vec4(max,max,max,gl_FragColor.a)*colorer;
	}
	else{
		gl_FragColor*=vec4(colorer.r,colorer.g,colorer.b,1.0);
	}
	gl_FragDepth = log2(ex_logDepth) / log2(10000 + 1.0);
}
