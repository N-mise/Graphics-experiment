#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ������Ƶ������ͽ���
#define CONTROL_POINTS_1D 4
#define CONTROL_POINTS_2D 4
#define DEGREE_1D 3
#define DEGREE_2D 3

// ���Ƶ����ݽṹ
typedef struct {
    float x, y, z;
} Point3D;

// 1D���Ƶ�
Point3D controlPoints1D[CONTROL_POINTS_1D] = {
    {-0.8, -0.5, 0.0},
    {-0.4, 0.5, 0.0},
    {0.4, 0.5, 0.0},
    {0.8, -0.5, 0.0}
};

// 2D���Ƶ�����
Point3D controlPoints2D[CONTROL_POINTS_2D][CONTROL_POINTS_2D] = {
    {{-0.8, -0.8, -0.5}, {-0.4, -0.8, 0.5}, {0.4, -0.8, 0.5}, {0.8, -0.8, -0.5}},
    {{-0.8, -0.4, 0.5}, {-0.4, -0.4, 1.0}, {0.4, -0.4, 1.0}, {0.8, -0.4, 0.5}},
    {{-0.8, 0.4, 0.5}, {-0.4, 0.4, 1.0}, {0.4, 0.4, 1.0}, {0.8, 0.4, 0.5}},
    {{-0.8, 0.8, -0.5}, {-0.4, 0.8, 0.5}, {0.4, 0.8, 0.5}, {0.8, 0.8, -0.5}}
};

// ��ʾģʽ
enum DisplayMode {
    MODE_BOTH,
    MODE_CURVE,
    MODE_SURFACE
};
enum DisplayMode currentMode = MODE_BOTH;

// ���ɾ���B�����ڵ�����
void generateUniformKnotVector(int n, int p, float* U) {
    int m = n + p + 1;
    for (int i = 0; i <= m; i++) {
        if (i <= p) {
            U[i] = 0.0f;
        }
        else if (i >= n + 1) {
            U[i] = 1.0f;
        }
        else {
            U[i] = (float)(i - p) / (float)(n - p + 1);
        }
    }
}

// ����B����������ֵ
float basisFunction(int i, int p, float u, float* U) {
    if (p == 0) {
        return (u >= U[i] && u < U[i + 1]) || (u == U[i + 1] && U[i + 1] != U[i + p + 1]) ? 1.0f : 0.0f;
    }

    float d1 = U[i + p] - U[i];
    float d2 = U[i + p + 1] - U[i + 1];

    float c1 = (d1 > 0) ? (u - U[i]) / d1 : 0.0f;
    float c2 = (d2 > 0) ? (U[i + p + 1] - u) / d2 : 0.0f;

    return c1 * basisFunction(i, p - 1, u, U) + c2 * basisFunction(i + 1, p - 1, u, U);
}

// ����B���������ϵĵ�
Point3D evaluateBSplineCurve(float u, Point3D* controlPoints, int n, int p, float* U) {
    Point3D result = { 0.0f, 0.0f, 0.0f };

    for (int i = 0; i <= n; i++) {
        float N = basisFunction(i, p, u, U);
        result.x += N * controlPoints[i].x;
        result.y += N * controlPoints[i].y;
        result.z += N * controlPoints[i].z;
    }

    return result;
}

// ����B���������ϵĵ�
Point3D evaluateBSplineSurface(float u, float v, Point3D controlPoints[][CONTROL_POINTS_2D],
    int n, int m, int p, int q, float* U, float* V) {
    Point3D result = { 0.0f, 0.0f, 0.0f };

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            float Nu = basisFunction(i, p, u, U);
            float Nv = basisFunction(j, q, v, V);
            float weight = Nu * Nv;

            result.x += weight * controlPoints[i][j].x;
            result.y += weight * controlPoints[i][j].y;
            result.z += weight * controlPoints[i][j].z;
        }
    }

    return result;
}

// ��ʼ������
void initLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    // ���ù�Դ����
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // ����ȫ�ֻ�����
    GLfloat global_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
}

// ��ʾ����
void displayCurve() {
    // ���ɲ�����B��������
    float U[CONTROL_POINTS_1D + DEGREE_1D + 1];
    generateUniformKnotVector(CONTROL_POINTS_1D - 1, DEGREE_1D, U);

    // �������߲���
    GLfloat curve_ambient[] = { 0.0, 0.2, 0.4, 1.0 };
    GLfloat curve_diffuse[] = { 0.0, 0.6, 1.0, 1.0 };
    GLfloat curve_specular[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat curve_shininess = 64.0;

    glMaterialfv(GL_FRONT, GL_AMBIENT, curve_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, curve_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, curve_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, curve_shininess);

    glLineWidth(3.0);
    glBegin(GL_LINE_STRIP);
    for (float u = 0.0; u <= 1.0; u += 0.01) {
        Point3D p = evaluateBSplineCurve(u, controlPoints1D, CONTROL_POINTS_1D - 1, DEGREE_1D, U);
        // �������ߵķ��������򻯴���
        Point3D p_next = evaluateBSplineCurve(u + 0.01, controlPoints1D, CONTROL_POINTS_1D - 1, DEGREE_1D, U);
        float nx = p_next.y - p.y;
        float ny = -(p_next.x - p.x);
        float nz = 0.0;
        float len = sqrt(nx * nx + ny * ny + nz * nz);
        if (len > 0) {
            nx /= len;
            ny /= len;
            nz /= len;
        }
        glNormal3f(nx, ny, nz);
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();

    // �������߿��Ƶ�
    GLfloat control_point_ambient[] = { 0.6, 0.0, 0.6, 1.0 };
    GLfloat control_point_diffuse[] = { 1.0, 0.0, 1.0, 1.0 };
    GLfloat control_point_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat control_point_shininess = 32.0;

    glMaterialfv(GL_FRONT, GL_AMBIENT, control_point_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, control_point_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, control_point_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, control_point_shininess);

    glPointSize(8.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < CONTROL_POINTS_1D; i++) {
        glNormal3f(0.0, 0.0, 1.0);
        glVertex3f(controlPoints1D[i].x, controlPoints1D[i].y, controlPoints1D[i].z);
    }
    glEnd();

    // ���ƿ��ƶ����
    glLineWidth(1.0);
    glColor3f(0.8, 0.4, 0.8);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < CONTROL_POINTS_1D; i++) {
        glVertex3f(controlPoints1D[i].x, controlPoints1D[i].y, controlPoints1D[i].z);
    }
    glEnd();
}

// ��ʾ����
void displaySurface() {
    // ���ɲ�����B��������
    float U[CONTROL_POINTS_2D + DEGREE_2D + 1];
    float V[CONTROL_POINTS_2D + DEGREE_2D + 1];
    generateUniformKnotVector(CONTROL_POINTS_2D - 1, DEGREE_2D, U);
    generateUniformKnotVector(CONTROL_POINTS_2D - 1, DEGREE_2D, V);

    // �����������
    GLfloat surface_ambient[] = { 0.0, 0.4, 0.2, 1.0 };
    GLfloat surface_diffuse[] = { 0.0, 0.8, 0.4, 1.0 };
    GLfloat surface_specular[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat surface_shininess = 32.0;

    glMaterialfv(GL_FRONT, GL_AMBIENT, surface_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, surface_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, surface_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, surface_shininess);

    glBegin(GL_QUADS);
    for (float u = 0.0; u < 1.0; u += 0.05) {
        for (float v = 0.0; v < 1.0; v += 0.05) {
            Point3D p1 = evaluateBSplineSurface(u, v, controlPoints2D,
                CONTROL_POINTS_2D - 1, CONTROL_POINTS_2D - 1,
                DEGREE_2D, DEGREE_2D, U, V);
            Point3D p2 = evaluateBSplineSurface(u + 0.05, v, controlPoints2D,
                CONTROL_POINTS_2D - 1, CONTROL_POINTS_2D - 1,
                DEGREE_2D, DEGREE_2D, U, V);
            Point3D p3 = evaluateBSplineSurface(u + 0.05, v + 0.05, controlPoints2D,
                CONTROL_POINTS_2D - 1, CONTROL_POINTS_2D - 1,
                DEGREE_2D, DEGREE_2D, U, V);
            Point3D p4 = evaluateBSplineSurface(u, v + 0.05, controlPoints2D,
                CONTROL_POINTS_2D - 1, CONTROL_POINTS_2D - 1,
                DEGREE_2D, DEGREE_2D, U, V);

            // ���㷨������ʹ�ò����
            float v1x = p2.x - p1.x;
            float v1y = p2.y - p1.y;
            float v1z = p2.z - p1.z;

            float v2x = p4.x - p1.x;
            float v2y = p4.y - p1.y;
            float v2z = p4.z - p1.z;

            float nx = v1y * v2z - v1z * v2y;
            float ny = v1z * v2x - v1x * v2z;
            float nz = v1x * v2y - v1y * v2x;

            float len = sqrt(nx * nx + ny * ny + nz * nz);
            if (len > 0) {
                nx /= len;
                ny /= len;
                nz /= len;
            }

            glNormal3f(nx, ny, nz);
            glVertex3f(p1.x, p1.y, p1.z);

            glNormal3f(nx, ny, nz);
            glVertex3f(p2.x, p2.y, p2.z);

            glNormal3f(nx, ny, nz);
            glVertex3f(p3.x, p3.y, p3.z);

            glNormal3f(nx, ny, nz);
            glVertex3f(p4.x, p4.y, p4.z);
        }
    }
    glEnd();

    // ����������Ƶ�����
    GLfloat control_point_ambient[] = { 0.8, 0.4, 0.0, 1.0 };
    GLfloat control_point_diffuse[] = { 1.0, 0.5, 0.0, 1.0 };
    GLfloat control_point_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat control_point_shininess = 32.0;

    glMaterialfv(GL_FRONT, GL_AMBIENT, control_point_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, control_point_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, control_point_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, control_point_shininess);

    glPointSize(6.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < CONTROL_POINTS_2D; i++) {
        for (int j = 0; j < CONTROL_POINTS_2D; j++) {
            glNormal3f(0.0, 0.0, 1.0);
            glVertex3f(controlPoints2D[i][j].x, controlPoints2D[i][j].y, controlPoints2D[i][j].z);
        }
    }
    glEnd();

    // ���ƿ���������
    glLineWidth(1.0);
    glColor3f(0.8, 0.5, 0.0);

    // �з���
    for (int i = 0; i < CONTROL_POINTS_2D; i++) {
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < CONTROL_POINTS_2D; j++) {
            glVertex3f(controlPoints2D[i][j].x, controlPoints2D[i][j].y, controlPoints2D[i][j].z);
        }
        glEnd();
    }

    // �з���
    for (int j = 0; j < CONTROL_POINTS_2D; j++) {
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < CONTROL_POINTS_2D; i++) {
            glVertex3f(controlPoints2D[i][j].x, controlPoints2D[i][j].y, controlPoints2D[i][j].z);
        }
        glEnd();
    }
}

// ��ʾ�ص�����
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // �����ӽ�
    if (currentMode == MODE_CURVE) {
        gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    }
    else {
        gluLookAt(3.0, 3.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    }

    // ����������
    glDisable(GL_LIGHTING);
    glLineWidth(2.0);

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(-2.0, 0.0, 0.0);
    glVertex3f(2.0, 0.0, 0.0);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, -2.0, 0.0);
    glVertex3f(0.0, 2.0, 0.0);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, -2.0);
    glVertex3f(0.0, 0.0, 2.0);
    glEnd();

    glEnable(GL_LIGHTING);

    // ���ݵ�ǰģʽ��ʾ���߻�����
    if (currentMode == MODE_BOTH || currentMode == MODE_CURVE) {
        displayCurve();
    }

    if (currentMode == MODE_BOTH || currentMode == MODE_SURFACE) {
        displaySurface();
    }

    // ��ʾ������Ϣ
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(-1.0, 0.9);
    const char* helpText = "1: ��ʾ����  2: ��ʾ����  3: ��ʾ���ߺ�����  ESC: �˳�";
    for (int i = 0; helpText[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, helpText[i]);
    }

    glutSwapBuffers();
}

// �������ڴ�С�ص�����
void reshape(int width, int height) {
    if (height == 0) height = 1;
    float aspect = (float)width / (float)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

// ���̻ص�����
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '1':
        currentMode = MODE_CURVE;
        break;
    case '2':
        currentMode = MODE_SURFACE;
        break;
    case '3':
        currentMode = MODE_BOTH;
        break;
    case 27: // ESC���˳�
        exit(0);
        break;
    }
    glutPostRedisplay();
}

// ������
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("B����������������ʵ��");

    glClearColor(0.1, 0.1, 0.15, 1.0);

    initLighting();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}