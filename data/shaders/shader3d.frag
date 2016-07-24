varying vec4 ex_WorldPosition;
varying vec2 ex_TexMap;
varying vec3 ex_Normal;
varying float ex_logDepth;

uniform vec4 colorer;
uniform float lighting;
uniform sampler2D tex;

void main(void) {
	vec4 map = texture2D(tex, ex_TexMap);
	if (map.a < 0.2)
		discard;
	gl_FragDepth = unwrapDepth(ex_logDepth, 10000.0);
	gl_FragData[2] = vec4(ex_Normal, 1.0);
	gl_FragData[1] = vec4(ex_WorldPosition.xyz/ex_WorldPosition.w, 1.0);
	gl_FragData[0] = dye(map, colorer);
}
