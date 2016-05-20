#include "ShadowModel.h"

#include <client/components/graphics/shaders/ShaderShadow.h>

Model3d::ShadowModel::ShadowModel(Model3d &p) : Model(), parent(&p) {
	g_ShaderShadow()->RegisterModel(this);
}
Model3d::ShadowModel::~ShadowModel() {
	g_ShaderShadow()->UnregisterModel(this);
	parent = NULL;
}
void Model3d::ShadowModel::Render() {
	parent->texture.Bind();
	g_ShaderShadow()->SetMatrix(parent->modelMatrix);
	parent->data->Render(parent->type);
}
