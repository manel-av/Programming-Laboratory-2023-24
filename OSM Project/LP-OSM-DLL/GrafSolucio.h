#pragma once
#include "Common.h"
#include <map>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

inline bool operator==(const Coordinate& a, const Coordinate& b) {
    const double epsilon = 0.000001;
    return (std::abs(a.lat - b.lat) < epsilon) &&
        (std::abs(a.lon - b.lon) < epsilon);
}

inline bool operator!=(const Coordinate& a, const Coordinate& b) {
    return !(a == b);
}

inline bool operator<(const Coordinate& a, const Coordinate& b) {
    const double epsilon = 0.000001;
    if (a.lat < b.lat - epsilon) return true;
    if (a.lat > b.lat + epsilon) return false;
    return a.lon < b.lon - epsilon;
}

class GrafSolucio {
public:
    void afegeixNode(const Coordinate& coord) {
        if (m_arestes.find(coord) == m_arestes.end()) {
            m_arestes[coord] = {};
        }
    }

    void afegeixAresta(const Coordinate& a, const Coordinate& b) {
        double dist = Util::DistanciaHaversine(a, b);
        m_arestes[a].push_back({ b, dist });
        m_arestes[b].push_back({ a, dist }); // Grafo no dirigido
    }

    static bool cercaCoords(const std::vector<Coordinate>& vec, const Coordinate& c) {
        return std::find(vec.begin(), vec.end(), c) != vec.end();
    }

    void camiMesCurt(const Coordinate& origen, const Coordinate& desti, CamiBase* cami) {
        std::map<Coordinate, double> distancies;
        std::map<Coordinate, Coordinate> predecessors;
        std::priority_queue<std::pair<double, Coordinate>,
            std::vector<std::pair<double, Coordinate>>,
            std::greater<std::pair<double, Coordinate>>> pq;

        // Inicialización
        for (const auto& pair : m_arestes) {
            distancies[pair.first] = (std::numeric_limits<double>::max)();
        }
        distancies[origen] = 0;
        pq.push({ 0, origen });

        // Algoritmo de Dijkstra
        while (!pq.empty()) {
            Coordinate u = pq.top().second;
            pq.pop();

            if (u == desti) break;

            for (const auto& vei : m_arestes[u]) {
                Coordinate v = vei.first;
                double pes = vei.second;

                if (distancies[v] > distancies[u] + pes) {
                    distancies[v] = distancies[u] + pes;
                    predecessors[v] = u;
                    pq.push({ distancies[v], v });
                }
            }
        }

        // Reconstruir camino
        std::vector<Coordinate> ruta;
        Coordinate actual = desti;
        while (predecessors.find(actual) != predecessors.end()) {
            ruta.push_back(actual);
            actual = predecessors[actual];
        }
        ruta.push_back(origen);
        std::reverse(ruta.begin(), ruta.end());

        // Asignar al objeto cami
        for (const auto& coord : ruta) {
            cami->afegeixCoord(coord);
        }
    }

private:
    std::map<Coordinate, std::vector<std::pair<Coordinate, double>>> m_arestes;
};