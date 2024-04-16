#pragma once
#include "Object.h"
class ParamPlane : public Object
{
private:
	vector<ofVec3f> points;
	ofShader* brazier_surface_shader;
	GLuint vaoHandle;

public:
	ParamPlane(ofShader* TesselShader);

	void draw(bool highlight, bool animated, unsigned int substage);

	void update();
};

