#pragma once
#include "ofMain.h"


class Object
{
private:
	bool selected = true;
	string name;
	ofColor color, stroke_color;
	unsigned int stroke_width;
	ofMatrix3x3 temp;

	float exposure;
	float gamma;
	bool tone_mapping;

	ofColor ambiantColor;
	ofColor diffuseColor;
	ofColor specularColor;
	ofColor emissiveColor;
	float shininess;

	ofMaterial material;

	deque<ofMatrix3x3> changes_buffer;
	unsigned int current_change;//index of the current change in the queu
	

public:
	Object(string name);
	~Object();

	virtual void draw(bool highlight, bool animated = false, unsigned int substage = 0) = 0;

	virtual string* getName();

	virtual bool operator==(const Object& a);

	virtual void addChange(ofMatrix3x3);
	virtual ofMatrix3x3 getCurrentChangeM();

	virtual void setColor(ofColor color);
	virtual ofColor getColor();

	virtual void setStrokeColor(ofColor color);
	virtual ofColor getStrokeColor();

	virtual void setStrokeWidth(unsigned int width);
	virtual unsigned int getStrokeWidth();

	virtual void setToneMapping(float exposure, float gamma, bool tone_mapping);
	virtual float getExposure();
	virtual float getGamma();
	virtual bool getToneMapping();

	virtual void setAmbiantColor(ofColor ambiantColor);
	virtual void setDiffuseColor(ofColor diffuseColor);
	virtual void setSpecularColor(ofColor specularColor);
	virtual void setEmissiveColor(ofColor emissiveColor);
	virtual void setShininess(float shininess);
	virtual ofColor getAmbiantColor();
	virtual ofColor getDiffuseColor();
	virtual ofColor getSpecularColor();
	virtual ofColor getEmissiveColor();
	virtual float getShininess();


	virtual bool undoChange();
	virtual bool recoverChange();

	bool isSameMatrix(ofMatrix3x3 a, ofMatrix3x3 b);
};

