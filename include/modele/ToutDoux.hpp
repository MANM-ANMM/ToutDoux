#pragma once

#include <vector>
#include <filesystem>
#include <string_view>
#include <string>


namespace ToutDoux
{

struct Element
{
	bool fini;
	std::string objet;
};

class Projet
{
public:
	Projet (const std::string_view& nom);
	~Projet ();

	inline std::string nom() const
	{
		return _nom;
	}
	void sauvegarder() const;
	std::vector<Element> elements() const;

	void updateElement(const Element& element);

	inline static const std::filesystem::path pathProjetsDirectory{"./projets/"};
private:
	void chargeElements() const;
	const std::string _nom;
	mutable std::vector<Element> _elements;
	mutable bool _charge = false;
};

std::vector<Projet> GetAllProject();
}
