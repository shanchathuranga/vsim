#ifndef _PhysicsObject_
#define _PhysicsObject_

#include "IPhysicsObject.h"
#include "btBulletDynamicsCommon.h"

namespace heat
{
	class PhysicsObject : public IPhysicsObject
	{
	public:
		PhysicsObject(btRigidBody* rigidBody);
		~PhysicsObject();

		void getTransformMatrix(float* m);
	private:
		btRigidBody* m_rigidBody;
	};
}

#endif