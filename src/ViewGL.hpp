
#ifndef _VIEWGL_HPP_
#define _VIEWGL_HPP_

#include <gtkmm.h>
#include <gtkglmm.h>

class View;

// Displays an OpenGL scene in a gtkmm window.
class ViewGL : public Gtk::GL::DrawingArea 
{

	View & _refView;

	Glib::RefPtr< Gdk::Window > _window;
	Glib::RefPtr< Gdk::GL::Config > _glconfig;
	Glib::RefPtr< Gdk::GL::Context > _glcontext;
	Glib::RefPtr< Gdk::GL::Window > _glwindow;

    float _translateX;
    float _translateY;
    float _motionX;
    float _motionY;
    bool _isMotion;

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
	//bool handle_key_press_event(GdkEventKey * event);
	//bool handle_key_release_event(GdkEventKey * event);
};

#endif

