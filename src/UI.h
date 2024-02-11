#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "scene.h"

struct parameterVectorGroup {
	ofxFloatSlider x;
	ofxFloatSlider y;
	ofxFloatSlider z;
};

class UI
{
private:
	Object* holder;
	const Object* selected_object;

	ofxPanel interface;
	parameterVectorGroup position_slider_group;
	parameterVectorGroup rotation_slider_group;
	parameterVectorGroup scale_slider_group;

	list<ofxButton*> object_element_list;

	ofParameter<std::string> selected_object_name;
	ofxTextField selected_object_name_field;
	list<ofxButton*> object_creation_selection;


public:

	void setup();
	void draw();
	void update();
	void changeFocus(const Object* Object = nullptr);
	bool addObject(Object* Object);
	bool removeObject(Object* Object);

};

