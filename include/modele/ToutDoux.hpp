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

class Manager
{
public:
	Manager(const std::string_view& pathToProjectDirectory, const bool autoSaveActivated = false);
	~Manager();

	std::vector<std::string> getProjectsNames() const;
	const std::vector<Element> getProjectElements(const std::string_view& nomProjet);
	bool projetExiste(const std::string_view& nomProjet) const;

	void markElementAs(const std::string_view& nomProjet, const std::string_view& objetElement, const StatusElement& nouveauStatus);

	void addElement(const std::string_view& nomProjet, const std::string_view& objetNouvelElement);
	void addProject(const std::string_view& nomNouveauProjet);

	void deleteProject(const std::string_view& nomProjetASupprimer);
	void deleteElement(const std::string_view& nomProjet, const std::string_view& objetElement);

	bool verifyNomNouveauProjet(const std::string_view& nom) const;
	bool verifyObjetNouvelElement(const std::string_view& nomProjet, const std::string_view& objetNouvelElement);

	void save() const;
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
