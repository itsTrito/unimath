#ifndef RIGID_BODY_HPP
#define RIGID_BODY_HPP

#include "../core/PhysicsComponent.hpp"
#include "../handlers/PhysicsHandler.hpp"

#define gravity 9.81

namespace GEngine {
class RigidBody : public PhysicsComponent {
   private:
    double mass;
    vector<PhysicsConstraint> constraints;

   public:
    RigidBody(double mass = 0) {
        this->mass = mass;
    }

    void Init() {
        PhysicsHandler::GetInstance().Subscribe(this);
        ApplyConstraint(PhysicsConstraint(Vector3D::Down() * mass * gravity));
    }

    void Evaluate(double deltaTime) {
        for (PhysicsConstraint constraint : constraints) {
            constraint.Apply(this, deltaTime);
        }
    }

    void ApplyConstraint(PhysicsConstraint constraint) {
        constraints.push_back(constraint);
    }

    void Destroy() {
        PhysicsHandler::GetInstance().Unsubscribe(this);
    }
};
}  // namespace GEngine

#endif
