#include <boost/ut.hpp>
#include "modele/ToutDoux.hpp"

#include <iostream>

int main()
{
	using namespace boost::ut;

	auto ps = ToutDoux::GetAllProject();

	for (const auto& p : ps)
	{
		expect(!p.nom().empty())<<" un nom de projet est vide";

		for (const auto& elem : p.elements())
		{
			expect(!elem.objet.empty());
		}
	}
}
