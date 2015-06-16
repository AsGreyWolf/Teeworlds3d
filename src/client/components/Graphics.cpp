#include "Graphics.h"
#include <vector>
#include <string>
#include <cstdio>
#include "../../shared/Console.h"
#include "../Client.h"
#include "Camera.h"
#include "graphics/PlayerModel.h"
#include "graphics/Model.h"
#include "graphics/Model2d.h"
#include "graphics/Resources.h"
#include "../../tools/Protocol.h"
#define USE_SHADOWS

class Graphics* pGraphics;
Graphics* g_Graphics(){ return pGraphics; }

int Graphics::to_pixels(float coord){
	return coord*screenSize/2;
}
float Graphics::to_screen(int pix){
	return pix*2.0f/screenSize;
}
void Graphics::to_RGBA(SDL_Surface* &src){
	if(src==NULL) return;
	SDL_Surface* ret=SDL_ConvertSurfaceFormat(src,SDL_PIXELFORMAT_ABGR8888,0);
	if(ret!=NULL){
		SDL_FreeSurface(src);
		src=ret;
	}
}
Graphics::Graphics() : Component(){
	pGraphics = this;
	SDL_GLContext context;

	if ((context = SDL_GL_CreateContext(g_Client()->screen)) == NULL)
	{

		Console::Err("Could not get context: " + string(SDL_GetError()));
		return; //TODO: exceptions
	}
	SDL_GL_SetSwapInterval(1);
	glewInit();
	Console::Info("Initialized OpenGL " + string((char*)glGetString(GL_VERSION)));
	int w=1024;
	int h=768;
	if( h == 0 )
	{
		h = 1;
	}
	screenSize=h;
	aspect=(float)w/h;
	screen=quad2(-1*aspect,-1,2*aspect,2);
	perspectiveMatrix=glm::perspective(1.0471975512f, aspect, 1.0f,10000.0f);
	orthoMatrix=glm::ortho(-320.0f,320.0f,-320.0f,320.0f,0.0f,1.0f);

	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(0, 0.75f, 1, 1);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glPolygonMode(GL_FRONT, GL_FILL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_FOG_HINT, GL_NICEST);
	glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);


	m_Resources=new Resources();
	m_Resources->Load();

	glBindAttribLocation(m_Resources->shader3d, SHADER_POS, "in_Position");
	glBindAttribLocation(m_Resources->shader3d, SHADER_TEXMAP, "in_TexMap");
	glBindAttribLocation(m_Resources->shader3d, SHADER_NORMAL, "in_Normal");

	glBindAttribLocation(m_Resources->shaderShadow, SHADER_POS, "in_Position");
	glBindAttribLocation(m_Resources->shaderShadow, SHADER_TEXMAP, "in_TexMap");

	glBindAttribLocation(m_Resources->shader2d, SHADER_POS, "in_Position");
	glBindAttribLocation(m_Resources->shader2d, SHADER_TEXMAP, "in_TexMap");

	colorUniform3d=glGetUniformLocation(m_Resources->shader3d,"colorer");
	lightUniform3d=glGetUniformLocation(m_Resources->shader3d,"lighting");
	viewProjectionMatrixUniform3d=glGetUniformLocation(m_Resources->shader3d,"viewProjectionMatrix");
	modelMatrixUniform3d=glGetUniformLocation(m_Resources->shader3d,"modelMatrix");
	normalMatrixUniform3d=glGetUniformLocation(m_Resources->shader3d,"normalMatrix");
	shadowProjectionMatrixUniform3d=glGetUniformLocation(m_Resources->shader3d,"shadowProjectionMatrix");

	modelMatrixUniformShadow = glGetUniformLocation(m_Resources->shaderShadow, "modelMatrix");
	viewProjectionMatrixUniformShadow=glGetUniformLocation(m_Resources->shaderShadow,"viewProjectionMatrix");

	colorUniform2d=glGetUniformLocation(m_Resources->shader2d,"colorer");
	aspectUniform2d=glGetUniformLocation(m_Resources->shader2d,"aspect");
	posUniform2d=glGetUniformLocation(m_Resources->shader2d,"pos");

	glLineWidth(3);
	glPointSize(3);
	//glPolygonOffset(-1, -1);

	glGenFramebuffersEXT(1, &shadowFBO);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, shadowFBO);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	//glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,GL_TEXTURE_2D,m_Resources->textureShadowColor,0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,GL_TEXTURE_2D,m_Resources->textureShadowDepth,0);
	SDL_SetRelativeMouseMode(SDL_TRUE);
}
Graphics::~Graphics(){
	m_Resources->UnLoad();
	glDeleteFramebuffers(1,&shadowFBO);
	delete m_Resources;
	pGraphics = NULL;
}
void Graphics::Input(unsigned char* keys,int xrel,int yrel,int wheel){}
void Graphics::Render(){}
void Graphics::RenderBillboard(){}
void Graphics::Render2d(){}
int currentShader;
void Graphics::Tick(){
#ifdef USE_SHADOWS
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, shadowFBO);
	glUseProgram(m_Resources->shaderShadow);
	currentShader = m_Resources->shaderShadow;
	glViewport(0,0,screenSize*aspect*4,screenSize*aspect*4);
	//glEnable(GL_POLYGON_OFFSET_FILL);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	vec3 pos = g_Camera()->position;
	pos.z=1;
	mat4 shadowMatrix=orthoMatrix*glm::lookAt(pos, pos+vec3(0,0,-1), vec3(0,1,0));
	glUniformMatrix4fv(viewProjectionMatrixUniformShadow,1,false,(const float*)glm::value_ptr(shadowMatrix));
	glCullFace(GL_FRONT);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDepthMask(GL_TRUE);
	g_Client()->Render();
#endif
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glCullFace(GL_BACK);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glUseProgram(m_Resources->shader3d);
	currentShader = m_Resources->shader3d;
	glViewport(0,0,screenSize*aspect,screenSize);
	glDisable(GL_POLYGON_OFFSET_FILL);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glUniform1i(glGetUniformLocation(m_Resources->shader3d,"tex"),0);
	glUniform1i(glGetUniformLocation(m_Resources->shader3d,"shadow"),1);
	g_Camera()->SetMatrix();
#ifdef USE_SHADOWS
	glUniformMatrix4fv(shadowProjectionMatrixUniform3d,1,false,(const float*)glm::value_ptr(shadowMatrix));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D,m_Resources->textureShadowDepth);
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	restoreMatrix=true;
#endif
	g_Client()->Render();
	restoreMatrix=false;
#ifdef USE_SHADOWS
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D,m_Resources->textureBlank);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
#endif

	glClear(GL_DEPTH_BUFFER_BIT);
	g_Client()->RenderBillboard();

	glUseProgram(m_Resources->shader2d);
	currentShader = m_Resources->shader2d;
	glClear(GL_DEPTH_BUFFER_BIT);
	glUniform1f(aspectUniform2d,aspect);
	g_Client()->Render2d();
}
void Graphics::Message(int type,char* value){}
void Graphics::StateChange(STATE lastState){}
void Graphics::SetColor(vec4 color){
	if (currentShader == m_Resources->shader3d)
	glUniform4f(colorUniform3d,color.r,color.g,color.b,color.a);
}
void Graphics::SetColor2d(vec4 color){
	glUniform4f(colorUniform2d,color.r,color.g,color.b,color.a);
}
void Graphics::SetLight(bool light){
	if (currentShader == m_Resources->shader3d)
	glUniform1f(lightUniform3d, light?1.0f:0.0f);
}
void Graphics::SetPos2d(vec2 pos, float depth){
	glUniform3f(posUniform2d, pos.x, pos.y, depth);
}
void Graphics::SetViewMatrix(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up){
	glUniformMatrix4fv(viewProjectionMatrixUniform3d,1,false,(const float*)glm::value_ptr(perspectiveMatrix*glm::lookAt(position, center, up)));
}
void Graphics::SetModelMatrix(glm::mat4 &modelMatrix,glm::mat4 &normalMatrix,const vec3 &position, const vec3 &rotation, const vec3 &size){
	if(!restoreMatrix){
		Transform(modelMatrix,position,rotation,size);

		normalMatrix=modelMatrix;
		normalMatrix=glm::inverse(normalMatrix);
		normalMatrix=glm::transpose(normalMatrix);
	}
	if (currentShader == m_Resources->shader3d){
		glUniformMatrix4fv(normalMatrixUniform3d, 1, false, (const float*)glm::value_ptr(normalMatrix));
		glUniformMatrix4fv(modelMatrixUniform3d, 1, false, (const float*)glm::value_ptr(modelMatrix));
	}
	if (currentShader == m_Resources->shaderShadow)
		glUniformMatrix4fv(modelMatrixUniformShadow,1,false,(const float*)glm::value_ptr(modelMatrix));
}
void Graphics::Translate(glm::mat4 &modelMatrix,const glm::vec3 &position){
	if(!restoreMatrix)
		modelMatrix=glm::translate(modelMatrix,position);
}
void Graphics::RotateX(glm::mat4 &modelMatrix,const glm::vec3 &rotation){
	if(!restoreMatrix)
		modelMatrix=glm::rotate(modelMatrix,rotation.x,vec3(1,0,0));
}
void Graphics::RotateY(glm::mat4 &modelMatrix,const glm::vec3 &rotation){
	if(!restoreMatrix)
		modelMatrix=glm::rotate(modelMatrix,rotation.y,vec3(0,1,0));
}
void Graphics::RotateZ(glm::mat4 &modelMatrix,const glm::vec3 &rotation){
	if(!restoreMatrix)
		modelMatrix=glm::rotate(modelMatrix,rotation.z,vec3(0,0,1));
}
void Graphics::Scale(glm::mat4 &modelMatrix,const glm::vec3 &scale){
	if(!restoreMatrix)
		modelMatrix=glm::scale(modelMatrix,scale);
}
void Graphics::Transform(glm::mat4 &modelMatrix,const glm::vec3 &position,const glm::vec3 &rotation,const glm::vec3 &scale){
	Translate(modelMatrix,position);
	RotateZ(modelMatrix,rotation);
	RotateX(modelMatrix,rotation);
	RotateY(modelMatrix,rotation);
	Scale(modelMatrix,scale);
}
//TODO: Exceptions support
void Graphics::CheckGLError() throw(OpenGLException){
	int glError = glGetError();
	while(glError!=GL_NO_ERROR){
		throw OpenGLException(glError);
		glError = glGetError();
	}
}
