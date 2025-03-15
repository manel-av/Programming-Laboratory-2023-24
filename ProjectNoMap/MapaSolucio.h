#pragma once

#include "Util.h"
#include "MapaBase.h"
#include "PuntDeInteresBotigaSolucio.h"
#include "PuntDeInteresRestaurantSolucio.h"
#include "CamiSolucio.h"
#include "BallTree.h"
#include "GrafSolucio.h"

class MapaSolucio : public MapaBase
{
public:
	void getPdis(std::vector<PuntDeInteresBase*>& pdis);
	void getCamins(std::vector<CamiBase*>& camins);
	void parsejaXmlElements(std::vector<XmlElement>& xmlElements);
	void construeixGraf() { if (!m_camins.empty()) m_graf = new GrafSolucio(m_camins); }
	CamiBase* buscaCamiMesCurt(PuntDeInteresBase* from, PuntDeInteresBase* to);
private:
	GrafSolucio* m_graf;
	std::vector<CamiBase*> m_camins;
	std::vector<PuntDeInteresBase*> m_pdis;
};