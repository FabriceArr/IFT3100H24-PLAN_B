#pragma once
#include "ofMain.h"
#include "UI.h"

enum class illum_enum { flat, lambert, gouraud, phong, blinnPhong };

class Object
{
protected:
	//dimensions of the bounding boxes
	ofVec3f obb_min, obb_max;

private:
	bool selected = true;
	string name;
	ofColor color, stroke_color;
	unsigned int stroke_width;
	ofMatrix3x3 temp;
	//unsigned int filterSelection;
	ofImage image;

	float exposure;
	float gamma;
	bool tone_mapping;
	illum_enum illumModel;

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

	virtual ofVec3f getObbMin();
	virtual ofVec3f getObbMax();

	virtual void setToneMapping(float exposure, float gamma, bool tone_mapping);
	virtual void setIllumModel(illum_enum illumModel);
	virtual float getExposure();
	virtual float getGamma();
	virtual bool getToneMapping();
	virtual illum_enum getIllumModel();

	virtual bool undoChange();
	virtual bool recoverChange();

	virtual void TextureConfigure(ofImage image, unsigned int filterOption);

	bool isSameMatrix(ofMatrix3x3 a, ofMatrix3x3 b);
};

