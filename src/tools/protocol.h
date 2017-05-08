#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <chrono>
#include <cstdint>
#include <type_traits>

namespace tee3d {
constexpr int MAX_PLAYERS = 16;
using player_id_t = int16_t;
using tile_type_t = uint8_t;
enum class weapon_t : uint8_t {
	hammer,
	gun,
	shotgun,
	grenade,
	rifle,
	ninja,
	max,
};
enum class emote_t : uint8_t {
	normal,
	angry,
	pain,
	happy,
	blink,
	surprise,
	max
};
enum class hook_state_t : int8_t {
	retracted = -1,
	idle = 0,
	start = 1,
	end = 3,
	flying,
	max,
};
enum class sound_t : uint8_t {
	max,
};

template <class T, class = typename std::enable_if<T::max == T::max>::type>
inline auto operator++(T &c) -> T & {
	using type = typename std::underlying_type<T>::type;
	return c = static_cast<T>((static_cast<type>(c) + 1) %
	                          static_cast<type>(T::max));
};
template <class T, class = typename std::enable_if<T::max == T::max>::type>
inline auto operator++(T &c, int) -> T {
	T result = c;
	++c;
	return result;
};
template <class T, class = typename std::enable_if<T::max == T::max>::type>
inline auto operator--(T &c) -> T & {
	using type = typename std::underlying_type<T>::type;
	if (static_cast<type>(c) == static_cast<type>(0))
		c = static_cast<type>(T::max);
	return --c;
};
template <class T, class = typename std::enable_if<T::max == T::max>::type>
inline auto operator--(T &c, int) -> T {
	T result = c;
	--c;
	return result;
};
};

#endif
