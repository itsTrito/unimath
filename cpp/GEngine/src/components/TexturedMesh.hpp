#ifndef TEXTURED_MESH_HPP
#define TEXTURED_MESH_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_ttf.h>

#include <fstream>
#include <string>
#include <vector>

#include "../core/Transform.hpp"
#include "../math/MathUtils.hpp"
#include "../math/Matrix44D.hpp"
#include "../math/Vector3D.hpp"
#include "Mesh.hpp"

using namespace std;
namespace GEngine {
class TexturedMesh : public Mesh {
   private:
    string texturePath;
    double *normals;
    double *textureCoords;
    unsigned int textureId;
    unsigned int tmpCount = 0;

    const static unsigned char VERTEX_LENGHT = 3;
    const static unsigned char NORMAL_LENGHT = 3;
    const static unsigned char TEXTURE_LENGHT = 2;

    Transform lastTransform;

   public:
    TexturedMesh(string meshPath, string texturePath) : Mesh(meshPath) {
        vertexCount = textureId = 0;
        this->texturePath = texturePath;
        this->lastTransform = GEngine::Transform();
    }

    ~TexturedMesh() {
        delete[] normals;
        delete[] textureCoords;
    }

    void Translate(const Vector3D &v) {
        for (int i = 0; i < vertexCount * VERTEX_LENGHT; i = i + 3) {
            verticies[i] += v.x;
            normals[i] += v.x;

            verticies[i + 1] += v.y;
            normals[i + 1] += v.y;

            verticies[i + 2] += v.z;
            normals[i + 2] += v.z;
        }
    }

    // Global
    void Transform(const Matrix44D &m) {
        for (int i = 0; i < (faceCount * 3) * 3; i = i + 3) {
            double cX = verticies[i], cY = verticies[i + 1], cZ = verticies[i + 2];
            verticies[i] = (m.m11 * cX) + (m.m12 * cY) + (m.m13 * cZ);
            verticies[i + 1] = (m.m21 * cX) + (m.m22 * cY) + (m.m23 * cZ);
            verticies[i + 2] = (m.m31 * cX) + (m.m32 * cY) + (m.m33 * cZ);

            cX = normals[i];
            cY = normals[i + 1];
            cZ = normals[i + 2];
            normals[i] = (m.m11 * cX) + (m.m12 * cY) + (m.m13 * cZ);
            normals[i + 1] = (m.m21 * cX) + (m.m22 * cY) + (m.m23 * cZ);
            normals[i + 2] = (m.m31 * cX) + (m.m32 * cY) + (m.m33 * cZ);
        }
    }

    // Local
    void Transform(const Matrix44D &m, const Vector3D &v) {
        for (int i = 0; i < (faceCount * 3) * 3; i = i + 3) {
            verticies[i] -= v.x;
            verticies[i + 1] -= v.y;
            verticies[i + 2] -= v.z;

            double cX = verticies[i], cY = verticies[i + 1], cZ = verticies[i + 2];
            verticies[i] = (m.m11 * cX) + (m.m12 * cY) + (m.m13 * cZ);
            verticies[i + 1] = (m.m21 * cX) + (m.m22 * cY) + (m.m23 * cZ);
            verticies[i + 2] = (m.m31 * cX) + (m.m32 * cY) + (m.m33 * cZ);
            cX = verticies[i], cY = verticies[i + 1], cZ = verticies[i + 2];

            verticies[i] += v.x;
            verticies[i + 1] += v.y;
            verticies[i + 2] += v.z;

            cX = normals[i];
            cY = normals[i + 1];
            cZ = normals[i + 2];
            normals[i] = (m.m11 * cX) + (m.m12 * cY) + (m.m13 * cZ);
            normals[i + 1] = (m.m21 * cX) + (m.m22 * cY) + (m.m23 * cZ);
            normals[i + 2] = (m.m31 * cX) + (m.m32 * cY) + (m.m33 * cZ);
        }
    }

    void Load() {
        string line;
        ifstream reader(this->meshPath);

        vector<double> tmpVertecies;
        vector<double> tmpNormals;
        vector<double> tmpTextCoords;

        vector<double> finalVertecies;
        vector<double> finalNormal;
        vector<double> finalText;

        if (reader.is_open()) {
            while (!reader.eof()) {
                reader >> line;
                switch (line[0]) {
                    case 'v':
                        if (line.length() > 1) {
                            if (line[1] == 't') {
                                for (int i = 0; i < TEXTURE_LENGHT; i++) {
                                    reader >> line;
                                    tmpTextCoords.push_back(stod(line));
                                }
                            } else {
                                for (int i = 0; i < NORMAL_LENGHT; i++) {
                                    reader >> line;
                                    tmpNormals.push_back(stod(line));
                                }
                            }
                        } else {
                            for (int i = 0; i < VERTEX_LENGHT; i++) {
                                reader >> line;
                                tmpVertecies.push_back(stod(line));
                            }
                        }
                        getline(reader, line);
                        break;
                    case 'f':
                        for (int i = 0; i < 3; i++) {
                            reader >> line;
                            string *t = Explode(line, '/');

                            int index = stoi(t[0]) - 1;  // dans le .obj, le vertex 0 sera noté comme 1
                            for (int i = index * VERTEX_LENGHT; i < (index * VERTEX_LENGHT) + VERTEX_LENGHT; i++) {
                                finalVertecies.push_back(tmpVertecies[i]);
                            }

                            index = stod(t[1]) - 1;
                            for (int i = index * TEXTURE_LENGHT; i < (index * TEXTURE_LENGHT) + TEXTURE_LENGHT; i++) {
                                finalText.push_back(tmpTextCoords[i]);
                            }

                            index = stod(t[2]) - 1;
                            for (int i = index * NORMAL_LENGHT; i < (index * NORMAL_LENGHT) + NORMAL_LENGHT; i++) {
                                finalNormal.push_back(tmpNormals[i]);
                            }
                        }
                        break;
                    default:
                        getline(reader, line);
                        break;
                }
            }
            reader.close();
        }

        this->vertexCount = finalVertecies.size() / VERTEX_LENGHT;
        this->faceCount = this->vertexCount / VERTEX_LENGHT;
        this->verticies = new double[vertexCount * VERTEX_LENGHT];
        this->normals = new double[vertexCount * NORMAL_LENGHT];
        this->textureCoords = new double[vertexCount * TEXTURE_LENGHT];

        for (int i = 0; i < vertexCount * VERTEX_LENGHT; i++) {
            verticies[i] = finalVertecies[i];
        }
        for (int i = 0; i < vertexCount * NORMAL_LENGHT; i++) {
            normals[i] = finalNormal[i];
        }
        for (int i = 0; i < vertexCount * TEXTURE_LENGHT; i++) {
            textureCoords[i] = finalText[i];
        }
    }

    void Render() override {
        if (textureId == 0) {
            glGenTextures(1, &textureId);
            glBindTexture(GL_TEXTURE_2D, textureId);
            SDL_Surface *sdlSurface = IMG_Load(texturePath.c_str());
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
            SDL_FreeSurface(sdlSurface);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glBindTexture(GL_TEXTURE_2D, textureId);
        glVertexPointer(3, GL_DOUBLE, 0, verticies);
        glNormalPointer(GL_DOUBLE, 0, normals);
        glTexCoordPointer(2, GL_DOUBLE, 0, textureCoords);

        glDrawArrays(GL_TRIANGLES, 0, vertexCount);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }

    void Notification() {
        Vector3D movement = this->GetGameObjectTransform()->getPosition() - this->lastTransform.getPosition();
        if (movement.GetNorm() > 0) {
            this->Translate(movement);
        }

        Vector3D rotationChange = this->GetGameObjectTransform()->getRotation() - this->lastTransform.getRotation();
        if (rotationChange.GetNorm() > 0) {
            Matrix44D rotation = Matrix44D();
            if (abs(rotationChange.x) > 0) {
                double test = MathUtils::degToRad(rotationChange.x);
                rotation.LoadRotationX(test);
                this->Transform(rotation, this->GetGameObjectTransform()->getPosition());
            }
            if (abs(rotationChange.y) > 0) {
                rotation.LoadRotationY(rotationChange.y);
                this->Transform(rotation, this->GetGameObjectTransform()->getPosition());
            }
            if (abs(rotationChange.z) > 0) {
                rotation.LoadRotationZ(rotationChange.z);
                this->Transform(rotation, this->GetGameObjectTransform()->getPosition());
            }
        }

        Vector3D scaleChange = this->GetGameObjectTransform()->getScale() - this->lastTransform.getScale();
        if (scaleChange.GetNorm() > 0) {
            Matrix44D scale = Matrix44D();
            scale.LoadScale(scaleChange.x, scaleChange.y, scaleChange.z);
            this->Transform(scale, this->GetGameObjectTransform()->getPosition());
        }

        this->lastTransform = *this->GetGameObjectTransform();
    }

    string *Explode(string textToSplit, char delimiter = 0) {
        vector<string> value = vector<string>();
        int s = 0;
        for (int i = 0; i < textToSplit.length(); i++) {
            if (textToSplit[i] == delimiter || delimiter == 0) {
                value.push_back(textToSplit.substr(s, i));
                textToSplit = textToSplit.substr(i + 1, textToSplit.length() - 1);
                i = -1;
            }
        }
        value.push_back(textToSplit);
        string *v = new string[value.size()];
        int i = 0;
        for (string s : value) {
            v[i] = value[i];
            i++;
        }
        return v;
    }
};
}  // namespace GEngine

#endif