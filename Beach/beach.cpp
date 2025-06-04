#include "glut.h"
#include <cmath>
#include <cstdlib>


// --- Cấu hình camera ---
const float S = 20.0f;
float eyeX = 0, eyeY = 1.2f * S, eyeZ = 0;
float yaw = 0, pitch = 0;
const float speed = 2.0f;
const float sensitivity = 0.009f;
bool firstMouse = true;
int lastX, lastY;
bool lightEnabled = false;
bool lampEnabled = false;
bool dhlight1 = false;

void toggleLight() {
    lightEnabled = !lightEnabled;
    if (lightEnabled) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        glEnable(GL_COLOR_MATERIAL);

        glClearColor(0.4f, 0.8f, 1.0f, 1.0f);
    }
    else {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);

        glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
    }
    glutPostRedisplay();
}
void toggledhlight1() {
    dhlight1 = !dhlight1;
    if (dhlight1) {
        glEnable(GL_LIGHT1);
    }
    else {
        glDisable(GL_LIGHT1);
    }
    glutPostRedisplay();
}

void toggleLamp() {
    lampEnabled = !lampEnabled;
    if (lampEnabled) {
        glEnable(GL_LIGHT2);
    }
    else {
        glDisable(GL_LIGHT2);
    }
    glutPostRedisplay();
}

void setupLight() {
    // Thiết lập nguồn sáng chính
    GLfloat light0_pos[] = { 0.0f, 20.0f, 20.0f, 1.0f };
    GLfloat light0_ambient[] = { 0.6f, 0.4f, 0.2f, 1.0f };
    GLfloat light0_diffuse[] = { 1.0f, 0.9f, 0.7f, 1.0f };
    GLfloat light0_specular[] = { 1.0f, 1.0f, 0.8f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

    // Nguồn sáng phụ dịu(định hướng)
    GLfloat light1_pos[] = { -10.0f, 5.0f, -10.0f, 0.0f };
    GLfloat light1_diffuse[] = { 0.4f, 0.2f, 0.25f, 1.0f };

    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
}
//ánh sáng đèn
void setupLampLight() {
    /*glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT2);*/
    // Vì đèn đường được biến đổi bởi:
    // glTranslatef(-19, 1, -29); glRotated(-90, 0, 1, 0); glScalef(5, 5, 5);
    // nên ta áp dụng các phép biến đổi đó khi đặt vị trí và hướng của ánh sáng.
    glPushMatrix();
    glTranslatef(-19.0f, 1.0f, -29.0f);
    glRotated(-90.0, 1.0, 0, 0.0);
    glScalef(5.0f, 5.0f, 5.0f);
    // Vị trí của bóng đèn trong hệ tọa độ của mô hình đèn đường (w = 1.0 → light position)
    GLfloat lampPos[] = { 0.7f, 2.9f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT2, GL_POSITION, lampPos);

    // Thiết lập spotlight: chiếu hướng từ bóng đèn xuống dưới (có thể điều chỉnh theo ý bạn)
    GLfloat spotDir[] = { 0.0f, 1.0f, 0.0f }; // chiếu xuống dưới
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDir);

    // Thiết lập góc cắt cho chùm tia: giá trị nhỏ để tạo nên chùm tia hẹp
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 10);  // chỉ 10 độ
    // Độ tập trung cao giúp ánh sáng càng tập trung vào trung tâm chùm tia
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 80.0f);
    glPopMatrix();
    // Cài đặt màu cho ánh sáng
    GLfloat lampAmbient[] = { 0.0f, 0.0f, 0.2f, 0.0f }; // môi trường: xanh đậm
    GLfloat lampDiffuse[] = { 0.0f, 0.0f, 1.0f, 1.0f }; // khuếch tán: xanh sáng
    GLfloat lampSpecular[] = { 0.2f, 0.2f, 1.0f, 1.0f }; // phản xạ: xanh nhạt

    glLightfv(GL_LIGHT2, GL_AMBIENT, lampAmbient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lampDiffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, lampSpecular);
    // Áp dụng các hệ số suy giảm cường độ ánh sáng theo khoảng cách
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.2f);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.05f);
}
// --- Khởi tạo OpenGL ---
void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 800.0 / 600.0, 0.1, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.4f, 0.8f, 1.0f, 1.0f);  //blue xanh
    toggleLight();
	toggleLamp();
}

//lập phương tam giác vuông góc
void drawRightTriangularPrism(float base, float height, float depth) {
    // Đáy tam giác vuông nằm trên mặt phẳng XZ, chiều sâu theo trục Y
    float halfDepth = depth / 2.0f;
    glBegin(GL_TRIANGLES);
    // Mặt trước (tam giác vuông)
    glVertex3f(0.0f, 0.0f, halfDepth);     // góc vuông
    glVertex3f(base, 0.0f, halfDepth);     // cạnh đáy
    glVertex3f(0.0f, height, halfDepth);   // cạnh cao
    // Mặt sau (tam giác vuông)
    glVertex3f(0.0f, 0.0f, -halfDepth);
    glVertex3f(0.0f, height, -halfDepth);
    glVertex3f(base, 0.0f, -halfDepth);
    glEnd();
    glBegin(GL_QUADS);
    // Mặt đáy (hình chữ nhật dưới đáy)
    glVertex3f(0.0f, 0.0f, halfDepth);
    glVertex3f(0.0f, 0.0f, -halfDepth);
    glVertex3f(base, 0.0f, -halfDepth);
    glVertex3f(base, 0.0f, halfDepth);
    // Mặt bên thẳng đứng (vuông góc với đáy)
    glVertex3f(0.0f, 0.0f, halfDepth);
    glVertex3f(0.0f, height, halfDepth);
    glVertex3f(0.0f, height, -halfDepth);
    glVertex3f(0.0f, 0.0f, -halfDepth);
    // Mặt nghiêng (cạnh huyền tam giác vuông)
    glVertex3f(0.0f, height, halfDepth);
    glVertex3f(0.0f, height, -halfDepth);
    glVertex3f(base, 0.0f, -halfDepth);
    glVertex3f(base, 0.0f, halfDepth);
    glEnd();
}
//mặt trời
void drawSun() {
    glPushMatrix();
    glColor3f(1.0f, 0.7f, 0.0f);
    glutSolidSphere(2.0, 50, 50);
    glPopMatrix();
}
//đèn đường
void drawStreetLamp() {
    // Thân cột
    glPushMatrix();
    glColor3f(0.8f, 0.2f, 0.2f);
    glTranslatef(0.0f, 1.5f, 0.0f);
    glScalef(0.1f, 3.0f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();
    // Cột nối chao đèn
    glPushMatrix();
    glColor3f(0.8f, 0.2f, 0.2f);
    glTranslatef(0.25f, 3.0f, 0.0f);
    glScalef(0.61f, 0.08f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.275f, 2.85f, 0.0f);
    glRotatef(33.7f, 0.0f, 0.0f, 1.0f);
    glScalef(0.54f, 0.08f, 0.08f);
    glColor3f(0.8, 0.2, 0.2);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Chao đèn
    glPushMatrix();
    glColor3f(0.3, 0.2, 0.2);
    glTranslatef(0.7f, 3.0f, 0.0f);
    glScalef(2.3, 1, 1.5);
    glutSolidSphere(0.1, 20, 20);
    glPopMatrix();
    // Bóng đèn
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.8f); // Màu vàng nhạt
    glTranslatef(0.7f, 2.9f, 0.0f);
    glutSolidSphere(0.07f, 20, 20);
    glPopMatrix();
}
//cỏ - cát - biển
void drawGround() {
    glPushMatrix();
    glColor3f(0.5f, 0.35f, 0.15f); // Màu nâu đất
    glTranslatef(0, -0.7f, 0);
    glScalef(3 * S, 0.5, 3 * S);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Grass
    glPushMatrix();
    glColor3f(0.0f, 0.6f, 0.0f);
    glTranslatef(0, 0.01f, -S);
    glScalef(3 * S, 1, S);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Sand
    glPushMatrix();
    glColor3f(0.96f, 0.87f, 0.70f);
    glScalef(3.0f * S, 1, S);
    glutSolidCube(1.0f);
    glPopMatrix();
    //phan duoi
    glPushMatrix();
    glColor3f(1.0f, 0.5f, 0.2f);  // Màu cam nhạt
    glTranslatef(0, -0.55, 10);
    glScalef(3 * S, 0.7, 2);
    glRotatef(-90, 0, 1, 0);
    drawRightTriangularPrism(2.0f, 1.5f, 1.0f);
    glPopMatrix();

    // Biển
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPushMatrix();
    glTranslatef(0, 0.02f, S);
    glScalef(3 * S, 1, S);
    glColor4f(0.2f, 0.5f, 0.9f, 0.5f); // màu nước trong suốt
    glutSolidCube(1.0f);
    glPopMatrix();
    glDisable(GL_BLEND);
}
//Cây dừa
void drawPalmTrunkBase(float height, float radius, int slices) {
    glPushMatrix();
    glColor3f(0.4f, 0.2f, 0.0f);  // Nâu đậm
    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, radius, radius * 0.95, height, slices, 1); // hơi thu nhỏ ở đầu
    glTranslatef(0, 0, height);
    gluDeleteQuadric(quad);
    glPopMatrix();
}
void drawPalmBaseSection() {
    float segmentHeight = 0.4f;
    float baseRadius = 0.4f;
    for (int i = 0; i < 3; i++) {
        drawPalmTrunkBase(segmentHeight, baseRadius, 20);
        glTranslatef(0, 0, segmentHeight);
        baseRadius *= 0.98f;  // thu nhỏ nhẹ để tự nhiên
    }
}
void drawPalmTrunkMiddle(float totalHeight, float startRadius, float endRadius, int segments) {
    float heightStep = totalHeight / segments;
    float radiusStep = (startRadius - endRadius) / segments;
    for (int i = 0; i < segments; i++) {
        float currentRadius = startRadius - i * radiusStep;
        drawPalmTrunkBase(heightStep, currentRadius, 16);
        glTranslatef(0, 0, heightStep);
    }
}
void drawPalmTopBase(float height, float baseRadius, float topRadius) {
    glPushMatrix();
    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, baseRadius, topRadius, height, 16, 1);
    glTranslatef(0, 0, height);
    gluDeleteQuadric(quad);
    glPopMatrix();
}
void drawPalmLeaf(float length, float curveAngle, float width) {
    glPushMatrix();
    glColor3f(0.1f, 0.5f, 0.1f);

    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= 9; i++) {
        float t = i / 10.0f;
        float angle = curveAngle * t;

        // Điều chỉnh vị trí X theo một hàm phi tuyến tính để làm phần giữa to hơn
        float x = length * t + sin(t * 3.14) * 0.2f;

        //  Làm phần giữa rộng hơn bằng cách tăng biến đổi theo t
        float y = sin(angle * 3.14 / 180.0f) * 0.8f;
        float scaledWidth = width * (2 + sin(t * 3.14) * 0.5f);
        //  Điểm cuối cùng được điều chỉnh để tạo đầu nhọn
        float finalX = length + 0.1f;  // Dịch nhẹ về X để nhọn hơn
        float finalY = sin(curveAngle * 3.14 / 180.0f) * 0.6f; // Nhọn hơn chút
        glVertex3f(finalX, finalY, 0.0f);

        glVertex3f(x, y, -scaledWidth / 2);
        glVertex3f(x, y, scaledWidth / 2);
    }
    glEnd();

    glPopMatrix();
}
void drawPalmLeaves(int numLeaves = 8) {
    for (int i = 0; i < numLeaves; i++) {
        glPushMatrix();
        glRotatef(360.0f / numLeaves * i, 0, 0, 1);  // xoay đều
        glRotatef(-60, 1, 0, 0);                    // nghiêng xuống
        drawPalmLeaf(2.5f, 30.0f, 0.3f);            // cong nhẹ
        glPopMatrix();
    }
}
void drawPalmTree() {
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    // Thân dưới
    drawPalmBaseSection();

    // Thân giữa
    drawPalmTrunkMiddle(4.0f, 0.35f, 0.2f, 10);

    // Bệ lá
    glPushMatrix();
    glColor3f(0.45f, 0.2f, 0.1f);
    drawPalmTopBase(0.4f, 0.2f, 0.3f);
    glPopMatrix();

    // Chùm lá
    drawPalmLeaves(9);

    glPopMatrix();
}
//Ô
void drawUmbrella(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0, z);
    // Cột
    glColor3f(0.7f, 0.7f, 0.7f);
    GLUquadric* q = gluNewQuadric();
    glPushMatrix();
    glTranslatef(0, 1, 0);
    glScalef(1, 1.9, 1);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(q, 0.1, 0.1, 4, 8, 8);
    glPopMatrix();
    // Dù    
    glPushMatrix();
    glColor3f(1.0f, 0.3f, 0.3f);
    glTranslatef(0, 7, 0);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(4, 2, 10, 2);
    glPopMatrix();
    gluDeleteQuadric(q);
    glPopMatrix();
}
//phao
void drawPhao() {
    glColor3f(0.0f, 0.5f, 1.0f);
    glPushMatrix();
    glTranslatef(-2.5f, 1.0, 0.0f);
    glRotatef(90, 3.0, 0.0, 0.0);
    glScalef(1.9f, 1, 1);
    glutSolidTorus(0.32, 0.65, 10, 35);
    glPopMatrix();
}
//cái ghế 
void drawCubeChair() {
    //mat duoi
    glColor3f(0.2, 0.2f, 0.2);
    glPushMatrix();
    glTranslatef(-10, 1.9, -0.8f);
    glScalef(2.5, 0.3f, 4);
    glutSolidCube(1);
    glPopMatrix();
    //mat tren
    glPushMatrix();
    glTranslatef(-10, 2.7f, -3.55f);
    glRotatef(45, 1, 0, 0);
    glScalef(2.5, 0.3f, 2.5);
    glutSolidCube(1);
    glPopMatrix();
    //4 Chân ghế mặt dưới
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        //i < 2 trái(-11).i >= 2 phải(9).i chẵn sau(-1).i lẻ trước(1)
        glTranslatef((i < 2 ? -1 : 1) - 10, 1.2f, (i % 2 == 0 ? -2.5 : 1));
        glScalef(0.3, 1.5f, 0.3);
        glutSolidCube(1);
        glPopMatrix();
    }
    // 2 chân ghế mặt trên
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef((i % 2 == 0 ? -1 : 1) - 10, 2.1f, (i < 2 ? -4.3 : 1));
        glScalef(0.3, 2.7f, 0.3);
        glutSolidCube(1);
        glPopMatrix();
    }
}
//cái bàn
void drawTable() {
    GLUquadric* q = gluNewQuadric();
    //cột
    glPushMatrix();
    glTranslatef(0, 4, 5);
    glScalef(1, 0.8, 1);
    glRotatef(90, 1, 0, 0);
    glColor3f(0.7f, 0.7f, 0.7f);
    gluCylinder(q, 0.1, 0.1, 4, 8, 8);
    glPopMatrix();
    //chân bàn
    glPushMatrix();
    glTranslatef(0, 1, 5);
    //glScalef(2, 0.8, 2);
    glRotatef(90, 1, 0, 0);
    glColor3f(0.7f, 0.7f, 0.7f);
    gluCylinder(q, 0.6, 0.6, 0.4, 10, 10);
    // Đáy chân
    glPushMatrix();
    gluDisk(q, 0, 0.6, 10, 1);
    glPopMatrix();

    // Miệng chân
    glPushMatrix();
    glTranslatef(0, 0, 0.4);
    gluDisk(q, 0, 0.6, 10, 1);
    glPopMatrix();
    glPopMatrix();
    // mặt bàn
    glPushMatrix();
    glTranslatef(0, 4, 5);
    glScalef(2.5, 0.3f, 2.5);
    glColor3f(0.3f, 0.3f, 0.3f);
    glutSolidCube(1);
    gluDeleteQuadric(q);
    glPopMatrix();
}
//Cái thảm
void drawCarpet() {
    glPushMatrix();
    glTranslatef(1.2f, 1, 2);
    glScalef(6, 0.03f, 8);
    glColor3f(0.8, 0.8, 0.1);   // Màu đỏ đậm
    glutSolidCube(1);
    glPopMatrix();
}
//quả bóng
void drawBeachBall() {
    float radius = 1.0;// r bán kính
    int slices = 50, stacks = 50;
    int numSectors = 6; // 6 lần cắt(mặt)
    float anglePerSector = 360.0f / numSectors;

    // Các màu xen kẽ
    float colors[6][3] = {
        {1.0f, 0.0f, 0.0f},  // đỏ
        {1.0f, 1.0f, 0.0f},  // vàng
        {0.0f, 1.0f, 0.0f},  // xanh lá
        {0.0f, 1.0f, 1.0f},  // cyan
        {0.0f, 0.0f, 1.0f},  // xanh dương
        {1.0f, 0.0f, 1.0f}   // tím
    };

    for (int i = 0; i < numSectors; i++) {
        float startAngle = i * anglePerSector;//góc bắt đầu cắt của 1 mỗi múi
        float endAngle = (i + 1) * anglePerSector;//góc kết thúc cắt của 1 mỗi múi
        //eqn là phương trình mặt phẳng dạng Ax + By + Cz + D = 0
        //Mọi điểm thỏa mãn Ax + By + Cz + D < 0 sẽ bị loại bỏ(không vẽ)
        //Vậy mặt phẳng có pháp tuyến(A, B, C), và đi qua gốc nếu D = 0
        // Cắt từ startAngle đến endAngle theo trục Z
        double eqn1[4] = { -cos(startAngle * 3.14 / 180.0), -sin(startAngle * 3.14 / 180.0), 0.0, 0.0 };
        double eqn2[4] = { cos(endAngle * 3.14 / 180.0),  sin(endAngle * 3.14 / 180.0), 0.0, 0.0 };

        glEnable(GL_CLIP_PLANE0);// gọi hàm cắt 
        glClipPlane(GL_CLIP_PLANE0, eqn1);
        glEnable(GL_CLIP_PLANE1);
        glClipPlane(GL_CLIP_PLANE1, eqn2);

        glColor3f(colors[i][0], colors[i][1], colors[i][2]);
        glutSolidSphere(radius, slices, stacks);

        glDisable(GL_CLIP_PLANE0);
        glDisable(GL_CLIP_PLANE1);
    }
}
//chai nước 
void drawWaterBottle() {
    GLUquadric* bottlePart = gluNewQuadric();

    // === Thân chai nước ===
    glColor3f(0.4f, 0.7f, 1.0f); // Màu xanh nhạt (như nước)
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f); // Gốc ở đáy chai
    float bodyRadius = 0.4f;
    float bodyHeight = 1.5f;
    gluCylinder(bottlePart, bodyRadius, bodyRadius, bodyHeight, 32, 32);
    glPopMatrix();

    // === Đáy chai (hình tròn bịt dưới) ===
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    gluDisk(bottlePart, 0.0f, bodyRadius, 32, 1);
    glPopMatrix();

    // === Nắp chai ===
    glColor3f(0.1f, 0.1f, 0.8f); // Màu xanh đậm
    glPushMatrix();
    float capRadius = 0.3f;
    float capHeight = 0.2f;
    glTranslatef(0.0f, 0.0f, bodyHeight); // Đặt trên thân chai
    gluCylinder(bottlePart, capRadius, capRadius, capHeight, 32, 32);

    // Mặt trên nắp
    glTranslatef(0.0f, 0.0f, capHeight);
    gluDisk(bottlePart, 0.0f, capRadius, 32, 1);
    glPopMatrix();

    gluDeleteQuadric(bottlePart);
}
//cái xô
void drawHandle(float r, float h, int segments) {// tay cầm
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= segments; i++) {
        float a = 3.14 * i / segments;
        glVertex3f(r * cos(a), 0, r * sin(a) + h / 2);
    }
    glEnd();
}
void drawBucket() {
    glColor3f(0.8f, 0.8f, 0.8f);
    float h = 1.5f, r1 = 0.6f, r2 = 1.0f;
    drawPalmTopBase(h, r1, r2);  // Thân
    // Vẽ đáy
    GLUquadric* q = gluNewQuadric();
    glPushMatrix();

    glTranslatef(0, 0, 0);
    gluDisk(q, 0, r1, 30, 1);
    glPopMatrix();
    gluDeleteQuadric(q);
    drawHandle(1, 2 * h, 20);
}
// xẻng
void drawShovel() {
    GLUquadric* quad = gluNewQuadric();
    //cán
    glPushMatrix();
    glColor3f(0.4f, 0.25f, 0.1f); // Nâu gỗ
    glTranslatef(0, 0, 0.75f);
    gluCylinder(quad, 0.05f, 0.05f, 1.5f, 16, 1); // Cán dài 1.5
    glPopMatrix();
    //lưỡi
    glPushMatrix();
    glTranslatef(0, 0, 1);
    glColor3f(0.2f, 0.5f, 0.5f);

    glBegin(GL_POLYGON);
    glVertex3f(0.0f, -0.01f, 0.0f);
    glVertex3f(0.15f, 0.0f, -0.0f);
    glVertex3f(0.3f, 0.1f, -0.0f);
    glVertex3f(0.28f, 0.1f, -0.5f);
    glVertex3f(0.18f, 0.1f, -1.0f);
    glVertex3f(0.15f, 0.1f, -1.1f);
    glVertex3f(0.0f, 0.1f, -1.2f);
    glVertex3f(-0.15f, 0.1f, -1.1f);
    glVertex3f(-0.18f, 0.1f, -1.0f);
    glVertex3f(-0.28f, 0.1f, -0.5f);
    glVertex3f(-0.3f, 0.1f, -0.0f);
    glVertex3f(-0.15f, 0.0f, -0.0f);
    glEnd();
    glPopMatrix();
    gluDeleteQuadric(quad);
    //tay cầm
    glPushMatrix();
    glColor3f(0.4f, 0.25f, 0.1f);
    glTranslatef(-0.25, 0, 2.3);
    glRotatef(90, 0, 1, 0);
    gluCylinder(quad, 0.07f, 0.07f, 0.5f, 16, 1);
    glPopMatrix();
}
// ván lướt sóng
void drawSurfboard() {
    glColor3f(0.3f, 0.6f, 0.3f);
    glPushMatrix();

    glScalef(7, 0.2, 1.8);
    glRotatef(-90, 1, 0, 0);
    glutSolidSphere(0.6f, 30, 30);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(2.5, 0, 0);
    glRotatef(90, 1, 0, 0);
    glColor3f(0.3f, 0.6f, 0.3f);

    glBegin(GL_POLYGON);
    glVertex3f(0.0f, -0.0f, 0.0f);
    glVertex3f(0.15f, 0.0f, -0.0f);
    glVertex3f(0.3f, 0.0f, -0.0f);
    glVertex3f(0.28f, 0.0f, -0.5f);
    glVertex3f(0.18f, 0.0f, -1.0f);
    glVertex3f(0.85f, 0.0f, -1.1f);
    glVertex3f(0.6f, 0.0f, -1.2f);
    glVertex3f(-0.15f, 0.0f, -1.1f);
    glVertex3f(-0.18f, 0.0f, -1.0f);
    glVertex3f(-0.28f, 0.0f, -0.5f);
    glVertex3f(-0.3f, 0.0f, -0.0f);
    glVertex3f(-0.15f, 0.0f, -0.0f);
    glEnd();
    glPopMatrix();

}
// lâu đài cát
void drawlaudaicat() {
    glPushMatrix();//1
    glColor3f(0.96f, 0.87f, 0.70f);
    GLUquadric* quad = gluNewQuadric();
    //4 tháp 
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef((i < 2 ? -0.5 : 0.5), 1, (i % 2 == 0 ? -0.5 : 0.5));
        glRotated(-90, 1, 0, 0);
        gluCylinder(quad, 0.2, 0.1, 1, 20, 10);
        glPopMatrix();
    }
    // 4 mũ tháp
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef((i < 2 ? -0.5 : 0.5), 2, (i % 2 == 0 ? -0.5 : 0.5));
        glRotated(-90, 1, 0, 0);
        gluCylinder(quad, 0.2, 0.2, 0.3, 20, 10);
        gluDisk(quad, 0, 0.2, 30, 1);
        glPopMatrix();
    }

    // mũ tháp chính
    glPushMatrix();
    glTranslatef(0, 2.5, 0);
    glRotated(-90, 1, 0, 0);
    glutSolidCone(0.3, 0.6, 10, 6);// chóp    
    glPopMatrix();

    //thành chính
    glPushMatrix();
    glTranslatef(0, 1.5, 0);
    glutSolidCube(1);// lập phương
    glRotated(-90, 1, 0, 0);
    // tháp chính
    gluCylinder(quad, 0.2, 0.2, 1, 20, 10);// trụ không bọc 2 đầu (tuýp sắt)
    glPopMatrix();
    //cửa
    glPushMatrix();
    glTranslatef(0, 1, 0.51);
    glRotated(90, 1, 0, 0);
    glScalef(0.5, 0.5, 0.5);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f(0.0f, -0.01f, 0.0f);
    glVertex3f(0.15f, 0.0f, -0.0f);
    glVertex3f(0.3f, 0.0f, -0.0f);
    glVertex3f(0.28f, 0.0f, -0.5f);
    glVertex3f(0.18f, 0.0f, -1.0f);
    glVertex3f(0.15f, 0.0f, -1.1f);
    glVertex3f(-0.15f, 0.0f, -1.1f);
    glVertex3f(-0.18f, 0.0f, -1.0f);
    glVertex3f(-0.28f, 0.0f, -0.5f);
    glVertex3f(-0.3f, 0.0f, -0.0f);
    glVertex3f(-0.15f, 0.0f, -0.0f);
    glEnd();
    glPopMatrix();
    gluDeleteQuadric(quad);
    glPopMatrix();

}
// bánh snack
void drawSnackBag() {
    glPushMatrix();
    // Thân chính
    glColor3f(1.0f, 0.2f, 0.0f);
    glScalef(1.2f, 1.8f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();
    //
    GLUquadric* quad = gluNewQuadric();
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(-0.6, (i == 0) ? -0.7 : 0.7, 0.0f);
        glColor3f(1.0f, 0.2f, 0.0f);
        glScalef(2.4, 5, 1.5);
        glRotated(90, 0, 1, 0);
        glPushMatrix();
        gluDisk(quad, 0.0f, 0.1f, 20, 1);
        glPopMatrix();
        gluCylinder(quad, 0.1f, 0.1f, 0.5f, 20, 10);
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.5f);
        gluDisk(quad, 0.0f, 0.1f, 20, 1);
        glPopMatrix();
        glPopMatrix();
    }
    //
    glColor3f(1.0f, 0.2f, 0.0f);
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(0.0f, (i == 0) ? -1.2f : 1.2f, 0.0f);
        glScalef(1.19f, 0.3f, 0.01f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }
    gluDeleteQuadric(quad);
}
// cỏ 
void drawGrassTuft(float x, float y, float z, float scale) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(scale, scale, scale);
    // Sử dụng alpha blending để tạo sự mỏng nhẹ cho lá
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.3f, 0.7f, 0.3f, 0.7f);
    // Định nghĩa các tham số cho từng lá:
    // Mỗi lá có chiều cao (y) và độ lệch theo trục z tùy việt
    // Ta sẽ sử dụng bảng dữ liệu để lưu các giá trị này
    const int SLICE_COUNT = 9;
    float leafHeights[SLICE_COUNT] = { 0.12f, 0.14f, 0.13f, 0.15f, 0.11f, 0.16f, 0.12f, 0.13f, 0.14f };
    float leafDepths[SLICE_COUNT] = { 0.0f,  0.01f, -0.01f, 0.02f, -0.02f, 0.03f, -0.03f, 0.04f, -0.04f };

    // Giá trị halfWidth điều khiển độ "mỏng" của lá
    float halfWidth = 0.008f;
    // Vẽ từng lá với một phép quay riêng, phân bố đều xung quanh trục y
    for (int i = 0; i < SLICE_COUNT; i++) {
        glPushMatrix();
        // Quay lá xung quanh trục Y, chia đều 360 độ cho 9 lá
        float angle = i * (360.0f / SLICE_COUNT);
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
        // Vẽ tam giác của lá với đỉnh gốc tại (0,0,0) và đỉnh còn lại lệch theo chỉ số của lá
        glBegin(GL_TRIANGLES);
        // Đỉnh gốc
        glVertex3f(0.0f, 0.0f, 0.0f);
        // Đỉnh trái (mỏng lại bằng cách giới hạn halfWidth)
        glVertex3f(-halfWidth, leafHeights[i], leafDepths[i]);
        // Đỉnh phải
        glVertex3f(halfWidth, leafHeights[i], leafDepths[i]);
        glEnd();
        glPopMatrix();
    }

    glDisable(GL_BLEND);
    glPopMatrix();
}
void drawManyGrassTufts(int count, float areaWidth, float areaDepth) {
    srand(42);

    for (int i = 0; i < count; i++) {
        float x = ((rand() % 1000) / 1000.0f - 0.5f) * areaWidth;
        float z = ((rand() % 1000) / 1000.0f - 0.5f) * areaDepth;
        float y = 0.0f;
        float scale = 5 + (rand() % 50) / 100.0f;

        drawGrassTuft(x, y, z, scale);
    }
}
//sỏi
void drawPebble(float x, float y, float z, float radius) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(1.0f, 0.6f, 0.8f);
    glColor3f(0.4f, 0.4f, 0.4f); // Màu xám đá
    glutSolidSphere(radius, 20, 20);
    glPopMatrix();
}
void drawManyPebbles(int count, float areaWidth, float areaDepth) {
    srand(42);

    for (int i = 0; i < count; i++) {
        float x = ((rand() % 1000) / 1000.0f - 0.5f) * areaWidth;
        float z = ((rand() % 1000) / 1000.0f - 0.5f) * areaDepth;
        float y = 0.0f;
        float radius = 0.05f + (rand() % 50) / 1000.0f; // 0.05 - 0.1

        drawPebble(x, y, z, radius);
    }
}
//trục tọa độ x,y,z để test
void drawAxis(float length = 0.2f) {
    glDisable(GL_LIGHTING); // Tắt ánh sáng để màu không bị ảnh hưởng

    //glLineWidth(2.0f);
    glBegin(GL_LINES);

    // Trục X - Đỏ
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(length, 0, 0);

    // Trục Y - Lục
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, length, 0);

    // Trục Z - Xanh dương
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, length);

    glEnd();

    glEnable(GL_LIGHTING); // Bật lại ánh sáng
}
// --- Hàm hiển thị ---
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // Tính toán hướng nhìn từ yaw và pitch
    float dirX = cos(pitch) * sin(yaw);
    float dirY = sin(pitch);
    float dirZ = -cos(pitch) * cos(yaw);
    gluLookAt(eyeX, eyeY, eyeZ,            // vị trí mắt
        eyeX + dirX, eyeY + dirY, eyeZ + dirZ,  // điểm nhìn tới
        0.0f, 1.0f, 0.0);

    setupLight();
    
    //sun
    glPushMatrix();    glTranslatef(29, 29, 29);   drawSun();   glPopMatrix();
    drawAxis();// trục tọa độ
    //đèn đường
    glPushMatrix();    glTranslatef(-19, 1, -29); glRotated(-90, 0, 1, 0); glScalef(5, 5, 5);   drawStreetLamp();   glPopMatrix();
    // nền
    drawGround();
    //thảm
    drawCarpet();
    // ghế
    drawCubeChair();
    // bàn
    glPushMatrix();    glTranslatef(-7.0f, 0, -7.0f);   drawTable();   glPopMatrix();
    // ô
    glPushMatrix();    glTranslatef(-8.5f, 0, -3.5f);   drawUmbrella(0, 0);   glPopMatrix();
    // phao
    drawPhao();
    // quả bóng
    glPushMatrix();   glTranslatef(-3.5f, 1.35, 6.0f);     drawBeachBall();        glPopMatrix();
    // chai nước
    glPushMatrix();    glTranslatef(-6.5f, 4.2, -2.7f); glRotated(-90, 1, 0, 0);   drawWaterBottle();  glPopMatrix();
    // xô
    glPushMatrix();    glTranslatef(5.0f, 1, 1.0f);    glRotated(-90, 1, 0, 0);    drawBucket();    glPopMatrix();
    //xẻng
    glPushMatrix();    glTranslatef(5.0f, 1, 3.0f);    drawShovel();   glPopMatrix();
    //ván lướt sóng 
    glPushMatrix();    glTranslatef(10.0f, 1, 5.0f); glRotated(90, 0, 1, 0);    drawSurfboard();   glPopMatrix();
    // lâu đài cát
    glPushMatrix();    glTranslatef(6.5f, 0, 4.0f);    drawlaudaicat();   glPopMatrix();
    //bánh snack
    glPushMatrix();     glTranslatef(-6.8f, 4.4, -1.3f); glScalef(0.5f, 0.5f, 0.5f);   glRotated(-90, 1, 0, 0);   drawSnackBag();   glPopMatrix();
    //cỏ
    glPushMatrix();    glTranslatef(0, 0.9, -20); glRotated(-90, 0, 1, 0);    drawManyGrassTufts(200, 19, 50);    glPopMatrix();
    //sỏi
    glPushMatrix();    glTranslatef(0, 0.7, 0);     drawManyPebbles(200, 45, 18.0f);    glPopMatrix();
    // vẽ cây dừa 
    glPushMatrix();    glTranslatef(25.0f, 1, -25.0);       drawPalmTree();     glPopMatrix();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    float dirX = cos(pitch) * sin(yaw);
    float dirY = sin(pitch);
    float dirZ = -cos(pitch) * cos(yaw);

    float rightX = sin(yaw - 3.14f / 2.0f);
    float rightZ = -cos(yaw - 3.14f / 2.0f);

    switch (key) {
    case 'w': eyeX += dirX * speed; eyeY += dirY * speed; eyeZ += dirZ * speed; break;
    case 's': eyeX -= dirX * speed; eyeY -= dirY * speed; eyeZ -= dirZ * speed; break;
    case 'a': eyeX += rightX * speed; eyeZ += rightZ * speed; break;
    case 'd': eyeX -= rightX * speed; eyeZ -= rightZ * speed; break;
    case 'q': eyeY += speed; break;
    case 'e': eyeY -= speed; break;
    case '1': case 'mt': toggleLight(); break; //bật/tắt ánh sáng
    case '2': case 'den': toggleLamp(); break;    //bật/tắt đèn đường
    case '3': case 'đh': toggledhlight1(); break; //bật/tắt ánh sáng định hướng của mặt trời
    case 27: exit(0); break;
    }

    glutPostRedisplay();
}

void passiveMouse(int x, int y) {
    if (firstMouse) {
        lastX = x; lastY = y; firstMouse = false;
    }
    int dx = x - lastX, dy = y - lastY; yaw += dx * sensitivity; pitch -= dy * sensitivity;
    if (pitch > 1.5f)pitch = 1.5f;
    if (pitch < -1.5f)pitch = -1.5f;
    lastX = x; lastY = y;
    glutPostRedisplay();
}

int main(int c, char** v) {
    glutInit(&c, v);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Beach");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(passiveMouse);
    glutMainLoop();
}
