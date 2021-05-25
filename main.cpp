#define GLM_FORCE_RADIANS

#include <ctime>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
// #include "constants.h"
// #include "lodepng.h"
#include "shaderprogram.h"

float speed = 0;
float angle_speed = 0;
float camera_angle_speed = 0;

const float ANGLE_SPEED = PI/4
const float SPEED = 1

bool walking = true;

void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void keyCallback(GLFWwindow* window,int key,int scancode,int action,int mods) {
    if (action==GLFW_PRESS) {
				//worm
			  if (key==GLFW_KEY_LEFT) angle_speed = -ANGLE_SPEED;
        if (key==GLFW_KEY_RIGHT) angle_speed = ANGLE_SPEED;
        if (key==GLFW_KEY_UP) speed = SPEED;
        if (key==GLFW_KEY_DOWN) speed = -SPEED;
				//camera
			  if (key==GLFW_KEY_A) camera_angle_speed = -ANGLE_SPEED;
				if (key==GLFW_KEY_D) camera_angle_speed = ANGLE_SPEED;

    }
    if (action==GLFW_RELEASE) {
        if (key==GLFW_KEY_LEFT) angle_speed = 0;
        if (key==GLFW_KEY_RIGHT) angle_speed = 0;
        if (key==GLFW_KEY_UP) speed = 0;
        if (key==GLFW_KEY_DOWN) speed = 0;
				if (key==GLFW_KEY_SPACE) walking = !walking;
				if (key==GLFW_KEY_A) camera_angle_speed = 0;
				if (key==GLFW_KEY_D) camera_angle_speed = 0;
    }
}

void initOpenGLProgram(GLFWwindow* window) {
	glClearColor(0.2,0.2,0.9,1);
	glEnable(GL_DEPTH_TEST);
	glfwSetKeyCallback(window,keyCallback);
	// sp=new ShaderProgram("v_simplest.glsl",NULL,"f_simplest.glsl");

}

void freeOpenGLProgram(GLFWwindow* window) {
	// delete sp;
}

void drawSceneWalking(GLFWwindow* window,float angle_x,float angle_y) {
	/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUniform4f(sp->u("light_position"), 0,0,0,1); // light position
  glUniform4f(sp->u("light_position"), 0,0,0,1); // light position

	glm::mat4 V=glm::lookAt(
        glm::vec3(0.0f,0.0f,-5.0f),
        glm::vec3(0.0f,0.0f,0.0f),
        glm::vec3(0.0f,1.0f,0.0f));
  glm::mat4 P=glm::perspective(50.0f*PI/180.0f, 1.0f, 1.0f, 50.0f);

  sp->use();//activate shading program
  glUniformMatrix4fv(sp->u("P"),1,false,glm::value_ptr(P));
  glUniformMatrix4fv(sp->u("V"),1,false,glm::value_ptr(V));

  glm::mat4 M=glm::mat4(1.0f);
	M=glm::rotate(M,angle_y,glm::vec3(1.0f,0.0f,0.0f));
	M=glm::rotate(M,angle_x,glm::vec3(0.0f,1.0f,0.0f));
  glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));


  glEnableVertexAttribArray(sp->a("vertex"));
  glVertexAttribPointer(sp->a("vertex"),4,GL_FLOAT,false,0, vertices);

  glEnableVertexAttribArray(sp->a("color"));
	glVertexAttribPointer(sp->a("color"),4,GL_FLOAT,false,0,colors);

	glEnableVertexAttribArray(sp->a("normal"));
	glVertexAttribPointer(sp->a("normal"),4,GL_FLOAT,false,0,normals);


  glDrawArrays(GL_TRIANGLES,0,vertexCount);

  glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("color"));
	glDisableVertexAttribArray(sp->a("normal"));

  glfwSwapBuffers(window);*/
}

void drawSceneShooting(GLFWwindow* window,float angle_x,float angle_y){}


GLFWwindow* create_window(){
  GLFWwindow* window;
  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) { //Initialize GLFW library
    fprintf(stderr, "Can't initialize GLFW.\n");
    exit(EXIT_FAILURE);
  }

  window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);

  if (!window) //If no window is opened then close the program
  {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); //During vsync wait for the first refresh

  GLenum err;
  if ((err=glewInit()) != GLEW_OK) { //Initialize GLEW library
    fprintf(stderr, "Can't initialize GLEW: %s\n", glewGetErrorString(err));
    exit(EXIT_FAILURE);
  }

  initOpenGLProgram(window);

  return window;
}



int main(void)
{
	srand(time(NULL));
  GLFWwindow* window = create_window();

	Board* board;
	vector<Worm*> worms = [Worm("Napoleon", board), Worm("Che Guevara", board)];
	Camera* camera;
	glm::vec3 wind = (std::rand(20)/10-10, std::rand(6)/10-3, std::rand(20)/10-10);

	glfwSetTime(0); //Zero the timer
	//Main application loop
	while (!glfwWindowShouldClose(window))
	{
		for(int i=0; i<2; i++){
			active_worm = worms[i];
			clock_t start = clock();
			while((clock() - start/ (double) CLOCKS_PER_SEC <= 20) && walking = true){
				//ruch gracza
				active_worm.update(speed, angle_speed, glfwGetTime());
				glfwSetTime(0);

				drawSceneWalking(window,angle_x,angle_y);
				glfwPollEvents();
			}

			while(walking=false){
				glfwSetTime(0);

				drawSceneShooting(window,angle_x,angle_y);
				glfwPollEvents();
			}

			Bullet* bullet = Bullet(active_worm.get_position(), camera->get_angle_x(), camera->get_angle_y());
			camera->change_mode();
			while(bullet.speed != (0,0,0)){
				bullet.apply_gravity_and_wind(wind, glfwGetTime());
				bullet.check_collision(board, worms);

				glfwSetTime(0);

				drawSceneShooting(window,angle_x,angle_y);
				glfwPollEvents();
			}

			drawSceneExplosion();

		}
	}
	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Delete OpenGL context and the window.
	glfwTerminate(); //Free GLFW resources
	exit(EXIT_SUCCESS);
}