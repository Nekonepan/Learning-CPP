// deklarasikan semua header disini
#include <windows.h>
#include <GL/glut.h>

#include <stdio.h>
#include <iostream>
#include <math.h>

int SCREEN_WIDTH = 400; 
int SCREEN_HEIGHT = 400;

// inisialisasi variabel
float angle = 0.0f;					
float posX = 0.0f, rotX =  0.0f;	
float posY = 0.0f, rotY =  0.0f;	
float posZ = 5.0f, rotZ = -1.0f;	

float objectAngleX = 0.0f;			
float objectAngleY = 0.0f;			
float objectAngleZ = 0.0f;			

// struktur titik
struct Vec3{ 
	float X; float Y; float Z;
	Vec3(float x, float y, float z) { X = x; Y = y; Z = z; }
	Vec3() { }
}; 

// ==========================================
// fungsi interpolasi cubic (PERUBAHAN DI SINI)
// ==========================================
float cubicInterpolate(float y0, float y1, float y2, float y3, float u)
{
	float a = y3 - y2 - y0 + y1;
	float b = y0 - y1 - a;
	float c = y2 - y0;
	float d = y1;

	return a*u*u*u + b*u*u + c*u + d;
}

// ==========================================
// fungsi untuk menggambar kurva interpolasi cubic
// ==========================================
void lineInterpolasiCubic(Vec3 p0, Vec3 p1, Vec3 p2, Vec3 p3)
{
    float u = 0.0f;
    int n = 50;
    float step = 1.0f / n;

    float x, y;

    // =====================
    // KALAU INI BUAT GAMBAR GARIS
    // =====================
    glBegin(GL_LINE_STRIP);

    for (int i = 0; i <= n; i++)
    {
        x = p1.X + (p2.X - p1.X) * u;
        y = cubicInterpolate(p0.Y, p1.Y, p2.Y, p3.Y, u);

        glVertex3f(x, y, 0.0f);
        u += step;
    }

    glEnd();

    // =====================
    // GAMBAR TITIK DISINI YHHH
    // =====================
    u = 0.0f;

    glPointSize(6.0f);
    glBegin(GL_POINTS);

    for (int i = 0; i <= n; i++)
    {
        x = p1.X + (p2.X - p1.X) * u;
        y = cubicInterpolate(p0.Y, p1.Y, p2.Y, p3.Y, u);

        if (i % 5 == 0)
        {
            glVertex3f(x, y, 0.0f);
        }

        u += step;
    }

    glEnd();
}

// fungsi menggambar objek
void drawObject()
{
	glPushMatrix();
	glRotatef(objectAngleY, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glRotatef(objectAngleX, 1.0f, 0.0f, 0.0f);
	
	//WHITE
	glColor3f(1.0f, 1.0f, 1.0f); //ini buat warna, inget konsep 'RGB'
	
	// 4 titik kontrol (PENTING untuk cubic)
	Vec3 p0 = Vec3(-400.0f, -250.0f, 0.0f); // ditarik jauh ke bawah
	Vec3 p1 = Vec3(-300.0f, -100.0f, 0.0f);
	Vec3 p2 = Vec3( 300.0f,  150.0f, 0.0f);
	Vec3 p3 = Vec3( 400.0f,  350.0f, 0.0f); // dinaikkan lebih tinggi

	// gambar kurva cubic
	lineInterpolasiCubic(p0, p1, p2, p3);
	
	// GREEN
	glColor3f(0.0f, 1.0f, 0.0f); //ini buat warna, inget konsep 'RGB'
	
	// 4 titik kontrol (PENTING untuk cubic)
	Vec3 p4 = Vec3(-500.0f, -250.0f, 0.0f); // ditarik jauh ke bawah
	Vec3 p5 = Vec3(-400.0f, -100.0f, 0.0f);
	Vec3 p6 = Vec3( 400.0f,  150.0f, 0.0f);
	Vec3 p7 = Vec3( 500.0f,  350.0f, 0.0f); // dinaikkan lebih tinggi

	// gambar kurva cubic
	lineInterpolasiCubic(p4, p5, p6, p7);
	
	//RED
	glColor3f(1.0f, 0.0f, 0.0f); //ini buat warna, inget konsep 'RGB'
	
	// 4 titik kontrol (PENTING untuk cubic)
	Vec3 p8 = Vec3(-600.0f, -250.0f, 0.0f); // ditarik jauh ke bawah
	Vec3 p9 = Vec3(-500.0f, -100.0f, 0.0f);
	Vec3 p10 = Vec3( 500.0f, 150.0f, 0.0f);
	Vec3 p11 = Vec3( 600.0f, 350.0f, 0.0f); // dinaikkan lebih tinggi

	// gambar kurva cubic
	lineInterpolasiCubic(p8, p9, p10, p11);
	
	//BLUE
	glColor3f(0.0f, 0.0f, 1.0f); //ini buat warna, inget konsep 'RGB'
	
	// 4 titik kontrol (PENTING untuk cubic)
	Vec3 p12 = Vec3(-300.0f, -250.0f, 0.0f); // ditarik jauh ke bawah
	Vec3 p13 = Vec3(-200.0f, -100.0f, 0.0f);
	Vec3 p14 = Vec3( 200.0f,  150.0f, 0.0f);
	Vec3 p15 = Vec3( 300.0f,  350.0f, 0.0f); // dinaikkan lebih tinggi

	// gambar kurva cubic
	lineInterpolasiCubic(p12, p13, p14, p15);
	
	glPopMatrix();
	glPopMatrix();
}

// display
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

// init
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);		
	glLoadIdentity();

	glOrtho(-SCREEN_WIDTH/2, SCREEN_WIDTH/2, 
			-SCREEN_HEIGHT/2, SCREEN_HEIGHT/2, 
			1.0, 100.0);

	glMatrixMode(GL_MODELVIEW);				
	glLoadIdentity();						
}

// reshape
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-w/2, w/2, -h/2, h/2, 1.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
}

// keyboard
void keyboard(int key, int x, int y)
{
	switch (key) 
	{
	case GLUT_KEY_LEFT: objectAngleY -= 1.0f; break;
	case GLUT_KEY_RIGHT: objectAngleY += 1.0f; break;
	case GLUT_KEY_UP: objectAngleX -= 1.0f; break;
	case GLUT_KEY_DOWN: objectAngleX += 1.0f; break;
	}

	glutPostRedisplay();
}

// main
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(480, 480);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("NAMA / NIM - CUBIC INTERPOLASI GRAFKOM PERTEMUAN 3");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(keyboard);

	glutMainLoop();

	return 0;
}
