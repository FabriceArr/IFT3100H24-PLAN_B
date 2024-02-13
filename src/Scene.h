#pragma once

#include "ofMain.h"
#include "Object.h"
#include <vector>

class Scene
{
private:
	ofVec3f origin_pos;

	const ofVec3f* UI_trans_output;
	const ofVec3f* UI_rotation_output;
	const ofVec3f* UI_scale_output;

	std::vector<Object*>* scene_content;
	Object* selected_object;
	//Object cursor;

public:
	//set all defaults and settings
	void setup(const ofVec3f* UIposition, const  ofVec3f* UIrot, const  ofVec3f* UIscale);

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



