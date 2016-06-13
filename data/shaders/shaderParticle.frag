varying float ex_logDepth;
varying float ex_size;

uniform vec4 colorer;
uniform sampler2D tex;

void main(void) {
	vec4 map = texture2D(tex, gl_PointCoord.st);
	if (map.a < 0.2)
		discard;
	gl_FragColor = dye(map, colorer);
	vec2 pos = gl_PointCoord.st * 2.0 - vec2(1, 1);
	gl_FragDepth = unwrapDepth(
	    ex_logDepth -
	        sqrt(max(0.0, 1.0 - pos.x * pos.x - pos.y * pos.y)) * ex_size / 16,
	    10000);
}
