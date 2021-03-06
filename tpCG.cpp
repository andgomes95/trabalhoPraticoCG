#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>  // Header File For The OpenGL32 Library
#include <GL/glu.h> // Header File For The GLu32 Library
#include <unistd.h> 
#include <stdio.h>
#include "SOIL.h"
#include <time.h>
#define ESCAPE 27 //Valor em ASCII do Esc
#define QTDOBJ 2
#define FLAGSALTO 0.0005
#define VELOCIDADE 1
int window;
int texture[5];
GLfloat xRotated , yRotated, zRotated,move,x;
float *vetposicao;
GLint salto,agacha,q;
GLfloat direction;
GLdouble size=1; 
GLint flag =0;
void drawBody(){
    glPushMatrix();
    glColor3f(1.0f,1.0f,0.0f);
    glScalef(1.0f,1.5f,0.3f);
    glutSolidCube(1.0f);
   glPopMatrix();
}
void drawShoulder(){
    glPushMatrix();
    glColor3f(1.0f,0.5f,0.25f);
    glScalef(0.15f,0.25f,0.15f);
    glRotatef(90,-1.0f,0.0f,0.0f);
    glutSolidCone(1.0f,1.0f,10,10);
    glPopMatrix();
}
void anteHuge(){
    glPushMatrix();
    glColor3f(1.0f,1.0f,1.0f);
    glScalef(0.10f,0.5f,0.15f);
    glutSolidCube(1.0f);
    glPopMatrix();
}
void huge(){
    glTranslatef(0.0,-0.1f,0.0);
    anteHuge();
  glTranslatef(0.0,-0.3f,0.0);
    glPushMatrix();
    glColor3f(0.5f,1.0f,0.5f);
    glScalef(0.045f,0.045f,0.045f);
    glutSolidSphere(1.0f,10,10);
    glPopMatrix();
    glTranslatef(0.0,-0.25f,0.0);
    anteHuge();
}
void hand(){
    glPushMatrix();
    glColor3f(0.5f,1.0f,1.0f);
    glScalef(0.15f,0.15f,0.15f);
    glutSolidCube(1.0f);
    glPopMatrix();
}
void drawHuge(){
   drawShoulder();
    glTranslatef(0.0,-0.11f,0.0);
    huge();
    glTranslatef(0.0,-0.2f,0.0);
    hand();
}
void drawLegDeslocated(GLfloat x){
    glTranslatef(x,0.0,0.0);
    glPushMatrix();
    anteHuge();
    glTranslatef(0.0,-0.3f,0.0);
    glPushMatrix();
    glColor3f(0.5f,1.0f,0.5f);
    glScalef(0.075f,0.075f,0.075f);
    glutSolidSphere(1.0f,10,10);
    glPopMatrix();
    glTranslatef(0.25,0.0,0.0);
    glRotatef(90,0,0,1);
    anteHuge();
    glTranslatef(0.00f,-0.2f,0.0);
  //  glTranslatef(0.2f,0.0,0.0);
    hand();
    glPopMatrix();
}

void drawLeg(){
    huge();
    glTranslatef(0.0,-0.2f,0.0);
    hand();
}
void putHuges(){
    glPushMatrix();
    glTranslatef(-0.6f,0.0f,-0.01f);
   drawHuge();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.6f,0.0f,-0.01f);
    drawHuge();
    glPopMatrix();
}
void putLegs(){
    glPushMatrix();
    glTranslatef(-0.3f,-1.6f,-0.01f);
    drawLeg();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.3f,-1.6f,-0.01f);
    drawLeg();
    glPopMatrix();
}
int LoadGLTextures() // Load Bitmaps And Convert To Textures
{
    /* load an image file directly as a new OpenGL texture */
    texture[0] = SOIL_load_OGL_texture
        (
        "media/text.bmp",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
    if(texture[0] == 0)
        return 0;
     texture[1] = SOIL_load_OGL_texture
        (
        "media/top.bmp",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
    if(texture[1] == 0)
        return 0;
    texture[2] = SOIL_load_OGL_texture
        (
        "media/samuel.bmp",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
    if(texture[2] == 0)
        return 0;
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
 
    return 1;                                        // Return Success
}
void InitGL(int Width, int Height){          // We call this right after our OpenGL window is created.{
    LoadGLTextures();               // Load The Texture(s) 
    glClearDepth(1.0);        // Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS);             // The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);            // Enables Depth Testing     
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10,10,-((GLfloat)Width/(GLfloat)Height) * 10,((GLfloat)Width/(GLfloat)Height) * 10, 0, 10);
    //gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.01f,100.0f);
    glMatrixMode(GL_MODELVIEW);
}
void drawfinal(int id){
   glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texture[id]);   // choose the texture to use.
    glTranslatef(0.0f,0.0f,-10.0f);              // move 5 units into the screen.

    glBegin(GL_QUADS);

    // Front Face (note that the texture's corners have to match the quad's corners)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -10.0f,  1.0f); // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 10.0f, -10.0f,  1.0f); // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 10.0f,  10.0f,  1.0f); // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f,  10.0f,  1.0f); // Top Left Of The Texture and Quad
    
    // Back Face
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -10.0f, -1.0f);    // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f,  10.0f, -1.0f);    // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 10.0f,  10.0f, -1.0f);    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 10.0f, -10.0f, -1.0f);    // Bottom Left Of The Texture and Quad
    
    // Top Face
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f,  10.0f, -1.0f);    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f,  10.0f,  1.0f);    // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 10.0f,  10.0f,  1.0f);    // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 10.0f,  10.0f, -1.0f);    // Top Right Of The Texture and Quad
    
    // Bottom Face       
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, -10.0f, -1.0f);    // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 10.0f, -10.0f, -1.0f);    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 10.0f, -10.0f,  1.0f);    // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -10.0f,  1.0f);    // Bottom Right Of The Texture and Quad
    
    // Right face
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 10.0f, -10.0f, -1.0f);    // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 10.0f,  10.0f, -1.0f);    // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 10.0f,  10.0f,  1.0f);    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 10.0f, -10.0f,  1.0f);    // Bottom Left Of The Texture and Quad
    
    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -10.0f, -1.0f); // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -10.0f,  1.0f); // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f,  10.0f,  1.0f); // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f,  10.0f, -1.0f); // Top Left Of The Texture and Quad

    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void pagina(){
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0); 
    glScalef(1.0,0.25,2.0);
    glutSolidCube(1.0f);

    glPopMatrix();
}
void capaLivro(float locate){
    glPushMatrix();
    glColor3f(0.0, 0.2, 0.9); 
    glScalef(1.0,0.05,2.0);
    glTranslatef(0.0,locate,0.0);
    glutSolidCube(1.0f);
    glPopMatrix();
}
void capaLivro2(float locate){
    glPushMatrix();
    glColor3f(0.0, 0.2, 0.45); 
    glScalef(0.75,0.05,1.5);
    glTranslatef(0.0,locate,0.0);
    glutSolidCube(1.0f);
    glPopMatrix();
}
void colisaoBaixo(float bonecoY){
    if(bonecoY < 0.2){
        flag=1;
    }
}
void colisaoFim(float bonecoY){
    flag=2;
}
void colisaoAlto(float bonecoY){
    if(bonecoY > -0.2){
        flag=1;
    }
}
void barraHorizontal(){
    glPushMatrix();
    glColor3f(0.36, 0.2, 0.09); 
    //glRotatef(xRotated,1.0,0.0,0.0);
    //glRotatef(yRotated,0.0,1.0,0.0);
    glScalef(0.5,0.5,10.0);
    GLUquadricObj *Cylinder; // Create pointer for our cylinder
     Cylinder = gluNewQuadric();
    gluCylinder( Cylinder, 0.1, 0.1, 0.1, 50, 50 );
    glPopMatrix();
}
void barraVertical(){
    glPushMatrix();
    glColor3f(0.36, 0.2, 0.09); 
    //glRotatef(xRotated,1.0,0.0,0.0);
    //glRotatef(yRotated,0.0,1.0,0.0);
    glRotatef(-90,1.0,0.0,0.0);
    glScalef(0.5,0.5,1.0);
    GLUquadricObj *Cylinder; // Create pointer for our cylinder
     Cylinder = gluNewQuadric();
gluCylinder( Cylinder, 0.1, 0.1, 0.1, 50, 50 );
    glPopMatrix();
}
void saltoFunc(){
    if(salto == 1){
        if(move < 0.5){
            move+=FLAGSALTO;
            glTranslatef(0.0,move,0.0);
        }else{
            q = 0;
            salto = 0;
        }
    }else if(agacha == 1){
        if(move > -0.5){
            move-=FLAGSALTO;
            glTranslatef(0.0,move,0.0);
        }else{
            q = 0;
            agacha = 0;
        }
    }else if (move < 0.005){
        if(move < 0.0){
            glTranslatef(0.0,move,0.0);
            move+=FLAGSALTO;
        }
    }else{
        if(move > -0.005){
            glTranslatef(0.0,move,0.0);
            move-=FLAGSALTO;
        }else if (move < 0.005){
            move= 0.0;
            glTranslatef(0.0,move,0.0);
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
    glScalef(0.3,1.0,3.5);
    glTranslatef(direction-position,0.0,-0.5);   
    glRotatef(yRotated,0.0,1.0,0.0);
    glPushMatrix();
    barraHorizontal();
    glTranslatef(0.0,0.2,0.0);
    barraHorizontal();
    glTranslatef(0.0,-0.4,0.1);
    barraVertical();
    glTranslatef(0.0,0.0,0.8);
    barraVertical();
    glPopMatrix();
    glPopMatrix();
    if(direction-position > -4.525 && direction-position < -4.425){
        colisaoBaixo(move);
    }
}
void barreiraFim(float position){
    glPushMatrix();
    glColor3f(0.0, 0.2, 0.9); 
    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glScalef(0.3,1.0,3.5);
    glTranslatef(direction-position,0.0,-0.5);   
    glutSolidCube(1.0f);
    glPopMatrix();
    if(direction-position > -1.0 && direction-position < -0){
        colisaoFim(move);
    }
}
void barreiraAlto(float position){
    glPushMatrix();
    glColor3f(0.0, 0.2, 0.9); 
    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glTranslatef(direction-position,2.0,0.0);
    capaLivro2(-3.0);
    capaLivro(-3.0);
    pagina();
    capaLivro(3.0);
    capaLivro2(3.0);
    glPopMatrix();
    if(direction-position > -1.325 && direction-position < -1.025){
        colisaoAlto(move);
    }
}
void body(){
    glPushMatrix();
    if(q == 0 && agacha != 1){
        glRotatef(xRotated,1.0,0.0,0.0);
        glRotatef(yRotated+90.0,0.0,1.0,0.0);
        glTranslatef(0.0,1.7,-1.0);   
        saltoFunc();
        drawBody();
        putHuges();
        glTranslatef(0.0,0.5,0.0); 
        putLegs(); 
    }else if (agacha == 1){
        glRotatef(zRotated,0.0,0.0,1.0);
        glRotatef(xRotated,1.0,0.0,0.0);
        glRotatef(yRotated+90.0,0.0,1.0,0.0);
        glTranslatef(0.0,1.7,-1.0);   
        saltoFunc();
       drawBody();
        putHuges();
        glTranslatef(0.0,-1.2,0.0); 
        drawLegDeslocated(0.25);
        drawLegDeslocated(-0.25);
    }else{
        glRotatef(xRotated,1.0,0.0,0.0);
        glRotatef(yRotated+90.0,0.0,1.0,0.0);
        glTranslatef(0.0,1.7,-1.0);   
        saltoFunc();
        drawBody();
        putHuges();
        glTranslatef(0.0,-1.2,0.0); 
        drawLegDeslocated(0.25);
        drawLegDeslocated(-0.25);
    }
    glPopMatrix();
}
float * geraPosicao(){
    float *posicao = (float*)malloc(QTDOBJ* sizeof(float));
    for (int i = 0; i < QTDOBJ; i++){
        posicao[i] = rand()%2;;//(float)(rand()%160);
        //printf("%f\t",posicao[i]);
    }
    printf("\n");
    return posicao;
}
void displayInit(){
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    srand((unsigned)time(NULL));
    glLoadIdentity();
    drawfinal(0);
    vetposicao = geraPosicao();
    glTranslatef(0.0,0.0,-10.0);
    estrada();
    body();
    glFlush();        
}
void display(void){
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    int i;
    if (flag == 0){
        glColor3f(1.0f,1.0f,1.0f);
        drawfinal(0);
        estrada();
        body();
        for(i = 0;i<QTDOBJ;i++){
            if(direction+i*40 < 15.0 && direction+i*40 > -30.0){
                if(vetposicao[i]==0){       
                    barreiraAlto(-i*40);
                }
                else{
                    barreiraChao(-i*40);
                }

            }
        }
        if(direction+i*40 < 15.0 && direction+i*40 > -30.0){
            barreiraFim(-i*40);
        }
    }else if (flag == 1){
        glLoadIdentity();
        glTranslatef(0.0f,0.0f,-11.0f);              // move 5 units into the screen.
        glColor3f(1.0f,1.0f,1.0f);
        drawfinal(2);
    }else{
        glLoadIdentity();
        glTranslatef(0.0f,0.0f,-11.0f);              // move 5 units into the screen.
        glColor3f(1.0f,1.0f,1.0f);
        drawfinal(1);
    }
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
    }else if(key == 110){
        q = 1;
        salto = 1;
    }else if(key == 109){
        q = 1;
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
    if(flag == 0){
        direction -= 0.005*VELOCIDADE;
    }
    display();
}
int main (int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
    glutInitWindowSize(700,500);
    glutCreateWindow("TUPBOY SIMULATOR");
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    xRotated = yRotated = zRotated = 30.0;
    direction = 20.0;
    move=0.0;
    salto = 0;
    agacha = 0;
    q = 0;
    glutDisplayFunc(displayInit);
    glutReshapeFunc(reshapeFunc);
    glutIdleFunc(idleFunc);
    InitGL(700,500);
    glutKeyboardFunc(&keyPressed);
    Inicializa();
    glutMainLoop();
    return 0;
}
