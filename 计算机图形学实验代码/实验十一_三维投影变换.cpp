#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

// 全局变量
int projectionType = 1;  // 1:一点透视, 2:二点透视, 3:三点透视
int windowWidth = 800;
int windowHeight = 600;

// 金字塔顶点定义
GLfloat pyramidVertices[5][3] = {
    {0.0, 1.0, 0.0},       // 顶部顶点
    {-1.0, -1.0, 1.0},     // 底部前左
    {1.0, -1.0, 1.0},      // 底部前右
    {1.0, -1.0, -1.0},     // 底部后右
    {-1.0, -1.0, -1.0}     // 底部后左
};

// 金字塔面定义（顶点索引）
GLint pyramidFaces[4][3] = {
    {0, 1, 2},  // 前面
    {0, 2, 3},  // 右面
    {0, 3, 4},  // 后面
    {0, 4, 1}   // 左面
};

// 初始化OpenGL设置
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);  // 设置背景颜色为黑色
    glEnable(GL_DEPTH_TEST);           // 启用深度测试
    glShadeModel(GL_SMOOTH);           // 启用平滑着色
}

// 设置光源
void setupLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_position[] = { 5.0, 5.0, 5.0, 1.0 };
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

// 设置材质
void setupMaterial() {
    GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 100.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

// 绘制金字塔
void drawPyramid() {
    // 禁用光照，使用直接颜色
    glDisable(GL_LIGHTING);

    glBegin(GL_TRIANGLES);

    // 前面 - 红色
    glColor3f(1.0, 0.0, 0.0);
    glVertex3fv(pyramidVertices[0]);
    glVertex3fv(pyramidVertices[1]);
    glVertex3fv(pyramidVertices[2]);

    // 右面 - 绿色
    glColor3f(0.0, 1.0, 0.0);
    glVertex3fv(pyramidVertices[0]);
    glVertex3fv(pyramidVertices[2]);
    glVertex3fv(pyramidVertices[3]);

    // 后面 - 蓝色
    glColor3f(0.0, 0.0, 1.0);
    glVertex3fv(pyramidVertices[0]);
    glVertex3fv(pyramidVertices[3]);
    glVertex3fv(pyramidVertices[4]);

    // 左面 - 黄色
    glColor3f(1.0, 1.0, 0.0);
    glVertex3fv(pyramidVertices[0]);
    glVertex3fv(pyramidVertices[4]);
    glVertex3fv(pyramidVertices[1]);

    // 底面 - 紫色
    glColor3f(1.0, 0.0, 1.0);
    glVertex3fv(pyramidVertices[1]);
    glVertex3fv(pyramidVertices[4]);
    glVertex3fv(pyramidVertices[3]);
    glVertex3fv(pyramidVertices[1]);
    glVertex3fv(pyramidVertices[3]);
    glVertex3fv(pyramidVertices[2]);

    glEnd();

    // 重新启用光照
    glEnable(GL_LIGHTING);
}

// 显示回调函数
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // 设置观察点
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // 根据当前投影类型应用不同的变换
    switch (projectionType) {
    case 1: // 一点透视
        glRotatef(20.0, 1.0, 0.0, 0.0);  // 稍微旋转以显示3D效果
        break;
    case 2: // 二点透视
        glRotatef(30.0, 0.0, 1.0, 0.0);  // 绕Y轴旋转
        glRotatef(15.0, 1.0, 0.0, 0.0);  // 绕X轴旋转
        break;
    case 3: // 三点透视
        glRotatef(30.0, 0.0, 1.0, 0.0);  // 绕Y轴旋转
        glRotatef(20.0, 1.0, 0.0, 0.0);  // 绕X轴旋转
        glRotatef(10.0, 0.0, 0.0, 1.0);  // 绕Z轴旋转
        break;
    default:
        break;
    }

    // 绘制金字塔
    drawPyramid();

    glutSwapBuffers();
}

// 窗口大小改变回调函数
void reshape(int width, int height) {
    windowWidth = width;
    windowHeight = height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 设置透视投影
    gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

// 键盘回调函数
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '1':
        projectionType = 1;
        printf("切换到一点透视投影\n");
        break;
    case '2':
        projectionType = 2;
        printf("切换到二点透视投影\n");
        break;
    case '3':
        projectionType = 3;
        printf("切换到三点透视投影\n");
        break;
    case 27:  // ESC键退出程序
        exit(0);
        break;
    }
    glutPostRedisplay();
}

// 特殊键回调函数（用于方向键控制）
void special(int key, int x, int y) {
    static float angleX = 0.0, angleY = 0.0;

    switch (key) {
    case GLUT_KEY_UP:
        angleX += 5.0;
        break;
    case GLUT_KEY_DOWN:
        angleX -= 5.0;
        break;
    case GLUT_KEY_LEFT:
        angleY += 5.0;
        break;
    case GLUT_KEY_RIGHT:
        angleY -= 5.0;
        break;
    }

    // 更新模型变换
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(angleX, 1.0, 0.0, 0.0);
    glRotatef(angleY, 0.0, 1.0, 0.0);

    glutPostRedisplay();
}

// 主函数
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("OpenGL透视投影变换实验");

    init();
    setupLighting();
    setupMaterial();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);

    printf("透视投影变换实验\n");
    printf("按键1: 一点透视投影\n");
    printf("按键2: 二点透视投影\n");
    printf("按键3: 三点透视投影\n");
    printf("ESC: 退出程序\n");
    printf("方向键: 旋转视图\n");

    glutMainLoop();
    return 0;
}