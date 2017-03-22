// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#include "Controller.hpp"
#include "View.hpp"
#include "ViewGL.hpp"

#include <petanqulator/Utils.hpp>

// use old OpenGL so it should even run on bread toasters
#include <GL/glu.h>

#include <array>
#include <iostream>

ViewGL::ViewGL(Controller & controller, View & view, int & argc, char** argv) :
    _refController(controller), _refView(view),
    _theta(0), _phi(10),
    _thetaRef(_theta), _phiRef(_phi),
    _motionThetaPhi(false),
    _x(-5), _y(0), _z(0),
    _dxRef(_x), _dyRef(_y),
    _motionDxDy(false),
    _distance(10)
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
    add_events(Gdk::BUTTON3_MOTION_MASK);
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

        setGlColor(GL_SPECULAR, {{0.8f, 0.8f, 0.8f, 1.f}});
        setGlColor(GL_SHININESS, {{10.f, 10.f, 10.f, 1.f}});

        _glwindow->gl_end();
    }
}

bool ViewGL::on_expose_event(GdkEventExpose* ) 
{
    // begin drawing
    _glwindow->gl_begin(_glcontext);
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // camera transformation
    glLoadIdentity();
    float thetaRad = degToRad(_theta);
    float phiRad = degToRad(_phi);
    float ct = cos(thetaRad);
    float st = sin(thetaRad);
    float cp = cos(phiRad);
    float sp = sin(phiRad);
    float ex = _distance*cp*st;
    float ey = _distance*sp;
    float ez = _distance*cp*ct;
    float ux = -sp*st;
    float uy = cp;
    float uz = -sp*ct;
    gluLookAt(_x+ex, _y+ey, _z+ez,   // position
            _x, _y, _z,              // center
            ux, uy, uz);             // up vector

    // update light position
    float lightPosition[4] = {0, 100, 0, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // draw red balls
    for (const GameBall & b : _refController.getRedBalls())
    {
        setGlColor(GL_DIFFUSE, {{1.f, 0.f, 0.f, 1.f}});
        glPushMatrix();
        btVector3 p = b._transform.getOrigin();
        glTranslatef(p.getX(), p.getY(), p.getZ());
        gluSphere(gluNewQuadric(), b._radius, 16, 16);
        glPopMatrix();
    }

    // draw blue balls
    for (const GameBall & b : _refController.getBlueBalls())
    {
        setGlColor(GL_DIFFUSE, {{0.f, 0.f, 1.f, 1.f}});
        glPushMatrix();
        btVector3 p = b._transform.getOrigin();
        glTranslatef(p.getX(), p.getY(), p.getZ());
        gluSphere(gluNewQuadric(), b._radius, 16, 16);
        glPopMatrix();
    }

    // draw jack
    const GameBall & jack = _refController.getJack();
    setGlColor(GL_DIFFUSE, {{1.f, 0.f, 1.f, 1.f}});
    glPushMatrix();
    btVector3 pJack = jack._transform.getOrigin();
    glTranslatef(pJack.getX(), pJack.getY(), pJack.getZ());
    gluSphere(gluNewQuadric(), jack._radius, 16, 16);
    glPopMatrix();

    // draw ground
    const GameGround & ground = _refController.getGround();
    setGlColor(GL_DIFFUSE, {{0.6f, 0.6f, 0.2f, 1.f}});
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(ground._xMin, 0, ground._zMin);
    glVertex3f(ground._xMin, 0, ground._zMax);
    glVertex3f(ground._xMax, 0, ground._zMax);
    glVertex3f(ground._xMax, 0, ground._zMin);
    glEnd();

    // draw shooter
    player_t currentPlayer = _refController.getCurrentPlayer();
    if (currentPlayer == 0)
        setGlColor(GL_DIFFUSE, {{1.f, 0.f, 0.f, 1.f}});
    else
        setGlColor(GL_DIFFUSE, {{0.f, 0.f, 1.f, 1.f}});
    glPushMatrix();
    btVector3 shooterPosition = _refController.getShooterPosition();
    glTranslatef(shooterPosition.getX(), shooterPosition.getY(), 
            shooterPosition.getZ());
    VecParam params = _refView.getThrowParams();
    double pitch = params(0);
    double yaw = params(1);
    glRotatef(90 - yaw, 0, 1, 0);
    glRotatef(- pitch, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 0.06, 0.06, 1, 16, 2);
    glTranslatef(0, 0, 1);
    gluCylinder(gluNewQuadric(), 0.12, 0, 0.3, 16, 2);
    glPopMatrix();

    // end drawing
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
    if (event->button == 3)
    {
        _dxRef = event->x;
        _dyRef = event->y;
        _motionDxDy = true;
    }
    return true;
}

bool ViewGL::on_button_release_event(GdkEventButton * event) 
{
    if (event->button == 1)
        _motionThetaPhi = false; 
    if (event->button == 3) 
        _motionDxDy = false; 
    return true;
}

bool ViewGL::on_motion_notify_event(GdkEventMotion * event) 
{
    if (_motionThetaPhi)
    {
        _theta += 0.2*(_thetaRef - event->x);
        _phi += -0.2*(_phiRef - event->y);
        _thetaRef = event->x;
        _phiRef = event->y;
        update();
    }
    if (_motionDxDy)
    {
        float dx = 0.02*(_dxRef - event->x);
        float dy = 0.02*(_dyRef - event->y);
        _dxRef = event->x;
        _dyRef = event->y;
        float thetaRad = degToRad(_theta);
        _x += dx*cos(thetaRad) + dy*sin(thetaRad); 
        _z += -dx*sin(thetaRad) + dy*cos(thetaRad); 
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

void ViewGL::setGlColor(GLenum type, const std::array<float,4> & colorv)
{
    glMaterialfv(GL_FRONT_AND_BACK, type, colorv.data());
}

