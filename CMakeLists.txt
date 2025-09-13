cmake_minimum_required(VERSION 3.16)

project(trabalho1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(C:/SDL2-2.32.8/include)

link_directories(C:/SDL2-2.32.8/lib)
link_libraries(Mingw32 SDL2main SDL2_image SDL2_ttf SDL2_mixer SDL2)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/*.h")
file(GLOB RECURSOS "${PROJECT_SOURCE_DIR}/recursos/*")

source_group("src" FILES ${SOURCES})
source_group("include" FILES ${HEADERS})
source_group("recursos" FILES ${RECURSOS})

# Define onde o executável será gerado
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

add_executable(trabalho1
    ${SOURCES}
    ${HEADERS}    # só para aparecer no Qt Creator
    ${RECURSOS}   # só para aparecer no Qt Creator
)

add_custom_command(TARGET trabalho1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/recursos $<TARGET_FILE_DIR:trabalho1>/recursos
)

include(GNUInstallDirs)
install(TARGETS trabalho1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
