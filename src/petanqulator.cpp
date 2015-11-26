// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#include "Controller.hpp"

// TODO(dehos): add camera zoom and camera translation

int main(int argc, char ** argv)
{
    Controller controller(argc, argv);
    controller.run();
    return 0;
}

