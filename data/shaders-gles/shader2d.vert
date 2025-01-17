in vec2 in_Position;
in vec2 in_TexMap;

out vec2 ex_TexMap;

uniform vec3 pos;
uniform float aspect;

void main(void) {
	gl_Position=vec4(in_Position+pos.xy,pos.z, 1.0);
	gl_Position.x/=aspect;
	ex_TexMap = in_TexMap;
}
