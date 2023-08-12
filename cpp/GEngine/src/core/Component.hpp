#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "LifeCycleObject.hpp"

namespace GEngine {
class Component : public LifeCycleObject {
   public:
    virtual void Init(){};
    virtual void Start(){};
    virtual void Update(double deltaTime){};
    virtual void LateUpdate(double deltaTime){};
    virtual void Quit(){};
    virtual void Destroy(){};
};
}  // namespace GEngine
#endif