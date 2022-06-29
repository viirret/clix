#ifndef GLOBAL_HH
#define GLOBAL_HH

#include <string>
#include <random>
#include "Vector2.hh"

template<typename T>
class rnd
{
	public:
		static T randomValue(T from, T to)
		{
			std::random_device rand_dev;
			std::mt19937 generator(rand_dev());
			std::uniform_real_distribution<T> dist(from, to);
			return dist(generator);
		}
};

class glb
{
	public:
		const static std::string assetsPath;
};

#endif
