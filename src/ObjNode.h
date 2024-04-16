#pragma once
#include "Object.h"
#include "RayCaster.h"


class ObjNode
{
private:
	
	std::vector<ObjNode*> sub_objects;
	vector<ofParameter<float>*>* trans, *rot, *sca;
	ofParameter<ofColor> color, stroke_color;
	ofParameter<int> stroke_width;
	unsigned int sub_groupe_stage;
	ofParameter<float> *exposure;
	ofParameter<float> *gamma;
	ofParameter<bool> *tone_mapping;
	ofParameter<int> illumModel_setting;
	ofParameter<int> *illumModel_setting;
	//unsigned int filter;
	ofParameter<ofColor>* ambiantColor;
	ofParameter<ofColor>* diffuseColor;
	ofParameter<ofColor>* specularColor;
	ofParameter<ofColor>* emissiveColor;
	ofParameter<float>* shininess;

	void increaseSubStage();

public:
	Object* object;

	ObjNode* group_master;


	ObjNode(Object* object, ObjNode* master = nullptr);

	void remove();

	void draw(bool selected = false, bool animated = false);

	bool isSelected(ofVec3f origin, ofVec3f direction, float &distance);

	void add(ObjNode* objnode);

	std::vector<ObjNode*>* getSubs();

	void destroy_subs();

	void setAsSelected(vector<ofParameter<float>*>* trans, vector<ofParameter<float>*>* rot, vector<ofParameter<float>*>* sca);
	void setToneMapping(ofParameter<float>* exposure, ofParameter<float>* gamma, ofParameter<bool>* tone_mapping);
	void setAmbiantColor(ofParameter<ofColor>* color);
	void setDiffuseColor(ofParameter<ofColor>* color);
	void setSpecularColor(ofParameter<ofColor>* color);
	void setEmissiveColor(ofParameter<ofColor>* color);
	void setShininess(ofParameter<float>* shininess);
	void setFillColor(ofParameter<ofColor> colorparam);
	void setStrokeColor(ofParameter<ofColor> colorparam);
	void setStrokeWidth(ofParameter<int> widthparam);
	void setIllumModel(ofParameter<int>* illumparam);
	//void setFilter(unsigned int filterparam);

	void resetSubStage();
};