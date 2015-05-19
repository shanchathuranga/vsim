#ifndef _RenderObject_
#define _RenderObject_

#include "IRenderObject.h"
#include "VBO.h"
#include <map>

namespace smoke
{
	class RenderObject : public IRenderObject
	{
	public:
		typedef std::map<std::string,std::pair<IRenderObject*,Matrix4f> > RenderChildren;
		RenderObject(VBO* vbo);
		~RenderObject();
		VBO* getVBO();
		void addChild(const std::string& name, IRenderObject* child, Matrix4f& offsetTransform);
		void setChildTransform( const std::string& name, const Matrix4f& transform );
		RenderObject::RenderChildren& getChildren();

	private:
		VBO* m_vbo;
		RenderChildren m_children;
	};
}

#endif