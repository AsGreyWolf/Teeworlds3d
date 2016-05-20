#include "Shader.h"

#include <shared/Console.h>
#include <shared/System.h>

char *filetobuf(std::string file) {
	FILE *fptr;
	long length;
	char *buf;
	fptr = fopen(file.c_str(), "rb");
	if (!fptr)
		return NULL;
	fseek(fptr, 0, SEEK_END);
	length = ftell(fptr);
	buf = new char[length + 1];
	fseek(fptr, 0, SEEK_SET);
	fread(buf, length, 1, fptr);
	fclose(fptr);
	buf[length] = 0;

	return buf;
}
Shader::Shader(const std::string &filepath, glm::vec2 viewport, GLenum culling,
               GLboolean colormask0, GLboolean colormask1, GLboolean colormask2,
               GLboolean colormask3, GLboolean depthmask, GLbitfield clear) {
	registred.push_back(this);

	this->culling = culling;
	this->colormask[0] = colormask0;
	this->colormask[1] = colormask1;
	this->colormask[2] = colormask2;
	this->colormask[3] = colormask3;
	this->depthmask = depthmask;
	this->clear = clear;
	this->viewport = viewport;

	std::string firstpath = g_System()->GetDataFile(filepath);

	GLchar *vertexsource, *fragmentsource, *geometrysource;
	GLuint vertexshader, fragmentshader, geometryshader;
	int IsCompiled_VS, IsCompiled_FS, IsCompiled_GS;
	int IsLinked;
	int maxLength;
	char *vertexInfoLog;
	char *fragmentInfoLog;
	char *geometryInfoLog;
	char *shaderProgramInfoLog;
	std::string path = firstpath;
	path.append(".vert");
	vertexsource = filetobuf(path);
	path = firstpath;
	path.append(".frag");
	fragmentsource = filetobuf(path);
	path = firstpath;
	path.append(".geom");
	geometrysource = filetobuf(path);

	vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, (const GLchar **)&vertexsource, 0);
	glCompileShader(vertexshader);
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &IsCompiled_VS);
	if (IsCompiled_VS == GL_FALSE) {
		glGetShaderiv(vertexshader, GL_INFO_LOG_LENGTH, &maxLength);
		vertexInfoLog = new char[maxLength];
		glGetShaderInfoLog(vertexshader, maxLength, &maxLength, vertexInfoLog);
		g_Console()->Err(std::string(vertexInfoLog));
		delete[] vertexInfoLog;
	}

	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, (const GLchar **)&fragmentsource, 0);
	glCompileShader(fragmentshader);
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &IsCompiled_FS);
	if (IsCompiled_FS == GL_FALSE) {
		glGetShaderiv(fragmentshader, GL_INFO_LOG_LENGTH, &maxLength);
		fragmentInfoLog = new char[maxLength];
		glGetShaderInfoLog(fragmentshader, maxLength, &maxLength, fragmentInfoLog);
		g_Console()->Err(std::string(fragmentInfoLog));
		delete[] fragmentInfoLog;
	}

	if (geometrysource != NULL) {
		geometryshader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryshader, 1, (const GLchar **)&geometrysource, 0);
		glCompileShader(geometryshader);
		glGetShaderiv(geometryshader, GL_COMPILE_STATUS, &IsCompiled_GS);
		if (IsCompiled_GS == GL_FALSE) {
			glGetShaderiv(geometryshader, GL_INFO_LOG_LENGTH, &maxLength);
			geometryInfoLog = new char[maxLength];
			glGetShaderInfoLog(geometryshader, maxLength, &maxLength, geometryInfoLog);
			g_Console()->Err(std::string(geometryInfoLog));
			delete[] geometryInfoLog;
		}
	}

	id = glCreateProgram();
	glAttachShader(id, vertexshader);
	glAttachShader(id, fragmentshader);
	if (geometrysource != NULL)
		glAttachShader(id, geometryshader);
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, (int *)&IsLinked);
	if (IsLinked == GL_FALSE) {
		id = 0;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);
		shaderProgramInfoLog = new char[maxLength];
		glGetProgramInfoLog(id, maxLength, &maxLength, shaderProgramInfoLog);
		g_Console()->Err(std::string(shaderProgramInfoLog));
		delete[] shaderProgramInfoLog;
	}
	delete[] vertexsource;
	delete[] fragmentsource;
	if (geometrysource != NULL)
		delete[] geometrysource;
	g_Console()->Info("Shader loaded " + filepath);
}
Shader::~Shader() {
	glDeleteProgram(id);
	id = 0;
	registredModels.clear();
	registred.remove(this);
}
void Shader::RegisterModel(Model *model) { registredModels.insert(model); }
void Shader::UnregisterModel(Model *model) { registredModels.erase(model); }
void Shader::Render() {
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffer);
	glCullFace(culling);
	glColorMask(colormask[0], colormask[1], colormask[2], colormask[3]);
	glDepthMask(depthmask);
	glUseProgram(id);
	glViewport(0, 0, viewport.x, viewport.y);
	glClear(clear);
}
std::list<Shader *> Shader::registred;
void Shader::RenderShaders() {
	for (Shader *&shader : registred)
		shader->Render();
}
void Shader::ClearShaders() {
	while (!registred.empty())
		delete registred.back();
}
