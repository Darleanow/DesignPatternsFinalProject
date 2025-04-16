cmake_minimum_required(VERSION 3.28)
project(TechMa)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(
  TechMa

  src/main.cpp
  
  src/Technician/ExpertiseDecorator.cpp
  src/Technician/TechnicianDecorator.cpp
  src/Technician/Technician.cpp
)

target_include_directories(TechMa PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(TechMa Qt6::Widgets)
