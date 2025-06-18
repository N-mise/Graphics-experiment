#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

// 窗口大小
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

inline int round(const float a) {
    return static_cast<int>(a + 0.5f);  // 使用 static_cast 进行更明确的类型转换
}

// 绘制点，只保留一个定义
void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// DDA 
void lineDDA(int x0, int y0, int xEnd, int yEnd) {
    int dx = xEnd - x0, dy = yEnd - y0, steps;
    float xIncrement, yIncrement, x = static_cast<float>(x0), y = static_cast<float>(y0);  // 明确转换为 float

    // 确定步数
    if (fabs(dx) > fabs(dy)) {
        steps = abs(dx);
    }
    else {
        steps = abs(dy);
    }

    // 计算增量，明确用 float 参与运算
    xIncrement = static_cast<float>(dx) / static_cast<float>(steps);
    yIncrement = static_cast<float>(dy) / static_cast<float>(steps);

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
    glColor3f(1.0f, 1.0f, 1.0f);  // 数值后加 f 明确是 float 类型
    // 测试绘制三角形
    lineDDA(100, 100, 300, 100);  // 水平线
    lineDDA(100, 100, 200, 200);
    lineDDA(200, 200, 300, 100);
    glFlush();
}

// 初始化函数
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // 数值后加 f 明确是 float 类型
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
    glutCreateWindow("DAA算法画三角");  // 创建窗口
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}