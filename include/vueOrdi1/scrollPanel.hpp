#pragma once

#include <nana/gui.hpp>
#include <nana/gui/widgets/scroll.hpp>
#include <nana/gui/widgets/panel.hpp>

#include <tuple>

namespace vueOrdi1
{
	class panel_scrolled : public nana::panel<false>
	{
	public:
	    panel_scrolled(const nana::window& parent, const unsigned int&& scrollHight);

		const nana::panel<false>& scrollPanel() const;

		void div(std::string div_str);

		nana::place::field_reference field(const char* name);

		void collocate();

		unsigned scrollHeight() const;

		void scrollHeight(const unsigned h);

	private:
	    nana::panel<false> myVisible;           ///< Part of scrolled panel that is visible
		nana::panel<false> scrolled_panel;
	    nana::scroll<true> myScrollVert;
	    nana::place myPlace;
		nana::place scrolled_panel_place;

		unsigned int _scrollHeight;
	};

template<typename ElementType>
std::vector<std::unique_ptr<ElementType>> populateScrollPanel(panel_scrolled& scrollPanel, const std::vector<std::string>& args)
{
	std::vector<std::unique_ptr<ElementType>> elements;
	for (const auto& a : args)
	{
		elements.push_back(std::make_unique<ElementType>(scrollPanel.scrollPanel(), a));
		scrollPanel.field("elements")<<*elements.back();
	}
	scrollPanel.collocate();

	return elements;
}
}
