#include "scene.h"
#include <algorithm>

void Scene::setup()
{
	origin_pos = { 0, 0, 0 };
	//selected_object = &cursor;
	selected_object = nullptr;
}

void Scene::exit()
{
	
}

const std::vector<Object>* Scene::getSceneContent()
{
	return &scene_content;
}

void Scene::createObject(int type, ofVec3f angle)
{
	switch (type)
	{
		case 0://plane
		{
			ofPlanePrimitive plane;
			scene_content.push_back(plane);
		break; 
		}
			

		case 1://cube
		{
			ofBoxPrimitive box;
			scene_content.push_back(box);
			break;
		}

		default:
			break;

	}
}

void Scene::moveObject(unsigned int object_id, ofVec3f position_change)
{
	//apply changes to object mesh permanently 
}

void Scene::rotateObject(unsigned int object_id, ofVec3f rotation_change)
{
	//apply changes to object mesh permanently 
}

Object* Scene::getSelectedObject()
{
	return selected_object;
}

void Scene::selectNextObject()
{
	/*
	//Is there an element to choose in the scene? If not do nothing
	if (scene_content.size() > 0) {
		//finds the currently selected object in the scene's content if there is an object
		//!!TAKES INTO ACCOUNT THAT THE SELECTED OBJECT HASNT BEEN REMOVED SOMEHOW
		if (selected_object != nullptr) {
			
			auto result = std::find(
				&scene_content.begin(), &scene_content.end(), selected_object);
			//le resultat est le dernier element de la liste
			//retour du front comme suivant.
			if (result == &scene_content.end() - 1) {
				selected_object = &(*scene_content.begin());
			}
			else {
				//cas normal, selection du suivant
				selected_object = &(*scene_content.begin());
			}
			
		}
		//elements are in the scene, but no one are currently selected
		//retour du premier element de la scene alors
		else {
			selected_object = &scene_content.front();
		}

	}
	
	*/




}

void Scene::selectPreviousObject()
{
	//std::find(scene_content.begin(), scene_content.end(), selected_object);
}


