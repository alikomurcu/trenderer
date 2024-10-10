#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "iostream"
#include <glm.hpp>
#include "Model.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Light.h"

// Global variables
float lastX = 400, lastY = 300;  // Assuming window size is 800x600
float xOffset, yOffset;
bool firstMouse = true;
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float fov = 45.0f;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);

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
	if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
	{
		if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		camera.processMouseMovement(-1.0f, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		camera.processMouseMovement(1.0f, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		camera.processMouseMovement(0.0f, 1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		camera.processMouseMovement(0.0f, -1.0f);
	}
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
	Shader shader("shaders/model_vertex.glsl", "shaders/model_fragment.glsl");
	Model backpack("assets/objects/backpack/backpack.obj");
	
	shader.use();
	glm::mat4 projection = glm::perspective(glm::radians(fov), (float)800 / (float)600, 0.1f, 100.0f);
	shader.setMat4("projection", projection);
	glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	//view = glm::lookAt(glm::vec3(0.0f, 0.0f,2.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	view = camera.getViewMatrix();
	shader.setMat4("view", view);
	
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 modelPos = camera.position + camera.front * 10.0f;
	model = glm::translate(model, modelPos);
	shader.setMat4("model", model);
	
	// Lighting
	DirectionalLight dirLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.05f), glm::vec3(0.4f), glm::vec3(0.5f));
	dirLight.setLight(shader);

	PointLight pointLight1(glm::vec3(0.7f, 0.2f, 2.0f), glm::vec3(0.05f), glm::vec3(0.8f), glm::vec3(1.0f), 1.0f, 0.09f, 0.032f);
	pointLight1.setLight(shader, 0);

	PointLight pointLight2(glm::vec3(2.3f, -3.3f, -4.0f), glm::vec3(0.05f), glm::vec3(0.8f), glm::vec3(1.0f), 1.0f, 0.09f, 0.032f);
	pointLight2.setLight(shader, 1);

	PointLight pointLight3(glm::vec3(-4.0f, 2.0f, -12.0f), glm::vec3(0.05f), glm::vec3(0.8f), glm::vec3(1.0f), 1.0f, 0.09f, 0.032f);
	pointLight3.setLight(shader, 2);

	PointLight pointLight4(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.05f), glm::vec3(0.8f), glm::vec3(1.0f), 1.0f, 0.09f, 0.032f);
	pointLight4.setLight(shader, 3);

	SpotLight spotLight(camera.position, camera.front, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.0f)), glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(1.0f), 1.0f, 0.09f, 0.032f);
	spotLight.setLight(shader);


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
        glClearColor(0.6f, 0.7f, 0.3f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		
		// update spotLight
		spotLight.position = camera.position;
		spotLight.direction = camera.front;
		spotLight.setLight(shader);

		float shininess = 32.0f;
		shader.setFloat("material.shininess", shininess);

		// render container
		view = camera.getViewMatrix();
		shader.setMat4("view", view);
		
		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)800 / (float)600, 0.1f, 100.0f);
		shader.setMat4("projection", projection);
		
		backpack.draw(shader);

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
