// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#include "Controller.hpp"
#include "View.hpp"

#include <petanqulator/Utils.hpp>

View::View(Controller & refController, int & argc, char** argv) :
    _refController(refController),
    _kit(argc, argv),
    _window(),
    _viewPanel(refController, *this),
    _viewGL(refController, *this, argc, argv) 
{
    _window.set_title("PETANQue simULATOR");
    _window.resize(800, 600);
    _window.move(0, 0);

    Gtk::VBox * ptrVBox = Gtk::manage(new Gtk::VBox());
	_window.add(*ptrVBox);

    Gtk::HBox * ptrHBox = Gtk::manage(new Gtk::HBox());
	ptrVBox->pack_start(*ptrHBox);
	ptrHBox->pack_start(_viewPanel, Gtk::PACK_SHRINK);
	ptrHBox->pack_start(_viewGL);

    ptrVBox->pack_start(_statusbar, Gtk::PACK_SHRINK);

	_window.show_all();
}

void View::run() 
{
    UTILS_INFO("run");
	_viewGL.init();
    _refController.newGame();
    update();
	_kit.run(_window);
}

void View::quit()
{
    if (displayConfirm("Quit ?",
                "Do you really want to quit this wonderful game ?"))
    {
        UTILS_INFO("quit");
        _kit.quit();
    }
}

void View::update()
{
    _viewGL.update();
}

std::string View::getPlayerName(player_t player)
{
    switch (player)
    {
        case PLAYER_RED: return "red";
        case PLAYER_BLUE: return "blue";
        default: return "none";
    }
}

void View::startAnimation()
{
    displayStatus("Simulation in progress...");
    _viewPanel.startAnimation();
    _viewGL.startAnimation();
}

void View::stopAnimation()
{
    _viewPanel.stopAnimation();
    _viewGL.stopAnimation();

    if (_refController.isGameFinished())
    {
        GameResult res = _refController.computeGameResult();
        std::stringstream ss;
        ss << "We've got a winner: " << getPlayerName(res._winningPlayer)
            << " with " << res._nbWinningBalls << " ball(s) !";

        displayStatus(ss.str());
        displayMessage("Game finished", ss.str());
    }
    else
    {
        std::stringstream ss;
        player_t player = _refController.getCurrentPlayer();
        ss << "current player: " << getPlayerName(player);
        displayStatus(ss.str());
    }
}

void View::displayMessage(const std::string & title, const std::string & message) 
{
    Glib::ustring uTitle(title.c_str());
    Glib::ustring uMessage(message.c_str());
    Gtk::MessageDialog dialog(_window, uMessage);
    dialog.set_title(uTitle);
    dialog.run();
}

bool View::displayConfirm(const std::string & title, const std::string & message) 
{
    Glib::ustring uTitle(title.c_str());
    Glib::ustring uMessage(message.c_str());
    Gtk::MessageDialog dialog(_window, uMessage, false, Gtk::MESSAGE_QUESTION, 
            Gtk::BUTTONS_YES_NO);
    dialog.set_title(uTitle);
    int ret = dialog.run();
    return ret == Gtk::RESPONSE_YES;
}

void View::displayStatus(const std::string & message) 
{
    _statusbar.pop();
    _statusbar.push(message);
}

VecParam View::getThrowParams() const
{
    return _viewPanel.getThrowParams();
}

