#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <string>
using namespace std;
#define FROM_RIGHT 1
#define FROM_LEFT 2
#define FROM_TOP 3
#define FROM_BOTTOM 4
static int WINDOW_WIDTH, WINDOW_HEIGHT;
int playerResult = 0, win1;
static float Xspeed = 0.5, Yspeed = 0.5;
static float delta = 0.5;
static int mouse_stop = 1;
struct RECTANGLE
{
    float left, top, right, bottom;
};
RECTANGLE ball = {100, 100, 120, 120}, wall, player = {0, 740, 40, 750};
void drawRectangle(RECTANGLE r)
{
    glBegin(GL_QUADS);
    glVertex2f(r.left, r.bottom);
    glVertex2f(r.right, r.bottom);
    glVertex2f(r.right, r.top);
    glVertex2f(r.left, r.top);
    glEnd();
}
void write(double x, double y, double z, double scale, string s)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(scale, scale, scale);
    PING PONG GAME
        Dept,
        of CSE, GAT 2021 - 2022 8 for (int i = 0; i < s.length(); i++) glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);
    glPopMatrix();
}
void drawText(string s, int x, int y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(0.75, -0.75, 1);
    for (int i = 0; i < s.length(); i++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);
    glPopMatrix();
}
void timer(int v)
{
    ball.left += Xspeed;
    ball.right += Xspeed;
    ball.top += Yspeed;
    ball.bottom += Yspeed;
    glutTimerFunc(1, timer, 1);
}
void mouseFunc(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        printf("%d %d\n", x, y);
    }
}
void stop()
{
    drawText("GAME OVER", 394, 185);
    string str1 = "SCORE: " + to_string(playerResult);
    drawText(str1, 394, 300);
    delta = 0;
    mouse_stop = 0;
    glutMouseFunc(mouseFunc);
}
int testBallWall(RECTANGLE ball, RECTANGLE wall)
{
    if (ball.right >= wall.right)
        return FROM_RIGHT;
    if (ball.left <= wall.left)
        return FROM_LEFT;
    if (ball.top <= wall.top)
        return FROM_TOP;
    if (ball.bottom >= wall.bottom)
        stop();
    PING PONG GAME
        Dept,
        of CSE, GAT 2021 - 2022 9 else return 0;
}
bool testBallPlayer(RECTANGLE ball, RECTANGLE player)
{
    if (ball.bottom >= player.top && ball.bottom <= (player.top + 1) && ball.left >= player.left && ball.right <= player.right)
    {
        playerResult++;
        return true;
    }
    return false;
}
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    }
}
static int mouse_x = 0;
void mouseMotion(int x, int y)
{
    mouse_x = x * mouse_stop;
}
void setting(void)
{
    glClearColor(0.59, 0.20, 0.67, 1.0);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
void reshape(int w, int h)
{
    WINDOW_WIDTH = w;
    WINDOW_HEIGHT = h;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void display()
{
    glClearColor(0.94, 0.33, 0.33, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.17, 0.20, 0.32);
    write(-1, 0.4, 1, 0.0007, " GLOBAL ACADEMY OF TECHNOLOGY ");
    write(-0.9, 0.3, 1, 0.0007, "DEPARTMENT OF COMPUTER SCIENCE ");
    write(-0.5, 0.2, 1, 0.0007, "AND ENGINEERING");
    PING PONG GAME
        Dept,
        of CSE, GAT 2021 - 2022 10 write(-0.8, 0.1, 0.0, 0.0006, "Mini Project on Computer Graphics");
    write(-0.5, 0.0, 0.0, 0.0006, "and Visualisation");
    write(-0.8, -0.3, 0.0, 0.0007, "Submitted BY:");
    write(-0.8, -0.4, 0.0, 0.0008, "Likith.R 1GA19CS079");
    write(-0.4, -0.7, 0.0, 0.0006, "Press 'S' to continue");
    glFlush();
}
void render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    wall.left = wall.top = 0;
    wall.right = WINDOW_WIDTH;
    wall.bottom = WINDOW_HEIGHT;
    drawRectangle(ball);
    if (testBallWall(ball, wall) == FROM_RIGHT)
        Xspeed = -delta;
    if (testBallWall(ball, wall) == FROM_LEFT)
        Xspeed = delta;
    if (testBallWall(ball, wall) == FROM_TOP)
        Yspeed = delta;
    drawRectangle(player);
    player.left = mouse_x - 80;
    player.right = mouse_x + 40;
    if (testBallPlayer(ball, player) == true)
        Yspeed = -delta;
    glutSwapBuffers();
}
void keyboard1(unsigned char key, int x, int y)
{
    if (key == 's' || key == 'S')
    {
        glutDestroyWindow(win1);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutInitWindowSize(1540, 750);
        glutInitWindowPosition(0, 0);
        glutCreateWindow("GAME");
        setting();
        glutDisplayFunc(render);
        glutIdleFunc(render);
        glutTimerFunc(1, timer, 1);
        glutReshapeFunc(reshape);
        glutKeyboardFunc(keyboard);
        glutReshapeFunc(reshape);
        PING PONG GAME
            Dept,
            of CSE, GAT 2021 - 2022 11 glutPassiveMotionFunc(mouseMotion);
        glutMainLoop();
    }
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1540, 750);
    glutInitWindowPosition(0, 0);
    win1 = glutCreateWindow("INTRODUCTION");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard1);
    glutMainLoop();
    return 0;
}