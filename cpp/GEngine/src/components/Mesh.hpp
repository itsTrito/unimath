#ifndef MESH_HPP
#define MESH_HPP

#include "../core/Component.hpp"

namespace GEngine {
class Mesh : public Component {
   protected:
    string meshPath;
    double* verticies;
    size_t vertexCount;

    Mesh(string meshPath) {
        this->meshPath = meshPath;
    }

   public:
    void Init() override {
        Load();
    }

    void LateUpdate(double deltaTime) override {
        Draw();
    }

    virtual void Load() = 0;

    virtual void Draw() = 0;
};
}  // namespace GEngine

#endif