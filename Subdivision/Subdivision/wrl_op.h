#ifndef _WRL_OP_H
#define _WRL_OP_H

#include <vector>

using namespace std;

//struct of vertex
typedef struct VertexXYZ{
	float x;
	float y;
	float z;
}Vertex;

//struct of face
typedef struct FaceStruct{
	int vertexIndex0;
	int	vertexIndex1;
	int	vertexIndex2;
}Face;

//read data from a .wrl file
bool read_from_wrl(const char* fileName, vector<Vertex>& vertexes, vector<Face>& faces);

//write data to a .wrl file
bool write_to_wrl(const char* fileName, vector<Vertex>& vertexes, vector<Face>& faces);

#endif