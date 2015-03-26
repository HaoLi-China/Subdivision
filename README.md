# Subdivision
Subdivision of mesh

1.Problem Statement:

In the field of 3D computer graphics, We usually want to make a coarse mesh more smooth. The smooth surface can be calculated from the coarse mesh as the limit of a recursive process of subdividing each polygonal face into smaller faces that better approximate the smooth surface. We call this process subdivision.
In this project, we focus on triangular meshes, the input data is read from a basic VRML 3D model file(.wrl), then the code constructs the data as a half edge structure, and do loop subdivision or modified butterfly subdivision with this structure. Finally, the code can store the result data of subdivision to a .wrl file. 


2.My implementation:

The function of the code is listed here:
1)Be able to read and write basic VRML 3D model files (.wrl)
2)Implemented the half edge data structure for representing, traversing and manipulating 3D triangular meshes.
3)Implemented the loop subdivision. 
4)Implemented the modified butterfly subdivision.
5)Using openGl to show the mesh, it can show not only vertexes and edges but also surfaces.
