// kode dasar untuk semua praktikum grafika komputer
// adhi prahara. 2018

// deklarasikan semua header disini
#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/glut.h>

// inisialisasi variabel untuk transformasi seperti translasi, rotasi atau scaling
float angle = 0.0f;          // sudut transformasi kamera
float posX = 0.0f, rotX = 0.0f;   // posisi kamera di sumbu X
float posY = 0.0f, rotY = 0.0f;   // posisi kamera di sumbu Y
float posZ = 5.0f, rotZ = -1.0f;  // posisi kamera di sumbu Z

float objectAngleX = 0.0f;  // sudut transformasi obyek di sumbu X
float objectAngleY = 0.0f;  // sudut transformasi obyek di sumbu Y
float objectAngleZ = 0.0f;  // sudut transformasi obyek di sumbu Z

float objectScaleX = 1.0f;  // skala perbesaran obyek ke arah X
float objectScaleY = 1.0f;  // skala perbesaran obyek ke arah Y
float objectScaleZ = 1.0f;  // skala perbesaran obyek ke arah Z

float objectPositionX = 0.0f;  // posisi obyek di sumbu X
float objectPositionY = 0.0f;  // posisi obyek di sumbu Y
float objectPositionZ = 0.0f;  // posisi obyek di sumbu Z

// container untuk membuat tipe data 3D (X, Y, Z)
struct Vec3
{
    float X; float Y; float Z;
    Vec3(float x, float y, float z) { X = x; Y = y; Z = z; }
    Vec3() { }
    ~Vec3() { }
};

// fungsi untuk menggambar obyek kubus
void drawObject()
{
    glPushMatrix();
    
    // operasi transformasi translasi obyek ke arah sumbu X, Y atau Z
    glTranslatef(objectPositionX, objectPositionY, objectPositionZ);
    
    // operasi transformasi scaling obyek ke arah sumbu X, Y atau Z
    glScalef(objectScaleX, objectScaleY, objectScaleZ);
    
    // operasi transformasi rotasi obyek ke arah kanan-kiri
    glRotatef(objectAngleY, 0.0f, 1.0f, 0.0f);
    
    glPushMatrix();
    
    // operasi transformasi rotasi obyek ke arah atas-bawah
    glRotatef(objectAngleX, 1.0f, 0.0f, 0.0f);
    
    // set warna obyek ke warna hijau (0.0f, 1.0f, 0.0f)
    glColor3f(0.0f, 1.0f, 0.0f);
    
    glutSolidCube(1.0f); // menggambar obyek kubus
    
    glPopMatrix();
    
    glPopMatrix();
}

// taruh semua obyek yang akan digambar di fungsi display()
void display()
{
    // bersihkan dan reset layar dan buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // posisikan kamera pandang
    // dalam hal ini sumbu Y ada diatas dan posisi kamera pandang di (posX, posY, posZ)
    gluLookAt(posX, posY, posZ, posX + rotX, posY + rotY, posZ + rotZ, 0.0f, 1.0f, 0.0f);

    // panggil fungsi untuk menggambar obyek
    drawObject();

    // tampilkan obyek ke layar
    glutSwapBuffers();
}

// inisialisasikan variabel, pencahayaan, tekstur dan pengaturan kamera pandang di fungsi init()
void init(void)
{
    // inisialisasi warna latar belakang layar dalam hal ini warna putih (1.0, 1.0, 1.0, 0.0)
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);             // mengaktifkan depth buffer
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0); // set proyeksi ke perspektif
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // inisialisasi kamera pandang
    gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

// fungsi ini digunakan bila layar akan diresize (default)
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// fungsi untuk mengatur masukan dari keyboard
// untuk arah kiri, kanan, atas, bawah, PgUp, dan PgDn
void keyboard(int key, int x, int y)
{
    float fraction = 0.1f;

    switch (key)
    {
    case GLUT_KEY_LEFT: // rotasi obyek ke kiri
        objectAngleY -= 1.0f;
        glutPostRedisplay();    // update obyek
        break;
    case GLUT_KEY_RIGHT: // rotasi obyek ke kanan
        objectAngleY += 1.0f;
        glutPostRedisplay();    // update obyek
        break;
    case GLUT_KEY_UP: // rotasi obyek ke atas
        objectAngleX -= 1.0f;
        glutPostRedisplay();    // update obyek
        break;
    case GLUT_KEY_DOWN: // rotasi obyek ke bawah
        objectAngleX += 1.0f;
        glutPostRedisplay();    // update obyek
        break;
    case GLUT_KEY_PAGE_UP: // zoom in
        posX += rotX * fraction;
        posZ += rotZ * fraction;
        glutPostRedisplay();    // update obyek
        break;
    case GLUT_KEY_PAGE_DOWN: // zoom out
        posX -= rotX * fraction;
        posZ -= rotZ * fraction;
        glutPostRedisplay();    // update obyek
        break;
    }
}

// fungsi untuk mengatur masukan dari keyboard
void keyboard1(unsigned char key, int x, int y)
{
    float fraction = 0.5f;
    switch (key)
    {
    case 'w': // translasi ke atas
        objectPositionY += fraction;
        glutPostRedisplay();
        break;
    case 's': // translasi ke bawah
        objectPositionY -= fraction;
        glutPostRedisplay();
        break;
    case 'a': // translasi ke kiri
        objectPositionX -= fraction;
        glutPostRedisplay();
        break;
    case 'd': // translasi ke kanan
        objectPositionX += fraction;
        glutPostRedisplay();
        break;
    case 'q': // translasi ke depan
        objectPositionZ += fraction;
        glutPostRedisplay();
        break;
    case 'e': // translasi ke belakang
        objectPositionZ -= fraction;
        glutPostRedisplay();
        break;
    case 't': // perbesar ke arah sumbu Y
        objectScaleY += 0.1f;
        glutPostRedisplay();
        break;
    case 'g': // perkecil ke arah sumbu Y
        objectScaleY = (objectScaleY - 0.1f < 1.0f) ? 1.0f : objectScaleY - 0.1f;
        glutPostRedisplay();
        break;
    case 'f': // perbesar ke arah sumbu X
        objectScaleX += 0.1f;
        glutPostRedisplay();
        break;
    case 'h': // perkecil ke arah sumbu X
        objectScaleX = (objectScaleX - 0.1f < 1.0f) ? 1.0f : objectScaleX - 0.1f;
        glutPostRedisplay();
        break;
    case 'r': // perbesar ke arah sumbu Z
        objectScaleZ += 0.1f;
        glutPostRedisplay();
        break;
    case 'y': // perkecil ke arah sumbu Z
        objectScaleZ = (objectScaleZ - 0.1f < 1.0f) ? 1.0f : objectScaleZ - 0.1f;
        glutPostRedisplay();
        break;
    case 27: // keluar program
        exit(0);
        break;
    }
}

// timer untuk animasi (gunakan bila perlu)
void timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(55, timer, 0);
}

// program utama
int main(int argc, char** argv)
{
    // inisialisasi jendela OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    // set ukuran jendela tampilan
    glutInitWindowSize(480, 480);      // besarnya jendela dalam piksel
    glutInitWindowPosition(100, 100);  // posisi jendela dilayar komputer
    glutCreateWindow("NAMA / NIM - KODE DASAR PRAKTIKUM GRAFIKA KOMPUTER");

    // panggil fungsi init untuk inisialisasi awal
    init();

    // event handler untuk display, reshape dan keyboard
    glutDisplayFunc(display);   // display
    glutReshapeFunc(reshape);   // reshape
    glutSpecialFunc(keyboard);  // keyboard
    glutKeyboardFunc(keyboard1); // keyboard

    // looping
    glutMainLoop();

    return 0;
}
