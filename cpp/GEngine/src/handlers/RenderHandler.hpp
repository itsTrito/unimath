#ifndef RENDER_HANDLER_HPP
#define RENDER_HANDLER_HPP

#include <map>

#include "../core/RenderComponent.hpp"
#include "../core/Scene.hpp"
#include "../design/Singleton.hpp"
#include "Handler.hpp"

namespace GEngine {

class RenderHandler : public Handler<RenderHandler, RenderComponent> {
   public:
    void Render() {
        if (currentScene == nullptr) {
            return;
        }

        std::vector<RenderComponent*> currentSceneRenderComponents = components[currentScene];
        for (RenderComponent* component : currentSceneRenderComponents) {
            component->Render();
        }
    }
};

}  // namespace GEngine

#endif
