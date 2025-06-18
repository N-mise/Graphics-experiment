#include <GL/glut.h>
//图元实验
GLsizei winWidth = 600, winHeight = 500;
GLint xRaster = 25, yRaster = 150;
GLubyte label[36] = { 'J','a','n', 'F','e','b',  'M','a','r',
                      'A','p','r', 'M','a','y',  'J','u','n',
                      'J','u','l', 'A','u','g',  'S','e','p',
                      'O','c','t', 'N','o','v',  'D','e','c' };
GLint dataValue[12] = { 420,342,324,310,262,185,
                        190,196,217,240,312,438 };

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 600.0, 0.0, 500.0);
}

void drawAxes() {
    glColor3f(0.0, 0.0, 0.0);
    // 绘制 x 轴
    glBegin(GL_LINES);
    glVertex2i(50, 50);
    glVertex2i(winWidth - 50, 50);
    // 绘制 y 轴
    glVertex2i(50, 50);
    glVertex2i(50, winHeight - 50);
    glEnd();

    // 绘制 x 轴刻度和标签
    for (int i = 0; i < 12; i++) {
        int x = 50 + i * 50;
        glBegin(GL_LINES);
        glVertex2i(x, 50);
        glVertex2i(x, 45);
        glEnd();
        glRasterPos2i(x - 10, 20);
        for (int k = 3 * i; k < 3 * i + 3; k++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[k]);
    }

    // 绘制 y 轴刻度
    for (int i = 0; i < 10; i++) {
        int y = 50 + i * 40;
        glBegin(GL_LINES);
        glVertex2i(50, y);
        glVertex2i(45, y);
        glEnd();
    }
}

void lineGraph(void)
{
    GLint k;
    glClear(GL_COLOR_BUFFER_BIT);

    // 绘制坐标轴
    //drawAxes();

    // 绘制折线
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_STRIP);
    for (k = 0; k < 12; k++) {
        glVertex2i(50 + k * 50, 50 + dataValue[k] / 10);
    }
    glEnd();

    // 绘制数据点
    glColor3f(1.0, 0.0, 0.0);
    for (k = 0; k < 12; k++) {
        glRasterPos2i(50 + k * 50 - 2, 50 + dataValue[k] / 10 - 4);
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '*');
    }

    glFlush();
}

void winReshapeFcn(int newWidth, int newHeight)
{
    winWidth = newWidth;
    winHeight = newHeight;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)newWidth, 0.0, (GLdouble)newHeight);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Line Chart Data Plot");
    init();
    glutDisplayFunc(lineGraph);
    glutReshapeFunc(winReshapeFcn);
    glutMainLoop();
    return 0;
}