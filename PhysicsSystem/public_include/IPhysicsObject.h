#ifndef _IPhysicsObject_
#define _IPhysicsObject_
#include "vmath.h"

namespace heat
{
	class IPhysicsObject
	{
	public:
		virtual ~IPhysicsObject(){}
		virtual void getTransformMatrix(float* m) = 0;
	};
}

#endif