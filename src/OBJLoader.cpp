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

	vector<ofVec2f> uv;
	vector<unsigned int> uvid;

	vector<ofVec3f> norm;
	vector<unsigned int> normid;

	//return carrier
	ofMesh mesh;

	//getting the file to read the lines
	filereader.open(path, ios::in);
	

	//goes on until the doc is finished
	while (filereader.peek() != EOF) {
		getline(filereader, textbuffer);

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
			ofVec3f first, second, third;
			switch (tokens.size())
			{
			case(4)://triangular faces

				//set the first set of face ids
				vertid.push_back(stoi(tokens.at(1).substr(0, tokens.at(1).find_first_of("/"))) - 1);
				temp = tokens.at(1).substr(tokens.at(1).find_first_of("/") + 1);

				uvid.push_back(stoi(temp.substr(0, temp.find_first_of("/"))) - 1);
				temp = temp.substr(temp.find_first_of("/") + 1);

				normid.push_back(stoi(temp.substr(0, temp.find_first_of("/"))) - 1);

				//set the second set of face ids
				vertid.push_back(stoi(tokens.at(2).substr(0, tokens.at(1).find_first_of("/"))) - 1);
				temp = tokens.at(2).substr(tokens.at(2).find_first_of("/") + 1);

				uvid.push_back(stoi(temp.substr(0, temp.find_first_of("/"))) - 1);
				temp = temp.substr(temp.find_first_of("/") + 1);

				normid.push_back(stoi(temp.substr(0, temp.find_first_of("/"))) - 1);

				//set the last set of face ids
				vertid.push_back(stoi(tokens.at(3).substr(0, tokens.at(1).find_first_of("/"))) - 1);
				temp = tokens.at(3).substr(tokens.at(3).find_first_of("/") + 1);

				uvid.push_back(stoi(temp.substr(0, temp.find_first_of("/"))) - 1);
				temp = temp.substr(temp.find_first_of("/") + 1);

				normid.push_back(stoi(temp.substr(0, temp.find_first_of("/"))) - 1);

				break;

			case(5)://square faces
				
				//converting to triangles by adding  the first and third indices a second time
				// doing this to split the square face into to, that share the second and third indices
				//set the first set of face ids
				first.x = stoi(tokens.at(1).substr(0, tokens.at(1).find_first_of("/"))) - 1;
				temp = tokens.at(1).substr(tokens.at(1).find_first_of("/") + 1);

				first.y = stoi(temp.substr(0, temp.find_first_of("/"))) - 1;
				temp = temp.substr(temp.find_first_of("/") + 1);

				first.z = stoi(temp.substr(0, temp.find_first_of("/"))) - 1;

				vertid.push_back(first.x);
				uvid.push_back(first.y);
				normid.push_back(first.z);

				//set the second set of face ids
				second.x = stoi(tokens.at(2).substr(0, tokens.at(1).find_first_of("/"))) - 1;
				temp = tokens.at(2).substr(tokens.at(2).find_first_of("/") + 1);

				second.y = stoi(temp.substr(0, temp.find_first_of("/"))) - 1;
				temp = temp.substr(temp.find_first_of("/") + 1);

				second.z = stoi(temp.substr(0, temp.find_first_of("/"))) - 1;

				vertid.push_back(second.x);
				uvid.push_back(second.y);
				normid.push_back(second.z);

				//set the third set of face ids
				third.x = stoi(tokens.at(3).substr(0, tokens.at(1).find_first_of("/"))) - 1;
				temp = tokens.at(3).substr(tokens.at(3).find_first_of("/") + 1);

				third.y = stoi(temp.substr(0, temp.find_first_of("/"))) - 1;
				temp = temp.substr(temp.find_first_of("/") + 1);

				third.z = stoi(temp.substr(0, temp.find_first_of("/"))) - 1;

				vertid.push_back(third.x);
				uvid.push_back(third.y);
				normid.push_back(third.z);

				//first triangle done, now duplicating it to make another triangle that has the 4rth data point

				vertid.push_back(first.x);
				uvid.push_back(first.y);
				normid.push_back(first.z);

				vertid.push_back(third.x);
				uvid.push_back(third.y);
				normid.push_back(third.z);

				//set the last set of face ids
				vertid.push_back(stoi(tokens.at(4).substr(0, tokens.at(1).find_first_of("/"))) - 1);
				temp = tokens.at(1).substr(tokens.at(1).find_first_of("/") + 1);

				uvid.push_back(stoi(temp.substr(0, temp.find_first_of("/"))) - 1);
				temp = temp.substr(temp.find_first_of("/") + 1);

				normid.push_back(stoi(temp.substr(0, temp.find_first_of("/"))) - 1);
				break;

			default://n gons, which is cursed
				break;
			}			
			
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
					stof(tokens.at(2))
					));
		}
		
	}
	filereader.close();
	for (int i = 0; i < vert.size(); i++) {
		mesh.addVertex(vert.at(i));
	}
	for (int i = 0; i < norm.size(); i++) {
		mesh.addNormal(norm.at(i));
	}
	for (int i = 0; i < uv.size(); i++) {
		mesh.addTexCoord(uv.at(i));
	}
	for (int i = 0; i < vertid.size() / 3; i++) {
		
		mesh.addIndex(vertid.at(i*3));

		
		mesh.addIndex(vertid.at(i*3+1));

		
		mesh.addIndex(vertid.at(i*3+2));
	}
	
	return mesh;
}
