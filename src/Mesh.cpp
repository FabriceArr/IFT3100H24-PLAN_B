//implemented following the tutorial found here https://github.com/VictorGordan/opengl-tutorials/tree/main

#include "Mesh.h"

Mesh::Mesh(vector<ofVec3f> vertices, vector<ofVec3f> normals,  vector<GLuint> verticesIDs)
{
	this->verts = vertices;
	this->verticesIDs = verticesIDs;
	this->normals = normals;
	

	 GLuint VAO, VBO, EBO;
	 
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

}

void Mesh::draw()
{
	glDrawElements(GL_TRIANGLES, verticesIDs.size(), GL_UNSIGNED_INT, 0);
}
