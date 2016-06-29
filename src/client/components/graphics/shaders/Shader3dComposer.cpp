#include "Shader3dComposer.h"

#include <client/components/Graphics.h>
#include <client/components/graphics/shaders/Shader3d.h>
#include <client/components/graphics/shaders/ShaderShadow.h>
#include <client/components/graphics/geometry/Geometry2d.h>
#include <client/components/graphics/geometry/Primitives.h>
#include <string>

Geometry2d screen;
GLuint vao,vbuffer,tbuffer;

Shader3dComposer *pShader3dComposer;
Shader3dComposer *g_Shader3dComposer() { return pShader3dComposer ? pShader3dComposer : new Shader3dComposer(); }

Shader3dComposer::Shader3dComposer()
    : Shader::Shader(std::string("shaders/shader3dcomposer"), g_Graphics()->screenSize,
                     GL_BACK, GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE,
                     GL_DEPTH_BUFFER_BIT) {
	pShader3dComposer = this;

	GLuint id = *this;

	glBindAttribLocation(id, SHADER_POS, "in_Position");
	glBindAttribLocation(id, SHADER_TEXMAP, "in_TexMap");

	colorUniform = glGetUniformLocation(id, "colorMap");
	positionUniform = glGetUniformLocation(id, "positionMap");
	normalUniform = glGetUniformLocation(id, "normalMap");
	depthUniform = glGetUniformLocation(id, "depthMap");
	shadowUniform = glGetUniformLocation(id, "shadowMap");
	shadowProjectionMatrixUniform = glGetUniformLocation(id, "shadowProjectionMatrix");

	screen = Quad(quad2(-1, -1, 2, 2), quad2(0, 1, 1, -1));

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbuffer);
	glGenBuffers(1, &tbuffer);
	glBindVertexArray(vao);
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
}
Shader3dComposer::~Shader3dComposer() {
	glDeleteBuffers(1, &vbuffer);
	glDeleteBuffers(1, &tbuffer);
	glDeleteVertexArrays(1, &vao);
	pShader3dComposer = 0;
}
void Shader3dComposer::Render() {
	Shader::Render();
	glUniformMatrix4fv(shadowProjectionMatrixUniform, 1, GL_FALSE,
	                   (const float *)glm::value_ptr(g_ShaderShadow()->matrix));
	glUniform1i(shadowUniform, 4);
	glActiveTexture(GL_TEXTURE4);
	g_ShaderShadow()->shadowMap.Bind();
	glUniform1i(depthUniform, 3);
	glActiveTexture(GL_TEXTURE3);
	g_Shader3d()->depth.Bind();
	glUniform1i(normalUniform, 2);
	glActiveTexture(GL_TEXTURE2);
	g_Shader3d()->normal.Bind();
	glUniform1i(positionUniform, 1);
	glActiveTexture(GL_TEXTURE1);
	g_Shader3d()->position.Bind();
	glUniform1i(colorUniform, 0);
	glActiveTexture(GL_TEXTURE0);
	g_Shader3d()->color.Bind();

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, screen.v.size());
}
