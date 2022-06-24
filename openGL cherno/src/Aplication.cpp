#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <iostream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hay World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        /*float positions[] = {
             -50.0f, -50.0f, 0.0f, 0.0f, //0
              50.0f, -50.0f, 1.0f, 0.0f, //1
              50.0f,  50.0f, 1.0f, 1.0f, //2
             -50.0f,  50.0f, 0.0f, 1.0f, //3
        };

        unsigned int indices[]
        {
            0, 1, 2,
            2, 3, 0
        };*/
        
        GLCALL(glEnable(GL_BLEND));
        GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        /*VertexArray va;
        VertexBufferLayout layout;
        
        //pos Vertices
        layout.Push<float>(2);
        //Tex Vertices
        layout.Push<float>(2);
        
        VertexBuffer vb(positions, sizeof(positions));
        va.AddBufer(vb, layout);

        IndexBuffer ib(indices, 6);

        glm::mat4 projMat = glm::ortho(0.0f, 980.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        glm::mat4 viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

        Shader shader("res/shaders/basic.shader");
        shader.Bind();
        Texture texture("res/Textures/moon.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unind();*/

        Renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);

        ImGui::StyleColorsDark();

       /* glm::vec3 translationA(200, 200, 0);
        glm::vec3 translationB(200, 200, 0);

        float r = 0.0f;
        float increment = 0.05;*/

        test::Test* current = nullptr;
        test::TestMenu* menu = new test::TestMenu(current);
        current = menu;
        
        menu->RegisterTest<test::TestClearColor>("Clear color");
        menu->RegisterTest<test::TestTexture2D>("2D texture");

        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();

            ImGui_ImplGlfwGL3_NewFrame();
            if (current)
            {
                current->onUpdate(0.0f);
                current->onRender();
                ImGui::Begin("Test");
                if(current != menu && ImGui::Button("<-"))
                {
                    delete current;
                    current = menu;
                }
                current->onImGuiRender();
                ImGui::End();
            }

            
            /*bool show_demo_window = true;
            bool show_another_window = false;
            ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


            glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), translationA);
            glm::mat4 mvp = projMat * viewMat * modelMat;

            shader.Bind();
            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(va, ib, shader);

            modelMat = glm::translate(glm::mat4(1.0f), translationB);
            mvp = projMat * viewMat * modelMat;

            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(va, ib, shader);



            incroment = r > 1.0f ? -0.05f : (r < 0.0f ? 0.05f : incroment);
            r += incroment;*/
            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
    }
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}