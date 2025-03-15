#include "pch.h"
#include "GrafSolucio.h"

GrafSolucio::GrafSolucio()
{
	m_numNodes = 0;
	m_numArestes = 0;
}

bool GrafSolucio::cercaCoords(std::vector<Coordinate> v, const Coordinate& coord)
{
	auto it = v.begin();
	bool trobat = false;
	while (it != v.end())
	{
		if ((*it).lat == coord.lat && (*it).lon == coord.lon)
			trobat = true;
		it++;
	}
	return trobat;
}

GrafSolucio::GrafSolucio(std::vector<CamiBase*> camins) 
{
	m_numNodes = 0;
	m_numArestes = 0;
	for (int i = 0; i < camins.size(); i++)
	{
		std::vector<Coordinate> cami = camins[i]->getCamiCoords();
		if (!cercaCoords(m_nodes, cami[0]))
		{
			afegirNode(cami[0]);
		}
		for (int j = 1; j < cami.size(); j++)
		{
			int prev = j - 1;
			if (!cercaCoords(m_nodes, cami[j]))
			{
				afegirNode(cami[j]);
				int pos1 = cerca(cami[prev], m_nodes);
				int pos2 = cerca(cami[j], m_nodes);
				afegirAresta(pos1, pos2);
			}
			else
			{
				int pos1 = cerca(cami[prev], m_nodes);
				int pos2 = cerca(cami[j], m_nodes);

				afegirAresta(pos1, pos2);
			}
		}
	}
}

GrafSolucio::~GrafSolucio()
{
}

void GrafSolucio::afegirAresta(int posNode1, int posNode2)
{
	if ((posNode1 < m_numNodes) && (posNode2 < m_numNodes) && (posNode1 >= 0) && (posNode2 >= 0))
	{
		double distancia = Util::DistanciaHaversine(m_nodes[posNode1], m_nodes[posNode2]);
		m_veins[posNode1].emplace_back(std::pair<int, double>(posNode2, distancia));
		m_veins[posNode2].emplace_back(std::pair<int, double>(posNode1, distancia));
		m_numArestes++;
	}
}

void GrafSolucio::afegirNode(const Coordinate& node)
{
	m_nodes.push_back(node);
	m_numNodes++;
	m_veins.resize(m_numNodes);
}

int GrafSolucio::distanciaMin(std::vector<float>& distancia, std::vector<bool>& visitat)
{
	float min = abs(DISTMAX), pos = -1;
	for (int index = 0; index < m_numNodes; index++)
	{
		if (!visitat[index] && distancia[index] < min)
		{
			min = distancia[index];
			pos = index;
		}
	}
	return pos;
}

float GrafSolucio::distanciaVei(int posVeiAct, int posVei)
{
	return 0;
}

int GrafSolucio::cerca(const Coordinate cerca, const std::vector<Coordinate> nodes)
{
	int i = 0;
	bool trobat = false;
	while (i < nodes.size() && !trobat)
	{
		if (nodes[i].lat == cerca.lat && nodes[i].lon == cerca.lon)
			trobat = true;
		else
			i++;
	}
	if (trobat)
		return i;
	return -1;
}

void GrafSolucio::camiMesCurt(Coordinate node1, Coordinate node2, CamiBase* camiSolucio)
{
	int pos1 = cerca(node1, m_nodes);
	int pos2 = cerca(node2, m_nodes);
	std::vector<int> prev;
	std::vector<float> distancias;

	// Aplicar algoritmo de dijkstra
	std::vector<bool> visitat;
	distancias.resize(m_numNodes, DISTMAX);
	prev.resize(m_numNodes, -1);
	visitat.resize(m_numNodes, false);
	distancias[pos1] = 0;
	prev[pos1] = pos1;

	for (int i = 0; i < m_numNodes - 1; i++) {
		int indexActual = distanciaMin(distancias, visitat);
		visitat[indexActual] = true;
		if (indexActual == pos2)
		{
			return;
		}
		for (auto index = m_veins[indexActual].begin(); index != m_veins[indexActual].end(); index++) {
			if (!visitat[index->first]) {
				if (distancias[indexActual] + index->second < distancias[index->first]) {
					distancias[index->first] = distancias[indexActual] + index->second;
					prev[index->first] = indexActual;
				}
			}
		}
	}

	int it = pos2;
	camiSolucio->afegeixCoord(m_nodes[pos2]);
	while (it != pos1)
	{
		camiSolucio->afegeixCoord(m_nodes[prev[it]]);
		it = prev[it];
	}
}