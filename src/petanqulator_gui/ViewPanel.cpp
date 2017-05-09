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

    VecParam pmin = _refController.getMinParams();
    VecParam pmax = _refController.getMaxParams();

    packLabel("\n pitch:");
    _pitchSpin.set_range(pmin(0), pmax(0));
    _pitchSpin.set_increments(1, 5);
    _pitchSpin.set_value(45);
    pack_start(_pitchSpin, Gtk::PACK_SHRINK);
	_pitchSpin.signal_changed().connect(sigc::mem_fun(_refView, &View::update));
    packLabel(" yaw:");
    _yawSpin.set_range(pmin(1), pmax(1));
    _yawSpin.set_increments(1, 5);
    pack_start(_yawSpin, Gtk::PACK_SHRINK);
	_yawSpin.signal_changed().connect(sigc::mem_fun(_refView, &View::update));
    packLabel(" velocity:");
    _velocitySpin.set_digits(1);
    _velocitySpin.set_range(pmin(2), pmax(2));
    _velocitySpin.set_increments(0.1, 5);
    _velocitySpin.set_value(5);
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
    // throw ball
    _refController.startThrow(getThrowParams());
}

void ViewPanel::packLabel(const char * str)
{
    Gtk::Label * ptrLabel = Gtk::manage(new Gtk::Label(str));
    ptrLabel->set_alignment(Gtk::ALIGN_START);
    pack_start(*ptrLabel, Gtk::PACK_SHRINK);
}

VecParam ViewPanel::getThrowParams() const
{
    double pitch = _pitchSpin.get_value();
    double yaw = _yawSpin.get_value();
    double velocity = _velocitySpin.get_value();
    return VecParam(pitch, yaw, velocity);
}

