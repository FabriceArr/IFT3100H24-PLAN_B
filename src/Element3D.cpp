#include "Element3D.h"
#define MAXCHANGEBUFFERSIZE 10
#define OBJECT_SCALE 200

const ofVec3f cube_vertices[] =
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

const ofVec3f cube_normals[] =
{
	ofVec3f(0.0f ,  1.0f, 0.0f),//0
	ofVec3f(0.0f , 0.0f, 1.0f),//1
	ofVec3f(-1.0f ,  0.0f,  0.0f),//2
	ofVec3f(0.0f , -1.0f,  0.0f),//3
	ofVec3f(1.0f,  0.0f, 0.0f),//4
	ofVec3f(0.0f, 0.0f, -1.0f)//5
};

const ofVec2f cube_uvs[] =
{
	ofVec2f(1.0f, 1.0f),//0
	ofVec2f(1.0f, 0.0f),//1
	ofVec2f(0.0f, 1.0f),//2
	ofVec2f(0.0f, 0.0f)//3
	
};

const const GLuint cube_vertices_ids[] =
{
	
	
	0, 1, 2,
	1, 2, 3,

	2, 3, 6,
	3, 6, 7,

	4, 6, 7,
	4, 5, 7,

	0, 1, 5,
	0, 4, 5,

	0, 2, 6,
	0, 4, 6,

	1, 3, 5,
	3, 5, 7

};

const const GLuint cube_uv_ids[] =
{
	0,1,2,1,2,3,
	0,1,2,1,2,3,
	2,0,1,2,3,1,
	2,3,1,2,0,1,
	1,3,2,1,0,2,
	0,2,1,2,1,3
	

};

ofVec3f plane_vertices[] =
{
	ofVec3f(-1.0f, 1.0f,  0.0f),//0
	ofVec3f(1.0f, 1.0f,  0.0f),//1
	ofVec3f(-1.0f, -1.0f,  0.0f),//2
	ofVec3f(1.0f, -1.0f,  0.0f)//3

};

ofVec2f plane_uvs[] =
{
	ofVec2f(0.0f, 1.0f),//0
	ofVec2f(1.0f, 1.0f),//1
	ofVec2f(0.0f, 0.0f),//2
	ofVec2f(1.0f, 0.0f)//3

};

const const GLuint plane_uvs_ids[] =
{
	0,1,2,
	1,2,3

};


GLuint plane_vert_ids[] =
{
	0, 1, 2,
	1, 2, 3
};




Element3D::Element3D(string primitivetype, ofColor color): Object(primitivetype)
{
	if (primitivetype == "cube") {
		updateVertData(&cube_vertices[0], &cube_vertices_ids[0], 36);
		updateTextureData(&cube_uvs[0],&cube_uv_ids[0], 36);
		
		primitivesLimitBox(0);
	}
	else if (primitivetype == "plane") {
		updateVertData(&plane_vertices[0], &plane_vert_ids[0], 6);
		updateTextureData(&plane_uvs[0],&plane_uvs_ids[0], 6);
		
		primitivesLimitBox(1);
	}

	
	
}

Element3D::Element3D(string name, ofMesh mesh): Object(name)
{
	object_buffer.setMesh(mesh, GL_STATIC_DRAW);
	//object_buffer.setTexCoordData()
	texture.getImage()->getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
	customBox(mesh);
}

Element3D::~Element3D()
{

}

void Element3D::draw(bool highlight, bool animated, unsigned int substage)
{
	ofScale(OBJECT_SCALE);


	if (animated && highlight) {
		ofTranslate(0.0f, sin(ofGetElapsedTimef()), 0.0f);
		ofRotateYDeg(fmod((ofGetElapsedTimef() * 100.0f), 360));


	}
	
	if (object_buffer.getNumVertices() > 0) {
		texture.getImage()->bind();
		object_buffer.draw(GL_TRIANGLES, 0, object_buffer.getNumVertices());
		texture.getImage()->unbind();
	}
	else {
		ofLogError() << "Object with no vertices drawn";
	}
	if (highlight) {
		
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

void Element3D::updateVertData(const ofVec3f* vecs, const GLuint* ids, unsigned int size)
{
	ofVec3f* holder = new ofVec3f[size];
	for (int i = 0; i < size; i++) {
		holder[i] = vecs[ids[i]];
	}
	object_buffer.setVertexData(&holder[0], size, GL_STATIC_DRAW);

	delete[] holder;
}

void Element3D::updateTextureData(const ofVec2f *uvs, const GLuint *ids,  unsigned int size)
{
	//copies the coords to keep normalized map for future textures
	ofVec2f* holder = new ofVec2f[size];
	//resizes map to fit texture coords
	for (int i = 0; i < size; i++) {
		holder[i] = uvs[ids[i]];
		//holder[i].x *= texture.getImage()->getWidth();
		//invert the y
		holder[i].y = abs(1.0f - holder[i].y);
		//holder[i].y *= texture.getImage()->getHeight();
	}
	object_buffer.setTexCoordData(&holder[0], size, GL_STATIC_DRAW);

	delete [] holder;
}
