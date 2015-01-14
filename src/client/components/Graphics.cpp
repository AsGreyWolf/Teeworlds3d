#include "Graphics.h"
#include <vector>
#include <string>
#include <cstdio>
#include "../Client.h"
#include "Camera.h"
#include "graphics/PlayerModel.h"
#include "graphics/Model.h"
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

bool Graphics::Init(){
	SDL_GLContext context;

	if ((context = SDL_GL_CreateContext(m_Client->screen)) == NULL)
	{

		m_Client->Err("Could not get context: "+string(SDL_GetError()));
		return false;
	}
	glewInit();
	m_Client->Info((char*)glGetString(GL_VERSION));
	int w=1024;
	int h=768;
	if( h == 0 )
	{
		h = 1;
	}
	screenSize=h;
	glViewport( 0, 0, w, h );
	aspect=(float)w/h;
	screen=quad2(-1*aspect,-1,2*aspect,2);
	perspectiveMatrix=glm::perspective(1.0471975512f, aspect, 1.0f,10000.0f);

	glEnable( GL_BLEND );
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(0, 0.75f, 1, 1);

	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	glPolygonMode(GL_FRONT, GL_FILL);
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	glHint( GL_FOG_HINT, GL_NICEST );
	glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST );
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST );


	m_Resources=new Resources(this);
	m_Resources->Load();

	glBindAttribLocation(m_Resources->shader3d, SHADER_POS, "in_Position");
	glBindAttribLocation(m_Resources->shader3d, SHADER_TEXMAP, "in_TexMap");
	glBindAttribLocation(m_Resources->shader3d, SHADER_NORMAL, "in_Normal");

	glBindAttribLocation(m_Resources->shader2d, SHADER_POS, "in_Position");
	glBindAttribLocation(m_Resources->shader2d, SHADER_TEXMAP, "in_TexMap");

	colorUniform3d=glGetUniformLocation(m_Resources->shader3d,"colorer");
	lightUniform=glGetUniformLocation(m_Resources->shader3d,"lighting");
	viewProjectionMatrixUniform=glGetUniformLocation(m_Resources->shader3d,"viewProjectionMatrix");
	modelMatrixUniform=glGetUniformLocation(m_Resources->shader3d,"modelMatrix");
	normalMatrixUniform=glGetUniformLocation(m_Resources->shader3d,"normalMatrix");

	colorUniform2d=glGetUniformLocation(m_Resources->shader2d,"colorer");
	aspectUniform2d=glGetUniformLocation(m_Resources->shader2d,"aspect");
	posUniform2d=glGetUniformLocation(m_Resources->shader2d,"pos");


	glUseProgram(m_Resources->shader3d);

	glLineWidth(3);
	glPointSize(3);

	SDL_SetRelativeMouseMode(SDL_TRUE);
	return true;
}
void Graphics::Input(unsigned char* keys,int xrel,int yrel,int wheel){}
void Graphics::Quit(){
	m_Resources->UnLoad();
	delete m_Resources;
}
void Graphics::Render(){}
void Graphics::RenderBillboard(){}
void Graphics::Render2d(){}
void Graphics::Tick(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();
	modelMatrix=mat4(1.0f);
	std::stack<glm::mat4> empty;
	std::swap(ModelMatrixStack, empty);

	m_Client->m_Camera->SetMatrix();

	m_Client->Render();
	glClear(GL_DEPTH_BUFFER_BIT);
	m_Client->RenderBillboard();

	glDisable(GL_CULL_FACE);
	glClear(GL_DEPTH_BUFFER_BIT);
	glUseProgram(m_Resources->shader2d);
	glUniform1f(aspectUniform2d,aspect);

	m_Client->Render2d();

	glUseProgram(m_Resources->shader3d);
	glEnable(GL_CULL_FACE);

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
	glUniform1f(lightUniform, light?1.0f:0.0f);
}
void Graphics::SetPos2d(vec2 pos){
	glUniform2f(posUniform2d,pos.x,pos.y);
}
void Graphics::SetViewMatrix(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up){
	viewMatrix=glm::lookAt(position, center, up);
	viewProjectionMatrix=perspectiveMatrix*viewMatrix;
	glUniformMatrix4fv(viewProjectionMatrixUniform,1,false,(const float*)glm::value_ptr(viewProjectionMatrix));
}
void Graphics::SetModelMatrix(const vec3 &position, const vec3 &rotation, const vec3 &size){
	modelMatrix*=Transform(position,rotation,size);

	normalMatrix=modelMatrix;
	normalMatrix=glm::inverse(normalMatrix);
	normalMatrix=glm::transpose(normalMatrix);
	glUniformMatrix4fv(normalMatrixUniform,1,false,(const float*)glm::value_ptr(normalMatrix));
	glUniformMatrix4fv(modelMatrixUniform,1,false,(const float*)glm::value_ptr(modelMatrix));
}
void Graphics::PushMatrix(){
	ModelMatrixStack.push(modelMatrix);
}
void Graphics::PopMatrix(){
	modelMatrix=ModelMatrixStack.top();
	ModelMatrixStack.pop();
}
glm::mat4 Graphics::Translate(const glm::vec3 &position){
	return glm::translate(position);
}
glm::mat4 Graphics::RotateX(const glm::vec3 &rotation){
	return glm::rotate(rotation.x,vec3(1,0,0));
}
glm::mat4 Graphics::RotateY(const glm::vec3 &rotation){
	return glm::rotate(rotation.y,vec3(0,1,0));
}
glm::mat4 Graphics::RotateZ(const glm::vec3 &rotation){
	return glm::rotate(rotation.z,vec3(0,0,1));
}
glm::mat4 Graphics::Scale(const glm::vec3 &scale){
	return glm::scale(scale);
}
glm::mat4 Graphics::Transform(const glm::vec3 &position,const glm::vec3 &rotation,const glm::vec3 &scale){
	return (((Translate(position)*RotateZ(rotation))*RotateX(rotation))*RotateY(rotation))*Scale(scale);
}
