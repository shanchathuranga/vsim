#ifndef _VertexBuffer_
#define _VertexBuffer_

#include <Windows.h>
#include "Definitions.h"
#include <vector>
#include "Vertex.h"
#include "GL/glew.h"
#include "GL/GL.h"
#include "GL/GLU.h"

namespace smoke
{
	class VertexBuffer
	{
	public:
		VertexBuffer(const std::vector<Vertex>& vertices);
		void bind() const;
		void unbind() const;
	private:
		GLuint m_ID;
	};
}

#endif