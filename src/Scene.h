#pragma once

#include "ofMain.h"
#include "Object.h"

class Scene
{
private:
	ofVec3f origin_pos;
	list<Object> scene_content;
	Object* selected_object;
	//Object cursor;

public:
	//set all defaults and settings
	void setup();

	//clean up the scene from memory
	void exit();

	const list<Object> getSceneContent();

	//creates a new object on the origin of the scene
	void createObject(int type, ofVec3f angle);

	//moves the origin of object number x in the list of the scene for 
	//the given amount in the scene.
	void moveObject(unsigned int object_id, ofVec3f position_change);

	//rotate the origin of object number x in the list of the scene for 
	//the given amount in the scene.
	void rotateObject(unsigned int object_id, ofVec3f rotation_change);

	Object* get_selected_object();
};



