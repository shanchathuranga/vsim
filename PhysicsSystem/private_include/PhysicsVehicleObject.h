#ifndef _PhysicsVehicleObject_
#define _PhysicsVehicleObject_

#include "IPhysicsVehicleObject.h"
#include "btBulletDynamicsCommon.h"

namespace heat
{
	class PhysicsVehicleObject : public IPhysicsVehicleObject
	{
	public:
		PhysicsVehicleObject(btRaycastVehicle* vehicle);
		
		~PhysicsVehicleObject();

		void getChassisTransformMatrix( float* m );

		void getWheelTransformMatrix( int wheel, float* m );

		void setEngineForce(float force);

		void setBreakForce(float force);
		
		void setSteeringAngle(float angle);

	private:
		btRaycastVehicle* m_vehicle;

	};
}

#endif