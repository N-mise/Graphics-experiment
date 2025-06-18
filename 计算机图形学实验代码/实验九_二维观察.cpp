//二位观察变化算法（P190）

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 窗口尺寸
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// 观察参数
float translateX = 0.0f;
float translateY = 0.0f;
float scale = 1.0f;
float rotation = 0.0f;

// 视图中心
float viewCenterX = 0.0f;
float viewCenterY = 0.0f;

// 鼠标状态
int mouseButton = -1;
int lastX, lastY;

// 初始化OpenGL设置
void init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // 设置背景色为黑色
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-WINDOW_WIDTH / 2, WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2, WINDOW_HEIGHT / 2);
}

// 绘制坐标系
void drawCoordinateSystem() {
    glColor3f(0.5f, 0.5f, 0.5f);  // 灰色
    glLineWidth(1.0f);

    // X轴
    glBegin(GL_LINES);
    glVertex2f(-WINDOW_WIDTH / 2, 0);
    glVertex2f(WINDOW_WIDTH / 2, 0);
    // Y轴
    glVertex2f(0, -WINDOW_HEIGHT / 2);
    glVertex2f(0, WINDOW_HEIGHT / 2);
    glEnd();
}

// 绘制简化的二维图形（不重叠）
void drawShapes() {
    // 绘制一个红色三角形（上半部分）
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-100.0f, 50.0f);
    glVertex2f(100.0f, 50.0f);
    glVertex2f(0.0f, 200.0f);
    glEnd();

    // 绘制一个绿色矩形（下半部分）
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-100.0f, -200.0f);
    glVertex2f(100.0f, -200.0f);
    glVertex2f(100.0f, -50.0f);
    glVertex2f(-100.0f, -50.0f);
    glEnd();
}

// 显示回调函数
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // 应用观察变换
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 平移到视图中心
    glTranslatef(viewCenterX, viewCenterY, 0.0f);

    // 应用用户变换
    glTranslatef(translateX, translateY, 0.0f);
    glRotatef(rotation, 0.0f, 0.0f, 1.0f);
    glScalef(scale, scale, 1.0f);

    // 绘制坐标系和图形
    drawCoordinateSystem();
    drawShapes();

    glutSwapBuffers();
}

// 窗口大小改变回调函数
void reshape(int width, int height) {
    if (height == 0) height = 1;
    float aspect = (float)width / (float)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width >= height) {
        gluOrtho2D(-WINDOW_WIDTH / 2 * aspect, WINDOW_WIDTH / 2 * aspect, -WINDOW_HEIGHT / 2, WINDOW_HEIGHT / 2);
    }
    else {
        gluOrtho2D(-WINDOW_WIDTH / 2, WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2 / aspect, WINDOW_HEIGHT / 2 / aspect);
    }
}

// 键盘回调函数
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
    case 'W':
        translateY += 10.0f;
        break;
    case 's':
    case 'S':
        translateY -= 10.0f;
        break;
    case 'a':
    case 'A':
        translateX -= 10.0f;
        break;
    case 'd':
    case 'D':
        translateX += 10.0f;
        break;
    case '+':
        scale *= 1.1f;
        break;
    case '-':
        scale /= 1.1f;
        break;
    case 'r':
    case 'R':
        rotation += 5.0f;
        break;
    case 'e':
    case 'E':
        rotation -= 5.0f;
        break;
    case ' ':  // 重置变换
        translateX = 0.0f;
        translateY = 0.0f;
        scale = 1.0f;
        rotation = 0.0f;
        break;
    case 27:  // ESC键退出
        exit(0);
        break;
    }
    glutPostRedisplay();
}

// 鼠标点击回调函数
void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        mouseButton = button;
        lastX = x;
        lastY = y;
    }
    else {
        mouseButton = -1;
    }
}

// 鼠标移动回调函数
void motion(int x, int y) {
    int dx = x - lastX;
    int dy = y - lastY;

    switch (mouseButton) {
    case GLUT_LEFT_BUTTON:  // 左键拖动 - 平移
        translateX += dx;
        translateY -= dy;  // 注意：窗口坐标的y轴向下，而世界坐标的y轴向上
        break;
    case GLUT_RIGHT_BUTTON:  // 右键拖动 - 旋转
        rotation += dx * 0.5f;
        break;
    }

    lastX = x;
    lastY = y;
    glutPostRedisplay();
}

// 显示帮助信息
void showHelp() {
    printf("\n二维图形观察变换程序\n");
    printf("------------------------\n");
    printf("控制键:\n");
    printf("  W/S/A/D: 向上/下/左/右平移\n");
    printf("  +/ -: 放大/缩小\n");
    printf("  R/E: 顺时针/逆时针旋转\n");
    printf("  空格键: 重置变换\n");
    printf("  ESC: 退出程序\n");
    printf("\n鼠标控制:\n");
    printf("  左键拖动: 平移\n");
    printf("  右键拖动: 旋转\n");
}

// 主函数
int main(int argc, char** argv) {
    showHelp();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("二维图形观察变换");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutMainLoop();
    return 0;
}