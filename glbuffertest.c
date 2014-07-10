#include <stdio.h>
#include <math.h>
#include <GL/glut.h>


void disp_fps(){
    static GLint frames = 0;
    static GLint t0 = 0;
    static char fps_str[20] = {'\0'};
    GLint t = glutGet(GLUT_ELAPSED_TIME);
    if (t - t0 >= 200) {
        GLfloat seconds = (t - t0) / 1000.0;
        GLfloat fps = frames / seconds;
        sprintf(fps_str, "%6.f FPS\n", fps);
        printf("%6.f FPS\n", fps);
        t0 = t;
        frames = 0;
    }
    glColor3f(0.0, 0.0, 1.0);
    glRasterPos2f(0, 0);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, fps_str);
    frames++;
}

void display() {
    
    float siz = 0.01;
    float inc = 0.05;
    float delay = 1.0 / 55;
    
    static double a = 0;
    a = fmod(a+inc, 2*M_PI);
    double x = sin(a);
    
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    usleep((int)(delay*1000000));
    
    glColor3f(0,1,0);
    glBegin(GL_POLYGON);
    glVertex3f(x-siz,-1.0,0.0);
    glVertex3f(x-siz,1.0,0.0);
    glVertex3f(x+siz,1.0,0.0);
    glVertex3f(x+siz,-1.0,0.0);
    glEnd(); 
    
    disp_fps();
    
    glutPostRedisplay();
    glutSwapBuffers();
    glFinish();
}


void toggle_fullscreen(){
    static int fullscreen = 1;
    if(fullscreen){
        glutFullScreen();
    }else{
        glutReshapeWindow(1800, 900);
        glutPositionWindow(0,0);
    }
    fullscreen = !fullscreen;
}


static void key(unsigned char k, int x, int y)
{
    switch (k) {
        case 'f':
            toggle_fullscreen();
            break;
        case 27:  // Escape
        case 'q':
            exit(0);
            break;
        default:
            return;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH  | GLUT_DOUBLE);
    glutCreateWindow("OpenGL Buffering Tests");
    glutKeyboardFunc(key);
    glutDisplayFunc(display);
    toggle_fullscreen();
    glutMainLoop();
    return 0;
}
