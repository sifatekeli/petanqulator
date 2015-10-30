
#include "Controller.hpp"
#include "View.hpp"
#include "ViewGL.hpp"
#include "Utils.hpp"

// use old OpenGL so it should even run on bread toasters
#include <GL/glu.h>

#include <iostream>

ViewGL::ViewGL(Controller & refController, View & refView, int& argc, 
        char** argv) :
    _refController(refController),
    _refView(refView),
    _theta(0),
    _phi(20),
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

        setGlColor(GL_SPECULAR, {0.8f, 0.8f, 0.8f, 1.f});
        setGlColor(GL_SHININESS, {10.f, 10.f, 10.f, 1.f});

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
    glRotatef(_theta, 0, 0, 1);
    glRotatef(_phi, sin(M_PI*_theta/180.0), cos(M_PI*_theta/180.0), 0);

    // update light position
    float lightPosition[4] = {0, 0, 100, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // draw red balls
    for (const GameBall & b : _refController.getRedBalls())
    {
        setGlColor(GL_DIFFUSE, {1.f, 0.f, 0.f, 1.f});
        glPushMatrix();
        btVector3 p = b._transform.getOrigin();
        glTranslatef(p.getX(), p.getY(), p.getZ());
        gluSphere(gluNewQuadric(), b._radius, 16, 16);
        glPopMatrix();
    }

    // draw blue balls
    for (const GameBall & b : _refController.getBlueBalls())
    {
        setGlColor(GL_DIFFUSE, {0.f, 0.f, 1.f, 1.f});
        glPushMatrix();
        btVector3 p = b._transform.getOrigin();
        glTranslatef(p.getX(), p.getY(), p.getZ());
        gluSphere(gluNewQuadric(), b._radius, 16, 16);
        glPopMatrix();
    }

    // draw jack
    const GameBall & jack = _refController.getJack();
    setGlColor(GL_DIFFUSE, {1.f, 0.f, 1.f, 1.f});
    glPushMatrix();
    btVector3 pJack = jack._transform.getOrigin();
    glTranslatef(pJack.getX(), pJack.getY(), pJack.getZ());
    gluSphere(gluNewQuadric(), jack._radius, 16, 16);
    glPopMatrix();

    // draw ground
    const GameGround & ground = _refController.getGround();
    setGlColor(GL_DIFFUSE, {0.6f, 0.6f, 0.2f, 1.f});
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glVertex3f(ground._xMin, ground._yMin, 0);
    glVertex3f(ground._xMin, ground._yMax, 0);
    glVertex3f(ground._xMax, ground._yMax, 0);
    glVertex3f(ground._xMax, ground._yMin, 0);
    glEnd();

    // draw shooter
    player_t currentPlayer = _refController.getCurrentPlayer();
        if (currentPlayer == 0)
            setGlColor(GL_DIFFUSE, {1.f, 0.f, 0.f, 1.f});
        else
            setGlColor(GL_DIFFUSE, {0.f, 0.f, 1.f, 1.f});
    glPushMatrix();
    btVector3 shooterPosition = _refController.getShooterPosition();
    glTranslatef(shooterPosition.getX(), shooterPosition.getY(), 
            shooterPosition.getZ());
    glRotatef(90 - _refView.getYaw(), 0, 0, 1);
    glRotatef(90 - _refView.getPitch(), 0, 1, 0);
    gluCylinder(gluNewQuadric(), 0.06, 0.06, 1, 16, 2);
    glTranslatef(0, 0, 1);
    gluCylinder(gluNewQuadric(), 0.12, 0, 0.3, 16, 2);
    glPopMatrix();

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
    gluLookAt(10, 0, 2,      // position
            0, 0, 2,          // center
            0, 0, 1);  // up vector

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

void ViewGL::startAnimation()
{
    _chrono.start();
    _timeoutConnection = Glib::signal_timeout().connect(
            sigc::mem_fun(*this, &ViewGL::handleTimeout), 30);
}

void ViewGL::stopAnimation()
{
    if (_timeoutConnection.connected())
    {
        _chrono.stop();
        _timeoutConnection.disconnect();

        std::stringstream ss;
        ss << "animation, duration=" << _chrono.elapsedStopped();
        UTILS_INFO(ss.str());
    }
}

bool ViewGL::handleTimeout()
{
    update();
    double duration = _chrono.elapsedRunning();
    _refController.updateThrow(duration);
    return true;
}

void ViewGL::setGlColor(GLenum type, std::array<float,4> colorv)
{
    glMaterialfv(GL_FRONT_AND_BACK, type, colorv.data());
}

