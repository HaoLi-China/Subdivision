#include "gl_draw.h"
#include "subdivision .h"

#define ColoredVertex(c, v) do{ glColor3fv(c); glVertex3fv(v); }while(0)

float thetaX=0.0;
float thetaY=0.0;
float scaleFactor=1.0;

float dx=0;
float dy=0;
float oldy=-1;
float oldx=-1;

int width=600;
int height=500;

float centerX=0;
float centerY=0;
float centerZ=0;

float fleft=0;
float fbottom=0;
float ffar=0; 
float fright=0;
float ftop=0;
float fnear=0;

float rad=0;

HalfEdgeMesh halfEdgeMesh;
HalfEdgeMesh halfEdgeMesh_tem;

int isRendering=0;

//get normal of a face
void getNormal(GLfloat p1[3],GLfloat p2[3],GLfloat p3[3],GLfloat *pN)
{
	GLfloat PL1[3]; 
	GLfloat PL2[3]; 

	for(int i = 0; i < 3; i++)
	{
		PL1[i] = p2[i] - p1[i];
		PL2[i] = p3[i] - p2[i];
	}

	GLfloat PN[3]; 
	PN[0] = PL1[1]*PL2[2] - PL1[2]*PL2[1];
	PN[1] = PL1[2]*PL2[0] - PL1[0]*PL2[2];
	PN[2] = PL1[0]*PL2[1] - PL1[1]*PL2[0];

	//normalize
	GLfloat NL = sqrt(PN[0]*PN[0]+PN[1]*PN[1]+PN[2]*PN[2]);
	*pN = PN[0]/NL;
	*(pN+1) = PN[1]/NL;
	*(pN+2) = PN[2]/NL;
}


//compute the bounding box of the model
void compute_bounding_box(vector<HEVtx> vtxes,float *min_x,float *min_y,float *min_z, float *max_x, float *max_y, float *max_z){
	*min_x=vtxes.at(0).x;
	*min_y=vtxes.at(0).y;
	*min_z=vtxes.at(0).z;
	*max_x=vtxes.at(0).x;
	*max_y=vtxes.at(0).y;
	*max_z=vtxes.at(0).z;

	for (int i=0; i<vtxes.size(); i++) {
		float x, y, z;
		x=vtxes.at(i).x;
		y=vtxes.at(i).y;
		z=vtxes.at(i).z;

		if(x<(*min_x)){
			(*min_x)=x;
		}
		else if(x>(*max_x)){
			(*max_x)=x;
		}

		if(y<(*min_y)){
			(*min_y)=y;
		}
		else if(y>(*max_y)){
			(*max_y)=y;
		}

		if(z<(*min_z)){
			(*min_z)=z;
		}
		else if(z>(*max_z)){
			(*max_z)=z;
		}
	}
}

//read data from a file
bool readData(const char* fileName,HalfEdgeMesh &halfEdgeMesh){

	vector<Vertex> vertexes;
	vector<Face> faces;
	if(!read_from_wrl(fileName, vertexes, faces)){
		return false;
	}

	halfEdgeMesh.init(vertexes, faces);
	return true;
}

//save data to a file
void saveData(const char* fileName,HalfEdgeMesh &halfEdgeMesh){

	vector<Vertex> vertexes;
	vector<Face> faces;

	vector<HEFace> HEFaces=halfEdgeMesh.getHEFaces();
	vector<HEVtx> HEVtxes = halfEdgeMesh.getHEVtxes();

	for(int i=0; i<HEVtxes.size(); i++){
		Vertex vtx={HEVtxes.at(i).x,HEVtxes.at(i).y,HEVtxes.at(i).z};
		vertexes.push_back(vtx);
	}

	for(int i=0; i<HEFaces.size(); i++){
		int v0_id,v1_id,v2_id;
		halfEdgeMesh.getVertexesInFace(i, &v0_id, &v1_id, &v2_id);
		Face face={v0_id,v1_id,v2_id};
		faces.push_back(face);
	}

	if(write_to_wrl(fileName, vertexes, faces)){
		printf("succeed!\n");
	}
}

//init
void init(void)
{
	glMatrixMode (GL_PROJECTION);    
	glLoadIdentity ();  

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_CULL_FACE);        // Do not calculate inside of jet
	glFrontFace(GL_CCW);        // Counter clock-wise polygons face out

	//set param of light 
	GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_specular[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_position[] = { 3.0, 3.0, 3.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);    //Ambient
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);    //Diffuse
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);  //Specular
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);  //Position

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//set param of material 
	GLfloat mat_ambient[] = { 0.4f, 0.5f, 0.6f, 0.3f };
	GLfloat mat_diffuse[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat mat_specular[] = { 0.8f, 0.8f, 0.8f, 0.8f };
	GLfloat mat_shininess = 20.0;

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);	//Specular
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);	//Ambient
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);	//Diffuse
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);	//shininess

	glShadeModel(GL_SMOOTH);

	glOrtho(-rad,rad,-rad,rad,rad,-rad); 
}

//display the image
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (thetaY<0){
		thetaY=thetaY+360;
	}
	if (thetaY>360){
		thetaY=thetaY-360;
	}
	if (thetaX<0){
		thetaX=thetaX+360;
	}
	if (thetaX>360){
		thetaX=thetaX-360;
	}

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRotatef(thetaY,0,1,0);
	glRotatef(thetaX,1,0,0);
	glScalef(scaleFactor,scaleFactor,scaleFactor);
	glTranslatef(-centerX,-centerY,-centerZ);

	vector<HEFace> HEFaces=halfEdgeMesh.getHEFaces();
	vector<HEVtx> HEVtxes = halfEdgeMesh.getHEVtxes();

	if(isRendering==0){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glBegin(GL_TRIANGLES);

		for(int i=0; i<HEFaces.size(); i++){

			int v0_id,v1_id,v2_id;
			halfEdgeMesh.getVertexesInFace(i, &v0_id, &v1_id, &v2_id);

			glVertex3f(HEVtxes.at(v0_id).x, HEVtxes.at(v0_id).y, HEVtxes.at(v0_id).z);
			glVertex3f(HEVtxes.at(v1_id).x, HEVtxes.at(v1_id).y, HEVtxes.at(v1_id).z);
			glVertex3f(HEVtxes.at(v2_id).x, HEVtxes.at(v2_id).y, HEVtxes.at(v2_id).z);
		}
		glEnd();
	}
	else if(isRendering==1){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_TRIANGLES);

		for(int i=0; i<HEFaces.size(); i++){

			int v0_id,v1_id,v2_id;
			halfEdgeMesh.getVertexesInFace(i, &v0_id, &v1_id, &v2_id);

			GLfloat P0[]={HEVtxes.at(v0_id).x, HEVtxes.at(v0_id).y, HEVtxes.at(v0_id).z};
			GLfloat P1[]={HEVtxes.at(v1_id).x, HEVtxes.at(v1_id).y, HEVtxes.at(v1_id).z};
			GLfloat P2[]={HEVtxes.at(v2_id).x, HEVtxes.at(v2_id).y, HEVtxes.at(v2_id).z};

			GLfloat Normal[3] = {0};
			getNormal(P0, P1, P2,Normal);
			glNormal3fv(Normal);

			glVertex3f(HEVtxes.at(v0_id).x, HEVtxes.at(v0_id).y, HEVtxes.at(v0_id).z);
			glVertex3f(HEVtxes.at(v1_id).x, HEVtxes.at(v1_id).y, HEVtxes.at(v1_id).z);
			glVertex3f(HEVtxes.at(v2_id).x, HEVtxes.at(v2_id).y, HEVtxes.at(v2_id).z);

		}

		glEnd();
	}

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

//reshape
void reshape(int width,int height)
{
	if (width <= height)
		glViewport(0, 0, (GLsizei)width, (GLsizei)width);
	else
		glViewport(0, 0, (GLsizei)height, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);      
	glLoadIdentity();
	glOrtho(-rad*1.5,rad*1.5,-rad*1.5,rad*1.5,rad*1.5,-rad*1.5); 
}

//do when some keys presses
void onKeyBoard(unsigned char key,int x,int y)
{
	switch (key)
	{
		//zoom
	case 'A':              
	case 'a':
		scaleFactor*=0.9;
		glutPostRedisplay();
		break;
		//shrink
	case 'D':
	case 'd':
		scaleFactor*=1.1;
		glutPostRedisplay();
		break;
		//recover
	case 'R':                     
	case 'r':
		thetaX=0;
		thetaY=0;
		scaleFactor=1.0;
		glutPostRedisplay();
		break;
		//loop subdivision
	case 'L':                     
	case 'l':
		loopSubdivision(halfEdgeMesh_tem,halfEdgeMesh);

		halfEdgeMesh_tem.clear();
		halfEdgeMesh_tem.setHEVtxes(halfEdgeMesh.getHEVtxes());
		halfEdgeMesh_tem.setHEFaces(halfEdgeMesh.getHEFaces());
		halfEdgeMesh_tem.setHEHalfEdges(halfEdgeMesh.getHEHalfEdges());

		glutPostRedisplay();
		break;
		//modified Butterfly subdivision
	case 'M':                     
	case 'm':
		mButterflySubdivision(halfEdgeMesh_tem,halfEdgeMesh);

		halfEdgeMesh_tem.clear();
		halfEdgeMesh_tem.setHEVtxes(halfEdgeMesh.getHEVtxes());
		halfEdgeMesh_tem.setHEFaces(halfEdgeMesh.getHEFaces());
		halfEdgeMesh_tem.setHEHalfEdges(halfEdgeMesh.getHEHalfEdges());

		glutPostRedisplay();
		break;
		//show mesh
	case 'F':                     
	case 'f':
		isRendering=1;
		glutPostRedisplay();
		break;
		//show line
	case 'E':                     
	case 'e':
		isRendering=0;
		glutPostRedisplay();
		break;
		//save data
	case 'S':                    
	case 's':
		char fileName[256];
		printf("Save data to wrl file.\nPlease input the file path.\n");
		scanf("%s",fileName);
		saveData(fileName, halfEdgeMesh);
		break;
		//exit
	case 'Q':                    
	case 'q':
		exit(0);
		break;
	default:
		break;
	}
}

//do when mouse clicks
void onMouseClick(int button, int state, int x, int y)      
{
	if(state==GLUT_DOWN && button==GLUT_LEFT_BUTTON){                  
		oldx=x,oldy=y;
	}
	if (state==GLUT_DOWN && button==GLUT_RIGHT_BUTTON)             
	{
		thetaX=0;thetaY=0;scaleFactor=1;
		glutPostRedisplay();
	}
	if (state==GLUT_DOWN && button==GLUT_MIDDLE_BUTTON)
	{

	}
}

//do when mouse moves
void onMouseMove(int x,int y)
{
	dx+=x-oldx;
	dy+=y-oldy;
	thetaX=dy/width*90;
	thetaY=dx/height*90;
	oldx=x,oldy=y;              
	glutPostRedisplay();
}

//do when special keys presses
void onSpecialKey(int key, int x, int y){
	switch(key){
	case GLUT_KEY_UP:
		thetaY-=6;
		break;
	case GLUT_KEY_DOWN:
		thetaY+=6;
		break;
	case GLUT_KEY_LEFT:
		thetaX-=6;
		break;
	case GLUT_KEY_RIGHT:
		thetaX+=6;
		break;
	default:
		printf("please select command correctly...\n");
		break;
	}
}

//refresh
void reDisplay(void){
	glutPostRedisplay();
}

void setCenterPoint(float cenX,float cenY,float cenZ){
	centerX=cenX;
	centerY=cenY;
	centerZ=cenZ;
}

//show image
void gl_show(int argc, char ** argv){

	char fileName[256];
	printf("Read data from wrl file.\nPlease input the file path.\n");
	scanf("%s",fileName);

	if(!readData(fileName, halfEdgeMesh_tem)){
		return;
	}

	printf("*************Subdivision****************\n");

	printf("Command:<A/a>zoom\n");
	printf("Command:<D/d>shrink\n");
	printf("Command:<R/r>reset position\n");
	printf("Command:<L/l>loopSubdivison\n");
	printf("Command:<M/m>modifiedButterflySubdivison\n");
	printf("Command:<F/f>show mesh\n");
	printf("Command:<E/e>show line\n");
	printf("Command:<S/s>save Subdivision data\n");
	printf("Command:<Q/q>exit\n");
	printf("Command:<direction key ¡ü¡ý¡û¡ú>navigation\n");
	printf("Command:<mouse drag>navigation\n");

	halfEdgeMesh.setHEVtxes(halfEdgeMesh_tem.getHEVtxes());
	halfEdgeMesh.setHEFaces(halfEdgeMesh_tem.getHEFaces());
	halfEdgeMesh.setHEHalfEdges(halfEdgeMesh_tem.getHEHalfEdges());

	compute_bounding_box(halfEdgeMesh.getHEVtxes(), &fleft, &fbottom, &ffar, &fright, &ftop, &fnear);

	vector<float> fv;
	fv.push_back(std::abs(fleft));
	fv.push_back(std::abs(fright));
	fv.push_back(std::abs(fbottom));
	fv.push_back(std::abs(ftop));
	fv.push_back(std::abs(ffar));
	fv.push_back(std::abs(fnear));

	for(int i=0;i<fv.size();i++){
		if(rad<fv.at(i)){
			rad=fv.at(i);
		}
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Subdivision View");
	init();
	glutDisplayFunc(&display);
	glutReshapeFunc(&reshape);
	glutKeyboardFunc(&onKeyBoard);
	glutSpecialFunc(&onSpecialKey);
	glutMouseFunc(&onMouseClick);
	glutMotionFunc(&onMouseMove);
	glutIdleFunc(&reDisplay);
	glutMainLoop();
}




