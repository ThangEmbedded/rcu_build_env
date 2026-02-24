
drivers/

# Embedded Gateway Architecture Contract

**Project Type:** STM32 Industrial Gateway  
**RTOS:** FreeRTOS  
**Protocols:** Modbus, MQTT, HTTP  
**Network:** Ethernet (LwIP)  
**Architecture Version:** 2.0  
**Last Updated:** 2026-02-23

---

## 1. Purpose

This document defines the mandatory architectural rules for this embedded project.

It ensures:
- Clear separation of concerns
- Hardware abstraction
- Scalability
- Portability
- Maintainability
- AI-readable structure
- Prevention of circular dependency

> All contributors must follow this contract strictly.

---

## 2. Layered Architecture Overview

```text
app
  ↓
services
  ↓
components
  ↓
drivers
  ↓
platform
    ├── pal
    ├── osal
    └── mcu
  ↓
STM32 HAL
```

> Dependency direction is strictly downward. Upward calls are forbidden.

---

## 3. Folder Structure Definition


```text
project_root/
├── app/
├── services/
├── components/
├── drivers/
├── platform/
│   ├── pal/
│   ├── osal/
│   ├── mcu/
│   └── bsp/   # Board Support Package: định nghĩa, cấu hình phần cứng, chân, board, đặc tả board
├── config/
├── third_party/
├── tests/
└── docs/
```

**bsp/** (Board Support Package):
- Chứa các file định nghĩa, cấu hình phần cứng, sơ đồ chân, thông tin board, đặc tả board cụ thể.
- Giúp tách biệt cấu hình board với phần code generic, hỗ trợ dễ dàng mở rộng cho nhiều loại board khác nhau.

---

## 4. Layer Responsibilities

### 4.1 APP Layer
**Location:** `app/`

**Role:**
- Entry point
- System initialization
- Dependency wiring
- Start services

**Allowed To Use:**
  - services

**Forbidden:**
  - drivers
  - components
  - pal
  - osal
  - STM32 HAL
  - hardware registers

> APP must remain thin.

### 4.2 SERVICES Layer
**Location:** `services/`

**Role:**
- Business logic
- Task loops
- State orchestration
- Queue management
- Retry & timeout handling
- Data flow between modules

**Allowed To Use:**
  - components
  - drivers
  - osal
  - config

**Forbidden:**
  - pal
  - STM32 HAL
  - register access
  - direct hardware manipulation

> Services define system behavior.

### 4.3 COMPONENTS Layer
**Location:** `components/`

**Role:**
- Reusable, platform-independent logic modules.

**Examples:**
  - Modbus core state machine
  - MQTT protocol core
  - HTTP parser
  - Flash manager
  - Message bus
  - CRC utilities
  - Ring buffer
  - Logger

**Allowed To Use:**
  - drivers
  - osal
  - config

**Forbidden:**
  - pal
  - STM32 HAL
  - hardware registers
  - service calls

> Components must be portable across MCU platforms.

### 4.4 DRIVERS Layer
**Location:** `drivers/`

**Role:**
- Hardware device abstraction.

**Includes:**
  - External IC drivers (PCA9555, NAND Flash)
  - Ethernet MAC driver
  - SPI Flash
  - ADC
  - UART abstraction if device-specific

> Drivers translate hardware registers into clean APIs.

**Allowed To Use:**
  - pal
  - config

**Forbidden:**
  - services
  - components
  - osal
  - STM32 HAL directly (must go through pal)
  - task creation
  - business logic

> Drivers must remain deterministic and lightweight.

### 4.5 PLATFORM Layer

#### 4.5.1 PAL (Platform Abstraction Layer)
**Location:** `platform/pal/`

**Role:**
- Wrapper over STM32 HAL.

**Examples:**
  - pal_uart
  - pal_spi
  - pal_i2c
  - pal_gpio
  - pal_eth

**Allowed To Use:**
  - STM32 HAL
  - CMSIS
  - hardware registers

**Forbidden:**
  - drivers
  - services
  - components
  - osal

> PAL isolates vendor dependency.

#### 4.5.2 OSAL (Operating System Abstraction Layer)
**Location:** `platform/osal/`

**Role:**
- RTOS abstraction.

**Examples:**
  - osal_task
  - osal_queue
  - osal_mutex
  - osal_timer

**Allowed To Use:**
  - FreeRTOS

**Forbidden:**
  - hardware access
  - STM32 HAL
  - drivers

> OSAL enables RTOS portability.

#### 4.5.3 MCU Layer
**Location:** `platform/mcu/`

**Role:**
- Startup code
- Clock configuration
- Interrupt vectors
- Linker script
- Board-specific only.

---

## 5. Peripheral Placement Rule

External hardware IC must be placed in `drivers/`.

| Peripheral      | Layer   |
|-----------------|---------|
| PCA9555         | drivers |
| NAND Flash      | drivers |
| Ethernet PHY    | drivers |
| SPI Flash       | drivers |

**Rule:**
> If it has registers and communicates via SPI/I2C/RMII/UART → it is a DRIVER.

---

## 6. Protocol & Network Placement Rule

| Module               | Layer      |
|----------------------|------------|
| Modbus state machine | components |
| Modbus polling task  | services   |
| MQTT core            | components |
| MQTT task            | services   |
| HTTP parser          | components |
| LwIP port adapter    | components |
| TCP client wrapper   | components |

> Protocol logic is NOT driver.

---

## 7. Dependency Rules (Strict)

**Allowed dependency chain:**

```text
app → services → components → drivers → pal → HAL
```

**Forbidden patterns:**
- Driver calling service
- Component calling service
- Service calling pal
- Component including STM32 HAL
- Driver including FreeRTOS
- PAL including drivers
- Circular include between modules

---

## 8. Include Rules

Each module must:
- Expose only public header in its folder
- Avoid cross-folder includes
- Avoid deep relative includes (`../../../../`)
- Public API only.

---

## 9. Configuration Rules

All configuration must be placed in `config/`.

**Examples:**
- modbus_config.h
- mqtt_config.h
- network_config.h
- board_config.h

> No magic numbers inside drivers or services.

---

## 10. Third Party Rules

All external libraries must remain untouched inside `third_party/`.

**Examples:**
- FreeRTOS
- LwIP
- mbedTLS

> Modifications must be wrapped, not edited directly.

---

## 11. Testing Rules

Unit tests must target:
- components
- drivers (mocked pal)
> Services can be integration-tested.

---

## 12. Architectural Violations

The following are considered critical violations:
- Upward dependency
- Direct HAL usage outside PAL
- Business logic inside driver
- RTOS usage inside driver
- Platform-specific code inside component

> Violations must be rejected in code review.

---

## 13. Design Philosophy

This architecture enforces:
- Hardware isolation
- Business logic isolation
- RTOS isolation
- Protocol modularity
- Portability to other MCU families
- Clean CI/CD integration
- AI-readable structure

---

## 14. Final Rule

If unsure where a module belongs:

Ask:
- Does it access hardware registers? → **DRIVER**
- Does it wrap STM32 HAL? → **PAL**
- Does it create tasks? → **SERVICE**
- Is it reusable logic? → **COMPONENT**
- Is it business orchestration? → **SERVICE**

If still unclear → escalate before implementation.

---

**End of Contract**

All contributors must follow this architecture strictly.  
Architecture violations may result in code rejection.