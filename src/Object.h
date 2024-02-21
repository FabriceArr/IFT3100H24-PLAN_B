#pragma once
#include "ofMain.h"



class Object
{
private:
	string name;
	ofTexture texture;
	ofNode object;//change to mesh
	ofMatrix3x3 temp;

	deque<ofMatrix3x3> changes_buffer;
	unsigned int current_change;//index of the current change in the queu



public:

	Object(ofNode object, string name);

	string* getName();
	void setName(string name);

	const ofTexture* getTexture() const;
	void setTexture(ofTexture texture);

	const ofNode* getObject() const;
	void setObject(ofNode object);

	bool operator==(const Object& a);

	void addChange(ofMatrix3x3);
	ofMatrix3x3 getCurrentChangeM();

	bool undoChange();
	bool recoverChange();
	
};

