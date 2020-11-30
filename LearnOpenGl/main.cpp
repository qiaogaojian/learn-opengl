#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader_loader.h"

#include <iostream>
using namespace std;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// 三角形顶点
float triVertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};
// 矩形顶点
float rectVertices[] = {
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	// 0左下角
	 0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	// 1右下角
	 0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	// 2右上角
	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	// 3左上角
	 0.0f,  0.0f, 0.0f,		0.0f, 0.0f, 0.0f,	// 4中间
	 0.0f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	// 5中上
	 0.0f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f	// 6中下
};
// 顶点索引
unsigned int indices[] = {
	0, 3, 4,
	1, 2, 4
};

unsigned int indices1[] = {
	0, 3, 6
};

unsigned int indices2[] = {
	1, 2, 5
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	// 初始化和配置 glfw
	//--------------------------------------------------------------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建窗口对象
	//--------------------------------------------------------------------------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// 设置上下文为当前窗口对象
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	// 初始化 glad  加载所有 opengl 的函数指针
	//--------------------------------------------------------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// 构建和编译 shader 程序
	//--------------------------------------------------------------------------------------
	ShaderLoader shaderLoader1("3.3.vs.shader.glsl", "3.3.fs.shader1.glsl", nullptr);
	ShaderLoader shaderLoader2("3.3.vs.shader.glsl", "3.3.fs.shader2.glsl", nullptr);

	// 设置顶点数据 配置顶点属性
	//--------------------------------------------------------------------------------------
	unsigned int VAO[2], VBO[2], EBO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);
	glGenBuffers(2, EBO);
	// 首先绑定VAO, 然后绑定并设置VBO, 然后设置顶点属性
	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(triVertices), triVertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);					// 位置属性
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // 颜色属性  3 * sizeof(float)是偏移量
	glEnableVertexAttribArray(1);


	// 第二个图形
	glBindVertexArray(VAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(triVertices), triVertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// glVertexAttribPointer() 函数把VBO注册到顶点的属性,这里可以安全的解绑
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// 这里可以解绑 VAO 防止别的 VAO 调用修改这个 VAO, 但这种情况一般不会发生,因为修改 VAO 需要调用 glBindVertexArray(), 如果不是必须的一般不解绑 VAO 或 VBO
	glBindVertexArray(0);

	// 开关绘制线框
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// 渲染循环
	//--------------------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window)) // 我们每次循环的开始前检查一次GLFW是否被要求退出，如果是的话该函数返回true然后渲染循环便结束了
	{
		// 输入
		processInput(window);


		// 渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	// 设置状态
		glClear(GL_COLOR_BUFFER_BIT);			// 使用状态

		// 绘制图形
		shaderLoader1.use();
		//int uniColorLocation1 = glGetUniformLocation(shaderProgram, "uniColor1");
		float time = glfwGetTime();
		float alpha = (sin(time) / 2.0f) + 0.5f;
		//glUniform4f(uniColorLocation1, 1.0f, alpha, 0.0f, 1.0f);

		glBindVertexArray(VAO[0]);					// 因为只有一个 VAO 这里没有必要每次都绑定 VAO ,之所以这样写是为了更有组织行
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);						// 不需要每次都解绑

		shaderLoader2.use();
		shaderLoader2.setFloat("uniColor2", alpha);
		glBindVertexArray(VAO[1]);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		// 检查并调用事件，交换缓冲
		glfwPollEvents();			// 检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）
		glfwSwapBuffers(window);	// 双缓冲交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上
	}

	// 释放资源
	//--------------------------------------------------------------------------------------
	// 释放 shader 资源
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	glDeleteBuffers(2, EBO);

	// 释放 GLFW 资源
	glfwTerminate();				// 当渲染循环结束后我们需要正确释放/删除之前的分配的所有资源 这样便能清理所有的资源并正确地退出应用程序
	return 0;
}

// 窗口大小改变时 调整视口大小
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// 处理输入
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
