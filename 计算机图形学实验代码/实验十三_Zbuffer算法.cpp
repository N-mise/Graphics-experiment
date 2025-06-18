#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ����M_PI����
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ���ڳߴ�
const int WIDTH = 800;
const int HEIGHT = 600;

// ��ʼ�� OpenGL ����
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // ���ñ�����ɫΪ��ɫ
    glEnable(GL_DEPTH_TEST);               // ������Ȳ��ԣ�Z-buffer��
    glDepthFunc(GL_LESS);                  // ������ȱȽϺ���
}

// ����һ����ɫ������
void drawCube() {
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.5f);  // ����λ�ã�ʹ��������������ص�
    glScalef(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

    // ǰ��
    glColor3f(1.0f, 0.0f, 0.0f);  // ��ɫ
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    // ����
    glColor3f(0.0f, 1.0f, 0.0f);  // ��ɫ
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // ����
    glColor3f(0.0f, 0.0f, 1.0f);  // ��ɫ
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    // ����
    glColor3f(1.0f, 1.0f, 0.0f);  // ��ɫ
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // ����
    glColor3f(1.0f, 0.0f, 1.0f);  // ��ɫ
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // ����
    glColor3f(0.0f, 1.0f, 1.0f);  // ��ɫ
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    glEnd();
    glPopMatrix();
}

// ����һ����ɫ������
void drawPyramid() {
    glPushMatrix();
    glTranslatef(0.5f, 0.0f, 0.0f);  // ����λ�ã�ʹ���������岿���ص�
    glScalef(1.0f, 1.0f, 1.0f);

    glBegin(GL_TRIANGLES);

    // ǰ��
    glColor3f(1.0f, 0.0f, 0.0f);  // ��ɫ
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // ����
    glColor3f(0.0f, 1.0f, 0.0f);  // ��ɫ
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // ����
    glColor3f(0.0f, 0.0f, 1.0f);  // ��ɫ
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // ����
    glColor3f(1.0f, 1.0f, 0.0f);  // ��ɫ
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    glEnd();

    // ���棨�����Σ�
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);  // ��ɫ
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glEnd();

    glPopMatrix();
}

// ��������ϵ
void drawCoordinateSystem() {
    glPushMatrix();

    // ����X�ᣨ��ɫ��
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(-5.0f, 0.0f, 0.0f);
    glVertex3f(5.0f, 0.0f, 0.0f);
    glEnd();

    // ����Y�ᣨ��ɫ��
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, -5.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 0.0f);
    glEnd();

    // ����Z�ᣨ��ɫ��
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, -5.0f);
    glVertex3f(0.0f, 0.0f, 5.0f);
    glEnd();

    glPopMatrix();
}

// ��ʾ�ص�����
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // �����ɫ����������Ȼ�����

    // ���ù۲����
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // ��������ϵ
    drawCoordinateSystem();

    // ���Ƴ����е����壨�Ȼ��������壬�ٻ��ƽ�������
    drawCube();
    drawPyramid();

    glutSwapBuffers();  // ����ǰ�󻺳���
}

// �������ڴ�С�ص�����
void reshape(int width, int height) {
    if (height == 0) height = 1;
    float aspect = (float)width / (float)height;

    // �����ӿ�
    glViewport(0, 0, width, height);

    // ����ͶӰ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 0.1, 100.0);
}

// ���̻ص�����
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27:     // ESC���˳�����
        exit(0);
        break;
    }
}

// ������
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  // ����˫�������Ȼ���
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("OpenGL Z-buffer �ص���ʾ");

    init();  // ��ʼ��OpenGL����

    // ���ûص�����
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();  // ����GLUT��ѭ��
    return 0;
}