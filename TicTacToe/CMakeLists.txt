cmake_minimum_required(VERSION 3.16)

project(TicTacToe VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appTicTacToe
    main.cpp
)

qt_add_qml_module(appTicTacToe
    URI TicTacToe
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES model.h model.cpp
        SOURCES controller.h controller.cpp
        QML_FILES RoundButton.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appTicTacToe PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appTicTacToe
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appTicTacToe
    PRIVATE Qt6::Quick
)
target_link_libraries(appTicTacToe PRIVATE Qt6::Core)
target_link_libraries(appTicTacToe PRIVATE Qt6::Core Qt6::Widgets)

include(GNUInstallDirs)
install(TARGETS appTicTacToe
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
