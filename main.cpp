
#include <dlib/uintn.h>
#include "world.h"

using namespace dlib;

const dlib::uint64 FRAME_TIME = 30000;

int main() {
    // create our window
    win my_window;

    timestamper ts;
    world world(my_window);

    while (!my_window.is_closed()) {
        auto start = ts.get_timestamp();

        world.update();

        auto stop = ts.get_timestamp();

        unsigned long sleep_time = (unsigned long) ((FRAME_TIME - (stop - start)) / 1000);
        if (sleep_time > 0) {
            dlib::sleep(sleep_time);
        }
    }


    my_window.wait_until_closed();

    return 0;
}


