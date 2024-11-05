cmake_minimum_required(VERSION 3.10)

project(redstone LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 11)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    include(GNUInstallDirs)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    add_compile_options(
        -fvisibility=hidden
        -Wno-deprecated-declarations
        -Wno-deprecated-register
    )
    find_package(Threads REQUIRED)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_definitions(
        -D_WIN32_WINNT=0x0601
        -DNOMINMAX
        -DVC_EXTRALEAN
        -DWIN32_LEAN_AND_MEAN
        -D_CRT_SECURE_NO_WARNINGS
        -D_SCL_SECURE_NO_WARNINGS
        -D_WINSOCK_DEPRECATED_NO_WARNINGS
    )
endif()

set (LIB_SRCS
    driver.cpp
    logger.cpp
)

set (PUB_HDRS
    iapi.h
    idriver.h
)

add_library(libredstone SHARED ${LIB_SRCS})

set_target_properties(libredstone PROPERTIES PREFIX "")
set_target_properties(libredstone PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(libredstone PROPERTIES PUBLIC_HEADER "${PUB_HDRS}")

target_include_directories(libredstone INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/libredstone>
)

install(TARGETS libredstone EXPORT libredstone
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libredstone
    RUNTIME       DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY       DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE       DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(EXPORT libredstone
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libredstone
    FILE libredstone.cmake
)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_link_libraries(libredstone PRIVATE Threads::Threads)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    target_link_libraries(libredstone wsock32 ws2_32)
    target_compile_definitions(libredstone PUBLIC _WINDLL)
endif()
 
set (TEST_SRCS
    testredstone.cpp
)

add_executable(testredstone ${TEST_SRCS})

target_link_libraries(testredstone libredstone)

install(TARGETS testredstone
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set (REDSTONE_SRCS
    redstone.cpp
)

add_executable(redstone ${REDSTONE_SRCS})

target_link_libraries(redstone libredstone)

install (TARGETS redstone
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
