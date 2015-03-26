#include <vector>
#include "subdivision .h"

//get new vertex index by old vertexes
int getNewVertexIndexByOldVertexes(vector<pair<int,int>>& vertexes_pair,int v0_id, int v1_id, int old_vtx_num){

	for(int i=0;i<vertexes_pair.size();i++){

		pair<int,int> pr=vertexes_pair.at(i);
		if((pr.first==v0_id&&pr.second==v1_id)||(pr.first==v1_id&&pr.second==v0_id)){
			return old_vtx_num+i;
		}
	}

	return -1;
}

//do loop subdivision for odd vertices
void loop_subdiv_odd(HalfEdgeMesh &halfEdgeMesh,vector<Vertex>& new_vertexes,vector<Face>& new_faces){

	vector<HEVtx> HEVtxes = halfEdgeMesh.getHEVtxes();
	vector<HEFace> HEFaces = halfEdgeMesh.getHEFaces();
	vector<HEHalfEdge> HEHalfEdges = halfEdgeMesh.getHEHalfEdges();

	const int faceNum=HEFaces.size();
	const int vertexNum=HEVtxes.size();
	const int heNum=HEHalfEdges.size();

	vector<pair<int,int>> vertexes_pair;

	//add old vertexes
	for(int i=0;i<vertexNum;i++){
		Vertex vtx={HEVtxes.at(i).x,HEVtxes.at(i).y,HEVtxes.at(i).z};
		new_vertexes.push_back(vtx);
	}

	vector<int> flags;
	for(int i=0;i<heNum;i++){
		flags.push_back(0);
	}

	//add new vertexes
	for(int i=0;i<faceNum;i++){
		int he_index0=HEFaces.at(i).edge;
		HEHalfEdge he0=HEHalfEdges.at(he_index0);
		int v0_id=he0.origin;

		int he_index1=he0.next;
		HEHalfEdge he1=HEHalfEdges.at(he_index1);
		int v1_id=he1.origin;

		int he_index2=he1.next;
		HEHalfEdge he2=HEHalfEdges.at(he_index2);
		int v2_id=he2.origin;

		if(halfEdgeMesh.isBoundary(he0)&&flags.at(he_index0)==0){
			Vertex new_vtx;
			new_vtx.x=(HEVtxes.at(v0_id).x+HEVtxes.at(v1_id).x)/2.0;
			new_vtx.y=(HEVtxes.at(v0_id).y+HEVtxes.at(v1_id).y)/2.0;
			new_vtx.z=(HEVtxes.at(v0_id).z+HEVtxes.at(v1_id).z)/2.0;
			new_vertexes.push_back(new_vtx);

			pair<int,int> pr(v0_id,v1_id);
			vertexes_pair.push_back(pr);

			flags.at(he_index0)=1;
		}
		else if(flags.at(he_index0)==0){
			int twin_he_index=he0.twin;
			int pre_he_index=he0.prev;
			int twin_pre_he_index=HEHalfEdges.at(twin_he_index).prev;
			int v_tem1=HEHalfEdges.at(pre_he_index).origin;
			int v_tem2=HEHalfEdges.at(twin_pre_he_index).origin;

			Vertex new_vtx;
			new_vtx.x=3*(HEVtxes.at(v0_id).x+HEVtxes.at(v1_id).x)/8.0+(HEVtxes.at(v_tem1).x+HEVtxes.at(v_tem2).x)/8.0;
			new_vtx.y=3*(HEVtxes.at(v0_id).y+HEVtxes.at(v1_id).y)/8.0+(HEVtxes.at(v_tem1).y+HEVtxes.at(v_tem2).y)/8.0;
			new_vtx.z=3*(HEVtxes.at(v0_id).z+HEVtxes.at(v1_id).z)/8.0+(HEVtxes.at(v_tem1).z+HEVtxes.at(v_tem2).z)/8.0;
			new_vertexes.push_back(new_vtx);

			pair<int,int> pr(v0_id,v1_id);
			vertexes_pair.push_back(pr);

			flags.at(he_index0)=1;
			flags.at(twin_he_index)=1;
		}

		if(halfEdgeMesh.isBoundary(he1)&&flags.at(he_index1)==0){
			Vertex new_vtx;
			new_vtx.x=(HEVtxes.at(v1_id).x+HEVtxes.at(v2_id).x)/2.0;
			new_vtx.y=(HEVtxes.at(v1_id).y+HEVtxes.at(v2_id).y)/2.0;
			new_vtx.z=(HEVtxes.at(v1_id).z+HEVtxes.at(v2_id).z)/2.0;
			new_vertexes.push_back(new_vtx);

			pair<int,int> pr(v1_id,v2_id);
			vertexes_pair.push_back(pr);

			flags.at(he_index1)=1;
		}
		else if(flags.at(he_index1)==0){
			int twin_he_index=he1.twin;
			int pre_he_index=he1.prev;
			int twin_pre_he_index=HEHalfEdges.at(twin_he_index).prev;
			int v_tem1=HEHalfEdges.at(pre_he_index).origin;
			int v_tem2=HEHalfEdges.at(twin_pre_he_index).origin;

			Vertex new_vtx;
			new_vtx.x=3*(HEVtxes.at(v1_id).x+HEVtxes.at(v2_id).x)/8.0+(HEVtxes.at(v_tem1).x+HEVtxes.at(v_tem2).x)/8.0;
			new_vtx.y=3*(HEVtxes.at(v1_id).y+HEVtxes.at(v2_id).y)/8.0+(HEVtxes.at(v_tem1).y+HEVtxes.at(v_tem2).y)/8.0;
			new_vtx.z=3*(HEVtxes.at(v1_id).z+HEVtxes.at(v2_id).z)/8.0+(HEVtxes.at(v_tem1).z+HEVtxes.at(v_tem2).z)/8.0;
			new_vertexes.push_back(new_vtx);

			pair<int,int> pr(v1_id,v2_id);
			vertexes_pair.push_back(pr);

			flags.at(he_index1)=1;
			flags.at(twin_he_index)=1;
		}

		if(halfEdgeMesh.isBoundary(he2)&&flags.at(he_index2)==0){
			Vertex new_vtx;
			new_vtx.x=(HEVtxes.at(v2_id).x+HEVtxes.at(v0_id).x)/2.0;
			new_vtx.y=(HEVtxes.at(v2_id).y+HEVtxes.at(v0_id).y)/2.0;
			new_vtx.z=(HEVtxes.at(v2_id).z+HEVtxes.at(v0_id).z)/2.0;
			new_vertexes.push_back(new_vtx);

			pair<int,int> pr(v2_id,v0_id);
			vertexes_pair.push_back(pr);

			flags.at(he_index2)=1;
		}
		else if((flags.at(he_index2)==0)){
			int twin_he_index=he2.twin;
			int pre_he_index=he2.prev;
			int twin_pre_he_index=HEHalfEdges.at(twin_he_index).prev;
			int v_tem1=HEHalfEdges.at(pre_he_index).origin;
			int v_tem2=HEHalfEdges.at(twin_pre_he_index).origin;

			Vertex new_vtx;
			new_vtx.x=3*(HEVtxes.at(v2_id).x+HEVtxes.at(v0_id).x)/8.0+(HEVtxes.at(v_tem1).x+HEVtxes.at(v_tem2).x)/8.0;
			new_vtx.y=3*(HEVtxes.at(v2_id).y+HEVtxes.at(v0_id).y)/8.0+(HEVtxes.at(v_tem1).y+HEVtxes.at(v_tem2).y)/8.0;
			new_vtx.z=3*(HEVtxes.at(v2_id).z+HEVtxes.at(v0_id).z)/8.0+(HEVtxes.at(v_tem1).z+HEVtxes.at(v_tem2).z)/8.0;
			new_vertexes.push_back(new_vtx);

			pair<int,int> pr(v2_id,v0_id);
			vertexes_pair.push_back(pr);

			flags.at(he_index2)=1;
			flags.at(twin_he_index)=1;
		}
	}

	//gen new faces
	for(int i=0;i<faceNum;i++){
		int he_index0=HEFaces.at(i).edge;
		HEHalfEdge he0=HEHalfEdges.at(he_index0);
		int v0_id=he0.origin;

		int he_index1=he0.next;
		HEHalfEdge he1=HEHalfEdges.at(he_index1);
		int v1_id=he1.origin;

		int he_index2=he1.next;
		HEHalfEdge he2=HEHalfEdges.at(he_index2);
		int v2_id=he2.origin;

		int index0=getNewVertexIndexByOldVertexes(vertexes_pair,v0_id, v1_id, vertexNum);
		int index1=getNewVertexIndexByOldVertexes(vertexes_pair,v1_id, v2_id, vertexNum);
		int index2=getNewVertexIndexByOldVertexes(vertexes_pair,v2_id, v0_id, vertexNum);

		if(index0!=-1&&index1!=-1&&index2!=-1){
			Face face0={v0_id,index0,index2};
			Face face1={index0,v1_id,index1};
			Face face2={index0,index1,index2};
			Face face3={index1,index2,v2_id};

			new_faces.push_back(face0);
			new_faces.push_back(face1);
			new_faces.push_back(face2);
			new_faces.push_back(face3);
		}
	}
}

//do loop subdivision for even vertices
void loop_subdiv_even(HalfEdgeMesh &halfEdgeMesh,vector<Vertex>& new_vertexes){

	vector<HEVtx> HEVtxes = halfEdgeMesh.getHEVtxes();

	for(int i=0;i<HEVtxes.size();i++){
		if(halfEdgeMesh.isOnBoundary(i)){
			vector<int> adjVtx_ids;
			halfEdgeMesh.getBoundaryAdjacentVertexes(i, adjVtx_ids);

			new_vertexes.at(i).x=(new_vertexes.at(adjVtx_ids[0]).x+new_vertexes.at(adjVtx_ids[1]).x+6*(new_vertexes.at(i).x))/8.0;
			new_vertexes.at(i).y=(new_vertexes.at(adjVtx_ids[0]).y+new_vertexes.at(adjVtx_ids[1]).y+6*(new_vertexes.at(i).y))/8.0;
			new_vertexes.at(i).z=(new_vertexes.at(adjVtx_ids[0]).z+new_vertexes.at(adjVtx_ids[1]).z+6*(new_vertexes.at(i).z))/8.0;
		}
		else{
			vector<int> adjVtx_ids;
			halfEdgeMesh.getAdjacentVertexes(i, adjVtx_ids);

			int n=adjVtx_ids.size();

			if(n==3){		
				new_vertexes.at(i).x=(3*(new_vertexes.at(adjVtx_ids[0]).x+new_vertexes.at(adjVtx_ids[1]).x+new_vertexes.at(adjVtx_ids[2]).x)+7*new_vertexes.at(i).x)/16.0;
				new_vertexes.at(i).y=(3*(new_vertexes.at(adjVtx_ids[0]).y+new_vertexes.at(adjVtx_ids[1]).y+new_vertexes.at(adjVtx_ids[2]).y)+7*new_vertexes.at(i).y)/16.0;
				new_vertexes.at(i).z=(3*(new_vertexes.at(adjVtx_ids[0]).z+new_vertexes.at(adjVtx_ids[1]).z+new_vertexes.at(adjVtx_ids[2]).z)+7*new_vertexes.at(i).z)/16.0;

			}
			else if(n>3){
				float beta=3/(8.0*n);
				float x_tem=0.0;
				float y_tem=0.0;
				float z_tem=0.0;

				for(int j=0;j<n;j++){		
					x_tem+=beta*new_vertexes.at(adjVtx_ids[j]).x;
					y_tem+=beta*new_vertexes.at(adjVtx_ids[j]).y;
					z_tem+=beta*new_vertexes.at(adjVtx_ids[j]).z;

				}
				new_vertexes.at(i).x=x_tem+5*new_vertexes.at(i).x/8.0;
				new_vertexes.at(i).y=y_tem+5*new_vertexes.at(i).y/8.0;
				new_vertexes.at(i).z=z_tem+5*new_vertexes.at(i).z/8.0;

			}
		}
	}
}

//compute vertexes position for modified Butterfly subdivision
void comVtxPosForMBS(HalfEdgeMesh &halfEdgeMesh,int he_index,int v0_id,int v1_id,vector<Vertex>& new_vertexes,vector<int> &flags,vector<pair<int,int>> &vertexes_pair){

	vector<HEHalfEdge> HEHalfEdges = halfEdgeMesh.getHEHalfEdges();
	HEHalfEdge he=HEHalfEdges.at(he_index);

	vector<HEVtx> HEVtxes = halfEdgeMesh.getHEVtxes();

	if(halfEdgeMesh.isBoundary(he)&&flags.at(he_index)==0){

		vector<int> adjVtx_ids0;
		halfEdgeMesh.getBoundaryAdjacentVertexes(v0_id, adjVtx_ids0);

		int v_tem1;

		for(int k=0;k<adjVtx_ids0.size();k++){
			if(adjVtx_ids0.at(k)!=v1_id){
				v_tem1=adjVtx_ids0.at(k);
				break;
			}
		}

		vector<int> adjVtx_ids1;
		halfEdgeMesh.getBoundaryAdjacentVertexes(v1_id, adjVtx_ids1);

		int v_tem2;

		for(int k=0;k<adjVtx_ids1.size();k++){
			if(adjVtx_ids1.at(k)!=v0_id){
				v_tem2=adjVtx_ids1.at(k);
				break;
			}
		}

		Vertex new_vtx;
		new_vtx.x=9*(HEVtxes.at(v0_id).x+HEVtxes.at(v1_id).x)/16.0-(HEVtxes.at(v_tem1).x+HEVtxes.at(v_tem2).x)/16.0;
		new_vtx.y=9*(HEVtxes.at(v0_id).y+HEVtxes.at(v1_id).y)/16.0-(HEVtxes.at(v_tem1).y+HEVtxes.at(v_tem2).y)/16.0;
		new_vtx.z=9*(HEVtxes.at(v0_id).z+HEVtxes.at(v1_id).z)/16.0-(HEVtxes.at(v_tem1).z+HEVtxes.at(v_tem2).z)/16.0;
		new_vertexes.push_back(new_vtx);

		pair<int,int> pr(v0_id,v1_id);
		vertexes_pair.push_back(pr);

		flags.at(he_index)=1;
	}
	else if(flags.at(he_index)==0){
		vector<int> adjVtx_ids0;
		vector<int> adjVtx_ids1;

		halfEdgeMesh.getSequentialAdjacentVertexes(he_index, adjVtx_ids0, adjVtx_ids1);

		if(adjVtx_ids0.size()==6&&adjVtx_ids1.size()==6){
			Vertex new_vtx;
			new_vtx.x=(HEVtxes.at(v0_id).x+HEVtxes.at(v1_id).x)/2.0+(HEVtxes.at(adjVtx_ids0.at(1)).x+HEVtxes.at(adjVtx_ids0.at(5)).x)/8.0-(HEVtxes.at(adjVtx_ids0.at(2)).x+HEVtxes.at(adjVtx_ids0.at(4)).x)/16.0-(HEVtxes.at(adjVtx_ids1.at(2)).x+HEVtxes.at(adjVtx_ids1.at(4)).x)/16.0;
			new_vtx.y=(HEVtxes.at(v0_id).y+HEVtxes.at(v1_id).y)/2.0+(HEVtxes.at(adjVtx_ids0.at(1)).y+HEVtxes.at(adjVtx_ids0.at(5)).y)/8.0-(HEVtxes.at(adjVtx_ids0.at(2)).y+HEVtxes.at(adjVtx_ids0.at(4)).y)/16.0-(HEVtxes.at(adjVtx_ids1.at(2)).y+HEVtxes.at(adjVtx_ids1.at(4)).y)/16.0;
			new_vtx.z=(HEVtxes.at(v0_id).z+HEVtxes.at(v1_id).z)/2.0+(HEVtxes.at(adjVtx_ids0.at(1)).z+HEVtxes.at(adjVtx_ids0.at(5)).z)/8.0-(HEVtxes.at(adjVtx_ids0.at(2)).z+HEVtxes.at(adjVtx_ids0.at(4)).z)/16.0-(HEVtxes.at(adjVtx_ids1.at(2)).z+HEVtxes.at(adjVtx_ids1.at(4)).z)/16.0;

			new_vertexes.push_back(new_vtx);

			pair<int,int> pr(v0_id,v1_id);
			vertexes_pair.push_back(pr);

			flags.at(he_index)=1;
			flags.at(he.twin)=1;
		}


		if((adjVtx_ids0.size()!=6&&adjVtx_ids1.size()==6)){
			if(adjVtx_ids0.size()==3){
				Vertex new_vtx;
				new_vtx.x=9*HEVtxes.at(v0_id).x/12.0+5*HEVtxes.at(v1_id).x/12.0-(HEVtxes.at(adjVtx_ids0.at(1)).x+HEVtxes.at(adjVtx_ids0.at(2)).x)/12.0;
				new_vtx.y=9*HEVtxes.at(v0_id).y/12.0+5*HEVtxes.at(v1_id).y/12.0-(HEVtxes.at(adjVtx_ids0.at(1)).y+HEVtxes.at(adjVtx_ids0.at(2)).y)/12.0;
				new_vtx.z=9*HEVtxes.at(v0_id).z/12.0+5*HEVtxes.at(v1_id).z/12.0-(HEVtxes.at(adjVtx_ids0.at(1)).z+HEVtxes.at(adjVtx_ids0.at(2)).z)/12.0;

				new_vertexes.push_back(new_vtx);

				pair<int,int> pr(v0_id,v1_id);
				vertexes_pair.push_back(pr);

				flags.at(he_index)=1;
				flags.at(he.twin)=1;
			}
			else if(adjVtx_ids0.size()==4){
				Vertex new_vtx;
				new_vtx.x=6*HEVtxes.at(v0_id).x/8.0+3*HEVtxes.at(v1_id).x/8.0-HEVtxes.at(adjVtx_ids0.at(2)).x/8.0;
				new_vtx.y=6*HEVtxes.at(v0_id).y/8.0+3*HEVtxes.at(v1_id).y/8.0-HEVtxes.at(adjVtx_ids0.at(2)).y/8.0;
				new_vtx.z=6*HEVtxes.at(v0_id).z/8.0+3*HEVtxes.at(v1_id).z/8.0-HEVtxes.at(adjVtx_ids0.at(2)).z/8.0;

				new_vertexes.push_back(new_vtx);

				pair<int,int> pr(v0_id,v1_id);
				vertexes_pair.push_back(pr);

				flags.at(he_index)=1;
				flags.at(he.twin)=1;
			}
			else if(adjVtx_ids0.size()>=5){

				int k=adjVtx_ids0.size();
				float tem_x=0;
				float tem_y=0;
				float tem_z=0;

				float sum_rate=0;

				for(int n=0;n<k;n++){
					float rate=(1/4.0+cos((2*n*PI)/k)+ cos((4*n*PI)/k)/2.0)/k;
					sum_rate+=rate;

					tem_x+=HEVtxes.at(adjVtx_ids0.at(n)).x*rate;
					tem_y+=HEVtxes.at(adjVtx_ids0.at(n)).y*rate;
					tem_z+=HEVtxes.at(adjVtx_ids0.at(n)).z*rate;
				}

				tem_x+=HEVtxes.at(v0_id).x*(1-sum_rate);
				tem_y+=HEVtxes.at(v0_id).y*(1-sum_rate);
				tem_z+=HEVtxes.at(v0_id).z*(1-sum_rate);

				Vertex new_vtx;
				new_vtx.x=tem_x;
				new_vtx.y=tem_y;
				new_vtx.z=tem_z;

				new_vertexes.push_back(new_vtx);

				pair<int,int> pr(v0_id,v1_id);
				vertexes_pair.push_back(pr);

				flags.at(he_index)=1;
				flags.at(he.twin)=1;
			}
		}

		if((adjVtx_ids0.size()==6&&adjVtx_ids1.size()!=6)){
			if(adjVtx_ids1.size()==3){
				Vertex new_vtx;
				new_vtx.x=9*HEVtxes.at(v1_id).x/12.0+5*HEVtxes.at(v0_id).x/12.0-(HEVtxes.at(adjVtx_ids1.at(1)).x+HEVtxes.at(adjVtx_ids1.at(2)).x)/12.0;
				new_vtx.y=9*HEVtxes.at(v1_id).y/12.0+5*HEVtxes.at(v0_id).y/12.0-(HEVtxes.at(adjVtx_ids1.at(1)).y+HEVtxes.at(adjVtx_ids1.at(2)).y)/12.0;
				new_vtx.z=9*HEVtxes.at(v1_id).z/12.0+5*HEVtxes.at(v0_id).z/12.0-(HEVtxes.at(adjVtx_ids1.at(1)).z+HEVtxes.at(adjVtx_ids1.at(2)).z)/12.0;

				new_vertexes.push_back(new_vtx);

				pair<int,int> pr(v1_id,v0_id);
				vertexes_pair.push_back(pr);

				flags.at(he_index)=1;
				flags.at(he.twin)=1;
			}
			else if(adjVtx_ids1.size()==4){
				Vertex new_vtx;
				new_vtx.x=6*HEVtxes.at(v1_id).x/8.0+3*HEVtxes.at(v0_id).x/8.0-HEVtxes.at(adjVtx_ids1.at(2)).x/8.0;
				new_vtx.y=6*HEVtxes.at(v1_id).y/8.0+3*HEVtxes.at(v0_id).y/8.0-HEVtxes.at(adjVtx_ids1.at(2)).y/8.0;
				new_vtx.z=6*HEVtxes.at(v1_id).z/8.0+3*HEVtxes.at(v0_id).z/8.0-HEVtxes.at(adjVtx_ids1.at(2)).z/8.0;

				new_vertexes.push_back(new_vtx);

				pair<int,int> pr(v1_id,v0_id);
				vertexes_pair.push_back(pr);

				flags.at(he_index)=1;
				flags.at(he.twin)=1;
			}
			else if(adjVtx_ids1.size()>=5){

				int k=adjVtx_ids1.size();
				float tem_x=0;
				float tem_y=0;
				float tem_z=0;

				float sum_rate=0;

				for(int n=0;n<k;n++){
					float rate=(1/4.0+cos((2*n*PI)/k)+ cos((4*n*PI)/k)/2.0)/k;
					sum_rate+=rate;

					tem_x+=HEVtxes.at(adjVtx_ids1.at(n)).x*rate;
					tem_y+=HEVtxes.at(adjVtx_ids1.at(n)).y*rate;
					tem_z+=HEVtxes.at(adjVtx_ids1.at(n)).z*rate;
				}

				tem_x+=HEVtxes.at(v1_id).x*(1-sum_rate);
				tem_y+=HEVtxes.at(v1_id).y*(1-sum_rate);
				tem_z+=HEVtxes.at(v1_id).z*(1-sum_rate);


				Vertex new_vtx;
				new_vtx.x=tem_x;
				new_vtx.y=tem_y;
				new_vtx.z=tem_z;

				new_vertexes.push_back(new_vtx);

				pair<int,int> pr(v1_id,v0_id);
				vertexes_pair.push_back(pr);

				flags.at(he_index)=1;
				flags.at(he.twin)=1;
			}
		}

		if((adjVtx_ids0.size()!=6&&adjVtx_ids1.size()!=6)){

			float tem_x0=0;
			float tem_y0=0;
			float tem_z0=0;

			if(adjVtx_ids0.size()==3){
				tem_x0=9*HEVtxes.at(v0_id).x/12.0+5*HEVtxes.at(v1_id).x/12.0-(HEVtxes.at(adjVtx_ids0.at(1)).x+HEVtxes.at(adjVtx_ids0.at(2)).x)/12.0;
				tem_y0=9*HEVtxes.at(v0_id).y/12.0+5*HEVtxes.at(v1_id).y/12.0-(HEVtxes.at(adjVtx_ids0.at(1)).y+HEVtxes.at(adjVtx_ids0.at(2)).y)/12.0;
				tem_z0=9*HEVtxes.at(v0_id).z/12.0+5*HEVtxes.at(v1_id).z/12.0-(HEVtxes.at(adjVtx_ids0.at(1)).z+HEVtxes.at(adjVtx_ids0.at(2)).z)/12.0;

			}
			else if(adjVtx_ids0.size()==4){
				tem_x0=6*HEVtxes.at(v0_id).x/8.0+3*HEVtxes.at(v1_id).x/8.0-HEVtxes.at(adjVtx_ids0.at(2)).x/8.0;
				tem_y0=6*HEVtxes.at(v0_id).y/8.0+3*HEVtxes.at(v1_id).y/8.0-HEVtxes.at(adjVtx_ids0.at(2)).y/8.0;
				tem_z0=6*HEVtxes.at(v0_id).z/8.0+3*HEVtxes.at(v1_id).z/8.0-HEVtxes.at(adjVtx_ids0.at(2)).z/8.0;
			}
			else if(adjVtx_ids0.size()>=5){
				int k=adjVtx_ids0.size();
				float sum_rate=0;

				for(int n=0;n<k;n++){
					float rate=(1/4.0+cos((2*n*PI)/k)+ cos((4*n*PI)/k)/2.0)/k;
					sum_rate+=rate;

					tem_x0+=HEVtxes.at(adjVtx_ids0.at(n)).x*rate;
					tem_y0+=HEVtxes.at(adjVtx_ids0.at(n)).y*rate;
					tem_z0+=HEVtxes.at(adjVtx_ids0.at(n)).z*rate;
				}

				tem_x0+=HEVtxes.at(v0_id).x*(1-sum_rate);
				tem_y0+=HEVtxes.at(v0_id).y*(1-sum_rate);
				tem_z0+=HEVtxes.at(v0_id).z*(1-sum_rate);
			}

			float tem_x1=0;
			float tem_y1=0;
			float tem_z1=0;

			if(adjVtx_ids1.size()==3){

				tem_x1=9*HEVtxes.at(v1_id).x/12.0+5*HEVtxes.at(v0_id).x/12.0-(HEVtxes.at(adjVtx_ids1.at(1)).x+HEVtxes.at(adjVtx_ids1.at(2)).x)/12.0;
				tem_y1=9*HEVtxes.at(v1_id).y/12.0+5*HEVtxes.at(v0_id).y/12.0-(HEVtxes.at(adjVtx_ids1.at(1)).y+HEVtxes.at(adjVtx_ids1.at(2)).y)/12.0;
				tem_z1=9*HEVtxes.at(v1_id).z/12.0+5*HEVtxes.at(v0_id).z/12.0-(HEVtxes.at(adjVtx_ids1.at(1)).z+HEVtxes.at(adjVtx_ids1.at(2)).z)/12.0;

			}
			else if(adjVtx_ids1.size()==4){

				tem_x1=6*HEVtxes.at(v1_id).x/8.0+3*HEVtxes.at(v0_id).x/8.0-HEVtxes.at(adjVtx_ids1.at(2)).x/8.0;
				tem_y1=6*HEVtxes.at(v1_id).y/8.0+3*HEVtxes.at(v0_id).y/8.0-HEVtxes.at(adjVtx_ids1.at(2)).y/8.0;
				tem_z1=6*HEVtxes.at(v1_id).z/8.0+3*HEVtxes.at(v0_id).z/8.0-HEVtxes.at(adjVtx_ids1.at(2)).z/8.0;

			}
			else if(adjVtx_ids1.size()>=5){
				int k=adjVtx_ids1.size();
				float sum_rate=0;

				for(int n=0;n<k;n++){
					float rate=(1/4.0+cos((2*n*PI)/k)+ cos((4*n*PI)/k)/2.0)/k;
					sum_rate+=rate;

					tem_x1+=HEVtxes.at(adjVtx_ids1.at(n)).x*rate;
					tem_y1+=HEVtxes.at(adjVtx_ids1.at(n)).y*rate;
					tem_z1+=HEVtxes.at(adjVtx_ids1.at(n)).z*rate;

				}

				tem_x1+=HEVtxes.at(v1_id).x*(1-sum_rate);
				tem_y1+=HEVtxes.at(v1_id).y*(1-sum_rate);
				tem_z1+=HEVtxes.at(v1_id).z*(1-sum_rate);
			}

			Vertex new_vtx;
			new_vtx.x=(tem_x0+tem_x1)/2.0;
			new_vtx.y=(tem_y0+tem_y1)/2.0;
			new_vtx.z=(tem_z0+tem_z1)/2.0;

			new_vertexes.push_back(new_vtx);

			pair<int,int> pr(v0_id,v1_id);
			vertexes_pair.push_back(pr);

			flags.at(he_index)=1;
			flags.at(he.twin)=1;
		}
	}
}

//do the Loop subdivision
void loopSubdivision(HalfEdgeMesh &halfEdgeMesh,HalfEdgeMesh &new_halfEdgeMesh){
	new_halfEdgeMesh.clear();

	vector<Vertex> new_vertexes;
	vector<Face> new_faces;

	loop_subdiv_odd(halfEdgeMesh,new_vertexes,new_faces);
	loop_subdiv_even(halfEdgeMesh,new_vertexes);

	new_halfEdgeMesh.init(new_vertexes,new_faces);
}

//the modified Butterfly subdivision
void mButterflySubdivision(HalfEdgeMesh &halfEdgeMesh,HalfEdgeMesh &new_halfEdgeMesh){

	vector<HEVtx> HEVtxes = halfEdgeMesh.getHEVtxes();
	vector<HEFace> HEFaces = halfEdgeMesh.getHEFaces();
	vector<HEHalfEdge> HEHalfEdges = halfEdgeMesh.getHEHalfEdges();

	const int faceNum=HEFaces.size();
	const int vertexNum=HEVtxes.size();
	const int heNum=HEHalfEdges.size();

	vector<Vertex> new_vertexes;
	vector<Face> new_faces;

	//add old vertexes
	for(int i=0;i<vertexNum;i++){
		Vertex vtx={HEVtxes.at(i).x,HEVtxes.at(i).y,HEVtxes.at(i).z};
		new_vertexes.push_back(vtx);
	}

	vector<int> flags;
	for(int i=0;i<heNum;i++){
		flags.push_back(0);
	}

	vector<pair<int,int>> vertexes_pair;

	//add new vertexes
	for(int i=0;i<faceNum;i++){

		int he_index0=HEFaces.at(i).edge;
		HEHalfEdge he0=HEHalfEdges.at(he_index0);
		int v0_id=he0.origin;

		int he_index1=he0.next;
		HEHalfEdge he1=HEHalfEdges.at(he_index1);
		int v1_id=he1.origin;

		int he_index2=he1.next;
		HEHalfEdge he2=HEHalfEdges.at(he_index2);
		int v2_id=he2.origin;

		comVtxPosForMBS(halfEdgeMesh,he_index0,v0_id,v1_id, new_vertexes, flags, vertexes_pair);
		comVtxPosForMBS(halfEdgeMesh,he_index1,v1_id,v2_id, new_vertexes, flags, vertexes_pair);
		comVtxPosForMBS(halfEdgeMesh,he_index2,v2_id,v0_id, new_vertexes, flags, vertexes_pair);
	}

	//gen new faces
	for(int i=0;i<faceNum;i++){
		int he_index0=HEFaces.at(i).edge;
		HEHalfEdge he0=HEHalfEdges.at(he_index0);
		int v0_id=he0.origin;

		int he_index1=he0.next;
		HEHalfEdge he1=HEHalfEdges.at(he_index1);
		int v1_id=he1.origin;

		int he_index2=he1.next;
		HEHalfEdge he2=HEHalfEdges.at(he_index2);
		int v2_id=he2.origin;

		int index0=getNewVertexIndexByOldVertexes(vertexes_pair,v0_id, v1_id, vertexNum);
		int index1=getNewVertexIndexByOldVertexes(vertexes_pair,v1_id, v2_id, vertexNum);
		int index2=getNewVertexIndexByOldVertexes(vertexes_pair,v2_id, v0_id, vertexNum);

		if(index0!=-1&&index1!=-1&&index2!=-1){
			Face face0={v0_id,index0,index2};
			Face face1={index0,v1_id,index1};
			Face face2={index0,index1,index2};
			Face face3={index1,index2,v2_id};

			new_faces.push_back(face0);
			new_faces.push_back(face1);
			new_faces.push_back(face2);
			new_faces.push_back(face3);
		}
	}

	new_halfEdgeMesh.init(new_vertexes,new_faces);
}
