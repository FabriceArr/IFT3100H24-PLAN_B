#pragma once
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"



class Object
{
private:
	string name;
	ofTexture texture;
	ofxAssimpModelLoader* object_mesh;
	ofMatrix3x3 temp;

	deque<ofMatrix3x3> changes_buffer;
	unsigned int current_change;//index of the current change in the queu

	

public:

	Object(ofxAssimpModelLoader* object = nullptr, string name = "object");
	~Object();

	void draw();

	string* getName();
	void setName(string name);

	const ofTexture* getTexture() const;
	void setTexture(ofTexture texture);

	const ofxAssimpModelLoader* getMesh() const;
	void setObject(ofxAssimpModelLoader mesh);

	bool operator==(const Object& a);

	void addChange(ofMatrix3x3);
	ofMatrix3x3 getCurrentChangeM();

	bool undoChange();
	bool recoverChange();
	
};

