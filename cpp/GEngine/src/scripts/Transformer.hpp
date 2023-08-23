#ifndef TRANSFORMER_HPP
#define TRANSFORMER_HPP

#include "../core/Component.hpp"
#include "../core/Transform.hpp"
#include "../math/MathUtils.hpp"
#include "../math/Matrix44D.hpp"

using namespace GEngine;

namespace GEngineExample {
class Transformer : public Component {
   public:
    Transformer() {}

    void Update(double deltaTime) {
        double angle = 0.05;
        GetGameObjectTransform()->Translate(0.001, 0, 0);
        GetGameObjectTransform()->Rotate(angle, 0, angle);
    }
};
}  // namespace GEngineExample

#endif
