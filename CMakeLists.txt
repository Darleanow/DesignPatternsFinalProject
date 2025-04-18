cmake_minimum_required(VERSION 3.28)
project(TechMa)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Svg)
qt_add_resources(APP_RESOURCES resources.qrc)

add_executable(
  TechMa

  src/main.cpp
  
  src/Technician/ExpertiseDecorator.cpp
  src/Technician/TechnicianDecorator.cpp
  src/Technician/Technician.cpp

  src/Views/TechMapp.cpp
  include/TechMa/Views/TechMapp.h

  src/Views/Pages/InterventionPage.cpp
  include/TechMa/Views/Pages/InterventionPage.h 

  src/Views/Pages/TechniciansPage.cpp
  include/TechMa/Views/Pages/TechniciansPage.h 

  src/Views/Pages/ParametersPage.cpp
  include/TechMa/Views/Pages/ParametersPage.h

  src/Views/Widgets/NavigationBar.cpp
  include/TechMa/Views/Widgets/NavigationBar.h
)

target_sources(TechMa PRIVATE ${APP_RESOURCES})

target_include_directories(TechMa PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(TechMa Qt6::Widgets Qt6::Svg)
