#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

// �ֶ����� M_PI ����
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ����ƽ���ı��εĶ���
GLfloat parallelogram[4][2] = {
    {100, 100},
    {200, 100},
    {250, 200},
    {150, 200}
};

// ����ƽ���ı���
void drawParallelogram(GLfloat vertices[4][2], GLfloat color[3]) {
    glColor3fv(color);
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++) {
        glVertex2fv(vertices[i]);
    }
    glEnd();
}

// ��ת�任
void rotate(GLfloat vertices[4][2], GLfloat angle) {
    GLfloat rad = angle * M_PI / 180.0;
    GLfloat cosA = cos(rad);
    GLfloat sinA = sin(rad);
    GLfloat newVertices[4][2];

    for (int i = 0; i < 4; i++) {
        newVertices[i][0] = vertices[i][0] * cosA - vertices[i][1] * sinA;
        newVertices[i][1] = vertices[i][0] * sinA + vertices[i][1] * cosA;
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            vertices[i][j] = newVertices[i][j];
        }
    }
}

// �����任
void scale(GLfloat vertices[4][2], GLfloat sx, GLfloat sy) {
    for (int i = 0; i < 4; i++) {
        vertices[i][0] *= sx;
        vertices[i][1] *= sy;
    }
}

// ƽ�Ʊ任
void translate(GLfloat vertices[4][2], GLfloat tx, GLfloat ty) {
    for (int i = 0; i < 4; i++) {
        vertices[i][0] += tx;
        vertices[i][1] += ty;
    }
}

// �ԳƱ任������ x �ᣩ
void reflectX(GLfloat vertices[4][2]) {
    for (int i = 0; i < 4; i++) {
        vertices[i][1] = -vertices[i][1];
    }
}

// ���б任
void shear(GLfloat vertices[4][2], GLfloat shx, GLfloat shy) {
    GLfloat newVertices[4][2];
    for (int i = 0; i < 4; i++) {
        newVertices[i][0] = vertices[i][0] + shx * vertices[i][1];
        newVertices[i][1] = vertices[i][1] + shy * vertices[i][0];
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            vertices[i][j] = newVertices[i][j];
        }
    }
}

// ��ʾ����
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // ԭʼƽ���ı���
    GLfloat originalColor[3] = { 1.0, 0.0, 0.0 };
    drawParallelogram(parallelogram, originalColor);

    // ��ת���ƽ���ı���
    GLfloat rotated[4][2];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            rotated[i][j] = parallelogram[i][j];
        }
    }
    rotate(rotated, 45);
    translate(rotated, 300, 0); // ����ƽ���Ա����ص�
    GLfloat rotatedColor[3] = { 0.0, 1.0, 0.0 };
    drawParallelogram(rotated, rotatedColor);

    // ���ź��ƽ���ı���
    GLfloat scaled[4][2];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            scaled[i][j] = parallelogram[i][j];
        }
    }
    scale(scaled, 1.5, 1.5);
    translate(scaled, 600, 0); // ��������ƽ��
    GLfloat scaledColor[3] = { 0.0, 0.0, 1.0 };
    drawParallelogram(scaled, scaledColor);

    // ƽ�ƺ��ƽ���ı���
    GLfloat translated[4][2];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            translated[i][j] = parallelogram[i][j];
        }
    }
    translate(translated, 100, 200); // ���º�����ƽ��
    GLfloat translatedColor[3] = { 1.0, 1.0, 0.0 };
    drawParallelogram(translated, translatedColor);

    // �Գƺ��ƽ���ı���
    GLfloat reflected[4][2];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            reflected[i][j] = parallelogram[i][j];
        }
    }
    reflectX(reflected);
    translate(reflected, 400, 200); // ���º�����ƽ��
    GLfloat reflectedColor[3] = { 1.0, 0.0, 1.0 };
    drawParallelogram(reflected, reflectedColor);

    // ���к��ƽ���ı���
    GLfloat sheared[4][2];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            sheared[i][j] = parallelogram[i][j];
        }
    }
    shear(sheared, 0.5, 0);
    translate(sheared, 750, 200); // ����ƽ������ȷ������ͼ����ʾ�ڴ�����
    GLfloat shearedColor[3] = { 0.0, 1.0, 1.0 };
    drawParallelogram(sheared, shearedColor);

    glFlush();
}

// ��ʼ������
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0, 1200, 0, 600); // ��������ͶӰ��Χ��������ͼ�������ռ�
}

// ������
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1200, 600); // ���󴰿ڴ�С
    glutCreateWindow("Parallelogram Transformations");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}