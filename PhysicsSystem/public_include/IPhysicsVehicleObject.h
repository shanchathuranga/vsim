#ifndef _IPhysicsVehicleObject_
#define _IPhysicsVehicleObject_
#include "vmath.h"

namespace heat
{
	class IPhysicsVehicleObject
	{
	public:
		virtual ~IPhysicsVehicleObject(){}
		virtual void getChassisTransformMatrix(float* m) = 0;
		virtual void getWheelTransformMatrix(int wheel, float* m) = 0;
		virtual void setEngineForce(float force) = 0;
		virtual void setBreakForce(float force) = 0;
		virtual void setSteeringAngle(float angle) = 0;
	};
}

#endif