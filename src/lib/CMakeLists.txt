LIST(APPEND EDOORS_CC_SOURCES
   edoors_main.c
   edoors_particle.c
   edoors_link.c
   edoors_iota.c
   edoors_spin.c
   edoors_room.c
   edoors_door.c
   edoors_board.c
   )

include_directories(
    ${EINA_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/src/include
   )

add_library(edoors SHARED ${EDOORS_CC_SOURCES})
target_link_libraries(edoors
    ${EINA_LIBRARIES}
   )

set_target_properties(edoors PROPERTIES
    VERSION ${EDOORS_VERSION} SOVERSION ${EDOORS_VERSION_MAJOR})
set_target_properties(edoors PROPERTIES OUTPUT_NAME "edoors")
