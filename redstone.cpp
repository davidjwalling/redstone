#include "idriver.h"

#include <iostream>
#include <string>

using namespace std;

namespace redstone {
    namespace command {
        constexpr const char* exit = "exit";
    }
}

int __cdecl main(int argc, char* argv[])
{
    IDriver& driver = TheDriver();
    if (driver.Start(argc, argv)) {
        string line;
        while (getline(cin, line) && line != redstone::command::exit);
        driver.Stop();
    }
    return driver.Result();
}
