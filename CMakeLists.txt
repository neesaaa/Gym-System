cmake_minimum_required(VERSION 3.5)
project(gym_v2 VERSION 0.1 LANGUAGES CXX)

# Required by Qt for automatic handling of UI files, MOC, and RCC
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Set C++ standard to C++17 and make it required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



# Find necessary Qt components
find_package(Qt6 REQUIRED COMPONENTS Widgets Sql PrintSupport)

# Find ODBC package
find_package(ODBC REQUIRED)

# List of project source files
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    dashboard.h
    dashboard.cpp
    dashboard.ui
    member.h
    member.cpp
    member.ui
    packages.cpp
    packages.h
    packages.ui
    safe.h
    safe.cpp
    safe.ui
    user.h
    user.cpp
    user.ui
    sheets.cpp
    sheets.h
    sheets.ui
    images/images.qrc
)

# Add executable target and specify source files
qt_add_executable(gym_v2
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    search.h search.cpp search.ui
    emp.h emp.cpp emp.ui
)

# Link necessary Qt modules and ODBC library to the executable
target_link_libraries(gym_v2 PRIVATE
    Qt6::Widgets
    Qt6::Sql
    Qt6::PrintSupport
    ODBC::ODBC
)

# Installation rules (adjust as needed)
include(GNUInstallDirs)
install(TARGETS gym_v2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
