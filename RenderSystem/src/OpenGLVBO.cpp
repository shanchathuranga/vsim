#include "OpenGLVBO.h"

namespace smoke
{

	OpenGLVBO::OpenGLVBO() : m_vertexBuffer(NULL)
	{
	}

	void OpenGLVBO::setVertexBuffer( VertexBuffer* vertexBuffer )
	{
		m_vertexBuffer = vertexBuffer;
	}

	void OpenGLVBO::addIndexBuffer( const std::string& matName, IndexBuffer* indexBuffer )
	{
		m_indexBuffers[matName] = indexBuffer;
	}

	void OpenGLVBO::render( OpenGLRenderer& renderer )
	{
		for (std::map<std::string,IndexBuffer*>::const_iterator it = m_indexBuffers.begin(), eit = m_indexBuffers.end(); it != eit; ++it)
		{
			const IndexBuffer* indexBuffer = it->second;
			renderer.setActiveTexture(it->first);
			renderer.drawBuffers(m_vertexBuffer, indexBuffer);
		}
	}

}