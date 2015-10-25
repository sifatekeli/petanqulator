
#ifndef _VIEWGL_HPP_
#define _VIEWGL_HPP_

#include <gtkmm.h>
#include <gtkglmm.h>

class Game;
class View;

class ViewGL : public Gtk::GL::DrawingArea 
{
    Game & _refGame;
	View & _refView;

	Glib::RefPtr< Gdk::Window > _window;
	Glib::RefPtr< Gdk::GL::Config > _glconfig;
	Glib::RefPtr< Gdk::GL::Context > _glcontext;
	Glib::RefPtr< Gdk::GL::Window > _glwindow;

    float _theta;
    float _thetaRef;
    float _phi;
    float _phiRef;
    bool _motionThetaPhi;

public:
	ViewGL(Game & refGame, View & refView, int & argc, char** argv);
	void init();
    void update();

private:
	// override signal handlers
	bool on_expose_event(GdkEventExpose * event);
	bool on_configure_event(GdkEventConfigure * event);
	bool on_button_press_event(GdkEventButton* event);
	bool on_button_release_event(GdkEventButton* event);
	bool on_motion_notify_event(GdkEventMotion * event);

	// new handlers
	//bool handle_idle();
};

#endif

