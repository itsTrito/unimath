#ifndef RENDER_COMPONENT_HPP
#define RENDER_COMPONENT_HPP

#include "../handlers/RenderConfig.hpp"
#include "Component.hpp"

namespace GEngine {
class RenderComponent : public Component {
   public:
    virtual void Render(RenderConfig config) = 0;
};
}  // namespace GEngine

#endif
