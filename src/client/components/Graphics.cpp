#include "Graphics.h"
#include <vector>
#include <string>
#include <cstdio>
#include "../Client.h"
#include "Camera.h"
#include "graphics/PlayerModel.h"
#include "graphics/Model.h"
#include "graphics/Model2d.h"
#include "graphics/Resources.h"
#include "../../tools/Protocol.h"

float renderSize=1;
const float LightPos[4]={0, 0, 500, 1};
const float LightColorDif[4]={1*renderSize, 1*renderSize, 1*renderSize, 1};
const float LightColorAmb[4]={0.5f, 0.5f, 0.5f, 1};
const float LightColorSpec[4]={0.001f, 0.001f, 0.001f, 1};

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
Model2d* mm;
Graphics::Graphics(Client* c) : Component(c){
	SDL_GLContext context;

	if ((context = SDL_GL_CreateContext(m_Client->screen)) == NULL)
	{

		m_Client->Err("Could not get context: "+string(SDL_GetError()));
		return; //TODO: exceptions
	}
	glewInit();
	m_Client->Info("Initialized OpenGL "+string((char*)glGetString(GL_VERSION)));
	int w=1024;
	int h=768;
	if( h == 0 )
	{
		h = 1;
	}
	screenSize=h;
	WscreenSize=w;
	aspect=(float)w/h;
	screen=quad2(-1*aspect,-1,2*aspect,2);
	perspectiveMatrix=glm::perspective(1.0471975512f, aspect, 10.0f,5000.0f);
	orthoMatrix=glm::ortho(-160.0f,160.0f,-160.0f,160.0f,0.0f,1.0f);

	glEnable(GL_BLEND);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();

	glEnable(GL_CULL_FACE);
	glClearColor(0, 0.75f, 1, 1);

	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	glPolygonMode(GL_FRONT, GL_FILL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glHint(GL_FOG_HINT,GL_NICEST);
	glHint(GL_GENERATE_MIPMAP_HINT,GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);


	m_Resources=new Resources(this);
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
	shadowViewProjectionMatrixUniform3d=glGetUniformLocation(m_Resources->shader3d,"shadowViewProjectionMatrix");
	textureUniform3d=glGetUniformLocation(m_Resources->shader3d,"tex");
	shadowUniform3d=glGetUniformLocation(m_Resources->shader3d,"shadow");

	viewProjectionMatrixUniformShadow=glGetUniformLocation(m_Resources->shaderShadow,"viewProjectionMatrix");
	modelMatrixUniformShadow=glGetUniformLocation(m_Resources->shaderShadow,"modelMatrix");

	colorUniform2d=glGetUniformLocation(m_Resources->shader2d,"colorer");
	aspectUniform2d=glGetUniformLocation(m_Resources->shader2d,"aspect");
	posUniform2d=glGetUniformLocation(m_Resources->shader2d,"pos");

	glGenFramebuffersEXT(1, &frameShadowBuffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, frameShadowBuffer);
	//glDrawBuffer(GL_NONE);
	//glReadBuffer(GL_NONE);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_Resources->textureShadowColor, 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, m_Resources->textureShadowDepth, 0);

	glLineWidth(3);
	glPointSize(3);

	SDL_SetRelativeMouseMode(SDL_TRUE);
	mm=new Model2d(this);
	mm->addQuad(screen/2,quad2(0,0,1,1));
	mm->texture=m_Resources->textureShadowDepth;
	mm->create();
}
Graphics::~Graphics(){
	m_Resources->UnLoad();
	delete m_Resources;
}
void Graphics::Input(unsigned char* keys,int xrel,int yrel,int wheel){}
void Graphics::Render(bool buffered){}
void Graphics::RenderBillboard(){}
void Graphics::Render2d(){}
void Graphics::Tick(){
	glUseProgram(m_Resources->shader3d);
	m_Client->m_Camera->SetMatrix();
	glUseProgram(m_Resources->shader2d);
	glUniform1f(aspectUniform2d,aspect);
	vec3 shadowCameraPos=vec3(m_Client->m_Camera->position.x,m_Client->m_Camera->position.y,1);
	SetShadowMatrix(shadowCameraPos,shadowCameraPos+vec3(0,0,-1),vec3(0,1,0));
	glViewport( 0, 0, WscreenSize*2, screenSize*2 );

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, frameShadowBuffer);
	//glUseProgram(m_Resources->shaderShadow);
	glCullFace(GL_FRONT);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	m_Client->Render();

	glViewport( 0, 0, WscreenSize, screenSize );
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D,m_Resources->textureShadowDepth);
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glUseProgram(m_Resources->shader3d);
	glCullFace(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	m_Client->Render(true);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D,m_Resources->textureBlank);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);

	glClear(GL_DEPTH_BUFFER_BIT);
	m_Client->RenderBillboard();

	glUseProgram(m_Resources->shader2d);
	glClear(GL_DEPTH_BUFFER_BIT);
	m_Client->Render2d();
	mm->render();

	glFlush();
}
void Graphics::Message(int type,char* value){}
void Graphics::StateChange(STATE lastState){}
void Graphics::SetColor(vec4 color){
	glUniform4f(colorUniform3d,color.r,color.g,color.b,color.a);
}
void Graphics::SetColor2d(vec4 color){
	glUniform4f(colorUniform2d,color.r,color.g,color.b,color.a);
}
void Graphics::SetLight(bool light){
	glUniform1f(lightUniform3d, light?1.0f:0.0f);
}
void Graphics::SetPos2d(vec2 pos){
	glUniform2f(posUniform2d,pos.x,pos.y);
}
void Graphics::SetViewMatrix(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up){
	viewMatrix=glm::lookAt(position, center, up);
	viewProjectionMatrix=perspectiveMatrix*viewMatrix;
	glUniformMatrix4fv(viewProjectionMatrixUniform3d,1,false,(const float*)glm::value_ptr(viewProjectionMatrix));
}
void Graphics::SetShadowMatrix(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up){
	viewMatrix=glm::lookAt(position, center, up);
	viewProjectionMatrix=orthoMatrix*viewMatrix;
	glUniformMatrix4fv(viewProjectionMatrixUniformShadow,1,false,(const float*)glm::value_ptr(viewProjectionMatrix));
	glUniformMatrix4fv(shadowViewProjectionMatrixUniform3d,1,false,(const float*)glm::value_ptr(viewProjectionMatrix));
}
void Graphics::SetModelMatrix(glm::mat4 &modelBuffer, glm::mat4 &normalBuffer,const vec3 &position, const vec3 &rotation, const vec3 &size,const glm::mat4 &lastMatrix){
	modelBuffer=lastMatrix;
	Transform(modelBuffer,position,rotation,size);

	normalBuffer=modelBuffer;
	normalBuffer=glm::inverse(normalBuffer);
	normalBuffer=glm::transpose(normalBuffer);
	glUniformMatrix4fv(normalMatrixUniform3d,1,false,(const float*)glm::value_ptr(normalBuffer));
	glUniformMatrix4fv(modelMatrixUniform3d,1,false,(const float*)glm::value_ptr(modelBuffer));
	glUniformMatrix4fv(modelMatrixUniformShadow,1,false,(const float*)glm::value_ptr(modelBuffer));
}
void Graphics::SetModelMatrix(const glm::mat4 &modelBuffer, const glm::mat4 &normalBuffer){
	glUniformMatrix4fv(normalMatrixUniform3d,1,false,(const float*)glm::value_ptr(normalBuffer));
	glUniformMatrix4fv(modelMatrixUniform3d,1,false,(const float*)glm::value_ptr(modelBuffer));
	glUniformMatrix4fv(modelMatrixUniformShadow,1,false,(const float*)glm::value_ptr(modelBuffer));
}
void Graphics::Translate(glm::mat4& matrix,const glm::vec3 &position){
	matrix=glm::translate(matrix,position);
}
void Graphics::RotateX(glm::mat4& matrix,const glm::vec3 &rotation){
	matrix=glm::rotate(matrix,rotation.x,vec3(1,0,0));
}
void Graphics::RotateY(glm::mat4& matrix,const glm::vec3 &rotation){
	matrix=glm::rotate(matrix,rotation.y,vec3(0,1,0));
}
void Graphics::RotateZ(glm::mat4& matrix,const glm::vec3 &rotation){
	matrix=glm::rotate(matrix,rotation.z,vec3(0,0,1));
}
void Graphics::Scale(glm::mat4& matrix,const glm::vec3 &scale){
	matrix=glm::scale(matrix,scale);
}
void Graphics::Transform(glm::mat4& matrix,const glm::vec3 &position,const glm::vec3 &rotation,const glm::vec3 &scale){
	Translate(matrix,position);
	RotateZ(matrix,rotation);
	RotateX(matrix,rotation);
	RotateY(matrix,rotation);
	Scale(matrix,scale);
}
void Graphics::CheckGLError() throw(OpenGLException){
	int glError = glGetError();
	while(glError!=GL_NO_ERROR){
		throw OpenGLException(glError);
		glError = glGetError();
	}
}
