#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <cstdint>
#include <tools/protocol.h>
#include <utility>

namespace tee3d {
using std::chrono::seconds;
using std::chrono::duration_cast;

using duration_t = std::chrono::microseconds;
template <class T> inline duration_t to_duration(T &&value) {
	return duration_cast<duration_t>(value);
}

template <int FPS> struct performance_t {
	uint16_t dynamic_fps;
	double factor;
	performance_t() {
		dynamic_fps = FPS;
		factor = 1.0;
	}
	performance_t(duration_t a, duration_t b) {
		dynamic_fps = to_duration(seconds(1)).count() / (b.count() - a.count());
		factor =
		    (b.count() - a.count()) * FPS * 1.0 / to_duration(seconds(1)).count();
	}
};
};

#endif
