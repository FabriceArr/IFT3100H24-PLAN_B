#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "scene.h"

struct parameterVectorGroup {
	ofxGuiGroup group;
	ofParameter<float> x;
	ofParameter<float> y;
	ofParameter<float> z;

	parameterVectorGroup(ofParameter<float> x = 0.f, ofParameter<float> y = 0.f, ofParameter<float> z = 0.f) {
		this->x = x;
		this->y = y;
		this->z = z;

	}
};

class UI
{
private:
	Object* selected_object;

	ofxPanel interface;
	parameterVectorGroup position_slider_group;
	parameterVectorGroup rotation_slider_group;
	parameterVectorGroup scale_slider_group;

public:

	void setup(Object* selectedObject);
	void draw();
	void update();

};

