cmake_minimum_required(VERSION 3.16)
project(CVRP_Project VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CRUCIAL para que Qt genere el código de la interfaz de forma automática
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Buscar cabeceras y fuentes en tus carpetas
file(GLOB HEADERS "include/*.hpp" "include/*.h")
file(GLOB SOURCES "src/*.cpp")

add_executable(cvrp_app
    main/main.cpp
    ${SOURCES}
    ${HEADERS}
    ui/mainwindow.ui
)

target_include_directories(cvrp_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(cvrp_app PROPERTIES AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")
target_link_libraries(cvrp_app PRIVATE Qt6::Widgets)