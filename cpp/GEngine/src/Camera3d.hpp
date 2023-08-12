/**
 * @file Camera3d.hpp
 * @author Trito
 * @brief
 * @version 0.1
 * @date 2021-09-22
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef CAMERA3D_HPP
#define CAMERA3D_HPP

#include <SDL2/SDL_opengl.h>

#include "Matrix44D.hpp"
#include "Vector3D.hpp"
#include "design/Observer_Observable.hpp"

namespace GEngine {
class Camera3D : public Observer {
   protected:
    Vector3D position;
    Vector3D target;
    Vector3D up;
    Matrix44D viewMatrix;

   public:
    Camera3D(Vector3D tar = Vector3D(0.0, 0.0, -1.0), Vector3D pos = Vector3D(0.0, 0.0, 5.0), Vector3D angleUp = Vector3D(0.0, 1.0, 0.0)) {
        this->position = pos;
        this->target = tar;
        this->up = angleUp;
        LoadView();
    }

    void ApplyView() {
        // Multiplier la matrice de vue
        glMultMatrixd(viewMatrix.matrix);
        glTranslated(-position.x, -position.y, -position.z);
    }

    /*void Move(Vector3D v){
        position = position + v;
    }*/

    Matrix44D LoadView() {
        Vector3D front = target - position;
        front.Normalize();

        Vector3D side = front % up;
        side.Normalize();

        up = side % front;
        up.Normalize();

        viewMatrix.LoadView(front, side, up);
        return viewMatrix;
    }

    void LookAt(Vector3D newTarget) {
        this->target = newTarget;
        LoadView();
    }

    void DrawRay() {
        glDisable(GL_TEXTURE_2D);
        glBegin(GL_LINES);
        glVertex3d(position.x, position.y + 1.0, position.z);
        Vector3D f = position - target;
        f.z *= 100.0;
        glVertex3d(f.x, f.y, f.z);
        glEnd();
        glEnable(GL_TEXTURE_2D);
    }

    virtual void Notification() = 0;

    virtual void Update() = 0;
};
}  // namespace GEngine

#endif