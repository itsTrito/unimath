#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "../core/PhysicsComponent.hpp"

namespace GEngine {
class Collider : public PhysicsComponent {
   private:
    /* data */
   public:
    Collider(/* args */);
    ~Collider();
};

}  // namespace GEngine

#endif
