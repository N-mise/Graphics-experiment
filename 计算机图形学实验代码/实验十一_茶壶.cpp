#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

// 全局变量
float angleX = 0.0f;       // X轴旋转角度
float angleY = 0.0f;       // Y轴旋转角度
float scale = 1.0f;        // 缩放比例
float translateX = 0.0f;   // X轴平移量
float translateY = 0.0f;   // Y轴平移量
float translateZ = -5.0f;  // Z轴平移量（初始位置）
int isDragging = 0;        // 是否正在拖动鼠标
int lastX, lastY;          // 鼠标最后位置
int windowWidth = 800;
int windowHeight = 600;

// 初始化OpenGL设置
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);  // 设置背景颜色为黑色
    glEnable(GL_DEPTH_TEST);           // 启用深度测试
    glEnable(GL_LIGHTING);             // 启用光照
    glEnable(GL_LIGHT0);               // 启用光源0

    // 设置光源
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // 设置材质
    GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 100.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

// 显示回调函数
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // 设置相机位置
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // 应用变换（平移、旋转、缩放）
    glTranslatef(translateX, translateY, translateZ);
    glRotatef(angleX, 1.0, 0.0, 0.0);  // 绕X轴旋转
    glRotatef(angleY, 0.0, 1.0, 0.0);  // 绕Y轴旋转
    glScalef(scale, scale, scale);      // 缩放

    // 绘制GLUT茶壶
    glutSolidTeapot(1.0);

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

// 键盘回调函数（普通键）
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': case 'W':  // 向前移动（Z轴负方向）
        translateZ += 0.1f;
        break;
    case 's': case 'S':  // 向后移动（Z轴正方向）
        translateZ -= 0.1f;
        break;
    case 'a': case 'A':  // 向左移动（X轴负方向）
        translateX -= 0.1f;
        break;
    case 'd': case 'D':  // 向右移动（X轴正方向）
        translateX += 0.1f;
        break;
    case 'q': case 'Q':  // 缩小
        scale -= 0.05f;
        if (scale < 0.1f) scale = 0.1f;
        break;
    case 'e': case 'E':  // 放大
        scale += 0.05f;
        break;
    case 27:  // ESC键退出程序
        exit(0);
        break;
    }
    glutPostRedisplay();
}

// 键盘回调函数（特殊键，如方向键）
void special(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:    // 向上旋转（X轴）
        angleX += 5.0f;
        break;
    case GLUT_KEY_DOWN:  // 向下旋转（X轴）
        angleX -= 5.0f;
        break;
    case GLUT_KEY_LEFT:  // 向左旋转（Y轴）
        angleY += 5.0f;
        break;
    case GLUT_KEY_RIGHT: // 向右旋转（Y轴）
        angleY -= 5.0f;
        break;
    }
    glutPostRedisplay();
}

// 鼠标回调函数
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isDragging = 1;
            lastX = x;
            lastY = y;
        }
        else {
            isDragging = 0;
        }
    }
}

// 鼠标移动回调函数（处理拖动）
void motion(int x, int y) {
    if (isDragging) {
        // 计算鼠标移动的差值
        int deltaX = x - lastX;
        int deltaY = y - lastY;

        // 更新旋转角度
        angleY += deltaX * 0.5f;
        angleX += deltaY * 0.5f;

        // 限制X轴旋转角度范围
        if (angleX > 90.0f) angleX = 90.0f;
        if (angleX < -90.0f) angleX = -90.0f;

        // 更新最后位置
        lastX = x;
        lastY = y;

        glutPostRedisplay();
    }
}

// 主函数
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("GLUT茶壶观察控制实验");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    printf("GLUT茶壶观察控制实验\n");
    printf("控制方式:\n");
    printf("  方向键: 旋转茶壶\n");
    printf("  WASD: 平移茶壶\n");
    printf("  QE: 缩放茶壶\n");
    printf("  鼠标左键拖动: 旋转茶壶\n");
    printf("  ESC: 退出程序\n");

    glutMainLoop();
    return 0;
}