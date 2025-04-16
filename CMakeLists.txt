cmake_minimum_required(VERSION 3.28)
project(TechMa)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
  TechMa

  src/main.cpp
  
  src/Technician/ExpertiseDecorator.cpp
  src/Technician/TechnicianDecorator.cpp
  src/Technician/Technician.cpp
)

target_include_directories(TechMa PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
