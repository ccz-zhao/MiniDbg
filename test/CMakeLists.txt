add_executable(hello hello.cc)
set_target_properties(hello
                      PROPERTIES COMPILE_FLAGS "-g -O0")

add_executable(variable variable.cc)
set_target_properties(variable
                      PROPERTIES COMPILE_FLAGS "-gdwarf-2 -O0")

add_executable(unwinding stack_unwinding.cc)
set_target_properties(unwinding
                      PROPERTIES COMPILE_FLAGS "-g -O0")