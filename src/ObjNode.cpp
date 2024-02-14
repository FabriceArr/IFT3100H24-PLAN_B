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
	for (auto it = begin (sub_objects); it != end(sub_objects); it++) {
		//place tous les object vers pointer l'object
		(*it)->group_master = this->group_master;
	}
}

//adds a child to this one
void ObjNode::add(ObjNode* objnode)
{
	this->sub_objects.push_back(objnode);
}
