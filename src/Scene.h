#pragma once

#include "ofMain.h"
#include "Object.h"
#include "ObjNode.h"
#include "ofxGui.h"
#include "ClickTexture.h"
#include <vector>

class Scene
{
private:
	ofVec3f origin_pos;

	ofMatrix4x4 project_matrice, view_matrice;

	vector<ofParameter<float>*> UI_trans_output;
	vector<ofParameter<float>*> UI_rotation_output;
	vector<ofParameter<float>*> UI_scale_output;
	
	//vector for selecting multiple objects
	std::vector<Object*> selected_objects;

	ObjNode* object_tree_head;

	ClickTexture select_mode;

public:
	//set all defaults and settings
	void setup(const vector<ofParameter<float>*> UIposition, 
		const vector<ofParameter<float>*> UIrot, 
		const vector<ofParameter<float>*> UIscale);

	//clean up the scene from memory
	void exit();

	const ObjNode* getSceneContent() const;

	//creates a new object on the origin of the scene
	void createObject(int type, ofVec3f angle);

	//moves the origin of object number x in the list of the scene for 
	//the given amount in the scene.
	void moveObject(unsigned int object_id, ofVec3f position_change);

	//rotate the origin of object number x in the list of the scene for 
	//the given amount in the scene.
	void rotateObject(unsigned int object_id, ofVec3f rotation_change);

	const vector<Object*>* getSelectedObjects() const;

	void removeObject(ObjNode* objectNode);

	void selectNextObject();

	void selectPreviousObject();

	void draw();

	void drawSubObjects(std::vector<Object*>* subVector);

	void PickingPhase(ofMatrix4x4 projectM, ofMatrix4x4 viewM);

	void findSelectedObject(int x, int y);

};



