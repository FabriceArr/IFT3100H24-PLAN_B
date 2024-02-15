#include "scene.h"
#include <algorithm>

void Scene::setup(const vector<ofParameter<float>*> UIposition,
	const vector<ofParameter<float>*> UIrot,
	const vector<ofParameter<float>*> UIscale)
{
	//Doit etre le SEUL object initialiser comme ceci
	object_tree_head = new ObjNode(nullptr);


	origin_pos = { 0, 0, 0 };

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


	for (std::vector<ObjNode*>::const_iterator it =
		object_tree_head->getSubs()->begin() ; it !=
		object_tree_head->getSubs()->end(); it++)
	{
		ofLog() << "one drawn";

		if (*it) {

			//only apply transform if selected
			//draw others normally

			//transform selected on rot and scales from the point of (*it)->object->getObject()->getGlobalPosition(); ((x1+x2+x3)/3, (y1+y2+y3)/3, (z1+z2+z3)/3)

			ofPushMatrix();

			

			ofTranslate(*UI_trans_output.at(0), *UI_trans_output.at(1), *UI_trans_output.at(2));

			ofRotateXDeg(*UI_rotation_output.at(0));
			ofRotateYDeg(*UI_rotation_output.at(1));
			ofRotateZDeg(*UI_rotation_output.at(2));

			ofScale(*UI_scale_output.at(0), *UI_scale_output.at(1),*UI_scale_output.at(2));

			(*it)->object->getObject()->draw();


			ofPopMatrix();
		}


	}

}

void Scene::drawSubObjects(std::vector<Object*>* subVector) {

}

void Scene::exit()
{
	//cleans the entire scene
	object_tree_head->destroy_subs();
	
	delete object_tree_head;

	UI_trans_output.clear();
	UI_rotation_output.clear();
	UI_scale_output.clear();
	

}

const ObjNode* Scene::getSceneContent() const
{
	return object_tree_head;
}

void Scene::createObject(int type, ofVec3f angle)
{
	switch (type)
	{
		case 0://plane
		{
			Object* plane = new Object(ofPlanePrimitive(), "Plane");
			object_tree_head->add(new ObjNode(plane, object_tree_head));
		break; 
		}
			

		case 1://cube
		{
			Object* box = new Object(ofBoxPrimitive(), "Cube");
			object_tree_head->add(new ObjNode(box, object_tree_head));
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

const vector<Object*>* Scene::getSelectedObjects() const
{
	return &selected_objects;
}

void Scene::removeObject(ObjNode* objectNode)
{
	objectNode->remove();
}


void Scene::selectNextObject()
{
	//Is there an element to choose in the scene? If not do nothing
	/*
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
	*/




}

void Scene::selectPreviousObject()
{
	//std::find(scene_content.begin(), scene_content.end(), selected_object);
}





