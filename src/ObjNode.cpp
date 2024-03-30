#include "ObjNode.h"




ObjNode::ObjNode(Object* object, ObjNode* master)
{
	this->object = object;

	//if nullptr, then is head of scene, if is nullptr and not head, its lost :(
	group_master = master;

	this->sub_objects = vector<ObjNode*>();
	trans = rot = sca = nullptr;
	sub_groupe_stage = 0;

	
}


//removes this node, not other ones
void ObjNode::remove()
{
	//check if nullptr since scene origine node is nullptr
	if (group_master != nullptr) {
		for (auto it = begin(sub_objects); it != end(sub_objects); it++) {
			//place tous les object vers pointer l'object
			(*it)->remove();
		}
	}
	if (object != nullptr) {
		delete object;
		group_master = nullptr;
	}
}

void ObjNode::draw(bool selected, bool animated)
{
	bool selectedpasser = selected;
	ofMatrix3x3 hold = this->object->getCurrentChangeM();
	ofTranslate(
		hold.a,
		hold.b,
		hold.c);
	ofRotateXDeg(
		hold.d);
	ofRotateYDeg(
		hold.e);
	ofRotateZDeg(
		hold.f);
	ofScale(
		hold.g,
		hold.h,
		hold.i);

	if (trans != nullptr && rot != nullptr && sca != nullptr)
	{
		this->object->setColor(color);
		this->object->setStrokeColor(stroke_color);
		this->object->setStrokeWidth(stroke_width);
		this->object->setToneMapping(*this->exposure, *this->gamma, *this->tone_mapping);
		
		ofTranslate(*this->trans->at(0), *this->trans->at(1), *this->trans->at(2));
		ofRotateXDeg(*this->rot->at(0));
		ofRotateYDeg(*this->rot->at(1));
		ofRotateZDeg(*this->rot->at(2));
		ofScale(*this->sca->at(0), *this->sca->at(1), *this->sca->at(2));
		selectedpasser = true;
	}
	if (this->object != nullptr) {
		this->object->draw(selectedpasser, animated, sub_groupe_stage);
	}
	for (auto it = begin(sub_objects); it != end(sub_objects); it++) {
		
		if ((*it)->object != nullptr) {
			(*it)->increaseSubStage();
			(*it)->draw(selectedpasser, animated);
		}
		
	}

	//resets the pointers
	if (trans != nullptr && rot != nullptr && sca != nullptr)
	{
		sca = rot = trans = nullptr;
	}
	
}

bool ObjNode::isSelected(ofVec3f origin, ofVec3f direction)
{
	return RayCaster::CastRay(origin, direction, 
								this->object->getObbMin(),
								this->object->getObbMax(),
								this->object->getCurrentChangeM());
}



//adds a child to this one
void ObjNode::add(ObjNode* objnode)
{
	this->sub_objects.push_back(objnode);
}

 std::vector<ObjNode*>* ObjNode::getSubs()
{
	return &(this->sub_objects);
}



void ObjNode::destroy_subs()
{
	for (auto it = begin(sub_objects); it != end(sub_objects); it++) {
		//place tous les object vers pointer l'object
		(*it)->group_master = this->group_master;
	}
}

void ObjNode::setAsSelected(vector<ofParameter<float>*>* trans, vector<ofParameter<float>*>* rot, vector<ofParameter<float>*>* sca)
{
	this->trans = trans;
	this->rot = rot;
	this->sca = sca;
}

void ObjNode::setToneMapping(ofParameter<float>* exposure,ofParameter<float>* gamma,ofParameter<bool>* tone_mapping)
{
	this->exposure = exposure;
	this->gamma = gamma;
	this->tone_mapping = tone_mapping;
}

void ObjNode::setFillColor(ofParameter<ofColor> colorparam) {
	this->color = colorparam;
}

void ObjNode::setStrokeColor(ofParameter<ofColor> colorparam)
{
	this->stroke_color = colorparam;
}

void ObjNode::setStrokeWidth(ofParameter<int> widthparam)
{
	this->stroke_width = widthparam;
}

void ObjNode::setIllumModel(ofParameter<int> illumparam)
{
	this->illumModel_setting = illumparam;
}

void ObjNode::setFilter(unsigned int filterparam)
{
	this->filter = filterparam;
}

void ObjNode::increaseSubStage()
{
	this->sub_groupe_stage++;
	ofLog() << sub_groupe_stage;
}

void ObjNode::resetSubStage()
{
	this->sub_groupe_stage = 0;
	for (auto it = begin(sub_objects); it != end(sub_objects); it++) {

		(*it)->resetSubStage();

	}
}
