add_library(oscillators STATIC oscillator.cpp sine.cpp saw.cpp square.cpp triangle.cpp)
target_compile_features(oscillators PUBLIC cxx_std_20)
target_include_directories(oscillators PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})