//��λ�۲�仯�㷨��P190��

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ���ڳߴ�
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// �۲����
float translateX = 0.0f;
float translateY = 0.0f;
float scale = 1.0f;
float rotation = 0.0f;

// ��ͼ����
float viewCenterX = 0.0f;
float viewCenterY = 0.0f;

// ���״̬
int mouseButton = -1;
int lastX, lastY;

// ��ʼ��OpenGL����
void init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // ���ñ���ɫΪ��ɫ
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-WINDOW_WIDTH / 2, WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2, WINDOW_HEIGHT / 2);
}

// ��������ϵ
void drawCoordinateSystem() {
    glColor3f(0.5f, 0.5f, 0.5f);  // ��ɫ
    glLineWidth(1.0f);

    // X��
    glBegin(GL_LINES);
    glVertex2f(-WINDOW_WIDTH / 2, 0);
    glVertex2f(WINDOW_WIDTH / 2, 0);
    // Y��
    glVertex2f(0, -WINDOW_HEIGHT / 2);
    glVertex2f(0, WINDOW_HEIGHT / 2);
    glEnd();
}

// ���Ƽ򻯵Ķ�άͼ�Σ����ص���
void drawShapes() {
    // ����һ����ɫ�����Σ��ϰ벿�֣�
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-100.0f, 50.0f);
    glVertex2f(100.0f, 50.0f);
    glVertex2f(0.0f, 200.0f);
    glEnd();

    // ����һ����ɫ���Σ��°벿�֣�
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-100.0f, -200.0f);
    glVertex2f(100.0f, -200.0f);
    glVertex2f(100.0f, -50.0f);
    glVertex2f(-100.0f, -50.0f);
    glEnd();
}

// ��ʾ�ص�����
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Ӧ�ù۲�任
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // ƽ�Ƶ���ͼ����
    glTranslatef(viewCenterX, viewCenterY, 0.0f);

    // Ӧ���û��任
    glTranslatef(translateX, translateY, 0.0f);
    glRotatef(rotation, 0.0f, 0.0f, 1.0f);
    glScalef(scale, scale, 1.0f);

    // ��������ϵ��ͼ��
    drawCoordinateSystem();
    drawShapes();

    glutSwapBuffers();
}

// ���ڴ�С�ı�ص�����
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

// ���̻ص�����
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
    case ' ':  // ���ñ任
        translateX = 0.0f;
        translateY = 0.0f;
        scale = 1.0f;
        rotation = 0.0f;
        break;
    case 27:  // ESC���˳�
        exit(0);
        break;
    }
    glutPostRedisplay();
}

// ������ص�����
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

// ����ƶ��ص�����
void motion(int x, int y) {
    int dx = x - lastX;
    int dy = y - lastY;

    switch (mouseButton) {
    case GLUT_LEFT_BUTTON:  // ����϶� - ƽ��
        translateX += dx;
        translateY -= dy;  // ע�⣺���������y�����£������������y������
        break;
    case GLUT_RIGHT_BUTTON:  // �Ҽ��϶� - ��ת
        rotation += dx * 0.5f;
        break;
    }

    lastX = x;
    lastY = y;
    glutPostRedisplay();
}

// ��ʾ������Ϣ
void showHelp() {
    printf("\n��άͼ�ι۲�任����\n");
    printf("------------------------\n");
    printf("���Ƽ�:\n");
    printf("  W/S/A/D: ����/��/��/��ƽ��\n");
    printf("  +/ -: �Ŵ�/��С\n");
    printf("  R/E: ˳ʱ��/��ʱ����ת\n");
    printf("  �ո��: ���ñ任\n");
    printf("  ESC: �˳�����\n");
    printf("\n������:\n");
    printf("  ����϶�: ƽ��\n");
    printf("  �Ҽ��϶�: ��ת\n");
}

// ������
int main(int argc, char** argv) {
    showHelp();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("��άͼ�ι۲�任");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutMainLoop();
    return 0;
}