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
		primitivesLimitBox(0);
	}
	else if (primitivetype == "plane") {
		object_buffer.setVertexData(&plane_vertices[0], 4, GL_STATIC_DRAW);
		object_buffer.setIndexData(&plane_vert_ids[0], 6, GL_STATIC_DRAW);
		primitivesLimitBox(1);
	}

	ofFloatColor* holder = new ofFloatColor[object_buffer.getNumVertices()];
	for (int i = 0; i < object_buffer.getNumVertices(); i++) {
		holder[i] = color;
	}
	object_buffer.setColorData(&holder[0], object_buffer.getNumVertices(), GL_STATIC_DRAW);

	delete [] holder;

	this->name = primitivetype;

	temp.g = temp.h = temp.i = 1;
	
	current_change = 0;
	changes_buffer.push_back(ofMatrix3x3(0,0,0,0,0,0,1,1,1));
}

Object::Object(string name, ofMesh mesh)
{
	object_buffer.setMesh(mesh, GL_STATIC_DRAW);
	this->name = name;
	temp.g = temp.h = temp.i = 1;
	

	current_change = 0;
	changes_buffer.push_back(ofMatrix3x3(0,0,0,0,0,0,1,1,1));

	customBox(mesh);
}

Object::~Object()
{
	
}

void Object::draw(bool highlight)
{
	ofMatrix3x3 hold = getCurrentChangeM();
	ofTranslate(
		hold.a,
		hold.b,
		hold.c);
	ofRotateXDeg(
		hold.d);
	ofRotateYDeg(
		hold.e);
	ofRotateZDeg(
		hold.f);
	ofScale(
		hold.g,
		hold.h,
		hold.i);
	
	if (object_buffer.getNumIndices() > 0) {

		object_buffer.drawElements(GL_TRIANGLES, object_buffer.getNumIndices());
	}
	else {
		int i = object_buffer.getNumIndices();
		object_buffer.draw(GL_TRIANGLES, 0, object_buffer.getNumIndices());
	}
	if (highlight) {
		//draw the box
		ofBeginShape();

		ofSetColor(232, 247, 14);
		glPointSize(5);
		limit_box.draw(GL_POINTS, 0, 8);
		glPointSize(0);
		ofSetColor(233, 15, 233);

		glLineWidth(5);
		limit_box.drawElements(GL_LINES, limit_box.getNumIndices());
		glLineWidth(0);
		ofSetColor(255);

		ofEndShape();
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
	ofLog() << "Current change : " << current_change;
	//fail safe if the queu is somehow empty,
	//will show as teh object not being visible anymore and will never be visible again
	if (changes_buffer.size() < 1) {
		ofMatrix3x3 i;
		return i;
	}
	return (changes_buffer.at(current_change));
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

void Object::primitivesLimitBox(bool type) {
	if (!type) {
		GLuint vertices_ids[] =
		{
			0, 1,
			0, 2,
			1, 3,
			1, 5,
			2, 3,
			2, 6,
			3, 7,
			4, 5,
			4, 0,
			5, 7,
			6, 7,
			6, 4
		};

		this->limit_box.setVertexData(&cube_vertices[0], 8, GL_STATIC_DRAW);
		this->limit_box.setIndexData(&vertices_ids[0], 24, GL_STATIC_DRAW);
	}
	else {
		GLuint vertices_ids[] =
		{
			0, 1,
			1, 3,
			2, 3,
			2, 0
		};

		this->limit_box.setVertexData(&plane_vertices[0], 4, GL_STATIC_DRAW);
		this->limit_box.setIndexData(&vertices_ids[0], 8, GL_STATIC_DRAW);
	}
}

void Object::customBox(ofMesh mesh){
	float max_x, min_x, max_y, min_y, max_z, min_z;
	max_x = min_x = max_y = min_y = max_z = min_z = 0.0f;
	ofVec3f hold;

	//define limts for the limit box
	for (int i = 0; i < mesh.getNumVertices(); i++) {
		hold = mesh.getVertex(i);

		if (hold.x < min_x) { min_x = hold.x; }
		if (hold.x > max_x) { max_x = hold.x; }

		if (hold.y < min_y) { min_y = hold.y; }
		if (hold.y > max_y) { max_y = hold.y; }

		if (hold.z < min_z) { min_z = hold.z; }
		if (hold.z > max_z) { max_z = hold.z; }
	}
	
	ofVec3f cube_vertices_custom[] =
	{
		ofVec3f(max_x ,  max_y, min_z),//0
		ofVec3f(max_x , min_y, min_z),//1
		ofVec3f(max_x , max_y,  max_z),//2
		ofVec3f(max_x , min_y, max_z),//3
		ofVec3f(min_x,  max_y, min_z),//4
		ofVec3f(min_x, min_y, min_z),//5
		ofVec3f(min_x,  max_y,  max_z),//6
		ofVec3f(min_x,  min_y, max_z)//7
	};
	GLuint cube_vertices_ids[] =
	{
		0, 1,
		0, 2,
		1, 3,
		1, 5,
		2, 3,
		2, 6,
		3, 7,
		4, 5,
		4, 0,
		5, 7,
		6, 7,
		6, 4
	};

	this->limit_box.setVertexData(&cube_vertices_custom[0], 8, GL_STATIC_DRAW);
	this->limit_box.setIndexData(&cube_vertices_ids[0], 24, GL_STATIC_DRAW);
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