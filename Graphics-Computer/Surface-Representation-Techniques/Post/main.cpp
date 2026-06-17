// praktikum 09 grafika komputer
// adhi prahara. 2018

// deklarasikan semua header disini
#ifdef _WIN32
#include <windows.h>
#endif

#include "GL/glut.h"

// inisialisasi variabel untuk transformasi seperti translasi, rotasi atau scaling
float angle = 0.0f;                  // sudut transformasi kamera
float posX = 0.0f, rotX =  0.0f;     // posisi kamera di sumbu X
float posY = 0.0f, rotY =  0.0f;     // posisi kamera di sumbu Y
float posZ = 5.0f, rotZ = -1.0f;     // posisi kamera di sumbu Z

float objectAngleX = 0.0f;           // sudut tranformasi obyek di sumbu X
float objectAngleY = 0.0f;           // sudut tranformasi obyek di sumbu Y
float objectAngleZ = 0.0f;           // sudut tranformasi obyek di sumbu Z

// container untuk membuat tipe data 3D (X, Y, Z)
struct Vec3 {
    float X, Y, Z;
    Vec3(float x, float y, float z) { X = x; Y = y; Z = z; }
    Vec3() { }
    ~Vec3() { }
};

// kurva
Vec3 controlPoint[4][4];
bool showPoints = true;

GLfloat mat_diffuse[] = { 0.5, 0.5, 0.0, 0.0 };
GLfloat mat_specular[] = { 0.0, 0.5, 1.0, 1.0 };
GLfloat mat_shininess[] = { 100.0 };

GLUnurbsObj *theNurb;

// fungsi untuk menggambar obyek
void drawObject() {
    glPushMatrix();
    glRotatef(objectAngleY, 0.0f, 1.0f, 0.0f); // rotasi kanan-kiri

    glPushMatrix();
    glRotatef(objectAngleX, 1.0f, 0.0f, 0.0f); // rotasi atas-bawah
    glScalef(0.5, 0.5, 0.5);
    glColor3f(0.0f, 1.0f, 0.0f); // warna hijau

    GLfloat knots[8] = { 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 };
    gluBeginSurface(theNurb);
    gluNurbsSurface(theNurb, 8, knots, 8, knots, 4 * 3, 3, &controlPoint[0][0].X, 4, 4, GL_MAP2_VERTEX_3);
    gluEndSurface(theNurb);

    if (showPoints) {
        glPointSize(5.0);
        glDisable(GL_LIGHTING);
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_POINTS);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                glVertex3f(controlPoint[i][j].X, controlPoint[i][j].Y, controlPoint[i][j].Z);
            }
        }
        glEnd();
        glEnable(GL_LIGHTING);
    }

    glPopMatrix();
    glPopMatrix();
}

// taruh semua obyek yang akan digambar di fungsi display()
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(posX, posY, posZ, posX + rotX, posY + rotY, posZ + rotZ, 0.0f, 1.0f, 0.0f);

    drawObject();

    glutSwapBuffers();
}

// inisialisasi
void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

for (int u = 0; u < 4; u++) {
    for (int v = 0; v < 4; v++) {
        controlPoint[u][v].X = 2.0 * ((GLfloat)u - 1.5);
        controlPoint[u][v].Y = 2.0 * ((GLfloat)v - 1.5);

        // Mengatur posisi Z (ketinggian) dari titik kontrol
        // Jika titik berada di bagian tengah (u = 1 atau 2 dan v = 1 atau 2)
        // maka diberi nilai Z = 3.0 ? permukaan menonjol di tengah (cembung)
        if ((u == 1 || u == 1) && (v == 1 || v == 1))
            controlPoint[u][v].Z = 9.0;
        else
            // Selain titik tengah, diberi Z = -3.0 ? permukaan turun di pinggir
            controlPoint[u][v].Z = -2.0;
    }
}


    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);

    theNurb = gluNewNurbsRenderer();
    gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 25.0);
    gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);
}

// fungsi ini digunakan bila layar akan diresize (default)
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// fungsi untuk mengatur masukan dari keyboard
void keyboard(int key, int x, int y) {
    float fraction = 0.1f;

    switch (key) {
    case GLUT_KEY_LEFT:
        objectAngleY -= 1.0f;
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        objectAngleY += 1.0f;
        glutPostRedisplay();
        break;
    case GLUT_KEY_UP:
        objectAngleX -= 1.0f;
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        objectAngleX += 1.0f;
        glutPostRedisplay();
        break;
    case GLUT_KEY_PAGE_UP:
        posX += rotX * fraction;
        posZ += rotZ * fraction;
        glutPostRedisplay();
        break;
    case GLUT_KEY_PAGE_DOWN:
        posX -= rotX * fraction;
        posZ -= rotZ * fraction;
        glutPostRedisplay();
        break;
    case GLUT_KEY_F1:
        showPoints = !showPoints;
        break;
    }
}

// timer untuk animasi (gunakan bila perlu)
void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(55, timer, 0);
}

// program utama
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(480, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2400018032 - LUTFAN ALAUDIN NAJA - PRAKTIKUM 09 GRAFIKA KOMPUTER");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    // glutTimerFunc(0, timer, 0); // aktifkan timer bila perlu

    glutMainLoop();
    return 0;
}


