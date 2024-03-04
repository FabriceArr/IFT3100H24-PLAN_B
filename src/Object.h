#pragma once
#include "ofMain.h"


class Object
{
private:
	bool selected = true;
	string name;
	ofTexture texture;
	ofMatrix3x3 temp;

	deque<ofMatrix3x3> changes_buffer;
	unsigned int current_change;//index of the current change in the queu
	

public:
	Object(string name);
	~Object();

	virtual void draw(bool highlight, bool animated = false) = 0;

	virtual string* getName();

	bool operator==(const Object& a);

	virtual void addChange(ofMatrix3x3);
	virtual ofMatrix3x3 getCurrentChangeM();

	virtual bool undoChange();
	virtual bool recoverChange();

	bool isSameMatrix(ofMatrix3x3 a, ofMatrix3x3 b);
};

