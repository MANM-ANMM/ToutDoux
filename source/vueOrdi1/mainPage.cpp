#include "vueOrdi1/mainPage.hpp"


#include <string>
#include <iostream>


#include "modele/ToutDoux.hpp"

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
		ToutDoux::Projet p{name};

		elementsCheckbox.clear();
		//elementsPanel.div("<fit vert elements>");
		int i = 0;
		for (const auto& e : p.elements())
		{
			elementsCheckbox.push_back(std::make_unique<checkbox>(elementsPanel.scrollPanel(), rectangle{0,20*i,1000,20}));
			elementsCheckbox.back()->caption(e.objet);
			elementsCheckbox.back()->check(e.fini);
			++i;

			//elementsPanel.field("elements")<<*elementsCheckbox.back();
		}

		elementsPanel.collocate();
	}

	void MainPage::UpdateProjectList()
	{
		projetsButton.clear();

		std::vector<ToutDoux::Projet> projets = ToutDoux::GetAllProject();

		for (const auto& p : projets)
		{
			projetsButton.push_back(std::make_unique<button>(projetsPanel.scrollPanel(), p.nom()));
			projetsButton.back()->events().click([n=p.nom(), this](){
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
