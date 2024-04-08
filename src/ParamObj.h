#pragma once
#include "Object.h"
class ParamObj : public Object
{
private:
	vector<ofVec3f> points;
	ofShader* brazier_curve_shader;

public:
	ParamObj(unsigned int NumbSeg);
};

