cmake_minimum_required(VERSION 3.10)
project(CS50Harvard C)

set(CMAKE_C_STANDARD 11)
set(FILE_NAME copy) #создание переменной FILE_NAME - ВПИСАТЬ ИМЯ ИСХОДНИКА .c
set(SOURCE_C_LIST  Sourses/${FILE_NAME}.c)
set(SOURCE_LIB_LIST ${CMAKE_CURRENT_SOURCE_DIR}/Libs/libcs50-8.1.0/cs50.c)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/)

add_executable(${FILE_NAME} ${SOURCE_C_LIST})

add_library(cs50 STATIC ${SOURCE_LIB_LIST})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Libs)

target_link_libraries(${FILE_NAME} cs50)
#link_directories(directory1 directory2 ...)

install(TARGETS ${FILE_NAME} DESTINATION Build) #C:/_Code/C/CLionProjects/CS50Harvard/Build
#install(PROGRAMS ${FILE_NAME} RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/Build/)
