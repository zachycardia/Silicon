/**
 * @file    singleton.h
 *
 * @brief   Singleton class.
 *
 * @author  Zachary Ning
**/

#pragma once

#include <cassert>
#include <utility>

namespace Silicon {

template <typename T>
class Singleton {
public:
	/**
	 * @brief   Gets the singleton instance.
	 * 
	 * @return  Instance of the templated T.
	**/
	static T& Instance();

	/**
	 * @brief   Initializes the singleton instance.
	 * 
	 * @param   args    Arguments to be passed to the constructor.
	**/
	template <typename ...Args>
	static void Initialize(Args&& ...args);

	/**
	 * @brief   Destroys the singleton instance.
	**/
	static void Reset();

private:
	static T* s_instance;
};

template <typename T>
inline T& Singleton<T>::Instance() {
	return *s_instance;
}

template <typename T>
template <typename ...Args>
inline void Singleton<T>::Initialize(Args&& ...args) {
	s_instance = new T{std::forward<Args>(args)...};
}

template <typename T>
inline void Singleton<T>::Reset() {
	if (s_instance) { delete s_instance; }
	s_instance = nullptr;
}

template <typename T>
T* Singleton<T>::s_instance{nullptr};

}
