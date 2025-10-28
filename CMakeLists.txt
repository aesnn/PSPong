cmake_minimum_required(VERSION 3.11)
project(PSPong)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} PRIVATE
    pspdebug
    pspdisplay
    pspctrl
    pspge
    pspgu
    pspgum
)

create_pbp_file(
    TARGET ${PROJECT_NAME}
    ICON_PATH ${CMAKE_SOURCE_DIR}/assets/ICON0.png
    BACKGROUND_PATH ${CMAKE_SOURCE_DIR}/assets/PIC1.png
    PREVIEW_PATH NULL
    TITLE ${PROJECT_NAME}
    VERSION 01.00
)
