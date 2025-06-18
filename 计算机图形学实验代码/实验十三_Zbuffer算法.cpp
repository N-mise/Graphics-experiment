#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 定义M_PI常量
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// 窗口尺寸
const int WIDTH = 800;
const int HEIGHT = 600;

// 初始化 OpenGL 设置
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // 设置背景颜色为黑色
    glEnable(GL_DEPTH_TEST);               // 启用深度测试（Z-buffer）
    glDepthFunc(GL_LESS);                  // 设置深度比较函数
}

// 绘制一个彩色立方体
void drawCube() {
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.5f);  // 调整位置，使其与金字塔部分重叠
    glScalef(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

    // 前面
    glColor3f(1.0f, 0.0f, 0.0f);  // 红色
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    // 后面
    glColor3f(0.0f, 1.0f, 0.0f);  // 绿色
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // 顶面
    glColor3f(0.0f, 0.0f, 1.0f);  // 蓝色
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    // 底面
    glColor3f(1.0f, 1.0f, 0.0f);  // 黄色
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // 右面
    glColor3f(1.0f, 0.0f, 1.0f);  // 紫色
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // 左面
    glColor3f(0.0f, 1.0f, 1.0f);  // 青色
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    glEnd();
    glPopMatrix();
}

// 绘制一个彩色金字塔
void drawPyramid() {
    glPushMatrix();
    glTranslatef(0.5f, 0.0f, 0.0f);  // 调整位置，使其与立方体部分重叠
    glScalef(1.0f, 1.0f, 1.0f);

    glBegin(GL_TRIANGLES);

    // 前面
    glColor3f(1.0f, 0.0f, 0.0f);  // 红色
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // 右面
    glColor3f(0.0f, 1.0f, 0.0f);  // 绿色
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // 后面
    glColor3f(0.0f, 0.0f, 1.0f);  // 蓝色
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // 左面
    glColor3f(1.0f, 1.0f, 0.0f);  // 黄色
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    glEnd();

    // 底面（正方形）
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);  // 灰色
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glEnd();

    glPopMatrix();
}

// 绘制坐标系
void drawCoordinateSystem() {
    glPushMatrix();

    // 绘制X轴（红色）
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(-5.0f, 0.0f, 0.0f);
    glVertex3f(5.0f, 0.0f, 0.0f);
    glEnd();

    // 绘制Y轴（绿色）
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, -5.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 0.0f);
    glEnd();

    // 绘制Z轴（蓝色）
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, -5.0f);
    glVertex3f(0.0f, 0.0f, 5.0f);
    glEnd();

    glPopMatrix();
}

// 显示回调函数
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // 清除颜色缓冲区和深度缓冲区

    // 设置观察矩阵
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // 绘制坐标系
    drawCoordinateSystem();

    // 绘制场景中的物体（先绘制立方体，再绘制金字塔）
    drawCube();
    drawPyramid();

    glutSwapBuffers();  // 交换前后缓冲区
}

// 调整窗口大小回调函数
void reshape(int width, int height) {
    if (height == 0) height = 1;
    float aspect = (float)width / (float)height;

    // 设置视口
    glViewport(0, 0, width, height);

    // 设置投影矩阵
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 0.1, 100.0);
}

// 键盘回调函数
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27:     // ESC键退出程序
        exit(0);
        break;
    }
}

// 主函数
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  // 启用双缓冲和深度缓冲
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("OpenGL Z-buffer 重叠演示");

    init();  // 初始化OpenGL设置

    // 设置回调函数
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();  // 进入GLUT主循环
    return 0;
}