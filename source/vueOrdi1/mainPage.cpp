#include "vueOrdi1/mainPage.hpp"


#include <string>
#include <iostream>



namespace vueOrdi1
{
using namespace nana;
using namespace std::string_literals;
using namespace ToutDoux;

void Run()
{
	Manager manager {"./projets", true};
	std::string nomProjetCourrant;

	form fenetre;
	fenetre.caption("ToutDoux");

	fenetre.div("<<min=20 projetsPanel>| <vert <fit title><elementsPanel> min=20>>"s);

	label titreProjet {fenetre, "Titre"s};
	fenetre["title"]<<titreProjet;

	listbox elementsListbox {fenetre};
	fenetre["elementsPanel"]<<elementsListbox;
	elementsListbox.append_header("Elements"s);

	elementsListbox.checkable(true);

	elementsListbox.events().checked.connect_unignorable([&elementsListbox, &manager, &nomProjetCourrant](const nana::arg_listbox& args)
	{
		if (args.item.empty()) return;
		std::string objet;
		args.item.resolve_to(objet);
		const StatusElement status = statusElementFromBool(args.item.checked());
		manager.markElementAs(nomProjetCourrant, objet, status);
	});

	listbox projetsListbox {fenetre};
	fenetre["projetsPanel"]<<projetsListbox;
	projetsListbox.append_header("Projets"s);

	projetsListbox.checkable(false);
	projetsListbox.enable_single(true, true);

	projetsListbox.events().selected.connect_unignorable([&projetsListbox, &elementsListbox, &manager, &nomProjetCourrant](const nana::arg_listbox& args){
		if (args.item.empty()) return;
		std::string nomProjetSelectionne;
		args.item.resolve_to(nomProjetSelectionne);

		if (nomProjetCourrant == nomProjetSelectionne) return;
		nomProjetCourrant = nomProjetSelectionne;

		std::vector<Element> elements = manager.getProjectElements(nomProjetSelectionne);

		elementsListbox.clear();

		for (const Element& element : elements)
		{
			elementsListbox.at(0).append(element.objet);
			elementsListbox.at(0).back().check(statusElementToBool(element.status));
		}
	});


	std::vector<std::string> nomsProjets = manager.getProjectsNames();
	for (const std::string nomProjet : nomsProjets) {
		projetsListbox.at(0).append(nomProjet);
	}


	fenetre.collocate();

	fenetre.show();
	exec();
}

}
