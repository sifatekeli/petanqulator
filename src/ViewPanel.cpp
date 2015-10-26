
#include "Game.hpp"
#include "View.hpp"
#include "ViewPanel.hpp"
#include "Utils.hpp"

ViewPanel::ViewPanel(Game & refGame, View & refView) :
    _refGame(refGame),
    _refView(refView),
    _newButton("new"),
    _quitButton("quit"),
    _throwBallButton("   throw ball   ")
{

	pack_start(_newButton, Gtk::PACK_SHRINK);
	_newButton.signal_clicked().connect(
            sigc::mem_fun(*this, &ViewPanel::handleNew));

	pack_start(_quitButton, Gtk::PACK_SHRINK);
	_quitButton.signal_clicked().connect(
            sigc::mem_fun(_refView, &View::quit));

    packLabel("\npitch:");
    _pitchSpin.set_range(-180, 180);
    _pitchSpin.set_increments(1, 5);
    pack_start(_pitchSpin, Gtk::PACK_SHRINK);
    packLabel("yaw:");
    _yawSpin.set_range(-180, 180);
    _yawSpin.set_increments(1, 5);
    _yawSpin.set_value(20);
    pack_start(_yawSpin, Gtk::PACK_SHRINK);
    packLabel("velocity:");
    _velocitySpin.set_digits(1);
    _velocitySpin.set_range(0, 20);
    _velocitySpin.set_increments(0.1, 5);
    _velocitySpin.set_value(10);
    pack_start(_velocitySpin, Gtk::PACK_SHRINK);

    pack_start(_throwBallButton, Gtk::PACK_SHRINK);
	_throwBallButton.signal_clicked().connect(
            sigc::mem_fun(*this, &ViewPanel::handleThrowBall));

    pack_start(_teamLabel, Gtk::PACK_SHRINK);
    _teamLabel.set_label("\nTODO teams");
}

void ViewPanel::update()
{
    _refView.displayStatus(_refGame.getStatus());
}

void ViewPanel::handleNew()
{
    UTILS_INFO("new game");
    _refGame.newGame();
    _refView.update();
}

void ViewPanel::handleThrowBall()
{
    _refView.update();
}

void ViewPanel::packLabel(const char * str)
{
    Gtk::Label * ptrLabel = Gtk::manage(new Gtk::Label(str));
    pack_start(*ptrLabel, Gtk::PACK_SHRINK);
}

