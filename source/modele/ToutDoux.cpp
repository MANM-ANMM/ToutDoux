#include "modele/ToutDoux.hpp"

#include <algorithm>
#include <ranges>
#include <string_view>
#include <fstream>
#include <stdexcept>

#include <iostream>

#include "utilities/stringOperation.hpp"

namespace ToutDoux
{
using namespace std::string_literals;

Manager::Manager(const std::string_view& pathToProjectDirectory, const bool autoSaveActivated)
	:_pathToProjectDirectory(pathToProjectDirectory),
	_autoSaveActivated(autoSaveActivated)
{
	//check if project's directory exists and create it if it doesn't
	using namespace std::filesystem;
	if (!exists(_pathToProjectDirectory) || !is_directory(_pathToProjectDirectory))
	{
		create_directory(_pathToProjectDirectory);
	}

	//populate _projets
	for(auto const& dir_entry: std::filesystem::directory_iterator{_pathToProjectDirectory})
	{
		if (dir_entry.is_regular_file())
		{
			_projets.emplace_back(dir_entry.path());
		}
	}
}

Manager::~Manager()
{
	if (_autoSaveActivated)
	{
		save();
	}
}

std::vector<std::string> Manager::getProjectsNames() const
{
	std::vector<std::string> nomsProjets(_projets.size());
	std::ranges::transform(_projets, nomsProjets.begin(), [](const Projet& projet){return projet.getNom();});
	return nomsProjets;
}

const std::vector<Element> Manager::getProjectElements(const std::string_view& nomProjet)
{
	return getProject(nomProjet)->getElements();
}

void Manager::markElementAs(const std::string_view& nomProjet, const std::string_view& objetElement, const StatusElement& nouveauStatus)
{
	getProject(nomProjet)->markElementAs(objetElement, nouveauStatus);
}

void Manager::addElement(const std::string_view& nomProjet, const std::string_view& objetNouvelElement)
{
	getProject(nomProjet)->addElement(objetNouvelElement);
}


void Manager::addProject(const std::string_view& nomNouveauProjet)
{
	if (std::ranges::any_of(_projets, [&nomNouveauProjet](const Projet& projet){
		return projet.getNom() == nomNouveauProjet;}
	))
	{
		throw std::domain_error("Le nom du nouveau projet est deja pris"s);
	}
	_projets.emplace_back(_pathToProjectDirectory/nomNouveauProjet);
}

void Manager::deleteProject(const std::string_view& nomProjetASupprimer)
{
	std::erase_if(_projets, [&nomProjetASupprimer](const Projet& projet){
		return projet.getNom() == nomProjetASupprimer;
	});

	_nomsProjetsSupprimer.emplace_back(nomProjetASupprimer);
}

void Manager::deleteElement(const std::string_view& nomProjet, const std::string_view& objetElement)
{
	getProject(nomProjet)->deleteElement(objetElement);
}

void Manager::save() const
{
	std::ranges::for_each(_projets, [](const Projet& projet){projet.save();});

	std::ranges::for_each(_nomsProjetsSupprimer, [this](const std::string& nomProjetASupprimer){
		std::cout<<std::filesystem::remove(std::filesystem::path(_pathToProjectDirectory/nomProjetASupprimer));
	});

	_nomsProjetsSupprimer.clear();
}

void Manager::saveProject(const std::string_view& nomProjet) const
{
	getProject(nomProjet)->save();
}

std::vector<Projet>::const_iterator Manager::getProject(const std::string_view& nomProjet) const
{
	std::vector<Projet>::const_iterator itProjet = std::ranges::find_if(_projets, [&nomProjet](const Projet& projet){
		return projet.getNom() == nomProjet;
	});

	if (itProjet == _projets.end())
	{
		throw std::domain_error("Le nom du projet specifié ne correspond à aucun projet"s);
	}

	return itProjet;
}

std::vector<Projet>::iterator Manager::getProject(const std::string_view& nomProjet)
{
	std::vector<Projet>::iterator itProjet = std::ranges::find_if(_projets, [&nomProjet](const Projet& projet){
		return projet.getNom() == nomProjet;
	});

	if (itProjet == _projets.end())
	{
		throw std::domain_error("Le nom du projet specifié ne correspond à aucun projet"s);
	}

	return itProjet;
}







Projet::Projet (const std::filesystem::path& pathProjet)
	: _pathProjet(pathProjet)
{
}

std::string Projet::getNom() const
{
	return _pathProjet.filename().string();
}

void Projet::markElementAs(const std::string_view& objetElement, const StatusElement& nouveauStatus)
{
	if (!_elements)
	{
		charger();
	}
	getElement(objetElement)->status = nouveauStatus;
}

void Projet::addElement(const std::string_view& objetNouvelElement)
{
	if (!_elements)
	{
		charger();
	}

	if (std::ranges::any_of(*_elements, [&objetNouvelElement](const Element& element){
		return element.objet == objetNouvelElement;}
	))
	{
		throw std::domain_error("Un element de ce nom existe déjà"s);
	}

	_elements->emplace_back(StatusElement::ToDo, std::string(objetNouvelElement));
}

void Projet::deleteElement(const std::string_view& objetElement)
{
	if (!_elements)
	{
		charger();
	}

	_elements->erase(getElement(objetElement));
}

const std::vector<Element> Projet::getElements()
{
	if (!_elements)
	{
		charger();
	}

	return *_elements;
}


std::vector<Element>::iterator Projet::getElement(const std::string_view& objetElement)
{
	std::vector<Element>::iterator itProjet = std::ranges::find_if(*_elements, [&objetElement](const Element& element){
		return element.objet == objetElement;
	});

	if (itProjet == _elements->end())
	{
		throw std::domain_error("L'objet specifié ne correspond à aucun element"s);
	}

	return itProjet;
}



void Projet::charger()
{
	using namespace std::filesystem;

	_elements = std::vector<Element>();

	if (exists(_pathProjet) && is_regular_file(_pathProjet))
	{
		std::ifstream projetFile{_pathProjet};

		while (!projetFile.eof())
		{
			std::string objet;
			short fini;
			projetFile >> fini;
			getline(projetFile, objet);
			objet = util::trim(objet);
			if (objet.empty()) break;

			if (std::ranges::none_of(*_elements, [&objet](const Element& element){
				return element.objet == objet;
			}))
			{
				_elements->emplace_back(StatusElement{fini==1}, objet);
			}
		}
	}

}

void Projet::save() const
{
	if (!_elements) return;

	std::ofstream projetFile(_pathProjet, std::ios::out | std::ios::trunc);

	for (const auto& elem : *_elements)
	{
		projetFile<<(elem.status == StatusElement::Fini)<<" "<<elem.objet<<'\n';
	}
	projetFile.close();
}
}
