#pragma once
#include "Test.h"

#include "glm/glm.hpp"

#include "../VertexArray.h"
#include "../IndexBuffer.h"
#include "../Shader.h"
#include "../Texture.h"

namespace test {
	class TestTexture2D : public Test
	{
	private:
		glm::mat4 projMat;
		glm::mat4 viewMat;

		glm::vec3 translationA;
		glm::vec3 translationB;

		VertexArray va;
		IndexBuffer ib;
		VertexBuffer vb;
		Shader shader;
		Texture texture;

		IndexBuffer* p_ib;
		VertexBuffer* p_vb;
	public:
		TestTexture2D();
		~TestTexture2D();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	};
}

