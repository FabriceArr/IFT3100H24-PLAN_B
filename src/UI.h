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

	list<ofxButton*> object_element_list;

	ofxPanel object_creation_interface;
	ofxLabel selected_object_namefield;
	list<ofxButton*> object_creation_selection;

	parameterVectorGroup color_selection_group;	
	parameterVectorGroup stroke_color_selection_group;


public:

	void setup();
	void draw();
	void update();
	void changeFocus(Object* Object);
	bool addObject(Object* Object);
	bool removeObject(Object* Object);

};

