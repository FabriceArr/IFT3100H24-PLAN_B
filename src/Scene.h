#pragma once

#include "ofMain.h"
#include "Object.h"
#include "ofxGui.h"
#include <vector>

class Scene
{
private:
	ofVec3f origin_pos;

	vector<ofParameter<float>*> UI_trans_output;
	vector<ofParameter<float>*> UI_rotation_output;
	vector<ofParameter<float>*> UI_scale_output;

	std::vector<Object*>* scene_content;
	Object* selected_object;
	//Object cursor;

public:
	//set all defaults and settings
	void setup(const vector<ofParameter<float>*> UIposition, 
		const vector<ofParameter<float>*> UIrot, 
		const vector<ofParameter<float>*> UIscale);

	//clean up the scene from memory
	void exit();

	const std::vector<Object*>* getSceneContent() const;

	//creates a new object on the origin of the scene
	void createObject(int type, ofVec3f angle);

	//moves the origin of object number x in the list of the scene for 
	//the given amount in the scene.
	void moveObject(unsigned int object_id, ofVec3f position_change);

	//rotate the origin of object number x in the list of the scene for 
	//the given amount in the scene.
	void rotateObject(unsigned int object_id, ofVec3f rotation_change);

	const Object* getSelectedObject() const;

	void selectNextObject();

	void selectPreviousObject();

	void draw();


};



