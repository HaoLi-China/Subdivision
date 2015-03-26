#include <fstream>
#include <iostream>
#include <string>
#include <sstream> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wrl_op.h"

//read data from a .wrl file
bool read_from_wrl(const char* fileName, vector<Vertex>& vertexes, vector<Face>& faces){

	ifstream input(fileName);

	if(input.fail()) {
		cout<<"could not open file!"<< endl;
		return false;
	}

	while(!input.eof()){
		string line;
		getline(input, line);

		if(strstr(line.c_str(),"point")!=NULL){
			break;
		}
	}

	while(!input.eof()){
		string line;
		getline(input, line);

		if(strstr(line.c_str(),"]")==NULL){
			istringstream line_input(line);
			Vertex vt;
			line_input >> vt.x >> vt.y >>vt.z;
			vertexes.push_back(vt);
		}
		else{
			break;
		}
	}

	while(!input.eof()){
		string line;
		getline(input, line);
		//cout<<line<<endl;
		if(strstr(line.c_str(),"coordIndex ")!=NULL){
			break;
		}
	}

	while(!input.eof()){
		string line;
		getline(input, line);
		if(strstr(line.c_str(),"]")==NULL){
			istringstream line_input(line);
			Face face;
			line_input >> face.vertexIndex0>>face.vertexIndex1 >>face.vertexIndex2;
			faces.push_back(face);
		}
		else{
			break;
		}
	}

	input.close();

	return true;
}

//write data to a .wrl file
bool write_to_wrl(const char* fileName, vector<Vertex>& vertexes, vector<Face>& faces){

	std::ofstream output(fileName) ;
	if(output.fail()) {
		cout<<"could not open file!"<< endl;
		return false;
	}

	output<<"#VRML V2.0 utf8 (Converted to ASCII)\n"
		<<"Shape {\n"
		<<"geometry IndexedFaceSet {\n"
		<<"coord Coordinate {\n"
		<<"point [\n";

	for(int i=0;i<vertexes.size();i++){
		output << vertexes.at(i).x << " " << vertexes.at(i).y << " " <<  vertexes.at(i).z << std::endl;
	}

	output<<"]\n"
		<<"}\n"
		<<"coordIndex [\n";

	for(int i=0;i<faces.size();i++){
		output << faces.at(i).vertexIndex0 << " " << faces.at(i).vertexIndex1 << " " <<  faces.at(i).vertexIndex2 << " " <<-1<<std::endl;
	}

	output<<"]\n"
		<<"}\n"
		<<"}\n";

	output.close();

	return true;
}