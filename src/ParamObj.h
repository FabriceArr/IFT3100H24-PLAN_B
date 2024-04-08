#pragma once
#include "Object.h"
class ParamObj : public Object
{
private:
	vector<ofVec3f> points;
	ofShader* brazier_curve_shader;
	GLuint vaoHandle;
	ofMatrix4x4* vue,* project;

public:
	ParamObj(ofShader* TesselShader, ofEasyCam* cam);

	void draw(bool highlight, bool animated, unsigned int substage);
};

