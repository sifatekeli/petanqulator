
#include "View.hpp"
#include "ViewGL.hpp"

#include <iostream>

ViewGL::ViewGL(View & refView, int& argc, char** argv) :
_refView(refView)
{

	// initialize gtkglextmm
	Gtk::GL::init(argc, argv);
	_glconfig = Gdk::GL::Config::create(Gdk::GL::MODE_RGBA | Gdk::GL::MODE_DEPTH | Gdk::GL::MODE_DOUBLE);
	if (not _glconfig)
        std::cerr << "init error\n";
	set_gl_capability(_glconfig);

	// initialize event handling
	//Glib::signal_idle().connect(sigc::mem_fun(*this, &ViewGL::handle_idle));
	Glib::signal_timeout().connect(sigc::mem_fun(*this, &ViewGL::handle_idle), 20);
	add_events(Gdk::BUTTON_PRESS_MASK);
	add_events(Gdk::BUTTON_RELEASE_MASK);
	add_events(Gdk::BUTTON1_MOTION_MASK);
	add_events(Gdk::KEY_PRESS_MASK);
	add_events(Gdk::KEY_RELEASE_MASK);
	signal_key_press_event().connect(sigc::mem_fun(*this, &ViewGL::handle_key_press_event));
	signal_key_release_event().connect(sigc::mem_fun(*this, &ViewGL::handle_key_release_event));
	set_can_focus(true);
}

void ViewGL::init() {

	_glcontext = get_gl_context();

	// begin OpenGL
	Glib::RefPtr<Gdk::GL::Window> glwindow = get_gl_window();
	if (!glwindow->gl_begin(get_gl_context()))
		return;

	// end OpenGL
	glwindow->gl_end();

	// start counting fps
	//_fpsCounter.start();
}

bool ViewGL::on_expose_event(GdkEventExpose* ) {

	Glib::RefPtr<Gdk::GL::Window> glwindow = get_gl_window();
	if (not glwindow->gl_begin(_glcontext))
		return false;

    /*/
	// update camera
	float tx = _keyRight.getValue() - _keyLeft.getValue();
	float ty = _keyUp.getValue() - _keyDown.getValue();
	float tz = _keyBackward.getValue() - _keyForward.getValue();
	float rx = -_mouse.getYValue();	// mouse y controls rotation around opengl x-axis
	float ry = -_mouse.getXValue();	// mouse x controls rotation around opengl y-axis
	_displayDevice.updateView(tx, ty, tz, rx, ry, 0.f);
    */

	// render scene
    glClearColor(0.6, 0.7, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glwindow->swap_buffers();

	glwindow->gl_end();

	return true;
}

bool ViewGL::on_configure_event(GdkEventConfigure * ) {
	return true;
}

bool ViewGL::on_button_press_event(GdkEventButton* ) {
	return true;
}

bool ViewGL::on_button_release_event(GdkEventButton* ) {
		return true;
}

bool ViewGL::on_motion_notify_event(GdkEventMotion* ) {
	return true;
}

bool ViewGL::handle_idle() {

	// FIXME beurk
	grab_focus();

	// refresh opengl view
	Glib::RefPtr<Gdk::Window> win = get_window();
	if (win) win->invalidate(false);

	return true;
}

bool ViewGL::handle_key_press_event(GdkEventKey * ) {

    /*
	switch (event->keyval) {
	case GDK_KEY_Page_Up : _keyUp.press(); break;
	case GDK_KEY_Page_Down : _keyDown.press(); break;
	case GDK_KEY_Up : _keyForward.press(); break;
	case GDK_KEY_Down : _keyBackward.press(); break;
	case GDK_KEY_Left : _keyLeft.press(); break;
	case GDK_KEY_Right : _keyRight.press(); break;
	}
    */

	return true;
}

bool ViewGL::handle_key_release_event(GdkEventKey * ) {

    /*
	switch (event->keyval) {
	case GDK_KEY_Page_Up : _keyUp.release(); break;
	case GDK_KEY_Page_Down : _keyDown.release(); break;
	case GDK_KEY_Up : _keyForward.release(); break;
	case GDK_KEY_Down : _keyBackward.release(); break;
	case GDK_KEY_Left : _keyLeft.release(); break;
	case GDK_KEY_Right : _keyRight.release(); break;
	case GDK_KEY_Escape : Gtk::Main::quit();
	}
    */

	return true;
}
