
#ifndef _VIEWGL_HPP_
#define _VIEWGL_HPP_

#include <gtkmm.h>
#include <gtkglmm.h>

class View;

// Displays an OpenGL scene in a gtkmm window.
class ViewGL : public Gtk::GL::DrawingArea 
{

	View & _refView;

    /*
	// display info
	Herve::FpsCounter _fpsCounter;
	Herve::InputMotion1dRelative _keyUp;
	Herve::InputMotion2d _mouse;
    */

public:

	Glib::RefPtr< Gdk::GL::Config > _glconfig;
	Glib::RefPtr< Gdk::GL::Context > _glcontext;


public:
	ViewGL(View & refView, int & argc, char** argv);
	void init();

private:
	// override signal handlers
	bool on_expose_event(GdkEventExpose * event);
	bool on_configure_event(GdkEventConfigure * event);
	bool on_button_press_event(GdkEventButton* event);
	bool on_button_release_event(GdkEventButton* event);
	bool on_motion_notify_event(GdkEventMotion * event);

	// new handlers
	bool handle_idle();
	bool handle_key_press_event(GdkEventKey * event);
	bool handle_key_release_event(GdkEventKey * event);
};

#endif
