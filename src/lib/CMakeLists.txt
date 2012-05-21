LIST(APPEND EIOTAS_CC_SOURCES
   eiotas_main.c
   eiotas_particle.c
   eiotas_link.c
   eiotas_iota.c
   eiotas_spin.c
   eiotas_room.c
   eiotas_door.c
   eiotas_board.c
   )

include_directories(
    ${EINA_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/src/include
   )

add_library(eiotas SHARED ${EIOTAS_CC_SOURCES})
target_link_libraries(eiotas
    ${EINA_LIBRARIES}
   )

set_target_properties(eiotas PROPERTIES
    VERSION ${EIOTAS_VERSION} SOVERSION ${EIOTAS_VERSION_MAJOR})
set_target_properties(eiotas PROPERTIES OUTPUT_NAME "eiotas")
