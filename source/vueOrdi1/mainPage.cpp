#include "mainPage.hpp"


#include <vector>
#include <memory>
#include <string>
#include <iostream>

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/checkbox.hpp>

#include "scrollPanel.hpp"

namespace vueOrdi1
{
	void SetUp()
	{
		using namespace nana;
		using namespace std::string_literals;

		form fenetre;
		fenetre.caption("ToutDoux");


		fenetre.div("<min=20 projetsPanel>| <vert <fit title><elementsPanel> min=20>");


		label titreProjet{fenetre, "Titre"s};
		titreProjet.text_align(align::center);

		panel_scrolled elementsPanel(fenetre, 1000);
		panel_scrolled projetsPanel(fenetre,500);

		fenetre["projetsPanel"]<<projetsPanel;
		fenetre["elementsPanel"]<<elementsPanel;
		fenetre["title"]<<titreProjet;

		projetsPanel.div("<vert fit projets>");
		elementsPanel.div("<vert fit elements>");

		std::vector<std::unique_ptr<label>> projects;

		for (int i=0; i<10;++i)
		{
			projects.push_back(std::make_unique<label>(projetsPanel.scrollPanel(),"ProjetPviezoqhk "s+std::to_string(i)));
			projetsPanel.field("projets")<<*projects.back();
		}
		projetsPanel.collocate();


		std::vector<std::unique_ptr<checkbox>> elements;
		for (int i=0; i<100;++i)
		{
			elements.push_back(std::make_unique<checkbox>(elementsPanel.scrollPanel(),"Element n°"s+std::to_string(i)));
			elementsPanel.field("elements")<<*elements.back();
		}
		elementsPanel.collocate();

		fenetre.collocate();

		fenetre.show();
		exec();

	}

}
