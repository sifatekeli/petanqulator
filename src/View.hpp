
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
        void messageBox(const std::string & title, const std::string & message);
        bool confirmBox(const std::string & title, const std::string & message);
        void displayStatus(const std::string & message);
};

#endif
