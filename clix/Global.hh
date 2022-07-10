#ifndef GLOBAL_HH
#define GLOBAL_HH

#include <random>

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

#endif
