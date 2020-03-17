include_directories(${PROJECT_SOURCE_DIR}/ext)
include_directories(${PROJECT_SOURCE_DIR}/src)

ADD_EXECUTABLE(tests
        ../src/board.cpp
        ../src/board.h
        test_board.cpp ../src/game.cpp ../src/game.h test_game.cpp ../src/table.cpp ../src/table.h test_table.cpp ../src/trainer.cpp ../src/trainer.h test_trainer.cpp)

set_target_properties(tests
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )

target_link_libraries(tests)


