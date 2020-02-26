cmake_minimum_required (VERSION 3.10)
project(CppHL VERSION 0.0.1 LANGUAGES C CXX)

set(SRC lexer.cpp
        main.cpp)

set(BSTRING_SRC bstrlib/bsafe.c
                bstrlib/bstraux.c
                bstrlib/bstrlib.c
                bstrlib/bstrwrap.cpp
                bstrlib/buniutil.c
                bstrlib/utf8util.c)

add_executable(hl ${SRC} ${BSTRING_SRC})

target_include_directories(hl PUBLIC ${PROJECT_SOURCE_DIR})