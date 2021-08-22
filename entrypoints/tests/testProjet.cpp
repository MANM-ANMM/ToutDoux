#include <boost/ut.hpp>
#include "modele/ToutDoux.hpp"

#include <iostream>
#include <string>

namespace Test
{
namespace td = ToutDoux;
using namespace std::string_literals;


void FonctionementModele()
{
	td::Manager manager{"./projets/"s};

	std::vector<std::string> nomsProjets{manager.getProjectsNames()};

	for (const std::string& nomP : nomsProjets)
	{
		std::cout<<nomP<<'\n';
	}


	std::vector<td::Element> elementsProjet {manager.getProjectElements(nomsProjets[0])};

	for (const td::Element& elem : elementsProjet)
	{
		std::cout<<(elem.status == td::StatusElement::Fini)<<" "<<elem.objet<<'\n';
		manager.markElementAs(nomsProjets[0], elem.objet, td::StatusElement::Fini);
	}

	elementsProjet = manager.getProjectElements(nomsProjets[0]);
	for (const td::Element& elem : elementsProjet)
	{
		std::cout<<(elem.status == td::StatusElement::Fini)<<" "<<elem.objet<<'\n';
	}
}
}

boost::ut::suite tests = []
{
	using namespace boost::ut;
	using namespace std::string_literals;

	"nomProjetsValide"_test = []{
		ToutDoux::Manager manager{"./projets/"s};
		std::vector<std::string> nomsProjets{manager.getProjectsNames()};
		for (const std::string& nomP : nomsProjets)
		{
			expect(nothrow([&]{manager.getProjectElements(nomP);}));
		}
	};

	"setElemsToFini"_test = []{
		ToutDoux::Manager manager{"./projets/"s};
		std::vector<std::string> nomsProjets{manager.getProjectsNames()};
		for (const std::string& nomP : nomsProjets)
		{
			std::vector<ToutDoux::Element> elementsProjet {manager.getProjectElements(nomP)};

			for (const auto& e : elementsProjet)
			{
				manager.markElementAs(nomP, e.objet, ToutDoux::StatusElement::Fini);
			}

			elementsProjet = manager.getProjectElements(nomP);

			for (const auto& e : elementsProjet)
			{
				expect(e.status == ToutDoux::StatusElement::Fini);
			}
		}
	};

	"setElemsToToDo"_test = []{
		ToutDoux::Manager manager{"./projets/"s};
		std::vector<std::string> nomsProjets{manager.getProjectsNames()};
		for (const std::string& nomP : nomsProjets)
		{
			std::vector<ToutDoux::Element> elementsProjet {manager.getProjectElements(nomP)};

			for (const auto& e : elementsProjet)
			{
				manager.markElementAs(nomP, e.objet, ToutDoux::StatusElement::ToDo);
			}

			elementsProjet = manager.getProjectElements(nomP);

			for (const auto& e : elementsProjet)
			{
				expect(e.status == ToutDoux::StatusElement::ToDo);
			}
		}
	};
};


int main(int, char**)
{
	using namespace boost::ut;

	//Test::FonctionementModele();


	return 0;
}
