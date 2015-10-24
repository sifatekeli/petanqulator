
#include "View.hpp"

View::View(int & argc, char** argv) :
_kit(argc, argv),
_window(),
_viewPanel(*this),
_viewGL(*this, argc, argv) 
{
	_window.set_title("PETANQue simULATOR");
	_window.set_size_request(800, 600);
	_window.move(0, 0);

	_window.add(_hbox);
	_hbox.pack_start(_viewPanel, Gtk::PACK_SHRINK);
	_hbox.pack_start(_viewGL);
	_window.show_all();
}

void View::run() 
{
	_viewGL.init();
	_kit.run(_window);
}

void View::quit()
{
    _kit.quit();
}
