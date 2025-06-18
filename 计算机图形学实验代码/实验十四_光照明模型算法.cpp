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

// 光照参数
GLfloat light_position[] = { 5.0f, 5.0f, 5.0f, 1.0f };  // 光源位置
GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };   // 环境光
GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };   // 漫反射光
GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // 镜面反射光

// 材质参数
GLfloat material_ambient[] = { 0.2f, 0.2f, 0.8f, 1.0f };    // 球体环境光反射
GLfloat material_diffuse[] = { 0.2f, 0.2f, 0.8f, 1.0f };    // 球体漫反射
GLfloat material_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };   // 球体镜面反射
GLfloat material_shininess = 50.0f;                        // 球体光泽度

// 平面材质
GLfloat plane_ambient[] = { 0.2f, 0.8f, 0.2f, 1.0f };       // 平面环境光反射
GLfloat plane_diffuse[] = { 0.2f, 0.8f, 0.2f, 1.0f };       // 平面漫反射
GLfloat plane_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };      // 平面镜面反射
GLfloat plane_shininess = 30.0f;                           // 平面光泽度

// 视角参数
float camera_angle = 0.0f;
float camera_distance = 10.0f;

// 初始化 OpenGL 设置
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // 设置背景颜色为黑色
    glEnable(GL_DEPTH_TEST);               // 启用深度测试

    // 启用光照
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // 设置光照属性
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // 启用法线归一化
    glEnable(GL_NORMALIZE);
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

// 绘制球体
void drawSphere() {
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f);  // 将球体放置在平面上方

    // 设置球体材质属性
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, material_shininess);

    // 绘制球体
    glutSolidSphere(1.0f, 32, 32);

    glPopMatrix();
}

// 绘制平面
void drawPlane() {
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 0.0f);  // 将平面放置在Y=-1位置

    // 设置平面材质属性
    glMaterialfv(GL_FRONT, GL_AMBIENT, plane_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, plane_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, plane_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, plane_shininess);

    // 绘制平面
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);  // 平面法线朝上
    glVertex3f(-5.0f, 0.0f, -5.0f);
    glVertex3f(5.0f, 0.0f, -5.0f);
    glVertex3f(5.0f, 0.0f, 5.0f);
    glVertex3f(-5.0f, 0.0f, 5.0f);
    glEnd();

    glPopMatrix();
}

// 显示回调函数
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // 清除颜色缓冲区和深度缓冲区

    // 设置观察矩阵
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 计算相机位置
    float camX = camera_distance * sin(camera_angle);
    float camZ = camera_distance * cos(camera_angle);
    gluLookAt(camX, 3.0f, camZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // 绘制坐标系
    drawCoordinateSystem();

    // 绘制场景中的物体
    drawPlane();
    drawSphere();

    // 绘制光源位置（小立方体）
    glPushMatrix();
    glTranslatef(light_position[0], light_position[1], light_position[2]);
    glColor3f(1.0f, 1.0f, 0.0f);  // 黄色表示光源
    glutSolidCube(0.2f);
    glPopMatrix();

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

// 定时器回调函数，用于旋转相机
void timer(int value) {
    camera_angle += 0.01f;
    if (camera_angle > 2 * M_PI) camera_angle -= 2 * M_PI;

    glutPostRedisplay();  // 标记当前窗口需要重新绘制
    glutTimerFunc(16, timer, 0);  // 设置下一次定时器回调，约60帧/秒
}

// 键盘回调函数
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27:     // ESC键退出程序
        exit(0);
        break;
    case 'w':    // 向上移动光源
        light_position[1] += 0.5f;
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        break;
    case 's':    // 向下移动光源
        light_position[1] -= 0.5f;
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        break;
    case 'a':    // 向左移动光源
        light_position[0] -= 0.5f;
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        break;
    case 'd':    // 向右移动光源
        light_position[0] += 0.5f;
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        break;
    case 'q':    // 向前移动光源
        light_position[2] -= 0.5f;
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        break;
    case 'e':    // 向后移动光源
        light_position[2] += 0.5f;
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        break;
    case '+':    // 增加球体光泽度
        material_shininess += 5.0f;
        if (material_shininess > 128.0f) material_shininess = 128.0f;
        break;
    case '-':    // 减少球体光泽度
        material_shininess -= 5.0f;
        if (material_shininess < 1.0f) material_shininess = 1.0f;
        break;
    }
}

// 主函数
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  // 启用双缓冲和深度缓冲
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Pong光照模型演示");

    init();  // 初始化OpenGL设置

    // 设置回调函数
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);  // 设置定时器回调

    glutMainLoop();  // 进入GLUT主循环
    return 0;
}