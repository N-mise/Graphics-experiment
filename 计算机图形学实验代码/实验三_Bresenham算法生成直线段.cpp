#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
// 窗口大小
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
// 初始化函数
void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);  // 设置黑色背景
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
}

void setPixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}
//Bresenham算法(0<k<1)
void linBres(int x0, int y0, int xEnd, int yEnd) {
	int dx = fabs(xEnd-x0),dy=fabs(yEnd-y0);
	int p = 2 * dy - dx;
	int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy-dx);
	int x, y;
	if (x0 > xEnd) {
		x = xEnd;
		y = yEnd;
		xEnd = x0;
	}else {
		x = x0;
		y = y0;
	}
	setPixel(x, y);
	while (x<xEnd) {
		x++;
		if (p < 0) {
			p += twoDy;
		}
		else {
			y++;
			p += twoDyMinusDx;
		}
		setPixel(x, y);
	}
}
// 显示回调函数
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);  // 设置白色
	// 生成直线段
	linBres(100, 100, 300, 300); 
	glFlush();
}

// 主函数
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Bresenham算法示例");  // 创建窗口
	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}