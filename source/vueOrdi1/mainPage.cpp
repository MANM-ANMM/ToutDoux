#include "vueOrdi1/mainPage.hpp"

#include <string>
#include <iostream>
#include <string_view>
#include <vector>
#include <memory>
#include <ranges>
#include <algorithm>
#include <functional>

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/listbox.hpp>

#include "modele/ToutDoux.hpp"

namespace vueOrdi1
{
using namespace nana;
using namespace std::string_literals;
using namespace ToutDoux;


bool verifyHelpeur(window handle, const std::string_view& titreFenetreErreur, const std::string_view& messageErreur, std::function<bool()> predVerify)
{
	if (predVerify()) return true;

	msgbox erreurMsgBox{handle, std::string(titreFenetreErreur)};
	erreurMsgBox << messageErreur;
	erreurMsgBox.show();
	return false;
}

void Run()
{
	Manager manager {"./projets", true};
	std::string nomProjetCourrant;

	form fenetre;
	fenetre.caption("ToutDoux");
	fenetre.size({600,400});

	fenetre.div("<<vert min=20 fit <fit boutonsProjets><projetsListbox>>| <vert min=20 <fit boutonsElements><elementsListbox>>"s);


	//elementsListbox
	listbox elementsListbox {fenetre};
	fenetre["elementsListbox"]<<elementsListbox;
	elementsListbox.append_header("Elements"s);
	elementsListbox.events().resized([&elementsListbox](const arg_resized& arg){
		elementsListbox.column_at(0).width(arg.width-10);
	});

	elementsListbox.checkable(true);

	auto actualiseElementsListbox = [&manager, &elementsListbox, &nomProjetCourrant]()
	{
		elementsListbox.clear();
		try {
			std::vector<Element> elements = manager.getProjectElements(nomProjetCourrant);
			for (const Element& element : elements)
			{
				elementsListbox.at(0).append(element.objet);
				elementsListbox.at(0).back().check(statusElementToBool(element.status));
			}
		} catch (const std::domain_error& err) {
			
		}
	};

	elementsListbox.events().checked.connect_unignorable([&elementsListbox, &manager, &nomProjetCourrant](const nana::arg_listbox& args)
	{
		if (args.item.empty()) return;
		std::string objet;
		args.item.resolve_to(objet);
		const StatusElement status = statusElementFromBool(args.item.checked());
		manager.markElementAs(nomProjetCourrant, objet, status);
	});

	//boutonsElements
	button ajouterElementBouton{fenetre, "Ajouter Element"};
	ajouterElementBouton.events().click([&fenetre, &manager, &nomProjetCourrant, &actualiseElementsListbox]{
		if (nomProjetCourrant == "") return;
		inputbox newElemInputBox{fenetre, "Entr??e de l'objet du nouvel element"s, "Nouvel Element"s};
		inputbox::text objetInput{"Objet de l'??l??ment"};

		std::vector<std::string> nomsElementsActuels;
		std::ranges::transform(manager.getProjectElements(nomProjetCourrant), std::back_inserter(nomsElementsActuels), [](const Element& elem){return elem.objet;});

		newElemInputBox.verify([&objetInput, &manager, &nomProjetCourrant](window handle)
		{
			return verifyHelpeur(handle, "Objet invalide"s, "Un ??l??ment de ce projet porte ce nom ou l'objet sp??cifi?? est invalide"s,
					[&manager, nomProjetCourrant, objet=objetInput.value()](){ return manager.verifyObjetNouvelElement(nomProjetCourrant, objet);});
		});

		if (newElemInputBox.show_modal(objetInput))
		{
			manager.addElement(nomProjetCourrant, objetInput.value());
			actualiseElementsListbox();
		}
	});

	button supprimerElementsBouton{fenetre, "Supprimer Element(s)"};
	supprimerElementsBouton.events().click([&manager, &elementsListbox, &actualiseElementsListbox, &nomProjetCourrant](){
		if (elementsListbox.selected().empty()) return;
		for (const auto& itemElem: elementsListbox.selected())
		{
			std::string obj;
			elementsListbox.at(itemElem).resolve_to<std::string>(obj);
			manager.deleteElement(nomProjetCourrant, obj);
		}
		actualiseElementsListbox();
	});

	fenetre["boutonsElements"]<<ajouterElementBouton<<supprimerElementsBouton;

	//projetsListbox
	listbox projetsListbox {fenetre};
	fenetre["projetsListbox"]<<projetsListbox;
	projetsListbox.append_header("Projets"s);
	projetsListbox.events().resized([&projetsListbox](const arg_resized& arg){
		projetsListbox.column_at(0).width(arg.width-10);
	});

	projetsListbox.checkable(false);

	projetsListbox.events().selected.connect_unignorable([&projetsListbox, &elementsListbox, &manager, &nomProjetCourrant, &actualiseElementsListbox](const nana::arg_listbox& args){
		if (args.item.empty()) return;
		std::string nomProjetSelectionne;
		args.item.resolve_to(nomProjetSelectionne);

		if (nomProjetCourrant == nomProjetSelectionne) return;
		nomProjetCourrant = nomProjetSelectionne;

		actualiseElementsListbox();
	});

	auto actualiseProjetsListbox = [&projetsListbox, &manager]{
		projetsListbox.clear();

		std::vector<std::string> nomsProjets = manager.getProjectsNames();
		for (const std::string& nomProjet : nomsProjets) {
			projetsListbox.at(0).append(nomProjet);
		}
	};
	actualiseProjetsListbox();

	//boutonsProjets
	button ajouterProjetBouton{fenetre, "Ajouter Projet"};
	ajouterProjetBouton.events().click([&fenetre, &manager, &actualiseProjetsListbox]{
		inputbox newProjetInputBox{fenetre, "Entr??e du nom du projet"s, "Nouveau Projet"s};
		inputbox::text nomInput{"Nom du projet"s};

		newProjetInputBox.verify([&nomInput, &manager](window handle){
			return verifyHelpeur(handle, "Nom d??j?? utilis?? ou invalide", "Un projet de ce nom existe d??j?? ou ce nom est invalide",
					[nom=nomInput.value(), &manager]()->bool {return manager.verifyNomNouveauProjet(nom);});
		});

		if (newProjetInputBox.show_modal(nomInput))
		{
			manager.addProject(nomInput.value());
			actualiseProjetsListbox();
		}
	});

	button supprimerProjetBouton{fenetre, "Supprimer Projet"s};
	supprimerProjetBouton.events().click([&manager, &projetsListbox, &actualiseProjetsListbox, &actualiseElementsListbox, &nomProjetCourrant]{
		if (projetsListbox.selected().empty()) return;
		for (const auto& itemProjet: projetsListbox.selected())
		{
			std::string nomProjet;
			projetsListbox.at(itemProjet).resolve_to<std::string>(nomProjet);
			manager.deleteProject(nomProjet);
		}
		nomProjetCourrant = "";
		actualiseProjetsListbox();
		actualiseElementsListbox();
	});

	fenetre["boutonsProjets"] <<ajouterProjetBouton<<supprimerProjetBouton;

	fenetre.collocate();

	fenetre.show();
	exec();
}

}
