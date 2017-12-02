#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>  // Header File For The OpenGL32 Library
#include <GL/glu.h> // Header File For The GLu32 Library
#include <unistd.h> 
#include <stdio.h>
#define ESCAPE 27 //Valor em ASCII do Esc
int window;

GLfloat xRotated , yRotated, zRotated,move;
GLint salto,agacha;
GLfloat direction;
GLdouble size=1; 
void saltoFunc(){
    if(salto == 1){
        if(move < 1.0){
            move+=0.001;
            glTranslatef(0.0,move,0.0);
        }else{
            salto = 0;
        }
    }else if(agacha == 1){
        if(move > -0.4){
            move-=0.001;
            glTranslatef(0.0,move,0.0);
        }else{
            agacha = 0;
        }
    }else if (move < 0.0){
        if(move < 0.0){
            glTranslatef(0.0,move,0.0);
            move+=0.001;
        }
    }else{
        if(move > 0.0){
            glTranslatef(0.0,move,0.0);
            move-=0.001;
        }
    }
}
void Inicializa (void){
    GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
    GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};      // "cor"
    GLfloat luzEspecular[4]={0.3, 0.3, 0.3, 1.0};// "brilho"
    GLfloat posicaoLuz[4]={0.0, 100.0, -100.0, 1.0};

    // Capacidade de brilho do material
    GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
    GLint especMaterial = 60;

    // Especifica que a cor de fundo da janela será preta
    glClearColor(0.2f, 0.2f, 0.6f, 1.0f);

    // Habilita o modelo de colorização de Gouraud
    glShadeModel(GL_SMOOTH);

    // Define a refletância do material
    glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
    // Define a concentração do brilho
    glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    // Define os parâmetros da luz de número 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

    // Habilita a definição da cor do material a partir da cor corrente
    glEnable(GL_COLOR_MATERIAL);
    //Habilita o uso de iluminação
    glEnable(GL_LIGHTING);
    // Habilita a luz de número 0
    glEnable(GL_LIGHT0);
    // Habilita o depth-buffering
    glEnable(GL_DEPTH_TEST);
}

void estrada(){
    glPushMatrix();
    glColor3f(0.4, 0.2, 0.5); 
    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glScalef(1000.0,0.01,3.0);
    glutSolidCube(1.0f);
    glPopMatrix();
}
void barreiraChao(float position){
    glPushMatrix();
    glColor3f(0.0, 0.2, 0.9); 
    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glScalef(0.3,0.5,3.0);
    glTranslatef(direction-position,0.25,0.0);
    glutSolidCube(1.0f);
    glPopMatrix();
}
void barreiraAlto(float position){
    glPushMatrix();
    glColor3f(0.0, 0.2, 0.9); 
    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glScalef(0.3,0.5,3.0);
    glTranslatef(direction-position,4.0,0.0);
    glutSolidCube(1.0f);
    glPopMatrix();
}
void body(){
    glPushMatrix();
    glColor3f(0.6, 0.2, 0.9); 
    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glScalef(0.3,5.0,3.0);
    saltoFunc();
    glutSolidCube(1.0f);
    glPopMatrix();
}

void display(void){
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0,0.0,-10.0);
    estrada();
    barreiraChao(100.0);
    barreiraAlto(150.0);
    barreiraChao(200.0);
     body();
    barreiraAlto(120.0);

    glFlush();        
}
void keyPressed(unsigned char key, int x, int y) {
    usleep(100);
    if (key == ESCAPE){ 
      glutDestroyWindow(window); 
      exit(0);                   
    }else if(key == 97){
        xRotated++;
    }else if(key == 115){
        yRotated++;
    }else if(key == 108){
        salto = 1;
    }else if(key == 109){
        agacha = 1;
    }
}
void reshapeFunc(int x, int y){
    if (y == 0 || x == 0) return;  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glViewport(0,0,x,y);  
}
void idleFunc(void){
     xRotated += 0.0;
     yRotated += 0.0;
     zRotated += 0.0;
     direction -= 0.025;
    display();
}


int main (int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
    glutInitWindowSize(800,600);
    glutCreateWindow("Games");
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    xRotated = yRotated = zRotated = 30.0;
    direction = 200.0;
    move=0.0;
    salto = 0;
    agacha = 0;
    glClearColor(0.0,0.0,0.0,0.0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshapeFunc);
    glutIdleFunc(idleFunc);
    glutKeyboardFunc(&keyPressed);
    Inicializa();
    glutMainLoop();
    return 0;
}
