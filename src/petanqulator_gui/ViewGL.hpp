// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#ifndef _VIEWGL_HPP_
#define _VIEWGL_HPP_

#include <petanqulator/Chrono.hpp>

#include <gtkmm.h>
#include <gtkglmm.h>

class Controller;
class View;

class ViewGL : public Gtk::GL::DrawingArea 
{
    private:
        Controller & _refController;
        View & _refView;

        Glib::RefPtr< Gdk::Window > _window;
        Glib::RefPtr< Gdk::GL::Config > _glconfig;
        Glib::RefPtr< Gdk::GL::Context > _glcontext;
        Glib::RefPtr< Gdk::GL::Window > _glwindow;

        // camera orbit
        float _theta, _phi;
        float _thetaRef, _phiRef;
        bool _motionThetaPhi;

        // camera target
        float _x, _y, _z;
        float _dxRef, _dyRef;
        bool _motionDxDy;

        // camera distance
        float _distance;
        // TODO add camera zoom and camera translation

    public:
        ViewGL(Controller & controller, View & view, int & argc, char** argv);

        void init();
        void update();

        void startAnimation();
        void stopAnimation();

    private:
        // override signal handlers
        bool on_expose_event(GdkEventExpose * event) override;
        bool on_configure_event(GdkEventConfigure * event) override;
        bool on_button_press_event(GdkEventButton* event) override;
        bool on_button_release_event(GdkEventButton* event) override;
        bool on_motion_notify_event(GdkEventMotion * event) override;

        // new handlers
        Chrono _chrono;
        sigc::connection _timeoutConnection;
        bool handleTimeout();

        void setGlColor(GLenum type, std::array<float,4> colorv);
};

#endif

