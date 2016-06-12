cmake_minimum_required(VERSION 3.4.0)
include("avrgcc.cmake")

project("modbus_registers")

enable_testing()

add_executable(modbus_registers_test modbus_registers.c modbus_registers_test.c)

add_test(modbus_registers_test modbus_registers_test)
