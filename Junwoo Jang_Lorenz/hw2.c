/*
	Junwoo Jang - CS 5229 - HW2
	Got few ideas from example 6 and 9
	
	This Program displays the lorenz attractor in different angles, perspectives, 
	closeness, and dimensions (in x-axis, y-axis, and z-axis).
	
	*******Hot Keys*******
	↑↓→←: View with different angles
	0: Original(Reset) view with original angle
	PageDown/PageUp: Zoom in/out
	ESC: Exit Program
	+: x dimension increase
	-: x dimension decrease
	*: y dimension increase
	/: y dimension decrease
	]: z dimension increase
	[: z dimension decrease
 
*/

//Header files
#include <math.h> //standard library  for basic mathematical operations
#include <stdlib.h> //handles memory allocation, process control, conversions and others
#include <stdarg.h> //for  indefinite number of argument
#include <stdio.h> //for input and output
#include <string.h> 
//for OpenGL 
#ifdef USEGLEW 
#include <GL/glew.h> 
#endif 
#define GL_GLEXT_PROTOTYPES 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 


//variables
int circangle=0; //Azimuth when viewing angle
int elevat=0; //Elevation when viewing angle
int viewstructure=0; //1D,2D,3D,4D: view mode, but we only have 1 view mode in this program
int sightangle=55; //Perspective

double siderat=1; //side ratio
double z_axis=0;     
double dimension=5.0;  

//X,Y,Z dimension 
double X_dim = 0.04; 
double Y_dim = 0.04;
double Z_dim = 0.04;


char* Dim_title[] = {"(Reset)Original View",""}; //Dimension view Title(We only have one view here)


#define LEN 8192  

//To print out
void characprint(const char* format , ...) 
{
   char    chprint[LEN]; //Set length(8192) for the characters
   char*   ch=chprint; 
   va_list args; 
  
   va_start(args,format); 
   vsnprintf(chprint,LEN,format,args); 
   va_end(args); 
   
   //  Display chracters
   while (*ch) 
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}


// To use GLUT, this function is necessary
void Fatal4gl(const char* format , ...) 
{
   va_list args; 
   va_start(args,format); 
   vfprintf(stderr,format,args); 
   va_end(args); 
   exit(1); 
} 


//For the Projection
static void Projection() 
{ 
  
   glMatrixMode(GL_PROJECTION); //to manipulate the projection matrix
   glLoadIdentity(); 
   //1D~4D views
   if (viewstructure) 
      gluPerspective(sightangle,siderat,dimension/4,4*dimension); 
   else 
      glOrtho(-siderat*dimension,+siderat*dimension, -dimension,+dimension, -dimension,+dimension); 
  
   glMatrixMode(GL_MODELVIEW); 
   
   glLoadIdentity(); 
} 

//Drawing Lorenz Attractor
void draw_lorenz(){

	//Lorenz variables
    double s  = 12;
    double b  = 2.7777;
    double r  = 30;
    
    
    int i; //initialzation variable for "for loop"
    
    double x_axis = 1;
    double y_axis = 1;
    double z_axis = 1;
	

	double delta_t = 0.002;
    double color_a = 0;
    double color_b = 1;
    double color_c = 1;
	
	
	
	for (i=0;i<40000;i++) //Actual drwaing part
    {
		//formulas for Lorenz Attractor
        double dx = s*(y_axis-x_axis);
        double dy = x_axis*(r-z_axis)-y_axis;
        double dz = x_axis*y_axis - b*z_axis;
        x_axis += delta_t*dx;
        y_axis += delta_t*dy;
        z_axis += delta_t*dz;
        glColor3d(color_a, color_b, color_c);
        glVertex3d(x_axis*X_dim,y_axis*Y_dim,z_axis*Z_dim);
    }
}

//For the scene(background)
void draw_scene() 
{ 
   
   glClear(GL_COLOR_BUFFER_BIT); 
   glLoadIdentity(); 
   
   //  initializing view angle
   glRotated(elevat,1,0,0);
   glRotated(circangle,0,1,0); 
   glBegin(GL_LINE_LOOP); 

	
   draw_lorenz();
	
	
   glEnd(); 
   //  Drawing axes with set up colors
   glColor3d(1,1,1); 
   glBegin(GL_LINES); 
   glVertex3d(0,0,0); 
   glVertex3d(1,0,0); 
   glVertex3d(0,0,0); 
   glVertex3d(0,1,0); 
   glVertex3d(0,0,0); 
   glVertex3d(0,0,1); 
   glEnd(); 
   
   
   // Set up X,Y,Z axes
   glRasterPos3d(1,0,0); 
   characprint("X"); 
   glRasterPos3d(0,1,0); 
   characprint("Y"); 
   glRasterPos3d(0,0,1); 
   characprint("Z"); 
   
   glWindowPos2i(5,5); //First window position
   
   characprint("View Angle=%d,%d %s",circangle,elevat,Dim_title[viewstructure]); 
   
   glFlush(); 
   glutSwapBuffers(); 
   
} 


// Hot keys to see Lorenz Attractor  in different angles, perspectives, closeness, and dimensions (in x-axis, y-axis, and z-axis)
void hotkey_press(unsigned char ch,int x_axis,int y_axis) 
{ 
   //  Press ESC then Exit the program
   if (ch == 27)
   {
      exit(0); 
   }
   
   // Press 0, then go back to original view(reset)
   else if (ch == '0') 
   { 
  
    circangle = elevat = 0; 
    X_dim = 0.04;
	Y_dim = 0.04;
	Z_dim = 0.04;
	viewstructure = 0;
	characprint("View Angle=%d,%d %s",circangle,elevat,Dim_title[viewstructure]);
   } 
    
	//Press + to increase X dimension, - to decrease X dimension
    else if (ch == '+') 
    {
		X_dim += 0.001;
    }
    else if (ch == '-')
    {
		X_dim -= 0.001;
    }
	
	//Press * to increase Y dimension, / decrease Y dimension
	else if (ch == '*')
    {
		Y_dim += 0.001;
    }
    else if (ch == '/')
    {
		Y_dim -= 0.001;
    }
	
	
	//Press ] to increase Z dimension, [ to decrease Z dimension
	else if (ch == ']')
    {
		Z_dim += 0.001;
    }
    else if (ch == '[')
    {
		Z_dim -= 0.001;
	
    }
   glutPostRedisplay(); 
}

// For special hotkeys that set up with ASCII codes
void special_hotkey(int hotkey_press,int x_axis,int y_axis) 
{ 
	//↑↓→←: View with different angles
   if (hotkey_press == GLUT_KEY_RIGHT) 
      circangle += 5; 
   else if (hotkey_press == GLUT_KEY_LEFT) 
      circangle -= 5; 
   else if (hotkey_press == GLUT_KEY_UP) 
	  elevat += 5;
   else if (hotkey_press == GLUT_KEY_DOWN) 
      elevat -= 5; 
  
   //PageDown/PageUp: Zoom in/out
   else if (hotkey_press == GLUT_KEY_PAGE_UP) 
      dimension += 0.1; 
   else if (hotkey_press == GLUT_KEY_PAGE_DOWN && dimension>1) 
      dimension -= 0.1; 
   circangle %= 360; //set angles to +/-360 degrees
   elevat %= 360; //set elevation to +/-360 degrees
 
   Projection(); 
   
   glutPostRedisplay(); 
} 



//Reshape
void shapeRedraw(int width,int height) 
{ 

   double widnheight = (height>0) ? (double)width/height : 1; 
   glViewport(0,0, width,height);
   glMatrixMode(GL_PROJECTION); 
   glLoadIdentity(); 
   glOrtho(-dimension*widnheight,+dimension*widnheight, -dimension,+dimension, -dimension,+dimension);//^^asp->w2h
   glMatrixMode(GL_MODELVIEW); 
   glLoadIdentity(); 
} 

// Tell GLUT what to do
int main(int argument1,char* argument2[]) 
{ 

   glutInit(&argument1,argument2); 
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); 
   glutInitWindowSize(700,700); 
   glutCreateWindow("Lorenz Attractor by Junwoo Jang"); 
   #ifdef USEGLEW 
   
   if (glewInit()!=GLEW_OK) Fatal4gl("Error initializing GLEW\n"); //Essential to use GLUT
   #endif 
   glutDisplayFunc(draw_scene); 
   glutReshapeFunc(shapeRedraw); 
   glutSpecialFunc(special_hotkey); 
   glutKeyboardFunc(hotkey_press); 
   glutMainLoop(); 
 
   return 0; 
} 


