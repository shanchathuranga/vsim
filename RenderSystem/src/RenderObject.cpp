#include "RenderObject.h"

namespace smoke
{
	RenderObject::RenderObject( VBO* vbo ) : m_vbo(vbo)
	{

	}

	RenderObject::~RenderObject()
	{
		delete m_vbo;
	}

	VBO* RenderObject::getVBO()
	{
		return m_vbo;
	}

	void RenderObject::addChild( const std::string& name, IRenderObject* child, Matrix4f& offsetTransform )
	{
		m_children[name] = std::make_pair(child,offsetTransform);
	}

	RenderObject::RenderChildren& RenderObject::getChildren()
	{
		return m_children;
	}

	void RenderObject::setChildTransform( const std::string& name, const Matrix4f& transform )
	{
		std::pair<IRenderObject*,Matrix4f>& data = m_children[name];
		data.second = transform;
	}

}

