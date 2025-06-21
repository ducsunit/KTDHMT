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
├── main() - Initializes window, camera, lighting, and callbacks
├── init() - Sets initial display and lighting parameters
├── display() - Renders the entire beach scene
├── keyboard() - Handles movement and light toggle controls
├── passiveMouse() - Controls camera direction via mouse
│
├── 3D Scene Components:
│ ├── drawGround() - Draws terrain (sand, grass, sea)
│ ├── drawPalmTree() - Detailed palm tree (trunk & leaves)
│ ├── drawStreetLamp() - Street lamp + light bulb
│ ├── drawUmbrella() - Beach umbrella
│ ├── drawCubeChair() - Beach chair
│ ├── drawTable() - Table
│ ├── drawCarpet() - Beach mat
│ ├── drawPhao() - Floating buoy
│ ├── drawBeachBall() - Colorful beach ball
│ ├── drawWaterBottle() - Water bottle
│ ├── drawSnackBag() - Snack bag
│ ├── drawBucket() - Sand bucket
│ ├── drawShovel() - Shovel
│ ├── drawSurfboard() - Surfboard
│ ├── drawlaudaicat() - Sandcastle
│ ├── drawManyGrassTufts() - Grass tufts
│ ├── drawManyPebbles() - Pebbles
│
├── Lighting Functions:
│ ├── toggleLight() - Toggle global ambient light
│ ├── toggleLamp() - Toggle street lamp
│ ├── toggledhlight1() - Toggle directional sunlight
│ ├── setupLight() - Configure main light sources
│ └── setupLampLight() - Configure spotlight for lamp

```
