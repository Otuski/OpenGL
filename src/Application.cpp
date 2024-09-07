#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>

#include <string>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shaders.h"

#include "Texture.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    
    if (glewInit() != GLEW_OK)
        std::cout << "Error!";

    
    const int size = 20;

    /*
    float positions[size] = {
        -0.5f, -0.5f,  0.0f,  0.0f, //0
         0.5f, -0.5f,  1.0f,  0.0f, //1
         0.5f,  0.5f,  1.0f,  1.0f, //2
        -0.5f,  0.5f,  0.0f,  1.0f, //3
    };
    */
    float positions[size] = {
        -50.0f, -50.0f,  0.0f,  0.0f, //0
         50.0f, -50.0f,  1.0f,  0.0f, //1
         50.0f,  50.0f,  1.0f,  1.0f, //2
        -50.0f,  50.0f,  0.0f,  1.0f, //3
    };
    
    //dati dell'index buffer
    unsigned int indices[] = {
        0, 1, 2, //primo triangolo
        2, 3, 0, //secondo triangolo
    };

    VertexArray va;
    VertexBuffer vb(positions, sizeof(positions));
    VertexBufferLayout layout;

    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer( vb, layout );

    IndexBuffer ib(indices, 6);

    glm::vec3 translation(0.0f, 0.0f, 0.0f);

    glm::mat4 proj = glm::ortho( 0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f ); //trasforma lo schermo da [-1;1] a x = [-2;2] y = [-1.5;1.5] conclusione: è lo zoom o il dezoom
    glm::mat4 view = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f) ); //sposta la camera
    glm::mat4 model = glm::translate( glm::mat4(1.0f), translation ); //sposta l'oggetto

    glm::vec4 pos( -0.5f, 0.5f, 0.0f, 0.0f);

    Shader shader("res/shader/Basic.shader");

    shader.Bind();

    float r = 0.0f;
    float increment = 0.5f;

    Renderer renderer;

    //setup imgui
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    Texture texture("res/Texture/pentagono.png");
    
    int slot = 0;
    texture.Bind(slot);

    shader.setUniform1i("u_Texture", slot);

    //variabili per imgui
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        renderer.Clear();

        ImGui_ImplGlfwGL3_NewFrame();

        shader.setUniform4f("u_Color", clear_color.x, clear_color.y, clear_color.z, clear_color.w);

        renderer.Draw(va, ib, shader);


        if (r <= 0.0f)
            increment = 0.05f;
        else if (r >= 1.0f)
            increment = -0.05f;

        r += increment;

        glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
        glm::mat4 mvp = proj * view * model;

        shader.setUniformMat4f("u_MVP", mvp);

        //pezzo imgui
        {
            static float f = 0.0f;
            static int counter = 0;
            ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 960.0f);
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
        
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    //glDeleteProgram(shader);

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
} 