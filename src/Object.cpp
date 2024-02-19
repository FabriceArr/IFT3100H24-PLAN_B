#include "Object.h"

#define MAXCHANGEBUFFERSIZE 10

Object::Object(ofNode object, string name = "Objet")
{
	this->name = name;
	this->object = object;
	translation_temp = { 0.f, 0.f, 0.f };
	rotation_temp = { 0.f, 0.f, 0.f };
	scale_temp = { 0.f, 0.f, 0.f };

	
	current_change = 0;
}

const ofNode* Object::getObject() const
{
	return &this->object;
}

const ofTexture* Object::getTexture() const
{
	return &this->texture;
}

string* Object::getName()
{
	return &this->name;
}

void Object::setObject(ofNode object)
{
	this->object = object;
}

void Object::setTexture(ofTexture texture)
{
	this->texture = texture;
}


void Object::setName(string name)
{
	this->name = name;
}

bool Object::operator==(const Object& a) {
	return (*this == a) ?  true :  false;
}

void Object::addChange(ofMatrix4x4 mat)
{
	//current change isnt the newest, so clean the top until it meets the current change, discarting previous ones
	if (current_change != changes_buffer.size()-1) {
		for (size_t i = 0; i < (changes_buffer.size() - current_change); i++)
		{
			changes_buffer.pop_front();
		}
	}


	if (changes_buffer.size() == MAXCHANGEBUFFERSIZE) {
		changes_buffer.pop_back();
	}

	changes_buffer.push_front(mat);
	current_change = changes_buffer.size()-1;
}

ofMatrix4x4 Object::getCurrentChangeM()
{
	//fail safe if the queu is somehow empty
	if (changes_buffer.size() < 1) {
		ofMatrix4x4 i;
		return i;
	}
	return (changes_buffer.at(current_change));
}

bool Object::undoChange()
{
	//no more changes to undo
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

