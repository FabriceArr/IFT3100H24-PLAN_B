#include "scene.h"
#include <algorithm>



void Scene::setup(const vector<ofParameter<float>*> UIposition,
	const vector<ofParameter<float>*> UIrot,
	const vector<ofParameter<float>*> UIscale,
	ofParameter<float>* UIExposure,
	ofParameter<float>* UIGamma,
	ofParameter<bool>* UIToneMapping)
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

	UI_exposure = UIExposure;
	UI_gamma = UIGamma;
	UI_tone_mapping = UIToneMapping;

	//select_mode.Init(ofGetWindowWidth(), ofGetWindowHeight());

	//the default object level selection is the scene
	sub_level_selected = object_tree_head->getSubs();
	//set at -1 puisque pas d'objet selectionner
	selected_obj_ind = -1;

	isOrtho = false;
	wasDragging = false;

	animate = false;

}

void Scene::draw()
{
	isOrtho ? ofDrawGrid(100, 12, false, false, false, true) :
		ofDrawGrid(100, 12, false, false, true, false);

	//sets which node will be updated with the ui changes,
	//this is not apply on the main head if non are selected
	//Since it would be a bit of a mess

	object_tree_head->resetSubStage();
	setSelectedNode();

	ofSetColor(52, 52, 52);
	camdebug.draw();
	clickdebug.draw();
	ofDrawLine(camdebug.getGlobalPosition(), clickdebug.getGlobalPosition());
	ofSetColor(255);

	for (std::vector<ObjNode*>::const_iterator it =
		object_tree_head->getSubs()->begin() ; it !=
		object_tree_head->getSubs()->end(); it++)
	{
		if (*it) {

			//only apply transform if selected
			//draw others normally

			ofPushMatrix();
			(*it)->draw(false, animate);
			


			ofPopMatrix();
			
		}


	}

}

void Scene::exit()
{
	//cleans the entire scene
	object_tree_head->destroy_subs();
	
	delete object_tree_head;

	UI_trans_output.clear();
	UI_rotation_output.clear();
	UI_scale_output.clear();

	UI_exposure = nullptr;
	UI_gamma = nullptr;


	delete sub_level_selected;

	anim_shader_rot.unload();
	anim_shader_bob.unload();

}

void Scene::setSelectedNode()
{
	if (getSelectedObjectsNode() != object_tree_head) {
		getSelectedObjectsNode()->setAsSelected(&UI_trans_output, &UI_rotation_output, &UI_scale_output);
		getSelectedObjectsNode()->setFillColor(UI_fill_color);
		getSelectedObjectsNode()->setStrokeColor(UI_stroke_color);
		getSelectedObjectsNode()->setStrokeWidth(UI_stroke_width);
		getSelectedObjectsNode()->setToneMapping(UI_exposure, UI_gamma, UI_tone_mapping);
		getSelectedObjectsNode()->setIllumModel(UI_illumModel);
		getSelectedObjectsNode()->setFilter(UI_filter);
	}
}

const ObjNode* Scene::getSceneContent() const
{
	return object_tree_head;
}

void Scene::createObject(bool i)
{
	if(i){
		getSelectedObjectsNode()->add(new ObjNode(new Element3D(
			"cube",
			this->UI_fill_color.get())
			, getSelectedObjectsNode()
		));

	}
	else {

		getSelectedObjectsNode()->add(new ObjNode(new Element3D(
			"plane",
			this->UI_fill_color.get())
			, getSelectedObjectsNode()
		));
	}
}

void Scene::createImportedObject3D(string path) {
	if (path.substr(path.length() - 4, 4) == ".obj") {
		ofMesh mesh = OBJLoader::loadMeshOBJ(path);
		getSelectedObjectsNode()->add(new ObjNode(new Element3D(
			"Imported",
			mesh
		), getSelectedObjectsNode()));
	}
	else {
		ofxAssimpModelLoader model;
		model.loadModel(path, true);
		getSelectedObjectsNode()->add(new ObjNode(new Element3D(
			model.getMeshNames().at(0),
			model.getMesh(0)
		), getSelectedObjectsNode()));
	}
	

}

void Scene::create2DObject(int i)
{
	if (i == 0) {
		getSelectedObjectsNode()->add(new ObjNode(new Element2DPrimitive(
			"triangle",
			this->UI_fill_color.get(),
			this->UI_stroke_color.get(),
			this->UI_stroke_width.get(),
			this->UI_point1,
			this->UI_point2, 
			this->UI_point3, 
			this->UI_radius),
			getSelectedObjectsNode()
		));
	}
	else if (i == 1) {
		getSelectedObjectsNode()->add(new ObjNode(new Element2DPrimitive(
			"point",
			this->UI_fill_color.get(),
			this->UI_stroke_color.get(),
			this->UI_stroke_width.get(),
			this->UI_point1,
			this->UI_point2,
			this->UI_point3,
			this->UI_radius),
			getSelectedObjectsNode()
		));
	}
	else if (i == 2) {
		getSelectedObjectsNode()->add(new ObjNode(new Element2DPrimitive(
			"ligne",
			this->UI_fill_color.get(),
			this->UI_stroke_color.get(),
			this->UI_stroke_width.get(),
			this->UI_point1,
			this->UI_point2,
			this->UI_point3,
			this->UI_radius),
			getSelectedObjectsNode()
		));
	}
	else if (i == 3) {
		getSelectedObjectsNode()->add(new ObjNode(new Element2DPrimitive(
			"rectangle",
			this->UI_fill_color.get(),
			this->UI_stroke_color.get(),
			this->UI_stroke_width.get(),
			this->UI_point1,
			this->UI_point2,
			this->UI_point3,
			this->UI_radius),
			getSelectedObjectsNode()
		));
	}
	else if (i == 4) {
		getSelectedObjectsNode()->add(new ObjNode(new Element2DPrimitive(
			"ellipse",
			this->UI_fill_color.get(),
			this->UI_stroke_color.get(),
			this->UI_stroke_width.get(),
			this->UI_point1,
			this->UI_point2,
			this->UI_point3,
			this->UI_radius),
			getSelectedObjectsNode()
		));
	}
	else if (i == 5) {
		ObjNode* obj = new ObjNode(new Element2DPrimitive(
			"rectangle",
			this->UI_fill_color.get(),
			this->UI_stroke_color.get(),
			this->UI_stroke_width.get(),
			this->UI_point1,
			this->UI_point2,
			this->UI_point3,
			this->UI_radius), 
			getSelectedObjectsNode());

		getSelectedObjectsNode()->add(obj);

		point1.set(UI_point1.x, UI_point2.y,0);

		obj->add(new ObjNode(new Element2DPrimitive(
			"triangle",
			this->UI_fill_color.get(),
			this->UI_stroke_color.get(),
			this->UI_stroke_width.get(),
			this->point1,
			this->UI_point2,
			this->UI_point3,
			this->UI_radius),
			obj
		));
	}
	else if (i == 6) {
		ObjNode* obj = new ObjNode(new Element2DPrimitive(
			"ligne",
			this->UI_fill_color.get(),
			this->UI_stroke_color.get(),
			this->UI_stroke_width.get(),
			this->UI_point1,
			this->UI_point2,
			this->UI_point3,
			this->UI_radius),
			getSelectedObjectsNode());

		getSelectedObjectsNode()->add(obj);

		point2.set(UI_point1.x, UI_point2.y, 0);
		point3.set(UI_point2.x, UI_point1.y, 0);

		obj->add(new ObjNode(new Element2DPrimitive(
			"ligne",
			this->UI_fill_color.get(),
			this->UI_stroke_color.get(),
			this->UI_stroke_width.get(),
			this->point2,
			this->point3,
			this->UI_point3,
			this->UI_radius),
			obj
		));
	}
	else if (i == 7) {
		
		radius.set(UI_radius.x, UI_radius.x, 0);

		ObjNode* obj = new ObjNode(new Element2DPrimitive(
			"ellipse",
			this->UI_fill_color.get(),
			this->UI_stroke_color.get(),
			this->UI_stroke_width.get(),
			this->UI_point1,
			this->UI_point2,
			this->UI_point3,
			this->radius),
			getSelectedObjectsNode()
		);

		getSelectedObjectsNode()->add(obj);

		point3.set(UI_point1.x + (radius.x /2), UI_point1.y, 0);
		radius.set(UI_radius.x, UI_radius.x, 0);

		obj->add(new ObjNode(new Element2DPrimitive(
			"ellipse",
			this->UI_fill_color.get(),
			this->UI_stroke_color.get(),
			this->UI_stroke_width.get(),
			this->point3,
			this->UI_point2,
			this->UI_point3,
			this->radius),
			obj
		));

		point3.set(UI_point1.x + (radius.x / 2), UI_point1.y - (radius.x / 2), 0);
		radius.set(UI_radius.x, UI_radius.x, 0);

		obj->add(new ObjNode(new Element2DPrimitive(
			"ellipse",
			this->UI_fill_color.get(),
			this->UI_stroke_color.get(),
			this->UI_stroke_width.get(),
			this->point3,
			this->UI_point2,
			this->UI_point3,
			this->radius),
			obj
		));

		point3.set(UI_point1.x, UI_point1.y - (radius.x / 2), 0);
		radius.set(UI_radius.x, UI_radius.x, 0);

		obj->add(new ObjNode(new Element2DPrimitive(
			"ellipse",
			this->UI_fill_color.get(),
			this->UI_stroke_color.get(),
			this->UI_stroke_width.get(),
			this->point3,
			this->UI_point2,
			this->UI_point3,
			this->radius),
			obj
		));
		}
}

void Scene::createImportedObject2D(string path) {
	ofImage imageImport;
	// importer le premier fichier déposé sur la fenêtre si c'est une image (attention : aucune validation du type de fichier)
	imageImport.load(path);

	getSelectedObjectsNode()->add(new ObjNode(new Element2D(
		"Imported",
		path
	), getSelectedObjectsNode()));

}

void Scene::changeSelectedMatrice(ofMatrix3x3 change)
{
	//updates the selected object to be stored in the fonction setting to make the 
	// if work
	updateSelectedObjects();
	if (getSelectedObjects() != nullptr) {
		selected_object->object->addChange(change);
	}
}

void Scene::updateFillColor(ofParameter<ofColor> colorparam)
{
	this->UI_fill_color = colorparam;
}

void Scene::updateStrokeColor(ofParameter<ofColor> colorparam)
{
	this->UI_stroke_color = colorparam;
}

void Scene::updateStrokeWidth(ofParameter<int> widthparam)
{
	this->UI_stroke_width = widthparam;
}

void Scene::updateIllumModel(unsigned int illumparam)
{
	this->UI_illumModel = illumparam;
}

void Scene::updateFilter(unsigned int filterparam)
{
	this->UI_filter = filterparam;
}

void Scene::updatePoint1(const ofVec3f point1)
{
	UI_point1 = point1;
}

void Scene::updatePoint2(const ofVec3f point2)
{
	UI_point2 = point2;
}

void Scene::updatePoint3(const ofVec3f point3)
{
	UI_point3 = point3;
}

void Scene::updateRadius(const ofVec3f radius)
{
	UI_radius = radius;
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
		 auto i = sub_level_selected->at(selected_obj_ind);
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
		deSelectObject();
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


void Scene::selectSubsObject()
{
	//Is there a selected object?
	ObjNode* hold = getSelectedObjectsNode();
	if (hold != object_tree_head) {
		//change the new vector to the one of the pointed object
		sub_level_selected = hold->getSubs();
		selected_obj_ind = -1;
	}
}

void Scene::deSelectObject()
{
	selected_obj_ind = -1;
	sub_level_selected = object_tree_head->getSubs();
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

void Scene::undoChange()
{
	if (getSelectedObjects() != nullptr) {

		getSelectedObjects()->undoChange();
	}
}

void Scene::redoChange()
{
	if (getSelectedObjects() != nullptr) {

		getSelectedObjects()->recoverChange();
	}
}






void Scene::PickingPhase(ofVec3f camPos, ofVec3f clickDirect)
//scans all objects to see which one have an obb that intersecs with the ray from the camera to click direction
{
	
	camdebug.setGlobalPosition(camPos);
	camdebug.setRadius(2);
	clickdebug.setGlobalPosition(camPos + 10 * clickDirect);
	clickdebug.setRadius(2);
	for (std::vector<ObjNode*>::const_iterator it =
		object_tree_head->getSubs()->begin(); it !=
		object_tree_head->getSubs()->end(); it++)
	{
		if (*it) {

			ofLog() << "Object clicked" << (*it)->isSelected(camPos, clickDirect);

		}


	}
	
}




