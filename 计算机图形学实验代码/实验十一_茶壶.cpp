#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

// ȫ�ֱ���
float angleX = 0.0f;       // X����ת�Ƕ�
float angleY = 0.0f;       // Y����ת�Ƕ�
float scale = 1.0f;        // ���ű���
float translateX = 0.0f;   // X��ƽ����
float translateY = 0.0f;   // Y��ƽ����
float translateZ = -5.0f;  // Z��ƽ��������ʼλ�ã�
int isDragging = 0;        // �Ƿ������϶����
int lastX, lastY;          // ������λ��
int windowWidth = 800;
int windowHeight = 600;

// ��ʼ��OpenGL����
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);  // ���ñ�����ɫΪ��ɫ
    glEnable(GL_DEPTH_TEST);           // ������Ȳ���
    glEnable(GL_LIGHTING);             // ���ù���
    glEnable(GL_LIGHT0);               // ���ù�Դ0

    // ���ù�Դ
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // ���ò���
    GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 100.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

// ��ʾ�ص�����
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // �������λ��
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Ӧ�ñ任��ƽ�ơ���ת�����ţ�
    glTranslatef(translateX, translateY, translateZ);
    glRotatef(angleX, 1.0, 0.0, 0.0);  // ��X����ת
    glRotatef(angleY, 0.0, 1.0, 0.0);  // ��Y����ת
    glScalef(scale, scale, scale);      // ����

    // ����GLUT���
    glutSolidTeapot(1.0);

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

// ���̻ص���������ͨ����
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': case 'W':  // ��ǰ�ƶ���Z�Ḻ����
        translateZ += 0.1f;
        break;
    case 's': case 'S':  // ����ƶ���Z��������
        translateZ -= 0.1f;
        break;
    case 'a': case 'A':  // �����ƶ���X�Ḻ����
        translateX -= 0.1f;
        break;
    case 'd': case 'D':  // �����ƶ���X��������
        translateX += 0.1f;
        break;
    case 'q': case 'Q':  // ��С
        scale -= 0.05f;
        if (scale < 0.1f) scale = 0.1f;
        break;
    case 'e': case 'E':  // �Ŵ�
        scale += 0.05f;
        break;
    case 27:  // ESC���˳�����
        exit(0);
        break;
    }
    glutPostRedisplay();
}

// ���̻ص���������������緽�����
void special(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:    // ������ת��X�ᣩ
        angleX += 5.0f;
        break;
    case GLUT_KEY_DOWN:  // ������ת��X�ᣩ
        angleX -= 5.0f;
        break;
    case GLUT_KEY_LEFT:  // ������ת��Y�ᣩ
        angleY += 5.0f;
        break;
    case GLUT_KEY_RIGHT: // ������ת��Y�ᣩ
        angleY -= 5.0f;
        break;
    }
    glutPostRedisplay();
}

// ���ص�����
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isDragging = 1;
            lastX = x;
            lastY = y;
        }
        else {
            isDragging = 0;
        }
    }
}

// ����ƶ��ص������������϶���
void motion(int x, int y) {
    if (isDragging) {
        // ��������ƶ��Ĳ�ֵ
        int deltaX = x - lastX;
        int deltaY = y - lastY;

        // ������ת�Ƕ�
        angleY += deltaX * 0.5f;
        angleX += deltaY * 0.5f;

        // ����X����ת�Ƕȷ�Χ
        if (angleX > 90.0f) angleX = 90.0f;
        if (angleX < -90.0f) angleX = -90.0f;

        // �������λ��
        lastX = x;
        lastY = y;

        glutPostRedisplay();
    }
}

// ������
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("GLUT����۲����ʵ��");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    printf("GLUT����۲����ʵ��\n");
    printf("���Ʒ�ʽ:\n");
    printf("  �����: ��ת���\n");
    printf("  WASD: ƽ�Ʋ��\n");
    printf("  QE: ���Ų��\n");
    printf("  �������϶�: ��ת���\n");
    printf("  ESC: �˳�����\n");

    glutMainLoop();
    return 0;
}