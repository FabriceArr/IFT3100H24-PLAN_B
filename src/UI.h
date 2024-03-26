#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxDropdown.h"
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

	ofParameter<ofColor> background_color_slider;

	ofParameter<float> h_slider_background;
	ofParameter<float> s_slider_background;
	ofParameter<float> v_slider_background;

	parameterVectorGroup position_slider_group;
	parameterVectorGroup rotation_slider_group;
	parameterVectorGroup scale_slider_group;
    
	ofxTextField selected_object_name_field;

	vector<ofParameter<float>*> trans_sliders_pointer;
	vector<ofParameter<float>*> rot_sliders_pointer;
	vector<ofParameter<float>*> scale_sliders_pointer;

	ofParameter<int> stroke_width_slider;

	ofParameter<ofColor> fill_color_slider;

	// Illumination Model with dropdown
	ofxDropdown_<string> IlluminationModel_dropdown;
	unsigned int illuminationModel_dropdown_selected = 0;
	vector<string> illuminationModel_vector{ "Flat","Lambert", "Gouraud", "Phong", "Blinn-Phong"};

	ofParameter<ofColor> color_picker;


	// Image Filter with dropdown
	ofxDropdown_<string> imageFilter_dropdown;
	unsigned int imageFilter_dropdown_selected = 0;
	vector<string> filter_vector{ "Aucun","Bilinéaire", "Trilinéaire", "Anistropique"};

	ofParameter<ofColor> stroke_color_slider;

	ofParameter<float> h_slider_fill;
	ofParameter<float> s_slider_fill;
	ofParameter<float> v_slider_fill;

	ofParameter<float> h_slider_stroke;
	ofParameter<float> s_slider_stroke;
	ofParameter<float> v_slider_stroke;
	

	hsv rgbToHSV(ofColor color);
	ofColor hsvToRGB(hsv hsvColor);
	ofxIntField intInputPoint1X;
	ofxIntField intInputPoint1Y;
	ofxIntField intInputPoint1Z;
	ofxIntField intInputPoint2X;
	ofxIntField intInputPoint2Y;
	ofxIntField intInputPoint2Z;
	ofxIntField intInputPoint3X;
	ofxIntField intInputPoint3Y;
	ofxIntField intInputPoint3Z;

	ofxIntField intInputRadiusX;
	ofxIntField intInputRadiusY;

	ofVec3f point1_values;
	ofVec3f point2_values;
	ofVec3f point3_values;
	ofVec3f radius_values;

	ofxGuiGroup group_point;

	ofxGuiGroup group_tone_mapping;
	ofParameter<float> slider_exposure;
	ofParameter<float> slider_gamma;
	ofParameter<bool> toggle_tone_mapping;

	float tone_mapping_exposure;
	float tone_mapping_gamma;
	bool tone_mapping_toggle;


	ofParameter<ofColor> slider_ambiant_color;
	ofParameter<ofColor> slider_diffuse_color;
	ofParameter<ofColor> slider_emissive_color;
	ofParameter<ofColor> slider_specular_color;
	ofParameter<float> slider_shininess;

	float material_shininess;
	ofMaterial material;

	ofxGuiGroup group_material;


	void fillColorRGBChanged(ofColor& color);
	void onIllumModelChangeStr(string& illum);
	void onFilterChangeStr(string& filter);
	void strokeColorRGBChanged(ofColor& color);
	void backgroundColorRGBChanged(ofColor& color);

	void hueChanged_background(float& value);
	void saturationChanged_background(float& value);
	void valueChanged_background(float& value);

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

	const ofVec3f UI::getPoint1Values();
	const ofVec3f UI::getPoint2Values();
	const ofVec3f UI::getPoint3Values();

	const ofVec3f UI::getRadiusValues();

	const vector<ofParameter<float>*> getPositionSliderValues();
	const vector<ofParameter<float>*> getRotationSliderValues();
	const vector<ofParameter<float>*> getScaleSliderValues();
	const ofParameter<ofColor> getBackgroundColorSlider();
	const ofParameter<ofColor> getFillColorSlider();	
	const ofParameter<ofColor> getStrokeColorSlider();
	const ofParameter<int> getStrokeWidthSlider();

	const unsigned int get_illuminationModel();

	const unsigned int getFilter();

	ofVec3f* setPositionSliderValues();
	ofVec3f* setRotationSliderValues();
	ofVec3f* setScaleSliderValues();

	float* setExposureSlider();
	float* setGammaSlider();
	bool* setToneMappingToggle();
	
	ofParameter<float>* getExposureSlider();
	ofParameter<float>* getGammaSlider();
	ofParameter<bool>* getToneMappingToggle();

	ofMaterial* setMaterial();
	ofMaterial* getMaterial();

	void setHSVSlidersFromRGB(ofColor rgbColor, bool isFillColor);
};


