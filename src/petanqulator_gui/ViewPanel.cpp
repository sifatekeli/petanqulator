// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#include "Controller.hpp"
#include "View.hpp"
#include "ViewPanel.hpp"

#include <petanqulator/Utils.hpp>

#include <set>
#include <sstream>

ViewPanel::ViewPanel(Controller & refController, View & refView) :
    _refController(refController),
    _refView(refView),
    _newButton("new"),
    _quitButton("quit"),
    _throwBallButton("         throw ball          ")
{
	pack_start(_newButton, Gtk::PACK_SHRINK);
	_newButton.signal_clicked().connect(
            sigc::mem_fun(*this, &ViewPanel::handleNew));

	pack_start(_quitButton, Gtk::PACK_SHRINK);
	_quitButton.signal_clicked().connect(
            sigc::mem_fun(_refView, &View::quit));

    packLabel("\n pitch:");
    _pitchSpin.set_digits(2);
    _pitchSpin.set_value(0.5);
    _pitchSpin.set_range(0, 1);
    _pitchSpin.set_increments(0.01, 0.1);
    pack_start(_pitchSpin, Gtk::PACK_SHRINK);
	_pitchSpin.signal_changed().connect(sigc::mem_fun(_refView, &View::update));
    packLabel(" yaw:");
    _yawSpin.set_digits(2);
    _yawSpin.set_value(0.5);
    _yawSpin.set_range(0, 1);
    _yawSpin.set_increments(0.01, 0.1);
    pack_start(_yawSpin, Gtk::PACK_SHRINK);
	_yawSpin.signal_changed().connect(sigc::mem_fun(_refView, &View::update));
    packLabel(" velocity:");
    _velocitySpin.set_digits(2);
    _velocitySpin.set_value(0.5);
    _velocitySpin.set_range(0, 1);
    _velocitySpin.set_increments(0.01, 0.1);
    pack_start(_velocitySpin, Gtk::PACK_SHRINK);

    pack_start(_throwBallButton, Gtk::PACK_SHRINK);
	_throwBallButton.signal_clicked().connect(
            sigc::mem_fun(*this, &ViewPanel::handleThrowBall));

    pack_start(_infoLabel, Gtk::PACK_SHRINK);
    _infoLabel.set_alignment(Gtk::ALIGN_START);
}

void ViewPanel::startAnimation()
{
    _throwBallButton.set_sensitive(false);
}

void ViewPanel::stopAnimation()
{
    _throwBallButton.set_sensitive(true);
    std::stringstream ss;
    ss << "\n remaining red:  " << _refController.getRemainingBallsRed();
    ss << "\n remaining blue: " << _refController.getRemainingBallsBlue();
    _infoLabel.set_label(ss.str());
}

void ViewPanel::handleNew()
{
    _refController.newGame();
}

void ViewPanel::handleThrowBall()
{
    /*
    // get velocity vector from the interface
    double radPitch = degToRad(getPitch());
    double radYaw = degToRad(getYaw());
    double velocity = getVelocity();

    // compute velocity vector from pitch/yaw
    double vx = velocity * cos(radPitch) * cos(radYaw);
    double vx = velocity * sin(radPitch);
    double vz = velocity * cos(radPitch) * sin(radYaw);
    */
    double pitch = getPitch();
    double yaw = getYaw();
    double velocity = getVelocity();

    // throw ball
    _refController.startThrow(pitch, yaw, velocity);
}

void ViewPanel::packLabel(const char * str)
{
    Gtk::Label * ptrLabel = Gtk::manage(new Gtk::Label(str));
    ptrLabel->set_alignment(Gtk::ALIGN_START);
    pack_start(*ptrLabel, Gtk::PACK_SHRINK);
}

double ViewPanel::getPitch() const
{
    return _pitchSpin.get_value();
}

double ViewPanel::getYaw() const
{
    return _yawSpin.get_value();
}

double ViewPanel::getVelocity() const
{
    return _velocitySpin.get_value();
}

