#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

// ���ڴ�С
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

    // ȷ������
    if (fabs(dx) > fabs(dy)) {
        steps = abs(dx);
    }
    else {
        steps = abs(dy);
    }

    // ��������
    xIncrement = float(dx) / float(steps);
    yIncrement = float(dy) / float(steps);

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
    glColor3f(1.0, 1.0, 1.0);  // ���ð�ɫ

    // ���Ի��ƶ���ֱ��
    lineDDA(100, 100, 300, 200);  // б��

    glFlush();
}

// ��ʼ������
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);  // ���ú�ɫ����
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
    glutCreateWindow("DDAֱ���㷨��ʾ");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}