#include "Model.h"

Model::Model() = default;
Model::Model(const Model &second) {}
Model::~Model() = default;
void Model::Render() {}
void Model::Enable() { enabled = true; }
void Model::Disable() { enabled = false; }
