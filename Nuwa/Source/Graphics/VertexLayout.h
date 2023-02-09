#pragma once
#include "../EngineTypes.h"
#include <vector>

namespace Nuwa
{
	class VertexLayout
	{
	public:
		VertexLayout() : stride(0) {}
		~VertexLayout() {}

		template<typename T>
		inline void Push(uint count)
		{
			static_assert(false);
		}

		template<>
		inline void Push<float>(uint count)
		{
			// type, count, normalized
			elements.push_back({ GL_FLOAT, count, GL_FALSE });
			stride += VertexElement::GetTypeSize(GL_FLOAT) * count;
		}

		template<>
		inline void Push<uint>(uint count)
		{
			elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			stride += VertexElement::GetTypeSize(GL_UNSIGNED_INT) * count;
		}

		template<>
		inline void Push<uchar>(uint count)
		{
			elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
			stride += VertexElement::GetTypeSize(GL_UNSIGNED_BYTE) * count;
		}

	private:
		uint stride;
		std::vector<VertexElement> elements;
	};
}


