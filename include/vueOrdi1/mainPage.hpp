#pragma once

#include <string_view>
#include <vector>
#include <memory>

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/checkbox.hpp>

#include "vueOrdi1/scrollPanel.hpp"

namespace vueOrdi1
{
class MainPage
{
public:
	MainPage();
	void SetUp();
	void ShowProjet(const std::string_view& nomProjet);
private:
	void UpdateProjectList();

	nana::form fenetre;
	nana::label titreProjet;

	panel_scrolled elementsPanel;
	panel_scrolled projetsPanel;

	std::vector<std::unique_ptr<nana::button>> projetsButton;
	std::vector<std::unique_ptr<nana::checkbox>> elementsCheckbox;
};



}
