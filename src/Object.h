#pragma once
#include "ofMain.h"
#include "ofVbo.h"
#include "ofxAssimpModelLoader.h"


class Object
{
private:
	string name;
	ofTexture texture;
	ofVbo object_buffer;
	ofMatrix3x3 temp;

	deque<ofMatrix3x3> changes_buffer;
	unsigned int current_change;//index of the current change in the queu

	

public:
	Object(string primitivetype, ofColor color);
	Object(string name, ofMesh mesh);
	~Object();

	void draw();

	string* getName();
	void setName(string name);

	const ofTexture* getTexture() const;
	void setTexture(ofTexture texture);

	void setMesh(ofMesh& mesh);

	bool operator==(const Object& a);

	void addChange(ofMatrix3x3);
	ofMatrix3x3 getCurrentChangeM();

	bool undoChange();
	bool recoverChange();
	
};

