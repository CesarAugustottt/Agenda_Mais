cmake_minimum_required(VERSION 3.19)
project(Agenda LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Agenda
    MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    Medicamentos.h
    MedicamentosImpl.h
    MedicamentosImpl.cpp
    User.h
    UserImpl.h
    UserImpl.cpp
    handleBody.h
    Appointment.h
    AppointmentImpl.h
    AppointmentImpl.cpp
)

target_link_libraries(Agenda
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS Agenda
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Agenda
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
