#pragma once
#include "ofMain.h"
#include "vector"
#include "regex"

class TexTGen
{
public:
	//Creates a texture of size 2^size, ideally you want to go from a size of 5 to 12
	static ofImage generateTextureDefault(unsigned int size);

};