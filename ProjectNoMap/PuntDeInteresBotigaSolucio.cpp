#include "pch.h"
#include "PuntDeInteresBotigaSolucio.h"


PuntDeInteresBotigaSolucio::PuntDeInteresBotigaSolucio(Coordinate coord, std::string name, std::string openingHours,
	std::string wheelchair, std::string shop) : PuntDeInteresBase(coord, name)
{
	m_openingHours = openingHours;
	m_shop = shop;
	m_wheelchair = wheelchair;
}

std::string PuntDeInteresBotigaSolucio::getName()
{
	return PuntDeInteresBase::getName();
}

unsigned int PuntDeInteresBotigaSolucio::getColor()
{
	if (m_shop == "supermarket")
		return 0xA5BE00;
	
	if (m_shop == "tobacco")
		return 0xFFAD69;
	
	if (m_shop == "bakery")
	{
		if (m_openingHours.find("06:00-22:00") != std::string::npos and m_wheelchair == "yes")
			return 0x4CB944;
		else
			return 0xE85D75;
	}
	
	return 0xEFD6AC;
}

