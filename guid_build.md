
# Hướng dẫn build & debug project chi tiết

## 1. Các tool cần chuẩn bị và cài đặt

### 1.1. Git
- Tải tại: https://git-scm.com/downloads
- Cài đặt theo hướng dẫn trên website.
- Kiểm tra cài đặt:
  ```sh
  git --version
  ```

### 1.2. Ninja
- Tải tại: https://ninja-build.org/
- Giải nén và thêm vào PATH.
- Kiểm tra cài đặt:
  ```sh
  ninja --version
  ```

### 1.3. CMake (>=3.20)
- Tải tại: https://cmake.org/download/
- Cài đặt và thêm vào PATH.
- Kiểm tra cài đặt:
  ```sh
  cmake --version
  ```

### 1.4. ARM GCC toolchain (gcc-arm-none-eabi)
- Tải tại: https://developer.arm.com/downloads/-/gnu-rm
- Cài đặt và thêm vào PATH.
- Kiểm tra cài đặt:
  ```sh
  arm-none-eabi-gcc --version
  ```

### 1.5. Visual Studio Code (VS Code)
- Tải tại: https://code.visualstudio.com/
- Cài đặt các extension:
  - C/C++ (ms-vscode.cpptools)
  - Cortex-Debug (marus25.cortex-debug)
  - CMake Tools (ms-vscode.cmake-tools)

## 2. Các bước kiểm tra môi trường
1. Mở terminal/cmd, kiểm tra các tool đã cài đủ chưa:
   ```sh
   git --version
   ninja --version
   cmake --version
   arm-none-eabi-gcc --version
   ```
2. Nếu thiếu tool nào, cài đặt lại theo hướng dẫn ở trên.

## 3. Các bước setup ban đầu để build
1. Clone project về máy:
   ```sh
   git clone <repo-url>
   ```
2. Mở VS Code, chọn "Open Folder" tới thư mục project vừa clone.
3. Tạo thư mục build và chuyển vào đó:
   ```sh
   mkdir build && cd build
   ```
4. Cấu hình project với CMake:
   ```sh
   cmake -G Ninja -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake ..
   ```
   - Nếu dùng VS Code, có thể chọn preset hoặc chỉnh sửa file CMakePresets.json nếu cần.
5. Build project:
   ```sh
   ninja
   ```
   - Hoặc dùng nút Build của extension CMake Tools trong VS Code.

## 4. Hướng dẫn debug
1. Đảm bảo đã cài extension Cortex-Debug.
2. Kết nối board qua ST-Link hoặc J-Link.
3. Kiểm tra file `.vscode/launch.json` đã đúng cấu hình (đã có mẫu trong repo, chỉnh sửa nếu cần).
4. Chọn cấu hình debug phù hợp trong VS Code (góc trái trên cùng).
5. Nhấn F5 để bắt đầu debug.
6. Có thể đặt breakpoint, xem giá trị biến, step code trực tiếp trên VS Code.

## 5. Một số lỗi thường gặp & cách xử lý
- Thiếu tool: Kiểm tra lại PATH, cài đặt đúng phiên bản.
- Không nhận board debug: Kiểm tra driver ST-Link/J-Link, thử cắm lại cáp.
- Build lỗi: Đọc kỹ log, kiểm tra lại các bước cấu hình CMake.

---
Nếu gặp lỗi hoặc cần thêm hướng dẫn, xem README.md hoặc liên hệ maintainer.