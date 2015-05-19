#ifndef _IndexBuffer_
#define _IndexBuffer_

#include "GL/glew.h"
#include "GL/GL.h"
#include "GL/GLU.h"
#include <vector>

namespace smoke
{
	class IndexBuffer
	{
	public:
		IndexBuffer( const std::vector<unsigned short>& indices );
		void bind() const;
		void unbind() const;
		int getIndexCount() const;
	private:
		int m_indexCount;
		GLuint m_ID;
	};
}

#endif