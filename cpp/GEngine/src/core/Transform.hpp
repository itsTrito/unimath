#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "../Vector3D.hpp"

namespace GEngine {
class Transform {
   private:
    Vector3D position;
    Vector3D rotation;
    Vector3D scale;

   public:
    Transform() {
        this->position = Vector3D();
        this->rotation = Vector3D();
        this->scale = Vector3D();
    }

    Transform(Vector3D position, Vector3D rotation, Vector3D scale) {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;
    }
    ~Transform() {
    }
};

}  // namespace GEngine

#endif