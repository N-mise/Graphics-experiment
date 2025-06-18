#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

// 手动定义 M_PI 常量
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// 定义平行四边形的顶点
GLfloat parallelogram[4][2] = {
    {100, 100},
    {200, 100},
    {250, 200},
    {150, 200}
};

// 绘制平行四边形
void drawParallelogram(GLfloat vertices[4][2], GLfloat color[3]) {
    glColor3fv(color);
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++) {
        glVertex2fv(vertices[i]);
    }
    glEnd();
}

// 旋转变换
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

// 比例变换
void scale(GLfloat vertices[4][2], GLfloat sx, GLfloat sy) {
    for (int i = 0; i < 4; i++) {
        vertices[i][0] *= sx;
        vertices[i][1] *= sy;
    }
}

// 平移变换
void translate(GLfloat vertices[4][2], GLfloat tx, GLfloat ty) {
    for (int i = 0; i < 4; i++) {
        vertices[i][0] += tx;
        vertices[i][1] += ty;
    }
}

// 对称变换（关于 x 轴）
void reflectX(GLfloat vertices[4][2]) {
    for (int i = 0; i < 4; i++) {
        vertices[i][1] = -vertices[i][1];
    }
}

// 错切变换
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

// 显示函数
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // 原始平行四边形
    GLfloat originalColor[3] = { 1.0, 0.0, 0.0 };
    drawParallelogram(parallelogram, originalColor);

    // 旋转后的平行四边形
    GLfloat rotated[4][2];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            rotated[i][j] = parallelogram[i][j];
        }
    }
    rotate(rotated, 45);
    translate(rotated, 300, 0); // 向右平移以避免重叠
    GLfloat rotatedColor[3] = { 0.0, 1.0, 0.0 };
    drawParallelogram(rotated, rotatedColor);

    // 缩放后的平行四边形
    GLfloat scaled[4][2];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            scaled[i][j] = parallelogram[i][j];
        }
    }
    scale(scaled, 1.5, 1.5);
    translate(scaled, 600, 0); // 继续向右平移
    GLfloat scaledColor[3] = { 0.0, 0.0, 1.0 };
    drawParallelogram(scaled, scaledColor);

    // 平移后的平行四边形
    GLfloat translated[4][2];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            translated[i][j] = parallelogram[i][j];
        }
    }
    translate(translated, 100, 200); // 向下和向右平移
    GLfloat translatedColor[3] = { 1.0, 1.0, 0.0 };
    drawParallelogram(translated, translatedColor);

    // 对称后的平行四边形
    GLfloat reflected[4][2];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            reflected[i][j] = parallelogram[i][j];
        }
    }
    reflectX(reflected);
    translate(reflected, 400, 200); // 向下和向右平移
    GLfloat reflectedColor[3] = { 1.0, 0.0, 1.0 };
    drawParallelogram(reflected, reflectedColor);

    // 错切后的平行四边形
    GLfloat sheared[4][2];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            sheared[i][j] = parallelogram[i][j];
        }
    }
    shear(sheared, 0.5, 0);
    translate(sheared, 750, 200); // 调整平移量，确保错切图形显示在窗口内
    GLfloat shearedColor[3] = { 0.0, 1.0, 1.0 };
    drawParallelogram(sheared, shearedColor);

    glFlush();
}

// 初始化函数
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0, 1200, 0, 600); // 扩大正交投影范围，给错切图形留出空间
}

// 主函数
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1200, 600); // 增大窗口大小
    glutCreateWindow("Parallelogram Transformations");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}