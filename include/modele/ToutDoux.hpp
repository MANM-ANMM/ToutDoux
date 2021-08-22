#pragma once

#include <vector>
#include <filesystem>
#include <string_view>
#include <string>
#include <optional>


namespace ToutDoux
{
enum class StatusElement : bool {
	Fini = true,
	ToDo = false
};




struct Element
{
	StatusElement status;
	std::string objet;
};

class Projet
{
public:
	Projet(const std::filesystem::path& pathProjet);
	/*Projet(const Projet& projet);
	Projet& operator=(const ToutDoux::Projet& projet);
	Projet(Projet&& projet);
	Projet& operator=(Projet&& projet);*/

	std::string getNom() const;
	void markElementAs(const std::string_view& objetElement, const StatusElement& nouveauStatus);
	void addElement(const std::string_view& objetNouvelElement);
	void deleteElement(const std::string_view& objetElement);

	const std::vector<Element> getElements();
private:
	std::vector<Element>::iterator getElement(const std::string_view& objetElement);
	void charger();

	std::filesystem::path _pathProjet;
	std::optional<std::vector<Element>> _elements;
};


class Manager
{
public:
	Manager(const std::string_view& pathToProjectDirectory);

	std::vector<std::string> getProjectsNames() const;
	const std::vector<Element> getProjectElements(const std::string_view& nomProjet);

	void markElementAs(const std::string_view& nomProjet, const std::string_view& objetElement, const StatusElement& nouveauStatus);

	void addElement(const std::string_view& nomProjet, const std::string_view& objetNouvelElement);
	void addProject(const std::string_view& nomNouveauProjet);

	void deleteProject(const std::string_view& nomProjetASupprimer);
	void deleteElement(const std::string_view& nomProjet, const std::string_view& objetElement);
private:
	std::vector<Projet>::iterator getProject(const std::string_view& nomProjet);
	std::vector<Projet>::const_iterator getProject(const std::string_view& nomProjet) const;


	std::filesystem::path _pathToProjectDirectory;

	std::vector<Projet> _projets;
};








}
