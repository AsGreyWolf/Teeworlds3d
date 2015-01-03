#include "Map.h"
#include <stdio.h>
#include <cstring>
#include "../Client.h"
#include "Graphics.h"
#include "graphics/Resources.h"
#include "graphics/Model.h"

bool Map::OnInit(){
	return true;
}
void Map::OnInput(unsigned char* keys,int xrel,int yrel,int wheel){}
void Map::OnStateChange(STATE lastState){
	if(!lastState.ingame && m_Client->state.ingame)
	{
		m_Model=new Model(m_Client->m_Graphics);
		Load("123");
		return;
	}
	if(lastState.ingame && !m_Client->state.ingame){
		OnQuit();
	}
}
void Map::OnQuit(){
	if(m_Client->state.ingame){
		delete m_Model;
		m_Client->m_Graphics->m_Resources->unLoadTexture(texture);
		tilesById.clear();
		for(int xi=0;xi<sizex;xi++){
			for(int yi=0;yi<sizey;yi++)
				delete[] tilesByPos[xi][yi];
			delete[] tilesByPos[xi];
		}
	}
}
void Map::OnRender(){
	if(m_Client->state.ingame)
		m_Model->render();
}
void Map::OnRenderBillboard(){}
void Map::OnRender2d(){}
void Map::OnTick(){}
void Map::OnMessage(int type,char* value){}
bool Map::Load(string name){
	string pp="maps/"+name+".map";
	string path=m_Client->GetDataFile(pp);

	m_Client->Info("Loading "+name);


	FILE* file=fopen(path.c_str(),"rb");
	if(file == 0){
		m_Client->Err("File not found");
		return false;
	}
	unsigned char buf;
	buf=fgetc(file);
	sizex=(int)(buf);
	buf=fgetc(file);
	sizey=(int)(buf);
	buf=fgetc(file);
	sizez=(int)(buf);

	tilesById.clear();
	tilesByPos=new Tile***[sizex];

	int i=0;
	for(int xi=0;xi<sizex;xi++){
		tilesByPos[xi]=new Tile**[sizey];
		for(int yi=0;yi<sizey;yi++){
			tilesByPos[xi][yi]=new Tile*[sizez];
			for(int zi=0;zi<sizez;zi++){
				Tile tile;
				tilesById.push_back(tile);
				tilesById[i].id=i;
				tilesById[i].x=xi;
				tilesById[i].y=yi;
				tilesById[i].z=zi;
				buf=fgetc(file);
				tilesById[i].type=(int)(buf);
				buf=fgetc(file);
				tilesById[i].texTop=(int)(buf);
				buf=fgetc(file);
				tilesById[i].texBottom=(int)(buf);
				buf=fgetc(file);
				tilesById[i].texOther=(int)(buf);
				i++;
			}
		}
	}
	for(i=0;i<tilesById.size();i++){
		tilesByPos[tilesById[i].x][tilesById[i].y][tilesById[i].z]=&tilesById[i];
	}
	char s[50];
	fgets(s,sizeof(s),file);
	for(int j=0;j<50;j++){
		if(s[j]=='\n') {
			s[j]='\0';
			break;
		}
	}
	string p="mapres/"+string(s)+".png";
	texture=-1;
	m_Client->m_Graphics->m_Resources->loadTexture(p,texture,true,false);


	fclose(file);
	for(int i=0;i<tilesById.size();i++){

		buffer=&tilesById[i];
		if(buffer->type==0) continue;
		if(!hasLeft()) buffer->hasx=false;
		if(!hasRight()) buffer->hasX=false;
		if(!hasy())  buffer->hasy=false;
		if(!hasY()) buffer->hasY=false;
		if(!hasBot()) buffer->hasz=false;
		if(!hasTop()) buffer->hasZ=false;


		if(!buffer->hasx){
			m_Model->addQuad(quad3(
				vec3(buffer->x*32-16,buffer->y*32-16,buffer->z*32+16),
				vec3(buffer->x*32-16,buffer->y*32+16,buffer->z*32+16),
				vec3(buffer->x*32-16,buffer->y*32+16,buffer->z*32-16),
				vec3(buffer->x*32-16,buffer->y*32-16,buffer->z*32-16)
				),vec3(-1,0,0),m_Client->m_Graphics->m_Resources->texturePos16[buffer->texOther]);

		}
		if(!buffer->hasX){
			m_Model->addQuad(quad3(
				vec3(buffer->x*32+16,buffer->y*32+16,buffer->z*32+16),
				vec3(buffer->x*32+16,buffer->y*32-16,buffer->z*32+16),
				vec3(buffer->x*32+16,buffer->y*32-16,buffer->z*32-16),
				vec3(buffer->x*32+16,buffer->y*32+16,buffer->z*32-16)
				),vec3(1,0,0),m_Client->m_Graphics->m_Resources->texturePos16[buffer->texOther]);
		}

		if(!buffer->hasy){
			m_Model->addQuad(quad3(
				vec3(buffer->x*32+16,buffer->y*32-16,buffer->z*32+16),
				vec3(buffer->x*32-16,buffer->y*32-16,buffer->z*32+16),
				vec3(buffer->x*32-16,buffer->y*32-16,buffer->z*32-16),
				vec3(buffer->x*32+16,buffer->y*32-16,buffer->z*32-16)
				),vec3(0,-1,0),m_Client->m_Graphics->m_Resources->texturePos16[buffer->texOther]);
		}
		if(!buffer->hasY){
			m_Model->addQuad(quad3(
				vec3(buffer->x*32-16,buffer->y*32+16,buffer->z*32+16),
				vec3(buffer->x*32+16,buffer->y*32+16,buffer->z*32+16),
				vec3(buffer->x*32+16,buffer->y*32+16,buffer->z*32-16),
				vec3(buffer->x*32-16,buffer->y*32+16,buffer->z*32-16)
				),vec3(0,1,0),m_Client->m_Graphics->m_Resources->texturePos16[buffer->texOther]);
		}
		if(!buffer->hasZ){
			m_Model->addQuad(quad3(
				vec3(buffer->x*32+16,buffer->y*32+16,buffer->z*32+16),
				vec3(buffer->x*32-16,buffer->y*32+16,buffer->z*32+16),
				vec3(buffer->x*32-16,buffer->y*32-16,buffer->z*32+16),
				vec3(buffer->x*32+16,buffer->y*32-16,buffer->z*32+16)
				),vec3(0,0,1),m_Client->m_Graphics->m_Resources->texturePos16[buffer->texTop]);
		}
		if(!buffer->hasz){
			m_Model->addQuad(quad3(
				vec3(buffer->x*32+16,buffer->y*32-16,buffer->z*32-16),
				vec3(buffer->x*32-16,buffer->y*32-16,buffer->z*32-16),
				vec3(buffer->x*32-16,buffer->y*32+16,buffer->z*32-16),
				vec3(buffer->x*32+16,buffer->y*32+16,buffer->z*32-16)
				),vec3(0,0,-1),m_Client->m_Graphics->m_Resources->texturePos16[buffer->texBottom]);
		}
	}
	m_Model->texture=texture;
	m_Model->create();
	return true;
}
bool Map::hasTop(){
	if(buffer->z<sizez-1){
		if(!tilesByPos[buffer->x][buffer->y][buffer->z+1]->isPhysTile()){
			return false;
		}
	}else return false;

	return true;
}
bool Map::hasBot(){
	if(buffer->z>0){
		if(!tilesByPos[buffer->x][buffer->y][buffer->z-1]->isPhysTile()){
			return false;
		}
	}else return false;

	return true;
}
bool Map::hasLeft(){
	if(buffer->x>0){
		if(!tilesByPos[buffer->x-1][buffer->y][buffer->z]->isPhysTile()){
			return false;
		}
	}else return false;

	return true;
}
bool Map::hasRight(){
	if(buffer->x<sizex-1){
		if(!tilesByPos[buffer->x+1][buffer->y][buffer->z]->isPhysTile()){
			return false;
		}
	}else return false;

	return true;
}
bool Map::hasY(){
	if(buffer->y<sizey-1){
		if(!tilesByPos[buffer->x][buffer->y+1][buffer->z]->isPhysTile()){
			return false;
		}
	}else return false;

	return true;
}bool Map::hasy(){
	if(buffer->y>0){
		if(!tilesByPos[buffer->x][buffer->y-1][buffer->z]->isPhysTile()){
			return false;
		}
	}else return false;

	return true;
}
