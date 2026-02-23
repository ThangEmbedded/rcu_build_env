# universal_io_stm32g0b0

Dự án firmware STM32 cấu trúc chuẩn:
- app/: code chính
- platform/: code nền tảng
- components/: các thành phần mở rộng
- drivers/: driver phần cứng
- middleware/: phần mềm trung gian
- services/: dịch vụ
- tests/: kiểm thử
- docs/: tài liệu

Build:
1. mkdir build
2. cd build
3. cmake -G Ninja -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake ..
4. ninja
