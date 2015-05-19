#include "PhysicsVehicleObject.h"

namespace heat
{

	void PhysicsVehicleObject::getChassisTransformMatrix( float* m )
	{
		btDefaultMotionState* myMotionState = (btDefaultMotionState*)m_vehicle->getRigidBody()->getMotionState();
		myMotionState->m_graphicsWorldTrans.getOpenGLMatrix(m);
	}

	void PhysicsVehicleObject::getWheelTransformMatrix( int wheel, float* m )
	{
		m_vehicle->getWheelInfo(wheel).m_worldTransform.getOpenGLMatrix(m);
	}

	PhysicsVehicleObject::PhysicsVehicleObject( btRaycastVehicle* vehicle ) : m_vehicle(vehicle)
	{

	}

	PhysicsVehicleObject::~PhysicsVehicleObject()
	{

	}

	void PhysicsVehicleObject::setEngineForce(float force)
	{
		m_vehicle->applyEngineForce(force, 2);
		m_vehicle->applyEngineForce(force, 3);		
	}
	
	void PhysicsVehicleObject::setBreakForce(float force)
	{
		m_vehicle->setBrake(force, 2);
		m_vehicle->setBrake(force, 3);
	}

	void PhysicsVehicleObject::setSteeringAngle(float angle)
	{
		m_vehicle->setSteeringValue(angle, 0);
		m_vehicle->setSteeringValue(angle, 1);
	}

}