in vec4 ex_WorldPosition;
in vec2 ex_TexMap;
in vec3 ex_Normal;
//in float ex_logDepth;

layout(location=0) out vec4 color;
layout(location=1) out vec4 position;
layout(location=2) out vec4 normal;

uniform vec4 colorer;
uniform float lighting;
uniform sampler2D tex;

void main(void) {
	vec4 map = texture(tex, ex_TexMap);
	if (map.a < 0.2)
		discard;
	//gl_FragDepth = unwrapDepth(ex_logDepth, 10000.0);
	normal = vec4(ex_Normal * lighting, 1.0);
	position = vec4(ex_WorldPosition.xyz/ex_WorldPosition.w, 1.0);
	color = dye(map, colorer);
}
