# Hướng dẫn build & debug project

## 1. Các tool cần chuẩn bị
- Git
- Ninja
- CMake (>=3.20)
- ARM GCC toolchain (gcc-arm-none-eabi)
- VS Code (khuyến nghị) với các extension:
  - C/C++
  - Cortex-Debug
  - CMake Tools

## 2. Cách setup ban đầu để build
1. Clone project về máy:
   ```sh
   git clone <repo-url>
   ```
2. Cài đặt các tool ở trên (nếu chưa có).
3. Mở project bằng VS Code hoặc terminal.
4. Tạo thư mục build và chuyển vào đó:
   ```sh
   mkdir build && cd build
   ```
5. Cấu hình project với CMake:
   ```sh
   cmake -G Ninja -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake ..
   ```
6. Build project:
   ```sh
   ninja
   ```
   Hoặc dùng CMake Tools extension trong VS Code (nút Build).

## 3. Cách debug
- Sử dụng VS Code với extension Cortex-Debug.
- Cấu hình file `.vscode/launch.json` cho debug (đã có mẫu trong repo).
- Kết nối board qua ST-Link hoặc J-Link.
- Chọn cấu hình debug và nhấn F5 để bắt đầu debug.

---
Nếu gặp lỗi hoặc cần thêm hướng dẫn, xem README.md hoặc liên hệ maintainer.