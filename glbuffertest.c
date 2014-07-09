#include <stdio.h>
#include <math.h>
#include <GL/glut.h>


static GLint win = 0;
static int fullscreen = 1;



float calc_fps() {
    static GLint frames = 0;
    static GLint t0 = 0;
    static float fps = 0;
    GLint t = glutGet(GLUT_ELAPSED_TIME);
    if (t - t0 >= 200) {
        GLfloat seconds = (t - t0) / 1000.0;
        fps = frames / seconds;
        printf("%6.f FPS\n", fps);
        fflush(stdout);
        t0 = t;
        frames = 0;
    }
    frames++;
    return fps;
}

void disp_fps(float fps){
    static char fps_str[100];
    sprintf(fps_str, "%6.f FPS\n", fps);
    glColor3f(0.0, 0.0, 1.0);
    glRasterPos2f(0, 0);
    int i;
    for(i=0; i<100; i++) {
        if(fps_str[i]=='\n'){ break;}
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, fps_str[i]);
    }
}




void display() {
    
    float siz = 0.01;
    float inc = 0.05;
    
    static int i = 1;
//     i = (i+1)%3;
    
    static double a = 0;
    a = fmod(a+inc, 2*M_PI);
    double x = sin(a);
    
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(i==0?1:0, i==1?1:0, i==2?1:0);
    
    glBegin(GL_POLYGON);
    glVertex3f(x-siz,-1.0,0.0);
    glVertex3f(x-siz,1.0,0.0);
    glVertex3f(x+siz,1.0,0.0);
    glVertex3f(x+siz,-1.0,0.0);
    glEnd(); 
    
    float fps = calc_fps();
    disp_fps(fps);
    
    usleep((int)((1./45)*1000000));
    
    glutPostRedisplay();
    glutSwapBuffers();
//     glFinish();
}

static void key(unsigned char k, int x, int y)
{
    switch (k) {
        case 'f':
            if(fullscreen){
                fullscreen = 0;
                glutReshapeWindow(1800, 900);
                glutPositionWindow(0,0);
            }else{
                glutFullScreen();
                fullscreen = 1;
            }
            break;
        case 27:  // Escape
        case 'q':
            glutDestroyWindow(win);
            exit(0);
            break;
        default:
            return;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH  | GLUT_DOUBLE);
    win = glutCreateWindow("Tearing Test");
    glutKeyboardFunc(key);
    glutDisplayFunc(display);
    glutFullScreen();
    glutMainLoop();
    return 0;
}