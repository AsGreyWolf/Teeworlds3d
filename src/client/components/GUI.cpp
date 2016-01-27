#include "GUI.h"
#include "Graphics.h"
#include "graphics/models/Text.h"
#include "graphics/models/Model2d.h"
#include "graphics/TextGenerator.h"
#include "../Client.h"
#include "../../shared/System.h"

class GUI* pGUI;
GUI* g_GUI(){ return pGUI; }

Model2d* test;
GUI::GUI() : Component(){
	pGUI = this;
	fpsObject=new Text(std::to_string(g_System()->fps), TextGenerator::FONT_BIG, TextGenerator::ALIGN_RIGHT_TOP, true);
	fpsObject->depth = 1;
	fpsObject->Create();
	fpsObject->position = g_Graphics()->screen.p11;
	fpsTitle=new Text("FPS=", TextGenerator::FONT_BIG, TextGenerator::ALIGN_RIGHT_TOP);
	fpsTitle->depth = 1;
	fpsTitle->Create();
	fpsTitle->position=fpsObject->data->geometry.p01+fpsObject->position;
	float round=0.05f;
	Fill(quad2(fpsTitle->data->geometry.p00+fpsTitle->position,fpsObject->data->geometry.p10+fpsObject->position,fpsTitle->data->geometry.p01+fpsTitle->position,fpsObject->data->geometry.p11+fpsObject->position),quad2(fpsTitle->data->geometry.p00+fpsTitle->position-vec2(round/2,round/2),fpsObject->data->geometry.p10+fpsObject->position-vec2(0,round/2),fpsTitle->data->geometry.p01+fpsTitle->position-vec2(round/2,0),fpsObject->data->geometry.p11+fpsObject->position));
}
GUI::~GUI(){
	delete fpsObject;
	delete fpsTitle;
	pGUI = NULL;
}
void GUI::Tick(){
	Component::Tick();
	fpsObject->SetText(std::to_string(g_System()->fps));
}
void GUI::Fill(const quad2& in, const quad2& out){
	//TODO: make something less stupid
	test=new Model2d();
	test->AddRectangle(in,out);
	test->color=vec4(0,0,0,0.5f);
	test->Create();
}