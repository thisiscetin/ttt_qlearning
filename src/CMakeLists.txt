INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)

ADD_EXECUTABLE(game
  ${PROJECT_SOURCE_DIR}/main.cpp

  ${PROJECT_SOURCE_DIR}/src/board.cpp
  ${PROJECT_SOURCE_DIR}/src/game.cpp
  ${PROJECT_SOURCE_DIR}/src/table.cpp
)

set_target_properties(game
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries (game)
