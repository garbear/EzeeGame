###########################################################################
# Arduino Toolchain. See https://github.com/queezythegreat/arduino-cmake
###########################################################################
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/arduino-cmake/cmake/ArduinoToolchain.cmake)

cmake_minimum_required(VERSION 2.8)

project(EzeeCube)

# If None is specified, the debug flag -g causes debug info to be included in the hex
set(CMAKE_BUILD_TYPE Release)

# Board configuration
set(ARDUINO_BOARD    leonardo)
set(ARCH             AVR8)
set(F_CPU            16000000)
set(F_USB            ${F_CPU})

# Options for flashing
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
	set(ARDUINO_DEFAULT_PORT "/dev/ttyACM0")
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
	set(ARDUINO_DEFAULT_PORT "/dev/tty.usbmodem1451")
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
	set(ARDUINO_DEFAULT_PORT )
endif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")

###########################################################################
# LUFA
###########################################################################
set(LUFA_ROOT ${PROJECT_SOURCE_DIR}/libraries/lufa)
set(LUFA_CORE_ROOT ${LUFA_ROOT}/LUFA/Drivers/USB/Core)

include_directories(${LUFA_ROOT})

set(LUFA_CORE_SRCS ConfigDescriptors.c
                   DeviceStandardReq.c
                   Events.c
                   # HostStandardReq.c
                   USBTask.c
                   ${ARCH}/Device_${ARCH}.c
                   ${ARCH}/Endpoint_${ARCH}.c
                   ${ARCH}/EndpointStream_${ARCH}.c
                   # ${ARCH}/Host_${ARCH}.c
                   # ${ARCH}/Pipe_${ARCH}.c
                   # ${ARCH}/PipeStream_${ARCH}.c
                   ${ARCH}/USBController_${ARCH}.c
                   ${ARCH}/USBInterrupt_${ARCH}.c
                   # Class/Common/HIDParser.c
)

foreach(f ${LUFA_CORE_SRCS})
    list(APPEND LUFA_CORE_SRCS_EXPANDED ${LUFA_CORE_ROOT}/${f})
    set_source_files_properties(${LUFA_CORE_ROOT}/${f}
                                PROPERTIES
                                COMPILE_FLAGS "-std=c99 -DF_USB=${F_USB}"
    )
endforeach(f ${LUFA_CORE_SRCS})

generate_avr_library(lufa-core-device
                     BOARD ${ARDUINO_BOARD}
                     SRCS ${LUFA_CORE_SRCS_EXPANDED}
)

###########################################################################
# EzeeGame
###########################################################################

# Hack so that Eclipse can find the pins_arduino.h file specific to the mega2560
# The "mega" part of this directory is determined by looking in boards.txt (see
# the arduino sdk path) and finding the boardID.build.variant setting.
#include_directories("${ARDUINO_VARIANTS_PATH}/mega2560")

# Public include files so that programs can interface with the Arduino hardware
#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# Local include files so that public include files can find their referenced classes
#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

# Tell CMake where to search for libraries use the link_directories command.
# The command has to be used before defining any firmware or libraries
# requiring those libraries. An Arduino library is ***any directory which
# contains a header named after the directory.***
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Weffc++ -pedantic -std=c++0x")

set(EZEEGAME_SRCS src/main.cpp
                  src/EzeeGameMaster.cpp
)

generate_arduino_firmware(ezeegame
    BOARD ${ARDUINO_BOARD}
    SRCS ${EZEEGAME_SRCS}
    LIBS lib/main_lib
    LIBS lufa-core-device
)
