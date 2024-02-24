#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "scene.h"
#include <vector>

struct parameterVectorGroup {
	ofParameter<float>* x;
	ofParameter<float>* y;
	ofParameter<float>* z;
	ofParameter<ofColor> fill_color_slider;
	ofParameter<ofColor> stroke_color_slider;
};

struct hsv {
	double h;
	double s;
	double v;
};

struct rgb {
	double r;
	double g;
	double b;
};


class UI
{
private:
	Object* holder;
	const Object* selected_object;

	parameterVectorGroup position_slider_group;
	parameterVectorGroup rotation_slider_group;
	parameterVectorGroup scale_slider_group;
    
	ofxTextField selected_object_name_field;

	vector<ofParameter<float>*> trans_sliders_pointer;
	vector<ofParameter<float>*> rot_sliders_pointer;
	vector<ofParameter<float>*> scale_sliders_pointer;

	ofParameter<int> stroke_width_slider;

	ofParameter<ofColor> fill_color_slider;
	ofParameter<ofColor> stroke_color_slider;

	ofParameter<float> h_slider_fill;
	ofParameter<float> s_slider_fill;
	ofParameter<float> v_slider_fill;

	ofParameter<float> h_slider_stroke;
	ofParameter<float> s_slider_stroke;
	ofParameter<float> v_slider_stroke;

	hsv rgbToHSV(ofColor color);
	ofColor hsvToRGB(hsv hsvColor);

	void fillColorRGBChanged(ofColor& color);
	void strokeColorRGBChanged(ofColor& color);

	void hueChanged_fill(float& value);
	void saturationChanged_fill(float& value);
	void valueChanged_fill(float& value);

	void hueChanged_stroke(float& value);
	void saturationChanged_stroke(float& value);
	void valueChanged_stroke(float& value);

public:
	ofxPanel interface;
	void setup();
	void draw();
	void update();
	void exit();

	void changeFocus(const Object* Object = nullptr);

	const vector<ofParameter<float>*> getPositionSliderValues();
	const vector<ofParameter<float>*> getRotationSliderValues();
	const vector<ofParameter<float>*> getScaleSliderValues();
	const ofParameter<ofColor> getFillColorSlider();	
	const ofParameter<ofColor> getStrokeColorSlider();
	const ofParameter<int> getStrokeWidthSlider();

	ofVec3f* setPositionSliderValues();
	ofVec3f* setRotationSliderValues();
	ofVec3f* setScaleSliderValues();

	void setHSVSlidersFromRGB(ofColor rgbColor, bool isFillColor);
};


