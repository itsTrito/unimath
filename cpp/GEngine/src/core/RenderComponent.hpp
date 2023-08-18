#ifndef RENDER_COMPONENT_HPP
#define RENDER_COMPONENT_HPP

#include "Component.hpp"
#include "Transform.hpp"

namespace GEngine {
class RenderComponent : public Component {
   public:
    RenderComponent(Transform* gameObjectTransform) : Component(gameObjectTransform) {}

    virtual void Render() = 0;
};
}  // namespace GEngine

#endif
