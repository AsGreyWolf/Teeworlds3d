#include "World.h"
#include <iostream>
#include "world/Player.h"
#include "world/Tile.h"
#include "Console.h"
#include "System.h"
//TODO debug
#include "../client/components/Graphics.h"
#include "../client/components/graphics/Resources.h"//TODO: REMOVE IT, NOW!

class World* pWorld;
World* g_World(){ return pWorld; }

World::World(){
	pWorld = this;
	UnLoad();
	//TODO: only debug
	auto skinName = g_Graphics()->m_Resources->skinTextures.begin();
	for (glm::uint8_t i = 0; i<MAX_PLAYERS; i++){
		players[i] = new Player(i);
		players[i]->pos = vec3(0, 0, rand() % 20048);//vec3(rand() % 2048, rand() % 2048, rand() % 2048);
		players[i]->rot = vec3(rand() / (static_cast <float> (RAND_MAX / (M_PI * 2))), rand() / (static_cast <float> (RAND_MAX / (M_PI * 2))), rand() / (static_cast <float> (RAND_MAX / (M_PI * 2))));
		players[i]->rot = glm::normalize(players[i]->rot);
		players[i]->weapon = rand() % NUM_WEAPONS;
		players[i]->emote = EMOTE_NORMAL;
		players[i]->skin = (*skinName).first;
		players[i]->nickname = (*skinName).first;
		skinName++;
		if (skinName == g_Graphics()->m_Resources->skinTextures.end()) skinName = g_Graphics()->m_Resources->skinTextures.begin();
	}
};
World::~World(){
	UnLoad();
	for (int i = 0; i < MAX_PLAYERS; i++){
		delete players[i];
	}
	pWorld = 0;
};
void World::Tick(){
	if (!tileset.empty())
		for (int i = 0; i < MAX_PLAYERS; i++) {
			if (pWorld->players[i])
				pWorld->players[i]->Tick();
		}
}
bool World::Load(string name){
	string pp = "maps/" + name + ".map";
	string path = g_System()->GetDataFile(pp);

	Console::Info("Loading " + name);

	FILE* file = fopen(path.c_str(), "rb");
	if (file == 0){
		Console::Err("File not found");
		return false;
	}
	unsigned char buf;
	buf = fgetc(file);
	worldSize.x = (int)(buf);
	buf = fgetc(file);
	worldSize.y = (int)(buf);
	buf = fgetc(file);
	worldSize.z = (int)(buf);

	tilesById.clear();
	tilesByPos = new Tile***[(int)worldSize.x];

	unsigned int i = 0;
	for (int xi = 0; xi<worldSize.x; xi++){
		tilesByPos[xi] = new Tile**[(int)worldSize.y];
		for (int yi = 0; yi<worldSize.y; yi++){
			tilesByPos[xi][yi] = new Tile*[(int)worldSize.z];
			for (int zi = 0; zi<worldSize.z; zi++){
				Tile tile;
				tilesById.push_back(tile);
				tilesById[i].id = i;
				tilesById[i].x = xi;
				tilesById[i].y = yi;
				tilesById[i].z = zi;
				buf = fgetc(file);
				tilesById[i].type = (int)(buf);
				buf = fgetc(file);
				tilesById[i].texTop = (int)(buf);
				buf = fgetc(file);
				tilesById[i].texBottom = (int)(buf);
				buf = fgetc(file);
				tilesById[i].texOther = (int)(buf);
				i++;
			}
		}
	}
	for (i = 0; i<tilesById.size(); i++){
		tilesByPos[tilesById[i].x][tilesById[i].y][tilesById[i].z] = &tilesById[i];
	}
	for (Tile& buffer : tilesById) {
		if (buffer.type == 0) continue;
		Tile* another = GetTile(buffer.x - 1, buffer.y, buffer.z);
		if (!another || !another->isVisible()) buffer.hasx = false;
		another = GetTile(buffer.x + 1, buffer.y, buffer.z);
		if (!another || !another->isVisible()) buffer.hasX = false;
		another = GetTile(buffer.x, buffer.y-1, buffer.z);
		if (!another || !another->isVisible()) buffer.hasy = false;
		another = GetTile(buffer.x, buffer.y+1, buffer.z);
		if (!another || !another->isVisible()) buffer.hasY = false;
		another = GetTile(buffer.x, buffer.y, buffer.z-1);
		if (!another || !another->isVisible()) buffer.hasz = false;
		another = GetTile(buffer.x, buffer.y, buffer.z+1);
		if (!another || !another->isVisible()) buffer.hasZ = false;
	}
	char s[50];
	fgets(s, sizeof(s), file);
	for (int j = 0; j<50; j++){
		if (s[j] == '\n') {
			s[j] = '\0';
			break;
		}
	}
	tileset = string(s);
	return true;
}
void World::UnLoad(){
	tileset = "";
	tilesById.clear();
	for (int xi = 0; xi<worldSize.x; xi++){
		for (int yi = 0; yi<worldSize.y; yi++)
			delete[] tilesByPos[xi][yi];
		delete[] tilesByPos[xi];
	}
	if(worldSize.x>0)
		delete[] tilesByPos;
	worldSize = glm::vec3(0, 0, 0);
}
Player* World::IntersectPlayer(glm::vec3 Pos0, glm::vec3 Pos1, glm::vec3 *pOutCollision, glm::vec3 *pOutBeforeCollision, int except, float radius){
	vec3 Pos = Pos1 - Pos0;
	float minv;
	Player* minp = NULL;
	float len = length(Pos);
	if (len <= 0) return NULL;
	vec3 dist = normalize(Pos);
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		if (i == except) continue;
		Player* p = players[i];
		vec3 Tee = p->pos - Pos0;
		float proj = dot(Tee, dist);
		float c = pow(length(Tee), 2.0f) - pow(p->physSize /2 + radius, 2.0f);
		float D = glm::sqrt(proj*proj - c);
		float v = (proj - D);
		if (glm::isnan(v) || v>len + 1 || v<-1){
			continue;
		}
		if (minp == NULL || minv > v) {
			minv = v;
			minp = p;
		}
	}
	if (minp != NULL) {
		if (pOutCollision)
			*pOutCollision = dist*minv + Pos0;
		if (pOutBeforeCollision)
			*pOutBeforeCollision = dist*minv - dist + Pos0;
		return minp;
	}
	return NULL;
}
// Code from original Teeworlds with small changes, Copyright Teeworlds team
Tile* World::GetTile(vec3 pos){
	int x = round(pos.x) / 32;
	int y = round(pos.y) / 32;
	int z = round(pos.z) / 32;
	return GetTile(x,y,z);
}
Tile* World::GetTile(int x, int y, int z) {
	return x < 0 ? NULL : x >= worldSize.x ? NULL : y < 0 ? NULL : y >= worldSize.y ? NULL : z < 0 ? NULL : z >= worldSize.z ? NULL : tilesByPos[x][y][z];
}
Tile* World::IntersectLine(vec3 Pos0, vec3 Pos1, vec3 *pOutCollision, vec3 *pOutBeforeCollision)
{
	float Distance = glm::distance(Pos0, Pos1);
	int End(Distance + 1);
	vec3 Last = Pos0;
	Tile* buf;
	for (int i = 0; i < End; i++)
	{
		float a = i / Distance;
		vec3 Pos = mix(Pos0, Pos1, a);
		buf = GetTile(Pos);
		if (buf && buf->isPhys())
		{
			if (pOutCollision)
				*pOutCollision = Pos;
			if (pOutBeforeCollision)
				*pOutBeforeCollision = Last;
			return buf;
		}
		Last = Pos;
	}
	if (pOutCollision)
		*pOutCollision = Pos1;
	if (pOutBeforeCollision)
		*pOutBeforeCollision = Pos1;
	return NULL;
}
void World::MovePoint(vec3 *pInoutPos, vec3 *pInoutVel, float Elasticity, int *pBounces)
{
	if (pBounces)
		*pBounces = 0;

	vec3 Pos = *pInoutPos;
	vec3 Vel = *pInoutVel;
	vec3 sVel= (float)(g_System()->tickCoeff * 60)*Vel;
	Tile* buf = GetTile(Pos + sVel);
	if (buf && buf->isPhys())
	{
		int Affected = 0;
		buf = GetTile(vec3(Pos.x + sVel.x, Pos.y, Pos.z));
		if (buf && buf->isPhys())
		{
			pInoutVel->x *= -Elasticity;
			if (pBounces)
				(*pBounces)++;
			Affected++;
		}
		buf = GetTile(vec3(Pos.x, Pos.y + sVel.y, Pos.z));
		if (buf && buf->isPhys())
		{
			pInoutVel->y *= -Elasticity;
			if (pBounces)
				(*pBounces)++;
			Affected++;
		}
		buf = GetTile(vec3(Pos.x, Pos.y, Pos.z + sVel.z));
		if (buf && buf->isPhys())
		{
			pInoutVel->z *= -Elasticity;
			if (pBounces)
				(*pBounces)++;
			Affected++;
		}

		if (Affected == 0)
		{
			pInoutVel->x *= -Elasticity;
			pInoutVel->y *= -Elasticity;
			pInoutVel->z *= -Elasticity;
		}
	}
	else
	{
		*pInoutPos = Pos + sVel;
	}
}
bool World::TestBox(vec3 Pos, vec3 Size)
{
	Size *= 0.5f;
	Tile* buf = GetTile(vec3(Pos.x - Size.x, Pos.y - Size.y, Pos.z - Size.z));
	if (buf && buf->isPhys())
		return true;
	buf = GetTile(vec3(Pos.x - Size.x, Pos.y - Size.y, Pos.z + Size.z));
	if (buf && buf->isPhys())
		return true;
	buf = GetTile(vec3(Pos.x - Size.x, Pos.y + Size.y, Pos.z - Size.z));
	if (buf && buf->isPhys())
		return true;
	buf = GetTile(vec3(Pos.x - Size.x, Pos.y + Size.y, Pos.z + Size.z));
	if (buf && buf->isPhys())
		return true;
	buf = GetTile(vec3(Pos.x + Size.x, Pos.y - Size.y, Pos.z - Size.z));
	if (buf && buf->isPhys())
		return true;
	buf = GetTile(vec3(Pos.x + Size.x, Pos.y - Size.y, Pos.z + Size.z));
	if (buf && buf->isPhys())
		return true;
	buf = GetTile(vec3(Pos.x + Size.x, Pos.y + Size.y, Pos.z - Size.z));
	if (buf && buf->isPhys())
		return true;
	buf = GetTile(vec3(Pos.x + Size.x, Pos.y + Size.y, Pos.z + Size.z));
	if (buf && buf->isPhys())
		return true;
	return false;
}
void World::MoveBox(vec3 *pInoutPos, vec3 *pInoutVel, vec3 Size, float Elasticity)
{
	// do the move
	vec3 Pos = *pInoutPos;
	vec3 Vel = *pInoutVel;
	vec3 sVel = (float)(g_System()->tickCoeff * 60)*Vel;

	float Distance = length(sVel);
	int Max = (int)Distance;

	if (Distance > 0.00001f)
	{
		//vec2 old_pos = pos;
		float Fraction = 1.0f / (float)(Max + 1);
		for (int i = 0; i <= Max; i++)
		{
			//float amount = i/(float)max;
			//if(max == 0)
			//amount = 0;

			vec3 NewPos = Pos + sVel*Fraction; // TODO: this row is not nice

			if (TestBox(NewPos, Size))
			{
				int Hits = 0;

				if (TestBox(vec3(Pos.x, Pos.y, NewPos.z), Size))
				{
					NewPos.z = Pos.z;
					Vel.z *= -Elasticity;
					sVel.z *= -Elasticity;
					Hits++;
				}

				if (TestBox(vec3(Pos.x, NewPos.y, Pos.z), Size))
				{
					NewPos.y = Pos.y;
					Vel.y *= -Elasticity;
					sVel.y *= -Elasticity;
					Hits++;
				}
				if (TestBox(vec3(NewPos.x, Pos.y, Pos.z), Size))
				{
					NewPos.x = Pos.x;
					Vel.x *= -Elasticity;
					sVel.x *= -Elasticity;
					Hits++;
				}

				// neither of the tests got a collision.
				// this is a real _corner case_!
				if (Hits == 0)
				{
					NewPos.z = Pos.z;
					Vel.z *= -Elasticity;
					sVel.z *= -Elasticity;
					NewPos.y = Pos.y;
					Vel.y *= -Elasticity;
					sVel.y *= -Elasticity;
					NewPos.x = Pos.x;
					Vel.x *= -Elasticity;
					sVel.x *= -Elasticity;
				}
			}

			Pos = NewPos;
		}
	}

	*pInoutPos = Pos;
	*pInoutVel = Vel;
}