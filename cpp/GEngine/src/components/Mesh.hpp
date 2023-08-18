#ifndef MESH_HPP
#define MESH_HPP

#include "../core/RenderComponent.hpp"
#include "../core/Transform.hpp"
#include "../handlers/RenderHandler.hpp"

namespace GEngine {
class Mesh : public RenderComponent {
   protected:
    string meshPath;
    double* verticies;
    size_t vertexCount;
    size_t faceCount;

    Mesh(string meshPath) {
        this->meshPath = meshPath;
    }

    ~Mesh() {
        delete[] verticies;
    }

   public:
    void Init() {
        RenderHandler::GetInstance().Subscribe(this);
        Load();
        this->getGameObjectTransform()->AddObserver(this);
    }

    void Destroy() {
        RenderHandler::GetInstance().Unsubscribe(this);
        this->getGameObjectTransform()->RemoveObserver(this);
    }

    virtual void Load() = 0;
};
}  // namespace GEngine

#endif