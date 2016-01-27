#include "BufferedModel.h"

BufferedModel::BufferedModel(Model* modelv):Model(),model(modelv) {
}
BufferedModel::~BufferedModel() {
}
void BufferedModel::Render() {
	std::swap(model->modelMatrix,modelMatrix);
	std::swap(model->normalMatrix, normalMatrix);
	model->Render();
	std::swap(model->modelMatrix, modelMatrix);
	std::swap(model->normalMatrix, normalMatrix);
}