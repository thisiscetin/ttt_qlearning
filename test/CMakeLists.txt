include_directories(${PROJECT_SOURCE_DIR}/ext)
include_directories(${PROJECT_SOURCE_DIR}/src)

ADD_EXECUTABLE(tests
  ${PROJECT_SOURCE_DIR}/test/test_board.cpp
  ${PROJECT_SOURCE_DIR}/test/test_game.cpp

  ${PROJECT_SOURCE_DIR}/src/board.cpp
  ${PROJECT_SOURCE_DIR}/src/game.cpp
  ${PROJECT_SOURCE_DIR}/src/table.cpp
)

set_target_properties(tests
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries(tests)


