#ifndef RENDER_HANDLER_HPP
#define RENDER_HANDLER_HPP

#include <map>

#include "../core/RenderComponent.hpp"
#include "../core/Scene.hpp"
#include "../design/Singleton.hpp"

namespace GEngine {

class RenderHandler : public Singleton<RenderHandler> {
   private:
    Scene* currentScene;
    std::map<Scene*, std::vector<RenderComponent*>> renderComponents;

   public:
    void SetCurrentScene(Scene* scene) {
        this->currentScene = scene;
        if (renderComponents.find(scene) == renderComponents.end()) {
            renderComponents[scene] = std::vector<RenderComponent*>();
        }
    }

    void Render() {
        if (currentScene == nullptr) {
            return;
        }

        std::vector<RenderComponent*> currentSceneRenderComponents = renderComponents[currentScene];
        for (RenderComponent* component : currentSceneRenderComponents) {
            component->Render();
        }
    }

    void Subscribe(RenderComponent* renderComponent) {
        if (currentScene != nullptr) {
            renderComponents[currentScene].push_back(renderComponent);
        }
    }

    void ClearCurrentScene() {
        if (currentScene == nullptr) {
            return;
        }

        renderComponents[currentScene].clear();
    }
};

}  // namespace GEngine

#endif
