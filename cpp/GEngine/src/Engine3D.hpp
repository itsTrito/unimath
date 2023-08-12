#ifndef ENGINE3D_HPP
#define ENGINE3D_HPP

#include <cmath>

#include "Chrono.hpp"
#include "Engine.hpp"
#include "EventContainer.hpp"
#include "EventDispatcher.hpp"
#include "FirstPersonCamera.hpp"
#include "Matrix44D.hpp"
#include "Renderer3D.hpp"
#include "Text.hpp"
#include "Vector3D.hpp"
#include "components/TexturedMesh.hpp"
#include "core/GameObject.hpp"
#include "core/Scene.hpp"

using namespace std;

namespace GEngine {
class Engine3D : public Engine<Engine3D> {
   private:
    Renderer3D renderer = Renderer3D(1000, 1000, "Crate");
    FirstPersonCamera cam;  // = FirstPersonCamera(Vector3D(0.0,0.0,-1.0), Vector3D(0.0,0.0,1.0), Vector3D(0.0,1.0,0.0));
    // Observable keyDown, keyUp;
    EventDispatcher eventDispatcher;
    TTF_Font* ttfFont;
    TexturedMesh mesh = TexturedMesh("../res/monkey.obj", "../res/crate.png");
    Chrono chrono;
    Text framecounter = Text("FPS : " + to_string(chrono.FramePerSecond()), "../res/monogram.ttf", 20);

   public:
    Engine3D() {
        // keyDown.AddObserver(&cam);
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
        // Vector3D p = Vector3D(0.0,0.0,0.0);
        // Vector3D m = Vector3D(0.00729,0.00651,0.0);

        Vector3D c1 = Vector3D(-1.0, 1.0, -1.0);
        Vector3D c2 = Vector3D(1.0, 1.0, -1.0);
        Vector3D c3 = Vector3D(1.0, 1.0, 1.0);
        Vector3D c4 = Vector3D(-1.0, 1.0, 1.0);
        Vector3D c5 = Vector3D(-1.0, -1.0, -1.0);
        Vector3D c6 = Vector3D(1.0, -1.0, -1.0);
        Vector3D c7 = Vector3D(1.0, -1.0, 1.0);
        Vector3D c8 = Vector3D(-1.0, -1.0, 1.0);

        Vector3D nt = Vector3D(0.0, 1.0, 0.0);
        Vector3D nb = Vector3D(0.0, -1.0, 0.0);
        Vector3D nf = Vector3D(0.0, 0.0, 1.0);
        Vector3D nbk = Vector3D(0.0, 0.0, -1.0);
        Vector3D nr = Vector3D(1.0, 0.0, 0.0);
        Vector3D nl = Vector3D(-1.0, 0.0, 0.0);

        Matrix44D rotationX;
        Matrix44D rotationY;
        Matrix44D rotationZ;

        rotationX.LoadRotationX(0.000488);
        rotationY.LoadRotationY(0.0000688);
        rotationZ.LoadRotationZ(0.0000988);

        Scene scene = initScene();
        scene.Init();

        /*
         size_t vertexCount = 24;
         //6 faces * 4 sommets * 3 coords(xyz)
         double verticies[vertexCount * 3] = {  c1.x,c1.y,c1.z, c2.x,c2.y,c2.z, c3.x,c3.y,c3.z, c4.x,c4.y,c4.z,
                                                 c5.x,c5.y,c5.z, c6.x,c6.y,c6.z, c7.x,c7.y,c7.z, c8.x,c8.y,c8.z,
                                                 c3.x,c3.y,c3.z, c2.x,c2.y,c2.z, c6.x,c6.y,c6.z, c7.x,c7.y,c7.z,
                                                 c1.x,c1.y,c1.z, c4.x,c4.y,c4.z, c8.x,c8.y,c8.z, c5.x,c5.y,c5.z,
                                                 c1.x,c1.y,c1.z, c2.x,c2.y,c2.z, c6.x,c6.y,c6.z, c5.x,c5.y,c5.z,
                                                 c4.x,c4.y,c4.z, c3.x,c3.y,c3.z, c7.x,c7.y,c7.z, c8.x,c8.y,c8.z};

         double normals[vertexCount * 3] = { nt.x,nt.y,nt.z,nt.x,nt.y,nt.z,nt.x,nt.y,nt.z,nt.x,nt.y,nt.z,
                                             nb.x,nb.y,nb.z,nb.x,nb.y,nb.z,nb.x,nb.y,nb.z,nb.x,nb.y,nb.z,
                                             nr.x,nr.y,nr.z,nr.x,nr.y,nr.z,nr.x,nr.y,nr.z,nr.x,nr.y,nr.z,
                                             nl.x,nl.y,nl.z,nl.x,nl.y,nl.z,nl.x,nl.y,nl.z,nl.x,nl.y,nl.z,
                                             nbk.x,nbk.y,nbk.z,nbk.x,nbk.y,nbk.z,nbk.x,nbk.y,nbk.z,nbk.x,nbk.y,nbk.z,
                                             nf.x,nf.y,nf.z,nf.x,nf.y,nf.z,nf.x,nf.y,nf.z,nf.x,nf.y,nf.z};

         //6 faces * 4 sommets * 2 coords(xy)
         double textureCoords[vertexCount * 2] = {   0.0,0.0,1.0,0.0,1.0,1.0,0.0,1.0,
                                                     0.0,0.0,1.0,0.0,1.0,1.0,0.0,1.0,
                                                     0.0,0.0,1.0,0.0,1.0,1.0,0.0,1.0,
                                                     0.0,0.0,1.0,0.0,1.0,1.0,0.0,1.0,
                                                     0.0,0.0,1.0,0.0,1.0,1.0,0.0,1.0,
                                                     0.0,0.0,1.0,0.0,1.0,1.0,0.0,1.0 };*/

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

                        /*
                    case SDL_KEYDOWN:
                        keyDown.Notify();
                        break;
                    case SDL_KEYUP:
                        keyUp.Notify();
                        break;*/
                }
            }

            // Gestion des mises à jour
            /*
            p = p + m;
            if((p.x + 100) >= renderer.GetSize().x || p.x <= 0.0){
                m.x = -m.x;
            }
            if((p.y + 100) >= renderer.GetSize().y || p.y <= 0.0){
                m.y = -m.y;
            }*/

            cam.Update();
            // 3d
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glMultMatrixd(perspectiveProjection.matrix);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslated(0.0, 0.0, -5.0);

            cam.ApplyView();

            renderer.CenterCursor();

            mesh.Transform(rotationX);
            mesh.Transform(rotationY);
            mesh.Transform(rotationZ);

            scene.LateUpdate(chrono.DeltaTime());
            // mesh.Draw();
            /*
            c1 = rotationX * c1;
            c2 = rotationX * c2;
            c3 = rotationX * c3;
            c4 = rotationX * c4;
            c5 = rotationX * c5;
            c6 = rotationX * c6;
            c7 = rotationX * c7;
            c8 = rotationX * c8;

            nt = rotationX * nt;
            nb = rotationX * nb;
            nr = rotationX * nr;
            nl = rotationX * nl;
            nf = rotationX * nf;
            nbk = rotationX * nbk;

            c1 = rotationY * c1;
            c2 = rotationY * c2;
            c3 = rotationY * c3;
            c4 = rotationY * c4;
            c5 = rotationY * c5;
            c6 = rotationY * c6;
            c7 = rotationY * c7;
            c8 = rotationY * c8;

            nt = rotationY * nt;
            nb = rotationY * nb;
            nr = rotationY * nr;
            nl = rotationY * nl;
            nf = rotationY * nf;
            nbk = rotationY * nbk;


            c1 = rotationZ * c1;
            c2 = rotationZ * c2;
            c3 = rotationZ * c3;
            c4 = rotationZ * c4;
            c5 = rotationZ * c5;
            c6 = rotationZ * c6;
            c7 = rotationZ * c7;
            c8 = rotationZ * c8;

            nt = rotationZ * nt;
            nb = rotationZ * nb;
            nr = rotationZ * nr;
            nl = rotationZ * nl;
            nf = rotationZ * nf;
            nbk = rotationZ * nbk;

            glBindTexture(GL_TEXTURE_2D, crateTextureId);

            glBegin(GL_QUADS);
                //Top
                glNormal3d(nt.x,nt.y,nt.z);
                glTexCoord2d(0.0,0.0); glVertex3d(c1.x,c1.y,c1.z);
                glTexCoord2d(1.0,0.0); glVertex3d(c2.x,c2.y,c2.z);
                glTexCoord2d(1.0,1.0); glVertex3d(c3.x, c3.y, c3.z);
                glTexCoord2d(0.0,1.0); glVertex3d(c4.x, c4.y, c4.z);
                //Bottom
                glNormal3d(nb.x,nb.y,nb.z);
                glTexCoord2d(0.0,0.0); glVertex3d(c5.x,c5.y,c5.z);
                glTexCoord2d(1.0,0.0); glVertex3d(c6.x,c6.y,c6.z);
                glTexCoord2d(1.0,1.0); glVertex3d(c7.x, c7.y, c7.z);
                glTexCoord2d(0.0,1.0); glVertex3d(c8.x, c8.y, c8.z);
                //Right
                glNormal3d(nr.x,nr.y,nr.z);
                glTexCoord2d(0.0,0.0); glVertex3d(c3.x, c3.y, c3.z);
                glTexCoord2d(1.0,0.0); glVertex3d(c2.x,c2.y,c2.z);
                glTexCoord2d(1.0,1.0); glVertex3d(c6.x,c6.y,c6.z);
                glTexCoord2d(0.0,1.0); glVertex3d(c7.x, c7.y, c7.z);
                //Left
                glNormal3d(nl.x,nl.y,nl.z);
                glTexCoord2d(0.0,0.0); glVertex3d(c1.x,c1.y,c1.z);
                glTexCoord2d(1.0,0.0); glVertex3d(c4.x, c4.y, c4.z);
                glTexCoord2d(1.0,1.0); glVertex3d(c8.x, c8.y, c8.z);
                glTexCoord2d(0.0,1.0); glVertex3d(c5.x,c5.y,c5.z);
                //Back
                glNormal3d(nbk.x,nbk.y,nbk.z);
                glTexCoord2d(0.0,0.0); glVertex3d(c1.x,c1.y,c1.z);
                glTexCoord2d(1.0,0.0); glVertex3d(c2.x,c2.y,c2.z);
                glTexCoord2d(1.0,1.0); glVertex3d(c6.x,c6.y,c6.z);
                glTexCoord2d(0.0,1.0); glVertex3d(c5.x,c5.y,c5.z);
                //Front
                glNormal3d(nf.x,nf.y,nf.z);
                glTexCoord2d(0.0,0.0); glVertex3d(c4.x, c4.y, c4.z);
                glTexCoord2d(1.0,0.0); glVertex3d(c3.x, c3.y, c3.z);
                glTexCoord2d(1.0,1.0); glVertex3d(c7.x,c7.y,c7.z);
                glTexCoord2d(0.0,1.0); glVertex3d(c8.x,c8.y,c8.z);



            glEnd();*/

            // glEnable(GL_TEXTURE_2D);
            // 2d

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glMultMatrixd(orthogonalProjection.matrix);
            // glOrtho(0.0,1000.0,1000.0,0.0,1.0,-1.0);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            framecounter.Draw();
            framecounter.SetText("FPS: " + to_string(chrono.FramePerSecond()));

            // cam.DrawRay();

            renderer.RenderUpdate();
        }
    }

    Scene initScene() {
        GameObject go;
        go.addChild(GameObject());
        go.addComponent(&mesh);
        Scene scene;
        scene.addGameObject(go);
        return scene;
    }

    // glDisable(GL_TEXTURE_2D);
};
}  // namespace GEngine

#endif
