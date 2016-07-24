attribute vec3 in_Position;

varying float ex_logDepth;
varying float ex_size;

uniform mat4 viewProjectionMatrix;
uniform mat4 modelMatrix;
uniform vec3 vel;
uniform float size;
uniform float gravity;
uniform float ttl;
uniform int time;

void main(void) {
	float t = time + ttl * rand(in_Position.xy);
	float f = t - floor(t / ttl) * ttl;
	f/=1000.0;
	vec2 rr =
	    normalize(vec2(rand(in_Position.zx) - 0.5, rand(in_Position.zy) - 0.5));
	gl_Position.xy = rr * vel.y * f;
	gl_Position.z = -gravity / 2.0 * f * f + vel.z * f;
	gl_Position.xyz *= 32.0;
	gl_Position.w = 1.0;
	gl_Position = viewProjectionMatrix * modelMatrix * gl_Position;

	ex_size = size * 10000.0 / 32.0 * (1.0 - gl_Position.z / gl_Position.w);
	gl_PointSize = ex_size;

	ex_logDepth = wrapDepth(gl_Position);
	gl_Position.z = wrapZ(ex_logDepth, 10000.0);
}
