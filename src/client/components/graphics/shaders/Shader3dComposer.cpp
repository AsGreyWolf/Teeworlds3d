#include "Shader3dComposer.h"

#include <client/components/Camera.h>
#include <client/components/Graphics.h>
#include <client/components/graphics/shaders/Shader3d.h>
#include <client/components/graphics/shaders/ShaderShadow.h>
#include <string>

Shader3dComposer *pShader3dComposer;
Shader3dComposer *g_Shader3dComposer() {
	return pShader3dComposer ? pShader3dComposer : new Shader3dComposer();
}

Shader3dComposer::Shader3dComposer()
    : ShaderTexture::ShaderTexture(
          "shaders/shader3dcomposer", g_Graphics()->screenSize,
          {"colorMap", "positionMap", "normalMap", "shadowMap"},
          {g_Shader3d()->color, g_Shader3d()->position, g_Shader3d()->normal,
           g_ShaderShadow()->shadowMap}) {
	pShader3dComposer = this;
}
Shader3dComposer::~Shader3dComposer() { pShader3dComposer = nullptr; }
void Shader3dComposer::Render() {
	glUseProgram(*this);
	static Uniform<glm::mat4> spMatrix(*this, "shadowProjectionMatrix");
	spMatrix.Set(g_ShaderShadow()->matrix);
	static Uniform<glm::vec3> camera(*this, "camera");
	camera.Set(g_Camera()->pos);
	ShaderTexture::Render();
}
