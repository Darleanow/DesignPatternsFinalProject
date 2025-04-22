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
  
  src/Authentication/UserAuthentication.cpp
  
  src/Repository/TechnicianRepositoryProxy.cpp
  
  src/Repository/InterventionRepositoryProxy.cpp
  
  src/Technician/ExpertiseDecorator.cpp
  src/Technician/TechnicianDecorator.cpp
  src/Technician/BasicTechnician.cpp

  src/Repository/TechnicianRepository.cpp
  include/TechMa/Repository/TechnicianRepository.h

  src/Repository/InterventionRepository.cpp
  include/TechMa/Repository/InterventionRepository.h

  src/Interventions/ConcreteIntervention.cpp
  src/Facade/InterventionCreatorFacade.cpp
  src/Factory/InterventionFactory.cpp

  src/Views/TechMapp.cpp
  include/TechMa/Views/TechMapp.h

  src/Views/Pages/LoginPage.cpp
  include/TechMa/Views/Pages/LoginPage.h
  
  src/Views/Pages/InterventionPage.cpp
  include/TechMa/Views/Pages/InterventionPage.h 

  src/Views/Pages/TechniciansPage.cpp
  include/TechMa/Views/Pages/TechniciansPage.h 

  src/Views/Pages/ParametersPage.cpp
  include/TechMa/Views/Pages/ParametersPage.h

  src/Views/Widgets/NavigationBar.cpp
  include/TechMa/Views/Widgets/NavigationBar.h
  
  src/Views/Widgets/CreateTechnicianDialog.cpp
  include/TechMa/Views/Widgets/CreateTechnicianDialog.h

  src/Views/Widgets/TechniciansListView.cpp
  include/TechMa/Views/Widgets/TechniciansListView.h

  src/Views/Widgets/EntityEditorLayout.cpp
  include/TechMa/Views/Widgets/EntityEditorLayout.h

  src/Views/Widgets/TechnicianEditPanel.cpp
  include/TechMa/Views/Widgets/TechnicianEditPanel.h

  src/Views/Controllers/TechListController.cpp
  include/TechMa/Views/Controllers/TechListController.h

  src/Views/Widgets/CreateInterventionDialog.cpp
  include/TechMa/Views/Widgets/CreateInterventionDialog.h 

  src/Views/Widgets/InterventionEditPanel.cpp
  include/TechMa/Views/Widgets/InterventionEditPanel.h

  src/Views/Widgets/InterventionsListView.cpp
  include/TechMa/Views/Widgets/InterventionsListView.h
)

target_sources(TechMa PRIVATE ${APP_RESOURCES})

target_include_directories(TechMa PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(TechMa Qt6::Widgets Qt6::Svg)