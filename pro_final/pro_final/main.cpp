//					Semestre 2018 - 2  Proyecto final//
//************************************************************//
//************************************************************//
//************** Alumno (s): Guevara Ch�vez Marco Antonio *********************************//
//*************				Moreno Mar�n Christian							******//
//*************											******//
//************************************************************//
//************************************************************//

#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#include "cmodel/CModel.h"		//PERMITE TEXTURAS EN 3D

static GLuint ciudad_display_list;

//keyframe

float movhombro = 0.0;
float anghom = 0.0;
float movpie = 0.0;

#define MAX_FRAMES 20  // Cuantos cuadros capturamos por segundo
int i_max_steps = 90;
int i_curr_steps = 0;

typedef struct _frame  // Debemos declarar la variable y otra que es su incremento
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ

	float transZ = -5.0f;
	float transX = 0.0f;
	float angleX = 0.0f;
	float angleY = 0.0f;
	int screenW = 0.0;
	int screenH = 0.0;
	float movhombro = 0.0;
	float movcodo = 0.0;
	float inchom = 0.0;
	float movpie = 0.0;
	float incpie = 0.0;


}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 20;			//introducir datos
bool play = false;  //Play en falso
int playIndex = 0;


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int w = 500, h = 500;
int frame = 0, time, timebase = 0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font = (int)GLUT_BITMAP_HELVETICA_18;



GLfloat Diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[] = { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[] = { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

CTexture text1;
CTexture t_pasto;
CTexture t_nubes;
CTexture t_pav;
CTexture t_ladrillo;
CTexture t_ct;
CTexture t_pelota;



CFiguras cubo;
CFiguras sky;

//END NEW//////////////////////////////////////////


CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;

CModel asiento;
CModel arbol;
CModel kiosko;





GLuint createDL()
{
	GLuint ciudadDL;
	//GLuint cieloDL;

	// Create the id for the list
	ciudadDL = glGenLists(1);
	// start list
	glNewList(ciudadDL, GL_COMPILE);
	// call the function that contains 
	// the rendering commands

	// endList
	glEndList();

	return(ciudadDL);
}

void InitGL(GLvoid)     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);
	//Para construir la figura comentar esto
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	text1.LoadBMP("cielo.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	t_pasto.LoadTGA("pasto.tga");
	t_pasto.BuildGLTexture();
	t_pasto.ReleaseImage();

	t_nubes.LoadTGA("nube.tga");
	t_nubes.BuildGLTexture();
	t_nubes.ReleaseImage();

	t_pav.LoadTGA("pavimento.tga");
	t_pav.BuildGLTexture();
	t_pav.ReleaseImage();

	t_ladrillo.LoadTGA("tabique.tga");
	t_ladrillo.BuildGLTexture();
	t_ladrillo.ReleaseImage();

	t_ct.LoadTGA("ct.tga");
	t_ct.BuildGLTexture();
	t_ct.ReleaseImage();

	t_pelota.LoadTGA("pel.tga");
	t_pelota.BuildGLTexture();
	t_pelota.ReleaseImage();


	//3ds carga
	arbol._3dsLoad("3ds/firtree3.3ds");
	asiento._3dsLoad("3ds/gardenB.3ds");

	//END NEW//////////////////////////////

	objCamera.Position_Camera(0, 2.5f, 3, 0, 2.5f, 0, 0, 1, 0);

	//NEW Crear una lista de dibujo
	//ciudad_display_list = createDL();

	///
	KeyFrame[0].movhombro = 0;	
	KeyFrame[1].movhombro = -55;	
	KeyFrame[2].movhombro = -55;	
	KeyFrame[3].movhombro = -100;	
	KeyFrame[4].movhombro = -55;

	KeyFrame[5].movpie = 0;
	KeyFrame[6].movpie= -25;
	KeyFrame[7].movpie = -40;
	KeyFrame[8].movpie = -25;
	//KeyFrame[].movhombro = -55;



	


}

void humanide(void) {

	//cabeza
	glPushMatrix();
	glScalef(4, 4, 4);
	glColor3f(1, 1, 1);
	fig4.esfera(0.6, 20, 20, 0);
	glPopMatrix();

	//ojos
	glPushMatrix();
	glTranslatef(-0.5, 0, 2.5);
	glScalef(.52, .52, .1);
	glColor3f(0, .1, 1);
	fig3.prisma3(0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0, 2.5);
	glScalef(.52, .52, .1);
	glColor3f(0, .1, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -3, 0);

	//cuello
	glPushMatrix();
	glScalef(3, 2, 3);
	glColor3f(1, 0, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -6, 0);
	//torso
	glPushMatrix();
	glScalef(10, 10, 3);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//pierna izquierda
	//muslo
	glTranslatef(2.5, -7.5, 0);

	glPushMatrix();
	glScalef(2, 5, 3);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -3, 0);
	//rodilla
	glPushMatrix();
	glScalef(2, 1, 3);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -3, 0);

	//espinilla
	glPushMatrix();
	glScalef(2, 5, 3);
	glColor3f(1, 0.5, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -2.75, 0);

	//tobillo
	glPushMatrix();
	glScalef(2, 0.5, 3);
	glColor3f(1, 0, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -1.25, 0);
	//pie
	glPushMatrix();
	glScalef(2, 2, 3);
	glColor3f(0.5, 0, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0);
	glPopMatrix();

	glTranslatef(3, 21.5, 0);

	//brazo izquierdo
	//Hombro1
	glPushMatrix();
	/*glPushMatrix();
	glScalef(1, 2, 2);
	glColor3f(1, 1, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();
	*/
	//hombro2
	glPushMatrix();
	glRotatef(movhombro, 0, 0, 1);
	glPushMatrix();
	glScalef(1, 2, 2);
	glColor3f(1, 1, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();


	//Bicep
	glPushMatrix();
	glTranslatef(2, 0, 0);
	glScalef(3, 2, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Codo
	//glRotatef(angCodo, 0, 1, 0);
	glPushMatrix();
	glTranslatef(3.75, 0, 0);
	glScalef(0.5, 2, 2);
	glColor3f(1, 0, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Antebrazo
	glPushMatrix();
	glTranslatef(6, 0, 0);
	glScalef(4, 2, 2);
	glColor3f(0, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Mu�eca
	//glRotatef(angMuni, 0, 1, 0);
	glPushMatrix();
	glTranslatef(8.25, 0, 0);
	glScalef(0.5, 2, 2);
	glColor3f(1, 1, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Mano
	glPushMatrix();
	glTranslatef(9.5, 0, 0);
	glScalef(2, 2, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo pulgar
	glPushMatrix();
	//glRotatef(angDedP, 1, 0, 0);
	glTranslatef(9.75, 1.25, 0);
	glScalef(.3, .5, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angDedP, 1, 0, 0);
	glTranslatef(9.75, 1.75, 0);
	glScalef(.3, .5, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo indice
	glPushMatrix();
	//glRotatef(angDedI, 0, 1, 0);
	glTranslatef(10.75, .75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angDedI, 0, 1, 0);
	glTranslatef(11.25, .75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angDedI, 0, 1, 0);
	glTranslatef(11.75, .75, 0);
	glScalef(.5, .3, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo medio

	glPushMatrix();
	//glRotatef(angMed, 0, 1, 0);
	glTranslatef(10.75, .25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angMed, 0, 1, 0);
	glTranslatef(11.25, .25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angMed, 0, 1, 0);
	glTranslatef(11.75, .25, 0);
	glScalef(.5, .3, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo anular
	glPushMatrix();
	//glRotatef(angAn, 0, 1, 0);
	glTranslatef(10.75, -.25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angAn, 0, 1, 0);
	glTranslatef(11.25, -.25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angAn, 0, 1, 0);
	glTranslatef(11.75, -.25, 0);
	glScalef(.5, .3, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();
	//me�ique
	glPushMatrix();
	//glRotatef(angMe, 0, 1, 0);
	glTranslatef(10.75, -.75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angMe, 0, 1, 0);
	glTranslatef(11.25, -.75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPopMatrix();


	//Brazo derecha
	//Hombro
	glPushMatrix();
	glTranslatef(-11, 0, 0);
	glRotatef(-movhombro, 0, 0, 1);
	glPushMatrix();
	glScalef(1, 2, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Bicep
	glPushMatrix();
	glTranslatef(-2, 0, 0);
	glScalef(3, 2, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Codo
	//glRotatef(-angCodo, 0, 1, 0);
	glPushMatrix();
	glTranslatef(-3.75, 0, 0);
	glScalef(0.5, 2, 2);
	glColor3f(1, 0, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Antebrazo
	glPushMatrix();
	glTranslatef(-6, 0, 0);
	glScalef(4, 2, 2);
	glColor3f(0, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Mu�eca
	//glRotatef(-angMuni, 0, 1, 0);
	glPushMatrix();
	glTranslatef(-8.25, 0, 0);
	glScalef(0.5, 2, 2);
	glColor3f(1, 1, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Mano
	glPushMatrix();
	glTranslatef(-9.5, 0, 0);
	glScalef(2, 2, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo pulgar
	glPushMatrix();
	//glRotatef(-angDedP, 1, 0, 0);
	glTranslatef(-9.75, 1.25, 0);
	glScalef(.3, .5, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angDedP, 1, 0, 0);
	glTranslatef(-9.75, 1.75, 0);
	glScalef(.3, .5, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo indice
	glPushMatrix();
	//glRotatef(-angDedI, 0, 1, 0);
	glTranslatef(-10.75, .75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angDedI, 0, 1, 0);
	glTranslatef(-11.25, .75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angDedI, 0, 1, 0);
	glTranslatef(-11.75, .75, 0);
	glScalef(.5, .3, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo medio

	glPushMatrix();
	//glRotatef(-angMed, 0, 1, 0);
	glTranslatef(-10.75, .25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angMed, 0, 1, 0);
	glTranslatef(-11.25, .25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angMed, 0, 1, 0);
	glTranslatef(-11.75, .25, 0);
	glScalef(.5, .3, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo anular
	glPushMatrix();
	//glRotatef(-angAn, 0, 1, 0);
	glTranslatef(-10.75, -.25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angAn, 0, 1, 0);
	glTranslatef(-11.25, -.25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angAn, 0, 1, 0);
	glTranslatef(-11.75, -.25, 0);
	glScalef(.5, .3, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();
	//me�ique
	glPushMatrix();
	//glRotatef(-angMe, 0, 1, 0);
	glTranslatef(-10.75, -.75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angMe, 0, 1, 0);
	glTranslatef(-11.25, -.75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPopMatrix();


	//pie derecho
	//muslo

	glTranslatef(-7.5, -11.5, 0);
	glPushMatrix();
	glScalef(2, 5, 3);
	glColor3f(0.6, 0, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();
	glTranslatef(0, -3, 0);
	//rodilla
	glPushMatrix();
	glScalef(2, 1, 3);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -3, 0);

	//espinilla
	glPushMatrix();
	glScalef(2, 5, 3);
	glColor3f(1, 0.5, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -2.75, 0);

	//tobillo
	glPushMatrix();
	glScalef(2, 0.5, 3);
	glColor3f(1, 0, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -1.25, 0);
	//pie
	glPushMatrix();
	glScalef(2, 2, 3);
	glColor3f(0.5, 0, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();



}

void ninio(void) {

	//cabeza
	glPushMatrix();
	glScalef(4, 4, 4);
	glColor3f(1, 1, 1);
	fig4.esfera(0.6, 20, 20, 0);
	glPopMatrix();

	//ojos
	glPushMatrix();
	glTranslatef(-0.5, 0, 2.5);
	glScalef(.52, .52, .1);
	glColor3f(0, .1, 1);
	fig3.prisma3(0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0, 2.5);
	glScalef(.52, .52, .1);
	glColor3f(0, .1, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -3, 0);

	//cuello
	glPushMatrix();
	glScalef(3, 2, 3);
	glColor3f(1, 0, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -6, 0);
	//torso
	glPushMatrix();
	glScalef(10, 10, 3);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//pierna izquierda
	//muslo
	glTranslatef(2.5, -7.5, 0);

	glPushMatrix();
	
	glScalef(2, 5, 3);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -3, 0);
	//rodilla
	glPushMatrix();
	glScalef(2, 1, 3);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -3, 0);

	//espinilla
	glPushMatrix();
	glScalef(2, 5, 3);
	glColor3f(1, 0.5, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -2.75, 0);

	//tobillo
	glPushMatrix();
	glScalef(2, 0.5, 3);
	glColor3f(1, 0, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -1.25, 0);
	//pie
	glPushMatrix();
	glScalef(2, 2, 3);
	glColor3f(0.5, 0, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0);
	glPopMatrix();

	glTranslatef(3, 21.5, 0);

	//brazo izquierdo
	//Hombro1
	
	glPushMatrix();
	glRotatef(-75, 0, 0, 1);
	glPushMatrix();
	//glRotatef(75,0,1,0);
	glScalef(1, 2, 2);
	glColor3f(1, 1, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();


	//Bicep
	glPushMatrix();
	glTranslatef(2, 0, 0);
	glScalef(3, 2, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Codo
	//glRotatef(angCodo, 0, 1, 0);
	glPushMatrix();
	glTranslatef(3.75, 0, 0);
	glScalef(0.5, 2, 2);
	glColor3f(1, 0, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Antebrazo
	glPushMatrix();
	glTranslatef(6, 0, 0);
	glScalef(4, 2, 2);
	glColor3f(0, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Mu�eca
	//glRotatef(angMuni, 0, 1, 0);
	glPushMatrix();
	glTranslatef(8.25, 0, 0);
	glScalef(0.5, 2, 2);
	glColor3f(1, 1, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Mano
	glPushMatrix();
	glTranslatef(9.5, 0, 0);
	glScalef(2, 2, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo pulgar
	glPushMatrix();
	//glRotatef(angDedP, 1, 0, 0);
	glTranslatef(9.75, 1.25, 0);
	glScalef(.3, .5, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angDedP, 1, 0, 0);
	glTranslatef(9.75, 1.75, 0);
	glScalef(.3, .5, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo indice
	glPushMatrix();
	//glRotatef(angDedI, 0, 1, 0);
	glTranslatef(10.75, .75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angDedI, 0, 1, 0);
	glTranslatef(11.25, .75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angDedI, 0, 1, 0);
	glTranslatef(11.75, .75, 0);
	glScalef(.5, .3, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo medio

	glPushMatrix();
	//glRotatef(angMed, 0, 1, 0);
	glTranslatef(10.75, .25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angMed, 0, 1, 0);
	glTranslatef(11.25, .25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angMed, 0, 1, 0);
	glTranslatef(11.75, .25, 0);
	glScalef(.5, .3, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo anular
	glPushMatrix();
	//glRotatef(angAn, 0, 1, 0);
	glTranslatef(10.75, -.25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angAn, 0, 1, 0);
	glTranslatef(11.25, -.25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angAn, 0, 1, 0);
	glTranslatef(11.75, -.25, 0);
	glScalef(.5, .3, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();
	//me�ique
	glPushMatrix();
	//glRotatef(angMe, 0, 1, 0);
	glTranslatef(10.75, -.75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(angMe, 0, 1, 0);
	glTranslatef(11.25, -.75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPopMatrix();


	//Brazo derecha
	//Hombro
	glPushMatrix();
	glTranslatef(-11, 0, 0);
	glRotatef(-75,0,0,1);
	glPushMatrix();
	glScalef(1, 2, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Bicep
	glPushMatrix();
	glTranslatef(-2, 0, 0);
	glScalef(3, 2, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Codo
	//glRotatef(-angCodo, 0, 1, 0);
	glPushMatrix();
	glTranslatef(-3.75, 0, 0);
	glScalef(0.5, 2, 2);
	glColor3f(1, 0, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Antebrazo
	glPushMatrix();
	glTranslatef(-6, 0, 0);
	glScalef(4, 2, 2);
	glColor3f(0, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Mu�eca
	//glRotatef(-angMuni, 0, 1, 0);
	glPushMatrix();
	glTranslatef(-8.25, 0, 0);
	glScalef(0.5, 2, 2);
	glColor3f(1, 1, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//Mano
	glPushMatrix();
	glTranslatef(-9.5, 0, 0);
	glScalef(2, 2, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo pulgar
	glPushMatrix();
	//glRotatef(-angDedP, 1, 0, 0);
	glTranslatef(-9.75, 1.25, 0);
	glScalef(.3, .5, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angDedP, 1, 0, 0);
	glTranslatef(-9.75, 1.75, 0);
	glScalef(.3, .5, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo indice
	glPushMatrix();
	//glRotatef(-angDedI, 0, 1, 0);
	glTranslatef(-10.75, .75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angDedI, 0, 1, 0);
	glTranslatef(-11.25, .75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angDedI, 0, 1, 0);
	glTranslatef(-11.75, .75, 0);
	glScalef(.5, .3, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo medio

	glPushMatrix();
	//glRotatef(-angMed, 0, 1, 0);
	glTranslatef(-10.75, .25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angMed, 0, 1, 0);
	glTranslatef(-11.25, .25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angMed, 0, 1, 0);
	glTranslatef(-11.75, .25, 0);
	glScalef(.5, .3, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	//dedo anular
	glPushMatrix();
	//glRotatef(-angAn, 0, 1, 0);
	glTranslatef(-10.75, -.25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angAn, 0, 1, 0);
	glTranslatef(-11.25, -.25, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angAn, 0, 1, 0);
	glTranslatef(-11.75, -.25, 0);
	glScalef(.5, .3, 2);
	glColor3f(0, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();
	//me�ique
	glPushMatrix();
	//glRotatef(-angMe, 0, 1, 0);
	glTranslatef(-10.75, -.75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(-angMe, 0, 1, 0);
	glTranslatef(-11.25, -.75, 0);
	glScalef(.5, .3, 2);
	glColor3f(1, 1, 0);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glPopMatrix();


	//pie derecho
	//muslo 
	glPushMatrix();
	glPushMatrix();
	glTranslatef(-7.5, -11.5, 0);
	glRotatef(movpie, 1, 0, 0);
	glPushMatrix();
	glScalef(2, 5, 3);
	glColor3f(0.6, 0, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();
	glTranslatef(0, -3, 0);
	//rodilla
	glPushMatrix();
	glScalef(2, 1, 3);
	glColor3f(1, 0, 1);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -3, 0);

	//espinilla
	glPushMatrix();
	glScalef(2, 5, 3);
	glColor3f(1, 0.5, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -2.75, 0);

	//tobillo
	glPushMatrix();
	glScalef(2, 0.5, 3);
	glColor3f(1, 0, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();

	glTranslatef(0, -1.25, 0);
	//pie
	glPushMatrix();
	glScalef(2, 2, 3);
	glColor3f(0.5, 0, 0.5);
	fig3.prisma2(0, 0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}

void pelota(void) {

	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	fig6.esfera(2, 10, 10,  t_pelota.GLindex);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);


}



void pintaTexto(float x, float y, float z, void *font, char *string)
{

	char *c;     //Almacena los caracteres a escribir
	glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
							//glWindowPos2i(150,100);
	for (c = string; *c != '\0'; c++) //Condicion de fin de cadena
	{
		glutBitmapCharacter(font, *c); //imprime
	}
}

void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();


	glPushMatrix();
	glRotatef(g_lookupdown, 1.0f, 0, 0);

	gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
		objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
		objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);


	glPushMatrix();
	glPushMatrix(); //Creamos cielo
	glDisable(GL_LIGHTING);
	glTranslatef(0, 60, 0);
	fig1.skybox(200.0, 200.0, 200.0, text1.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//pasto
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(0, -40, 0.0);
	glScalef(200, .1, 200);
	fig3.prisma2(t_pasto.GLindex, t_pasto.GLindex);
	glPopMatrix();

	//nubes

	glPushMatrix();
	glTranslatef(0, 160, 0.0);
	glScalef(200, .1, 200);
	fig3.prisma2(t_nubes.GLindex, t_nubes.GLindex);
	glPopMatrix();

	//tienda
	glPushMatrix();
	glTranslatef(23, -30, 45);
	glScalef(5, 5, 5);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glScalef(5, 5, 5);
	fig3.prisma2(t_ladrillo.GLindex, t_ladrillo.GLindex);
	glPopMatrix();
	//cara de tienda
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(-2.5, 0, 0);
	glScalef(.1, 5, 5);
	fig3.prisma3(t_ct.GLindex, t_ct.GLindex);
	glPopMatrix();
	glPopMatrix();


	//piso
	glPushMatrix();
	glTranslatef(0, -39.9, 0.0);
	glScalef(20, .1, 200);
	fig3.prisma3(t_pav.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();



	//3ds
	//arboles
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-20, -39.9, 10);
	glScalef(5, 5, 5);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(45, -39.9, 15);
	glScalef(5, 5, 5);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, -39.9, -75);
	glScalef(5, 5, 5);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	//bancos
	glPushMatrix();
	glTranslatef(20, -39.9, -40);
	glRotatef(270, 0, 1, 0);
	glScalef(.05, .05, .05);
	//asiento.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20, -39.9, -40);
	glRotatef(90, 0, 1, 0);
	glScalef(.05, .05, .05);
	//asiento.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glEnable(GL_COLOR_MATERIAL);

	//humanoide
	glPushMatrix();
	glTranslatef(0, -28, 0);
	glScalef(.4, .4, .4);
	humanide();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-3, -20, 5);
	//fig5.esfera(2,12,12,0);
	pelota();
	glPopMatrix();

	//ni�o
	glPushMatrix();
	glTranslatef(0, -10,  45);
	glRotatef(180,0,1,0);
	glScalef(.6, .6, .6);
	ninio();
	glPopMatrix();




	glPopMatrix();





	glColor3f(1.0, 1.0, 1.0);

	glPopMatrix();

	glPopMatrix();

	glutSwapBuffers();

}

void animacion()
{
	fig3.text_izq -= 0.01;
	fig3.text_der -= 0.01;
	if (fig3.text_izq<-1)
		fig3.text_izq = 0;
	if (fig3.text_der<0)
		fig3.text_der = 1;

	//Movimiento del monito
	if (play)
	{

		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex>FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation

								  //Interpolaciones incremento.
								  //el incremento es la distancia entre dos cuadros, el 2 - 1 y se divide entre el 90(i_max_steps)   Se hace la interpolacion


				KeyFrame[playIndex].inchom = (KeyFrame[playIndex + 1].movhombro - KeyFrame[playIndex].movhombro) / i_max_steps;
				KeyFrame[playIndex].incpie = (KeyFrame[playIndex + 1].movpie - KeyFrame[playIndex].movpie) / i_max_steps;

			}
		}
		else
		{	//Draw information


			movhombro += KeyFrame[playIndex].inchom;
			movpie += KeyFrame[playIndex].incpie;


			i_curr_steps++;
		}

	}

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(s, "FPS:%4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}

	glutPostRedisplay();
}

/*void animacion2()
{
	fig3.text_izq -= 0.01;
	fig3.text_der -= 0.01;
	if (fig3.text_izq<-1)
		fig3.text_izq = 0;
	if (fig3.text_der<0)
		fig3.text_der = 1;

	//Movimiento del monito
	if (play)
	{

		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex>FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation

								  //Interpolaciones incremento.
								  //el incremento es la distancia entre dos cuadros, el 2 - 1 y se divide entre el 90(i_max_steps)   Se hace la interpolacion


				
				KeyFrame[playIndex].incpie = (KeyFrame[playIndex + 1].movpie - KeyFrame[playIndex].movpie) / i_max_steps;

			}
		}
		else
		{	//Draw information


			
			movpie += KeyFrame[playIndex].incpie;


			i_curr_steps++;
		}

	}

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(s, "FPS:%4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}

	glutPostRedisplay();
}

*/
void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista

	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 300.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {

	case 'w':   //Movimientos de camara
	case 'W':
		objCamera.Move_Camera(CAMERASPEED + 0.2);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 0.2));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.4));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 0.4);
		break;

	case 'M':
	case 'm':
		if (play == false && (FrameIndex>1) )
		{

			movhombro = KeyFrame[0].movhombro;


			//First Interpolation


			KeyFrame[playIndex].inchom = (KeyFrame[playIndex + 1].movhombro - KeyFrame[playIndex].movhombro) / i_max_steps;


			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;
	case 'N':
	case 'n':
		if (play == false && (FrameIndex>1))
		{

			movpie = KeyFrame[4].movpie;


			//First Interpolation


			KeyFrame[playIndex].incpie = (KeyFrame[playIndex + 4].movpie - KeyFrame[playIndex].movpie) / i_max_steps;


			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;
	

		//break;

	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;
	}

	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

	case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

	case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View(CAMERASPEED);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)   // Main Function
{

	glutInit(&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutInitWindowSize(500, 500);	// Tama�o de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow("Final"); // Nombre de la Ventana
							   //glutFullScreen     ( );         // Full Screen
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut funci�n de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut funci�n en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut funci�n de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	glutIdleFunc(animacion);


	glutMainLoop();          // 

	return 0;
}
