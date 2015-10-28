
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
