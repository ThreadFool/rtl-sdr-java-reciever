cmake_minimum_required(VERSION 3.15)
project(rtlsdr_jni C)

find_package(JNI REQUIRED)

find_package(PkgConfig REQUIRED)

pkg_check_modules(RTLSDR REQUIRED librtlsdr)

pkg_check_modules(LIBUSB REQUIRED libusb-1.0)

add_library(rtlsdr_jni SHARED rtlsdr_jni.c)

target_include_directories(rtlsdr_jni PRIVATE
    ${JNI_INCLUDE_DIRS}
    ${RTLSDR_INCLUDE_DIRS}
    ${LIBUSB_INCLUDE_DIRS}
)

target_link_libraries(rtlsdr_jni
    ${RTLSDR_LIBRARIES}
    ${LIBUSB_LIBRARIES}
)