
# Universal IO – STM32G0B0 Firmware

## Overview
This project uses:

- **CMake**
- **Ninja**
- **GNU Arm Embedded Toolchain**
- **STM32 HAL** (generated from CubeMX – not IDE dependent)

> **No CubeIDE required.**

---

## 📦 Requirements

Before building, install the following tools:

### 1. GNU Arm Toolchain
- Download: [Arm GNU Toolchain](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)
- Verify installation:
	```sh
	arm-none-eabi-gcc --version
	```

### 2. CMake (>= 3.22)
- Download: [CMake](https://cmake.org/download/)
- Verify installation:
	```sh
	cmake --version
	```

### 3. Ninja
- Download: [Ninja](https://ninja-build.org/)
- Verify installation:
	```sh
	ninja --version
	```

---

## 🛠 Build Instructions

### 1. Clone repository
```sh
git clone <repo_url>
cd universal_io
```

### 2. Configure project
```sh
cmake -S . -B build ^
	-G Ninja ^
	-DCMAKE_TOOLCHAIN_FILE=toolchain.cmake ^
	-DCMAKE_BUILD_TYPE=Debug
```

### 3. Build firmware
```sh
cmake --build build
```

---

## 📂 Build Output

After successful build:

```
build/
 ├── universal_io.elf
 ├── universal_io.hex
 └── universal_io.bin
```

---

## 🔥 Flash Firmware (Optional)

Using STM32CubeProgrammer CLI:
```sh
STM32_Programmer_CLI -c port=SWD -w build/universal_io.hex -v -rst
```

---

## 🧠 Project Structure

```
universal_io/
 ├── app/                    # Application layer
 ├── platform/
 │   └── stm32_g0b0/         # BSP + HAL (CubeMX generated)
 ├── toolchain.cmake
 ├── CMakeLists.txt
 └── README.md
```

---

## ⚙ Build Configuration

- Debug:   `-DCMAKE_BUILD_TYPE=Debug`
- Release: `-DCMAKE_BUILD_TYPE=Release`

---

## 🧩 Clean Build

```sh
rm -rf build
# or on Windows PowerShell:
Remove-Item -Recurse -Force build
```

---

## 🏗 Architecture Overview

```
Application Layer
	 ↓
BSP (STM32 HAL)
	 ↓
CMSIS
	 ↓
Startup + Linker Script
```

CMake controls the entire build system.

---

## 🚀 Maintainer Notes

- Do not edit CubeMX generated files manually
- Regenerate HAL only when hardware configuration changes
- CMake build system is independent from CubeIDE