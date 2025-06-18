#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

// ���ڳߴ�
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// ��ʼ��OpenGL����
void init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // ���ñ���ɫΪ��ɫ
    glEnable(GL_DEPTH_TEST); // ������Ȳ���

    // ���ù���
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // ���ù�Դλ�ú�����
    GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

// ���ƹ⻬��ɫ��������
void drawSmoothTriangle() {
    glPushMatrix();
    glTranslatef(-0.7f, 0.0f, 0.0f); // ����ƽ��

    // ���������β������ԣ��⻬��ɫ��
    glShadeModel(GL_SMOOTH); // ���ù⻬��ɫ

    // ����������
    glBegin(GL_TRIANGLES);
    // ����1 - ��ɫ
    glNormal3f(0.0f, 0.0f, 1.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.0f);

    // ����2 - ��ɫ
    glNormal3f(0.0f, 0.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.0f);

    // ����3 - ��ɫ
    glNormal3f(0.0f, 0.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();

    glPopMatrix();
}

// ����ƽ����ɫ��ƽ���ı���
void drawFlatParallelogram() {
    glPushMatrix();
    glTranslatef(0.7f, 0.0f, 0.0f); // ����ƽ��

    // ����ƽ���ı��β������ԣ�ƽ����ɫ��
    glShadeModel(GL_FLAT); // ����ƽ����ɫ

    // ƽ����ɫ��ÿ��ͼԪ������Σ�ָֻ��һ������������ɫ
    glNormal3f(0.0f, 0.0f, 1.0f);
    glColor3f(0.5f, 0.5f, 1.0f); // ��ɫ��

    // ����ƽ���ı���
    glBegin(GL_QUADS);
    glVertex3f(-0.6f, -0.4f, 0.0f);
    glVertex3f(0.4f, -0.4f, 0.0f);
    glVertex3f(0.6f, 0.4f, 0.0f);
    glVertex3f(-0.4f, 0.4f, 0.0f);
    glEnd();

    glPopMatrix();
}

// ��ʾ�ص�����
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // �����ӽ�
    gluLookAt(0.0f, 0.0f, 5.0f,  // ���λ��
        0.0f, 0.0f, 0.0f,  // �۲��
        0.0f, 1.0f, 0.0f); // �Ϸ���

    // ��������ϵ
    glDisable(GL_LIGHTING);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    // X�� - ��ɫ
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-2.0f, 0.0f, 0.0f);
    glVertex3f(2.0f, 0.0f, 0.0f);
    // Y�� - ��ɫ
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -2.0f, 0.0f);
    glVertex3f(0.0f, 2.0f, 0.0f);
    // Z�� - ��ɫ
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -2.0f);
    glVertex3f(0.0f, 0.0f, 2.0f);
    glEnd();
    glEnable(GL_LIGHTING);

    // ���ƹ⻬��ɫ������
    drawSmoothTriangle();

    // ����ƽ����ɫƽ���ı���
    drawFlatParallelogram();

    glutSwapBuffers();
}

// �������ڴ�С�ص�����
void reshape(int width, int height) {
    if (height == 0) height = 1;
    float aspect = (float)width / (float)height;

    glViewport(0, 0, width, height);

    // ����͸��ͶӰ
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);

    // ����ģ����ͼ����
    glMatrixMode(GL_MODELVIEW);
}

// ������
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("OpenGL��ɫ��ʾ");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}