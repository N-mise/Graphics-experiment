#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

// �������ģʽ
#define MODE_POINT 0
#define MODE_LINE 1
#define MODE_RECTANGLE 2

// ����һ���ṹ�����洢���Ƶ�ͼ����Ϣ
typedef struct {
    int mode;
    int startX, startY;
    int endX, endY;
} Shape;

// ��̬�������洢���л��Ƶ�ͼ��
Shape* shapes = NULL;
int shapeCount = 0;
int shapeCapacity = 0;

int drawMode = MODE_POINT;
int startX, startY;
int endX, endY;
int isDrawing = 0;

// ��ʾ�ص�����
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    // ���������ѱ����ͼ��
    for (int i = 0; i < shapeCount; i++) {
        Shape shape = shapes[i];
        switch (shape.mode) {
        case MODE_POINT:
            glBegin(GL_POINTS);
            glVertex2i(shape.startX, shape.startY);
            glEnd();
            break;
        case MODE_LINE:
            glBegin(GL_LINES);
            glVertex2i(shape.startX, shape.startY);
            glVertex2i(shape.endX, shape.endY);
            glEnd();
            break;
        case MODE_RECTANGLE:
            glBegin(GL_QUADS);
            glVertex2i(shape.startX, shape.startY);
            glVertex2i(shape.endX, shape.startY);
            glVertex2i(shape.endX, shape.endY);
            glVertex2i(shape.startX, shape.endY);
            glEnd();
            break;
        }
    }

    // ���Ƶ�ǰ���ڻ��Ƶ�ͼ��
    if (isDrawing) {
        switch (drawMode) {
        case MODE_POINT:
            glBegin(GL_POINTS);
            glVertex2i(startX, startY);
            glEnd();
            break;
        case MODE_LINE:
            glBegin(GL_LINES);
            glVertex2i(startX, startY);
            glVertex2i(endX, endY);
            glEnd();
            break;
        case MODE_RECTANGLE:
            glBegin(GL_QUADS);
            glVertex2i(startX, startY);
            glVertex2i(endX, startY);
            glVertex2i(endX, endY);
            glVertex2i(startX, endY);
            glEnd();
            break;
        }
    }

    glutSwapBuffers();
}

// ���ص�����
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            startX = x;
            startY = glutGet(GLUT_WINDOW_HEIGHT) - y;
            isDrawing = 1;
        }
        else if (state == GLUT_UP) {
            endX = x;
            endY = glutGet(GLUT_WINDOW_HEIGHT) - y;
            isDrawing = 0;

            // ���浱ǰ���Ƶ�ͼ��
            if (shapeCount >= shapeCapacity) {
                shapeCapacity = shapeCapacity == 0 ? 1 : shapeCapacity * 2;
                shapes = (Shape*)realloc(shapes, shapeCapacity * sizeof(Shape));
            }
            shapes[shapeCount].mode = drawMode;
            shapes[shapeCount].startX = startX;
            shapes[shapeCount].startY = startY;
            shapes[shapeCount].endX = endX;
            shapes[shapeCount].endY = endY;
            shapeCount++;

            glutPostRedisplay();
        }
    }
}

// ���̻ص������������л�����ģʽ
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'p':
        drawMode = MODE_POINT;
        break;
    case 'l':
        drawMode = MODE_LINE;
        break;
    case 'r':
        drawMode = MODE_RECTANGLE;
        break;
    case 27: // ESC���˳�
        free(shapes);
        exit(0);
        break;
    }
    glutPostRedisplay();
}

// ��ʼ��OpenGL����
void init() {
    glClearColor(0.0, 1.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
}

// ������
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("GLUT Drawing");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    free(shapes);
    return 0;
}