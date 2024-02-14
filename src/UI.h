#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "scene.h"
#include <vector>

struct parameterVectorGroup {
	ofParameter<float>* x;
	ofParameter<float>* y;
	ofParameter<float>* z;
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



	ofxTextField selected_object_name_field;

	vector<ofParameter<float>*> trans_sliders_pointer;
	vector<ofParameter<float>*> rot_sliders_pointer;
	vector<ofParameter<float>*> scale_sliders_pointer;

public:

	void setup();
	void draw();
	void update();
	void exit();

	void changeFocus(const Object* Object = nullptr);
	bool addObject();
	bool removeObject();

	const vector<ofParameter<float>*> getPositionSliderValues();
	const vector<ofParameter<float>*> getRotationSliderValues();
	const vector<ofParameter<float>*> getScaleSliderValues();

	ofVec3f* setPositionSliderValues();
	ofVec3f* setRotationSliderValues();
	ofVec3f* setScaleSliderValues();


};


