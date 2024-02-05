#include "scene.h"
#include <algorithm>

void Scene::setup()
{
	origin_pos = { 0, 0, 0 };
	//selected_object = &cursor;
	scene_content = new vector<Object*>();
	selected_object = nullptr;
}

void Scene::exit()
{
	for (vector<Object*>::const_iterator it = scene_content->begin()
		; it != scene_content->end(); it++)
	{

	}
}

const std::vector<Object*>* Scene::getSceneContent() const
{
	return scene_content;
}

void Scene::createObject(int type, ofVec3f angle)
{
	switch (type)
	{
		case 0://plane
		{
			Object* plane = new Object(ofPlanePrimitive());
			scene_content->push_back(plane);
		break; 
		}
			

		case 1://cube
		{
			Object* box = new Object(ofBoxPrimitive());

			scene_content->push_back(box);
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

const Object* Scene::getSelectedObject() const
{
	return selected_object;
}


void Scene::selectNextObject()
{
	//Is there an element to choose in the scene? If not do nothing
	if (scene_content->size() > 0) {
		//finds the currently selected object in the scene's content if there is an object
		if (selected_object != nullptr) {
			std::vector<Object*>::const_iterator result = std::find(
				scene_content->begin(), scene_content->end(), selected_object);
			if (&result != &scene_content->end()) {
				//le resultat est le dernier element de la liste
			//retour du front comme suivant.
				if (&result == &scene_content->end() - 1) {
					selected_object = *scene_content->begin();
				}
				else {
					//cas normal, selection du suivant
					selected_object = *scene_content->begin();
				}
			}
			// L'object cherché n'est pas dans la scene... Somehow
			//else {}
			
			
		}
		//elements are in the scene, but no one are currently selected
		//retour du premier element de la scene alors
		else {
			selected_object = scene_content->front();
		}

	}




}

void Scene::selectPreviousObject()
{
	//std::find(scene_content.begin(), scene_content.end(), selected_object);
}



