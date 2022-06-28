#include "Global.hh"

const std::string glb::assetsPath = "../assets/";

float glb::randomFloat(float begin, float end)
{
	float random = ((float) rand() / (float) RAND_MAX);
	float diff = end - begin;
	float r = random * diff;
	return begin + r;
}


