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

	//the default object level selection is the scene
	sub_level_selected = object_tree_head->getSubs();
	//set at -1 puisque pas d'objet selectionner
	selected_obj_ind = -1;

	isOrtho = false;
	wasDragging = false;

	animate = false;
	//anim_shader_rot.load("rotateony_vs.glsl");
	//bool i = anim_shader_rot.isLoaded();
}

void Scene::draw()
{
	isOrtho ? ofDrawGrid(100, 12, false, false, false, true) :
		ofDrawGrid(100, 12, false, false, true, false);

	for (std::vector<ObjNode*>::const_iterator it =
		object_tree_head->getSubs()->begin() ; it !=
		object_tree_head->getSubs()->end(); it++)
	{
		ofLog() << object_tree_head->getSubs()->size();
		if (*it) {

			//only apply transform if selected
			//draw others normally
			

			PickingPhase(project_matrice, view_matrice);


			ofPushMatrix();

			//applies the ui changes only for the selected object, 
			//combining the current ui changes to the last change saved
			if ((*it)->object == getSelectedObjects()) {
				ofTranslate(
					*UI_trans_output.at(0) + (*it)->object->getCurrentChangeM().a,
					*UI_trans_output.at(1) + (*it)->object->getCurrentChangeM().b,
					*UI_trans_output.at(2) + (*it)->object->getCurrentChangeM().c);
				ofRotateXDeg(
					*UI_rotation_output.at(0) + (*it)->object->getCurrentChangeM().d);
				ofRotateYDeg(
					*UI_rotation_output.at(1) + (*it)->object->getCurrentChangeM().e);
				ofRotateZDeg(
					*UI_rotation_output.at(2) + (*it)->object->getCurrentChangeM().f);
				ofScale(
					*UI_scale_output.at(0) * (*it)->object->getCurrentChangeM().g,
					*UI_scale_output.at(1) * (*it)->object->getCurrentChangeM().h,
					*UI_scale_output.at(2) * (*it)->object->getCurrentChangeM().i);
			}
			//not the selected object, then we apply the 
			else {
				ofTranslate(
					(*it)->object->getCurrentChangeM().a,
					(*it)->object->getCurrentChangeM().b,
					(*it)->object->getCurrentChangeM().c);
				ofRotateXDeg(
					(*it)->object->getCurrentChangeM().d);
				ofRotateYDeg(
					(*it)->object->getCurrentChangeM().e);
				ofRotateZDeg(
					(*it)->object->getCurrentChangeM().f);
				ofScale(
					(*it)->object->getCurrentChangeM().g,
					(*it)->object->getCurrentChangeM().h,
					(*it)->object->getCurrentChangeM().i);
			}
			
			//object is drawn
			//transform selected on rot and scales from the point of (*it)->object->getObject()->getGlobalPosition(); ((x1+x2+x3)/3, (y1+y2+y3)/3, (z1+z2+z3)/3)
			if (animate) {
				//ofLog() << "Time: " << fmod((ofGetElapsedTimef() * 100), 360);
				//ofLog() << "Time: " << sin(ofGetElapsedTimef());
				ofTranslate(0.0f, sin(ofGetElapsedTimef()), 0.0f);
				ofRotateYDeg(fmod((ofGetElapsedTimef() * 100), 360));
			}
			(*it)->object->draw();

			//object is drawn
			//transform selected on rot and scales from the point of (*it)->object->getObject()->getGlobalPosition(); ((x1+x2+x3)/3, (y1+y2+y3)/3, (z1+z2+z3)/3)
			if (animate) {
				anim_shader_rot.end();
				//anim_shader_bob.end();
			}


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

	delete sub_level_selected;

	//anim_shader_rot.unload();
	//anim_shader_bob.unload();

}

const ObjNode* Scene::getSceneContent() const
{
	return object_tree_head;
}

void Scene::createObject(bool i)
{
	if(i){
		getSelectedObjectsNode()->add(new ObjNode(new Object(
			"cube",
			this->UI_fill_color.get())
			, object_tree_head
		));

	}
	else {

		getSelectedObjectsNode()->add(new ObjNode(new Object(
			"plane",
			this->UI_fill_color.get())
			, object_tree_head
		));
	}
}

void Scene::createImportedObject3D(string path) {
	if (path.substr(path.length() - 4, 4) == ".obj") {
		ofMesh mesh = OBJLoader::loadMeshOBJ(path);
		getSelectedObjectsNode()->add(new ObjNode(new Object(
			"Imported",
			mesh
		), object_tree_head));
	}
	else {
		ofxAssimpModelLoader model;
		model.loadModel(path, true);
		getSelectedObjectsNode()->add(new ObjNode(new Object(
			model.getMeshNames().at(0),
			model.getMesh(0)
		), object_tree_head));
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

void Scene::changeSelectedMatrice(ofMatrix3x3 change)
{
	//updates the selected object to be stored in the fonction setting to make the if work
	updateSelectedObjects();
	if (getSelectedObjects() != nullptr) {
		selected_object->object->addChange(change);

		ofLog() << endl;
		ofLog() << "--------------------------------------------------";
		ofLog() << " | " << change.a << " | " << change.b << " | " << change.c << " | " << endl;
		ofLog() << "--------------------------------------------------";
		ofLog() << " | " << change.d << " | " << change.e << " | " << change.f << " | " << endl;
		ofLog() << "--------------------------------------------------";
		ofLog() << " | " << change.g << " | " << change.h << " | " << change.i << " | " << endl;
		ofLog() << "--------------------------------------------------";
		ofLog() << endl;

		if (selected_object->getSubs()->size() > 0) {

		}
	}
}

void Scene::updateFillColor(ofParameter<ofColor> colorparam)
{
	this->UI_fill_color = colorparam;
}

void Scene::updateSelectedObjects()
{
	if (getSelectedObjects() != nullptr) {
		selected_object = sub_level_selected->at(selected_obj_ind);
	}
}

 Object* Scene::getSelectedObjects()
{
	if (selected_obj_ind >= 0) {
		return sub_level_selected->at(selected_obj_ind)->object;
	}
	else
		return nullptr;
}

 ObjNode* Scene::getSelectedObjectsNode()
 {
	 if (selected_obj_ind >= 0) {
		 return sub_level_selected->at(selected_obj_ind);
	 }
	 else
		 return object_tree_head;
 }

void Scene::removeObject()
{
	if (getSelectedObjects() != nullptr) {
		sub_level_selected->at(selected_obj_ind)->remove();
		sub_level_selected->erase(sub_level_selected->begin() + selected_obj_ind);
	}
	
}


void Scene::selectNextObject()
{
	if (!(selected_obj_ind < 0) && sub_level_selected->size() > 0) {
		if (selected_obj_ind < sub_level_selected->size() - 1) {
			//current isnt the last, cant change to next in vector of pointers
			selected_obj_ind++;
		}
		else{
			//the current is currently the last, send back to first
			selected_obj_ind = 0;
		}
	}
	else {
		//no obj currently selected, is there any object on scene?
		if(sub_level_selected->size() > 0)
		{
			//yes there is, set it to the first one
			selected_obj_ind = 0;
		}
		
	}
	ofLog()<< "Currently selected item : " << selected_obj_ind;
}

void Scene::selectPreviousObject()
{
	if (!(selected_obj_ind < 0)) {
		if (selected_obj_ind > 0) {
			//current is not first
			selected_obj_ind--;
		}
		else {
			//is the first, put at last
			selected_obj_ind = sub_level_selected->size() - 1;
		}
	}
	else {
		//no obj currently selected, is there any object on scene?
		if (sub_level_selected->size() > 0)
		{
			//yes there is, set it to the last one
			selected_obj_ind = sub_level_selected->size() - 1;
		}

	}
	ofLog() << "Currently selected item : " << selected_obj_ind;
}

void Scene::selectParentObject()
{
	sub_level_selected = object_tree_head->getSubs();
}

void Scene::selectSubsObject()
{
	//Is there a selected object?
	if (getSelectedObjects() != nullptr) {
		//check if it is the default, since its parent is nullptr
		//need to do 2 parent, since from default, the first is simply the treehead
		if (sub_level_selected->at(selected_obj_ind)->group_master) {

			//need to go up by two
			sub_level_selected = sub_level_selected->at(selected_obj_ind)->getSubs();
			//deselect since we are in a new layer, so we can create object there
			deSelectObject();
		}
	}
}

void Scene::deSelectObject()
{
	selected_obj_ind = -1;
}

void Scene::savechange()
{
	if (getSelectedObjects() != nullptr) {
		info.set(
			*UI_trans_output.at(0) + getSelectedObjects()->getCurrentChangeM().a,//a translation x
			*UI_trans_output.at(1) + getSelectedObjects()->getCurrentChangeM().b,//b translation y
			*UI_trans_output.at(2) + getSelectedObjects()->getCurrentChangeM().c,//c translation z
			*UI_rotation_output.at(0) + getSelectedObjects()->getCurrentChangeM().d,//d rotation x
			*UI_rotation_output.at(1) + getSelectedObjects()->getCurrentChangeM().e,//e rotation y
			*UI_rotation_output.at(2) + getSelectedObjects()->getCurrentChangeM().f,//f rotation z
			*UI_scale_output.at(0) * getSelectedObjects()->getCurrentChangeM().g,//g scale x
			*UI_scale_output.at(1) * getSelectedObjects()->getCurrentChangeM().h,//h scale y
			*UI_scale_output.at(2) * getSelectedObjects()->getCurrentChangeM().i);//i scale z

		getSelectedObjects()->addChange(info);
	}
}

void Scene::PickingPhase(ofMatrix4x4 projectM, ofMatrix4x4 viewM)
{
	/*select_mode.EnableWriting();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (std::vector<ObjNode*>::const_iterator it =
		object_tree_head->getSubs()->begin(); it !=
		object_tree_head->getSubs()->end(); it++)
	{
		// Background is zero, the real objects start at 1

		ofMatrix4x4 World = (*it)->object->getCurrentChangeM();
		ofMatrix4x4 WVP = projectM * viewM * World;
		select_mode.SetWVP(WVP);
		select_mode.SetObjPointer(1);
		//turns on the clickshader
		select_mode.enable();

		(*it)->object->getObject()->draw();

		//turns off the clickshader so the next WVP and item pointer can be loaded
		select_mode.disable();
	}

	select_mode.DisableWriting();
	*/
}

void Scene::findSelectedObject(int x, int y) {
	//need to invert the y since the coord of textures are opeosite of the ones of screen pixels
	ofLog() << select_mode.ReadPixel(x, ofGetWindowHeight() - y - 1);
}




