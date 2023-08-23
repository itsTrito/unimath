#ifndef ENGINE3D_HPP
#define ENGINE3D_HPP

#include <cmath>

#include "CameraGodCam.hpp"
#include "Chrono.hpp"
#include "Engine.hpp"
#include "EventContainer.hpp"
#include "EventDispatcher.hpp"
#include "Renderer3D.hpp"
#include "Text.hpp"
#include "components/TexturedMesh.hpp"
#include "core/GameObject.hpp"
#include "core/Scene.hpp"
#include "handlers/PhysicsHandler.hpp"
#include "handlers/RenderHandler.hpp"
#include "math/Matrix44D.hpp"
#include "math/Vector3D.hpp"
#include "scripts/TestScene.hpp"

using namespace std;

namespace GEngine {
class Engine3D : public Engine<Engine3D> {
   private:
    Renderer3D renderer = Renderer3D(1000, 1000, "Crate");
    CameraGodCam cam;
    EventDispatcher eventDispatcher;
    Chrono chrono;
    Text framecounter = Text("FPS : " + to_string(chrono.FramePerSecond()), "../res/monogram.ttf", 20);

   public:
    Engine3D() {
        eventDispatcher.Bind(SDL_KEYDOWN, &cam);
        eventDispatcher.Bind(SDL_KEYUP, &cam);
        eventDispatcher.Bind(SDL_MOUSEMOTION, &cam);
        eventDispatcher.Bind(SDL_KEYDOWN, &renderer);
    }

    ~Engine3D() {
        eventDispatcher.Unbind(SDL_KEYDOWN, &cam);
        eventDispatcher.Unbind(SDL_KEYUP, &cam);
        eventDispatcher.Unbind(SDL_MOUSEMOTION, &cam);
        eventDispatcher.Unbind(SDL_KEYDOWN, &renderer);
    }

    void Start() {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_DEPTH_TEST);
        // glEnable(GL_LIGHTING);
        // glEnable(GL_LIGHT0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        Matrix44D perspectiveProjection;
        double right = tan((45.0 * 3.14159) / 180.0);
        SDL_Point windowSize = renderer.GetSize();
        double top = ((double)windowSize.y / (double)windowSize.x) * right;
        perspectiveProjection.LoadPerspective(right, top, 1.0, 100.0);

        Matrix44D orthogonalProjection;
        orthogonalProjection.LoadOrthogonal(1000.0, 1000.0);

        Scene scene = GEngineExample::TestScene();
        RenderHandler::GetInstance().SetCurrentScene(&scene);
        PhysicsHandler::GetInstance().SetCurrentScene(&scene);

        scene.Init();
        scene.Start();

        bool isOpen = true;
        while (isOpen) {
            // Boucle de jeu
            // Gestion des évènements
            while (EventContainer::Poll()) {
                switch (EventContainer::GetType()) {
                    case SDL_QUIT:
                        isOpen = false;
                        break;
                    default:
                        eventDispatcher.Dispatch();
                        break;
                }
            }

            // TODO changer
            double deltaTime = chrono.EllapsedTime();
            chrono.Reset();
            cam.Update(deltaTime);

            // 3d
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glMultMatrixd(perspectiveProjection.matrix);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            cam.ApplyView();
            // cam.DrawRay();

            renderer.CenterCursor();

            scene.Update(deltaTime);
            PhysicsHandler::GetInstance().Evaluate(deltaTime);
            scene.LateUpdate(deltaTime);
            RenderHandler::GetInstance().Render();

            // glEnable(GL_TEXTURE_2D);
            // 2d

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glMultMatrixd(orthogonalProjection.matrix);
            // glOrtho(0.0,1000.0,1000.0,0.0,1.0,-1.0);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            double frameCount = chrono.FramePerSecond(0.5f);
            framecounter.Draw();
            framecounter.SetText("FPS: " + to_string(frameCount));

            renderer.RenderUpdate();
        }

        scene.Quit();
        scene.Destroy();
    }

    // glDisable(GL_TEXTURE_2D);
};
}  // namespace GEngine

#endif
