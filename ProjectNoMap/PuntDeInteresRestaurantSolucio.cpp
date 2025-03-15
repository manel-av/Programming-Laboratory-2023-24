#include "pch.h"
#include "PuntDeInteresRestaurantSolucio.h"

PuntDeInteresRestaurantSolucio::PuntDeInteresRestaurantSolucio(Coordinate coord, std::string name,
	std::string wheelchair, std::string cocina, std::string tipo) : PuntDeInteresBase(coord, name)
{
	m_wheelchair = wheelchair;
	m_cocina = cocina;
	m_tipo = tipo;
}


std::string PuntDeInteresRestaurantSolucio::getName()
{
	return PuntDeInteresBase::getName();
}

unsigned int PuntDeInteresRestaurantSolucio::getColor()
{
	if (m_cocina == "pizza" and m_wheelchair == "yes")
		return 0x03FCBA;
	
	if (m_cocina == "chinese")
		return 0xA6D9F7;
	
	if (m_wheelchair == "yes" and m_cocina != "")
		return 0x251351;
	
	return PuntDeInteresBase::getColor();
}