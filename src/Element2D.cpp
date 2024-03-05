#include "Element2D.h"

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


Element2D::Element2D(string primitivetype, string path) : Object(primitivetype)
{
	if (primitivetype == "Imported") {
	//	imageIns.load("image");
		//object_buffer.setVertexData(&plane_vertices[0], 4, GL_STATIC_DRAW);
		//object_buffer.setIndexData(&plane_vert_ids[0], 6, GL_STATIC_DRAW);
		//primitivesLimitBox(1);

		this->image.load(path);
		//object_buffer.setVertexData(&plane_vertices[0], 4, GL_STATIC_DRAW);
		//object_buffer.setIndexData(&plane_vert_ids[0], 6, GL_STATIC_DRAW);
		//primitivesLimitBox(1);

	}

}

Element2D::Element2D(string name, ofMesh mesh) : Object(name)
{
	object_buffer.setMesh(mesh, GL_STATIC_DRAW);

	customBox(mesh);

}

Element2D::~Element2D()
{
}

void Element2D::draw(bool highlight, bool animated)
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


	if (animated) {
		ofTranslate(0.0f, sin(ofGetElapsedTimef()), 0.0f);
		ofRotateYDeg(fmod((ofGetElapsedTimef() * 100), 360));
	}

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
	this->image.draw(image.getWidth()/-2,0,0);
}

void Element2D::primitivesLimitBox(bool type) {
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

void Element2D::customBox(ofMesh mesh) {
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
