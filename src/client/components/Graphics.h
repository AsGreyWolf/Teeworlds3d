#define GLM_FORCE_RADIANS
#ifndef GRAPHICS_H
#define GRAPHICS_H

#define GLEW_STATIC
#ifndef M_PI
#define M_PI    3.14159265358979323846264338327950288   /* pi */
#endif
#ifndef M_PI_2
#define M_PI_2    1.5707963267948966192313216916385   /* pi/2 */
#endif
#include <string>
#include <exception>

#include "../Component.h"
#include "../../tools/quad2.h"
#include "../../tools/quad3.h"
#include "../../../other/sdl/include/SDL.h"
#include "../../../other/glew/include/glew.h"
#include "../../../other/glm/gtc/matrix_transform.hpp"
#include "../../../other/glm/gtc/type_ptr.hpp"

using namespace std;
class Resources;

class OpenGLException{
public:
	GLuint error;
	OpenGLException(GLuint e){
		error=e;
	};
	virtual string what() const throw(){
		return "OpenGL Error: "+string((const char*)gluErrorString(error));
	};
};

///<summary>Graphics component</summary>
class Graphics : public Component{
public:
	///<summary>Shader data IDs</summary>
	enum {
		SHADER_POS=0,
		SHADER_TEXMAP,
		SHADER_NORMAL
		//SHADER_COLOR
	};

	Graphics();
	~Graphics();
	///<summary>Input callback</summary>
	///<param name="keys">Keyboard state</param>
	///<param name="xrel">Mouse X position change</param>
	///<param name="yrel">Mouse Y position change</param>
	///<param name="wheel">Mouse wheel state</param>
	void Input(unsigned char* keys,int xrel,int yrel,int wheel);
	///<summary>State change callback</summary>
	///<param name="lastState">Last state</param>
	void StateChange(STATE lastState);
	///<summary>3d render callback</summary>
	void Render();
	///<summary>Render 3d Billboard</summary>
	void RenderBillboard();
	///<summary>2d render callback</summary>
	void Render2d();
	///<summary>Tick callback</summary>
	void Tick();
	///<summary>System message callback</summary>
	void Message(int type,char* value);

	///<summary>Throwes exception on Opengl Error</summary>
	void CheckGLError() throw(OpenGLException);
	///<summary>Convertes SDL_Surface in RGBA mode</summary>
	///<param name="src">Source</param>
	void to_RGBA(SDL_Surface* &src);
	///<summary>Convertes screen coords to pixels</summary>
	///<param name="coord">Coord</param>
	int to_pixels(float coord);
	///<summary>Convertes pixels to screen coords</summary>
	///<param name="pix">Pixels</param>
	float to_screen(int pix);
	///<summary>Updates color uniform in 3d shader</summary>
	///<param name="color">Color</param>
	void SetColor(vec4 color);
	///<summary>Updates light uniform in 3d shader</summary>
	///<param name="light">Use light?</param>
	void SetLight(bool light);
	///<summary>Updates color uniform in 2d shader</summary>
	///<param name="color">Color</param>
	void SetColor2d(vec4 color);
	///<summary>Updates position uniform in 2d shader</summary>
	///<param name="pos">Position</param>
	void SetPos2d(glm::vec2 pos, float depth);
	///<summary>Updates viewProjectionMatrix uniform in 3d shader</summary>
	///<param name="position">Position of the camera</param>
	///<param name="center">Vector directed forward the camera</param>
	///<param name="up">Vector directed upforwards the camera</param>
	void SetViewMatrix(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up);
	///<summary>Updates modelMatrix uniform in 3d shader</summary>
	///<param name="position">Position of the model</param>
	///<param name="rotation">Rotation of the model</param>
	///<param name="size">Size of the model</param>
	void SetModelMatrix(glm::mat4 &modelMatrix,glm::mat4 &normalMatrix,const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &size);
	///<summary>Translate matrix</summary>
	///<param name="position">Position of the model</param>
	void Translate(glm::mat4 &modelMatrix,const glm::vec3 &position);
	///<summary>Rotate matrix</summary>
	///<param name="rotation">Rotation of the model</param>
	void RotateX(glm::mat4 &modelMatrix,const glm::vec3 &rotation);
	///<summary>Rotate matrix</summary>
	///<param name="rotation">Rotation of the model</param>
	void RotateY(glm::mat4 &modelMatrix,const glm::vec3 &rotation);
	///<summary>Rotate matrix</summary>
	///<param name="rotation">Rotation of the model</param>
	void RotateZ(glm::mat4 &modelMatrix,const glm::vec3 &rotation);
	///<summary>Scale matrix</summary>
	///<param name="scale">Scale of the model</param>
	void Scale(glm::mat4 &modelMatrix,const glm::vec3 &scale);
	///<summary>Transform matrix</summary>
	///<param name="position">Position of the model</param>
	///<param name="rotation">Rotation of the model</param>
	///<param name="scale">Scale of the model</param>
	void Transform(glm::mat4 &modelMatrix,const glm::vec3 &position,const glm::vec3 &rotation,const glm::vec3 &scale);

	///<summary>Light uniform in 3d shader</summary>
	unsigned int lightUniform3d;
	///<summary>Color uniform in 3d shader</summary>
	unsigned int colorUniform3d;
	///<summary>viewProjectionMatrix uniform in 3d shader</summary>
	unsigned int viewProjectionMatrixUniform3d;
	///<summary>shadowProjectionMatrix uniform in 3d shader</summary>
	unsigned int shadowProjectionMatrixUniform3d;
	///<summary>modelMatrix uniform in 3d shader</summary>
	unsigned int modelMatrixUniform3d;
	///<summary>normalMatrix uniform in 3d shader</summary>
	unsigned int normalMatrixUniform3d;

	///<summary>viewProjectionMatrix uniform in shadow shader</summary>
	unsigned int viewProjectionMatrixUniformShadow;
	///<summary>modelMatrix uniform in shadow shader</summary>
	unsigned int modelMatrixUniformShadow;

	///<summary>Color uniform in 2d shader</summary>
	unsigned int colorUniform2d;
	///<summary>Aspect uniform in 2d shader</summary>
	unsigned int aspectUniform2d;
	///<summary>Position uniform in 2d shader</summary>
	unsigned int posUniform2d;

	///<summary>Aspect (screen width/screen height)</summary>
	float aspect;
	///<summary>Screen quad</summary>
	quad2 screen;
	///<summary>Height in pixels</summary>
	int screenSize;

	///<summary>Data loader</summary>
	class Resources* m_Resources;

	///<summary>3d projection matrix</summary>
	glm::mat4 perspectiveMatrix;
	///<summary>ortho projection matrix</summary>
	glm::mat4 orthoMatrix;

	GLuint shadowFBO;

	///<summary>If we are rendering scene second time(not to calc matrix)</summary>
	bool restoreMatrix;
};
Graphics* m_Graphics();

#endif
