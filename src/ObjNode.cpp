#include "ObjNode.h"

ObjNode::ObjNode(Object* object, ObjNode* master)
{
	this->object = object;

	//if nullptr, then is head of scene, if is nullptr and not head, its lost :(
	group_master = master;

	this->sub_objects = vector<ObjNode*>();
}


//removes this node, not other ones
void ObjNode::remove()
{
	//check if nullptr since scene origine node is nullptr
	if (group_master != nullptr) {
		for (auto it = begin(sub_objects); it != end(sub_objects); it++) {
			//place tous les object vers pointer l'object
			(*it)->group_master = this->group_master;
		}
	}
	if (object != nullptr) {
		delete object;
	}
}

//adds a child to this one
void ObjNode::add(ObjNode* objnode)
{
	this->sub_objects.push_back(objnode);
}

const std::vector<ObjNode*>* ObjNode::getSubs() const
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
