#include "pch.h"
#include "BallTree.h"

int BallTree::puntMesLlunya(const std::vector<double> distancies)
{
	double max = distancies[0];
	int pos = 0;
	for (auto it = distancies.begin(); it != distancies.end(); it++)
	{
		if ((*it) > max)
		{
			max = (*it);
			pos = distance(distancies.begin(), it);
		}
	}
	return pos;
}

void BallTree::construirArbre(const std::vector<Coordinate>& coordenades) {
	if (coordenades.size() == 1) {
		m_radi = 0;
		m_coordenades = coordenades;
		m_pivot = m_coordenades[0];
		m_left = nullptr;
		m_right = nullptr;
		m_root = this;
		return;
	}
	else {
		m_coordenades = coordenades;

		m_pivot = Util::calcularPuntCentral(m_coordenades);

		std::vector<double> vectorDistancias;
		for (const auto& idx : m_coordenades) {
			vectorDistancias.push_back(Util::DistanciaHaversine(m_pivot, idx));
		}

		int puntAMesLlunya = 0;
		double maxDistanciaA = vectorDistancias[0];
		for (int i = 1; i < vectorDistancias.size(); ++i) {
			if (vectorDistancias[i] > maxDistanciaA) {
				maxDistanciaA = vectorDistancias[i];
				puntAMesLlunya = i;
			}
		}

		vectorDistancias.clear();
		for (const auto& idx : m_coordenades) {
			vectorDistancias.push_back(Util::DistanciaHaversine(m_coordenades[puntAMesLlunya], idx));
		}

		m_radi = vectorDistancias[puntMesLlunya(vectorDistancias)];
		Coordinate PuntA = m_coordenades[puntAMesLlunya];
		Coordinate PuntB = m_coordenades[puntMesLlunya(vectorDistancias)];

		if (m_left != nullptr) {
			delete m_left;
			m_left = nullptr;
		}
		if (m_right != nullptr) {
			delete m_right;
			m_right = nullptr;
		}

		std::vector<Coordinate> datapointsL;
		std::vector<Coordinate> datapointsR;
		for (const auto& coord : m_coordenades) {
			double D1 = Util::DistanciaHaversine(PuntA, coord);
			double D2 = Util::DistanciaHaversine(PuntB, coord);
			if (D1 >= D2) {
				datapointsL.push_back(coord);
			}
			else if (D1 < D2) {
				datapointsR.push_back(coord);
			}
		}

		m_left = new BallTree();
		m_left->construirArbre(datapointsL);
		m_right = new BallTree();
		m_right->construirArbre(datapointsR);
		m_root = this;
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

Coordinate BallTree::nodeMesProper(Coordinate pdi, Coordinate& Q, BallTree* ball) {
	double D1 = Util::DistanciaHaversine(pdi, ball->getPivot());
	double D2 = Util::DistanciaHaversine(Q, ball->getPivot());

	if (D1 - ball->getRadi() >= D2) {
		return Q;
	}
	else {
		if (ball->getDreta() == nullptr && ball->getEsquerre() == nullptr) {
			double distanciaActual = Util::DistanciaHaversine(pdi, Q);
			double distancia = Util::DistanciaHaversine(pdi, ball->getCoordenades()[0]);
			if (distancia < distanciaActual) {
				Q = ball->getCoordenades()[0];
			}
			return Q;


		}
		else {
			double Da = Util::DistanciaHaversine(pdi, ball->getDreta()->getPivot());
			double Db = Util::DistanciaHaversine(pdi, ball->getEsquerre()->getPivot());
			if (Da < Db) {
				nodeMesProper(pdi, Q, ball->getEsquerre());
				nodeMesProper(pdi, Q, ball->getDreta());
			}
			else if (Da >= Db) {
				nodeMesProper(pdi, Q, ball->getDreta());
				nodeMesProper(pdi, Q, ball->getEsquerre());
			}
		}
		return Q;
	}
}