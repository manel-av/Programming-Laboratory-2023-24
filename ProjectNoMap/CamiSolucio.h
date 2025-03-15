#pragma once

#include "CamiBase.h"

class CamiSolucio : public CamiBase
{
public:
	CamiSolucio() { m_way; }
	~CamiSolucio() { m_coords.clear(); }

	void setWay(const std::string& c) { m_way = c; }
	void setCoords(std::vector<Coordinate> coords) { m_coords = coords; }

	std::vector<Coordinate> getCamiCoords() { return m_coords; }
	void afegeixCoord(const Coordinate& element) { m_coords.push_back(element); }
private:
	std::string m_way;
	std::vector<Coordinate> m_coords; // Camino de coordenadas
};