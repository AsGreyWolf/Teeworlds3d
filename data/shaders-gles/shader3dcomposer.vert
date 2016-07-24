in vec2 in_Position;
in vec2 in_TexMap;

out vec2 ex_TexMap;

void main(void) {
	gl_Position = vec4(in_Position, 0.0, 1.0);
  ex_TexMap = in_TexMap;
}
