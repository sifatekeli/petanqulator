
#include "View.hpp"
#include "ViewPanel.hpp"

/*
#include <sstream>
#include <iomanip>
*/

ViewPanel::ViewPanel(View & refView) :
_refView(refView),
_sceneLabel(" scene: "),
_quitButton("Quit")
{

	// scene
	_sceneLabel.set_alignment(Gtk::ALIGN_START);
	pack_start(_sceneLabel, Gtk::PACK_SHRINK);
	pack_start(_quitButton, Gtk::PACK_SHRINK);
	_quitButton.signal_clicked().connect(
            sigc::mem_fun(_refView, &View::quit));
}

void ViewPanel::init() {
	// fill combo box with scene names

	// select the last scene in the combo box
}
