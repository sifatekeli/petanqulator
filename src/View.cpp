
#include "View.hpp"
#include "Utils.hpp"

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
    update();
	_kit.run(_window);
}

void View::quit()
{
    if (confirmBox("Quit ?","Do you really want to quit this wonderful game ?"))
    {
        UTILS_INFO("quit");
        _kit.quit();
    }
}

void View::update()
{
    _viewPanel.update();
    _viewGL.update();
}

void View::startAnimation()
{
    _viewPanel.startAnimation();
    _viewGL.startAnimation();
}

void View::stopAnimation()
{
    _viewPanel.stopAnimation();
    _viewGL.stopAnimation();
}

void View::messageBox(const std::string & title, const std::string & message) 
{
    Glib::ustring uTitle(title.c_str());
    Glib::ustring uMessage(message.c_str());
    Gtk::MessageDialog dialog(_window, uMessage);
    dialog.set_title(uTitle);
    dialog.run();
}

bool View::confirmBox(const std::string & title, const std::string & message) 
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

