// deklarasikan semua header disini

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/glut.h>

#include <stdio.h>
#include <iostream>
#include <math.h>

int SCREEN_WIDTH = 400; 
int SCREEN_HEIGHT = 400;

// inisialisasi variabel untuk transformasi seperti translasi, rotasi atau scaling
float angle = 0.0f;					
float posX = 0.0f, rotX =  0.0f;	
float posY = 0.0f, rotY =  0.0f;	
float posZ = 5.0f, rotZ = -1.0f;	

float objectAngleX = 0.0f;			
float objectAngleY = 0.0f;			
float objectAngleZ = 0.0f;			

// container untuk membuat tipe data 3D (X, Y, Z) 
struct Vec3{ 
	float X; float Y; float Z;
	Vec3(float x, float y, float z) { X = x; Y = y; Z = z; }
	Vec3() { }
	~Vec3() { }
}; 

// ==========================================
// fungsi interpolasi cosine (PERUBAHAN DI SINI)
// ==========================================
float cosineInterpolate(float y0, float y1, float u)
{
	float mu2 = (1 - cos(u * 3.14159265)) / 2;
	return (y0 * (1 - mu2) + y1 * mu2);
}

// ==========================================
// fungsi untuk menggambar kurva interpolasi cosine
// ==========================================
void lineInterpolasiCosine(Vec3 point1, Vec3 point2)
{
    float u = 0.0f;
    int n = 50;
    float step = 1.0f / n;

    float x, y;

    // =====================
    // GAMBAR GARIS
    // =====================
    glBegin(GL_LINE_STRIP);

    for (int i = 0; i <= n; i++)
    {
        x = point1.X + (point2.X - point1.X) * u;
        y = cosineInterpolate(point1.Y, point2.Y, u);

        glVertex3f(x, y, 0.0f);
        u += step;
    }

    glEnd();

    // =====================
    // GAMBAR TITIK (SEBAGIAN)
    // =====================
    u = 0.0f;

    glPointSize(6.0f);
    glBegin(GL_POINTS);

    for (int i = 0; i <= n; i++)
    {
        x = point1.X + (point2.X - point1.X) * u;
        y = cosineInterpolate(point1.Y, point2.Y, u);

        if (i % 5 == 0)   // tampilkan tiap 5 titik
        {
            glVertex3f(x, y, 0.0f);
        }

        u += step;
    }

    glEnd();
}

// fungsi untuk menggambar obyek
void drawObject()
{
	glPushMatrix();
	// operasi transformasi rotasi obyek ke arah kanan-kiri
	glRotatef(objectAngleY, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	// operasi transformasi rotasi obyek ke arah atas-bawah
	glRotatef(objectAngleX, 1.0f, 0.0f, 0.0f);
	
	// set warna obyek ke warna hijau
	glColor3f(0.0f, 1.0f, 0.0f);
	
	// titik kontrol kurva
	Vec3 point1 = Vec3(-200.0f, -100.0f, 0.0f);
	Vec3 point2 = Vec3( 200.0f,  150.0f, 0.0f);

	// gambar kurva interpolasi cosine
	lineInterpolasiCosine(point1, point2);
	
	glPopMatrix();
	glPopMatrix();
}

// taruh semua obyek yang akan digambar di fungsi display()
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(posX, posY, posZ, 
			 posX + rotX, posY + rotY, posZ + rotZ, 
			 0.0f, 1.0f, 0.0f);

	drawObject();
	
	glutSwapBuffers();
}

// inisialisasi awal
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);		
	glLoadIdentity();

	glOrtho((GLfloat)-SCREEN_WIDTH/2, (GLfloat)SCREEN_WIDTH/2, 
			(GLfloat)-SCREEN_HEIGHT/2, (GLfloat)SCREEN_HEIGHT/2, 
			1.0, 100.0);

	glMatrixMode(GL_MODELVIEW);				
	glLoadIdentity();						
}

// fungsi reshape
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho((GLfloat)-w/2, (GLfloat)w/2, 
			(GLfloat)-h/2, (GLfloat)h/2, 
			1.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
}

// fungsi keyboard
void keyboard(int key, int x, int y)
{
	switch (key) 
	{
	case GLUT_KEY_LEFT:
		objectAngleY -= 1.0f;
		break;
	case GLUT_KEY_RIGHT:		
		objectAngleY += 1.0f;
		break;
	case GLUT_KEY_UP:		
		objectAngleX -= 1.0f;
		break;
	case GLUT_KEY_DOWN:		
		objectAngleX += 1.0f;
		break;
	}

	glutPostRedisplay();
}

// program utama
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(480, 480);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("NAMA / NIM - COSINE INTERPOLASI GRAFKOM PERTEMUAN 3");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(keyboard);

	glutMainLoop();

	return 0;
}
