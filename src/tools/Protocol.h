#ifndef PROTOCOL_H
#define PROTOCOL_H

#define MAX_PLAYERS 16
enum WEAPONS {
	WEAPON_HAMMER,
	WEAPON_GUN,
	WEAPON_SHOTGUN,
	WEAPON_GRENADE,
	WEAPON_RIFLE,
	WEAPON_NINJA,
	NUM_WEAPONS,
};
enum EMOTES {
	EMOTE_NORMAL,
	EMOTE_ANGRY,
	EMOTE_PAIN,
	EMOTE_HAPPY,
	EMOTE_BLINK,
	EMOTE_SURPRISE,
	NUM_EMOTES
};
enum HOOKSTATES {
	HOOK_RETRACTED = -1,
	HOOK_IDLE = 0,
	HOOK_RETRACT_START = 1,
	HOOK_RETRACT_END = 3,
	HOOK_FLYING,
	HOOK_GRABBED,
};

#endif
