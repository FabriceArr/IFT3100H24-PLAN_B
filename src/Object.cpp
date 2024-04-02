#include "Object.h"
#define MAXCHANGEBUFFERSIZE 10

Object::Object(string primitivetype)
{

	this->name = primitivetype;

	temp.g = temp.h = temp.i = 1;
	
	current_change = 0;
	changes_buffer.push_back(ofMatrix3x3(0,0,0,0,0,0,1,1,1));

	this->stroke_width = 1;

	this->exposure = 2.2f;
	this->gamma = 1.0f;
	this->tone_mapping = true;

	this->ambiantColor = ofColor(255, 0, 0);
	this->diffuseColor = ofColor(255, 0, 0);
	this->specularColor = ofColor(255, 0, 0);
	this->emissiveColor = ofColor(255, 0, 0);
	this->shininess = 40.0f;
}


Object::~Object()
{
	
}


string* Object::getName()
{
	return &this->name;
}

bool Object::operator==(const Object& a) {
	return (*this == a) ?  true :  false;
}

void Object::addChange(ofMatrix3x3 mat)
{
	//if the mat presented is the same as current one, all actions are ignored
	if(!isSameMatrix(mat, getCurrentChangeM()))
	{
		//current change isnt the newest, so clean the top until it meets the current change, discarting previous ones
		if (current_change != changes_buffer.size() - 1) {
			for (size_t i = 0; i < (changes_buffer.size() - current_change); i++)
			{
				changes_buffer.pop_back();
			}
		}


		if (changes_buffer.size() == MAXCHANGEBUFFERSIZE) {
			changes_buffer.pop_front();
		}


		changes_buffer.push_back(mat);
		current_change = changes_buffer.size() - 1;
	}
	
}

ofMatrix3x3 Object::getCurrentChangeM()
{
	//fail safe if the queu is somehow empty,
	//will show as teh object not being visible anymore and will never be visible again
	if (changes_buffer.size() < 1) {
		ofMatrix3x3 i;
		return i;
	}
	return (changes_buffer.at(current_change));
}

void Object::setColor(ofColor color)
{
	this->color = color;
}

ofColor Object::getColor()
{
	return this->color;
}

void Object::setStrokeColor(ofColor color)
{
	this->stroke_color = color;
}

ofColor Object::getStrokeColor()
{
	return this->stroke_color;
}

void Object::setStrokeWidth(unsigned int width)
{
	this->stroke_width = width;
}

unsigned int Object::getStrokeWidth()
{
	return this->stroke_width;
}

void Object::setToneMapping(float exposure, float gamma, bool tone_mapping)
{
	this->exposure = exposure;
	this->gamma = gamma;
	this->tone_mapping = tone_mapping;
}

float Object::getExposure()
{
	return this->exposure;
}

float Object::getGamma()
{
	return this->gamma;
}

bool Object::getToneMapping()
{
	return this->tone_mapping;
}

void Object::setAmbiantColor(ofColor color)
{
	this->ambiantColor = color;
}

void Object::setDiffuseColor(ofColor color)
{
	this->diffuseColor = color;
}

void Object::setSpecularColor(ofColor color)
{
	this->specularColor = color;
}

void Object::setEmissiveColor(ofColor color)
{
	this->emissiveColor = color;
}

void Object::setShininess(float shininess)
{
	this->shininess = shininess;
}

ofColor Object::getAmbiantColor()
{
	return this->ambiantColor;
}

ofColor Object::getDiffuseColor()
{
	return this->diffuseColor;
}

ofColor Object::getSpecularColor()
{
	return this->specularColor;
}

ofColor Object::getEmissiveColor()
{
	return this->emissiveColor;
}

float Object::getShininess()
{
	return this->shininess;
}

bool Object::undoChange()
{
	//no more changes to undo, first change is default location
	if (current_change == 0) {
		return false;
	}
	else {
		current_change--;
		return true;
	}
	
}

bool Object::recoverChange()
{
	//no more changes to recover
	if (current_change == changes_buffer.size()-1) {
		return false;
	}
	else {
		current_change++;
		return true;
	}
}

bool Object::isSameMatrix(ofMatrix3x3 a, ofMatrix3x3 b) {
	for (int i = 0; i < 9; i++) {
		float tempa = a[i];
		float tempb = b[i];
		if (a[i] != b[i]) {
			return false;
		}
	}
	return true;

}