cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(project_3)

set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)
add_executable(project_3 main.cpp
        Board.cpp
        Board.h
        Cell.cpp
        Cell.h
        Visual.h
        Button.cpp
        Button.h
        TextureManager.cpp
        TextureManager.h
        UIComponent.cpp
        UIComponent.h
        Scene.cpp
        Scene.h
        TextElement.cpp
        TextElement.h
        Digits.cpp
        Digits.h
        GUI.h)
target_link_libraries(project_3 sfml-system sfml-window sfml-graphics sfml-audio)
