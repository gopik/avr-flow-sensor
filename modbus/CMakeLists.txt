enable_testing()

add_library(modbus_registers modbus_registers.c)
add_executable(modbus_registers_test modbus_registers.c modbus_registers_test.c)

add_test(modbus_registers_test modbus_registers_test)
