add_executable(hello hello.c)
add_executable(factorial factorial.c)

option(DISABLE_DBUG "Disable DBUG?" NO)
if (DISABLE_DBUG)
    message(STATUS "DBUG disabled")
    add_compile_definitions(DBUG_OFF)
else()
    message(STATUS "DBUG enabled")
endif()

target_link_libraries(hello dbug)
target_link_libraries(factorial dbug)