cmake_minimum_required(VERSION 3.22)

project(universal_io_stm32g0b0 C ASM)

add_compile_definitions(
    STM32G0B0xx
    USE_HAL_DRIVER
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(MCU_FLAGS
    -mcpu=cortex-m0plus
    -mthumb
)

add_compile_options(
    ${MCU_FLAGS}
    -Wall
    -ffunction-sections
    -fdata-sections
)

set(BSP_PATH ${CMAKE_SOURCE_DIR}/platform/stm32g0b0)

add_link_options(
    ${MCU_FLAGS}
    -T${BSP_PATH}/STM32G0B0XX_FLASH.ld
    --specs=nosys.specs
    -Wl,--gc-sections
)

include_directories(
    app
    ${BSP_PATH}/Inc
    ${BSP_PATH}/Drivers/CMSIS/Include
    ${BSP_PATH}/Drivers/CMSIS/Device/ST/STM32G0xx/Include
    ${BSP_PATH}/Drivers/STM32G0xx_HAL_Driver/Inc
)

file(GLOB HAL_SOURCES
    ${BSP_PATH}/Drivers/STM32G0xx_HAL_Driver/Src/*.c
)

file(GLOB BSP_SOURCES
    ${BSP_PATH}/Src/*.c
)

set(SOURCES
    app/app_main.c
    ${BSP_PATH}/startup_stm32g0b0xx.s
    ${BSP_SOURCES}
    ${HAL_SOURCES}
)

set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/output)
file(MAKE_DIRECTORY ${OUTPUT_DIR})

add_executable(${PROJECT_NAME}.elf ${SOURCES})

set_target_properties(${PROJECT_NAME}.elf PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)

find_program(OBJCOPY arm-none-eabi-objcopy REQUIRED)
find_program(SIZE arm-none-eabi-size REQUIRED)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${SIZE} ${OUTPUT_DIR}/${PROJECT_NAME}.elf
    COMMAND ${OBJCOPY} -O binary  ${OUTPUT_DIR}/${PROJECT_NAME}.elf ${OUTPUT_DIR}/${PROJECT_NAME}.bin
    COMMAND ${OBJCOPY} -O ihex    ${OUTPUT_DIR}/${PROJECT_NAME}.elf ${OUTPUT_DIR}/${PROJECT_NAME}.hex
)

target_compile_options(${PROJECT_NAME}.elf PRIVATE
    -g3
    -O0
)
