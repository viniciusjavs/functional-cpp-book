
add_executable(count-lines-stdcount  1.2\ count-lines-stdcount/main.cpp  )
add_executable(count-lines-transform 1.3\ count-lines-transform/main.cpp )

set_property(TARGET count-lines-stdcount   PROPERTY FOLDER "examples/chapter-01")
set_property(TARGET count-lines-transform  PROPERTY FOLDER "examples/chapter-01")
