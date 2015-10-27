
#include "Controller.hpp"
#include "View.hpp"
#include "ViewGL.hpp"
#include "Utils.hpp"

// use old OpenGL so it should even run on bread toasters
#include <GL/glu.h>

#include <iostream>

const std::vector<std::array<float,4>> ViewGL::COLORS = 
{
    {1, 0, 0, 1},        // player red
    {0, 0, 1, 1},        // player blue
    {1, 1, 1, 1},        // jack
    {0.6, 0.6, 0.2, 1}   // none (ground)
};

ViewGL::ViewGL(Controller & refController, View & refView, int& argc, char** argv) :
    _refController(refController),
    _refView(refView),
    _theta(0),
    _phi(0),
    _motionThetaPhi(false)
{
    Gtk::GL::init(argc, argv);
    _glconfig = Gdk::GL::Config::create(Gdk::GL::MODE_RGBA 
            | Gdk::GL::MODE_DEPTH | Gdk::GL::MODE_DOUBLE);
    if (not _glconfig)
    {
        UTILS_ERROR("OpenGL init failed");
    }
    else
    {
        UTILS_INFO("OpenGL init ok");
    }

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
        UTILS_ERROR("OpenGL begin failed");
    }
    else
    {
        UTILS_INFO("OpenGL begin ok");

        glEnable(GL_DEPTH_TEST);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        float specular[4] = {0.8f, 0.8f, 0.8f, 1.f};
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
        float shininess[4] = {10.f, 10.f, 10.f, 1.f};
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

        _glwindow->gl_end();
    }
}

bool ViewGL::on_expose_event(GdkEventExpose* ) 
{
    // begin drawing
	_glwindow->gl_begin(_glcontext);
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    // camera transformation
    glRotatef(_theta, 0, 1, 0);
    glRotatef(_phi, cos(M_PI*_theta/180.0), 0, sin(M_PI*_theta/180.0));

    // update light position
    float lightPosition[4] = {0, 100, 0, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // draw balls
    for (const Ball & b : _refController.getBalls())
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, COLORS[b._player].data());
        glPushMatrix();
        glTranslatef(b._position(0), b._position(1), b._position(2));
        gluSphere(gluNewQuadric(), b._radius, 16, 16);
        glPopMatrix();
    }

    // draw ground
    const Ground & ground = _refController.getGround();
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, COLORS[PLAYER_NONE].data());
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(ground._xMin, 0, ground._zMin);
    glVertex3f(ground._xMin, 0, ground._zMax);
    glVertex3f(ground._xMax, 0, ground._zMax);
    glVertex3f(ground._xMax, 0, ground._zMin);
    glEnd();

    // end drawing
    glPopMatrix();
	_glwindow->gl_end();
    _glwindow->swap_buffers();
	return true;
}

bool ViewGL::on_configure_event(GdkEventConfigure * event) 
{
    float h = std::max(1, event->height);
    float w = event->width;
    float ratio = w / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(60, ratio, 1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 12, 10,      // position
            0, 2, 0,         // center
            0, 0.77, -0.77); // up vector

    return true;
}

bool ViewGL::on_button_press_event(GdkEventButton * event) 
{
    if (event->button == 1)
    {
        _thetaRef = event->x;
        _phiRef = event->y;
        _motionThetaPhi = true;
    }
    return true;
}

bool ViewGL::on_button_release_event(GdkEventButton * event) 
{
    if (event->button == 1)
        _motionThetaPhi = false; 
    return true;
}

bool ViewGL::on_motion_notify_event(GdkEventMotion * event) 
{
    if (_motionThetaPhi)
    {
        _theta += 0.5*(event->x - _thetaRef);
        _thetaRef = event->x;
        _phi += 0.5*(event->y - _phiRef);
        _phiRef = event->y;
        update();
    }
    return true;
}

void ViewGL::update() 
{
    _window->invalidate(false);
}

