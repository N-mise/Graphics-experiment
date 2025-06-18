#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

// ���ڴ�С
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

inline int round(const float a) {
    return static_cast<int>(a + 0.5f);  // ʹ�� static_cast ���и���ȷ������ת��
}

// ���Ƶ㣬ֻ����һ������
void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// DDA 
void lineDDA(int x0, int y0, int xEnd, int yEnd) {
    int dx = xEnd - x0, dy = yEnd - y0, steps;
    float xIncrement, yIncrement, x = static_cast<float>(x0), y = static_cast<float>(y0);  // ��ȷת��Ϊ float

    // ȷ������
    if (fabs(dx) > fabs(dy)) {
        steps = abs(dx);
    }
    else {
        steps = abs(dy);
    }

    // ������������ȷ�� float ��������
    xIncrement = static_cast<float>(dx) / static_cast<float>(steps);
    yIncrement = static_cast<float>(dy) / static_cast<float>(steps);

    // ������ʼ��
    setPixel(round(x), round(y));

    // �𲽻���ֱ��
    for (int k = 0; k < steps; k++) {
        x += xIncrement;
        y += yIncrement;
        setPixel(round(x), round(y));
    }
}

// ��ʾ�ص�����
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);  // ��ֵ��� f ��ȷ�� float ����
    // ���Ի���������
    lineDDA(100, 100, 300, 100);  // ˮƽ��
    lineDDA(100, 100, 200, 200);
    lineDDA(200, 200, 300, 100);
    glFlush();
}

// ��ʼ������
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // ��ֵ��� f ��ȷ�� float ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
}

// ������
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DAA�㷨������");  // ��������
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}