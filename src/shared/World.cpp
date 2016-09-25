#include "World.h"

#include <fstream>
#include <shared/Console.h>
#include <shared/System.h>
#include <shared/world/Player.h>
#include <shared/world/Projectile.h>
#include <shared/world/Tile.h>

class World *pWorld;
World *g_World() { return pWorld != nullptr ? pWorld : new World(); }

World::World() : AsyncComponent("WORLD", 1000 / 60) {
	pWorld = this;
	UnLoad();
	Start();
};
World::~World() {
	Stop();
	UnLoad();
	for (auto p : players) {
		if (p != nullptr) {
			delete p;
		}
	}
	pWorld = nullptr;
};
void World::AsyncTick() {
	AsyncComponent::AsyncTick();
	if (!tileset.empty()) {
		for (Player *p : players) {
			if (p != nullptr) {
				p->Tick();
			}
		}
		for (Projectile *p : projectiles) {
			if (p != nullptr) {
				p->Tick();
			}
		}
	}
}
void World::Load(const std::string &name) {
	std::string path = g_System()->GetDataFile("maps/" + name + ".map");

	g_Console()->Info("Loading " + name);

	std::ifstream file(path);
	if (!file.good()) {
		g_Console()->Err("File not found");
		return;
	}
	unsigned char buf;
	file >> buf;
	worldSize.x = buf;
	file >> buf;
	worldSize.y = buf;
	file >> buf;
	worldSize.z = buf;

	tilesById.clear();
	tilesByPos.resize(worldSize.x);
	size_t i = 0;
	for (size_t xi = 0; xi < worldSize.x; xi++) {
		tilesByPos[xi].resize(worldSize.y);
		for (size_t yi = 0; yi < worldSize.y; yi++) {
			tilesByPos[xi][yi].resize(worldSize.z);
			for (size_t zi = 0; zi < worldSize.z; zi++) {
				// TODO: remove whitespaces
				Tile tile;
				tilesById.push_back(tile);
				tilesById[i].id = i;
				tilesById[i].x = xi;
				tilesById[i].y = yi;
				tilesById[i].z = zi;
				file >> buf;
				tilesById[i].type = buf;
				file >> buf;
				tilesById[i].texTop = buf;
				file >> buf;
				tilesById[i].texBottom = buf;
				file >> buf;
				tilesById[i].texOther = buf;
				i++;
			}
		}
	}
	for (i = 0; i < tilesById.size(); i++) {
		tilesByPos[tilesById[i].x][tilesById[i].y][tilesById[i].z] = &tilesById[i];
	}
	for (Tile &buffer : tilesById) {
		if (!buffer.isVisible()) {
			continue;
		}
		Tile *another = GetTile(buffer.x - 1, buffer.y, buffer.z);
		if (another != nullptr && another->isVisible()) {
			buffer.hasx = true;
		}
		another = GetTile(buffer.x + 1, buffer.y, buffer.z);
		if (another != nullptr && another->isVisible()) {
			buffer.hasX = true;
		}
		another = GetTile(buffer.x, buffer.y - 1, buffer.z);
		if (another != nullptr && another->isVisible()) {
			buffer.hasy = true;
		}
		another = GetTile(buffer.x, buffer.y + 1, buffer.z);
		if (another != nullptr && another->isVisible()) {
			buffer.hasY = true;
		}
		another = GetTile(buffer.x, buffer.y, buffer.z - 1);
		if (another != nullptr && another->isVisible()) {
			buffer.hasz = true;
		}
		another = GetTile(buffer.x, buffer.y, buffer.z + 1);
		if (another != nullptr && another->isVisible()) {
			buffer.hasZ = true;
		}
	}
	file >> tileset;
	for (size_t j = 0; j < tileset.length(); j++) {
		if (tileset[j] == '\n') {
			tileset = tileset.substr(0, j);
			break;
		}
	}
}
void World::UnLoad() {
	tileset = "";
	tilesById.clear();
	tilesByPos.clear();
	worldSize = glm::vec3(0, 0, 0);
}
bool World::isValid() const { return !tileset.empty(); }
Player *World::IntersectPlayer(const glm::vec3 &pos0, const glm::vec3 &pos1,
                               glm::vec3 *collision, glm::vec3 *beforeCollision,
                               int except, float radius) const {
	glm::vec3 pos = pos1 - pos0;
	float minv;
	Player *minp = nullptr;
	float len = glm::length(pos);
	if (len <= 0) {
		return nullptr;
	}
	glm::vec3 dist = glm::normalize(pos);
	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (i == except) {
			continue;
		}
		Player *p = players[i];
		if (p == nullptr) {
			continue;
		}
		glm::vec3 tee = p->pos - pos0;
		float proj = glm::dot(tee, dist);
		float c = pow(glm::length(tee), 2.0f) - pow(p->physSize / 2 + radius, 2.0f);
		float D = glm::sqrt(proj * proj - c);
		float v = (proj - D);
		if (glm::isnan(v) || v > len || v < 0) {
			continue;
		}
		if (minp == nullptr || minv > v) {
			minv = v;
			minp = p;
		}
	}
	if (minp != nullptr) {
		if (collision != nullptr) {
			*collision = dist * minv + pos0;
		}
		if (beforeCollision != nullptr) {
			*beforeCollision = dist * minv - dist + pos0;
		}
		return minp;
	}
	return nullptr;
	/*glm::vec3 pos00 = pos0;
	float Distance = distance(pos00, pos1);
	int End = Distance + 1;
	glm::vec3 PrevPos = pos00;
	for (int i = 0; i < End; i++) {
	 float a = i / Distance;
	 glm::vec3 Pos = glm::mix(pos00, pos1, a);
	 for (int p = 0; p < MAX_PLAYERS; p++) {
	  if (p == except)
	   continue;
	  Player *player = players[p];
	  float D = distance(Pos, player->pos);
	  if (D < player->physSize / 2 + radius && D > 0.0f) {
	   if (a > 0.0f)
	    pos00 = PrevPos;
	   else if (distance(pos1, player->pos) > D)
	    pos00 = pos1;
	   if (collision)
	    *collision = pos00;
	   if (beforeCollision)
	    *beforeCollision = pos00;
	   return player;
	  }
	 }
	 PrevPos = Pos;
	}
	return NULL;
	*/
}
// Code from original Teeworlds with small changes, Copyright Teeworlds team
Tile *World::GetTile(const glm::vec3 &pos) const {
	int x = round(pos.x) / 32;
	int y = round(pos.y) / 32;
	int z = round(pos.z) / 32;
	return GetTile(x, y, z);
}
Tile *World::GetTile(int x, int y, int z) const {
	return x < 0
	           ? nullptr
	           : static_cast<size_t>(x) >= worldSize.x
	                 ? nullptr
	                 : y < 0 ? nullptr
	                         : static_cast<size_t>(y) >= worldSize.y
	                               ? nullptr
	                               : z < 0 ? nullptr
	                                       : static_cast<size_t>(z) >= worldSize.z
	                                             ? nullptr
	                                             : tilesByPos[x][y][z];
}
Tile *World::IntersectLine(const glm::vec3 &pos0, const glm::vec3 &pos1,
                           glm::vec3 *collision,
                           glm::vec3 *beforeCollision) const {
	float distance = glm::distance(pos0, pos1);
	int end = distance + 1;
	glm::vec3 prev = pos0;
	Tile *buf;
	for (int i = 0; i < end; i++) {
		float a = i / distance;
		glm::vec3 pos = glm::mix(pos0, pos1, a);
		buf = GetTile(pos);
		if ((buf != nullptr) && buf->isPhys()) {
			if (collision != nullptr) {
				*collision = pos;
			}
			if (beforeCollision != nullptr) {
				*beforeCollision = prev;
			}
			return buf;
		}
		prev = pos;
	}
	if (collision != nullptr) {
		*collision = pos1;
	}
	if (beforeCollision != nullptr) {
		*beforeCollision = pos1;
	}
	return nullptr;
}
void World::MovePoint(glm::vec3 *position, glm::vec3 *velocity,
                      float elasticity, int *bounces) const {
	if (bounces != nullptr) {
		*bounces = 0;
	}

	glm::vec3 pos = *position;
	glm::vec3 vel = *velocity;
	glm::vec3 sVel = static_cast<float>(g_System()->tickCoeff * 60) * vel;
	Tile *buf = GetTile(pos + sVel);
	if ((buf != nullptr) && buf->isPhys()) {
		int affected = 0;
		buf = GetTile(glm::vec3(pos.x + sVel.x, pos.y, pos.z));
		if ((buf != nullptr) && buf->isPhys()) {
			velocity->x *= -elasticity;
			if (bounces != nullptr) {
				(*bounces)++;
			}
			affected++;
		}
		buf = GetTile(glm::vec3(pos.x, pos.y + sVel.y, pos.z));
		if ((buf != nullptr) && buf->isPhys()) {
			velocity->y *= -elasticity;
			if (bounces != nullptr) {
				(*bounces)++;
			}
			affected++;
		}
		buf = GetTile(glm::vec3(pos.x, pos.y, pos.z + sVel.z));
		if ((buf != nullptr) && buf->isPhys()) {
			velocity->z *= -elasticity;
			if (bounces != nullptr) {
				(*bounces)++;
			}
			affected++;
		}

		if (affected == 0) {
			velocity->x *= -elasticity;
			velocity->y *= -elasticity;
			velocity->z *= -elasticity;
		}
	} else {
		*position = pos + sVel;
	}
}
bool World::TestBox(const glm::vec3 &pos, const glm::vec3 &size) const {
	glm::vec3 Size = size * 0.5f;
	Tile *buf = GetTile(glm::vec3(pos.x - Size.x, pos.y - Size.y, pos.z - Size.z));
	if ((buf != nullptr) && buf->isPhys()) {
		return true;
	}
	buf = GetTile(glm::vec3(pos.x - Size.x, pos.y - Size.y, pos.z + Size.z));
	if ((buf != nullptr) && buf->isPhys()) {
		return true;
	}
	buf = GetTile(glm::vec3(pos.x - Size.x, pos.y + Size.y, pos.z - Size.z));
	if ((buf != nullptr) && buf->isPhys()) {
		return true;
	}
	buf = GetTile(glm::vec3(pos.x - Size.x, pos.y + Size.y, pos.z + Size.z));
	if ((buf != nullptr) && buf->isPhys()) {
		return true;
	}
	buf = GetTile(glm::vec3(pos.x + Size.x, pos.y - Size.y, pos.z - Size.z));
	if ((buf != nullptr) && buf->isPhys()) {
		return true;
	}
	buf = GetTile(glm::vec3(pos.x + Size.x, pos.y - Size.y, pos.z + Size.z));
	if ((buf != nullptr) && buf->isPhys()) {
		return true;
	}
	buf = GetTile(glm::vec3(pos.x + Size.x, pos.y + Size.y, pos.z - Size.z));
	if ((buf != nullptr) && buf->isPhys()) {
		return true;
	}
	buf = GetTile(glm::vec3(pos.x + Size.x, pos.y + Size.y, pos.z + Size.z));
	return (buf != nullptr) && buf->isPhys();
}
void World::MoveBox(glm::vec3 *position, glm::vec3 *velocity,
                    const glm::vec3 &size, float elasticity) const {
	// do the move
	glm::vec3 pos = *position;
	glm::vec3 vel = *velocity;
	glm::vec3 sVel = static_cast<float>(g_System()->tickCoeff * 60) * vel;

	float distance = glm::length(sVel);
	int max = static_cast<int>(distance);

	if (distance > 0.00001f) {
		// vec2 old_pos = pos;
		float Fraction = 1.0f / static_cast<float>(max + 1);
		for (int i = 0; i <= max; i++) {
			// float amount = i/(float)max;
			// if(max == 0)
			// amount = 0;

			glm::vec3 NewPos = pos + sVel * Fraction; // TODO: this row is not nice

			if (TestBox(NewPos, size)) {
				int Hits = 0;

				if (TestBox(glm::vec3(pos.x, pos.y, NewPos.z), size)) {
					NewPos.z = pos.z;
					vel.z *= -elasticity;
					sVel.z *= -elasticity;
					Hits++;
				}

				if (TestBox(glm::vec3(pos.x, NewPos.y, pos.z), size)) {
					NewPos.y = pos.y;
					vel.y *= -elasticity;
					sVel.y *= -elasticity;
					Hits++;
				}
				if (TestBox(glm::vec3(NewPos.x, pos.y, pos.z), size)) {
					NewPos.x = pos.x;
					vel.x *= -elasticity;
					sVel.x *= -elasticity;
					Hits++;
				}

				// neither of the tests got a collision.
				// this is a real _corner case_!
				if (Hits == 0) {
					NewPos.z = pos.z;
					pos.z *= -elasticity;
					sVel.z *= -elasticity;
					NewPos.y = pos.y;
					pos.y *= -elasticity;
					sVel.y *= -elasticity;
					NewPos.x = pos.x;
					vel.x *= -elasticity;
					sVel.x *= -elasticity;
				}
			}

			pos = NewPos;
		}
	}

	*position = pos;
	*velocity = vel;
}
