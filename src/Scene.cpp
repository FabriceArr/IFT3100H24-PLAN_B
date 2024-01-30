#include "scene.h"

void Scene::setup()
{
	origin_pos = { 0, 0, 0 };
	//selected_object = &cursor;
	selected_object = nullptr;
}

void Scene::exit()
{
	
}

const list<Object> Scene::getSceneContent()
{
	return scene_content;
}

void Scene::createObject(int type, ofVec3f angle)
{
	switch (type)
	{
		case 0://plane
		{
			ofPlanePrimitive plane;
			scene_content.push_front(plane);
		break; 
		}
			

		case 1://cube
		{
			ofBoxPrimitive box;
			scene_content.push_front(box);
			break;
		}

		default:
			break;

	}
}

void Scene::moveObject(unsigned int object_id, ofVec3f position_change)
{
}

void Scene::rotateObject(unsigned int object_id, ofVec3f rotation_change)
{
}

Object* Scene::get_selected_object()
{
	return selected_object;
}
