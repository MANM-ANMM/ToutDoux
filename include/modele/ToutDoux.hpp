/**
 *\file ToutDoux.hpp
 *\brief Le modèle du projet ToutDoux
 *\author Martin Rouault
 */

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

/**
 \brief Convertie un StatusElement en bool
 \param [in] status Le status a convertir
 \return true si status == Fini, false sinon
 */
bool statusElementToBool(const StatusElement& status);

/**
 \brief Convertie un bool en StatusElement
 \param [in] status Le boolean à convertir
 \return Fini si status == true, ToDo sinon
 */
StatusElement statusElementFromBool(const bool status);

/**
  \brief Convertie un StatusElement en string
  \param [in] status le status a convertir
  \return "fini" ou "à faire"
  */
std::string statusElementToString(const StatusElement& status);

struct Element
{
	StatusElement status;
	std::string objet;
};


class Projet
{
public:
	/**
	 \brief Construit un projet
	 \param [in] pathProjet Le chemin du projet
	 */
	Projet(const std::filesystem::path& pathProjet);

	/**
	 \brief Rend le nom du projet
	 \return Le nom du projet
	 */
	std::string getNom() const;

	/**
	 \brief Marque un élément comme étant Fini ou A faire
	 \param [in] objetElement L'objet de l'élément
	 \param [in] nouveauStatus Le nouveau status à donner
	 */
	void markElementAs(const std::string_view& objetElement, const StatusElement& nouveauStatus);
	/**
	 \brief Ajoute un nouvel élément à faire
	 \param [in] objetNouvelElement L'objet du nouvel élément
	 */
	void addElement(const std::string_view& objetNouvelElement);
	/**
	 \brief Supprime un élément
	 \param [in] objetElement L'objet de l'élément à supprimer
	 */
	void deleteElement(const std::string_view& objetElement);

	/**
	 \brief Rend les éléments du projet
	 \return Les éléments du projet
	 */
	const std::vector<Element> getElements();

	/**
	 \brief Sauvegarde le projet
	 */
	void save() const;
private:
	std::vector<Element>::iterator getElement(const std::string_view& objetElement);
	void charger();

	std::filesystem::path _pathProjet;
	std::optional<std::vector<Element>> _elements;
};

class Manager
{
public:
	/**
	 \brief Construit un nouveau Manager
	 \param [in] pathToProjectDirectory Le repertoire dans lequel le manager gère les projets
	 \param [in] autoSaveActivated Si activé, le manager sauvegarde les projets à sa destruction
	 */
	Manager(const std::string_view& pathToProjectDirectory, const bool autoSaveActivated = false);
	~Manager();

	/**
	 \brief Rends les noms des projets
	 \return Les noms des projets
	 */
	std::vector<std::string> getProjectsNames() const;

	/**
	 \brief Rends les éléments d'un projet donné
	 \param [in] nomProjet Le projet duquel les éléments sont retourné
	 \return Les éléments du projet
	 */
	const std::vector<Element> getProjectElements(const std::string_view& nomProjet);
	/**
	 \brief Indique si un projet existe
	 \param [in] nomProjet Le nom de projet à tester
	 \return true si le projet existe, false sinon
	 */
	bool projetExiste(const std::string_view& nomProjet) const;

	/**
	 \brief Marque un élément d'un projet comme étant Fini ou A faire
	 \param [in] nomProjet Le projet contenant l'élément en question
	 \param [in] objetElement L'objet de l'élément
	 \param [in] nouveauStatus Le nouveau status à donner
	 */
	void markElementAs(const std::string_view& nomProjet, const std::string_view& objetElement, const StatusElement& nouveauStatus);

	/**
	 \brief Ajoute un élément à un projet
	 \param [in] nomProjet Le nom du projet en question
	 \param [in] objetNouvelElement L'objet du nouvel élément
	 */
	void addElement(const std::string_view& nomProjet, const std::string_view& objetNouvelElement);
	/**
	 \brief Créer un nouveau projet
	 \param [in] nomNouveauProjet Le nom du nouveau projet
	 */
	void addProject(const std::string_view& nomNouveauProjet);

	/**
	 \brief Suppprime un projet
	 \param [in] nomProjetASupprimer Le nom du projet à supprimer
	 */
	void deleteProject(const std::string_view& nomProjetASupprimer);
	/**
	 \brief Supprime un élément d'un projet
	 \param [in] nomProjet Le nom du projet en question
	 \param [in] objetElement L'objet de l'élément à supprimer
	 */
	void deleteElement(const std::string_view& nomProjet, const std::string_view& objetElement);

	/**
	 \brief Verifie la validité d'un nom de projet
	 \param [in] nom Le nom à tester
	 \return true si le nom est valide, false sinon
	 */
	bool verifyNomNouveauProjet(const std::string_view& nom) const;
	/**
	 \brief Verifie la validité d'un objet pour un nouvel élément d'un projet
	 \param [in] nomProjet Le nom du projet en question
	 \param [in] objetNouvelElement L'objet à tester
	 \return true si l'objet est valide, false sinon
	 */
	bool verifyObjetNouvelElement(const std::string_view& nomProjet, const std::string_view& objetNouvelElement);

	/**
	 \brief Sauvegarde les projets
	 */
	void save() const;

	/**
	 \brief Sauvegarde un projet
	 */
	void saveProject(const std::string_view& nomProjet) const;
private:
	std::vector<Projet>::iterator getProject(const std::string_view& nomProjet);
	std::vector<Projet>::const_iterator getProject(const std::string_view& nomProjet) const;

	std::filesystem::path _pathToProjectDirectory;

	std::vector<Projet> _projets;
	mutable std::vector<std::string> _nomsProjetsSupprimer;

	bool _autoSaveActivated;
};








}
