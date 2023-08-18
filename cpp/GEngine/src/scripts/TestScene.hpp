#ifndef TEST_SCENE_HPP
#define TEST_SCENE_HPP

#include "../components/TexturedMesh.hpp"
#include "../core/GameObject.hpp"
#include "../core/Scene.hpp"
#include "../core/Transform.hpp"
#include "Transformer.hpp"

using namespace GEngine;

namespace GEngineExample {
class TestScene : public Scene {
   public:
    TestScene() {
        GameObject go = GameObject(new Transform(), {GameObject()}, {new TexturedMesh("../res/monkey.obj", "../res/crate.png"), new Transformer()});
        this->addGameObject(go);
    }
};
}  // namespace GEngineExample

#endif
