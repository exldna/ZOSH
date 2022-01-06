cmake_minimum_required (VERSION 3.8)

project (ZOSH LANGUAGES CXX)

set (SRC_I_PRO_B 
    ./i-pro-b/l1.cxx
    ./i-pro-b/l1.hxx
)

add_executable (ZOSH 
    main.cxx
    ${SRC_I_PRO_B}
)

target_include_directories (ZOSH PUBLIC ./)
target_compile_features (ZOSH PUBLIC cxx_std_17)
