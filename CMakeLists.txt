cmake_minimum_required (VERSION 3.8)

project (ZOSH LANGUAGES C CXX)

set (SRC_UTILS

    ./utils/pool.hxx
    ./utils/treap.hxx

)

set (SRC_I_PRO_B_L1

    ./i-pro-b/l1/l1.cxx
    ./i-pro-b/l1/l1.hxx

    # ./i-pro-b/l1/prob/f1.cxx
)

set (SRC_I_PRO_B_L2

    ./i-pro-b/l2/l2.cxx
    ./i-pro-b/l2/l2.hxx

    # ./i-pro-b/l2/prob/a2.cxx
    # ./i-pro-b/l2/prob/b2.cxx
)

set (SRC_I_PRO_B_L3

    ./i-pro-b/l3/l3.cxx
    ./i-pro-b/l3/l3.hxx

    # ./i-pro-b/l3/prob/a3.cxx
)

set (SRC_I_PRO_B_L4

    ./i-pro-b/l4/l4.cxx
    ./i-pro-b/l4/l4.hxx

    # ./i-pro-b/l4/prob/a4.cxx
    # ./i-pro-b/l4/prob/b4.cxx
    # ./i-pro-b/l4/prob/d4.cxx
)

set (SRC_I_PRO_B_L5

    ./i-pro-b/l5/l5.cxx
    ./i-pro-b/l5/l5.hxx

)

set (SRC_I_PRO_B_L6

    ./i-pro-b/l6/l6.cxx
    ./i-pro-b/l6/l6.hxx

)

add_executable (ZOSH 
    main.cxx
    # ${SRC_UTILS}
)

target_include_directories (ZOSH PUBLIC ./)
target_compile_features (ZOSH PUBLIC cxx_std_17)
target_precompile_headers (ZOSH PUBLIC pch.hxx)
