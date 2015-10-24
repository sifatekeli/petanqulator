
#include "View.hpp"
#include "ViewGL.hpp"

#include <GL/glu.h>

#include <iostream>

ViewGL::ViewGL(View & refView, int& argc, char** argv) :
    _refView(refView),
    _translateX(0),
    _translateY(0),
    _isMotion(false)
{

	// initialize gtkglextmm
	Gtk::GL::init(argc, argv);
	_glconfig = Gdk::GL::Config::create(Gdk::GL::MODE_RGBA 
            | Gdk::GL::MODE_DEPTH | Gdk::GL::MODE_DOUBLE);
	if (not _glconfig)
        std::cerr << "error: ViewGL::ViewGL" << std::endl;
	set_gl_capability(_glconfig);

	// initialize event handling
	//Glib::signal_idle().connect(sigc::mem_fun(*this, &ViewGL::handle_idle));
	//Glib::signal_timeout().connect(sigc::mem_fun(*this, &ViewGL::handle_idle), 20);
	add_events(Gdk::BUTTON_PRESS_MASK);
	add_events(Gdk::BUTTON_RELEASE_MASK);
	add_events(Gdk::BUTTON1_MOTION_MASK);
}

void ViewGL::init() 
{
    _window = get_window();
	_glcontext = get_gl_context();
    _glwindow = get_gl_window();

	if (not _glwindow->gl_begin(_glcontext))
    {
        std::cerr << "error: ViewGL::init" << std::endl;
        exit(-1);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

	_glwindow->gl_end();
}

bool ViewGL::on_expose_event(GdkEventExpose* ) 
{
	_glwindow->gl_begin(_glcontext);

    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(_translateX, _translateY, 0);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Material()._diffuse);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Material()._specular);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, Material()._shininess);
    gluSphere(gluNewQuadric(), 0.5, 32, 32);
    glPopMatrix();

	_glwindow->gl_end();
    _glwindow->swap_buffers();

	return true;
}

bool ViewGL::on_configure_event(GdkEventConfigure * ) 
{
	return true;
}

bool ViewGL::on_button_press_event(GdkEventButton * event) 
{
    if (event->button == 1)
    {
        _motionX = event->x;
        _motionY = event->y;
        _isMotion = true;
    }
	return true;
}

bool ViewGL::on_button_release_event(GdkEventButton * event) 
{
    if (event->button == 1)
        _isMotion = false; 
    return true;
}

bool ViewGL::on_motion_notify_event(GdkEventMotion * event) 
{
    if (_isMotion)
    {
        _translateX += 0.005*(event->x - _motionX);
        _motionX = event->x;
        _translateY += -0.005*(event->y - _motionY);
        _motionY = event->y;
        _window->invalidate(false);
    }
	return true;
}

bool ViewGL::handle_idle() 
{

	// FIXME beurk
	//grab_focus();

    _window->invalidate(false);
	return true;
}

/*
bool ViewGL::handle_key_press_event(GdkEventKey * ) 
{

	switch (event->keyval) {
	case GDK_KEY_Page_Up : _keyUp.press(); break;
	case GDK_KEY_Page_Down : _keyDown.press(); break;
	case GDK_KEY_Up : _keyForward.press(); break;
	case GDK_KEY_Down : _keyBackward.press(); break;
	case GDK_KEY_Left : _keyLeft.press(); break;
	case GDK_KEY_Right : _keyRight.press(); break;
	}

	return true;
}

bool ViewGL::handle_key_release_event(GdkEventKey * ) 
{

	switch (event->keyval) {
	case GDK_KEY_Page_Up : _keyUp.release(); break;
	case GDK_KEY_Page_Down : _keyDown.release(); break;
	case GDK_KEY_Up : _keyForward.release(); break;
	case GDK_KEY_Down : _keyBackward.release(); break;
	case GDK_KEY_Left : _keyLeft.release(); break;
	case GDK_KEY_Right : _keyRight.release(); break;
	case GDK_KEY_Escape : Gtk::Main::quit();
	}

	return true;
}
*/


