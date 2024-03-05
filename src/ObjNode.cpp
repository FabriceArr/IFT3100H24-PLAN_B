#include "ObjNode.h"

ObjNode::ObjNode(Object* object, ObjNode* master)
{
	this->object = object;

	//if nullptr, then is head of scene, if is nullptr and not head, its lost :(
	group_master = master;

	this->sub_objects = vector<ObjNode*>();
	trans = rot = sca = nullptr;
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
	bool selectedpasser = selected;
	if (trans != nullptr && rot != nullptr && sca != nullptr)
	{
		
		ofTranslate(*this->trans->at(0), *this->trans->at(1), *this->trans->at(2));
		ofRotateXDeg(*this->rot->at(0));
		ofRotateYDeg(*this->rot->at(1));
		ofRotateZDeg(*this->rot->at(2));
		ofScale(*this->sca->at(0), *this->sca->at(1), *this->sca->at(2));
		selectedpasser = true;
	}
	if (this->object != nullptr) {
		this->object->draw(selectedpasser, animated);
	}
	for (auto it = begin(sub_objects); it != end(sub_objects); it++) {
		
		if ((*it)->object != nullptr) {
			(*it)->draw(selectedpasser, animated);
		}
		
	}

	//resets the pointers
	if (trans != nullptr && rot != nullptr && sca != nullptr)
	{
		sca = rot = trans = nullptr;
	}
	
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
