#pragma once
#include "Util.h"
#include "CamiSolucio.h"
#include <list>

class GrafSolucio
{
public:
	GrafSolucio();
	GrafSolucio(std::vector<CamiBase*> camins);
	~GrafSolucio();

	void afegirAresta(int posNode1, int posNode2);
	void afegirNode(const Coordinate& node);

	int distanciaMin(std::vector<float>& dist, std::vector<bool>& visitat);
	float distanciaVei(int posVeiAct, int posVei);
	int cerca(const Coordinate cerca, const std::vector<Coordinate> nodes);
	void camiMesCurt(Coordinate node1, Coordinate node2, CamiBase* camiSolucio);

	static bool cercaCoords(std::vector<Coordinate> v, const Coordinate& coord);

private:
	std::vector<Coordinate> m_nodes;
	std::vector<std::list<std::pair<int, double>>> m_veins;
	int m_numNodes;
	int m_numArestes;
	const int DISTMAX = 2147483647;

};