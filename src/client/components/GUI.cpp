#include "GUI.h"
#include "../Client.h"
#include "Graphics.h"
#include "graphics/Resources.h"
#include "graphics/Text.h"
#include "graphics/Model2d.h"
#include "graphics/TextGenerator.h"

class GUI* pGUI;
GUI* g_GUI(){ return pGUI; }

Model2d* test;
GUI::GUI() : Component(){
	pGUI = this;
	fpsObject=new Text();
	fpsObject->depth = 1;
	fpsObject->AddText(std::to_string(g_Client()->fps), Resources::FONT_BIG, TextGenerator::ALIGN_RIGHT_TOP, true);
	fpsObject->Create();
	fpsObject->position = g_Graphics()->screen.p11;
	fpsTitle=new Text();
	fpsTitle->depth = 1;
	fpsTitle->AddText("FPS=",Resources::FONT_BIG,TextGenerator::ALIGN_RIGHT_TOP,false);
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
void GUI::Input(unsigned char* keys,int xrel,int yrel,int wheel){}
void GUI::StateChange(STATE lastState){}
void GUI::Render(){}
void GUI::RenderBillboard(){}
void GUI::Render2d(){
	test->Render();
	fpsObject->SetText(std::to_string(g_Client()->fps));
	fpsObject->Render();
	fpsTitle->Render();
}
void GUI::Tick(){}
void GUI::Message(int type,char* value){}
void GUI::Fill(quad2 in,quad2 out){
	//TODO: make something less stupid
	test=new Model2d();
	test->AddRectangle(in,out);
	test->coloring=vec4(0,0,0,0.5f);
	test->Create();
}