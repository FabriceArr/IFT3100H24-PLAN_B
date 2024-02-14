#include "scene.h"
#include <algorithm>

void Scene::setup(const vector<ofParameter<float>*> UIposition,
	const vector<ofParameter<float>*> UIrot,
	const vector<ofParameter<float>*> UIscale)
{
	object_tree_head = new ObjNode(nullptr);


	origin_pos = { 0, 0, 0 };
	//selected_object = &cursor;
	scene_content = new vector<Object*>();
	selected_object = nullptr;

	//sets the pointer to the elements in the UI to keep track of the transforms that are ordered.
	UI_trans_output.push_back(UIposition.at(0));//x
	UI_trans_output.push_back(UIposition.at(1));//y
	UI_trans_output.push_back(UIposition.at(2));//z

	UI_rotation_output.push_back(UIrot.at(0));//x
	UI_rotation_output.push_back(UIrot.at(1));//y
	UI_rotation_output.push_back(UIrot.at(2));//z

	UI_scale_output.push_back(UIscale.at(0));//x
	UI_scale_output.push_back(UIscale.at(1));//y
	UI_scale_output.push_back(UIscale.at(2));//z
}

void Scene::draw()
{
	ofDrawGrid(100, 12, false, false, true, false);


	std::vector<Object*>::const_iterator it = scene_content->begin();

	for (std::vector<Object*>::const_iterator it =
		scene_content->begin(); it !=
		scene_content->end(); it++)
	{
		ofLog() << "one drawn";

		if (*it) {
			ofPushMatrix();

			

			ofTranslate(*UI_trans_output.at(0), *UI_trans_output.at(1), *UI_trans_output.at(2));

			ofRotateXDeg(*UI_rotation_output.at(0));
			ofRotateYDeg(*UI_rotation_output.at(1));
			ofRotateZDeg(*UI_rotation_output.at(2));

			ofScale(*UI_scale_output.at(0), *UI_scale_output.at(1),*UI_scale_output.at(2));

			(*it)->getObject()->draw();


			ofPopMatrix();
		}


	}

}

void Scene::exit()
{
	//empty them first by iterator for the objects maybe
	scene_content->clear();
	delete scene_content;

	UI_trans_output.clear();
	UI_rotation_output.clear();
	UI_scale_output.clear();
	

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
			Object* plane = new Object(ofPlanePrimitive(), "Plane");
			scene_content->push_back(plane);
		break; 
		}
			

		case 1://cube
		{
			Object* box = new Object(ofBoxPrimitive(), "Cube");

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
					ofLog() << "next object select ordered";
				}
				else {
					//cas normal, selection du suivant
					selected_object = *scene_content->begin();
					ofLog() << "next object select ordered";
				}
			}
			// L'object cherché n'est pas dans la scene... Somehow
			else {
				ofLog() << "next object select not in scene";
			}
			
			
		}
		//elements are in the scene, but no one are currently selected
		//retour du premier element de la scene alors
		else {
			selected_object = scene_content->front();
			ofLog() << "next object select ordered";
		}

	}




}

void Scene::selectPreviousObject()
{
	//std::find(scene_content.begin(), scene_content.end(), selected_object);
}





