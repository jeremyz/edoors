LIST(APPEND TESTS_CC_SOURCES
   main.c
   )

include_directories(
    ${EINA_INCLUDE_DIRS}
   ${CMAKE_SOURCE_DIR}/src/include
   )

add_executable(tests ${TESTS_CC_SOURCES})

get_target_property(eiotas_LIB_FILE eiotas LOCATION)
target_link_libraries(tests
    ${EINA_LIBRARIES}
   ${eiotas_LIB_FILE}
   )

add_dependencies(tests eiotas)

add_test(Example_tests tests)
