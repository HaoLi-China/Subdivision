#ifndef _HALF_Edge_H
#define _HALF_Edge_H

#include <vector>
#include "wrl_op.h"
#include <iostream>

using namespace std;

//the struct of Vertex record
typedef struct HE_Vertex{
	float x;
	float y;
	float z;
	int incidentEdge;
}HEVtx;

//the struct of Face record
typedef struct HE_Face{
	int edge;
}HEFace;

//the struct of Half Edge record
typedef struct HE_Half_Edge{
	int origin;
	int twin;
	int incidentFace;
	int next;
	int prev;
}HEHalfEdge;

//the class of Half Edge Mesh
class HalfEdgeMesh{
public:
	HalfEdgeMesh();
	HalfEdgeMesh(vector<Vertex>& vertexes, vector<Face>& faces);
	~HalfEdgeMesh();

public:
	void init(vector<Vertex>& vertexes, vector<Face>& faces);
	void clear();

	vector<HEVtx>& getHEVtxes();
	vector<HEFace>& getHEFaces();
	vector<HEHalfEdge>& getHEHalfEdges();

	void setHEVtxes(vector<HEVtx>& HEVtxes);
	void setHEFaces(vector<HEFace>& HEFaces);
	void setHEHalfEdges(vector<HEHalfEdge>& HEHalfEdges);

	void getVertexesInFace(int face_id, int* v0_id, int* v1_id, int* v2_id);
	void getAdjacentVertexes(int vertexIndex, vector<int>& adjVtx_ids);
	void getSequentialAdjacentVertexes(int he_id, vector<int>& adjVtx_ids0, vector<int>& adjVtx_ids1);
	void getBoundaryAdjacentVertexes(int vertexIndex, vector<int>& adjVtx_ids);
	bool isBoundary(HEHalfEdge heHalfEdge);
	bool isOnBoundary(int vtx_index);

private:
	void sequentializeVtx(vector<Vertex>& vertexes, vector<Face>& faces);
	void invert(vector<int>& vec);

private:
	vector<HEVtx> HEVtxes;
	vector<HEFace> HEFaces;
	vector<HEHalfEdge> HEHalfEdges;
};

#endif