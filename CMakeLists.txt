cmake_minimum_required(VERSION 3.4.0)

project(water)

include("avrgcc.cmake")
add_subdirectory(modbus)

add_executable(water.elf main.c USART.c)
