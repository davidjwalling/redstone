#include "driver.h"
#include "logger.h"

using namespace std;

Driver theDriver;

Driver::Driver()
{
    Init();
}

Driver::~Driver()
{
    Reset();
}

void Driver::Init()
{
}

void Driver::Reset()
{
    Init();
}

bool Driver::Start(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    return true;
}

void Driver::Stop()
{
    AppErr(0);
}

int Driver::Result()
{
    return AppErr();
}

IDriver& TheDriver()
{
    return theDriver;
}

IDriver* TheDriverPtr()
{
    return &theDriver;
}
