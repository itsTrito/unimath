#ifndef CUBE_PRESET_HPP
#define CUBE_PRESET_HPP

#include "../components/TexturedMesh.hpp"
#include "../core/GameObject.hpp"
#include "../core/Transform.hpp"
#include "../scripts/Transformer.hpp"

namespace GEngine {
class CubePreset : public GameObject {
   public:
    CubePreset(Transform* transform = new Transform()) : GameObject(transform, {}, {new TexturedMesh("../res/box.obj", "../res/lindenCoeur.png")}) {}
};
}  // namespace GEngine

#endif
