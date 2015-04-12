#version 120
attribute vec3 in_Position;
attribute vec2 in_TexMap;

varying vec2 ex_TexMap;
//varying vec3 ex_Pos;

uniform mat4 viewProjectionMatrix;
uniform mat4 modelMatrix;

void main(void) {
	ex_TexMap = in_TexMap;
	gl_Position=modelMatrix*vec4(in_Position, 1.0);
	gl_Position.z*=0.00001;
	gl_Position=viewProjectionMatrix*gl_Position;
	gl_Position.x=gl_Position.x/(abs(gl_Position.x)+1);
	gl_Position.y=gl_Position.y/(abs(gl_Position.y)+1);
}
