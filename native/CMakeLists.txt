cmake_minimum_required(VERSION 3.20)
project(rtlsdr_jni C)

# --- JAVA / JNI ---
set(JAVA_HOME $ENV{JAVA_HOME})
set(JAVA_AWT_LIBRARY NotNeeded)

find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

# --- RTL-SDR (Homebrew) ---
find_path(RTLSDR_INCLUDE_DIR
    NAMES rtl-sdr.h
    PATHS /opt/homebrew/include
)

find_library(RTLSDR_LIBRARY
    NAMES rtlsdr
    PATHS /opt/homebrew/lib
)

if (NOT RTLSDR_INCLUDE_DIR OR NOT RTLSDR_LIBRARY)
    message(FATAL_ERROR "librtlsdr not found")
endif()

# --- JNI LIB ---
add_library(rtlsdr_jni SHARED rtlsdr_jni.c)

target_include_directories(rtlsdr_jni PRIVATE
    ${RTLSDR_INCLUDE_DIR}
)

target_link_libraries(rtlsdr_jni
    ${RTLSDR_LIBRARY}
)