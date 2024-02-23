//implemented following the tutorial found here https://github.com/VictorGordan/opengl-tutorials/tree/main

#pragma once
#include "Object.h"
#include<GLFW/glfw3.h>


class Mesh
{
private:

	vector<ofVec3f> verts;
	vector<GLuint> verticesIDs;

	vector<ofVec3f> normals;
	vector<GLuint> normalsIDs;

	//buffers to load and assembles the vertexs groups together based on their indexes
	//to form triangle faces ready to be drawn
	GLuint VAO, VBO, EBO;

	//add texture later pour tp2
	//add matt info for tp2
public:
	Mesh(vector<ofVec3f> verts, vector<ofVec3f> normals, vector<GLuint> verticesIDs);

	void draw();
};

