#pragma once
#include "Object.h"


class ObjNode
{
private:
	
	std::vector<ObjNode*> sub_objects;
	vector<ofParameter<float>*>* trans, *rot, *sca;
	ofParameter<ofColor> color;
	unsigned int sub_groupe_stage;

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

	void setFillColor(ofParameter<ofColor> colorparam);

	

	void resetSubStage();
};

