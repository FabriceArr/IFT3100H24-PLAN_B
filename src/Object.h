#pragma once
#include "ofMain.h"



class Object
{
private:
	string name;
	ofTexture texture;
	ofNode object;//change to mesh
	
	deque<ofMatrix4x4> changes_buffer;
	unsigned int current_change;//index of the current change in the queu



public:
	ofVec3f translation_temp;
	ofVec3f rotation_temp;
	ofVec3f scale_temp;

	Object(ofNode object, string name);

	string* getName();
	void setName(string name);

	const ofTexture* getTexture() const;
	void setTexture(ofTexture texture);

	const ofNode* getObject() const;
	void setObject(ofNode object);

	bool operator==(const Object& a);

	void addChange(ofMatrix4x4);
	ofMatrix4x4 getCurrentChangeM();

	bool undoChange();
	bool recoverChange();
	
};

