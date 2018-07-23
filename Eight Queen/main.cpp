#include<bits/stdc++.h>
#include <windows.h>
#include <glut.h>
using namespace std;
#define pi (2*acos(0.0))

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;

struct point
{
	double x,y,z;
};

class EightQueen
{
    int** board;
    int current_cost;
public:

    EightQueen()
    {

        board  = (int **)malloc(sizeof(int *) * 8);
        for(int i=0;i<8;i++)board[i]=(int*)malloc(sizeof(int)*8);
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)board[i][j]=0;
        }
    }
    ~EightQueen()
    {
        for(int i=0;i<8;i++)free(board[i]);
        free(board);
    }
    void createRandomStartState()
    {
        for(int col=0;col<8;col++)
        {
            int row=rand()%8;
            board[row][col]=1;
        }
        current_cost=findCost(board);
    }
    bool isDestination();

    bool findBestNeighbour();
    int findCost(int** mat);
    int** copyArray(int** a)
    {
        int** temp;
        temp  = (int **)malloc(sizeof(int *) * 8);
        for(int i=0;i<8;i++)temp[i]=(int*)malloc(sizeof(int)*8);
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)temp[i][j]=a[i][j];
        }
        return temp;
    }
    void print(int** temp)
    {
        cout<<"current cost is: "<<current_cost<<endl;
        cout<<"current condition of board is:"<<endl;
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)cout<<temp[i][j]<<' ';
            cout<<endl;
        }
    }
    void  run()
    {
        print(board);
        int random_restart=0;
        while(true)
        {
            if(isDestination())
            {
                printf("Owaooooo destination has found!!!\n");
                printf("number of rando restart is:%d\n\n",random_restart);
                break;
            }
            bool flag=findBestNeighbour();
            if(flag==false)
            {
                cout<<"local minima !!"<<endl;
                cout<<"call random restart"<<endl;
                cout<<endl;
                createRandomStartState();
                random_restart++;
            }
        }

    }
};
int nC2(int n)
{
    if(n<2)return 0;
    return (n*(n-1))/2;
}
int EightQueen::findCost(int** mat)
{
    int cost=0;
    for(int row=0;row<8;row++)/// row check
    {
        int cnt=0;
        for(int col=0;col<8;col++)
        {
            if(mat[row][col])cnt++;
        }
        cost+=nC2(cnt);
    }
    for(int col=0;col<8;col++)///col check
    {
        int cnt=0;
        for(int row=0;row<8;row++)
        {
            if(mat[row][col])cnt++;
        }
        cost+=nC2(cnt);
    }
    for(int row=0;row<8;row++)
    {
        int i=row; int j=0;
        int cnt=0;
        for(;i>=0&&j<8;i--,j++)
        {
            if(mat[i][j])cnt++;
        }
        cost+=nC2(cnt);

    }
    for(int col=1;col<8;col++)
    {
        int i=7;
        int j=col;
        int cnt=0;
        for(;j<8;j++,i--)
        {
            if(mat[i][j])cnt++;
        }
        cost+=nC2(cnt);
    }
    for(int row=0;row<8;row++)
    {
        int i=row; int j=0;
        int cnt=0;
        for(;i<8&&j<8;i++,j++)
        {
            if(mat[i][j])cnt++;
        }
        cost+=nC2(cnt);
    }
    for(int col=1;col<8;col++)
    {
        int i=0; int j=col;
        int cnt=0;
        for(;j<8;i++,j++)
        {
            if(mat[i][j])cnt++;
        }
        cost+=nC2(cnt);
    }
    return cost;
}
bool EightQueen::findBestNeighbour()
{

    int bestCost=INT_MAX;
    int** bestMatrix;
    bestMatrix  = (int **)malloc(sizeof(int *) * 8);
    for(int i=0;i<8;i++)bestMatrix[i]=(int*)malloc(sizeof(int)*8);

    for(int col=0;col<8;col++)
    {
        int booked;
        for(int i=0;i<8;i++)
        {
            if(board[i][col]){
                booked=i; break;
            }
        }
        for(int row=0;row<8;row++)
        {
            if(row==booked)continue;
            int ** temp=copyArray(board);
            temp[booked][col]=0;
            temp[row][col]=1;
            int temp_cost=findCost(temp);
            if(temp_cost<bestCost)
            {
                bestCost=temp_cost;
                bestMatrix=copyArray(temp);
            }

        }
    }
    if(bestCost<current_cost)
    {
        current_cost=bestCost;
        print(bestMatrix);
        board=copyArray(bestMatrix);
        return true;
    }
    return false;
}
bool EightQueen::isDestination()
{
    for(int row=0;row<8;row++)/// row check
    {
        int cnt=0;
        for(int col=0;col<8;col++)
        {
            if(board[row][col])cnt++;
        }
        if(cnt>1)return false;
    }
    for(int col=0;col<8;col++)///col check
    {
        int cnt=0;
        for(int row=0;row<8;row++)
        {
            if(board[row][col])cnt++;
        }
        if(cnt>1)return false;
    }
    for(int row=0;row<8;row++)
    {
        int i=row; int j=0;
        int cnt=0;
        for(;i>=0&&j<8;i--,j++)
        {
            if(board[i][j])cnt++;
        }
        if(cnt>1)return false;

    }
    for(int col=1;col<8;col++)
    {
        int i=7;
        int j=col;
        int cnt=0;
        for(;j<8;j++,i--)
        {
            if(board[i][j])cnt++;
        }
        if(cnt>1)return false;
    }
    for(int row=0;row<8;row++)
    {
        int i=row; int j=0;
        int cnt=0;
        for(;i<8&&j<8;i++,j++)
        {
            if(board[i][j])cnt++;
        }
        if(cnt>1)return false;
    }
    for(int col=1;col<8;col++)
    {
        int i=0; int j=col;
        int cnt=0;
        for(;j<8;i++,j++)
        {
            if(board[i][j])cnt++;
        }
        if(cnt>1)return false;
    }
    return true;

}
void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
			glVertex3f( 100,0,0);
			glVertex3f(-100,0,0);

			glVertex3f(0,-100,0);
			glVertex3f(0, 100,0);

			glVertex3f(0,0, 100);
			glVertex3f(0,0,-100);
		}glEnd();
	}
}


void drawGrid()
{
	int i;
	if(drawgrid==1)
	{
		glColor3f(0.6, 0.6, 0.6);	//grey
		glBegin(GL_LINES);{
			for(i=-8;i<=8;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -90, 0);
				glVertex3f(i*10,  90, 0);

				//lines parallel to X-axis
				glVertex3f(-90, i*10, 0);
				glVertex3f( 90, i*10, 0);
			}
		}glEnd();
	}
}

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,2);
		glVertex3f( a,-a,2);
		glVertex3f(-a,-a,2);
		glVertex3f(-a, a,2);
	}glEnd();
}

void drawSS()
{
    glColor3f(1,0,0);
    drawSquare(20);

    glRotatef(angle,0,0,1);
    glTranslatef(110,0,0);
    glRotatef(2*angle,0,0,1);
    glColor3f(0,1,0);
    drawSquare(15);

    glPushMatrix();
    {
        glRotatef(angle,0,0,1);
        glTranslatef(60,0,0);
        glRotatef(2*angle,0,0,1);
        glColor3f(0,0,1);
        drawSquare(10);
    }
    glPopMatrix();

    glRotatef(3*angle,0,0,1);
    glTranslatef(40,0,0);
    glRotatef(4*angle,0,0,1);
    glColor3f(1,1,0);
    drawSquare(5);
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			drawgrid=1-drawgrid;
			break;

		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			cameraHeight -= 3.0;
			break;
		case GLUT_KEY_UP:		// up arrow key
			cameraHeight += 3.0;
			break;

		case GLUT_KEY_RIGHT:
			cameraAngle += 0.03;
			break;
		case GLUT_KEY_LEFT:
			cameraAngle -= 0.03;
			break;

		case GLUT_KEY_PAGE_UP:
			break;
		case GLUT_KEY_PAGE_DOWN:
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				drawaxes=1-drawaxes;
			}
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}



void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	gluLookAt(0,0,200,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	//drawAxes();
	//drawGrid();

    //glColor3f(1,0,0);
    //drawSquare(10);

    //drawSS();

    //drawCircle(30,24);

    //drawCone(20,50,24);

	//drawSphere(30,24,20);




	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
	angle+=0.05;
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle=0;

	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}
void initGraphics(int argc, char **argv)
{
    glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)
}
int main(int argc, char **argv){
    srand(time(0));
    initGraphics(argc,argv);

    EightQueen ob;
    ob.createRandomStartState();
    ob.run();

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
