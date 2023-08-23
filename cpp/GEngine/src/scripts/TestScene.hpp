#ifndef TEST_SCENE_HPP
#define TEST_SCENE_HPP

#include "../components/RigidBody.hpp"
#include "../components/TexturedMesh.hpp"
#include "../core/GameObject.hpp"
#include "../core/Scene.hpp"
#include "../core/Transform.hpp"
#include "../physics/PhysicsConstraint.hpp"
#include "../presets/CubePreset.hpp"
#include "Transformer.hpp"

using namespace GEngine;

namespace GEngineExample {
class TestScene : public Scene {
   public:
    TestScene() {
        RigidBody* rb = new RigidBody(0.5);
        rb->ApplyConstraint(PhysicsConstraint(Vector3D(0, 9.81 * 0.5, 0)));
        GameObject go = GameObject(new Transform(Vector3D(0, 2, -5)), {GameObject()}, {new TexturedMesh("../res/monkey.obj", "../res/crate.png"), rb});
        CubePreset cube = CubePreset(new Transform(Vector3D(0, -2, -5), Vector3D::Zero(), Vector3D(5, 0.5, 5)));
        this->addGameObject(cube);
        this->addGameObject(go);
    }
};
}  // namespace GEngineExample

#endif
