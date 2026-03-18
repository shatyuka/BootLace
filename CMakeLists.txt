cmake_minimum_required(VERSION 3.20)

project(BootLace)

add_subdirectory(edk2)

edk2_add_package(BootLace BootLace.dsc)
