
add_executable(average-score                  2.1-3\ average-score/main.cpp)
add_executable(count-lines-using-accumulate   2.4\ count-lines-using-accumulate/main.cpp)
add_executable(filter-and-transform           2.8-9\ filter-and-transform/main.cpp)
add_executable(filter-and-transform-combined  2.11-15\ filter-and-transform-combined/main.cpp)
add_executable(filtering-using-remove-if      2.7\ filtering-using-remove-if/main.cpp)
add_executable(move-selected                  2.6\ move-selected/main.cpp)


set_property(TARGET average-score                 PROPERTY FOLDER "examples/chapter-02")
set_property(TARGET count-lines-using-accumulate  PROPERTY FOLDER "examples/chapter-02")
set_property(TARGET filter-and-transform          PROPERTY FOLDER "examples/chapter-02")
set_property(TARGET filter-and-transform-combined PROPERTY FOLDER "examples/chapter-02")
set_property(TARGET filtering-using-remove-if     PROPERTY FOLDER "examples/chapter-02")
set_property(TARGET move-selected                 PROPERTY FOLDER "examples/chapter-02")

set_property(TARGET average-score PROPERTY CXX_STANDARD 17)

target_link_libraries(average-score -ltbb)
