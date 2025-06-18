#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

// 定义裁剪窗口
#define X_MIN 100
#define X_MAX 300
#define Y_MIN 100
#define Y_MAX 300

// 定义区域码
#define INSIDE 0  // 0000
#define LEFT 1    // 0001
#define RIGHT 2   // 0010
#define BOTTOM 4  // 0100
#define TOP 8     // 1000

// 计算点的区域码
int computeCode(double x, double y) {
    int code = INSIDE;

    if (x < X_MIN)
        code |= LEFT;
    else if (x > X_MAX)
        code |= RIGHT;
    if (y < Y_MIN)
        code |= BOTTOM;
    else if (y > Y_MAX)
        code |= TOP;

    return code;
}

// Cohen - Sutherland线段裁剪算法
void cohenSutherlandClip(double x1, double y1, double x2, double y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    int accept = 0;

    while (1) {
        if (!(code1 | code2)) {
            // 线段完全在窗口内
            accept = 1;
            break;
        }
        else if (code1 & code2) {
            // 线段完全在窗口外
            break;
        }
        else {
            // 部分在窗口内
            int outsideCode;
            double x, y;

            outsideCode = code1 ? code1 : code2;

            if (outsideCode & TOP) {
                x = x1 + (x2 - x1) * (Y_MAX - y1) / (y2 - y1);
                y = Y_MAX;
            }
            else if (outsideCode & BOTTOM) {
                x = x1 + (x2 - x1) * (Y_MIN - y1) / (y2 - y1);
                y = Y_MIN;
            }
            else if (outsideCode & RIGHT) {
                y = y1 + (y2 - y1) * (X_MAX - x1) / (x2 - x1);
                x = X_MAX;
            }
            else if (outsideCode & LEFT) {
                y = y1 + (y2 - y1) * (X_MIN - x1) / (x2 - x1);
                x = X_MIN;
            }

            if (outsideCode == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
            else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept) {
        // 绘制裁剪后的线段
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
        glEnd();
    }
}

// 绘制裁剪窗口
void drawClippingWindow() {
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2d(X_MIN, Y_MIN);
    glVertex2d(X_MAX, Y_MIN);
    glVertex2d(X_MAX, Y_MAX);
    glVertex2d(X_MIN, Y_MAX);
    glEnd();
}

// 绘制原始线段
void drawOriginalLines() {
    glColor3f(0.0, 0.0, 1.0);
    // 多添加几条线
    double lines[][4] = {
        {50, 50, 350, 350},
        {20, 200, 400, 200},
        {150, 20, 150, 400},
        {50, 350, 350, 50}
    };

    for (int i = 0; i < sizeof(lines) / sizeof(lines[0]); i++) {
        glBegin(GL_LINES);
        glVertex2d(lines[i][0], lines[i][1]);
        glVertex2d(lines[i][2], lines[i][3]);
        glEnd();
    }
}

// 绘制裁剪后的线段
void drawClippedLines() {
    double lines[][4] = {
        {50, 50, 350, 350},
        {20, 200, 400, 200},
        {150, 20, 150, 400},
        {50, 350, 350, 50}
    };

    for (int i = 0; i < sizeof(lines) / sizeof(lines[0]); i++) {
        cohenSutherlandClip(lines[i][0], lines[i][1], lines[i][2], lines[i][3]);
    }
}

// 未裁剪窗口的显示回调函数
void displayOriginal() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawClippingWindow();
    drawOriginalLines();
    glFlush();
}

// 裁剪后窗口的显示回调函数
void displayClipped() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawClippingWindow();
    drawClippedLines();
    glFlush();
}

// 初始化OpenGL
void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

// 主函数
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // 创建未裁剪窗口
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    int originalWindow = glutCreateWindow("未发生裁剪");
    init();
    glutDisplayFunc(displayOriginal);

    // 创建裁剪后窗口
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(650, 100);
    int clippedWindow = glutCreateWindow("裁剪后");
    init();
    glutDisplayFunc(displayClipped);

    glutMainLoop();
    return 0;
}
