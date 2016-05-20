#version 120
attribute vec3 in_Position;

varying float ex_logDepth;

uniform mat4 viewProjectionMatrix;
uniform mat4 modelMatrix;

void main(void) {
	gl_Position=viewProjectionMatrix*modelMatrix*vec4(in_Position, 1.0);
	
	ex_logDepth = 1.0 + gl_Position.w;
    gl_Position.z = log2(max(1e-6, 1.0 + gl_Position.w)) * 2.0 / log2(10000.0 + 1.0) - 1.0;
}
