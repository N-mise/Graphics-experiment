#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

// 窗口尺寸
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// 初始化OpenGL设置
void init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 设置背景色为黑色
    glEnable(GL_DEPTH_TEST); // 启用深度测试

    // 设置光照
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // 设置光源位置和属性
    GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

// 绘制光滑着色的三角形
void drawSmoothTriangle() {
    glPushMatrix();
    glTranslatef(-0.7f, 0.0f, 0.0f); // 向左平移

    // 设置三角形材质属性（光滑着色）
    glShadeModel(GL_SMOOTH); // 启用光滑着色

    // 绘制三角形
    glBegin(GL_TRIANGLES);
    // 顶点1 - 红色
    glNormal3f(0.0f, 0.0f, 1.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.0f);

    // 顶点2 - 绿色
    glNormal3f(0.0f, 0.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.0f);

    // 顶点3 - 蓝色
    glNormal3f(0.0f, 0.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();

    glPopMatrix();
}

// 绘制平面着色的平行四边形
void drawFlatParallelogram() {
    glPushMatrix();
    glTranslatef(0.7f, 0.0f, 0.0f); // 向右平移

    // 设置平行四边形材质属性（平面着色）
    glShadeModel(GL_FLAT); // 启用平面着色

    // 平面着色：每个图元（多边形）只指定一个法向量和颜色
    glNormal3f(0.0f, 0.0f, 1.0f);
    glColor3f(0.5f, 0.5f, 1.0f); // 蓝色调

    // 绘制平行四边形
    glBegin(GL_QUADS);
    glVertex3f(-0.6f, -0.4f, 0.0f);
    glVertex3f(0.4f, -0.4f, 0.0f);
    glVertex3f(0.6f, 0.4f, 0.0f);
    glVertex3f(-0.4f, 0.4f, 0.0f);
    glEnd();

    glPopMatrix();
}

// 显示回调函数
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // 设置视角
    gluLookAt(0.0f, 0.0f, 5.0f,  // 相机位置
        0.0f, 0.0f, 0.0f,  // 观察点
        0.0f, 1.0f, 0.0f); // 上方向

    // 绘制坐标系
    glDisable(GL_LIGHTING);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    // X轴 - 红色
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-2.0f, 0.0f, 0.0f);
    glVertex3f(2.0f, 0.0f, 0.0f);
    // Y轴 - 绿色
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -2.0f, 0.0f);
    glVertex3f(0.0f, 2.0f, 0.0f);
    // Z轴 - 蓝色
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -2.0f);
    glVertex3f(0.0f, 0.0f, 2.0f);
    glEnd();
    glEnable(GL_LIGHTING);

    // 绘制光滑着色三角形
    drawSmoothTriangle();

    // 绘制平面着色平行四边形
    drawFlatParallelogram();

    glutSwapBuffers();
}

// 调整窗口大小回调函数
void reshape(int width, int height) {
    if (height == 0) height = 1;
    float aspect = (float)width / (float)height;

    glViewport(0, 0, width, height);

    // 设置透视投影
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);

    // 设置模型视图矩阵
    glMatrixMode(GL_MODELVIEW);
}

// 主函数
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("OpenGL着色演示");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}