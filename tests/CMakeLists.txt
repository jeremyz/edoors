LIST(APPEND TESTS_CC_SOURCES
   main.c
   helper.c
   spin.c
   particle.c
   user_door.c
   )

include_directories(
    ${EINA_INCLUDE_DIRS}
   ${CMAKE_SOURCE_DIR}/src/include
   )

add_executable(tests ${TESTS_CC_SOURCES})

get_target_property(edoors_LIB_FILE edoors LOCATION)
target_link_libraries(tests
    ${EINA_LIBRARIES}
   ${edoors_LIB_FILE}
   )

add_dependencies(tests edoors)

add_test(Example_tests tests)
