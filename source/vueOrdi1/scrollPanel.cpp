#include "scrollPanel.hpp"

namespace vueOrdi1
{
	panel_scrolled::panel_scrolled(const nana::window& parent, const unsigned int&& scrollHight)
	        : panel<false>(parent, true),
	          myVisible( *this, true ),
	          myScrollVert( *this, true ),
	          myPlace( *this )
	{
		scrollHeight(scrollHight);

		scrolled_panel.create(myVisible, true);
		scrolled_panel_place.bind(scrolled_panel);
		events().resized([&]()
		{
			const unsigned int h = std::max(scrollHeight(), size().height);
			myScrollVert.amount( h );
			scrolled_panel.move({0,0, size().width-16, h*2});
			scrolled_panel.move(
	            0,
	            -myScrollVert.value() );
			scrolled_panel_place.collocate();
		});

		events().mouse_wheel([&](const nana::arg_wheel& arg){
			myScrollVert.make_step(!arg.upwards, 5);
		});

	    // register scroll event handlers

	    myScrollVert.events().value_changed([&]
	    {
	        scrolled_panel.move(
	            0,
	            -myScrollVert.value() );
	    });

	    // arrange visible panel with scroll at right
	    myPlace.div("<<panel><scroll_vert weight=16>>");
	    myPlace["panel"] << myVisible;
	    myPlace["scroll_vert"] << myScrollVert;
	    myPlace.collocate();
	}

	const nana::panel<false>& panel_scrolled::scrollPanel() const
	{
		return scrolled_panel;
	}

	void panel_scrolled::div(std::string div_str)
	{
		scrolled_panel_place.div(div_str);
	}

	nana::place::field_reference panel_scrolled::field(const char* name)
	{
		return scrolled_panel_place.field(name);
	}

	void panel_scrolled::collocate()
	{
		scrolled_panel_place.collocate();
	}

	unsigned panel_scrolled::scrollHeight()const
	{
		return _scrollHeight;
	}

	void panel_scrolled::scrollHeight(const unsigned h)
	{
		_scrollHeight = h;
	}
}
