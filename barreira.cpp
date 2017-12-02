#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>  // Header File For The OpenGL32 Library
#include <GL/glu.h> // Header File For The GLu32 Library
#include <unistd.h> 
#include <stdio.h>
#define ESCAPE 27 //Valor em ASCII do Esc
int window;

GLfloat xRotated, yRotated, zRotated;
GLdouble size=1;
void pagina(){
    glPushMatrix();
    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glColor3f(1.0, 1.0, 1.0); 
    glScalef(1.0,0.25,2.0);
    glutSolidCube(1.0f);

    glPopMatrix();
}
void capaLivro(float locate){
    glPushMatrix();

    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glColor3f(0.0, 0.2, 0.9); 
    glScalef(1.0,0.05,2.0);
    glTranslatef(0.0,locate,0.0);
    glutSolidCube(1.0f);
    glPopMatrix();

}
void capaLivro2(float locate){
    glPushMatrix();

    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glColor3f(0.0, 0.2, 0.45); 
    glScalef(0.75,0.05,1.5);
    glTranslatef(0.0,locate,0.0);
    glutSolidCube(1.0f);
    glPopMatrix();

}

void display(void){
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0,0.0,-4.5);
    capaLivro2(-3.0);
    capaLivro(-3.0);
    pagina();
    capaLivro(3.0);
    capaLivro2(3.0);
    glFlush();
    // sawp buffers called because we are using double buffering 
   // glutSwapBuffers();
}
void keyPressed(unsigned char key, int x, int y) {
    usleep(100);
    if (key == ESCAPE){ 
      glutDestroyWindow(window); 
      exit(0);                   
    }//se pressionar esc, saiu
}
void reshapeFunc(int x, int y)
{
    if (y == 0 || x == 0) return;  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glViewport(0,0,x,y);  
}

void idleFunc(void)
{
 
     xRotated += 0.0;
     yRotated += 0.0;
     zRotated += 0.0;
     
    display();
}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
    glutInitWindowSize(400,350);
    glutCreateWindow("Book");
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    xRotated = yRotated = zRotated = 30.0;
    glClearColor(0.0,0.0,0.0,0.0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshapeFunc);
    glutIdleFunc(idleFunc);
    glutKeyboardFunc(&keyPressed);
    glutMainLoop();
    return 0;
}
