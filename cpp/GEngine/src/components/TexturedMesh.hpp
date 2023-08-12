#ifndef TEXTURED_MESH_HPP
#define TEXTURED_MESH_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_ttf.h>

#include <fstream>
#include <string>
#include <vector>

#include "../Matrix44D.hpp"
#include "../Vector3D.hpp"
#include "Mesh.hpp"

using namespace std;
namespace GEngine {
class TexturedMesh : public Mesh {
   private:
    string texturePath;
    double *normals;
    double *textureCoords;
    unsigned int textureId;

    const unsigned char VERTEX_LENGHT = 3;
    const unsigned char NORMAL_LENGHT = 3;
    const unsigned char TEXTURE_LENGHT = 2;

   public:
    TexturedMesh(string meshPath, string texturePath) : Mesh(meshPath) {
        vertexCount = textureId = 0;
        this->texturePath = texturePath;
    }

    ~TexturedMesh() {
        delete[] verticies;
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
        for (int i = 0; i < vertexCount * VERTEX_LENGHT; i = i + 3) {
            int iy = i + 1;
            int iz = i + 2;
            verticies[i] = (m.m11 * verticies[i]) + (m.m12 * verticies[iy]) + (m.m13 * verticies[iz]);
            verticies[iy] = (m.m21 * verticies[i]) + (m.m22 * verticies[iy]) + (m.m23 * verticies[iz]);
            verticies[iz] = (m.m31 * verticies[i]) + (m.m32 * verticies[iy]) + (m.m33 * verticies[iz]);

            normals[i] = (m.m11 * normals[i]) + (m.m12 * normals[iy]) + (m.m13 * normals[iz]);
            normals[iy] = (m.m21 * normals[i]) + (m.m22 * normals[iy]) + (m.m23 * normals[iz]);
            normals[iz] = (m.m31 * normals[i]) + (m.m32 * normals[iy]) + (m.m33 * normals[iz]);
        }
    }

    // Local
    void Transform(const Matrix44D &m, const Vector3D &v) {
        for (int i = 0; i < vertexCount * VERTEX_LENGHT; i = i + 3) {
            int iy = i + 1;
            int iz = i + 2;

            verticies[i] -= v.x;
            verticies[iy] -= v.y;
            verticies[iz] -= v.z;

            verticies[i] = (m.m11 * verticies[i]) + (m.m12 * verticies[iy]) + (m.m13 * verticies[iz]);
            verticies[iy] = (m.m21 * verticies[i]) + (m.m22 * verticies[iy]) + (m.m23 * verticies[iz]);
            verticies[iz] = (m.m31 * verticies[i]) + (m.m32 * verticies[iy]) + (m.m33 * verticies[iz]);

            normals[i] = (m.m11 * normals[i]) + (m.m12 * normals[iy]) + (m.m13 * normals[iz]);
            normals[iy] = (m.m21 * normals[i]) + (m.m22 * normals[iy]) + (m.m23 * normals[iz]);
            normals[iz] = (m.m31 * normals[i]) + (m.m32 * normals[iy]) + (m.m33 * normals[iz]);

            verticies[i] += v.x;
            verticies[iy] += v.y;
            verticies[iz] += v.z;
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

    void Draw() {
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