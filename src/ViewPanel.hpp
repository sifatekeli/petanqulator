
#ifndef _VIEWPANEL_HPP_
#define _VIEWPANEL_HPP_

#include <gtkmm.h>

class View;

class ViewPanel : public Gtk::VBox 
{
    View & _refView;

    Gtk::Button _newButton;
    Gtk::Button _quitButton;

    Gtk::SpinButton _pitchSpin1;
    Gtk::SpinButton _yawSpin1;
    Gtk::SpinButton _velocitySpin1;
    Gtk::Button _launchButton1;

    Gtk::SpinButton _pitchSpin2;
    Gtk::SpinButton _yawSpin2;
    Gtk::SpinButton _velocitySpin2;
    Gtk::Button _launchButton2;

    public:
    ViewPanel(View & refView);

    private:
    void packLabel(const char * str);
};

#endif
