
#include "View.hpp"
#include "ViewPanel.hpp"

ViewPanel::ViewPanel(View & refView) :
    _refView(refView),
    _newButton("new"),
    _quitButton("quit"),
    _launchButton1("launch"),
    _launchButton2("launch")
{

	pack_start(_newButton, Gtk::PACK_SHRINK);

	pack_start(_quitButton, Gtk::PACK_SHRINK);
	_quitButton.signal_clicked().connect(
            sigc::mem_fun(_refView, &View::quit));

    packLabel("\npitch:");
    _pitchSpin1.set_range(-180, 180);
    _pitchSpin1.set_increments(1, 5);
    pack_start(_pitchSpin1, Gtk::PACK_SHRINK);
    packLabel("yaw:");
    _yawSpin1.set_range(-180, 180);
    _yawSpin1.set_increments(1, 5);
    _yawSpin1.set_value(20);
    pack_start(_yawSpin1, Gtk::PACK_SHRINK);
    packLabel("velocity:");
    _velocitySpin1.set_digits(1);
    _velocitySpin1.set_range(0, 20);
    _velocitySpin1.set_increments(0.1, 5);
    _velocitySpin1.set_value(10);
    pack_start(_velocitySpin1, Gtk::PACK_SHRINK);
    pack_start(_launchButton1, Gtk::PACK_SHRINK);

}

void ViewPanel::packLabel(const char * str)
{
    Gtk::Label * ptrLabel = Gtk::manage(new Gtk::Label(str));
    pack_start(*ptrLabel, Gtk::PACK_SHRINK);
}

