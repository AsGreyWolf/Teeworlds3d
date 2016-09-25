#include "ShaderTexture.h"

#include <client/components/graphics/geometry/Primitives.h>
#include <string>

ShaderTexture::ShaderTexture(const std::string &file, const glm::uvec2 &size,
                             const std::string &uniform, const Texture &texture,
                             int flags)
    : ShaderTexture(file, size, {uniform}, std::vector<Texture>{texture},
                    flags) {}
ShaderTexture::ShaderTexture(const std::string &file, const glm::uvec2 &size,
                             const std::vector<std::string> &uniforms,
                             const std::vector<Texture> &textures, int flags)
    : Shader::Shader(file, size, GL_BACK, GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE,
                     GL_FALSE, 0) {
	SetAttribute("in_Position", SHADER_POS);
	SetAttribute("in_TexMap", SHADER_TEXMAP);

	screen = Quad(quad2(-1, -1, 2, 2), quad2(0, 1, 1, -1));
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &vbuffer);
	glGenBuffers(1, &tbuffer);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * screen.v.size() * 2,
	             screen.v.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(SHADER_POS, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(SHADER_POS);
	glBindBuffer(GL_ARRAY_BUFFER, tbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * screen.t.size() * 2,
	             screen.t.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(SHADER_TEXMAP, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(SHADER_TEXMAP);
	glBindVertexArray(0);

	colorTextures = textures;
	for (const std::string &uniform : uniforms)
		colorUniforms.push_back(Uniform<int>(*this, uniform));
	AddOutputTexture(out = Texture(nullptr, size, flags));
}
ShaderTexture::~ShaderTexture() {
	glDeleteBuffers(1, &vbuffer);
	glDeleteBuffers(1, &tbuffer);
	glDeleteVertexArrays(1, &VAO);
}
void ShaderTexture::Render() {
	glDisable(GL_DEPTH_TEST);
	Shader::Render();
	for (size_t i = 0; i < colorTextures.size(); i++) {
		colorUniforms[i].Set(i);
		glActiveTexture(GL_TEXTURE0 + i);
		colorTextures[i].Bind();
	}
	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, screen.v.size());
	glEnable(GL_DEPTH_TEST);
}
