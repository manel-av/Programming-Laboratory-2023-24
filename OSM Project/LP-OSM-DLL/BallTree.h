#ifndef _BALL_H
#define _BALL_H

#include "Util.h"
#include <list>
#include <vector>
#include <algorithm>

class BallTree {
public:
    BallTree() : m_root(nullptr), m_left(nullptr), m_right(nullptr), m_radi(0.0), m_pivot({ 0.0, 0.0 }) {}
    ~BallTree() {
        delete m_left;
        delete m_right;
    }

    // Getters
    BallTree* getArrel() { return m_root; }
    Coordinate getPivot() { return m_pivot; }
    double getRadi() { return m_radi; }
    BallTree* getDreta() { return m_right; }
    BallTree* getEsquerre() { return m_left; }
    std::vector<Coordinate>& getCoordenades() { return m_coordenades; }

    // Setters
    void setArrel(BallTree* root) { m_root = root; }
    void setPivot(Coordinate pivot) { m_pivot = pivot; }
    void setRadius(double radi) { m_radi = radi; }
    void setDreta(BallTree* right) { m_right = right; }
    void setEsquerre(BallTree* left) { m_left = left; }
    void setCoordenades(std::vector<Coordinate>& coordenades) { m_coordenades = coordenades; }

    // Métodos principales
    void construirArbre(const std::vector<Coordinate>& coordenades);
    void inOrdre(std::vector<std::list<Coordinate>>& out);
    void preOrdre(std::vector<std::list<Coordinate>>& out);
    void postOrdre(std::vector<std::list<Coordinate>>& out);
    Coordinate nodeMesProper(Coordinate pdi, Coordinate& Q, BallTree* bola_arrel);

private:
    BallTree* m_root;
    BallTree* m_left;
    BallTree* m_right;
    double m_radi;
    Coordinate m_pivot;
    std::vector<Coordinate> m_coordenades;

    // Métodos auxiliares
    Coordinate calcularCentroide(const std::vector<Coordinate>& coordenades);
    Coordinate encontrarPuntoMasLejano(const Coordinate& referencia, const std::vector<Coordinate>& coordenades);
    void dividirPuntos(const Coordinate& a, const Coordinate& b, const std::vector<Coordinate>& entrada,
        std::vector<Coordinate>& esquerra, std::vector<Coordinate>& dreta);
};

#endif