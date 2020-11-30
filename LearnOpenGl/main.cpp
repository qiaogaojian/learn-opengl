#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader_loader.h"
#include "stb_image.h"

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
	//	 -- 位置 --			   -- 颜色 --		--纹理坐标--
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	2.0f, 0.0f,	// 0 左下角
	 0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	// 1 右下角
	 0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 2.0f,	// 2 右上角
	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	2.0f, 2.0f,	// 3 左上角
	 0.0f,  0.0f, 0.0f,		0.0f, 0.0f, 0.0f,	0.5f, 0.5f,	// 4 中间
	 0.0f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.5f, 1.0f,	// 5 中上
	 0.0f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.5f, 0.0f	// 6 中下
};
// 顶点索引
unsigned int indices[] = {
	0, 3, 4,
	1, 2, 4
};

unsigned int indices1[] = {
	0, 1, 2,
	0, 2, 3
};

unsigned int indices2[] = {
	0, 1, 2
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);					// 位置属性
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // 颜色属性  3 * sizeof(float)是偏移量
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));	// 纹理属性
	glEnableVertexAttribArray(2);


	// 第二个图形
	glBindVertexArray(VAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(triVertices), triVertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// glVertexAttribPointer() 函数把VBO注册到顶点的属性,这里可以安全的解绑
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// 这里可以解绑 VAO 防止别的 VAO 调用修改这个 VAO, 但这种情况一般不会发生,因为修改 VAO 需要调用 glBindVertexArray(), 如果不是必须的一般不解绑 VAO 或 VBO
	glBindVertexArray(0);

	// 开关绘制线框
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// 加载和创建材质
	//--------------------------------------------------------------------------------------
	// 第一个材质
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);  // 所有对GL_TEXTURE_2D的操作都会作用到 texture 对象上

	// 设置 材质延申类型
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// 设置 材质Mipmap过渡类型
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// 加载图片 创建材质 生成mipmaps
	int width;
	int height;
	int channels;
	string imgPath = "box.jpg";
	string facePath = "awesomeface.png";
	unsigned char* data = stbi_load(imgPath.c_str(), &width, &height, &channels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "加载材质失败" << endl;
	}
	stbi_image_free(data);

	// 第二个材质
	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// 设置 材质延申类型
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// 设置 材质Mipmap过渡类型
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	unsigned char* dataFace = stbi_load(facePath.c_str(), &width, &height, &channels, 0);
	if (dataFace)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataFace);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "加载材质失败" << endl;
	}
	stbi_image_free(dataFace);

	shaderLoader1.use();
	shaderLoader1.setInt("texture1", 0);
	shaderLoader1.setInt("texture2", 1);


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
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);  // 所有对GL_TEXTURE_2D的操作都会作用到 texture 对象上
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);  // 所有对GL_TEXTURE_2D的操作都会作用到 texture 对象上
		shaderLoader1.use();
		glBindVertexArray(VAO[0]);					// 因为只有一个 VAO 这里没有必要每次都绑定 VAO ,之所以这样写是为了更有组织行
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//shaderLoader2.use();
		//glBindVertexArray(VAO[1]);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

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
