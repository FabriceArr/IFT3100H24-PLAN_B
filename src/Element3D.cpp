#include "Element3D.h"
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

Element3D::Element3D(string primitivetype, ofColor color): Object(primitivetype)
{
	shader_handler_singleton = shader_handler_singleton->getInstance();
	active_ilum_shader = shader_handler_singleton->getIllumShaderUsed();

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

	updateColorData(color);

}

Element3D::Element3D(string name, ofMesh mesh): Object(name)
{
	shader_handler_singleton = shader_handler_singleton->getInstance();
	active_ilum_shader = shader_handler_singleton->getIllumShaderUsed();

	object_buffer.setMesh(mesh, GL_STATIC_DRAW);

	customBox(mesh);
}

Element3D::~Element3D()
{

}

void Element3D::draw(bool highlight, bool animated, unsigned int substage)
{
	active_ilum_shader = shader_handler_singleton->getIllumShaderUsed();

	if (animated && highlight) {
		ofTranslate(0.0f, sin(ofGetElapsedTimef()), 0.0f);
		ofRotateYDeg(fmod((ofGetElapsedTimef() * 100.0f), 360));
	}
	shader_handler_singleton->setShaderValue(getAmbiantColor(), getDiffuseColor(), getSpecularColor());

	if (active_ilum_shader != nullptr) {
		active_ilum_shader->begin();
	}

	if (object_buffer.getNumIndices() > 0) {
		object_buffer.drawElements(GL_TRIANGLES, object_buffer.getNumIndices());
	}
	else {
		int i = object_buffer.getNumIndices();
		object_buffer.draw(GL_TRIANGLES, 0, object_buffer.getNumIndices());
	}
	if (active_ilum_shader != nullptr) {
		active_ilum_shader->end();
	}

	if (highlight) {
		

		updateColorData(this->getColor());
		//draw the box
		ofBeginShape();

		ofSetColor(232, 247, 14);
		glPointSize(5);
		limit_box.draw(GL_POINTS, 0, 8);
		glPointSize(0);
		ofSetColor((233 + (20 * substage))%255,( 15 + (10 * substage)) % 255, (233 + (42 * substage)) % 255 );

		glLineWidth(5);
		limit_box.drawElements(GL_LINES, limit_box.getNumIndices());
		glLineWidth(0);
		ofSetColor(255);

		ofEndShape();
	}
}

void Element3D::primitivesLimitBox(bool type) {
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
		this->obb_min = ofVec3f(-1.0f, -1.0f, -1.0f);
		this->obb_max = ofVec3f(1.0f, 1.0f, 1.0f);

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

		this->obb_min = ofVec3f(-1.0f, -1.0f, 0.0f);
		this->obb_max = ofVec3f(1.0f, 1.0f, 0.0f);

		this->limit_box.setVertexData(&plane_vertices[0], 4, GL_STATIC_DRAW);
		this->limit_box.setIndexData(&vertices_ids[0], 8, GL_STATIC_DRAW);
	}
}

void Element3D::customBox(ofMesh mesh) {
	ofVec3f hold;

	//define limts for the limit box
	for (int i = 0; i < mesh.getNumVertices(); i++) {
		hold = mesh.getVertex(i);
		if (hold.x < this->obb_min.x) { this->obb_min.x = hold.x; }
		if (hold.x > this->obb_max.x) { this->obb_max.x = hold.x; }

		if (hold.y < this->obb_min.y) { this->obb_min.y = hold.y; }
		if (hold.y > this->obb_max.y) { this->obb_max.y = hold.y; }

		if (hold.z < this->obb_min.z) { this->obb_min.z = hold.z; }
		if (hold.z > this->obb_max.z) { this->obb_max.z = hold.z; }
	}

	ofVec3f cube_vertices_custom[] =
	{
		ofVec3f(this->obb_max.x ,  this->obb_max.y, this->obb_min.z),//0
		ofVec3f(this->obb_max.x , this->obb_min.y, this->obb_min.z),//1
		ofVec3f(this->obb_max.x , this->obb_max.y,  this->obb_max.z),//2
		ofVec3f(this->obb_max.x , this->obb_min.y, this->obb_max.z),//3
		ofVec3f(this->obb_min.x,  this->obb_max.y, this->obb_min.z),//4
		ofVec3f(this->obb_min.x, this->obb_min.y, this->obb_min.z),//5
		ofVec3f(this->obb_min.x,  this->obb_max.y,  this->obb_max.z),//6
		ofVec3f(this->obb_min.x,  this->obb_min.y, this->obb_max.z)//7
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

void Element3D::updateColorData(ofColor c)
{
	ofFloatColor* holder = new ofFloatColor[object_buffer.getNumVertices()];
	for (int i = 0; i < object_buffer.getNumVertices(); i++) {
		holder[i] = c;
	}
	object_buffer.setColorData(&holder[0], object_buffer.getNumVertices(), GL_STATIC_DRAW);

	delete[] holder;
}
