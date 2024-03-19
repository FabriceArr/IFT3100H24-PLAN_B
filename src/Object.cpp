#include "Object.h"
#define MAXCHANGEBUFFERSIZE 10

Object::Object(string primitivetype)
{

	this->name = primitivetype;

	temp.g = temp.h = temp.i = 1;
	
	current_change = 0;
	changes_buffer.push_back(ofMatrix3x3(0,0,0,0,0,0,1,1,1));
	filterSelection = 0; /* Aucun = 0
						 Bilinéaire = 1
						 Trilinéaire = 2
						 Anistropique = 3 */
	//this->setFilter(filterSelection);
	this->stroke_width = 1;

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



void Object::setFilter(unsigned int filter_setting)
{
	GLfloat largest_anisotropy = GL_EXT_texture_filter_anisotropic;

	switch (filter_setting)
	{
	case 0:
		ofLog() << "Object filter setting is Aucun" ;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	case 1:
		ofLog() << "Object filter setting is bilineaire" ;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	case 2:
		ofLog() << "Object filter setting is trilineaire" ;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	case 3:
		ofLog() << "Object filter setting is anistropique" ;
		// avec GL_ARB_texture_filter_anisotropic si OpenGL 4.6
		// avec GL_EXT_texture_filter_anisotropic sinon
		//GLfloat largest_anisotropy = GL_EXT_texture_filter_anisotropic;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_anisotropy);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest_anisotropy);

	default:
		break;
	}

	this->filterSelection = filter_setting;
}

unsigned int Object::getFilter()
{
	return filterSelection;
}
