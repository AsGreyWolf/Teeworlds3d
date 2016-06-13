#include "Shader.h"

#include <shared/Console.h>
#include <shared/System.h>
#include <fstream>
#include <vector>

std::string filetobuf(std::string file) {
	std::ifstream in(file);
	if (!in.good())
		return "";
	return std::string((std::istreambuf_iterator<char>(in)),
	                   std::istreambuf_iterator<char>());
}
void logShader(GLuint id) {
	int maxLength;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
	char *infoLog = new char[maxLength];
	glGetShaderInfoLog(id, maxLength, &maxLength, infoLog);
	g_Console()->Err(std::string(infoLog));
	delete[] infoLog;
}
void logProgram(GLuint id) {
	int maxLength;
	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);
	char *infoLog = new char[maxLength];
	glGetProgramInfoLog(id, maxLength, &maxLength, infoLog);
	g_Console()->Err(std::string(infoLog));
	delete[] infoLog;
}
bool endsWith(std::string const &fullString, std::string const &ending) {
	if (fullString.length() >= ending.length()) {
		return (0 ==
		        fullString.compare(fullString.length() - ending.length(),
		                           ending.length(), ending));
	} else {
		return false;
	}
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

	std::string vertexsource, fragmentsource, geometrysource, libraries = "\n";
	GLuint vertexshader, fragmentshader, geometryshader;
	int IsCompiled_VS, IsCompiled_FS, IsCompiled_GS;
	int IsLinked;
	vertexsource = filetobuf(firstpath + ".vert");
	fragmentsource = filetobuf(firstpath + ".frag");
	geometrysource = filetobuf(firstpath + ".geom");
	std::vector<std::string> libs;
	g_System()->GetFilesInDirectory(libs, g_System()->GetDataFile("shaders"));
	for (auto &s : libs) {
		s = "shaders/" + s;
		if (endsWith(s, ".slib")) {
			std::string libsource = filetobuf(g_System()->GetDataFile(s));
			if (libsource.length() == 0)
				continue;
			g_Console()->Info("Shader library loaded " + s);
			libraries += libsource + "\n";
		}
	}
	vertexsource = libraries + vertexsource;
	fragmentsource = libraries + fragmentsource;
	if (geometrysource.length() > 0)
		geometrysource = libraries + geometrysource;

	vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, (const GLchar **)&vertexsource, 0);
	glCompileShader(vertexshader);
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &IsCompiled_VS);
	if (IsCompiled_VS == GL_FALSE) {
		logShader(vertexshader);
		return;
	}

	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, (const GLchar **)&fragmentsource, 0);
	glCompileShader(fragmentshader);
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &IsCompiled_FS);
	if (IsCompiled_FS == GL_FALSE) {
		logShader(fragmentshader);
		return;
	}

	if (geometrysource.length() > 0) {
		geometryshader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryshader, 1, (const GLchar **)&geometrysource, 0);
		glCompileShader(geometryshader);
		glGetShaderiv(geometryshader, GL_COMPILE_STATUS, &IsCompiled_GS);
		if (IsCompiled_GS == GL_FALSE) {
			logShader(geometryshader);
			return;
		}
	}

	id = glCreateProgram();
	glAttachShader(id, vertexshader);
	glAttachShader(id, fragmentshader);
	if (geometrysource.length() > 0)
		glAttachShader(id, geometryshader);
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, (int *)&IsLinked);
	if (IsLinked == GL_FALSE) {
		logProgram(id);
		id = 0;
		return;
	}
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
