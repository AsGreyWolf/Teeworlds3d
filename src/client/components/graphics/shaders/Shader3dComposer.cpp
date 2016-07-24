#include "Shader3dComposer.h"

#include <client/components/Camera.h>
#include <client/components/Graphics.h>
#include <client/components/graphics/shaders/Shader3d.h>
#include <client/components/graphics/shaders/ShaderShadow.h>
#include <string>

Shader3dComposer *pShader3dComposer;
Shader3dComposer *g_Shader3dComposer() { return pShader3dComposer ? pShader3dComposer : new Shader3dComposer(); }

static std::vector<std::string> getUniformList() {
	std::vector<std::string> v;
	v.push_back("colorMap");
	v.push_back("positionMap");
	v.push_back("normalMap");
	v.push_back("shadowMap");
	return v;
}
static std::vector<Texture> getTextureList() {
	std::vector<Texture> v;
	v.push_back(g_Shader3d()->color);
	v.push_back(g_Shader3d()->position);
	v.push_back(g_Shader3d()->normal);
	v.push_back(g_ShaderShadow()->shadowMap);
	return v;
}

Shader3dComposer::Shader3dComposer()
    : ShaderTexture::ShaderTexture(std::string("shaders/shader3dcomposer"), g_Graphics()->screenSize, getUniformList(), getTextureList()) {
	pShader3dComposer = this;
	shadowProjectionMatrixUniform = glGetUniformLocation(*this, "shadowProjectionMatrix");
	cameraUniform = glGetUniformLocation(*this, "camera");
}
Shader3dComposer::~Shader3dComposer() {
	pShader3dComposer = 0;
}
void Shader3dComposer::Render() {
	glUseProgram(*this);
	glUniformMatrix4fv(shadowProjectionMatrixUniform, 1, GL_FALSE,
				   (const float *)glm::value_ptr(g_ShaderShadow()->matrix));
	glUniform3fv(cameraUniform, 1,
				   (const float *)glm::value_ptr(g_Camera()->pos));
	ShaderTexture::Render();
}
