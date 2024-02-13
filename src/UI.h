#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "scene.h"

struct parameterVectorGroup {
	ofParameter<float> x;
	ofParameter<float> y;
	ofParameter<float> z;
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

	ofxTextField selected_object_name_field;

	ofxFloatSlider* test;


public:

	void setup();
	void draw();
	void update();

	void changeFocus(const Object* Object = nullptr);
	bool addObject(Object* Object);
	bool removeObject(Object* Object);

	const ofParameter<float>* getPositionSliderValues();
	const ofVec3f* getRotationSliderValues();
	const ofVec3f* getScaleSliderValues();

	ofVec3f* setPositionSliderValues();
	ofVec3f* setRotationSliderValues();
	ofVec3f* setScaleSliderValues();


};


