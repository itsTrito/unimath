#ifndef TRANSFORMER_HPP
#define TRANSFORMER_HPP

#include "../core/Component.hpp"
#include "../core/Transform.hpp"
#include "../math/Matrix44D.hpp"

using namespace GEngine;

namespace GEngineExample {
class Transformer : public Component {
   private:
   public:
    Transformer() {}

    void Update(double deltaTime) {
        // getGameObjectTransform()->Translate(0.001, 0.00001, 0.00001);
        getGameObjectTransform()->Rotate(0.0488, 0.00688, 0.00988);
        string tr = getGameObjectTransform()->toString();
        printf("%s", tr);
    }
};
}  // namespace GEngineExample

#endif
