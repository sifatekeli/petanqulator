
#ifndef _VIEW_HPP_
#define _VIEW_HPP_

#include "ViewPanel.hpp"
#include "ViewGL.hpp"

#include <gtkmm.h>

class View 
{
    Gtk::Main _kit;
    Gtk::Window _window;
	Gtk::HBox _hbox;
	ViewPanel _viewPanel;
	ViewGL _viewGL;

public :
	View (int & argc, char ** argv);
	void run();
    void quit();
};

#endif
