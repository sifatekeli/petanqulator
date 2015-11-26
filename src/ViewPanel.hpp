// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#ifndef _VIEWPANEL_HPP_
#define _VIEWPANEL_HPP_

#include <gtkmm.h>

class Controller;
class View;

class ViewPanel : public Gtk::VBox 
{
    private:
        Controller & _refController;
        View & _refView;

        Gtk::Button _newButton;
        Gtk::Button _quitButton;

        Gtk::SpinButton _pitchSpin;
        Gtk::SpinButton _yawSpin;
        Gtk::SpinButton _velocitySpin;
        Gtk::Button _throwBallButton;
        Gtk::Label _infoLabel;

    public:
        ViewPanel(Controller & refController, View & refView);
        void startAnimation();
        void stopAnimation();

        double getPitch() const;
        double getYaw() const;
        double getVelocity() const;

    private:
        void packLabel(const char * str);
        void handleNew();
        void handleThrowBall();
};

#endif
