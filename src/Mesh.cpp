//implemented following the tutorial found here https://github.com/VictorGordan/opengl-tutorials/tree/main

#include "Mesh.h"

Verts vertices[] =
{ //        COORDINATES         /          COLORS          /         NORMALS         / TEXTURE COORDINATES //
	Verts{ofVec3f(1.0f ,  1.0f, -1.0f), ofVec3f(0.0f, 1.0f, 0.0f), ofVec3f(1.0f, 1.0f, 1.0f), ofVec3f(0.0f, 0.0f)},//0
	Verts{ofVec3f(1.0f , -1.0f, -1.0f), ofVec3f(0.0f, 1.0f, 0.0f), ofVec3f(1.0f, 1.0f, 1.0f), ofVec3f(0.0f, 0.0f)},//1
	Verts{ofVec3f(1.0f ,  1.0f,  1.0f), ofVec3f(0.0f, 1.0f, 0.0f), ofVec3f(1.0f, 1.0f, 1.0f), ofVec3f(0.0f, 0.0f)},//2
	Verts{ofVec3f(1.0f , -1.0f,  1.0f), ofVec3f(0.0f, 1.0f, 0.0f), ofVec3f(1.0f, 1.0f, 1.0f), ofVec3f(0.0f, 0.0f)},//3
	Verts{ofVec3f(-1.0f,  1.0f, -1.0f), ofVec3f(0.0f, 1.0f, 0.0f), ofVec3f(1.0f, 1.0f, 1.0f), ofVec3f(0.0f, 0.0f)},//4
	Verts{ofVec3f(-1.0f, -1.0f, -1.0f), ofVec3f(0.0f, 1.0f, 0.0f), ofVec3f(1.0f, 1.0f, 1.0f), ofVec3f(0.0f, 0.0f)},//5
	Verts{ofVec3f(-1.0f,  1.0f,  1.0f), ofVec3f(0.0f, 1.0f, 0.0f), ofVec3f(1.0f, 1.0f, 1.0f), ofVec3f(0.0f, 0.0f)},//6
	Verts{ofVec3f(-1.0f,  -1.0f, 1.0f), ofVec3f(0.0f, 1.0f, 0.0f), ofVec3f(1.0f, 1.0f, 1.0f), ofVec3f(0.0f, 0.0f)}//7
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

Verts plane_vertices[] =
{ //        COORDINATES         /          COLORS          /         NORMALS         / TEXTURE COORDINATES //
	Verts{ofVec3f(-1.0f, 0.0f,  1.0f), ofVec3f(0.0f, 1.0f, 0.0f), ofVec3f(1.0f, 1.0f, 1.0f), ofVec3f(0.0f, 0.0f)},//0
	Verts{ofVec3f(-1.0f, 0.0f,  1.0f), ofVec3f(0.0f, 1.0f, 0.0f), ofVec3f(1.0f, 1.0f, 1.0f), ofVec3f(0.0f, 0.0f)},//1
	Verts{ofVec3f(-1.0f, 0.0f,  1.0f), ofVec3f(0.0f, 1.0f, 0.0f), ofVec3f(1.0f, 1.0f, 1.0f), ofVec3f(0.0f, 0.0f)},//2
	Verts{ofVec3f(-1.0f, 0.0f,  1.0f), ofVec3f(0.0f, 1.0f, 0.0f), ofVec3f(1.0f, 1.0f, 1.0f), ofVec3f(0.0f, 0.0f)}//3
};

GLuint plane_vert_ids[] =
{
	0, 1, 2,
	0, 2, 3
};

Mesh::Mesh(vector<Verts> vertices, vector<ofVec3f> normals,  vector<GLuint> verticesIDs)
{
	this->verts = vertices;
	this->verticesIDs = verticesIDs;
	
	//just to avoid some warnings since it makes the constructor happy, it deserve a lil treat
	VAO = VBO = EBO = 0;
	 
	 //generates the vertex buffer to intake the other buffers
	 glGenVertexArrays(1, &VAO);

	 //generates and initiates the vertex buffer and sets the buffer with the vertex data
	 glGenBuffers(1, &VBO);
	 glBindBuffer(GL_ARRAY_BUFFER, VBO);
	 glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(verts), vertices.data(), GL_STATIC_DRAW);

	 //generates and initiates the vertex id buffer and sets the buffer with the vertex id data
	 glGenBuffers(1, &EBO);
	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	 glBufferData(GL_ELEMENT_ARRAY_BUFFER, verticesIDs.size() * sizeof(GLuint), verticesIDs.data(), GL_STATIC_DRAW);

	 //link all the values together with their respective types
	 //verts
	 glBindBuffer(GL_ARRAY_BUFFER, VBO);
	 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertices.size(), (void*)0);
	 glEnableVertexAttribArray(0);
	 //color
	 glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertices.size(), (void*)0);
	 glEnableVertexAttribArray(0);
	 //norm
	 glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vertices.size(), (void*)0);
	 glEnableVertexAttribArray(0);

	 glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, vertices.size(), (void*)0);
	 glEnableVertexAttribArray(0);

	 VBO.Unbind();
}

void Mesh::draw()
{
	glDrawElements(GL_TRIANGLES, verticesIDs.size(), GL_UNSIGNED_INT, 0);
}
