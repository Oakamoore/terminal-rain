#ifndef RANDOM_H
#define RANDOM_H

#include <random>

namespace Random
{
	inline std::mt19937 generate()
	{
		std::random_device rd {};

		std::seed_seq ss {rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};

		return std::mt19937 {ss};
	}

	inline std::mt19937 mt {generate()};

	// Generates a random value between two integers (inclusive)
	int get(int min, int max)
	{
		return std::uniform_int_distribution {min, max} (mt);
	}
}

#endif