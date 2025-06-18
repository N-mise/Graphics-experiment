#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

// ȫ�ֱ���
int projectionType = 1;  // 1:һ��͸��, 2:����͸��, 3:����͸��
int windowWidth = 800;
int windowHeight = 600;

// ���������㶨��
GLfloat pyramidVertices[5][3] = {
    {0.0, 1.0, 0.0},       // ��������
    {-1.0, -1.0, 1.0},     // �ײ�ǰ��
    {1.0, -1.0, 1.0},      // �ײ�ǰ��
    {1.0, -1.0, -1.0},     // �ײ�����
    {-1.0, -1.0, -1.0}     // �ײ�����
};

// �������涨�壨����������
GLint pyramidFaces[4][3] = {
    {0, 1, 2},  // ǰ��
    {0, 2, 3},  // ����
    {0, 3, 4},  // ����
    {0, 4, 1}   // ����
};

// ��ʼ��OpenGL����
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);  // ���ñ�����ɫΪ��ɫ
    glEnable(GL_DEPTH_TEST);           // ������Ȳ���
    glShadeModel(GL_SMOOTH);           // ����ƽ����ɫ
}

// ���ù�Դ
void setupLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_position[] = { 5.0, 5.0, 5.0, 1.0 };
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

// ���ò���
void setupMaterial() {
    GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 100.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

// ���ƽ�����
void drawPyramid() {
    // ���ù��գ�ʹ��ֱ����ɫ
    glDisable(GL_LIGHTING);

    glBegin(GL_TRIANGLES);

    // ǰ�� - ��ɫ
    glColor3f(1.0, 0.0, 0.0);
    glVertex3fv(pyramidVertices[0]);
    glVertex3fv(pyramidVertices[1]);
    glVertex3fv(pyramidVertices[2]);

    // ���� - ��ɫ
    glColor3f(0.0, 1.0, 0.0);
    glVertex3fv(pyramidVertices[0]);
    glVertex3fv(pyramidVertices[2]);
    glVertex3fv(pyramidVertices[3]);

    // ���� - ��ɫ
    glColor3f(0.0, 0.0, 1.0);
    glVertex3fv(pyramidVertices[0]);
    glVertex3fv(pyramidVertices[3]);
    glVertex3fv(pyramidVertices[4]);

    // ���� - ��ɫ
    glColor3f(1.0, 1.0, 0.0);
    glVertex3fv(pyramidVertices[0]);
    glVertex3fv(pyramidVertices[4]);
    glVertex3fv(pyramidVertices[1]);

    // ���� - ��ɫ
    glColor3f(1.0, 0.0, 1.0);
    glVertex3fv(pyramidVertices[1]);
    glVertex3fv(pyramidVertices[4]);
    glVertex3fv(pyramidVertices[3]);
    glVertex3fv(pyramidVertices[1]);
    glVertex3fv(pyramidVertices[3]);
    glVertex3fv(pyramidVertices[2]);

    glEnd();

    // �������ù���
    glEnable(GL_LIGHTING);
}

// ��ʾ�ص�����
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // ���ù۲��
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // ���ݵ�ǰͶӰ����Ӧ�ò�ͬ�ı任
    switch (projectionType) {
    case 1: // һ��͸��
        glRotatef(20.0, 1.0, 0.0, 0.0);  // ��΢��ת����ʾ3DЧ��
        break;
    case 2: // ����͸��
        glRotatef(30.0, 0.0, 1.0, 0.0);  // ��Y����ת
        glRotatef(15.0, 1.0, 0.0, 0.0);  // ��X����ת
        break;
    case 3: // ����͸��
        glRotatef(30.0, 0.0, 1.0, 0.0);  // ��Y����ת
        glRotatef(20.0, 1.0, 0.0, 0.0);  // ��X����ת
        glRotatef(10.0, 0.0, 0.0, 1.0);  // ��Z����ת
        break;
    default:
        break;
    }

    // ���ƽ�����
    drawPyramid();

    glutSwapBuffers();
}

// ���ڴ�С�ı�ص�����
void reshape(int width, int height) {
    windowWidth = width;
    windowHeight = height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // ����͸��ͶӰ
    gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

// ���̻ص�����
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '1':
        projectionType = 1;
        printf("�л���һ��͸��ͶӰ\n");
        break;
    case '2':
        projectionType = 2;
        printf("�л�������͸��ͶӰ\n");
        break;
    case '3':
        projectionType = 3;
        printf("�л�������͸��ͶӰ\n");
        break;
    case 27:  // ESC���˳�����
        exit(0);
        break;
    }
    glutPostRedisplay();
}

// ������ص����������ڷ�������ƣ�
void special(int key, int x, int y) {
    static float angleX = 0.0, angleY = 0.0;

    switch (key) {
    case GLUT_KEY_UP:
        angleX += 5.0;
        break;
    case GLUT_KEY_DOWN:
        angleX -= 5.0;
        break;
    case GLUT_KEY_LEFT:
        angleY += 5.0;
        break;
    case GLUT_KEY_RIGHT:
        angleY -= 5.0;
        break;
    }

    // ����ģ�ͱ任
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(angleX, 1.0, 0.0, 0.0);
    glRotatef(angleY, 0.0, 1.0, 0.0);

    glutPostRedisplay();
}

// ������
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("OpenGL͸��ͶӰ�任ʵ��");

    init();
    setupLighting();
    setupMaterial();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);

    printf("͸��ͶӰ�任ʵ��\n");
    printf("����1: һ��͸��ͶӰ\n");
    printf("����2: ����͸��ͶӰ\n");
    printf("����3: ����͸��ͶӰ\n");
    printf("ESC: �˳�����\n");
    printf("�����: ��ת��ͼ\n");

    glutMainLoop();
    return 0;
}