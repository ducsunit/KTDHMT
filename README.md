# 🌴 Beach Scene with OpenGL

This is a 3D beach scene simulation program built using OpenGL (GLUT).  
It renders a vibrant environment including sun, sea, sand, trees, recreational items, and custom lighting effects.

---

## 🧰 Technologies Used

- **Language:** C++
- **Graphics:** OpenGL + GLUT
- **Lighting Effects:** GL_LIGHT0, GL_LIGHT1, GL_LIGHT2
- **Geometry:** Basic shapes such as cubes, spheres, cylinders, cones, and torus

---

## 🏝️ Scene Elements

- **Sun** ☀️  
- **Sea, sand, grass**  
- **Palm trees**  
- **Beach umbrellas**  
- **Buoys**  
- **Beach balls**  
- **Tables, chairs, mats**  
- **Street lamps (can toggle on/off)**  
- **Sandcastle** 🏰  
- **Snacks, water bottles, buckets, shovels**  
- **Surfboards**  
- **Scattered grass and pebbles**  
- **X, Y, Z coordinate axes for reference**

---

## 🔦 Key Features

- **Mouse-controlled camera view** (look around with `yaw`, `pitch`)
- **Free movement using keyboard**:  
  - `W`, `A`, `S`, `D`: move forward, left, backward, right  
  - `Q`, `E`: move up/down
- **Toggle lighting modes**:  
  - `1` or `mt`: toggle ambient light  
  - `2` or `den`: toggle street lamp  
  - `3` or `dh`: toggle directional sunlight
- **Transparent water and realistic lighting simulation**

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
