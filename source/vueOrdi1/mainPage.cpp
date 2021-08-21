#include "vueOrdi1/mainPage.hpp"


#include <string>
#include <iostream>



namespace vueOrdi1
{
using namespace nana;
using namespace std::string_literals;
	MainPage::MainPage()
	:	fenetre(),
		titreProjet(fenetre, "Titre"s),
		elementsPanel(fenetre, 1000),
		projetsPanel(fenetre,500)
	{
		SetUp();
	}

	void MainPage::ShowProjet(const std::string_view& name)
	{
		auto projet = getProjet(name);
		if (projet == nullptr) return;


		elementsCheckbox.clear();

		int i = 0;
		for (const auto& e : projet->elements())
		{
			elementsCheckbox.push_back(std::make_unique<checkbox>(elementsPanel.scrollPanel(), rectangle{0,20*i,1000,20}));
			elementsCheckbox.back()->caption(e.objet);
			elementsCheckbox.back()->check(e.fini);
			elementsCheckbox.back()->events().click([&](){getProjet(name)->updateElement(ToutDoux::Element{elementsCheckbox.back()->checked(), e.objet});});
			++i;
		}

		elementsPanel.collocate();
	}


	std::shared_ptr<ToutDoux::Projet> MainPage::getProjet(const std::string_view& nomProjet)
	{
		auto ret = std::ranges::find_if(_projets, [&](const std::shared_ptr<ToutDoux::Projet> p){return p->nom()==nomProjet;});
		if (ret == std::end(_projets)) return nullptr;

		return *ret;
	}

	void MainPage::UpdateProjectList()
	{
		projetsButton.clear();

		const auto& projs = ToutDoux::GetAllProject();
		for (const auto& p : projs)
		{
			_projets.push_back(std::make_shared<ToutDoux::Projet>(p.nom()));
		}

		for (const auto& p : _projets)
		{
			projetsButton.push_back(std::make_unique<button>(projetsPanel.scrollPanel(), p->nom()));
			projetsButton.back()->events().click([n=p->nom(), this](){
				ShowProjet(n);
				std::cout<<elementsCheckbox.size()<<'\n';
			});
			projetsPanel.field("projets")<<*projetsButton.back();
		}

		projetsPanel.collocate();
	}

	void MainPage::SetUp()
	{
		fenetre.caption("ToutDoux");
		fenetre.div("<min=20 projetsPanel>| <vert <fit title><elementsPanel> min=20>"s);

		fenetre["projetsPanel"]<<projetsPanel;
		fenetre["elementsPanel"]<<elementsPanel;
		fenetre["title"]<<titreProjet;

		projetsPanel.div("<vert fit projets>");

		UpdateProjectList();

		fenetre.collocate();

		fenetre.show();
		exec();
	}

}
