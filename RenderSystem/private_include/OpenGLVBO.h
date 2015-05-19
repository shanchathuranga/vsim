#ifndef _OpenGLVBO_
#define _OpenGLVBO_

#include <string>
#include <map>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "OpenGLRenderer.h"
#include "VBO.h"

namespace smoke
{
	class OpenGLVBO : public VBO
	{
	public:
		OpenGLVBO();
		void setVertexBuffer(VertexBuffer* vertexBuffer);
		void addIndexBuffer(const std::string& matName, IndexBuffer* indexBuffer);
		void render(OpenGLRenderer& renderer);
	private:
		VertexBuffer* m_vertexBuffer;
		std::map<std::string,IndexBuffer*> m_indexBuffers;
	};
}

#endif