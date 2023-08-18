/**
 * @file Vector3D.hpp
 * @author Tristan de Brault
 * @brief Représentation d'un vecteur 3 doubles
 * @version 0.1
 * @date 2021-09-01
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP
#include <math.h>

#include <iostream>

using namespace std;

namespace GEngine {
/**
 *
 * @brief Représentation d'un vecteur ayant comme composantes 3 doubles
 * @class Vecteur3D
 */
class Vector3D {
   public:
    double x;  ///< Composante horizontal du vecteur
    double y;  ///< Composante vertical du vecteur
    double z;  ///< Composante en profondeur du vecteur

    /**
     * @param x Composante horizontal du vecteur
     * @param y Composante vertical du vecteur
     * @param z Composante en profondeur du vecteur
     */
    Vector3D(double x = 0, double y = 0, double z = 0) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    /**
     * @brief Retourne la norme du vecteur
     * @return La norme du vecteur
     */
    double GetNorm() {
        return sqrt((x * x) + (y * y) + (z * z));
    }

    /**
     * @brief Normalise un vecteur (sa norme devient égal à 1)
     */
    void Normalize() {
        double norm = this->GetNorm();
        this->x /= norm;
        this->y /= norm;
        this->z /= norm;
    }

    /**
     * @brief Effectue une somme vectorielle
     *
     * @param v Le vecteur à additionner
     * @return Le somme des 2 vecteurs
     */
    Vector3D operator+(const Vector3D& v) {
        return Vector3D(this->x + v.x, this->y + v.y, this->z + v.z);
    }

    void operator+=(const Vector3D& v) {
        Vector3D v2 = *this + v;
        x = v2.x;
        y = v2.y;
        z = v2.z;
    }

    /**
     * @brief Effectue une différence vectorielle
     *
     * @param v Le vecteur à soustraire
     * @return Le différence des 2 vecteurs
     */
    Vector3D operator-(const Vector3D& v) {
        return Vector3D(this->x - v.x, this->y - v.y, this->z - v.z);
    }

    /**
     * @brief Effectue le calcul du produit scalaire
     *
     * @param v Le vecteur à multiplier
     * @return Le produit scalaire des 2 vecteurs
     */
    double operator*(const Vector3D& v) {
        return (this->x * v.x) + (this->y * v.y) + (this->z * v.z);
    }

    /**
     * @brief Effectue le produit par un scalaire
     *
     * @param s Le scalaire par lequel un multiplie notre norme
     * @return Le nouveau vecteur multiplié par le scalaire
     */
    Vector3D operator*(double s) {
        return Vector3D(this->x * s, this->y * s, this->z * s);
    }

    /**
     * @brief Effectue le calcul matricielle
     *
     * @param m La matrice 4d par laquel en multiplie le vecteur
     * @return Vector3D le nouveau vecteur modifié
     */
    /*
    Vector3D operator* (Matrix44D m){
        Vector3D t;
        t.x = (m[1] * this->x) + (m[2] * this->y) + (m[3] * this->z);
        t.y = (m[5] * this->x) + (m[6] * this->y) + (m[7] * this->z);
        t.z = (m[9] * this->x) + (m[10] * this->y) + (m[11] * this->z);
        return t;
    }*/

    /**
     * @brief Effectue le calcul matricielle sur un vecteur et assigne la nouvelle valeur
     *
     * @param m La matrice 4d par laquel en multiplie le vecteur
     */
    /* void operator*= (const Matrix44D& m){
         Vector3D t;
         t.x = (m[1] * this->x) + (m[2] * this->y) + (m[3] * this->z);
         t.y = (m[5] * this->x) + (m[6] * this->y) + (m[7] * this->z);
         t.z = (m[9] * this->x) + (m[10] * this->y) + (m[11] * this->z);
         *this = t;
     }*/

    /**
     * @brief Effectue le produit vectorielle
     *
     * @param v Le vecteur sur lequel on veut effectuer le produit vectorielle
     * @return Le vecteur orthogonale des 2 vecteurs
     */
    Vector3D operator%(const Vector3D& v) {
        return Vector3D((this->y * v.z) - (this->z * v.y), (this->z * v.x) - (this->x * v.z), (this->x * v.y) - (this->y * v.x));
    }

    /**
     * @brief Retourne l'angle entre 2 vecteurs
     *
     * @param v Le vecteur avec lequel on veut calculer l'angle
     * @return L'angle entre les 2 vecteurs
     */
    double GetAngle(Vector3D& v) {
        return acos((*this * v) / (this->GetNorm() * v.GetNorm()));
    }

    /**
     * @brief Inverse le vecteur
     *
     */
    Vector3D Inverse() {
        this->x = -this->x;
        this->y = -this->y;
        this->z = -this->z;
        return *this;
    }

    string toString() {
        string yo = "X :" + to_string(x) + " Y:" + to_string(y) + " Z:" + to_string(z);
        cout << yo << endl;
        return yo;
    }

    Vector3D noY() {
        return Vector3D(this->x, 0.0, this->z);
    }

    Vector3D justY() {
        return Vector3D(0.0, this->y, 0.0);
    }
};
}  // namespace GEngine
#endif