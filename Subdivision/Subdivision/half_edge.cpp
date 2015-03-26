#include "half_edge.h"

//constructor1
HalfEdgeMesh::HalfEdgeMesh(){

}

//constructor2
HalfEdgeMesh::HalfEdgeMesh(vector<Vertex>& vertexes, vector<Face>& faces){
	vector<Face> face_tem;
	sequentializeVtx(vertexes, faces);

	//init half edge vector
	for(int i=0;i < faces.size();i++){

		HEHalfEdge heHalfEdge0={faces.at(i).vertexIndex0,-1,i,3*i+1,3*i+2};
		HEHalfEdges.push_back(heHalfEdge0);

		HEHalfEdge heHalfEdge1={faces.at(i).vertexIndex1,-1,i,3*i+2,3*i};
		HEHalfEdges.push_back(heHalfEdge1);

		HEHalfEdge heHalfEdge2={faces.at(i).vertexIndex2,-1,i,3*i,3*i+1};
		HEHalfEdges.push_back(heHalfEdge2);
	}

	//init the twin of each half edge
	for(int i=0;i<3*faces.size();i++){

		int next_edge_id=HEHalfEdges.at(i).next;
		int v0_id=HEHalfEdges.at(i).origin;
		int v1_id=HEHalfEdges.at(next_edge_id).origin;

		for(int j=0;j<3*faces.size();j++){
			int next_twin=HEHalfEdges.at(j).next;

			if(HEHalfEdges.at(j).origin==v1_id &&HEHalfEdges.at(next_twin).origin==v0_id){

				HEHalfEdges.at(i).twin=j;
				break;
			}
		}		
	}

	//init face vector
	for(int i=0;i<faces.size();i++){
		HEFace heFace={3*i};
		HEFaces.push_back(heFace);
	}

	//init vertex vector
	for(int i=0;i<vertexes.size();i++){
		for(int j=0;j<3*faces.size();j++){
			if(HEHalfEdges.at(j).origin==i){
				HEVtx hevtx={vertexes.at(i).x,vertexes.at(i).y,vertexes.at(i).z,j};
				HEVtxes.push_back(hevtx);
				break;
			}
		}
	}
}

//destructor
HalfEdgeMesh::~HalfEdgeMesh(){

}

//init the half mesh edge
void HalfEdgeMesh::init(vector<Vertex>& vertexes, vector<Face>& faces){
	clear();

	vector<Face> face_tem;
	sequentializeVtx(vertexes, faces);

	//init half edge vector
	for(int i=0;i < faces.size();i++){

		HEHalfEdge heHalfEdge0={faces.at(i).vertexIndex0,-1,i,3*i+1,3*i+2};
		HEHalfEdges.push_back(heHalfEdge0);

		HEHalfEdge heHalfEdge1={faces.at(i).vertexIndex1,-1,i,3*i+2,3*i};
		HEHalfEdges.push_back(heHalfEdge1);

		HEHalfEdge heHalfEdge2={faces.at(i).vertexIndex2,-1,i,3*i,3*i+1};
		HEHalfEdges.push_back(heHalfEdge2);
	}

	//init the twin of each half edge
	for(int i=0;i<3*faces.size();i++){

		int next_edge_id=HEHalfEdges.at(i).next;
		int v0_id=HEHalfEdges.at(i).origin;
		int v1_id=HEHalfEdges.at(next_edge_id).origin;

		for(int j=0;j<3*faces.size();j++){
			int next_twin=HEHalfEdges.at(j).next;

			if(HEHalfEdges.at(j).origin==v1_id &&HEHalfEdges.at(next_twin).origin==v0_id){

				HEHalfEdges.at(i).twin=j;
				break;
			}
		}		
	}

	//init face vector
	for(int i=0;i<faces.size();i++){
		HEFace heFace={3*i};
		HEFaces.push_back(heFace);
	}

	//init vertex vector
	for(int i=0;i<vertexes.size();i++){
		for(int j=0;j<3*faces.size();j++){
			if(HEHalfEdges.at(j).origin==i){
				HEVtx hevtx={vertexes.at(i).x,vertexes.at(i).y,vertexes.at(i).z,j};
				HEVtxes.push_back(hevtx);
				break;
			}
		}
	}
}

//clear all data
void HalfEdgeMesh::clear(){
	HEVtxes.clear();
	HEFaces.clear();
	HEHalfEdges.clear();
}

//get the vertex vector
vector<HEVtx>& HalfEdgeMesh::getHEVtxes(){
	return this->HEVtxes;
}

//get the face vector
vector<HEFace>&  HalfEdgeMesh::getHEFaces(){
	return this->HEFaces;
}

//get the half edge vector
vector<HEHalfEdge>&  HalfEdgeMesh::getHEHalfEdges(){
	return this->HEHalfEdges;
}

//reset vertex vector
void HalfEdgeMesh::setHEVtxes(vector<HEVtx>& HEVtxes){
	this->HEVtxes=HEVtxes;
}

//reset face vector
void HalfEdgeMesh::setHEFaces(vector<HEFace>& HEFaces){
	this->HEFaces=HEFaces;
}

//reset half edge vector
void HalfEdgeMesh::setHEHalfEdges(vector<HEHalfEdge>& HEHalfEdges){
	this->HEHalfEdges=HEHalfEdges;
}

//get vertexes in a face
void HalfEdgeMesh::getVertexesInFace(int face_id, int* v0_id, int* v1_id, int* v2_id){

	int he_index0=HEFaces.at(face_id).edge;
	HEHalfEdge he0=HEHalfEdges.at(he_index0);
	*v0_id=he0.origin;

	int he_index1=he0.next;
	HEHalfEdge he1=HEHalfEdges.at(he_index1);
	*v1_id=he1.origin;

	int he_index2=he1.next;
	HEHalfEdge he2=HEHalfEdges.at(he_index2);
	*v2_id=he2.origin;
}

//get Boundary Adjacent Vertexes of a vertex
void HalfEdgeMesh::getBoundaryAdjacentVertexes(int vertexIndex, vector<int>& adjVtx_ids){
	for(int i=0;i<HEHalfEdges.size();i++){
		HEHalfEdge he=HEHalfEdges.at(i);
		int vtx_id=he.origin;

		int next_edge_id=HEHalfEdges.at(i).next;
		HEHalfEdge next_he=HEHalfEdges.at(next_edge_id);
		int next_vtx_id=HEHalfEdges.at(next_edge_id).origin;

		if(vtx_id==vertexIndex&&isBoundary(he)){
			adjVtx_ids.push_back(next_vtx_id);
		}
		else if(next_vtx_id==vertexIndex&&isBoundary(he)){
			adjVtx_ids.push_back(vtx_id);
		}
	}
}

//get Adjacent Vertexes of a vertex
void HalfEdgeMesh::getAdjacentVertexes(int vertexIndex, vector<int>& adjVtx_ids){

	if(!isOnBoundary(vertexIndex)){

		for(int i=0;i<HEHalfEdges.size();i++){
			if(HEHalfEdges.at(i).origin==vertexIndex){
				int next_edge_id=HEHalfEdges.at(i).next;
				int next_vtx_id=HEHalfEdges.at(next_edge_id).origin;

				adjVtx_ids.push_back(next_vtx_id);
			}
		}
	}
	else{
		for(int i=0;i<HEHalfEdges.size();i++){

			int next_edge_id=HEHalfEdges.at(i).next;
			int next_vtx_id=HEHalfEdges.at(next_edge_id).origin;

			if(HEHalfEdges.at(i).origin==vertexIndex){
				adjVtx_ids.push_back(next_vtx_id);
			}
			else if(next_vtx_id==vertexIndex&&isOnBoundary(HEHalfEdges.at(i).origin)){
				adjVtx_ids.push_back(HEHalfEdges.at(i).origin);
			}
		}
	}
}

//get two sets of sequential Adjacent Vertexes of two vertexes that is in a half edge which is not a boundary edge
void HalfEdgeMesh::getSequentialAdjacentVertexes(int he_id, vector<int>& adjVtx_ids0, vector<int>& adjVtx_ids1){

	if(!isBoundary(HEHalfEdges.at(he_id))){
		int twin_id=HEHalfEdges.at(he_id).twin;

		int tem_id=-1;
		int vtx0_id=HEHalfEdges.at(he_id).origin;
		int vtx1_id=HEHalfEdges.at(twin_id).origin;

		if(isOnBoundary(vtx0_id)){
			vector<int> vtx_ids;
			getBoundaryAdjacentVertexes(vtx0_id, vtx_ids);

			int tem_next=-1;
			int tem_pre=-1;

			for(int i=0;i<HEHalfEdges.size();i++){
				if(HEHalfEdges.at(i).origin==vtx0_id&&(HEHalfEdges.at(HEHalfEdges.at(i).next).origin==vtx_ids.at(0)||HEHalfEdges.at(HEHalfEdges.at(i).next).origin==vtx_ids.at(1))){
					tem_next=HEHalfEdges.at(i).next;
					tem_pre=HEHalfEdges.at(i).prev;
					adjVtx_ids0.push_back(HEHalfEdges.at(tem_next).origin);
					break;
				}
			}

			tem_id=HEHalfEdges.at(tem_pre).twin;
			while(tem_id!=-1){
				tem_next=HEHalfEdges.at(tem_id).next;
				tem_pre=HEHalfEdges.at(tem_id).prev;
				adjVtx_ids0.push_back(HEHalfEdges.at(tem_next).origin);

				tem_id=HEHalfEdges.at(tem_pre).twin;
			}

			adjVtx_ids0.push_back(HEHalfEdges.at(tem_pre).origin);

			vector<int> adjVtx_ids_tem;
			int index_tem=-1;

			for(int k=0;k<adjVtx_ids0.size();k++){
				if(adjVtx_ids0.at(k)==vtx1_id){
					index_tem=k;
				}
			}

			for(int k=index_tem;k<adjVtx_ids0.size();k++){
				adjVtx_ids_tem.push_back(adjVtx_ids0.at(k));
			}

			for(int k=0;k<index_tem;k++){
				adjVtx_ids_tem.push_back(adjVtx_ids0.at(k));
			}

			adjVtx_ids0=adjVtx_ids_tem;
		}
		else{

			adjVtx_ids0.push_back(HEHalfEdges.at(twin_id).origin);

			while(twin_id!=tem_id){
				if(tem_id==-1){
					tem_id=twin_id;
				}

				int next_id=HEHalfEdges.at(tem_id).next;
				tem_id=HEHalfEdges.at(next_id).twin;

				adjVtx_ids0.push_back(HEHalfEdges.at(tem_id).origin);
			}

			invert(adjVtx_ids0);
			adjVtx_ids0.pop_back();
		}

		tem_id=-1;

		if(isOnBoundary(vtx1_id)){

			vector<int> vtx_ids;
			getBoundaryAdjacentVertexes(vtx1_id, vtx_ids);

			int tem_next=-1;
			int tem_pre=-1;

			for(int i=0;i<HEHalfEdges.size();i++){
				if(HEHalfEdges.at(i).origin==vtx1_id&&(HEHalfEdges.at(HEHalfEdges.at(i).next).origin==vtx_ids.at(0)||HEHalfEdges.at(HEHalfEdges.at(i).next).origin==vtx_ids.at(1))){

					tem_next=HEHalfEdges.at(i).next;
					tem_pre=HEHalfEdges.at(i).prev;
					adjVtx_ids1.push_back(HEHalfEdges.at(tem_next).origin);

					break;
				}
			}

			tem_id=HEHalfEdges.at(tem_pre).twin;
			while(tem_id!=-1){
				tem_next=HEHalfEdges.at(tem_id).next;
				tem_pre=HEHalfEdges.at(tem_id).prev;
				adjVtx_ids1.push_back(HEHalfEdges.at(tem_next).origin);

				tem_id=HEHalfEdges.at(tem_pre).twin;
			}

			adjVtx_ids1.push_back(HEHalfEdges.at(tem_pre).origin);

			vector<int> adjVtx_ids_tem;
			int index_tem=-1;

			for(int k=0;k<adjVtx_ids1.size();k++){
				if(adjVtx_ids1.at(k)==vtx0_id){
					index_tem=k;
				}
			}

			for(int k=index_tem;k<adjVtx_ids1.size();k++){
				adjVtx_ids_tem.push_back(adjVtx_ids1.at(k));
			}

			for(int k=0;k<index_tem;k++){
				adjVtx_ids_tem.push_back(adjVtx_ids1.at(k));
			}

			adjVtx_ids1=adjVtx_ids_tem;
		}
		else{
			adjVtx_ids1.push_back(HEHalfEdges.at(he_id).origin);

			while(he_id!=tem_id){
				if(tem_id==-1){
					tem_id=he_id;
				}

				int next_id=HEHalfEdges.at(tem_id).next;
				tem_id=HEHalfEdges.at(next_id).twin;

				adjVtx_ids1.push_back(HEHalfEdges.at(tem_id).origin);
			}

			invert(adjVtx_ids1);
			adjVtx_ids1.pop_back();
		}
	}
}

//if a Half Edge is boundary
bool HalfEdgeMesh::isBoundary(HEHalfEdge heHalfEdge){
	if(heHalfEdge.twin==-1){
		return true;
	}
	return false;
}

//if a Vertex is on boundary
bool HalfEdgeMesh::isOnBoundary(int vtx_index){
	for(int i=0;i<HEHalfEdges.size();i++){
		HEHalfEdge he=HEHalfEdges.at(i);

		if(he.origin==vtx_index&&isBoundary(he)){
			return true;
		}
	}

	return false;
}

//sequentialize vertextes
void HalfEdgeMesh::sequentializeVtx(vector<Vertex>& vertexes, vector<Face>& faces){
	vector<Face> face_tem;
	int count=0;

	while(count!=faces.size()){
		int index=0;

		for(int i=0;i < faces.size();i++){
			if(faces.at(i).vertexIndex0!=-1){
				index=i;
				break;
			}
		}

		//adjust the sequence of vertexes in each face
		for(int i=index;i < faces.size();i++){

			int v0=faces.at(i).vertexIndex0;
			int v1=faces.at(i).vertexIndex1;
			int v2=faces.at(i).vertexIndex2;

			int flag=0;

			for(int j=0;j < face_tem.size(); j++){
				int v0_tem=face_tem.at(j).vertexIndex0;
				int v1_tem=face_tem.at(j).vertexIndex1;
				int v2_tem=face_tem.at(j).vertexIndex2;

				if(!(((v0==v0_tem||v0==v1_tem||v0==v2_tem)&&(v1==v0_tem||v1==v1_tem||v1==v2_tem))||((v0==v0_tem||v0==v1_tem||v0==v2_tem)&&(v2==v0_tem||v2==v1_tem||v2==v2_tem))||((v1==v0_tem||v1==v1_tem||v1==v2_tem)&&(v2==v0_tem||v2==v1_tem||v2==v2_tem)))){
					continue;
				}

				flag=1;

				if((v0==v0_tem&&v1==v1_tem)||(v0==v1_tem&&v1==v2_tem)||(v0==v2_tem&&v1==v0_tem)){
					v0=faces.at(i).vertexIndex1;
					v1=faces.at(i).vertexIndex0;
					break;
				}

				if((v1==v0_tem&&v2==v1_tem)||(v1==v1_tem&&v2==v2_tem)||(v1==v2_tem&&v2==v0_tem)){
					v1=faces.at(i).vertexIndex2;
					v2=faces.at(i).vertexIndex1;
					break;
				}

				if((v2==v0_tem&&v0==v1_tem)||(v2==v1_tem&&v0==v2_tem)||(v2==v2_tem&&v0==v0_tem)){
					v2=faces.at(i).vertexIndex0;
					v0=faces.at(i).vertexIndex2;
					break;
				}
			}

			if(flag==1||i==0){
				Face fc={v0,v1,v2};

				face_tem.push_back(fc);

				faces.at(i).vertexIndex0=-1;
				faces.at(i).vertexIndex1=-1;
				faces.at(i).vertexIndex2=-1;

				count++;
			}
		}

	}

	faces=face_tem;
}

//invert a vector<int>
void HalfEdgeMesh::invert(vector<int>& vec){
	vector<int> tem=vec;
	for(int i=0;i<vec.size();i++){
		vec.at(i)=tem.at(vec.size()-i-1);
	}
}