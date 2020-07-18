
add_executable(counting-team-members 3.3\ counting-team-members/main.cpp)
add_executable(older-than-generic    3.1\ older-than-generic/main.cpp)

set_property(TARGET counting-team-members PROPERTY FOLDER "examples/chapter-03")
set_property(TARGET older-than-generic    PROPERTY FOLDER "examples/chapter-03")

set_property(TARGET counting-team-members PROPERTY CXX_STANDARD 17)
