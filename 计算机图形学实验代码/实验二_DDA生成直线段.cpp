#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

// 窗口大小
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;


inline int round(const float a) {
    return int(a + 0.5);
}

void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// DDA
void lineDDA(int x0, int y0, int xEnd, int yEnd) {
    int dx = xEnd - x0, dy = yEnd - y0, steps;
    float xIncrement, yIncrement, x = x0, y = y0;

    // 确定步数
    if (fabs(dx) > fabs(dy)) {
        steps = abs(dx);
    }
    else {
        steps = abs(dy);
    }

    // 计算增量
    xIncrement = float(dx) / float(steps);
    yIncrement = float(dy) / float(steps);

    // 绘制起始点
    setPixel(round(x), round(y));

    // 逐步绘制直线
    for (int k = 0; k < steps; k++) {
        x += xIncrement;
        y += yIncrement;
        setPixel(round(x), round(y));
    }
}

// 显示回调函数
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);  // 设置白色

    // 测试绘制多条直线
    lineDDA(100, 100, 300, 200);  // 斜线

    glFlush();
}

// 初始化函数
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);  // 设置黑色背景
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
}

// 主函数
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA直线算法演示");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}