#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ���ڴ�С
#define WIDTH 800
#define HEIGHT 600

// ��ͼö��
typedef enum {
    FRONT_VIEW,
    TOP_VIEW,
    SIDE_VIEW,
    ISO_VIEW      // �������������ͼ��ԭ��άͼ�Σ�
} ViewType;

// ��ǰ��ʾģʽ
typedef enum {
    MULTI_VIEW,  // ����ͼģʽ
    FULLSCREEN   // ȫ��ģʽ
} DisplayMode;

DisplayMode displayMode = MULTI_VIEW;
ViewType currentFullscreenView = FRONT_VIEW;

// �Զ���ͼ�ζ������ݣ�ʾ���������壩
GLfloat vertices[8][3] = {
    {-0.5, -0.5, -0.5},
    {0.5, -0.5, -0.5},
    {0.5, 0.5, -0.5},
    {-0.5, 0.5, -0.5},
    {-0.5, -0.5, 0.5},
    {0.5, -0.5, 0.5},
    {0.5, 0.5, 0.5},
    {-0.5, 0.5, 0.5}
};

// ��������Ķ�������
GLint faces[6][4] = {
    {0, 1, 2, 3}, // ǰ�� -Z
    {4, 5, 6, 7}, // ���� +Z
    {0, 3, 7, 4}, // ���� -X
    {1, 2, 6, 5}, // ���� +X
    {0, 1, 5, 4}, // ���� -Y
    {2, 3, 7, 6}  // ���� +Y
};

// ��ʼ��OpenGL����
void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);  // ������Ȳ��Ժ���
    glEnable(GL_CULL_FACE); // �������޳�
    glCullFace(GL_BACK);    // �޳�����
}

// ������ͼ
void setView(ViewType view) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // ʹ������ͶӰ��ȷ�������涼�ܿ���
    glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    switch (view) {
    case FRONT_VIEW:
        gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        break;
    case TOP_VIEW:
        gluLookAt(0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
        break;
    case SIDE_VIEW:
        gluLookAt(5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        break;
    case ISO_VIEW:
        // �������ͼ����������ȱ����۲�
        gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        break;
    }
}

// ����������
void drawAxes(void) {
    glLineWidth(2.0);

    // X�ᣨ��ɫ��
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(-2.0, 0.0, 0.0);
    glVertex3f(2.0, 0.0, 0.0);
    glEnd();

    // Y�ᣨ��ɫ��
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, -2.0, 0.0);
    glVertex3f(0.0, 2.0, 0.0);
    glEnd();

    // Z�ᣨ��ɫ��
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, -2.0);
    glVertex3f(0.0, 0.0, 2.0);
    glEnd();

    glLineWidth(1.0);
}

// �����Զ���ͼ�Σ������壩
void drawCustomObject(void) {
    for (int i = 0; i < 6; i++) {
        glBegin(GL_POLYGON);
        for (int j = 0; j < 4; j++) {
            // Ϊ��ͬ�����ò�ͬ��ɫ
            switch (i) {
            case 0: glColor3f(1.0, 0.0, 0.0); break; // ǰ�� - ��ɫ
            case 1: glColor3f(0.0, 1.0, 0.0); break; // ���� - ��ɫ
            case 2: glColor3f(0.0, 0.0, 1.0); break; // ���� - ��ɫ
            case 3: glColor3f(1.0, 1.0, 0.0); break; // ���� - ��ɫ
            case 4: glColor3f(1.0, 0.0, 1.0); break; // ���� - ��ɫ
            case 5: glColor3f(0.0, 1.0, 1.0); break; // ���� - ��ɫ
            }
            glVertex3fv(vertices[faces[i][j]]);
        }
        glEnd();
    }
}

// ��ʾ����ͼģʽ
void displayMultiView(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // �ӿ����� - ��Ϊ�ĸ�����
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);

    // ǰ��ͼ
    glViewport(0, h / 2, w / 2, h / 2);
    setView(FRONT_VIEW);
    drawAxes();
    drawCustomObject();

    // ����ͼ
    glViewport(w / 2, h / 2, w / 2, h / 2);
    setView(TOP_VIEW);
    drawAxes();
    drawCustomObject();

    // ����ͼ
    glViewport(0, 0, w / 2, h / 2);
    setView(SIDE_VIEW);
    drawAxes();
    drawCustomObject();

    // ԭ��άͼ�Σ��������ͼ��
    glViewport(w / 2, 0, w / 2, h / 2);
    setView(ISO_VIEW);
    drawAxes();
    drawCustomObject();
}

// ��ʾȫ����ͼ
void displayFullscreen(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);

    glViewport(0, 0, w, h);
    setView(currentFullscreenView);
    drawAxes();
    drawCustomObject();
}

// ��ʾ�ص�����
void display(void) {
    if (displayMode == MULTI_VIEW) {
        displayMultiView();
    }
    else {
        displayFullscreen();
    }

    glutSwapBuffers();
}

// ���ڴ�С�ı�ص�����
void reshape(int w, int h) {
    if (h == 0) h = 1;
    glutPostRedisplay();
}

// ���̻ص�����
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27: // ESC���˳�
        exit(0);
        break;
    case 'f': case 'F':
        currentFullscreenView = FRONT_VIEW;
        displayMode = FULLSCREEN;
        glutPostRedisplay();
        break;
    case 't': case 'T':
        currentFullscreenView = TOP_VIEW;
        displayMode = FULLSCREEN;
        glutPostRedisplay();
        break;
    case 's': case 'S':
        currentFullscreenView = SIDE_VIEW;
        displayMode = FULLSCREEN;
        glutPostRedisplay();
        break;
    case 'i': case 'I':
        currentFullscreenView = ISO_VIEW;
        displayMode = FULLSCREEN;
        glutPostRedisplay();
        break;
    case 'm': case 'M':
        displayMode = MULTI_VIEW;
        glutPostRedisplay();
        break;
    }
}

// ������
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("OpenGL 3D Views");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    // ��ʾʹ�ð���
    printf("���̿���:\n");
    printf("F: ȫ����ʾǰ��ͼ\n");
    printf("T: ȫ����ʾ����ͼ\n");
    printf("S: ȫ����ʾ����ͼ\n");
    printf("I: ȫ����ʾԭ��άͼ��\n");
    printf("M: ���ض���ͼģʽ\n");
    printf("ESC: �˳�����\n");

    glutMainLoop();
    return 0;
}