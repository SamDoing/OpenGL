#include "TestTexture2D.h"
#include "../Renderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>


test::TestTexture2D::TestTexture2D()
    : shader("res/shaders/basic.shader"), translationA(200, 200, 0), translationB(200, 200, 0),
    projMat(glm::ortho(0.0f, 980.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
    viewMat(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
    texture("res/Textures/moon.png")
{
	const float positions[] = {
	 -50.0f, -50.0f, 0.0f, 0.0f, //0
	  50.0f, -50.0f, 1.0f, 0.0f, //1
	  50.0f,  50.0f, 1.0f, 1.0f, //2
	 -50.0f,  50.0f, 0.0f, 1.0f, //3
	};

	const unsigned int indices[]
	{
		0, 1, 2,
		2, 3, 0
	};


    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    
    VertexBufferLayout layout;
    p_vb = new(&vb) VertexBuffer(positions, sizeof(positions));

    //Pos Vertices
    layout.Push<float>(2);
    //Tex Vertices
    layout.Push<float>(2);

    va.AddBufer(vb, layout);
    p_ib = new(&ib) IndexBuffer(indices, 6);

    shader.Bind();
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unind();
}

test::TestTexture2D::~TestTexture2D()
{
}

void test::TestTexture2D::onUpdate(float deltaTime)
{
}

void test::TestTexture2D::onRender()
{
	GLCALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCALL(glClear(GL_COLOR_BUFFER_BIT));

    glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), translationA);
    glm::mat4 mvp = projMat * viewMat * modelMat;

    shader.Bind();
    shader.SetUniformMat4f("u_MVP", mvp);
    Renderer render;
    render.Draw(va, ib, shader);

    modelMat = glm::translate(glm::mat4(1.0f), translationB);
    mvp = projMat * viewMat * modelMat;

    shader.SetUniformMat4f("u_MVP", mvp);
    render.Draw(va, ib, shader);

}

void test::TestTexture2D::onImGuiRender()
{
    ImGui::SliderFloat3("TranslationA", &translationA.x, 0.0f, 960.0f);
    ImGui::SliderFloat3("TranslationB", &translationB.x, 0.0f, 960.0f);
}
