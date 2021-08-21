#include "modele/ToutDoux.hpp"

#include <algorithm>
#include <ranges>
#include <string_view>
#include <fstream>

namespace ToutDoux
{

Projet::Projet (const std::string_view nom)
	: _nom(nom)
{}

std::vector<Element> Projet::elements() const
{
	if (_elements.empty())
	{
		chargeElements();
	}

	return _elements;
}

void Projet::chargeElements() const
{
	using namespace std::filesystem;

	const path pathProjet{Projet::pathProjetsDirectory/_nom};

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

			_elements.emplace_back(fini==1, objet);
		}
	}
}

void Projet::updateElement(const Element& element)
{
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
