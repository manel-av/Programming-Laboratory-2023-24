#include "pch.h"
#include "BallTree.h"
#include <limits>

void BallTree::construirArbre(const std::vector<Coordinate>& coordenades) {
    if (coordenades.empty()) return;

    m_coordenades = coordenades;
    m_root = this;

    if (coordenades.size() == 1) {
        m_pivot = coordenades[0];
        m_radi = 0.0;
        return;
    }

    m_pivot = calcularCentroide(coordenades);
    Coordinate A = encontrarPuntoMasLejano(m_pivot, coordenades);
    Coordinate B = encontrarPuntoMasLejano(A, coordenades);

    // Dividir puntos según distancia a A y B
    std::vector<Coordinate> esquerra, dreta;
    dividirPuntos(A, B, coordenades, esquerra, dreta);
    if (esquerra.empty() && !dreta.empty()) {
        esquerra.push_back(dreta.back());
        dreta.pop_back();
    }
    else if (dreta.empty() && !esquerra.empty()) {
        dreta.push_back(esquerra.back());
        esquerra.pop_back();
    }

    // Construir subárboles recursivamente
    if (!esquerra.empty()) {
        m_left = new BallTree();
        m_left->construirArbre(esquerra);
    }
    if (!dreta.empty()) {
        m_right = new BallTree();
        m_right->construirArbre(dreta);
    }

    // Calcular radio como distancia máxima al pivot
    m_radi = 0;
    for (const auto& coord : coordenades) {
        double dist = Util::DistanciaHaversine(m_pivot, coord);
        if (dist > m_radi) m_radi = dist;
    }
}

Coordinate BallTree::calcularCentroide(const std::vector<Coordinate>& coordenades) {
    double lat = 0, lon = 0;
    for (const auto& coord : coordenades) {
        lat += coord.lat;
        lon += coord.lon;
    }
    return { lat / coordenades.size(), lon / coordenades.size() };
}

Coordinate BallTree::encontrarPuntoMasLejano(const Coordinate& referencia,
    const std::vector<Coordinate>& coordenades) {
    Coordinate puntoMasLejano = coordenades[0];
    double maxDist = 0;

    for (const auto& coord : coordenades) {
        double dist = Util::DistanciaHaversine(referencia, coord);
        if (dist > maxDist) {
            maxDist = dist;
            puntoMasLejano = coord;
        }
    }
    return puntoMasLejano;
}

void BallTree::dividirPuntos(const Coordinate& a, const Coordinate& b,
    const std::vector<Coordinate>& entrada,
    std::vector<Coordinate>& esquerra,
    std::vector<Coordinate>& dreta) {
    for (const auto& coord : entrada) {
        double distA = Util::DistanciaHaversine(a, coord);
        double distB = Util::DistanciaHaversine(b, coord);

        if (distA < distB) {
            esquerra.push_back(coord);
        }
        else {
            dreta.push_back(coord);
        }
    }
}

void BallTree::preOrdre(std::vector<std::list<Coordinate>>& out) {
    std::list<Coordinate> llista;
    for (int i = 0; i < m_coordenades.size(); i++)
    {
        llista.push_back(m_coordenades[i]);
    }
    out.push_back(llista);

    if (m_right != nullptr)
        m_right->preOrdre(out);
    if (m_left != nullptr)
        m_left->preOrdre(out);
}

void BallTree::inOrdre(std::vector<std::list<Coordinate>>& out)
{
    if (m_right != nullptr)
        m_right->inOrdre(out);

    std::list<Coordinate> llista;
    for (int i = 0; i < m_coordenades.size(); i++)
    {
        llista.push_back(m_coordenades[i]);
    }
    out.push_back(llista);

    if (m_left != nullptr)
        m_left->inOrdre(out);
}

void BallTree::postOrdre(std::vector<std::list<Coordinate>>& out)
{
    if (m_right != nullptr)
        m_right->postOrdre(out);
    if (m_left != nullptr)
        m_left->postOrdre(out);

    std::list<Coordinate> llista;
    for (int i = 0; i < m_coordenades.size(); i++)
    {
        llista.push_back(m_coordenades[i]);
    }
    out.push_back(llista);
}

Coordinate BallTree::nodeMesProper(Coordinate pdi, Coordinate& Q, BallTree* bola_arrel) {
    if (!bola_arrel) return Q;

    if (!bola_arrel->m_left && !bola_arrel->m_right) {
        double minDist = (std::numeric_limits<double>::max)();
        Coordinate closest;

        for (const auto& coord : bola_arrel->m_coordenades) {
            double dist = Util::DistanciaHaversine(pdi, coord);
            if (dist < minDist) {
                minDist = dist;
                closest = coord;
            }
        }
        return closest;
    }

    // Decidir por qué subárbol continuar
    BallTree* primer = bola_arrel->m_left;
    BallTree* segon = bola_arrel->m_right;

    double distPrimer = primer ? Util::DistanciaHaversine(pdi, primer->m_pivot) : (std::numeric_limits<double>::max)();
    double distSegon = segon ? Util::DistanciaHaversine(pdi, segon->m_pivot) : (std::numeric_limits<double>::max)();

    if (distSegon < distPrimer) {
        std::swap(primer, segon);
        std::swap(distPrimer, distSegon);
    }

    // Buscar recursivamente en el subárbol más cercano
    Coordinate millor = nodeMesProper(pdi, Q, primer);

    // Comprobar si es necesario buscar en el otro subárbol
    if (segon && (distSegon - segon->m_radi) < Util::DistanciaHaversine(pdi, millor)) {
        Coordinate candidat = nodeMesProper(pdi, Q, segon);
        if (Util::DistanciaHaversine(pdi, candidat) < Util::DistanciaHaversine(pdi, millor)) {
            millor = candidat;
        }
    }

    return millor;
}