#ifndef PHYSICS_COMPONENT_HPP
#define PHYSICS_COMPONENT_HPP

#include "../physics/PhysicsConstraint.hpp"
#include "Component.hpp"

namespace GEngine {
class PhysicsComponent : public Component {
   public:
    virtual void Evaluate(double deltaTime) = 0;
    virtual void ApplyConstraint(PhysicsConstraint constraint) = 0;
};

}  // namespace GEngine

#endif
