#include "Object.h"
#define MAXCHANGEBUFFERSIZE 10

ofVec3f cube_vertices[] =
{
	ofVec3f(1.0f ,  1.0f, -1.0f),//0
	ofVec3f(1.0f , -1.0f, -1.0f),//1
	ofVec3f(1.0f ,  1.0f,  1.0f),//2
	ofVec3f(1.0f , -1.0f,  1.0f),//3
	ofVec3f(-1.0f,  1.0f, -1.0f),//4
	ofVec3f(-1.0f, -1.0f, -1.0f),//5
	ofVec3f(-1.0f,  1.0f,  1.0f),//6
	ofVec3f(-1.0f,  -1.0f, 1.0f)//7
};

GLuint cube_vertices_ids[] =
{
	0, 1, 2,
	0, 1, 5,
	0, 2, 4,
	0, 4, 5,
	1, 2, 3,
	1, 3, 5,
	2, 3, 7,
	2, 4, 7,
	2, 6, 7,
	3, 5, 7,
	4, 5, 6,
	5, 6, 7

};

ofVec3f plane_vertices[] =
{
	ofVec3f(-1.0f, 1.0f,  0.0f),//0
	ofVec3f(1.0f, 1.0f,  0.0f),//1
	ofVec3f(-1.0f, -1.0f,  0.0f),//2
	ofVec3f(1.0f, -1.0f,  0.0f)//3
};

GLuint plane_vert_ids[] =
{
	0, 1, 2,
	1, 2, 3
};

Object::Object(string primitivetype, ofColor color)
{
	if (primitivetype == "cube") {
		object_buffer.setVertexData(&cube_vertices[0], 8, GL_STATIC_DRAW);
		object_buffer.setIndexData(&cube_vertices_ids[0], 36, GL_STATIC_DRAW);
	}
	else if (primitivetype == "plane") {
		object_buffer.setVertexData(&plane_vertices[0], 4, GL_STATIC_DRAW);
		object_buffer.setIndexData(&plane_vert_ids[0], 6, GL_STATIC_DRAW);
	}
	int size = object_buffer.getNumVertices();
	ofFloatColor* holder = new ofFloatColor[size];
	for (int i = 0; i < object_buffer.getNumVertices(); i++) {
		holder[i] = color;
	}
	object_buffer.setColorData(&holder[0], object_buffer.getNumVertices(), GL_STATIC_DRAW);

	delete [] holder;

	this->name = primitivetype;

	temp.g = temp.h = temp.i = 1;

	current_change = 0;
	this->addChange(temp);
}

Object::Object(string name, ofMesh mesh)
{
	object_buffer.setMesh(mesh, GL_STATIC_DRAW);
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
		object_buffer.drawElements(GL_TRIANGLES, object_buffer.getNumIndices());
	}
	else {
		int i = object_buffer.getNumIndices();
		object_buffer.draw(GL_TRIANGLES, 0, object_buffer.getNumIndices());
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

