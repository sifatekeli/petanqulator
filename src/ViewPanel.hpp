
#ifndef _VIEWPANEL_HPP_
#define _VIEWPANEL_HPP_

#include <gtkmm.h>

class Game;
class View;

class ViewPanel : public Gtk::VBox 
{
    private:
        Game & _refGame;
        View & _refView;

        Gtk::Button _newButton;
        Gtk::Button _quitButton;

        Gtk::SpinButton _pitchSpin;
        Gtk::SpinButton _yawSpin;
        Gtk::SpinButton _velocitySpin;
        Gtk::Button _launchButton;

    public:
        ViewPanel(Game & refGame, View & refView);
        void update();

    private:
        void packLabel(const char * str);
        void handleNew();
        void handleLaunch();
};

#endif
