#include "ShaderTexture.h"

#include <client/components/graphics/geometry/Primitives.h>
#include <string>

unsigned static int bufferList[] = {GL_COLOR_ATTACHMENT0};

template<typename T>
std::vector<T> make_vector(const T &a) {
	std::vector<T> v;
	v.push_back(a);
	return v;
}
ShaderTexture::ShaderTexture(const std::string &file, const glm::uvec2 &size, const std::string &uniform, const Texture &texture)
             : ShaderTexture(file, size, make_vector(uniform), make_vector(texture)) {}
ShaderTexture::ShaderTexture(const std::string &file, const glm::uvec2 &size, const std::vector<std::string> &uniforms, const std::vector<Texture> &textures)
    : Shader::Shader(file, size,
                     GL_BACK, GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE,
                     0) {
	GLuint id = *this;

	glBindAttribLocation(id, SHADER_POS, "in_Position");
	glBindAttribLocation(id, SHADER_TEXMAP, "in_TexMap");

	screen = Quad(quad2(-1, -1, 2, 2), quad2(0, 1, 1, -1));
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &vbuffer);
	glGenBuffers(1, &tbuffer);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * screen.v.size() * 2,
				 &screen.v[0], GL_STATIC_DRAW);
	glVertexAttribPointer(SHADER_POS, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(SHADER_POS);
	glBindBuffer(GL_ARRAY_BUFFER, tbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * screen.t.size() * 2,
				 &screen.t[0], GL_STATIC_DRAW);
	glVertexAttribPointer(SHADER_TEXMAP, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(SHADER_TEXMAP);
	glBindVertexArray(0);

	colorTextures = textures;
	for (const std::string &s : uniforms) {
		colorUniforms.push_back(glGetUniformLocation(id, s.c_str()));
	}

	out = Texture(NULL, size.x, size.y, 0);
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glDrawBuffers(1, bufferList);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
							  GL_TEXTURE_2D, out, 0);
}
ShaderTexture::~ShaderTexture() {
	glDeleteBuffers(1, &vbuffer);
	glDeleteBuffers(1, &tbuffer);
	glDeleteVertexArrays(1, &VAO);
}
void ShaderTexture::Render() {
	glDisable(GL_DEPTH_TEST);
	Shader::Render();
	for (size_t i = 0; i < colorUniforms.size(); i++) {
		glUniform1i(colorUniforms[i], i);
		glActiveTexture(GL_TEXTURE0+i);
		colorTextures[i].Bind();
	}
	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, screen.v.size());
	glEnable(GL_DEPTH_TEST);
}
