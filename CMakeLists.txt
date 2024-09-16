cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# obstacle_detection プロジェクトの作成
# このプロジェクトは C 言語、C++ 言語、アセンブリ言語を使用
project(obstacle_detection C CXX ASM)
# CMAKE_C_STANDARD 変数を生成 値は 11
set(CMAKE_C_STANDARD 11)
# CMAKE_CXX_STANDARD 変数を生成 値は 17
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# ディレクトリの libmicroros をリンク
# libmicroros ディレクトリを検索パスに追加
link_directories(
    include/libmicroros
    include/obstacle-detection
    )

# obstacle_detection という実行ファイルの作成
# main.c と pico_uart_transport.c から作成
add_executable(obstacle_detection
    src/main.c
    src/pico_uart_transport.c
    )

# pico_stdlib, microros, hardware_adc がリンク
target_link_libraries(obstacle_detection
    pico_stdlib
    microros
    hardware_adc
    )

# obstacle_detection に libmicroros/include というインクルードディレクトリを設定
target_include_directories(obstacle_detection PUBLIC
    include/libmicroros/include
    include/obstacle-detection
    )

# 変数の設定
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections")

# PICO の機能設定
pico_enable_stdio_usb(obstacle_detection 1)
pico_enable_stdio_uart(obstacle_detection 0)
add_compile_definitions(PICO_UART_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_DEFAULT_CRLF=0)

# UF2 を作成
pico_add_extra_outputs(obstacle_detection)

