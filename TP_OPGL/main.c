#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <sys/time.h>

#define WAIT_INTERVAL 200 //in clocks
#define PIXEL_SIZE 5 //in pixels

typedef struct node {
    int x;
    int y;
    struct node* suiv;
} LISTE;

int changed = 1;
clock_t last_check;
clock_t startup_time;

int **pixelsColor;
LISTE* toDraw;
int x, y;


void push(int x, int y){
    LISTE* m = malloc(sizeof(LISTE));
    m->x = x;
    m->y = y;
    m->suiv = toDraw;
}

void pop(int *x, int *y){
    LISTE* m = toDraw;
    if(!m)
        free(m);
    toDraw = (toDraw)? toDraw->suiv : toDraw;
}

int getColor(int a, int b) {
    if(x<0 || y<0 || x>100 || y>100)
        return -1;
    return pixelsColor[a][b];
}

void setColor(int a, int b) {
    x = a;
    y = b;
    pixelsColor[a][b] = 1;
}

void flood(int a, int b) {
    if(getColor(a, b) == 0) {
        printf("%d, %d\n", a, b);
        push(a, b);
        flood(a+1, b+1);
        flood(a-1, b+1);
        flood(a+1, b-1);
        flood(a-1, b-1);
    }
}

void update(clock_t time_passed) {
    int nbr_updates = time_passed/WAIT_INTERVAL;
    for(int i=0; i<nbr_updates; i++) {
        pop(&x, &y);
        printf("TO DRAW : %d, %d\n", x, y);
    }
    last_check += nbr_updates*WAIT_INTERVAL;
    changed = (nbr_updates)? 1:0;
    printf("last_check = %gs, time_interval = %gs\n", ((float)last_check-startup_time)/CLOCKS_PER_SEC, ((float)time_passed)/CLOCKS_PER_SEC);
}

void drawScene(void) {
    if(changed) {
        printf("Draw %d, %d\n", x, y);
        glBegin(GL_QUADS);
            int Nx = x*PIXEL_SIZE;
            int Ny = y*PIXEL_SIZE;
            glColor3f(1, 1, 1);
            glVertex2i(Nx, Ny);
            glVertex2i(Nx+PIXEL_SIZE, Ny);
            glVertex2i(Nx+PIXEL_SIZE, Ny+PIXEL_SIZE);
            glVertex2i(Nx, Ny+PIXEL_SIZE);
        glEnd();
    }
    if(x != 5 || y != 5) {
        clock_t new_check = clock();
        update(new_check-last_check);
        glutPostRedisplay();
        glFlush();
    }
}
int size() {
    int s = 0;
    while(toDraw)
        toDraw = toDraw->suiv;
    return s;
}
int main( int argc, char** argv ) {
    pixelsColor = malloc(sizeof(int*)*100);
    for(int i=0; i<100; i++){
        pixelsColor[i] = malloc(sizeof(int)*100);
        for(int j=0; j<100; j++)
            pixelsColor[i][j] = 0;
    }
    toDraw = NULL;
    flood(50, 50);
    printf("size = %d\n", size());
    last_check = clock();
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );

    glutInitWindowPosition( 10, 60 );
    glutInitWindowSize(PIXEL_SIZE*100, PIXEL_SIZE*100);
    glutCreateWindow( "FloodFill" );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, PIXEL_SIZE*100, PIXEL_SIZE*100,0.0);
    glutDisplayFunc( drawScene );

    startup_time = clock();
    glutMainLoop();

    return(0);
}
