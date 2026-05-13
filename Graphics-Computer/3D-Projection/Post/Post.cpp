#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/glut.h>

// =====================================
// LIGHTING
// =====================================
float lightPosition[] = {0.0f, 5.0f, 5.0f, 1.0f};

// =====================================
// CAMERA
// =====================================
float posX = 0.0f;
float posY = 0.0f;
float posZ = 5.0f;

float rotX = 0.0f;
float rotY = 0.0f;
float rotZ = -1.0f;

// =====================================
// OBJECT ROTATION
// =====================================
float objectAngleX = 0.0f;
float objectAngleY = 0.0f;

// =====================================
// FUNCTION : DRAW TORUS
// =====================================
void drawTorus(
    float zPos,
    float radius,
    float red,
    float green,
    float blue)
{
    glPushMatrix();

    // Rotasi object
    glRotatef(objectAngleY, 0.0f, 1.0f, 0.0f);
    glRotatef(objectAngleX + 90.0f, 1.0f, 0.0f, 0.0f);

    // Posisi
    glTranslatef(0.0f, -0.7f, zPos);

    // Warna
    glColor3f(red, green, blue);

    // Torus
    glutSolidTorus(0.08f, radius, 30, 50);

    glPopMatrix();
}

// =====================================
// FUNCTION : DRAW SPHERE
// =====================================
void drawSphere()
{
    glPushMatrix();

    glRotatef(objectAngleY, 0.0f, 1.0f, 0.0f);
    glRotatef(objectAngleX + 90.0f, 1.0f, 0.0f, 0.0f);

    glTranslatef(0.0f, -0.7, -0.55f);

    glColor3f(1.0f, 0.0f, 0.0f);

    glutSolidSphere(0.11f, 50, 50);

    glPopMatrix();
}

// =====================================
// FUNCTION : DRAW BASE
// =====================================
void drawBase()
{
    glPushMatrix();

    glRotatef(objectAngleY, 0.0f, 1.0f, 0.0f);
    glRotatef(objectAngleX + 90.0f, 1.0f, 0.0f, 0.0f);

    glScalef(2.0f, 2.0f, 0.15f);

    glTranslatef(0.0f, -0.3f, 2.5f);

    glColor3f(0.8f, 0.7f, 0.5f);

    glutSolidCube(1.0f);

    glPopMatrix();
}

// =====================================
// FUNCTION : DRAW OBJECT
// =====================================
void drawObject()
{
    drawTorus( 0.20f, 0.60f, 0.0f, 0.0f, 1.0f); // Biru tua
    drawTorus( 0.05f, 0.48f, 0.0f, 0.5f, 1.0f); // Biru muda
    drawTorus(-0.10f, 0.36f, 0.0f, 1.0f, 0.0f); // Hijau
    drawTorus(-0.25f, 0.24f, 1.0f, 1.0f, 0.0f); // Kuning
    drawTorus(-0.40f, 0.16f, 1.0f, 0.5f, 0.0f); // Orange

    // Sphere merah
    drawSphere();

    // Alas
    drawBase();
}

// =====================================
// DISPLAY
// =====================================
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(
        posX, posY, posZ,
        posX + rotX,
        posY + rotY,
        posZ + rotZ,
        0.0f, 1.0f, 0.0f);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    drawObject();

    glutSwapBuffers();
}

// =====================================
// INITIALIZATION
// =====================================
void init()
{
    // Background putih
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    // Depth test
    glEnable(GL_DEPTH_TEST);

    // Projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, 1.0f, 1.0f, 100.0f);

    glMatrixMode(GL_MODELVIEW);

    // Lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

// =====================================
// RESHAPE
// =====================================
void reshape(int width, int height)
{
    if (height == 0)
        height = 1;

    float aspect = (float)width / (float)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, aspect, 1.0f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

// =====================================
// KEYBOARD CONTROL
// =====================================
void keyboard(int key, int x, int y)
{
    float speed = 0.2f;

    switch (key)
    {
        // Rotasi kiri kanan
        case GLUT_KEY_LEFT:
            objectAngleY -= 3.0f;
            break;

        case GLUT_KEY_RIGHT:
            objectAngleY += 3.0f;
            break;

        // Rotasi atas bawah
        case GLUT_KEY_UP:
            objectAngleX -= 3.0f;
            break;

        case GLUT_KEY_DOWN:
            objectAngleX += 3.0f;
            break;

        // Zoom in
        case GLUT_KEY_PAGE_UP:
            posZ -= speed;
            break;

        // Zoom out
        case GLUT_KEY_PAGE_DOWN:
            posZ += speed;
            break;
    }

    glutPostRedisplay();
}

// =====================================
// TIMER
// =====================================
void timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

// =====================================
// MAIN FUNCTION
// =====================================
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_DOUBLE |
        GLUT_RGBA |
        GLUT_DEPTH);

    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);

    glutCreateWindow(
        "2400018032 / LUTFAN ALAUDIN NAJA - PRAKTIKUM GRAFIKA KOMPUTER");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);

    // Aktifkan jika ingin animasi
    // glutTimerFunc(0, timer, 0);

    glutMainLoop();

    return 0;
}