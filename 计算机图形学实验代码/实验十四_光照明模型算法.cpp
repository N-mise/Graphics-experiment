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

// ���ղ���
GLfloat light_position[] = { 5.0f, 5.0f, 5.0f, 1.0f };  // ��Դλ��
GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };   // ������
GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };   // �������
GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // ���淴���

// ���ʲ���
GLfloat material_ambient[] = { 0.2f, 0.2f, 0.8f, 1.0f };    // ���廷���ⷴ��
GLfloat material_diffuse[] = { 0.2f, 0.2f, 0.8f, 1.0f };    // ����������
GLfloat material_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };   // ���徵�淴��
GLfloat material_shininess = 50.0f;                        // ��������

// ƽ�����
GLfloat plane_ambient[] = { 0.2f, 0.8f, 0.2f, 1.0f };       // ƽ�滷���ⷴ��
GLfloat plane_diffuse[] = { 0.2f, 0.8f, 0.2f, 1.0f };       // ƽ��������
GLfloat plane_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };      // ƽ�澵�淴��
GLfloat plane_shininess = 30.0f;                           // ƽ������

// �ӽǲ���
float camera_angle = 0.0f;
float camera_distance = 10.0f;

// ��ʼ�� OpenGL ����
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // ���ñ�����ɫΪ��ɫ
    glEnable(GL_DEPTH_TEST);               // ������Ȳ���

    // ���ù���
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // ���ù�������
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // ���÷��߹�һ��
    glEnable(GL_NORMALIZE);
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

// ��������
void drawSphere() {
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f);  // �����������ƽ���Ϸ�

    // ���������������
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, material_shininess);

    // ��������
    glutSolidSphere(1.0f, 32, 32);

    glPopMatrix();
}

// ����ƽ��
void drawPlane() {
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 0.0f);  // ��ƽ�������Y=-1λ��

    // ����ƽ���������
    glMaterialfv(GL_FRONT, GL_AMBIENT, plane_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, plane_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, plane_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, plane_shininess);

    // ����ƽ��
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);  // ƽ�淨�߳���
    glVertex3f(-5.0f, 0.0f, -5.0f);
    glVertex3f(5.0f, 0.0f, -5.0f);
    glVertex3f(5.0f, 0.0f, 5.0f);
    glVertex3f(-5.0f, 0.0f, 5.0f);
    glEnd();

    glPopMatrix();
}

// ��ʾ�ص�����
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // �����ɫ����������Ȼ�����

    // ���ù۲����
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // �������λ��
    float camX = camera_distance * sin(camera_angle);
    float camZ = camera_distance * cos(camera_angle);
    gluLookAt(camX, 3.0f, camZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // ��������ϵ
    drawCoordinateSystem();

    // ���Ƴ����е�����
    drawPlane();
    drawSphere();

    // ���ƹ�Դλ�ã�С�����壩
    glPushMatrix();
    glTranslatef(light_position[0], light_position[1], light_position[2]);
    glColor3f(1.0f, 1.0f, 0.0f);  // ��ɫ��ʾ��Դ
    glutSolidCube(0.2f);
    glPopMatrix();

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

// ��ʱ���ص�������������ת���
void timer(int value) {
    camera_angle += 0.01f;
    if (camera_angle > 2 * M_PI) camera_angle -= 2 * M_PI;

    glutPostRedisplay();  // ��ǵ�ǰ������Ҫ���»���
    glutTimerFunc(16, timer, 0);  // ������һ�ζ�ʱ���ص���Լ60֡/��
}

// ���̻ص�����
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27:     // ESC���˳�����
        exit(0);
        break;
    case 'w':    // �����ƶ���Դ
        light_position[1] += 0.5f;
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        break;
    case 's':    // �����ƶ���Դ
        light_position[1] -= 0.5f;
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        break;
    case 'a':    // �����ƶ���Դ
        light_position[0] -= 0.5f;
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        break;
    case 'd':    // �����ƶ���Դ
        light_position[0] += 0.5f;
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        break;
    case 'q':    // ��ǰ�ƶ���Դ
        light_position[2] -= 0.5f;
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        break;
    case 'e':    // ����ƶ���Դ
        light_position[2] += 0.5f;
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        break;
    case '+':    // ������������
        material_shininess += 5.0f;
        if (material_shininess > 128.0f) material_shininess = 128.0f;
        break;
    case '-':    // ������������
        material_shininess -= 5.0f;
        if (material_shininess < 1.0f) material_shininess = 1.0f;
        break;
    }
}

// ������
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  // ����˫�������Ȼ���
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Pong����ģ����ʾ");

    init();  // ��ʼ��OpenGL����

    // ���ûص�����
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);  // ���ö�ʱ���ص�

    glutMainLoop();  // ����GLUT��ѭ��
    return 0;
}