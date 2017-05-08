#ifndef SHAREDCOMPONENT_H
#define SHAREDCOMPONENT_H

#include <list>
#include <memory>
#include <stdint.h>
#ifdef __ANDROID__
#include <tools/android.h> // NDK fix
#endif

namespace tee3d {
using std::list;
using std::shared_ptr;
using std::weak_ptr;
class component {
protected:
	component() = default;
	virtual void tick(){};

public:
	virtual ~component() = default;

	class manager {
		using value_type = shared_ptr<component>;
		static list<value_type> data;
		template <class T, class... Args> static weak_ptr<T> emplace(Args... args);
		friend class component;

	public:
		manager() = delete;
		static void cleanup();
		static void tick();
	};
	template <class T> class wrapper {
	public:
		using component_type = T;
		using value_type = weak_ptr<component_type>;
		using const_value_type = const weak_ptr<component_type>;
		using pointer = typename value_type::element_type *;
		using const_pointer = typename const_value_type::element_type *;
		virtual ~wrapper() = default;
		pointer operator->();
		const_pointer operator->() const;
		operator bool() const;

	private:
		static value_type ptr;
	};
};
};

#endif
