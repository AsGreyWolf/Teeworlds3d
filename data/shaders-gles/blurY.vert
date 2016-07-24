attribute vec2 in_Position;
attribute vec2 in_TexMap;

varying vec2 ex_TexMap;

void main(void) {
	ex_TexMap = in_TexMap;
	gl_Position = vec4(in_Position, 0.0, 1.0);
}
