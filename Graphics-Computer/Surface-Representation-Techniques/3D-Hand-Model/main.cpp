// ======================================================================================
// main.cpp
// 3D Hand Model with Articulated Fingers — Catmull-Clark Subdivision Surface
//
// Program ini mendemonstrasikan model tangan 3D dengan jari-jari yang dapat digerakkan
// (artikulasi) menggunakan teknik Subdivision Surface (Catmull-Clark).
//
// Setiap ruas jari merupakan mesh box terpisah yang disubdivisi dan dirender secara
// hierarkis menggunakan OpenGL matrix stack (glPushMatrix / glRotatef / glTranslatef).
//
// Fitur:
//   - Artikulasi jari: setiap jari memiliki 3 sendi yang dapat ditekuk
//   - Animasi Grab: mengepalkan dan membuka tangan secara otomatis
//   - Pilihan Tingkat Subdivision (Level 0 - 3) secara real-time
//   - Tampilan Wireframe overlay
//   - Pilihan Shading: Flat dan Smooth
//   - Preset warna dan auto-cycle warna
//   - Kontrol kamera interaktif
//
// Kontrol Keyboard:
//   Tab          : Pilih jari (Semua/Jempol/Telunjuk/Tengah/Manis/Kelingking)
//   Q / q        : Tekuk jari terpilih (+10°)
//   A / a        : Luruskan jari terpilih (-10°)
//   G / g        : Toggle Animasi Grab (mengepal/membuka)
//   + / =        : Naikkan tingkat subdivision (maks level 3)
//   - / _        : Turunkan tingkat subdivision (min level 0)
//   S / s        : Toggle Shading (Flat / Smooth)
//   W / w        : Toggle Wireframe overlay
//   1, 2, 3, 4   : Preset Warna (Putih / Merah / Hijau / Biru)
//   C / c        : Toggle Auto-cycle Warna
//   Spasi        : Toggle Auto-rotasi
//   R / r        : Reset kamera dan posisi jari
//   ESC          : Keluar program
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
#include <cstring>

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

// ====================== Generator Mesh Box ======================
// Membuat box dengan 3 baris vertex (bottom, middle, top) untuk kualitas
// subdivisi yang lebih baik. Box berorientasi vertikal: basis di y=0, puncak di y=1.
// topTaper mengatur seberapa besar puncak menyempit (0.0-1.0, 1.0 = tidak menyempit).
Mesh createUnitSegmentBox(float topTaper = 0.85f) {
    Mesh mesh;
    float t = 0.5f * topTaper;
    float m = (0.5f + t) * 0.5f; // middle row interpolation

    auto addVert = [&](float x, float y, float z) {
        Vertex v;
        v.position.Set(x, y, z);
        mesh.vertices.push_back(v);
    };

    // Bottom row (y=0.0)
    addVert(-0.50f, 0.0f, -0.50f); // 0
    addVert( 0.50f, 0.0f, -0.50f); // 1
    addVert( 0.50f, 0.0f,  0.50f); // 2
    addVert(-0.50f, 0.0f,  0.50f); // 3

    // Middle row (y=0.5)
    addVert(-m, 0.5f, -m); // 4
    addVert( m, 0.5f, -m); // 5
    addVert( m, 0.5f,  m); // 6
    addVert(-m, 0.5f,  m); // 7

    // Top row (y=1.0, tapered)
    addVert(-t, 1.0f, -t); // 8
    addVert( t, 1.0f, -t); // 9
    addVert( t, 1.0f,  t); // 10
    addVert(-t, 1.0f,  t); // 11

    // Faces (CCW outward winding)
    // Bottom cap (normal -Y)
    mesh.faces.push_back({{ 0, 1, 2, 3 }});
    // Top cap (normal +Y)
    mesh.faces.push_back({{ 8, 11, 10, 9 }});

    // Back side -Z: bottom tier & top tier
    mesh.faces.push_back({{ 0, 4, 5, 1 }});
    mesh.faces.push_back({{ 4, 8, 9, 5 }});

    // Front side +Z
    mesh.faces.push_back({{ 3, 2, 6, 7 }});
    mesh.faces.push_back({{ 7, 6, 10, 11 }});

    // Left side -X
    mesh.faces.push_back({{ 0, 3, 7, 4 }});
    mesh.faces.push_back({{ 4, 7, 11, 8 }});

    // Right side +X
    mesh.faces.push_back({{ 1, 5, 6, 2 }});
    mesh.faces.push_back({{ 5, 9, 10, 6 }});

    mesh.ComputeNormals();
    return mesh;
}

// Membuat mesh telapak tangan (palm) dengan dimensi langsung.
Mesh createPalmMesh() {
    Mesh mesh;

    auto addVert = [&](float x, float y, float z) {
        Vertex v;
        v.position.Set(x, y, z);
        mesh.vertices.push_back(v);
    };

    // Bottom row (y=0, wrist) — narrower
    addVert(-1.10f, 0.0f, -0.35f); // 0
    addVert( 1.10f, 0.0f, -0.35f); // 1
    addVert( 1.10f, 0.0f,  0.35f); // 2
    addVert(-1.10f, 0.0f,  0.35f); // 3

    // Middle row (y=1.5) — medium width
    addVert(-1.35f, 1.5f, -0.40f); // 4
    addVert( 1.35f, 1.5f, -0.40f); // 5
    addVert( 1.35f, 1.5f,  0.40f); // 6
    addVert(-1.35f, 1.5f,  0.40f); // 7

    // Top row (y=3.0, knuckles) — widest
    addVert(-1.50f, 3.0f, -0.42f); // 8
    addVert( 1.50f, 3.0f, -0.42f); // 9
    addVert( 1.50f, 3.0f,  0.42f); // 10
    addVert(-1.50f, 3.0f,  0.42f); // 11

    // Faces (CCW outward winding) — same pattern as segment box
    mesh.faces.push_back({{ 0, 1, 2, 3 }});     // Bottom (wrist cap)
    mesh.faces.push_back({{ 8, 11, 10, 9 }});   // Top (knuckle platform)

    mesh.faces.push_back({{ 0, 4, 5, 1 }});     // Back bottom
    mesh.faces.push_back({{ 4, 8, 9, 5 }});     // Back top

    mesh.faces.push_back({{ 3, 2, 6, 7 }});     // Front bottom
    mesh.faces.push_back({{ 7, 6, 10, 11 }});   // Front top

    mesh.faces.push_back({{ 0, 3, 7, 4 }});     // Left bottom (pinky side)
    mesh.faces.push_back({{ 4, 7, 11, 8 }});    // Left top

    mesh.faces.push_back({{ 1, 5, 6, 2 }});     // Right bottom (thumb side)
    mesh.faces.push_back({{ 5, 9, 10, 6 }});    // Right top

    mesh.ComputeNormals();
    return mesh;
}

// ====================== Struktur Data Skeleton ======================
struct FingerSegment {
    float length;
    float width;
    float depth;
};

struct Finger {
    static const int MAX_SEGMENTS = 3;
    int numSegments;
    FingerSegment segments[MAX_SEGMENTS];
    float bendAngles[MAX_SEGMENTS];   // tekukan sendi (derajat, 0=lurus, positif=menekuk)
    float maxBend[MAX_SEGMENTS];      // batas maksimum tekukan
    float fistTarget[MAX_SEGMENTS];   // sudut target saat mengepal
    VECTOR3D attachPoint;             // titik penempelan pada telapak tangan
    float baseAngleZ;                 // rotasi dasar sumbu Z (splay jari)
    float baseAngleX;                 // rotasi dasar sumbu X (tilt)
};

struct HandSkeleton {
    Finger fingers[5]; // 0=Thumb, 1=Index, 2=Middle, 3=Ring, 4=Pinky
};

const char* fingerNames[] = { "Jempol", "Telunjuk", "Tengah", "Manis", "Kelingking", "Semua" };

void initSkeleton(HandSkeleton& sk) {
    // Thumb (Jempol) — 3 segments: metacarpal, proximal, distal
    {
        Finger& f = sk.fingers[0];
        f.numSegments = 3;
        f.segments[0] = { 0.75f, 0.60f, 0.55f };
        f.segments[1] = { 0.60f, 0.52f, 0.50f };
        f.segments[2] = { 0.42f, 0.42f, 0.42f };
        f.maxBend[0] = 50.0f;  f.maxBend[1] = 80.0f;  f.maxBend[2] = 60.0f;
        f.fistTarget[0] = 35.0f; f.fistTarget[1] = 55.0f; f.fistTarget[2] = 40.0f;
        f.bendAngles[0] = f.bendAngles[1] = f.bendAngles[2] = 0.0f;
        f.attachPoint.Set(1.40f, 1.0f, 0.10f);
        f.baseAngleZ = -60.0f;
        f.baseAngleX = -15.0f;
    }

    // Index (Telunjuk)
    {
        Finger& f = sk.fingers[1];
        f.numSegments = 3;
        f.segments[0] = { 0.88f, 0.55f, 0.55f };
        f.segments[1] = { 0.62f, 0.48f, 0.48f };
        f.segments[2] = { 0.48f, 0.38f, 0.38f };
        f.maxBend[0] = 90.0f; f.maxBend[1] = 100.0f; f.maxBend[2] = 70.0f;
        f.fistTarget[0] = 85.0f; f.fistTarget[1] = 95.0f; f.fistTarget[2] = 65.0f;
        f.bendAngles[0] = f.bendAngles[1] = f.bendAngles[2] = 0.0f;
        f.attachPoint.Set(1.12f, 3.0f, 0.0f);
        f.baseAngleZ = -1.5f;
        f.baseAngleX = 0.0f;
    }

    // Middle (Tengah)
    {
        Finger& f = sk.fingers[2];
        f.numSegments = 3;
        f.segments[0] = { 1.00f, 0.58f, 0.58f };
        f.segments[1] = { 0.72f, 0.50f, 0.50f };
        f.segments[2] = { 0.55f, 0.40f, 0.40f };
        f.maxBend[0] = 90.0f; f.maxBend[1] = 100.0f; f.maxBend[2] = 70.0f;
        f.fistTarget[0] = 85.0f; f.fistTarget[1] = 95.0f; f.fistTarget[2] = 65.0f;
        f.bendAngles[0] = f.bendAngles[1] = f.bendAngles[2] = 0.0f;
        f.attachPoint.Set(0.38f, 3.0f, 0.0f);
        f.baseAngleZ = 0.0f;
        f.baseAngleX = 0.0f;
    }

    // Ring (Manis)
    {
        Finger& f = sk.fingers[3];
        f.numSegments = 3;
        f.segments[0] = { 0.90f, 0.55f, 0.55f };
        f.segments[1] = { 0.65f, 0.48f, 0.48f };
        f.segments[2] = { 0.50f, 0.38f, 0.38f };
        f.maxBend[0] = 90.0f; f.maxBend[1] = 100.0f; f.maxBend[2] = 70.0f;
        f.fistTarget[0] = 85.0f; f.fistTarget[1] = 95.0f; f.fistTarget[2] = 65.0f;
        f.bendAngles[0] = f.bendAngles[1] = f.bendAngles[2] = 0.0f;
        f.attachPoint.Set(-0.38f, 3.0f, 0.0f);
        f.baseAngleZ = 1.0f;
        f.baseAngleX = 0.0f;
    }

    // Pinky (Kelingking)
    {
        Finger& f = sk.fingers[4];
        f.numSegments = 3;
        f.segments[0] = { 0.65f, 0.50f, 0.50f };
        f.segments[1] = { 0.50f, 0.42f, 0.42f };
        f.segments[2] = { 0.40f, 0.35f, 0.35f };
        f.maxBend[0] = 90.0f; f.maxBend[1] = 100.0f; f.maxBend[2] = 70.0f;
        f.fistTarget[0] = 85.0f; f.fistTarget[1] = 95.0f; f.fistTarget[2] = 65.0f;
        f.bendAngles[0] = f.bendAngles[1] = f.bendAngles[2] = 0.0f;
        f.attachPoint.Set(-1.12f, 3.0f, 0.0f);
        f.baseAngleZ = 3.0f;
        f.baseAngleX = 0.0f;
    }
}

// ====================== Variabel Global Program ======================
// Camera
float cameraDistance = 14.0f;
float objectAngleX = 15.0f;
float objectAngleY = -20.0f;

bool autoRotate = false;
float autoRotateSpeed = 0.5f;

// Subdivision
int currentLevel = 0;
Mesh segmentMeshes[4]; // Cache unit segment box levels 0-3
Mesh palmMeshes[4];    // Cache palm mesh levels 0-3

// Render settings
bool showWireframe = true;
bool useFlatShading = true;

// Colors
const int numColors = 4;
COLOR diffuseColors[numColors];
int currentColorIdx = 0;
bool autoCycleColor = false;
int colorCycleDelayMs = 2000;
COLOR backgroundColor(0.12f, 0.12f, 0.15f, 1.0f);
float matWhite[] = { 1.0f, 1.0f, 1.0f, 1.0f };

// Lighting
float shininess = 40.0f;
float lightPosition0[] = { -3.0f,  4.0f,  5.0f, 0.0f };
float lightAmbient0[]  = {  0.15f, 0.15f, 0.18f, 1.0f };
float lightSpecular0[] = {  0.8f,  0.8f,  0.8f,  1.0f };

float lightPosition1[] = {  4.0f, -2.0f,  3.0f, 0.0f };
float lightAmbient1[]  = {  0.05f, 0.05f, 0.08f, 1.0f };
float lightDiffuse1[]  = {  0.30f, 0.33f, 0.45f, 1.0f };
float lightSpecular1[] = {  0.2f,  0.2f,  0.2f,  1.0f };

// Skeleton & Articulation
HandSkeleton skeleton;
int selectedFinger = 5; // 0-4 = specific finger, 5 = all
float bendStep = 10.0f;

// Grab Animation
bool grabAnimating = false;
bool grabTargetClosed = false;
float grabSpeed = 3.0f; // degrees per frame

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

// ====================== Menggambar Jari ======================
void drawFinger(const Finger& finger, bool isSelected) {
    glPushMatrix();

    // Pindah ke titik penempelan pada telapak tangan
    glTranslatef(finger.attachPoint.x, finger.attachPoint.y, finger.attachPoint.z);

    // Rotasi dasar (splay dan tilt)
    glRotatef(finger.baseAngleZ, 0.0f, 0.0f, 1.0f);
    glRotatef(finger.baseAngleX, 1.0f, 0.0f, 0.0f);

    for (int i = 0; i < finger.numSegments; ++i) {
        const FingerSegment& seg = finger.segments[i];

        // Terapkan tekukan sendi (rotasi sumbu X)
        glRotatef(finger.bendAngles[i], 1.0f, 0.0f, 0.0f);

        // Gambar segmen: scale unit box ke dimensi segmen
        glPushMatrix();
        glScalef(seg.width, seg.length, seg.depth);
        drawMesh(segmentMeshes[currentLevel]);
        glPopMatrix();

        // Pindah ke ujung segmen untuk sendi berikutnya
        glTranslatef(0.0f, seg.length, 0.0f);
    }

    glPopMatrix();
}

// ====================== Menggambar Seluruh Tangan ======================
void drawHand() {
    // Gambar telapak tangan (palm)
    drawMesh(palmMeshes[currentLevel]);

    // Gambar 5 jari
    for (int i = 0; i < 5; ++i) {
        bool isSelected = (selectedFinger == 5 || selectedFinger == i);
        drawFinger(skeleton.fingers[i], isSelected);
    }
}

// ====================== Fungsi Display ======================
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0f, 0.0f, cameraDistance,
              0.0f, 1.5f, 0.0f,
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

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matWhite);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matWhite);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);

    glEnable(GL_LIGHTING);

    glPushMatrix();
    glRotatef(objectAngleY, 0.0f, 1.0f, 0.0f);
    glRotatef(objectAngleX, 1.0f, 0.0f, 0.0f);

    // Geser tangan ke bawah agar center of mass di tengah viewport
    glTranslatef(0.0f, -1.5f, 0.0f);

    drawHand();

    glPopMatrix();

    glDisable(GL_LIGHTING);
    glutSwapBuffers();
}

// ====================== Inisialisasi Awal ======================
void init(void) {
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE); // Penting! Menormalisasi normal setelah glScalef

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    diffuseColors[0].Set(0.95f, 0.95f, 0.95f, 1.0f); // White
    diffuseColors[1].Set(0.85f, 0.15f, 0.15f, 1.0f); // Red
    diffuseColors[2].Set(0.15f, 0.70f, 0.25f, 1.0f); // Green
    diffuseColors[3].Set(0.15f, 0.35f, 0.85f, 1.0f); // Blue

    // Inisialisasi skeleton
    initSkeleton(skeleton);

    // Cache subdivision levels untuk unit segment box
    printf("[Init] Membuat unit segment box...\n");
    segmentMeshes[0] = createUnitSegmentBox(0.85f);
    for (int i = 1; i <= 3; ++i) {
        printf("[Init] Menghitung Segment Subdivision Level %d...\n", i);
        segmentMeshes[i] = SubdivideCatmullClark(segmentMeshes[i - 1]);
    }

    // Cache subdivision levels untuk palm mesh
    printf("[Init] Membuat palm mesh...\n");
    palmMeshes[0] = createPalmMesh();
    for (int i = 1; i <= 3; ++i) {
        printf("[Init] Menghitung Palm Subdivision Level %d...\n", i);
        palmMeshes[i] = SubdivideCatmullClark(palmMeshes[i - 1]);
    }

    printf("[Init] Semua mesh berhasil dikalkulasi!\n");
}

// ====================== Reshape Window ======================
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// ====================== Helper Artikulasi ======================
void bendFinger(int fingerIdx, float delta) {
    Finger& f = skeleton.fingers[fingerIdx];
    for (int j = 0; j < f.numSegments; ++j) {
        f.bendAngles[j] += delta;
        if (f.bendAngles[j] < 0.0f) f.bendAngles[j] = 0.0f;
        if (f.bendAngles[j] > f.maxBend[j]) f.bendAngles[j] = f.maxBend[j];
    }
}

void bendSelected(float delta) {
    if (selectedFinger == 5) {
        for (int i = 0; i < 5; ++i) bendFinger(i, delta);
    } else {
        bendFinger(selectedFinger, delta);
    }
}

void resetAllFingers() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < skeleton.fingers[i].numSegments; ++j) {
            skeleton.fingers[i].bendAngles[j] = 0.0f;
        }
    }
    grabAnimating = false;
    grabTargetClosed = false;
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
    // Subdivision level
    case '+':
    case '=':
        if (currentLevel < 3) {
            currentLevel++;
            printf("[Mesh] Subdivision Level %d\n", currentLevel);
            glutPostRedisplay();
        }
        break;
    case '-':
    case '_':
        if (currentLevel > 0) {
            currentLevel--;
            printf("[Mesh] Subdivision Level %d\n", currentLevel);
            glutPostRedisplay();
        }
        break;

    // Shading & Wireframe
    case 'S':
    case 's':
        useFlatShading = !useFlatShading;
        printf("[Render] Shading Mode: %s\n", useFlatShading ? "Flat (Faceted)" : "Smooth");
        glutPostRedisplay();
        break;
    case 'W':
    case 'w':
        showWireframe = !showWireframe;
        printf("[Render] Wireframe Overlay: %s\n", showWireframe ? "ON" : "OFF");
        glutPostRedisplay();
        break;

    // Color presets
    case '1': currentColorIdx = 0; glutPostRedisplay(); break;
    case '2': currentColorIdx = 1; glutPostRedisplay(); break;
    case '3': currentColorIdx = 2; glutPostRedisplay(); break;
    case '4': currentColorIdx = 3; glutPostRedisplay(); break;

    // Auto-rotate
    case ' ':
        autoRotate = !autoRotate;
        printf("[Animasi] Auto-rotasi: %s\n", autoRotate ? "Aktif" : "Nonaktif");
        break;

    // Auto-cycle color
    case 'C':
    case 'c':
        autoCycleColor = !autoCycleColor;
        printf("[Warna] Auto-cycle warna: %s\n", autoCycleColor ? "Aktif" : "Nonaktif");
        break;

    // Finger selection (Tab)
    case '\t':
        selectedFinger = (selectedFinger + 1) % 6;
        printf("[Jari] Terpilih: %s\n", fingerNames[selectedFinger]);
        glutPostRedisplay();
        break;

    // Bend finger
    case 'Q':
    case 'q':
        bendSelected(bendStep);
        glutPostRedisplay();
        break;

    // Straighten finger
    case 'A':
    case 'a':
        bendSelected(-bendStep);
        glutPostRedisplay();
        break;

    // Grab animation toggle
    case 'G':
    case 'g':
        grabTargetClosed = !grabTargetClosed;
        grabAnimating = true;
        printf("[Animasi] Grab: %s\n", grabTargetClosed ? "Mengepal..." : "Membuka...");
        break;

    // Reset
    case 'R':
    case 'r':
        objectAngleX = 15.0f;
        objectAngleY = -20.0f;
        cameraDistance = 14.0f;
        resetAllFingers();
        printf("[Reset] Kamera dan jari direset.\n");
        glutPostRedisplay();
        break;

    case 27: // ESC
        exit(0);
        break;
    }
}

// ====================== Timer Loop ======================
void timer(int value) {
    bool needRedraw = false;

    // Auto-rotate
    if (autoRotate) {
        objectAngleY += autoRotateSpeed;
        if (objectAngleY > 360.0f) objectAngleY -= 360.0f;
        needRedraw = true;
    }

    // Grab animation
    if (grabAnimating) {
        bool allDone = true;
        for (int i = 0; i < 5; ++i) {
            Finger& f = skeleton.fingers[i];
            for (int j = 0; j < f.numSegments; ++j) {
                float target = grabTargetClosed ? f.fistTarget[j] : 0.0f;
                if (f.bendAngles[j] < target) {
                    f.bendAngles[j] += grabSpeed;
                    if (f.bendAngles[j] > target) f.bendAngles[j] = target;
                    allDone = false;
                } else if (f.bendAngles[j] > target) {
                    f.bendAngles[j] -= grabSpeed;
                    if (f.bendAngles[j] < target) f.bendAngles[j] = target;
                    allDone = false;
                }
            }
        }
        if (allDone) {
            grabAnimating = false;
            printf("[Animasi] Grab selesai: %s\n", grabTargetClosed ? "Terkepal" : "Terbuka");
        }
        needRedraw = true;
    }

    if (needRedraw) glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // ~60 FPS
}

void colorTimer(int value) {
    if (autoCycleColor) {
        currentColorIdx = (currentColorIdx + 1) % numColors;
        glutPostRedisplay();
    }
    glutTimerFunc(colorCycleDelayMs, colorTimer, 0);
}

// ====================== Program Utama ======================
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(720, 720);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D Hand Model - Articulated Fingers - Catmull-Clark Subdivision");

    init();

    printf("=================================================================\n");
    printf("   3D Hand Model - Articulated Fingers\n");
    printf("   Catmull-Clark Subdivision Surface\n");
    printf("=================================================================\n");
    printf("   Kontrol Artikulasi Jari:\n");
    printf("     Tab          : Pilih jari (Semua/%s/%s/%s/%s/%s)\n",
           fingerNames[0], fingerNames[1], fingerNames[2],
           fingerNames[3], fingerNames[4]);
    printf("     Q / q        : Tekuk jari terpilih (+10)\n");
    printf("     A / a        : Luruskan jari terpilih (-10)\n");
    printf("     G / g        : Toggle Animasi Grab (mengepal/membuka)\n");
    printf("-----------------------------------------------------------------\n");
    printf("   Kontrol Tampilan:\n");
    printf("     + / =        : Tambah Level Subdivision (maks 3)\n");
    printf("     - / _        : Kurang Level Subdivision (min 0)\n");
    printf("     S / s        : Toggle Shading Mode (Flat / Smooth)\n");
    printf("     W / w        : Toggle Wireframe Overlay (ON / OFF)\n");
    printf("     1 - 4        : Preset Warna (Putih / Merah / Hijau / Biru)\n");
    printf("     C / c        : Toggle Auto-Cycle Warna\n");
    printf("-----------------------------------------------------------------\n");
    printf("   Kontrol Kamera:\n");
    printf("     Panah Arah   : Rotasi Obyek\n");
    printf("     Page Up/Down : Zoom In / Zoom Out\n");
    printf("     Spasi        : Toggle Auto-rotasi\n");
    printf("     R / r        : Reset Kamera dan Jari\n");
    printf("     ESC          : Keluar\n");
    printf("=================================================================\n");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboardSpecial);
    glutKeyboardFunc(keyboardNormal);
    glutTimerFunc(0, timer, 0);
    glutTimerFunc(colorCycleDelayMs, colorTimer, 0);

    glutMainLoop();
    return 0;
}
