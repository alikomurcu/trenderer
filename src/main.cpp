#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "iostream"
#include <glm.hpp>
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

// Global variables
float lastX = 400, lastY = 300;  // Assuming window size is 800x600
float xOffset, yOffset;
bool firstMouse = true;
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float fov = 45.0f;

Camera camera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
// In your main loop or callback function for handling key inputs
void processInput(GLFWwindow* window, Camera& camera, float deltaTime) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.processKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.processKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.processKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.processKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.processKeyboard(UPWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.processKeyboard(DOWNWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// Callback for handling mouse movement
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.processMouseMovement(xoffset, yoffset);
}

// Callback for handling mouse scroll
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
	std::cout << "fov: " << fov << std::endl;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

int main() {
	// GLFW initialization
	GLFWwindow* window;
	if (!glfwInit()) {
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetScrollCallback(window, scroll_callback);

	// GLEW initialization
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cout << "\nError:" << glewGetErrorString(err);
	}
	std::cout << "\nStatus: Using GLEW" << glewGetString(GLEW_VERSION);

	// Create and link shader program
	Shader shader("shaders/vertex1.glsl", "shaders/fragment1.glsl");

	// Create vertices and indices for a cube
	std::vector<Vertex> vertices = {
		// Front face (z = 0.5)
		{glm::vec3(0.5f,  0.5f, 0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
		{glm::vec3(0.5f, -0.5f, 0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
		{glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3(-0.5f,  0.5f, 0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)},

		// Back face (z = -0.5)
		{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f)},
		{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f)},
		{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)},

		// Right face (x = 0.5)
		{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
		{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
		{glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},

		// Left face (x = -0.5)
		{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
		{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
		{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},

		// Top face (y = 0.5)
		{glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
		{glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
		{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
		{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},

		// Bottom face (y = -0.5)
		{glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
		{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
		{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f)}
	};

	// Adjusted indices based on faces
	std::vector<unsigned int> indices = {
		// Front
		0, 1, 2, 0, 2, 3,
		// Back
		4, 5, 6, 4, 6, 7,
		// Right
		8, 9, 10, 8, 10, 11,
		// Left
		12, 13, 14, 12, 14, 15,
		// Top
		16, 17, 18, 16, 18, 19,
		// Bottom
		20, 21, 22, 20, 22, 23
	};



	// load and create a texture 
	// -------------------------
	Texture texture1("assets/container.jpg", "texture_diffuse");
	Texture texture2("assets/awesomeface.png", "texture_diffuse");

	std::vector<Texture> textures = { texture1, texture2 };

	// Create mesh
	Mesh mesh(vertices, indices, textures);

	shader.use();
	glm::mat4 projection = glm::perspective(glm::radians(fov), (float)800 / (float)600, 0.1f, 100.0f);
	shader.setMat4("projection", projection);
	glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	//view = glm::lookAt(glm::vec3(0.0f, 0.0f,2.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	view = camera.getViewMatrix();
	shader.setMat4("view", view);

	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		deltaTime = glfwGetTime() - lastFrame;
		lastFrame = glfwGetTime();
		// input
		// -----
		processInput(window, camera, deltaTime);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// render container
		shader.use();
		view = camera.getViewMatrix();
		shader.setMat4("view", view);
		
		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)800 / (float)600, 0.1f, 100.0f);
		shader.setMat4("projection", projection);

		glm::mat4 model = glm::mat4(1.0f);
		//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
		shader.setMat4("model", model);

		mesh.draw(shader);
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;

}
