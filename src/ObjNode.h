#pragma once
#include "Object.h"


class ObjNode
{
private:
	
	std::vector<ObjNode*> sub_objects;

public:
	Object* object;

	ObjNode* group_master;


	ObjNode(Object* object, ObjNode* master = nullptr);

	void remove();


	void add(ObjNode* objnode);

	std::vector<ObjNode*>* getSubs();

	void destroy_subs();
};

