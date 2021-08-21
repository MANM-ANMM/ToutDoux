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

	inline std::string nom() const
	{
		return _nom;
	}

	std::vector<Element> elements() const;

	void updateElement(const Element& element);

	inline static const std::filesystem::path pathProjetsDirectory{"./projets/"};
private:
	void chargeElements() const;
	const std::string _nom;
	mutable std::vector<Element> _elements;
};

std::vector<Projet> GetAllProject();
}
