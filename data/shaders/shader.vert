#version 130
in vec3 in_Position;
in vec2 in_TexMap;
in vec3 in_Normal;

out vec2 ex_TexMap;
out vec3 ex_Normal;

uniform mat4 viewProjectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;

void main(void) {
	gl_Position=viewProjectionMatrix*modelMatrix*vec4(in_Position, 1.0);
    ex_TexMap = in_TexMap;
	ex_Normal = normalize((normalMatrix*vec4(in_Normal, 1.0)).xyz);
}