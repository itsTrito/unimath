#ifndef FIRSTPERSONCAMERA_HPP
#define FIRSTPERSONCAMERA_HPP

#include <iostream>

#include "Camera3d.hpp"
#include "EventContainer.hpp"
#include "math/Matrix44D.hpp"
#include "math/Vector3D.hpp"

namespace GEngine {
class FirstPersonCamera : public Camera3D {
   private:
    bool keyW = false, keyS = false, keyA = false, keyD = false, keySpace = false, keyCtrl = false;
    double sensitivity = 0.001;
    bool firstMovement = true;
    Vector3D front;
    double dirX = 0.0;
    double dirY = 0.0;
    double movementSpeed = 0.1;

   public:
    FirstPersonCamera(Vector3D tar = Vector3D(0.0, 0.0, -1.0), Vector3D pos = Vector3D(0.0, 0.0, -5.0), Vector3D angleUp = Vector3D(0.0, 1.0, 0.0)) : Camera3D(tar, pos, angleUp) {
    }

    void Notification() {
        switch (EventContainer::GetType()) {
            case SDL_KEYDOWN:
                switch (EventContainer::GetKey()) {
                    case SDLK_w:
                        keyW = true;
                        break;
                    case SDLK_a:
                        keyA = true;
                        break;
                    case SDLK_s:
                        keyS = true;
                        break;
                    case SDLK_d:
                        keyD = true;
                        break;
                    case SDLK_SPACE:
                        keySpace = true;
                        break;
                    case SDLK_LCTRL:
                        keyCtrl = true;
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (EventContainer::GetKey()) {
                    case SDLK_w:
                        keyW = false;
                        break;
                    case SDLK_a:
                        keyA = false;
                        break;
                    case SDLK_s:
                        keyS = false;
                        break;
                    case SDLK_d:
                        keyD = false;
                        break;
                    case SDLK_SPACE:
                        keySpace = false;
                        break;
                    case SDLK_LCTRL:
                        keyCtrl = false;
                        break;
                }
                // glColor3d(1.0,1.0,1.0);
                break;
            case SDL_MOUSEMOTION:
                Vector3D m = EventContainer::GetMouseMovement();
                RotateView(m);
                break;
        }
    }
    /*
    void Update(){
        if (keyW)
            this->position.z += 0.01;
        if (keyA)
            this->position.x += 0.01;
        if (keyS)
            this->position.z -= 0.01;
        if (keyD)
            this->position.x -= 0.01;
        if (keySpace)
            this->position.y -= 0.01;
        if (keyCtrl)
            this->position.y += 0.01;
    }*/

    void Move(Vector3D v) {
        position = position + v;
    }

    void Update() {
        Vector3D front = target - position;
        Vector3D side = front % up;
        up = side % front;
        side.Normalize();
        up.Normalize();
        front.Normalize();

        // front = front * movementSpeed;
        // side = side * movementSpeed;
        Vector3D mup = up;
        // position.toString();

        if (keyW) {
            Move(front.noY() * movementSpeed);
        }
        if (keyS)
            Move((front.noY() * -1) * movementSpeed);
        if (keyA)
            Move((side.noY() * -1) * movementSpeed);
        if (keyD)
            Move(side.noY() * movementSpeed);
        if (keySpace)
            Move((mup.justY() * -1) * movementSpeed);
        if (keyCtrl)
            Move(mup.justY() * movementSpeed);
    }

    void RotateView(Vector3D m) {
        // ApplySensitivity(&m);

        if (!firstMovement) {
            Vector3D m = EventContainer::GetMouseMovement();
            Vector3D front = this->target - this->position;
            m = m * sensitivity;

            dirX += m.x;
            dirY += m.y;
            if (Clamp(&dirX, -89.0 * (3.14 / 180.0), 89.0 * (3.14 / 180.0))) {
                m.x = 0;
            }

            if (Clamp(&dirY, -89.0 * (3.14 / 180.0), 89.0 * (3.14 / 180.0))) {
                m.y = 0;
            }

            front.x = cos((dirX)) * cos((dirY));
            front.y = sin((dirY));
            front.z = sin((dirX)) * cos((dirY));
            front.Normalize();

            /*
            Matrix44D rotateX;
            rotateX.LoadRotationX(m.x);

            Matrix44D rotateY;
            rotateY.LoadRotationY(m.y);

            front = rotateX * front;
            front = rotateY * front;

            front.Normalize();
            */

            Vector3D side = front % this->up;
            side.Normalize();

            this->up = side % front;
            up.Normalize();

            // target = position + front;

            this->viewMatrix.LoadView(front, side, this->up);

        } else {
            this->front = this->target - this->position;
        }
        firstMovement = false;
    }

    void ApplySensitivity(Vector3D* m) {
        m->x = m->x * sensitivity;
        m->y = m->y * sensitivity;
    }

    bool Clamp(double* value, double min, double max) {
        bool clamper = false;
        if (*value > max) {
            *value = max;
            clamper = true;
        }
        if (*value < min) {
            *value = min;
            clamper = true;
        }

        return clamper;
    }
};
}  // namespace GEngine
#endif