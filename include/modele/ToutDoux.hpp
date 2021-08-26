#pragma once

#include <vector>
#include <filesystem>
#include <string_view>
#include <string>
#include <optional>
#include <stack>


namespace ToutDoux
{
enum class StatusElement : bool {
	Fini = true,
	ToDo = false
};

bool statusElementToBool(const StatusElement& status);
StatusElement statusElementFromBool(const bool status);
std::string statusElementToString(const StatusElement& status);

struct Element
{
	StatusElement status;
	std::string objet;
};


class Projet
{
public:
	Projet(const std::filesystem::path& pathProjet);

	std::string getNom() const;
	void markElementAs(const std::string_view& objetElement, const StatusElement& nouveauStatus);
	void addElement(const std::string_view& objetNouvelElement);
	void deleteElement(const std::string_view& objetElement);

	const std::vector<Element> getElements();

	void save() const;
private:
	std::vector<Element>::iterator getElement(const std::string_view& objetElement);
	void charger();

	std::filesystem::path _pathProjet;
	std::optional<std::vector<Element>> _elements;
};


struct RolebackData
{
	std::string expliquation;
	std::function<void()> roleback;
};
using namespace std::string_literals;

class Manager
{
public:
	Manager(const std::string_view& pathToProjectDirectory, const bool autoSaveActivated = false);
	~Manager();

	std::vector<std::string> getProjectsNames() const;
	const std::vector<Element> getProjectElements(const std::string_view& nomProjet);

	void markElementAs(const std::string_view& nomProjet, const std::string_view& objetElement, const StatusElement& nouveauStatus);

	void addElement(const std::string_view& nomProjet, const std::string_view& objetNouvelElement);
	void addProject(const std::string_view& nomNouveauProjet);

	void deleteProject(const std::string_view& nomProjetASupprimer);
	void deleteElement(const std::string_view& nomProjet, const std::string_view& objetElement);

	bool verifyNomNouveauProjet(const std::string_view& nom) const;
	bool verifyObjetNouvelElement(const std::string_view& nomProjet, const std::string_view& objetNouvelElement);

	void annuler();
	void annulerAnnulation();

	void save() const;
	void saveProject(const std::string_view& nomProjet) const;
private:
	std::vector<Projet>::iterator getProject(const std::string_view& nomProjet);
	std::vector<Projet>::const_iterator getProject(const std::string_view& nomProjet) const;

	template <bool forward>
	void _markElementAs(const std::string_view& nomProjet, const std::string_view& objetElement, const StatusElement& nouveauStatus)
	{
		const auto elements = getProject(nomProjet)->getElements();
		const auto it = std::ranges::find_if(elements, [&objetElement](const Element& elem){ return elem.objet == objetElement;});
		const StatusElement statusPrecedent = it->status;


		getProject(nomProjet)->markElementAs(objetElement, nouveauStatus);

		if constexpr (forward)
		{
			pileAnnulation.emplace("Annuler : marquer "s+std::string(objetElement)+" comme "s+statusElementToString(nouveauStatus), [this, nomProjet=std::string(nomProjet), statusPrecedent, objetElement=std::string(objetElement)](){
				_markElementAs<false>(nomProjet, objetElement, statusPrecedent);
			});
		}
		else
		{
			pileAnnulationAnnulation.emplace("Annuler annulation : marquer "s+std::string(objetElement)+" comme "s+statusElementToString(nouveauStatus), [this, nomProjet=std::string(nomProjet), statusPrecedent, objetElement=std::string(objetElement)](){
				_markElementAs<true>(nomProjet, objetElement, statusPrecedent);
			});
		}
	}

	template <bool forward>
	void _addElement(const std::string_view& nomProjet, const std::string_view& objetNouvelElement)
	{
		getProject(nomProjet)->addElement(objetNouvelElement);

		if constexpr (forward)
		{
			pileAnnulation.emplace("Annuler : ajouter l'élément "+std::string(objetNouvelElement), [this, nomProjet=std::string(nomProjet), objetNouvelElement=std::string(objetNouvelElement)](){
				_deleteElement<false>(nomProjet, objetNouvelElement);
			});
		}
		else
		{
			pileAnnulationAnnulation.emplace("Annuler annulation : ajouter l'élément "+std::string(objetNouvelElement), [this, nomProjet=std::string(nomProjet), objetNouvelElement=std::string(objetNouvelElement)]{
				_deleteElement<true>(nomProjet, objetNouvelElement);
			});
		}
	}

	template <bool forward>
	void _addProject(const std::string_view& nomNouveauProjet)
	{
		if (std::ranges::any_of(_projets, [&nomNouveauProjet](const Projet& projet){
			return projet.getNom() == nomNouveauProjet;}
		))
		{
			throw std::domain_error("Le nom du nouveau projet est deja pris"s);
		}
		_projets.emplace_back(_pathToProjectDirectory/nomNouveauProjet);

		if constexpr (forward)
		{
			pileAnnulation.emplace("Annuler : ajouter projet "+std::string(nomNouveauProjet), [this, nomNouveauProjet=std::string(nomNouveauProjet)]{
				_deleteProject<false>(nomNouveauProjet);
			});
		}
		else
		{
			pileAnnulationAnnulation.emplace("Annuler annulation : ajouter projet "+std::string(nomNouveauProjet), [this, nomNouveauProjet=std::string(nomNouveauProjet)]{
				_deleteProject<true>(nomNouveauProjet);
			});
		}
	}

	template <bool forward>
	void _deleteProject(const std::string_view& nomProjetASupprimer)
	{
		const std::vector<Element> elementsProjetSupprime = getProjectElements(nomProjetASupprimer);

		std::erase_if(_projets, [&nomProjetASupprimer](const Projet& projet){
			return projet.getNom() == nomProjetASupprimer;
		});

		_nomsProjetsSupprimer.emplace_back(nomProjetASupprimer);

		if constexpr (forward)
		{
			pileAnnulation.emplace("Annuler : suppression projet "+std::string(nomProjetASupprimer),[this, nomProjetASupprimer=std::string(nomProjetASupprimer), elementsProjetSupprime]{
				_projets.emplace_back(_pathToProjectDirectory/nomProjetASupprimer);
				for (const Element& e : elementsProjetSupprime)
				{
					_projets.back().addElement(e.objet);
					_projets.back().markElementAs(e.objet, e.status);
				}
				std::erase_if(_nomsProjetsSupprimer, [&nomProjetASupprimer](const std::string& nom){
					return nomProjetASupprimer == nom;
				});
				pileAnnulationAnnulation.emplace("Annuler annulation : suppression projet "+std::string(nomProjetASupprimer), [this, nomProjetASupprimer]{
					_deleteProject<true>(nomProjetASupprimer);
				});
			});
		}
		else
		{
			pileAnnulationAnnulation.emplace("Annuler annulation : suppression projet "+std::string(nomProjetASupprimer),[this, nomProjetASupprimer=std::string(nomProjetASupprimer), elementsProjetSupprime]{
				_projets.emplace_back(_pathToProjectDirectory/nomProjetASupprimer);
				for (const Element& e : elementsProjetSupprime)
				{
					_projets.back().addElement(e.objet);
					_projets.back().markElementAs(e.objet, e.status);
				}
				pileAnnulation.emplace("Annuler : suppression projet "+std::string(nomProjetASupprimer), [this, nomProjetASupprimer]{
					_deleteProject<false>(nomProjetASupprimer);
				});
			});
		}
	}

	template <bool forward>
	void _deleteElement(const std::string_view& nomProjet, const std::string_view& objetElement)
	{
		const auto elements = getProject(nomProjet)->getElements();
		const auto it = std::ranges::find_if(elements, [&objetElement](const Element& elem){ return elem.objet == objetElement;});
		const StatusElement statusPrecedent = it->status;

		getProject(nomProjet)->deleteElement(objetElement);

		if constexpr (forward)
		{
			pileAnnulation.emplace("Annuler : suppresion élément "+std::string(objetElement), [this, nomProjet=std::string(nomProjet), statusPrecedent, objetElement=std::string(objetElement)]{
				getProject(nomProjet)->addElement(objetElement);
				getProject(nomProjet)->markElementAs(objetElement, statusPrecedent);

				pileAnnulationAnnulation.emplace("Annuler annulation : suppression élément" + std::string(objetElement), [this, nomProjet, objetElement]{
					_deleteElement<true>(nomProjet, objetElement);
				});
			});
		}
		else
		{
			pileAnnulationAnnulation.emplace("Annuler annulation : suppresion élément "+std::string(objetElement), [this, nomProjet=std::string(nomProjet), statusPrecedent, objetElement=std::string(objetElement)]{
				getProject(nomProjet)->addElement(objetElement);
				getProject(nomProjet)->markElementAs(objetElement, statusPrecedent);

				pileAnnulation.emplace("Annuler : suppression élément" + std::string(objetElement), [this, nomProjet, objetElement]{
					_deleteElement<false>(nomProjet, objetElement);
				});
			});
		}
	}


	std::filesystem::path _pathToProjectDirectory;

	std::vector<Projet> _projets;
	mutable std::vector<std::string> _nomsProjetsSupprimer;

	std::stack<RolebackData> pileAnnulation;
	std::stack<RolebackData> pileAnnulationAnnulation;

	bool _autoSaveActivated;
};








}
