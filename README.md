
# 🌴 Beach Scene with OpenGL

Đây là một chương trình mô phỏng cảnh bãi biển 3D sử dụng thư viện OpenGL (GLUT). Chương trình hiển thị một khung cảnh phong phú bao gồm mặt trời, biển, cát, cây cối, đồ vật vui chơi, và hệ thống ánh sáng tùy chỉnh.

---

## 🧰 Công nghệ sử dụng

- **Ngôn ngữ:** C++
- **Đồ họa:** OpenGL + GLUT
- **Hiệu ứng ánh sáng:** GL_LIGHT0, GL_LIGHT1, GL_LIGHT2
- **Hiệu ứng hình học:** sử dụng các khối cơ bản như cube, sphere, cylinder, cone, torus...

---

## 🏝️ Các thành phần trong cảnh

- **Mặt trời** ☀️
- **Biển, cát, cỏ**
- **Cây dừa**
- **Ô che nắng**
- **Phao**
- **Quả bóng bãi biển**
- **Bàn, ghế, thảm**
- **Đèn đường có thể bật/tắt**
- **Lâu đài cát 🏰**
- **Snack, chai nước, xô, xẻng**
- **Ván lướt sóng**
- **Cỏ và sỏi rải rác**
- **Hệ tọa độ X, Y, Z để kiểm tra**

---

## 🔦 Tính năng nổi bật

- **Điều khiển camera bằng chuột** (nhìn xung quanh bằng `yaw`, `pitch`)
- **Di chuyển tự do bằng bàn phím**: 
  - `W`, `A`, `S`, `D`: tiến, trái, lùi, phải
  - `Q`, `E`: bay lên/xuống
- **Tùy chỉnh ánh sáng**:
  - `1` hoặc `mt`: bật/tắt ánh sáng môi trường
  - `2` hoặc `den`: bật/tắt đèn đường
  - `3` hoặc `đh`: bật/tắt ánh sáng định hướng từ mặt trời
- **Hiệu ứng nước trong suốt và ánh sáng mô phỏng thực tế**

---

## 📁 Cấu trúc file

```
beach.cpp
│
├── Hàm `main` - Khởi tạo cửa sổ, camera, ánh sáng và các callback
├── init() - Thiết lập chế độ hiển thị và ánh sáng ban đầu
├── display() - Hàm vẽ toàn bộ khung cảnh bãi biển
├── keyboard() - Xử lý điều khiển di chuyển và bật/tắt ánh sáng
├── passiveMouse() - Điều khiển hướng nhìn bằng chuột
│
├── Các khối cảnh 3D:
│   ├── drawGround()        - Vẽ nền gồm đất, cỏ, cát và biển
│   ├── drawPalmTree()      - Cây dừa chi tiết gồm thân và lá
│   ├── drawStreetLamp()    - Cột đèn đường + bóng đèn
│   ├── drawUmbrella()      - Ô che nắng
│   ├── drawCubeChair()     - Ghế nằm bãi biển
│   ├── drawTable()         - Bàn
│   ├── drawCarpet()        - Thảm
│   ├── drawPhao()          - Phao nổi
│   ├── drawBeachBall()     - Quả bóng bãi biển nhiều màu
│   ├── drawWaterBottle()   - Chai nước
│   ├── drawSnackBag()      - Túi snack
│   ├── drawBucket()        - Cái xô
│   ├── drawShovel()        - Cái xẻng
│   ├── drawSurfboard()     - Ván lướt sóng
│   ├── drawlaudaicat()     - Lâu đài cát
│   ├── drawManyGrassTufts() - Cỏ
│   ├── drawManyPebbles()   - Sỏi đá
│
├── Các hàm ánh sáng:
│   ├── toggleLight()       - Bật/tắt ánh sáng chung
│   ├── toggleLamp()        - Bật/tắt đèn đường
│   ├── toggledhlight1()    - Bật/tắt ánh sáng định hướng
│   ├── setupLight()        - Thiết lập nguồn sáng chính/phụ
│   └── setupLampLight()    - Thiết lập đèn đường (spotlight)
```

---

## 📸 Gợi ý ảnh minh họa

*(Bạn có thể thêm ảnh chụp màn hình khi chạy chương trình để minh họa các vật thể đã dựng.)*
