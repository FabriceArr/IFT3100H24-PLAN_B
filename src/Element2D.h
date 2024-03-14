#pragma once
#include "Object.h"
#include "ofVbo.h"

class Element2D : public Object
{
private:
	ofImage image;
	ofVbo square;
	ofShader shader;

	float tone_mapping_exposure;
	float tone_mapping_gamma;
	bool tone_mapping_toggle;

public:
	Element2D(string primitivetype, string path, float tone_mapping_exposure, float tone_mapping_gamma, bool tone_mapping_toggle);
	~Element2D();

	void draw(bool highlight, bool animated = false, unsigned int substage = 0);

};
