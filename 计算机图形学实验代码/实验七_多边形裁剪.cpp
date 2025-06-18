#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_POINTS 100
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// ����ü�����
float clip_x_min = 100, clip_y_min = 100, clip_x_max = 600, clip_y_max = 500;

// ����ƽ���ı���
float polygon[MAX_POINTS][2] = {
    {50, 200},
    {350, 100},
    {650, 200},
    {350, 300}
};
int num_points = 4;

// ����ü���Ķ����
float clipped_polygon[MAX_POINTS][2];
int num_clipped_points = 0;

// �жϵ��Ƿ��ڲü�������
int inside(float x, float y, int edge) {
    switch (edge) {
    case 0: return x >= clip_x_min;
    case 1: return y >= clip_y_min;
    case 2: return x <= clip_x_max;
    case 3: return y <= clip_y_max;
    default: return 0;
    }
}

// ���㽻��
void compute_intersection(float x1, float y1, float x2, float y2, int edge, float* ix, float* iy) {
    switch (edge) {
    case 0:
        *ix = clip_x_min;
        *iy = y1 + (y2 - y1) * (clip_x_min - x1) / (x2 - x1);
        break;
    case 1:
        *ix = x1 + (x2 - x1) * (clip_y_min - y1) / (y2 - y1);
        *iy = clip_y_min;
        break;
    case 2:
        *ix = clip_x_max;
        *iy = y1 + (y2 - y1) * (clip_x_max - x1) / (x2 - x1);
        break;
    case 3:
        *ix = x1 + (x2 - x1) * (clip_y_max - y1) / (y2 - y1);
        *iy = clip_y_max;
        break;
    }
}

// Sutherland - Hodgeman �㷨
void sutherland_hodgeman() {
    float input_polygon[MAX_POINTS][2];
    int input_num_points = num_points;
    for (int i = 0; i < input_num_points; i++) {
        input_polygon[i][0] = polygon[i][0];
        input_polygon[i][1] = polygon[i][1];
    }

    for (int edge = 0; edge < 4; edge++) {
        num_clipped_points = 0;
        for (int i = 0; i < input_num_points; i++) {
            int j = (i + 1) % input_num_points;
            float x1 = input_polygon[i][0], y1 = input_polygon[i][1];
            float x2 = input_polygon[j][0], y2 = input_polygon[j][1];

            int inside1 = inside(x1, y1, edge);
            int inside2 = inside(x2, y2, edge);

            if (inside1 && inside2) {
                // �����㶼���ڲ�
                clipped_polygon[num_clipped_points][0] = x2;
                clipped_polygon[num_clipped_points][1] = y2;
                num_clipped_points++;
            }
            else if (inside1 && !inside2) {
                // ��һ�������ڲ����ڶ��������ⲿ
                float ix, iy;
                compute_intersection(x1, y1, x2, y2, edge, &ix, &iy);
                clipped_polygon[num_clipped_points][0] = ix;
                clipped_polygon[num_clipped_points][1] = iy;
                num_clipped_points++;
            }
            else if (!inside1 && inside2) {
                // ��һ�������ⲿ���ڶ��������ڲ�
                float ix, iy;
                compute_intersection(x1, y1, x2, y2, edge, &ix, &iy);
                clipped_polygon[num_clipped_points][0] = ix;
                clipped_polygon[num_clipped_points][1] = iy;
                num_clipped_points++;
                clipped_polygon[num_clipped_points][0] = x2;
                clipped_polygon[num_clipped_points][1] = y2;
                num_clipped_points++;
            }
        }

        // ������������
        for (int i = 0; i < num_clipped_points; i++) {
            input_polygon[i][0] = clipped_polygon[i][0];
            input_polygon[i][1] = clipped_polygon[i][1];
        }
        input_num_points = num_clipped_points;
    }
}

// ���Ʋü�����
void draw_clip_window() {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(clip_x_min, clip_y_min);
    glVertex2f(clip_x_max, clip_y_min);
    glVertex2f(clip_x_max, clip_y_max);
    glVertex2f(clip_x_min, clip_y_max);
    glEnd();
}

// ���Ʋ����Ķ����
void draw_unfilled_polygon(float poly[MAX_POINTS][2], int num_p) {
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_p; i++) {
        glVertex2f(poly[i][0], poly[i][1]);
    }
    glEnd();
}

// �������Ķ����
void draw_filled_polygon(float poly[MAX_POINTS][2], int num_p) {
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_p; i++) {
        glVertex2f(poly[i][0], poly[i][1]);
    }
    glEnd();
}

// ��ʾ�ü�ǰ��ͼ��
void display_original() {
    glClear(GL_COLOR_BUFFER_BIT);
    draw_clip_window();
    draw_unfilled_polygon(polygon, num_points);
    glFlush();
}

// ��ʾ�ü����ͼ��
void display_clipped() {
    glClear(GL_COLOR_BUFFER_BIT);
    draw_clip_window();
    draw_filled_polygon(clipped_polygon, num_clipped_points);
    glFlush();
}

// ��ʼ�� OpenGL
void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    // ��һ�����ڣ��ü�ǰ��ͼ��
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Original Polygon");
    init();
    glutDisplayFunc(display_original);

    // ִ�вü�
    sutherland_hodgeman();

    // �ڶ������ڣ��ü����ͼ��
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Clipped Polygon");
    init();
    glutDisplayFunc(display_clipped);

    glutMainLoop();
    return 0;
}