#pragma once

#include "PuntDeInteresBase.h"

class PuntDeInteresRestaurantSolucio : public PuntDeInteresBase
{
public:
	PuntDeInteresRestaurantSolucio() : m_wheelchair(""), m_cocina(""), m_tipo("") {}
	PuntDeInteresRestaurantSolucio(Coordinate coord, std::string name,
		std::string wheelchair, std::string cocina, std::string tipo);

	std::string getName();
	unsigned int getColor();

private:
	std::string m_wheelchair;
	std::string m_cocina;
	std::string m_tipo;
};