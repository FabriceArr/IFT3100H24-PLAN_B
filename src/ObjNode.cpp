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
			(*it)->remove();
			sub_objects.erase(it);
		}
	}
	if (object != nullptr) {
		delete object;
		group_master = nullptr;
	}
}

void ObjNode::draw(bool selected)
{
	if (this->object != nullptr) {
		this->object->draw(selected);
	}
	for (auto it = begin(sub_objects); it != end(sub_objects); it++) {
		//place tous les object vers pointer l'object
		if ((*it)->object != nullptr) {
			(*it)->object->drawSub(selected);
		}
		
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
