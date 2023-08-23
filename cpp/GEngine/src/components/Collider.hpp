#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "../core/PhysicsComponent.hpp"
#include "../math/Matrix44D.hpp"
#include "../math/Vector3D.hpp"
#include "../resources/Color.hpp"
#include "ColoredMesh.hpp"
#include "Mesh.hpp"

namespace GEngine {
class Collider : public PhysicsComponent {
   private:
    Mesh mesh;
    bool isTrigger;

   public:
    Collider(Mesh mesh, bool isTrigger = false) {
        this->mesh = mesh;
        this->mesh.Load();
    }

    virtual bool DetectCollision() = 0;
    virtual void Draw() = 0;
    virtual void Translate(const Vector3D& translation) = 0;
    virtual void Transform(const Matrix44D& matrix, const Vector3D& position) = 0;
};

}  // namespace GEngine

#endif
