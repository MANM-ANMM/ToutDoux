#include <boost/ut.hpp>
#include "modele/ToutDoux.hpp"

#include <iostream>
#include <string>

namespace Test
{
namespace td = ToutDoux;
using namespace std::string_literals;

void printElement(const td::Element& element)
{
	std::cout<<(element.status == td::StatusElement::Fini)<<" "<<element.objet<<'\n';
}

void printElements(const std::vector<td::Element>& elements)
{
	for (const td::Element& elem : elements)
	{
		printElement(elem);
	}
}

void FonctionementModele()
{
	td::Manager manager{"./projets/"s, true};

	std::vector<std::string> nomsProjets{manager.getProjectsNames()};

	for (const std::string& nomP : nomsProjets)
	{
		std::cout<<nomP<<'\n';
	}


	std::vector<td::Element> elementsProjet {manager.getProjectElements(nomsProjets[0])};
	for (const td::Element& elem : elementsProjet)
	{
		printElement(elem);
		manager.markElementAs(nomsProjets[0], elem.objet, td::StatusElement::ToDo);
	}

	elementsProjet = manager.getProjectElements(nomsProjets[0]);
	printElements(elementsProjet);

	if (std::ranges::none_of(elementsProjet, [](const ToutDoux::Element& elem){return elem.objet == "Politik kills"s;}))
	{
		manager.addElement(nomsProjets[0], "Politik kills");
	}

	elementsProjet = manager.getProjectElements(nomsProjets[0]);
	printElements(elementsProjet);

	manager.deleteElement(nomsProjets[0], "Politik kills");
	elementsProjet = manager.getProjectElements(nomsProjets[0]);
	printElements(elementsProjet);


	manager.addElement(nomsProjets[0], "Politik kills");
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

	"addAndDeleteElement"_test = []{
		ToutDoux::Manager manager{"./projets/"s};
		std::vector<std::string> nomsProjets{manager.getProjectsNames()};
		for (const std::string& nomP : nomsProjets)
		{
			std::vector<ToutDoux::Element> elementsProjet {manager.getProjectElements(nomP)};
			std::size_t tailleAvant = elementsProjet.size();
			const std::string objetElem {"|||li$$$$$$$$$$$////|||"s};

			//add
			manager.addElement(nomP, objetElem);
			elementsProjet = manager.getProjectElements(nomP);
			expect(tailleAvant+1 == elementsProjet.size());
			expect(std::ranges::any_of(elementsProjet, [&objetElem](const ToutDoux::Element& elem){return elem.objet == objetElem;}));

			//delete
			expect(nothrow([&nomP,&objetElem, &manager]{manager.deleteElement(nomP, objetElem);}));
			elementsProjet = manager.getProjectElements(nomP);
			expect(tailleAvant == elementsProjet.size());
			expect(std::ranges::none_of(elementsProjet, [&objetElem](const ToutDoux::Element& elem){return elem.objet == objetElem;}));
		}
	};

	"addAndDeleteProject"_test = []{
		ToutDoux::Manager manager {"./projets/"s};
		std::vector<std::string> nomsProjets{manager.getProjectsNames()};
		std::size_t tailleAvant = nomsProjets.size();
		const std::string nomProjet{"#######||||$$$$$##"};

		manager.addProject(nomProjet);

		nomsProjets = manager.getProjectsNames();
		expect(tailleAvant+1 == nomsProjets.size());
		expect(nothrow([&nomProjet, &manager]{manager.getProjectElements(nomProjet);}));


		//delete
		expect(nothrow([&manager, &nomProjet]{manager.deleteProject(nomProjet);}));
		nomsProjets = manager.getProjectsNames();
		expect(tailleAvant == nomsProjets.size());
		expect(std::ranges::none_of(nomsProjets, [&nomProjet](const std::string& nomP){return nomP == nomProjet;}));
	};
};


int main(int, char**)
{
	using namespace boost::ut;

	Test::FonctionementModele();


	return 0;
}
