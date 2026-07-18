// ======================================================================================
// main.cpp
// 3D Hand Model menggunakan Subdivision Technique (Catmull-Clark)
//
// Program ini mendemonstrasikan pembentukan model tangan 3D dengan metode Subdivision.
// Mesh kontrol dasar (base mesh) berupa telapak tangan dan 5 jari yang diekstrusi
// disubdivisi secara rekursif menggunakan algoritma Catmull-Clark.
//
// Fitur:
//   - Pilihan Tingkat Subdivision (Level 0 - 3) secara real-time
//   - Tampilan Wireframe overlay untuk melihat struktur mesh subdivisi
//   - Pilihan Shading: Flat (low-poly / faceted look) dan Smooth (organic look)
//   - Preset warna pencahayaan dramatis (Marmer, Kulit, Perunggu, Giok)
//   - Kontrol kamera interaktif (rotasi, zoom, reset, auto-rotate)
//
// Kontrol Keyboard:
//   Panah Kiri/Kanan : Rotasi horizontal obyek
//   Panah Atas/Bawah : Rotasi vertikal obyek
//   Page Up/Down     : Zoom in/out kamera
//   + / =            : Naikkan tingkat subdivision (maks level 3)
//   - / _            : Turunkan tingkat subdivision (min level 0)
//   S / s            : Toggle Shading (Flat / Smooth)
//   W / w            : Toggle Wireframe overlay
//   1, 2, 3, 4       : Preset Warna (Marmer / Kulit / Perunggu / Giok)
//   Spasi            : Toggle Auto-rotasi
//   R / r            : Reset kamera ke posisi awal
//   ESC              : Keluar program
// ======================================================================================

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdio>

#include "VECTOR3D.h"
#include "COLOR.h"
#include "TIMER.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ====================== Struktur Data Mesh ======================
struct Vertex {
    VECTOR3D position;
    VECTOR3D normal;
};

struct Face {
    std::vector<int> vertexIndices;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<Face> faces;

    void ComputeNormals() {
        for (auto& v : vertices) {
            v.normal.LoadZero();
        }

        for (const auto& face : faces) {
            if (face.vertexIndices.size() < 3) continue;

            VECTOR3D v0 = vertices[face.vertexIndices[0]].position;
            VECTOR3D v1 = vertices[face.vertexIndices[1]].position;
            VECTOR3D v2 = vertices[face.vertexIndices[2]].position;

            VECTOR3D edge1 = v1 - v0;
            VECTOR3D edge2 = v2 - v0;
            VECTOR3D normal = edge1.CrossProduct(edge2);
            normal.Normalize();

            for (int idx : face.vertexIndices) {
                vertices[idx].normal += normal;
            }
        }

        for (auto& v : vertices) {
            v.normal.Normalize();
        }
    }
};

// ====================== Algoritma Catmull-Clark Subdivision ======================
Mesh SubdivideCatmullClark(const Mesh& input) {
    Mesh output;

    // 1. Hitung Face Points
    std::vector<VECTOR3D> facePoints(input.faces.size());
    for (size_t i = 0; i < input.faces.size(); ++i) {
        VECTOR3D fp(0.0f, 0.0f, 0.0f);
        for (int idx : input.faces[i].vertexIndices) {
            fp += input.vertices[idx].position;
        }
        facePoints[i] = fp / (float)input.faces[i].vertexIndices.size();
    }

    struct Edge {
        int v1, v2;
        std::vector<int> faceIndices;
        int edgePointIndex;
    };

    auto make_edge_key = [](int a, int b) {
        return a < b ? std::make_pair(a, b) : std::make_pair(b, a);
    };

    std::map<std::pair<int, int>, Edge> edgeMap;

    for (size_t fIdx = 0; fIdx < input.faces.size(); ++fIdx) {
        const auto& face = input.faces[fIdx];
        size_t n = face.vertexIndices.size();
        for (size_t i = 0; i < n; ++i) {
            int v1 = face.vertexIndices[i];
            int v2 = face.vertexIndices[(i + 1) % n];
            auto key = make_edge_key(v1, v2);
            auto& edge = edgeMap[key];
            edge.v1 = key.first;
            edge.v2 = key.second;
            edge.faceIndices.push_back(fIdx);
        }
    }

    int facePointOffset = output.vertices.size();
    for (const auto& fp : facePoints) {
        Vertex v;
        v.position = fp;
        output.vertices.push_back(v);
    }

    // 2. Hitung Edge Points
    int edgePointOffset = output.vertices.size();
    int currentEdgeIdx = edgePointOffset;
    for (auto& pair : edgeMap) {
        auto& edge = pair.second;
        edge.edgePointIndex = currentEdgeIdx++;

        VECTOR3D ep(0.0f, 0.0f, 0.0f);
        ep += input.vertices[edge.v1].position;
        ep += input.vertices[edge.v2].position;

        if (edge.faceIndices.size() == 2) {
            ep += facePoints[edge.faceIndices[0]];
            ep += facePoints[edge.faceIndices[1]];
            ep = ep / 4.0f;
        } else {
            ep = ep / 2.0f;
        }

        Vertex v;
        v.position = ep;
        output.vertices.push_back(v);
    }

    // 3. Hitung Vertex Points
    int vertexPointOffset = output.vertices.size();
    std::vector<std::vector<int>> vertexFaces(input.vertices.size());
    std::vector<std::vector<int>> vertexNeighbors(input.vertices.size());

    for (size_t fIdx = 0; fIdx < input.faces.size(); ++fIdx) {
        for (int vIdx : input.faces[fIdx].vertexIndices) {
            vertexFaces[vIdx].push_back(fIdx);
        }
    }

    for (const auto& pair : edgeMap) {
        const auto& edge = pair.second;
        vertexNeighbors[edge.v1].push_back(edge.v2);
        vertexNeighbors[edge.v2].push_back(edge.v1);
    }

    for (size_t i = 0; i < input.vertices.size(); ++i) {
        int n = vertexNeighbors[i].size();
        VECTOR3D newPos(0.0f, 0.0f, 0.0f);

        if (n > 0) {
            bool isBoundary = false;
            std::vector<int> boundaryNeighbors;
            for (int neighbor : vertexNeighbors[i]) {
                auto key = make_edge_key(i, neighbor);
                if (edgeMap[key].faceIndices.size() < 2) {
                    isBoundary = true;
                    boundaryNeighbors.push_back(neighbor);
                }
            }

            if (isBoundary) {
                newPos = input.vertices[i].position * 0.75f;
                if (boundaryNeighbors.size() >= 2) {
                    newPos += input.vertices[boundaryNeighbors[0]].position * 0.125f;
                    newPos += input.vertices[boundaryNeighbors[1]].position * 0.125f;
                } else if (boundaryNeighbors.size() == 1) {
                    newPos += input.vertices[boundaryNeighbors[0]].position * 0.25f;
                }
            } else {
                VECTOR3D F(0.0f, 0.0f, 0.0f);
                for (int fIdx : vertexFaces[i]) {
                    F += facePoints[fIdx];
                }
                F = F / (float)vertexFaces[i].size();

                VECTOR3D E(0.0f, 0.0f, 0.0f);
                for (int neighbor : vertexNeighbors[i]) {
                    E += (input.vertices[i].position + input.vertices[neighbor].position) * 0.5f;
                }
                E = E / (float)n;

                newPos = (F + E * 2.0f + input.vertices[i].position * (float)(n - 3)) / (float)n;
            }
        } else {
            newPos = input.vertices[i].position;
        }

        Vertex v;
        v.position = newPos;
        output.vertices.push_back(v);
    }

    // 4. Hubungkan titik-titik baru menjadi Quad Faces
    for (size_t fIdx = 0; fIdx < input.faces.size(); ++fIdx) {
        const auto& face = input.faces[fIdx];
        size_t n = face.vertexIndices.size();
        for (size_t i = 0; i < n; ++i) {
            int v_curr = face.vertexIndices[i];
            int v_next = face.vertexIndices[(i + 1) % n];
            int v_prev = face.vertexIndices[(i + n - 1) % n];

            int fpIdx = facePointOffset + fIdx;

            auto key_next = make_edge_key(v_curr, v_next);
            int epNextIdx = edgeMap[key_next].edgePointIndex;

            auto key_prev = make_edge_key(v_curr, v_prev);
            int epPrevIdx = edgeMap[key_prev].edgePointIndex;

            int vpIdx = vertexPointOffset + v_curr;

            Face quad;
            quad.vertexIndices = { vpIdx, epNextIdx, fpIdx, epPrevIdx };
            output.faces.push_back(quad);
        }
    }

    output.ComputeNormals();
    return output;
}

// ====================== Helper Ekstrusi Mesh ======================
int ExtrudeFace(Mesh& mesh, int faceIndex, const VECTOR3D& direction, float length, float scale = 0.9f) {
    Face origFace = mesh.faces[faceIndex];
    size_t numVerts = origFace.vertexIndices.size();

    VECTOR3D center(0.0f, 0.0f, 0.0f);
    for (int idx : origFace.vertexIndices) {
        center += mesh.vertices[idx].position;
    }
    center /= (float)numVerts;

    std::vector<int> newVertIndices(numVerts);
    for (size_t i = 0; i < numVerts; ++i) {
        int oldIdx = origFace.vertexIndices[i];
        VECTOR3D oldPos = mesh.vertices[oldIdx].position;

        VECTOR3D newPos = oldPos + direction * length;
        newPos = center + direction * length + (newPos - (center + direction * length)) * scale;

        Vertex v;
        v.position = newPos;
        mesh.vertices.push_back(v);
        newVertIndices[i] = mesh.vertices.size() - 1;
    }

    for (size_t i = 0; i < numVerts; ++i) {
        int v_old_curr = origFace.vertexIndices[i];
        int v_old_next = origFace.vertexIndices[(i + 1) % numVerts];
        int v_new_curr = newVertIndices[i];
        int v_new_next = newVertIndices[(i + 1) % numVerts];

        Face sideFace;
        sideFace.vertexIndices = { v_old_curr, v_old_next, v_new_next, v_new_curr };
        mesh.faces.push_back(sideFace);
    }

    mesh.faces[faceIndex].vertexIndices = newVertIndices;
    return faceIndex;
}

void ExtrudeFinger(Mesh& mesh, int faceIdx, const VECTOR3D& dir, const std::vector<float>& lengths, const std::vector<float>& scales) {
    int currentFace = faceIdx;
    for (size_t i = 0; i < lengths.size(); ++i) {
        currentFace = ExtrudeFace(mesh, currentFace, dir, lengths[i], scales[i]);
    }
}

// ====================== Generator Base Mesh Tangan (Hand) ======================
Mesh CreateBaseHand() {
    Mesh mesh;

    // 1. Definisikan koordinat dasar telapak tangan (Palm)
    for (int r = 0; r <= 2; ++r) {
        float y = -2.0f + 1.5f * r;
        float thickness = -0.4f - 0.05f * r;
        for (int c = 0; c < 5; ++c) {
            float x = -1.5f + 3.0f * (c / 4.0f);
            float curve = 0.15f * (1.0f - (x * x) / 3.0f);
            
            Vertex v;
            v.position.Set(x, y, thickness + curve);
            mesh.vertices.push_back(v);
        }
    }

    for (int r = 0; r <= 2; ++r) {
        float y = -2.0f + 1.5f * r;
        float thickness = 0.4f + 0.05f * r;
        for (int c = 0; c < 5; ++c) {
            float x = -1.5f + 3.0f * (c / 4.0f);
            float curve = 0.15f * (1.0f - (x * x) / 3.0f);
            
            Vertex v;
            v.position.Set(x, y, thickness + curve);
            mesh.vertices.push_back(v);
        }
    }

    // 2. Hubungkan sisi belakang (Back faces)
    mesh.faces.push_back({ { 0, 5, 6, 1 } });
    mesh.faces.push_back({ { 1, 6, 7, 2 } });
    mesh.faces.push_back({ { 2, 7, 8, 3 } });
    mesh.faces.push_back({ { 3, 8, 9, 4 } });
    mesh.faces.push_back({ { 5, 10, 11, 6 } });
    mesh.faces.push_back({ { 6, 11, 12, 7 } });
    mesh.faces.push_back({ { 7, 12, 13, 8 } });
    mesh.faces.push_back({ { 8, 13, 14, 9 } });

    // 3. Hubungkan sisi depan (Front faces)
    mesh.faces.push_back({ { 15, 16, 21, 20 } });
    mesh.faces.push_back({ { 16, 17, 22, 21 } });
    mesh.faces.push_back({ { 17, 18, 23, 22 } });
    mesh.faces.push_back({ { 18, 19, 24, 23 } });
    mesh.faces.push_back({ { 20, 21, 26, 25 } });
    mesh.faces.push_back({ { 21, 22, 27, 26 } });
    mesh.faces.push_back({ { 22, 23, 28, 27 } });
    mesh.faces.push_back({ { 23, 24, 29, 28 } });

    // 4. Hubungkan sisi samping kiri (pinky side)
    mesh.faces.push_back({ { 0, 15, 20, 5 } });
    mesh.faces.push_back({ { 5, 20, 25, 10 } });

    // 5. Hubungkan sisi samping kanan (thumb/index side)
    mesh.faces.push_back({ { 4, 9, 24, 19 } });
    mesh.faces.push_back({ { 9, 14, 29, 24 } }); // Ini index face 19: Thumb base!

    // 6. Hubungkan knuckle faces di bagian atas
    mesh.faces.push_back({ { 10, 25, 26, 11 } }); // Face 20: Pinky knuckle
    mesh.faces.push_back({ { 11, 26, 27, 12 } }); // Face 21: Ring knuckle
    mesh.faces.push_back({ { 12, 27, 28, 13 } }); // Face 22: Middle knuckle
    mesh.faces.push_back({ { 13, 28, 29, 14 } }); // Face 23: Index knuckle

    // 7. Tutup bagian bawah pergelangan tangan (wrist cap)
    std::vector<int> wristLoop = { 0, 15, 16, 17, 18, 19, 4, 3, 2, 1 };
    Vertex vWristCenter;
    vWristCenter.position.Set(0.0f, -2.3f, 0.0f);
    mesh.vertices.push_back(vWristCenter);
    int wristCenterIdx = mesh.vertices.size() - 1;

    for (size_t i = 0; i < wristLoop.size(); ++i) {
        int v0 = wristLoop[i];
        int v1 = wristLoop[(i + 1) % wristLoop.size()];
        mesh.faces.push_back({ { wristCenterIdx, v1, v0 } });
    }

    // 8. Ekstrusi Jari-Jari
    // Pinky Finger (Face 20)
    ExtrudeFinger(mesh, 20, VECTOR3D(-0.15f, 1.0f, 0.05f).GetNormalized(),
                  { 0.7f, 0.6f, 0.5f, 0.25f }, { 0.95f, 0.90f, 0.85f, 0.5f });

    // Ring Finger (Face 21)
    ExtrudeFinger(mesh, 21, VECTOR3D(-0.04f, 1.0f, 0.02f).GetNormalized(),
                  { 1.0f, 0.8f, 0.7f, 0.35f }, { 0.95f, 0.90f, 0.85f, 0.5f });

    // Middle Finger (Face 22)
    ExtrudeFinger(mesh, 22, VECTOR3D(0.0f, 1.0f, 0.0f).GetNormalized(),
                  { 1.1f, 0.9f, 0.8f, 0.35f }, { 0.95f, 0.90f, 0.85f, 0.5f });

    // Index Finger (Face 23)
    ExtrudeFinger(mesh, 23, VECTOR3D(0.05f, 1.0f, -0.02f).GetNormalized(),
                  { 1.0f, 0.8f, 0.7f, 0.35f }, { 0.95f, 0.90f, 0.85f, 0.5f });

    // Thumb (Face 19)
    ExtrudeFinger(mesh, 19, VECTOR3D(0.85f, 0.45f, 0.25f).GetNormalized(),
                  { 0.8f, 0.7f, 0.35f }, { 0.90f, 0.85f, 0.5f });

    mesh.ComputeNormals();
    return mesh;
}

// ====================== Variabel Global Program ======================
float cameraDistance = 14.0f;
float objectAngleX = 25.0f;
float objectAngleY = -15.0f;

bool autoRotate = false;
float autoRotateSpeed = 0.5f;

// Subdivision level
int currentLevel = 0;
Mesh subdividedMeshes[4]; // Cache untuk Level 0, 1, 2, 3

// Render settings
bool showWireframe = true;
bool useFlatShading = true;

// Colors
const int numColors = 4;
COLOR diffuseColors[numColors];
int currentColorIdx = 0;
COLOR backgroundColor(0.12f, 0.12f, 0.15f, 1.0f);

// Lighting
float shininess = 40.0f;
float lightPosition0[] = { -3.0f,  4.0f,  5.0f, 0.0f }; // Key light
float lightAmbient0[]  = {  0.15f, 0.15f, 0.18f, 1.0f };
float lightSpecular0[] = {  0.8f,  0.8f,  0.8f,  1.0f };

float lightPosition1[] = {  4.0f, -2.0f,  3.0f, 0.0f }; // Fill light
float lightAmbient1[]  = {  0.05f, 0.05f, 0.08f, 1.0f };
float lightDiffuse1[]  = {  0.30f, 0.33f, 0.45f, 1.0f };
float lightSpecular1[] = {  0.2f,  0.2f,  0.2f,  1.0f };

// ====================== Menggambar Mesh ======================
void drawMesh(const Mesh& mesh) {
    if (showWireframe) {
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(1.0f, 1.0f);
    }

    if (useFlatShading) {
        glShadeModel(GL_FLAT);
    } else {
        glShadeModel(GL_SMOOTH);
    }

    glBegin(GL_TRIANGLES);
    for (const auto& face : mesh.faces) {
        if (face.vertexIndices.size() < 3) continue;

        if (useFlatShading) {
            VECTOR3D v0 = mesh.vertices[face.vertexIndices[0]].position;
            VECTOR3D v1 = mesh.vertices[face.vertexIndices[1]].position;
            VECTOR3D v2 = mesh.vertices[face.vertexIndices[2]].position;
            VECTOR3D normal = (v1 - v0).CrossProduct(v2 - v0);
            normal.Normalize();
            glNormal3fv(normal);
        }

        for (size_t i = 1; i < face.vertexIndices.size() - 1; ++i) {
            int idx0 = face.vertexIndices[0];
            int idx1 = face.vertexIndices[i];
            int idx2 = face.vertexIndices[i + 1];

            if (!useFlatShading) glNormal3fv(mesh.vertices[idx0].normal);
            glVertex3fv(mesh.vertices[idx0].position);

            if (!useFlatShading) glNormal3fv(mesh.vertices[idx1].normal);
            glVertex3fv(mesh.vertices[idx1].position);

            if (!useFlatShading) glNormal3fv(mesh.vertices[idx2].normal);
            glVertex3fv(mesh.vertices[idx2].position);
        }
    }
    glEnd();

    if (showWireframe) {
        glDisable(GL_POLYGON_OFFSET_FILL);
        glDisable(GL_LIGHTING);

        glColor3f(0.18f, 0.22f, 0.28f);
        glLineWidth(1.0f);

        for (const auto& face : mesh.faces) {
            glBegin(GL_LINE_LOOP);
            for (int idx : face.vertexIndices) {
                glVertex3fv(mesh.vertices[idx].position);
            }
            glEnd();
        }

        glEnable(GL_LIGHTING);
    }
}

// ====================== Fungsi Display ======================
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0f, 0.0f, cameraDistance, 
              0.0f, 0.5f, 0.0f, 
              0.0f, 1.0f, 0.0f);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbient0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  diffuseColors[currentColorIdx]);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular0);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT1, GL_AMBIENT,  lightAmbient1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  lightDiffuse1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular1);
    glEnable(GL_LIGHT1);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

    glEnable(GL_LIGHTING);

    glPushMatrix();
    glRotatef(objectAngleY, 0.0f, 1.0f, 0.0f);
    glRotatef(objectAngleX, 1.0f, 0.0f, 0.0f);

    drawMesh(subdividedMeshes[currentLevel]);

    glPopMatrix();

    glDisable(GL_LIGHTING);
    glutSwapBuffers();
}

// ====================== Inisialisasi Awal ======================
void init(void) {
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    diffuseColors[0].Set(0.95f, 0.95f, 0.95f, 1.0f); // White
    diffuseColors[1].Set(0.85f, 0.15f, 0.15f, 1.0f); // Red
    diffuseColors[2].Set(0.15f, 0.70f, 0.25f, 1.0f); // Green
    diffuseColors[3].Set(0.15f, 0.35f, 0.85f, 1.0f); // Blue

    printf("[Init] Menghasilkan base control mesh tangan (Level 0)...\n");
    subdividedMeshes[0] = CreateBaseHand();
    
    for (int i = 1; i <= 3; ++i) {
        printf("[Init] Menghitung Subdivision Level %d...\n", i);
        subdividedMeshes[i] = SubdivideCatmullClark(subdividedMeshes[i - 1]);
    }
    printf("[Init] Semua level subdivisi tangan berhasil dikalkulasi!\n");
}

// ====================== Reshape Window ======================
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// ====================== Keyboard Special Keys ======================
void keyboardSpecial(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        objectAngleY -= 5.0f;
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        objectAngleY += 5.0f;
        glutPostRedisplay();
        break;
    case GLUT_KEY_UP:
        objectAngleX -= 5.0f;
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        objectAngleX += 5.0f;
        glutPostRedisplay();
        break;
    case GLUT_KEY_PAGE_UP:
        cameraDistance -= 0.5f;
        if (cameraDistance < 4.0f) cameraDistance = 4.0f;
        glutPostRedisplay();
        break;
    case GLUT_KEY_PAGE_DOWN:
        cameraDistance += 0.5f;
        if (cameraDistance > 30.0f) cameraDistance = 30.0f;
        glutPostRedisplay();
        break;
    }
}

// ====================== Keyboard Normal Keys ======================
void keyboardNormal(unsigned char key, int x, int y) {
    switch (key) {
    case '+':
    case '=':
        if (currentLevel < 3) {
            currentLevel++;
            printf("[Mesh] Mengubah ke tingkat subdivisi Level %d (%zu faces)\n", 
                   currentLevel, subdividedMeshes[currentLevel].faces.size());
            glutPostRedisplay();
        }
        break;
    case '-':
    case '_':
        if (currentLevel > 0) {
            currentLevel--;
            printf("[Mesh] Mengubah ke tingkat subdivisi Level %d (%zu faces)\n", 
                   currentLevel, subdividedMeshes[currentLevel].faces.size());
            glutPostRedisplay();
        }
        break;
    case 'S':
    case 's':
        useFlatShading = !useFlatShading;
        printf("[Render] Shading Mode: %s\n", useFlatShading ? "Flat (Faceted)" : "Smooth (Smooth)");
        glutPostRedisplay();
        break;
    case 'W':
    case 'w':
        showWireframe = !showWireframe;
        printf("[Render] Wireframe Overlay: %s\n", showWireframe ? "ON" : "OFF");
        glutPostRedisplay();
        break;
    case '1':
        currentColorIdx = 0;
        glutPostRedisplay();
        break;
    case '2':
        currentColorIdx = 1;
        glutPostRedisplay();
        break;
    case '3':
        currentColorIdx = 2;
        glutPostRedisplay();
        break;
    case '4':
        currentColorIdx = 3;
        glutPostRedisplay();
        break;
    case ' ':
        autoRotate = !autoRotate;
        printf("[Animasi] Auto-rotasi: %s\n", autoRotate ? "Aktif" : "Nonaktif");
        break;
    case 'R':
    case 'r':
        objectAngleX = 25.0f;
        objectAngleY = -15.0f;
        cameraDistance = 14.0f;
        glutPostRedisplay();
        break;
    case 27: // ESC
        exit(0);
        break;
    }
}

// ====================== Timer Loop ======================
void timer(int value) {
    if (autoRotate) {
        objectAngleY += autoRotateSpeed;
        if (objectAngleY > 360.0f) objectAngleY -= 360.0f;
        glutPostRedisplay();
    }
    glutTimerFunc(16, timer, 0); // ~60 FPS
}

// ====================== Program Utama ======================
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D Hand Model - Catmull-Clark Subdivision Technique");

    init();

    printf("=================================================================\n");
    printf("   3D Hand Model - Catmull-Clark Subdivision Surface\n");
    printf("=================================================================\n");
    printf("   Kontrol Keyboard:\n");
    printf("     + / =        : Tambah Level Subdivision (maks 3)\n");
    printf("     - / _        : Kurang Level Subdivision (min 0)\n");
    printf("     S / s        : Toggle Shading Mode (Flat / Smooth)\n");
    printf("     W / w        : Toggle Wireframe Overlay (ON / OFF)\n");
    printf("     Panah Arah   : Rotasi Obyek (Kiri/Kanan/Atas/Bawah)\n");
    printf("     Page Up/Down : Zoom In / Zoom Out\n");
    printf("     1 - 4        : Preset Warna (Marmer / Kulit / Perunggu / Giok)\n");
    printf("     Spasi        : Toggle Auto-rotasi\n");
    printf("     R / r        : Reset Posisi Kamera dan Obyek\n");
    printf("     ESC          : Keluar\n");
    printf("=================================================================\n");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboardSpecial);
    glutKeyboardFunc(keyboardNormal);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
