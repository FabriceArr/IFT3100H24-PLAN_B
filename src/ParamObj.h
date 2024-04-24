#pragma once
#include "Object.h"
class ParamObj : public Object
{
private:
	vector<ofVec2f> points;
	unsigned int segments;

	ofShader* brazier_curve_shader;
	GLuint vaoHandle;
	unsigned int pointsize;

public:
	ParamObj(ofShader* TesselShader);


	void draw(bool highlight, bool animated, unsigned int substage);
	ofVec2f getPointAt(float t);
	void update();
};

