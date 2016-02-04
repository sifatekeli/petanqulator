// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#ifndef _VIEW_HPP_
#define _VIEW_HPP_

#include "ViewPanel.hpp"
#include "ViewGL.hpp"

#include <gtkmm.h>

class Controller;

class View 
{
    private:
        Controller & _refController;
        Gtk::Main _kit;
        Gtk::Window _window;
        Gtk::Statusbar _statusbar;

        ViewPanel _viewPanel;
        ViewGL _viewGL;

    public :
        View (Controller & refController, int & argc, char ** argv);
        void run();
        void quit();
        void update();
        void displayMessage(const std::string & title, 
                const std::string & message);
        bool displayConfirm(const std::string & title, 
                const std::string & message);
        void displayStatus(const std::string & message);

        static std::string getPlayerName(player_t player);

        ThrowParams getThrowParams() const;

        void startAnimation();
        void stopAnimation();
};

#endif
