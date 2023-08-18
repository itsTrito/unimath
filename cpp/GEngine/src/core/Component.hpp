#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "LifeCycleObject.hpp"
#include "Transform.hpp"

namespace GEngine {
class Component : public LifeCycleObject {
   private:
    Transform* gameObjectTransform;

   public:
    Component(Transform* gameObjectTransform) {
        this->gameObjectTransform = gameObjectTransform;
    }

    virtual void Init(){};
    virtual void Start(){};
    virtual void Update(double deltaTime){};
    virtual void LateUpdate(double deltaTime){};
    virtual void Quit(){};
    virtual void Destroy(){};
};
}  // namespace GEngine
#endif