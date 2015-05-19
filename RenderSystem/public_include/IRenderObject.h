#ifndef _IRenderObject_
#define _IRenderObject_

#include "vmath.h"

namespace smoke
{
	class IRenderObject
	{
	public:
		virtual ~IRenderObject(){}
		virtual void addChild(const std::string& name, IRenderObject* child, Matrix4f& offsetTransform) = 0;
		virtual void setChildTransform(const std::string& name, const Matrix4f& transform) = 0;
	};
}

#endif