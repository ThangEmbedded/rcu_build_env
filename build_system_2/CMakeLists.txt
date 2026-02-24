cmake_minimum_required(VERSION 3.22)

project(universal_io C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# =============================
# MCU CONFIG
# =============================
set(MCU_FLAGS
    -mcpu=cortex-m0plus
    -mthumb
)

# =============================
# COMPILE OPTIONS
# =============================
add_compile_options(
    ${MCU_FLAGS}
    -Wall
    -O0
    -g3
    -ffunction-sections
    -fdata-sections
)

# =============================
# DEFINES
# =============================
add_compile_definitions(
    STM32G0B0xx
    USE_HAL_DRIVER
)

# =============================
# INCLUDE PATHS
# =============================
include_directories(
    platform/mcu/stm32g0b0/Inc
    platform/mcu/stm32g0b0/Drivers/STM32G0xx_HAL_Driver/Inc
    platform/mcu/stm32g0b0/Drivers/STM32G0xx_HAL_Driver/Inc/Legacy
    platform/mcu/stm32g0b0/Drivers/CMSIS/Include
    platform/mcu/stm32g0b0/Drivers/CMSIS/Device/ST/STM32G0xx/Include
)

# =============================
# HAL SOURCES
# =============================
file(GLOB_RECURSE HAL_SOURCES
    platform/mcu/stm32g0b0/Drivers/STM32G0xx_HAL_Driver/Src/*.c
)

file(GLOB_RECURSE CORE_SOURCES
    platform/mcu/stm32g0b0/Src/*.c
)

# =============================
# EXECUTABLE
# =============================
add_executable(${PROJECT_NAME}.elf
    app/app_main.c
    ${HAL_SOURCES}
    ${CORE_SOURCES}
    platform/mcu/stm32g0b0/startup_stm32g0b0xx.s
)

# =============================
# LINKER
# =============================
target_link_options(${PROJECT_NAME}.elf PRIVATE
    ${MCU_FLAGS}
    -T${CMAKE_SOURCE_DIR}/platform/mcu/stm32g0b0/STM32G0B0XX_FLASH.ld
    -Wl,--gc-sections
)

# ==========================================
# Generate .hex and .bin
# ==========================================
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex
        $<TARGET_FILE:${PROJECT_NAME}.elf>
        ${PROJECT_NAME}.hex

    COMMAND ${CMAKE_OBJCOPY} -O binary
        $<TARGET_FILE:${PROJECT_NAME}.elf>
        ${PROJECT_NAME}.bin

    COMMENT "Generating HEX and BIN files"
)