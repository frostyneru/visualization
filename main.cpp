#include <GL/glut.h>
#include <fstream>
#include <iostream>
#include <math.h>
using namespace std;
const GLfloat WindowWidth=512.f, WindowHeight=512.0f;
const GLfloat nRange=256.0f;
GLfloat xmax=0.0f,ymax=0.0f;
GLdouble scx=0.0d, scy=0.0d;
GLfloat xr=0.0f, yr=0.0f, xk=0.0f, yk=0.0f, xm=0.0f, ym=0.0f;
GLint ch=0;
GLboolean scale=false, scalerect=false;
void RenderScene(void)
	{
		GLfloat px=0.0f, py=0.0f;
		GLfloat px1=0.0f, py1=0.0f, px2=0.0f, py2=0.0f;

		glClear(GL_COLOR_BUFFER_BIT);
		glPushMatrix();



			glLineWidth(1.0f);
			glColor3f(1.0f,0.0f ,0.0f);
			glBegin(GL_LINES);
				glVertex3f(0.0f,0.0f,0.0f);
				glVertex3f(nRange*4.0f,0.0f,0.0f);
			glEnd();
			glColor3f(0.0f,0.0f ,0.0f);



		ifstream fin("4.txt");
		ofstream fout("2.txt");
		glPointSize(2.0f);
		glLineWidth(1.0f);
		//if ((xr!=0) && (yr!=0) && (xm!=0) && (ym!=0))
		//{
		//glBegin(GL_POLYGON);
		//			glVertex3f(xr*2.0f,ymax-yr*2.0f, 0.0f);
		//			glVertex3f(xm*2.0f,ymax-yr*2.0f, 0.0f);
		//			glVertex3f(xm*2.0f,ymax-ym*2.0f, 0.0f);
		//			glVertex3f(xr*2.0f,ymax-ym*2.0f, 0.0f);
		//		glEnd();
		//}
		
		for (GLint i=0; i<32768; i++)
			{
				if ((ch==1) || (ch==2))
					{
						fin >> px >> py;
						if (abs(px)>xmax)
							xmax=abs(px);
						if (abs(py)>ymax)
							ymax=abs(py);
						switch(ch)
							{
								case(1):
									glBegin(GL_POINTS);
										glVertex3f(px,py,0.0f);
									glEnd();
								break;
								case(2):
									glBegin(GL_LINES);
										glVertex3f(px,py,0.0f);
										glVertex3f(px,0.0f,0.0f);
									glEnd();
								break;
							}
						fout << i << " " << px << " " << py << endl;
					}
				else
					if (ch==3)
						{
							if (i==0)
								{
									fin >> px1 >> py1;
									fin >> px2 >> py2;
									if (abs(px1)>=abs(px2))
										xmax=abs(px1);
									else
										if (abs(px1)<abs(px2)) 
											xmax=abs(px2);
									if (abs(py1)>=abs(py2))
										ymax=abs(py1);
									else
										if (abs(py1)<abs(py2)) 
											ymax=abs(py2);
									glBegin(GL_LINES);
										glVertex3f(px1,py1,0.0f);
										glVertex3f(px2,py2,0.0f);
									glEnd();
								}
							else
								if (i!=0)
									{
										px1=px2;
										py1=py2;
										fin >> px2 >> py2;
										glBegin(GL_LINES);
											glVertex3f(px1,py1,0.0f);
											glVertex3f(px2,py2,0.0f);
										glEnd();
										if (abs(px2)>xmax)
											xmax=abs(px2);
										if (abs(py2)>ymax)
											ymax=abs(py2);
									}
						}
			}
		fin.close();
		fout.close();
		if (scale==false)
			{
				scx=nRange*4.0f/(xmax);
				scy=nRange*2.0f/(ymax);
				glScalef(scx,scy, 0.0f);
				scale=true;
			}
		if (scalerect==false)
			{
				for (GLint i=0; i<10; i++)
					{
						glBegin(GL_LINES);
							glVertex3f(xmax/10.0f*i,ymax,0.0f);
							glVertex3f(xmax/10.0f*i,-ymax,0.0f);
						glEnd();
					}
			}
		if (scalerect==true)
			{
				if (xr<xk)
					for (GLfloat i=xr; i<xk*2.0f; i+=abs(xr-xk)/10)
						{
							glBegin(GL_LINES);
								glVertex3f(i,ymax,0.0f);
								glVertex3f(i,-ymax,0.0f);
							glEnd();
						}
				else
					if (xr>xk)
						for (GLfloat i=xk; i<xr*2.0f; i+=abs(xr-xk)/10)
							{
								glBegin(GL_LINES);
									glVertex3f(i,ymax,0.0f);
									glVertex3f(i,-ymax,0.0f);
								glEnd();
							}
				glBegin(GL_LINES);
					glVertex3f(xr*2.0f, ymax-yr*2.0f, 0.0f);
					glVertex3f(xk*2.0f, ymax-yk*2.0f, 0.0f);
				glEnd();
				glColor3f(1.0f,0.0f ,0.0f);
				glPointSize(10.0f);
				glBegin(GL_POINTS);
					glVertex3f(xr*2.0f, ymax-yr*2.0f, 0.0f);
				glEnd();
				glColor3f(0.0f,1.0f ,0.0f);
				glBegin(GL_POINTS);
					glVertex3f(xk*2.0f, ymax-yk*2.0f, 0.0f);
				glEnd();



				//glBegin(GL_POLYGON);
				//	glVertex3f(xr*2.0f,ymax-yr*2.0f, 0.0f);
				//	glVertex3f(xm*2.0f,ymax-yr*2.0f, 0.0f);
				//	glVertex3f(xm*2.0f,ymax-ym*2.0f, 0.0f);
				//	glVertex3f(xr*2.0f,ymax-ym*2.0f, 0.0f);
				//glEnd();



				glColor3f(1.0f,1.0f ,1.0f);
				glPointSize(2.0f);
			}
		glutSwapBuffers();
	}
void ChangeSize(GLsizei w, GLsizei h)
	{
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho (0.0f, nRange*4.0f , -nRange*2.0f , nRange*2.0f , -1.0f, 1.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
void SetupRC(void)
	{
		glClearColor(0.9f, 0.9f, 0.9f, 0.0f);
	}
void Mouse(int button, int state, signed int x, signed int y)
	{
		if (scalerect==false)
		{
			if (button==GLUT_LEFT_BUTTON)
				{
					if (state==GLUT_DOWN)
					{
						xr=x/scx;
						yr=y/scy;
					}
					if (state==GLUT_UP)
					{
						xk=x/scx;
						yk=y/scy;
						if (((xr-xk)!=0) && ((yr-yk)!=0))
							{
								cout << xr << " " << yr << endl << xk << " " << yk << endl;
								scalerect=true;
								glScalef(1/scx, 1/scy ,0.0f); // В default
								scx=nRange*4.0f/abs(xr-xk);
								scy=nRange*2.0f/abs(yr-yk);
								glScalef(scx,scy,0.0f); // В newdefault
								if (xr<xk)
									glTranslatef(-xr*2.0f,-ymax+yr+yk,0.0f);
								else if (xr>xk)
									glTranslatef(-xk*2.0f,-ymax+yr+yk,0.0f);
								glutPostRedisplay();
							}
					}
				}
		}
	}
void Keyboard(unsigned char key, int x, int y)
	{
		switch(key)
			{
				case(32):
					if (scalerect==true)
						{
							scalerect=false;
							if (xr<xk)
								glTranslatef(xr*2.0f,ymax-yr-yk,0.0f);
							else if (xr>xk)
								glTranslatef(xk*2.0f,ymax-yr-yk,0.0f);
							glScalef(1/scx, 1/scy ,0.0f); // В default
							scx=nRange*4.0f/(xmax);
							scy=nRange*2.0f/(ymax);
							glScalef(scx,scy,0.0f);
							glutPostRedisplay();
						}
				break;
			}
	}
void Motion(int x, int y)
	{
		if (scalerect==false)
		{
			xm=x/scx;
			ym=y/scy;
			glColor3f(1.0f,0.0f ,0.0f);
			//glPointSize(10.0f);
			//glBegin(GL_POINTS);
			//	glVertex3f(xr*2.0f, ymax-yr*2.0f, 0.0f);
			//glEnd();
			//glColor3f(0.0f,1.0f ,0.0f);
			//glBegin(GL_POINTS);
			//	glVertex3f(xm*2.0f, ymax-ym*2.0f, 0.0f);
			//glEnd();
			glBegin(GL_POLYGON);
					glVertex3f(xr*2.0f,ymax-yr*2.0f, 0.0f);
					glVertex3f(xm*2.0f,ymax-yr*2.0f, 0.0f);
					glVertex3f(xm*2.0f,ymax-ym*2.0f, 0.0f);
					glVertex3f(xr*2.0f,ymax-ym*2.0f, 0.0f);
			glEnd();
			//glPointSize(2.0f);
			glutSwapBuffers();
		}
	}
int main(int argc, char **argv)
	{
		cin >> ch;
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
		glutInitWindowSize(WindowWidth,WindowHeight);
		glutCreateWindow("Project");
		glutReshapeFunc(ChangeSize);
		glutDisplayFunc(RenderScene);
		glutKeyboardFunc(Keyboard);
		glutMouseFunc(Mouse);
		glutMotionFunc(Motion);
		SetupRC();
		glutMainLoop();
	}
