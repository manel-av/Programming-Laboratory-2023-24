#include "pch.h"
#include "MapaSolucio.h"

void MapaSolucio::construeixGraf() {
    if (!m_camins.empty()) {
        m_graf = new GrafSolucio();
    }
}

void MapaSolucio::getPdis(std::vector<PuntDeInteresBase*>& pdis)
{
    std::vector<PuntDeInteresBase*>::iterator puntos = m_pdis.begin();
    while (puntos != m_pdis.end())
    {
        pdis.push_back(*puntos);
        puntos++;
    }
}

void MapaSolucio::getCamins(std::vector<CamiBase*>& camins)
{
    std::vector<CamiBase*>::iterator camino = m_camins.begin();
    while (camino != m_camins.end())
    {
        camins.push_back(*camino);
        camino++;
    }
}

void MapaSolucio::parsejaXmlElements(std::vector<XmlElement>& xmlElements)
{
    // Vaciar los vectores de la clase MapaSolucio
    if (!m_camins.empty())
    {
        m_camins.clear();
    }
    if (!m_pdis.empty())
    {
        m_pdis.clear();
    }

    std::vector<std::pair<std::string, Coordinate>> refNodos;
    for (std::vector<XmlElement>::iterator itXml = xmlElements.begin(); itXml != xmlElements.end(); itXml++)
    {
        double latitud = 0, longitud = 0;
        if ((*itXml).id_element == "node")
        {
            // Bucle para saber si es una tienda o un restaurante
            std::string establecimiento = "";
            for (int i = 0; i < (*itXml).fills.size(); i++)
            {
                if ((*itXml).fills[i].first == "tag")
                {
                    std::pair<std::string, std::string> valorTag = Util::kvDeTag((*itXml).fills[i].second);
                    if (valorTag.second == "restaurant")
                    {
                        establecimiento = "amenity";
                    }
                    else
                        if (valorTag.first == "shop")
                        {
                            establecimiento = "shop";
                        }
                        else 
                            if (valorTag.first == "amenity")
                            {
                                establecimiento = "base";
                            }
                }
            }
            
            if (establecimiento == "amenity") // si es un restaurante
            {
                PuntDeInteresRestaurantSolucio* pRest;
                pRest = new PuntDeInteresRestaurantSolucio;
                Coordinate coord;
                std::string name;
                std::string cocina;
                std::string wheelchair;
                std::string restaurant;

                // guardar coordenadas
                for (int i = 0; i < (*itXml).atributs.size(); i++)
                {
                    if ((*itXml).atributs[i].first == "lat")
                    {
                        latitud = stod((*itXml).atributs[i].second);
                    }
                    if ((*itXml).atributs[i].first == "lon")
                    {
                        longitud = stod((*itXml).atributs[i].second);
                    }
                    coord.lat = latitud;
                    coord.lon = longitud;
                }
                // guardar los atributos del punto de interés
                for (int i = 0; i < (*itXml).fills.size(); i++)
                {
                    if ((*itXml).fills[i].first == "tag")
                    {
                        std::pair<std::string, std::string> valorTag = Util::kvDeTag((*itXml).fills[i].second);
                        if (valorTag.first == "name")
                        {
                            name = valorTag.second;
                        }
                        else
                            if (valorTag.first == "amenity")
                            {
                                restaurant = valorTag.second;
                            }
                            else
                                if (valorTag.first == "cuisine")
                                {
                                    cocina = valorTag.second;
                                }
                                else
                                    if (valorTag.first == "wheelchair")
                                    {
                                        wheelchair = valorTag.second;
                                    }
                    }
                }
                if (name != "")
                {
                    pRest = new PuntDeInteresRestaurantSolucio(coord, name, wheelchair, cocina, restaurant);
                    m_pdis.push_back(pRest);
                }
            }
            else
                if (establecimiento == "shop") // si es una tienda
                {
                    PuntDeInteresBotigaSolucio* pShop;
                    pShop = new PuntDeInteresBotigaSolucio;
                    bool isNode = false;
                    Coordinate coord;
                    std::string name;
                    std::string shop;
                    std::string wheelchair;
                    std::string horario;

                    // guardar coordenadas
                    for (int i = 0; i < (*itXml).atributs.size(); i++)
                    {
                        if ((*itXml).atributs[i].first == "lat")
                        {
                            latitud = stod((*itXml).atributs[i].second);
                        }
                        if ((*itXml).atributs[i].first == "lon")
                        {
                            longitud = stod((*itXml).atributs[i].second);
                        }
                        coord.lat = latitud;
                        coord.lon = longitud;
                    }
                    // guardar los atributos del punto de interés
                    for (int i = 0; i < (*itXml).fills.size(); i++)
                    {
                        if ((*itXml).fills[i].first == "tag")
                        {
                            isNode = true;
                            std::pair<std::string, std::string> valorTag = Util::kvDeTag((*itXml).fills[i].second);
                            if (valorTag.first == "name")
                            {
                                name = valorTag.second;
                            }
                            else
                                if (valorTag.first == "shop")
                                {
                                    shop = valorTag.second;
                                }
                                else
                                    if (valorTag.first == "wheelchair")
                                    {
                                        wheelchair = valorTag.second;
                                    }
                                    else
                                        if (valorTag.first == "opening_hours")
                                        {
                                            horario = valorTag.second;
                                        }
                        }
                    }
                    if (isNode) // condición para saber si un nodo 
                    {
                        if (name != "")
                        {
                            pShop = new PuntDeInteresBotigaSolucio({ latitud, longitud }, name, horario, wheelchair, shop);
                            m_pdis.push_back(pShop);
                        }
                    }
                }
                else
                    if (establecimiento == "base") // es un punto de interes pero no es ni tienda ni restaurante
                    {
                        PuntDeInteresBase* pBase;
                        Coordinate coord;
                        std::string name;
                        
                        for (int i = 0; i < (*itXml).atributs.size(); i++)
                        {
                            // guardar coordenadas
                            if ((*itXml).atributs[i].first == "lat")
                            {
                                latitud = stod((*itXml).atributs[i].second);
                            }
                            if ((*itXml).atributs[i].first == "lon")
                            {
                                longitud = stod((*itXml).atributs[i].second);
                            }
                            coord.lat = latitud;
                            coord.lon = longitud;
                        }
                        // guardar nombre del punto de interes
                        for (int i = 0; i < (*itXml).fills.size(); i++)
                        {
                            if ((*itXml).fills[i].first == "tag")
                            {
                                std::pair<std::string, std::string> valorTag = Util::kvDeTag((*itXml).fills[i].second);
                                
                                if (valorTag.first == "name")
                                {
                                    name = valorTag.second;
                                }
                            }

                        }
                        if (name != "") {
                            pBase = new PuntDeInteresBase(coord, name);
                            m_pdis.push_back(pBase);
                        }
                    }
                    else // no es un punto de interés, es un nodo de camino
                    {
                        Coordinate coord;
                        std::string id;

                        // guardar coordenadas
                        for (int i = 0; i < (*itXml).atributs.size(); i++)
                        {
                            if ((*itXml).atributs[i].first == "id")
                            {
                                id = (*itXml).atributs[i].second;
                            }
                            if ((*itXml).atributs[i].first == "lat")
                            {
                                latitud = stod((*itXml).atributs[i].second);
                            }
                            if ((*itXml).atributs[i].first == "lon")
                            {
                                longitud = stod((*itXml).atributs[i].second);
                            }
                            coord.lat = latitud;
                            coord.lon = longitud;
                        }
                        // Busqueda para saber si el nodo del camino ya esta dentro del vector de referencias
                        bool isIn = false;
                        for (std::vector<std::pair<std::string, Coordinate>>::iterator it = refNodos.begin(); it != refNodos.end(); it++)
                        {
                            if ((*it).first == id)
                            {
                                isIn = true;
                            }
                        }
                        if (!isIn) // si no esta lo añade
                        {
                            std::pair<std::string, Coordinate> ref;
                            ref.first = id;
                            ref.second = coord;
                            refNodos.push_back(ref);
                        }
                    }
        }
        bool isHighway = false;
        if ((*itXml).id_element == "way")
        {
            CamiSolucio* cami;
            cami = new CamiSolucio;
            std::vector<Coordinate> resultat;
            for (int i = 0; i < (*itXml).fills.size(); i++)
            {
                if ((*itXml).fills[i].first == "nd") // si es nd se busca el nodo en el vector de referencias
                {
                    for (std::vector<std::pair<std::string, Coordinate>>::iterator it = refNodos.begin(); it != refNodos.end(); it++)
                    {
                        if ((*itXml).fills[i].second[0].second == (*it).first) // si se encuentra se pone en el camino resultante
                        {
                            resultat.push_back((*it).second);
                        }
                    }
                }
                if ((*itXml).fills[i].first == "tag") // se comprueba si es highway o no
                {
                    std::pair<std::string, std::string> valorTag = Util::kvDeTag((*itXml).fills[i].second);
                    if (valorTag.first == "highway")
                    {
                        cami->setWay(valorTag.second);
                        isHighway = true;
                    }
                }
            }
            if (isHighway) // si es highway se guarda el camino
            {
                cami->setCoords(resultat);
                m_camins.push_back(cami);
            }
        }
    }
}

CamiBase* MapaSolucio::buscaCamiMesCurt(PuntDeInteresBase* from, PuntDeInteresBase* to) {
    Coordinate nodeFrom, nodeTo;
    std::vector<Coordinate> datapoints;

    // Recoger todos los nodos de camino únicos
    for (auto it = m_camins.begin(); it != m_camins.end(); it++) {
        std::vector<Coordinate> cami = (*it)->getCamiCoords();
        for (auto ite = cami.begin(); ite != cami.end(); ite++) {
            if (!GrafSolucio::cercaCoords(datapoints, (*ite))) {
                datapoints.push_back(*ite);
            }
        }
    }

    // Construir BallTree para encontrar nodos más cercanos
    BallTree* bt = new BallTree();
    bt->construirArbre(datapoints);

    nodeFrom = bt->nodeMesProper(from->getCoord(), nodeFrom, bt);
    nodeTo = bt->nodeMesProper(to->getCoord(), nodeTo, bt);

    // Construir grafo con las conexiones
    GrafSolucio graf;
    for (const auto& coord : datapoints) {
        graf.afegeixNode(coord);
    }

    for (auto cami : m_camins) {
        std::vector<Coordinate> coords = cami->getCamiCoords();
        for (size_t i = 0; i < coords.size() - 1; i++) {
            graf.afegeixAresta(coords[i], coords[i + 1]);
        }
    }

    // Calcular camino más corto
    Util::escriuEnMonitor("Calculant ruta més curta...");
    CamiBase* camiMesCurt = new CamiSolucio();
    graf.camiMesCurt(nodeFrom, nodeTo, camiMesCurt);

    if (camiMesCurt->getCamiCoords().empty()) {
        Util::escriuEnMonitor("No s'ha trobat cap ruta");
        delete camiMesCurt;
        return nullptr;
    }

    Util::escriuEnMonitor("Ruta més curta calculada correctament");
    return camiMesCurt;
}