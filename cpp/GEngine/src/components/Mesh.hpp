#ifndef MESH_HPP
#define MESH_HPP

#include "../core/RenderComponent.hpp"
#include "../core/Transform.hpp"
#include "../handlers/RenderHandler.hpp"
#include "../math/MathUtils.hpp"

namespace GEngine {
class Mesh : public RenderComponent {
   protected:
    string meshPath;
    double *verticies;
    double *normals;
    size_t vertexCount;
    size_t faceCount;
    Transform lastTransform;

    const static unsigned char VERTEX_LENGHT = 3;
    const static unsigned char NORMAL_LENGHT = 3;

    Mesh(string meshPath) {
        this->meshPath = meshPath;
        this->lastTransform = GEngine::Transform();
    }

    ~Mesh() {
        delete[] verticies;
        delete[] normals;
    }

   public:
    void Init() {
        RenderHandler::GetInstance().Subscribe(this);
        Load();
        this->GetGameObjectTransform()->AddObserver(this);
    }

    void Destroy() {
        RenderHandler::GetInstance().Unsubscribe(this);
        this->GetGameObjectTransform()->RemoveObserver(this);
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

    void Notification() {
        Vector3D newScale = this->GetGameObjectTransform()->getScale();
        Vector3D movement = this->GetGameObjectTransform()->getPosition() - this->lastTransform.getPosition();
        Vector3D rotationChange = this->GetGameObjectTransform()->getRotation() - this->lastTransform.getRotation();
        Vector3D scaleChange = newScale - lastTransform.getScale();

        if (movement.GetNorm() > 0) {
            this->Translate(movement);
        }

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

        if (scaleChange.GetNorm() > 0) {
            Matrix44D scale = Matrix44D();
            scale.LoadScale(newScale.x, newScale.y, newScale.z);
            this->Transform(scale, this->GetGameObjectTransform()->getPosition());
        }

        this->lastTransform = *this->GetGameObjectTransform();
    }

    virtual void Load() = 0;
};
}  // namespace GEngine

#endif