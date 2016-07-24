attribute vec3 in_Position;
attribute vec2 in_TexMap;
attribute vec3 in_Normal;

varying vec4 ex_WorldPosition;
varying vec2 ex_TexMap;
varying vec3 ex_Normal;
varying float ex_logDepth;

uniform mat4 viewProjectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;

void main(void) {
	ex_WorldPosition = modelMatrix * vec4(in_Position, 1.0);
	gl_Position = viewProjectionMatrix * ex_WorldPosition;
	ex_TexMap = in_TexMap;
	ex_Normal = normalize((normalMatrix * vec4(in_Normal, 1.0)).xyz);

	ex_logDepth = wrapDepth(gl_Position);
	gl_Position.z = wrapZ(ex_logDepth, 10000.0);
}
