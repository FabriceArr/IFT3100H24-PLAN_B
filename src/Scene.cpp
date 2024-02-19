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

	select_mode.Init(ofGetWindowWidth(), ofGetWindowHeight());


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


			PickingPhase(project_matrice, view_matrice);

			ofPushMatrix();

			ofTranslate(*UI_trans_output.at(0), *UI_trans_output.at(1), *UI_trans_output.at(2));

			ofRotateXDeg(*UI_rotation_output.at(0));
			ofRotateYDeg(*UI_rotation_output.at(1));
			ofRotateZDeg(*UI_rotation_output.at(2));

			ofScale(*UI_scale_output.at(0), *UI_scale_output.at(1),*UI_scale_output.at(2));

			ofMatrix4x4 W = ofGetCurrentMatrix(OF_MATRIX_MODELVIEW);
			(*it)->object->addChange(W);
			
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
	return &selected_object;
}

void Scene::removeObject(ObjNode* objectNode)
{
	objectNode->remove();
}


void Scene::selectNextObject()
{
	




}

void Scene::selectPreviousObject()
{
	//std::find(scene_content.begin(), scene_content.end(), selected_object);
}

void Scene::PickingPhase(ofMatrix4x4 projectM, ofMatrix4x4 viewM)
{
	select_mode.EnableWriting();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (std::vector<ObjNode*>::const_iterator it =
		object_tree_head->getSubs()->begin(); it !=
		object_tree_head->getSubs()->end(); it++)
	{
		// Background is zero, the real objects start at 1

		ofMatrix4x4 World = (*it)->object->getCurrentChangeM();
		ofMatrix4x4 WVP = projectM * viewM * World;
		select_mode.SetWVP(WVP);
		select_mode.SetObjPointer(reinterpret_cast<unsigned int>((*it)->object));
		//turns on the clickshader
		select_mode.enable();

		(*it)->object->getObject()->draw();

		//turns on the clickshader so the next WVP and item pointer can be loaded
		select_mode.disable();
	}

	select_mode.DisableWriting();
}

void Scene::findSelectedObject(int x, int y) {
	//need to invert the y since the coord of textures are opeosite of the ones of screen pixels
	ofLog() << select_mode.ReadPixel(x, ofGetWindowHeight() - y - 1);
}




