#include "modele/ToutDoux.hpp"

#include <algorithm>
#include <ranges>
#include <string_view>
#include <fstream>

#include <iostream>

#include "utilities/stringOperation.hpp"

namespace ToutDoux
{

Projet::Projet (const std::string_view& nom)
	: _nom(nom)
{}

Projet::~Projet()
{
	if (_charge)
	{
		sauvegarder();
	}
}

void Projet::sauvegarder() const
{
	const std::filesystem::path pathProjet{Projet::pathProjetsDirectory/nom()};

	std::ofstream projetFile(pathProjet, std::ios::out | std::ios::trunc);

	for (const auto& elem : _elements)
	{
		projetFile<<elem.fini<<" "<<elem.objet<<'\n';
		std::cout<<elem.fini<<" "<<elem.objet<<'\n';
	}
	projetFile.close();

}

std::vector<Element> Projet::elements() const
{
	if (!_charge)
	{
		chargeElements();
	}

	return _elements;
}

void Projet::chargeElements() const
{
	using namespace std::filesystem;

	const path pathProjet{Projet::pathProjetsDirectory/nom()};

	_elements.clear();
	if (exists(pathProjet) && is_regular_file(pathProjet))
	{
		std::ifstream projetFile{pathProjet};

		while (!projetFile.eof())
		{
			std::string objet;
			short fini;
			projetFile >> fini;
			getline(projetFile, objet);
			objet = util::trim(objet);
			if (objet.empty()) break;

			_elements.emplace_back(fini==1, objet);
		}
	}

	_charge = true;
}

void Projet::updateElement(const Element& element)
{
	if (!_charge)
	{
		chargeElements();
	}

	auto itElem = std::ranges::find_if(_elements,[&](const Element& e){return element.objet == e.objet;});

	if (itElem == _elements.end())
	{
		_elements.push_back(element);
	}
	else
	{
		itElem->fini = element.fini;
	}
}


std::vector<Projet> GetAllProject()
{
	std::vector<Projet> projets;

	using namespace std::filesystem;
	if (!exists(Projet::pathProjetsDirectory) || !is_directory(Projet::pathProjetsDirectory))
	{
		create_directory(Projet::pathProjetsDirectory);
	}

    for(auto const& dir_entry: directory_iterator{Projet::pathProjetsDirectory})
	{
		if (dir_entry.is_regular_file())
		{
			projets.emplace_back(dir_entry.path().filename().string());
		}
	}

	return projets;
}
}
