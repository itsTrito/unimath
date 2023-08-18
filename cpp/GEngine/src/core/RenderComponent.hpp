#ifndef RENDER_COMPONENT_HPP
#define RENDER_COMPONENT_HPP

#include "Component.hpp"
#include "Transform.hpp"

namespace GEngine {
class RenderComponent : public Component {
   public:
    virtual void Render() = 0;
};
}  // namespace GEngine

#endif
