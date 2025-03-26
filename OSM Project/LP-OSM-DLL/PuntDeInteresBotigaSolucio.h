#pragma once

#include "PuntDeInteresBase.h"

class PuntDeInteresBotigaSolucio : public PuntDeInteresBase
{
public:
	PuntDeInteresBotigaSolucio() : m_openingHours(""), m_shop(""), m_wheelchair("") {}
	PuntDeInteresBotigaSolucio(Coordinate coord, std::string name, std::string openingHours,
		std::string wheelchair, std::string shop);

	std::string getName();
	unsigned int getColor();

private:
	std::string m_openingHours;
	std::string m_wheelchair;
	std::string m_shop;
};