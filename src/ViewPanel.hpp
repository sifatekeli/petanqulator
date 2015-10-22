
#ifndef _VIEWPANEL_HPP_
#define _VIEWPANEL_HPP_

#include <gtkmm.h>

class View;

class ViewPanel : public Gtk::VBox 
{
	View & _refView;

	Gtk::Label _sceneLabel;
    Gtk::Button _quitButton;

public:
	ViewPanel(View & refView);
	void init();
};

#endif
