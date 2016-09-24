#include "Model3d.h"

#include <client/components/Graphics.h>
#include <client/components/graphics/models/ShadowModel.h>
#include <client/components/graphics/shaders/Shader3d.h>

Model3d::Model3d(bool l, int t) : Model() {
	bufferedModelMatrix = glm::mat4(1.0f);
	bufferedPos = glm::vec3(0, 0, 0);
	bufferedRot = glm::vec3(0, 1, 0);
	bufferedParentMatrix = glm::mat4(1.0f);
	modelMatrix = glm::mat4(1.0f);
	normalMatrix = glm::transpose(glm::inverse(modelMatrix));
	light = l;
	type = t;
	data = make_dataPtr();
	pos = glm::vec3(0, 0, 0);
	rot = glm::vec3(0, 1, 0);
	color = glm::vec4(1, 1, 1, 0);
	scale = glm::vec3(1, 1, 1);
	g_Shader3d()->RegisterModel(this);
	if (light)
		shadow = new ShadowModel(*this);
	else
		shadow = NULL;
}
Model3d::Model3d(const Model3d &second) : Model(second) {
	bufferedModelMatrix = glm::mat4(1.0f);
	bufferedPos = glm::vec3(0, 0, 0);
	bufferedRot = glm::vec3(0, 1, 0);
	bufferedParentMatrix = glm::mat4(1.0f);
	modelMatrix = glm::mat4(1.0f);
	normalMatrix = glm::transpose(glm::inverse(modelMatrix));
	light = second.light;
	type = second.type;
	data = second.data;
	pos = second.pos;
	rot = second.rot;
	color = second.color;
	scale = second.scale;
	texture = second.texture;
	if (light)
		shadow = new ShadowModel(*this);
	else
		shadow = NULL;
	g_Shader3d()->RegisterModel(this);
}
Model3d &Model3d::operator=(const Model3d &second) {
	data.reset();
	light = second.light;
	type = second.type;
	data = second.data;
	pos = second.pos;
	rot = second.rot;
	color = second.color;
	scale = second.scale;
	texture = second.texture;
	if (light) {
		if (!shadow)
			shadow = new ShadowModel(*this);
		if (isEnabled())
			shadow->Enable();
		else
			shadow->Disable();
	} else if (shadow) {
		delete shadow;
		shadow = NULL;
	}
	return *this;
}
Model3d::~Model3d() {
	g_Shader3d()->UnregisterModel(this);
	if (shadow)
		delete shadow;
	data.reset();
}
void Model3d::Render() {
	texture.Bind();
	g_Shader3d()->SetLight(light);
	g_Shader3d()->SetColor(color);
	g_Shader3d()->SetMatrix(modelMatrix, normalMatrix);
	data->Render(type);
}
void Model3d::Enable() {
	Model::Enable();
	if (shadow)
		shadow->Enable();
}
void Model3d::Disable() {
	Model::Disable();
	if (shadow)
		shadow->Disable();
}
void Model3d::Add(const Geometry3d &geom) {
	*data += geom;
	data->Invalidate();
}
void Model3d::Clear() { data->Clear(); }
void Model3d::UpdateMatrix(const glm::mat4 &parentMatrix) {
	// position and rotation are buffered with matrix, don't calculate again if it
	// not set
	bool bufferedModelMatrixChanged = false;
	if (pos != bufferedPos || rot != bufferedRot) {
		bufferedModelMatrix = glm::translate(pos);
		bufferedModelMatrix =
		    glm::rotate(bufferedModelMatrix, rot.z, glm::vec3(0, 0, 1));
		bufferedModelMatrix =
		    glm::rotate(bufferedModelMatrix, rot.x, glm::vec3(1, 0, 0));
		bufferedModelMatrix =
		    glm::rotate(bufferedModelMatrix, rot.y, glm::vec3(0, 1, 0));
		bufferedModelMatrix = glm::scale(bufferedModelMatrix, scale);
		bufferedModelMatrixChanged = true;
	}
	// don't calculate model and normal matrix again if bufferedModelMatrix and
	// parentMatrix did not changed
	if (bufferedModelMatrixChanged || parentMatrix != bufferedParentMatrix) {
		modelMatrix = parentMatrix * bufferedModelMatrix;
		normalMatrix = glm::transpose(glm::inverse(modelMatrix));
		bufferedPos = pos;
		bufferedRot = rot;
		bufferedParentMatrix = parentMatrix;
	}
}
void Model3d::ScaleAt(const glm::vec3 &to, const glm::vec3 &basic,
                      const glm::vec3 &additional) {
	scale = additional * glm::length(to - pos) + basic;
}
Model3d::Data::Data() {
	g_Graphics(); // TODO: fix
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbuffer);
	glGenBuffers(1, &nbuffer);
	glGenBuffers(1, &tbuffer);
}
Model3d::Data::~Data() {
	g_Graphics(); // TODO: fix
	glDeleteBuffers(1, &vbuffer);
	glDeleteBuffers(1, &nbuffer);
	glDeleteBuffers(1, &tbuffer);
	glDeleteVertexArrays(1, &vao);
}
void Model3d::Data::Render(int type) {
	Validate();
	g_Graphics(); // TODO: fix
	glBindVertexArray(vao);
	glDrawArrays(type, 0, v.size());
}
void Model3d::Data::Invalidate() { valid = false; }
void Model3d::Data::Validate() {
	if (!valid) {
		g_Graphics(); // TODO: fix
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * v.size() * 3,
		             v.size() > 0 ? &v[0] : NULL, GL_STATIC_DRAW);
		glVertexAttribPointer(SHADER_POS, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(SHADER_POS);

		glBindBuffer(GL_ARRAY_BUFFER, tbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * t.size() * 2,
		             t.size() > 0 ? &t[0] : NULL, GL_STATIC_DRAW);
		glVertexAttribPointer(SHADER_TEXMAP, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(SHADER_TEXMAP);

		glBindBuffer(GL_ARRAY_BUFFER, nbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * n.size() * 3,
		             n.size() > 0 ? &n[0] : NULL, GL_STATIC_DRAW);
		glVertexAttribPointer(SHADER_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(SHADER_NORMAL);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	valid = true;
}
