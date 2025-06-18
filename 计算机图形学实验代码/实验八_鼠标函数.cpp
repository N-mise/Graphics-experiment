#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

// 定义绘制模式
#define MODE_POINT 0
#define MODE_LINE 1
#define MODE_RECTANGLE 2

// 定义一个结构体来存储绘制的图形信息
typedef struct {
    int mode;
    int startX, startY;
    int endX, endY;
} Shape;

// 动态数组来存储所有绘制的图形
Shape* shapes = NULL;
int shapeCount = 0;
int shapeCapacity = 0;

int drawMode = MODE_POINT;
int startX, startY;
int endX, endY;
int isDrawing = 0;

// 显示回调函数
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    // 绘制所有已保存的图形
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

    // 绘制当前正在绘制的图形
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

// 鼠标回调函数
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

            // 保存当前绘制的图形
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

// 键盘回调函数，用于切换绘制模式
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
    case 27: // ESC键退出
        free(shapes);
        exit(0);
        break;
    }
    glutPostRedisplay();
}

// 初始化OpenGL设置
void init() {
    glClearColor(0.0, 1.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
}

// 主函数
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