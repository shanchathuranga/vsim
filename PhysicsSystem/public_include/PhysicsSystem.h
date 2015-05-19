#ifndef _PhysicsSystem_
#define _PhysicsSystem_

#include "vmath.h"
#include "Definitions.h"
#include <vector>

namespace heat
{
	struct BoxInfo
	{
		Vector3f Size;
		Vector3f Position;
		float Mass;
	};
	struct SphereInfo
	{

	};
	struct CylinderInfo
	{

	};
	struct VehicleDescription
	{
		Vector3f mVehicleInitialPosition;
		Vector3f mVehicleBodySize;
		Vector3f mVehicleCoordinateSystem;
		Vector3f mWheelDirection;
		Vector3f mWheelAxle;
		Vector3f mFrontLeftWheelOffset;
		Vector3f mFrontRightWheelOffset;
		Vector3f mRearLeftWheelOffset;
		Vector3f mRearRightWheelOffset;
		float mVehicleMass;
		float mSuspensionStiffness;
		float mSuspensionCompression;
		float mSuspensionRestLength;
		float mSuspensionDamping;
		float mMaxSuspensionTravelCm;
		float mWheelsDampingRelaxation;
		float mWheelsDampingCompression;
		float mWheelFriction;
		float mWheelRadius;
		float mFrictionSlip;
		float mRollInfluence;
		float mMaxEngineForce;
		float mMaxBreakingForce;
		float mMaxSteeringAngle;
	};

	class IPhysicsObject;
	class IPhysicsVehicleObject;

	class PhysicsSystem
	{
	public:
		PhysicsSystem();
		~PhysicsSystem();

		void update(float elapsedTime);
		IPhysicsObject* createBox(const Vector3f& position, const Vector3f& size, float mass);
		IPhysicsObject* createPlane(const Vector3f& position, const Vector3f& normal);
		IPhysicsObject* createSphere(Vector3f position, float radius, float mass);
		IPhysicsObject* createCylinder();
		IPhysicsObject* createTriangleMesh(std::vector<float>& vertices, std::vector<unsigned int>& indices);
		IPhysicsVehicleObject* createVehicle(const VehicleDescription& desc);

	private:
		struct Impl;
		Impl* m_impl;
	};
}

#endif