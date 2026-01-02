file(GLOB_RECURSE CHARACTER ./ *.cpp)

#将FUNCS中所有cpp编译为funcs这个lib库
add_library(character ${CHARACTER})

