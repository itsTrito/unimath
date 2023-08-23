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
        // getGameObjectTransform()->Translate(0.001, 0.00001, 0.00001);
        double angle = 0.05;
        GetGameObjectTransform()->Rotate(angle, angle, angle);
        GetGameObjectTransform()->Scale(1.001, 1.001, 1.001);
    }
};
}  // namespace GEngineExample

#endif
