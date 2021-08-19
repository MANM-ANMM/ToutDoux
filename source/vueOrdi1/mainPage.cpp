#include "mainPage.hpp"

#include <nana/gui.hpp>
#include <nana/gui/widgets/listbox.hpp>

void SetUp()
{
	using namespace nana;
	form fenetre;
	fenetre.caption("ToutDoux");

	fenetre.div("<listeProjet margin=1>|90% <listeElements margin=10>");

	listbox listeProjet{fenetre};
	listeProjet.append_header("Projet", 100);
	listeProjet.at(0).append({"One"});
	listeProjet.at(0).append({"Two"});
	listeProjet.at(0).append({"Three"});

	fenetre["listeProjet"]<< listeProjet;

	fenetre.collocate();

	fenetre.show();
	exec();

}
