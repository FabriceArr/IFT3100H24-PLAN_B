#pragma once
#include "Object.h"
class ParamObj : public Object
{
private:
	vector<ofVec3f> points;
	ofShader* brazier_curve_shader;
	GLuint vaoHandle;

public:
	ParamObj(ofShader* TesselShader);

	void draw(bool highlight, bool animated, unsigned int substage);
};

