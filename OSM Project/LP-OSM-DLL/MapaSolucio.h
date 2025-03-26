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
    MapaSolucio() : m_graf(nullptr) {}
    ~MapaSolucio() {
        for (auto cami : m_camins) delete cami;
        for (auto pdi : m_pdis) delete pdi;
        delete m_graf;
    }

    void getPdis(std::vector<PuntDeInteresBase*>& pdis) override;
    void getCamins(std::vector<CamiBase*>& camins) override;
    void parsejaXmlElements(std::vector<XmlElement>& xmlElements) override;
    void construeixGraf();
    CamiBase* buscaCamiMesCurt(PuntDeInteresBase* from, PuntDeInteresBase* to) override;

private:
    GrafSolucio* m_graf;
    std::vector<CamiBase*> m_camins;
    std::vector<PuntDeInteresBase*> m_pdis;
};