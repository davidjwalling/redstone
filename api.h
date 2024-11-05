#pragma once

#include "iapi.h"

#if defined(_WIN32)
#include <WinSock2.h> // SOCKET, DWORD, va_list, vsnprintf
#else
#include <cstdarg> // va_start, va_end
#endif
