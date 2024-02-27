#pragma once

#include "ofMain.h"
#include "Object.h"
#include "ObjNode.h"
#include "ofxGui.h"
#include "ClickTexture.h"
#include "ofxAssimpModelLoader.h"
#include "OBJLoader.h"
#include <vector>

class Scene
{
private:
	ofVec3f origin_pos;

	ofMatrix4x4 project_matrice, view_matrice;

	ofMatrix3x3 temp_info, info;

	vector<ofParameter<float>*> UI_trans_output;
	vector<ofParameter<float>*> UI_rotation_output;
	vector<ofParameter<float>*> UI_scale_output;
	
	//points to the vector of elements currently selected
	int selected_obj_ind;
	std::vector<ObjNode*>* sub_level_selected;
	ObjNode* selected_object;

	ObjNode* object_tree_head;

	ClickTexture select_mode;

	ofxAssimpModelLoader mesh_loader;

	ofParameter<ofColor> UI_fill_color;

	ofShader anim_shader_rot, anim_shader_bob;

public:
	bool animate;
	bool isOrtho;

	//set all defaults and settings
	void setup(const vector<ofParameter<float>*> UIposition, 
		const vector<ofParameter<float>*> UIrot, 
		const vector<ofParameter<float>*> UIscale);

	//clean up the scene from memory
	void exit();

	const ObjNode* getSceneContent() const;

	//creates a new object on the origin of the scene
	void createObject(bool i);

	void createImportedObject3D(string path);

	//moves the origin of object number x in the list of the scene for 
	//the given amount in the scene.
	void moveObject(unsigned int object_id, ofVec3f position_change);

	//rotate the origin of object number x in the list of the scene for 
	//the given amount in the scene.
	void rotateObject(unsigned int object_id, ofVec3f rotation_change);

	void changeSelectedMatrice(ofMatrix3x3 change);

	void updateFillColor(ofParameter<ofColor> colorparam);
	void updateSelectedObjects();

	Object* getSelectedObjects();
	ObjNode* getSelectedObjectsNode();

	void removeObject();

	void deSelectObject();

	void savechange();

	void draw();

	void drawSubObjects(std::vector<Object*>* subVector);

	void PickingPhase(ofMatrix4x4 projectM, ofMatrix4x4 viewM);

	void findSelectedObject(int x, int y);

	void selectNextObject();
	void selectPreviousObject();
	void selectParentObject();
	void selectSubsObject();

};



