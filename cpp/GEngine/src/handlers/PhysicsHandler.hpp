#ifndef PHYSICS_HANDLER_HPP
#define PHYSICS_HANDLER_HPP

#include "../core/PhysicsComponent.hpp"
#include "Handler.hpp"

namespace GEngine {
class PhysicsHandler : public Handler<PhysicsHandler, PhysicsComponent> {
   public:
    void Evaluate(double deltaTime) {
        if (currentScene == nullptr) {
            return;
        }

        std::vector<PhysicsComponent*> currentScenePhysicsComponents = components[currentScene];
        for (PhysicsComponent* component : currentScenePhysicsComponents) {
            component->Evaluate(deltaTime);
        }
    }
};

}  // namespace GEngine

#endif
