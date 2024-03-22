#pragma once
#include "Object.h"


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
	ofMaterial *material;

	void increaseSubStage();

public:
	Object* object;

	ObjNode* group_master;


	ObjNode(Object* object, ObjNode* master = nullptr);

	void remove();

	void draw(bool selected = false, bool animated = false);

	void add(ObjNode* objnode);

	std::vector<ObjNode*>* getSubs();

	void destroy_subs();

	void setAsSelected(vector<ofParameter<float>*>* trans, vector<ofParameter<float>*>* rot, vector<ofParameter<float>*>* sca);
	void setToneMapping(ofParameter<float>* exposure, ofParameter<float>* gamma, ofParameter<bool>* tone_mapping);
	void setMaterial(ofMaterial* material);
	void setFillColor(ofParameter<ofColor> colorparam);
	void setStrokeColor(ofParameter<ofColor> colorparam);
	void setStrokeWidth(ofParameter<int> widthparam);

	void resetSubStage();
};

