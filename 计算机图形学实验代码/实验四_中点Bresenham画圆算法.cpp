#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
//画圆算法

// 窗口大小
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

// 初始化函数
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);  // 设置黑色背景
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
}

void setPixel(GLint xCoord, GLint yCoord) {
    glBegin(GL_POINTS);
    glVertex2i(xCoord, yCoord);
    glEnd();
}

class screenPt {
private:
    GLint x, y;
public:
    screenPt() {
        x = y = 0;
    }
    void setCoodrds(GLint xCoordValue, GLint yCoordValue) {
        x = xCoordValue;
        y = yCoordValue;
    }
    GLint getx() const {
        return x;
    }
    GLint gety() const {
        return y;
    }
    void incrementx() {
        x++;
    }
    void decrementy() {
        y--;
    }
};

// 修改 circlePlotPoints 函数以绘制四个象限的点
void circlePlotPoints(GLint xc, GLint yc, screenPt circPt) {
    setPixel(xc + circPt.getx(), yc + circPt.gety()); // 第一象限
    setPixel(xc - circPt.getx(), yc + circPt.gety()); // 第二象限
    setPixel(xc + circPt.getx(), yc - circPt.gety()); // 第四象限
    setPixel(xc - circPt.getx(), yc - circPt.gety()); // 第三象限

    // 同时绘制对称的另外四个点
    setPixel(xc + circPt.gety(), yc + circPt.getx());
    setPixel(xc - circPt.gety(), yc + circPt.getx());
    setPixel(xc + circPt.gety(), yc - circPt.getx());
    setPixel(xc - circPt.gety(), yc - circPt.getx());
}

void circleMidpoint(GLint xc, GLint yc, GLint radius) {
    screenPt circPt;
    GLint p = 1 - radius;
    circPt.setCoodrds(0, radius);

    while (circPt.getx() <= circPt.gety()) {
        circlePlotPoints(xc, yc, circPt);
        circPt.incrementx();
        if (p < 0)
            p += 2 * circPt.getx() + 1;
        else {
            circPt.decrementy();
            p += 2 * (circPt.getx() - circPt.gety()) + 1;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0); // 设置颜色为红色
    glPointSize(2.0); // 设置点的大小

    GLint xc = WINDOW_WIDTH / 2;
    GLint yc = WINDOW_HEIGHT / 2;
    GLint radius = 150;

    circleMidpoint(xc, yc, radius);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Circle Midpoint Algorithm");

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}