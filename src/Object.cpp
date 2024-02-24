#include "Object.h"
#define MAXCHANGEBUFFERSIZE 10


Object::Object(string name, ofMesh mesh)
{
	object_mesh = mesh;
	this->name = name;
	temp.g = temp.h = temp.i = 1;
	

	current_change = 0;
	this->addChange(temp);
}

Object::~Object()
{
	
}

void Object::draw()
{
	if (object_buffer.getNumIndices() > 0) {
		object_buffer.drawElements(GL_TRIANGLES, object_mesh.getNumIndices());
	}
}


const ofTexture* Object::getTexture() const
{
	return &this->texture;
}

string* Object::getName()
{
	return &this->name;
}

void Object::setTexture(ofTexture texture)
{
	this->texture = texture;
}

void Object::setMesh(ofMesh &mesh)
{
	object_buffer.setMesh(mesh, GL_STATIC_DRAW);
}


void Object::setName(string name)
{
	this->name = name;
}

bool Object::operator==(const Object& a) {
	return (*this == a) ?  true :  false;
}

void Object::addChange(ofMatrix3x3 mat)
{
	//current change isnt the newest, so clean the top until it meets the current change, discarting previous ones
	if (current_change != changes_buffer.size()-1) {
		for (size_t i = 0; i < (changes_buffer.size() - current_change); i++)
		{
			changes_buffer.pop_back();
		}
	}


	if (changes_buffer.size() == MAXCHANGEBUFFERSIZE) {
		changes_buffer.pop_front();
	}

	changes_buffer.push_back(mat);
	current_change = changes_buffer.size()-1;
}

ofMatrix3x3 Object::getCurrentChangeM()
{
	//fail safe if the queu is somehow empty
	if (changes_buffer.size() < 1) {
		ofMatrix3x3 i;
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

