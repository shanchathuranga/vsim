#include "PhysicsObject.h"
#include <iostream>

namespace heat
{

	PhysicsObject::PhysicsObject( btRigidBody* rigidBody ) : m_rigidBody(rigidBody)
	{

	}

	PhysicsObject::~PhysicsObject()
	{

	}

	void PhysicsObject::getTransformMatrix( float* m )
	{
		btTransform t;
		m_rigidBody->getMotionState()->getWorldTransform(t);
		t.getOpenGLMatrix(m);
	}

}