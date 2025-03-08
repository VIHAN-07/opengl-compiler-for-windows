#include <GL/freeglut.h>

float angle = 0.0f; // Rotation angle

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color & depth buffers
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -5.0f); // Move triangle into view
    glRotatef(angle, 0.0f, 1.0f, 0.0f); // Rotate around Y-axis

    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f); // Red
        glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);  // Green
        glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 1.0f, 0.0f);   // Blue
    glEnd();

    glutSwapBuffers(); // Double buffering
}

void update(int value) {
    angle += 2.0f; // Rotate triangle
    if (angle > 360) angle -= 360;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // Redraw at ~60 FPS
}

void reshape(int w, int h) {
    if (h == 0) h = 1; // Prevent division by zero
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL with FreeGLUT");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
