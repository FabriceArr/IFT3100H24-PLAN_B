//Implementaiton of an old code I did during my time in cegep, but adapted to work with ofmesh
#include "OBJLoader.h"

ofMesh OBJLoader::loadMeshOBJ(string path)
{
	
	//little variables pile so they can hang out before work :)
	//text handlers
	fstream filereader;
	string textbuffer, temp; 
	//regular expression for the tokenizator so it removes all spaces in a string
	regex regexp = std::regex{R"(\s+)"};

	//vertex handlers
	vector<ofVec3f> vert;
	vector<unsigned int> vertid;

	vector<ofVec3f> uv;
	vector<unsigned int> uvid;

	vector<ofVec3f> norm;
	vector<unsigned int> normid;

	//return carrier
	ofMesh mesh;

	//getting the file to read the lines
	filereader.open(path, ios::in);
	
	//goes on until the doc is finished
	while (getline(filereader, textbuffer)) {

		//tokenizes the line to get all the infor seperated, the first is the type of date the line is about
		//# = file header info, not useful here
		//o = object name
		//v = vertex x y z
		//vn = normals
		//vt = uvs
		//f = faces indexes (tri)
		
		vector<string> tokens = std::vector<std::string>(
			std::sregex_token_iterator{ begin(textbuffer), end(textbuffer), regexp, -1 },
			std::sregex_token_iterator{}
		);
		//skips this line since its jsut header stuff or empty lines
		if (tokens.at(0) == "#" || tokens.at(0) == "mtllib" || tokens.empty()) { continue; }

		//verts
		if (tokens.at(0) == "v") {
			vert.push_back(
				ofVec3f(stof(tokens.at(1)), 
						stof(tokens.at(2)), 
						stof(tokens.at(3))
						));
		}


		//faces
		if (tokens.at(0) == "f") {
			//set the first set of face ids
			vertid.push_back(stoi(tokens.at(1).substr(0, tokens.at(1).find_first_of("/"))) - 1);
			temp = tokens.at(1).substr(tokens.at(1).find_first_of("/") + 1);

			uvid.push_back(stoi(temp.substr(0, temp.find_first_of("/"))) - 1);
			temp = temp.substr(temp.find_first_of("/") + 1);

			normid.push_back(stoi(temp.substr(0, temp.find_first_of("/"))) - 1);

			//set the second set of face ids
			vertid.push_back(stoi(tokens.at(2).substr(0, tokens.at(1).find_first_of("/"))) - 1);
			temp = tokens.at(1).substr(tokens.at(1).find_first_of("/") + 1);

			uvid.push_back(stoi(temp.substr(0, temp.find_first_of("/"))) - 1);
			temp = temp.substr(temp.find_first_of("/") + 1);

			normid.push_back(stoi(temp.substr(0, temp.find_first_of("/"))) - 1);

			//set the last set of face ids
			vertid.push_back(stoi(tokens.at(3).substr(0, tokens.at(1).find_first_of("/"))) - 1);
			temp = tokens.at(1).substr(tokens.at(1).find_first_of("/") + 1);

			uvid.push_back(stoi(temp.substr(0, temp.find_first_of("/"))) - 1);
			temp = temp.substr(temp.find_first_of("/") + 1);

			normid.push_back(stoi(temp.substr(0, temp.find_first_of("/"))) - 1);
		}

		//normals
		if (tokens.at(0) == "vn") {
			norm.push_back(
				ofVec3f(stof(tokens.at(1)),
						stof(tokens.at(2)),
						stof(tokens.at(3))
						));
		}

		//uvs
		if (tokens.at(0) == "vt") {
			uv.push_back(
					ofVec3f(stof(tokens.at(1)),
					stof(tokens.at(2)),
					stof(tokens.at(3))
					));
		}
		
	}
	filereader.close();

	for (int i = 0; i < vertid.size() / 3; i++) {
		mesh.addVertex(vert.at(i*3));
		mesh.addIndex(vertid.at(i*3));

		mesh.addVertex(vert.at(i*3+1));
		mesh.addIndex(vertid.at(i*3+1));

		mesh.addVertex(vert.at(i*3)+2);
		mesh.addIndex(vertid.at(i*3)+2);
	}
	
	return ofMesh();
}
