#include "PhysicsSystem.h"
#include "btBulletDynamicsCommon.h"
#include "PhysicsObject.h"
#include <map>
#include "PhysicsVehicleObject.h"

namespace heat
{
// ------------------ Impl Start -------------------

	struct PhysicsSystem::Impl
	{
		Impl()
		{
			config = new btDefaultCollisionConfiguration();
			dispatcher = new btCollisionDispatcher(config);
			broadphase = new btDbvtBroadphase();
			solver = new btSequentialImpulseConstraintSolver();

			bWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, config);
			bWorld->setGravity(btVector3(0, -9.8f, 0));
		}

		void advance(float timestep)
		{
			bWorld->stepSimulation(timestep);
		}

		~Impl()
		{
			delete bWorld;
			delete solver;
			delete broadphase;
			delete dispatcher;
			delete config;
		}
		
		btDynamicsWorld* bWorld;
		btDispatcher* dispatcher;
		btCollisionConfiguration* config;
		btBroadphaseInterface* broadphase;
		btConstraintSolver* solver;
		
		std::map<long,btRaycastVehicle*> m_vehicles;

	};

// ------------------- Impl End --------------------

	PhysicsSystem::PhysicsSystem()
	{
		m_impl = new Impl;
	}

	PhysicsSystem::~PhysicsSystem()
	{
		delete m_impl;
	}

	void PhysicsSystem::update( float elapsedTime )
	{
		m_impl->advance(elapsedTime);
	}

	IPhysicsObject* PhysicsSystem::createBox(const Vector3f& position, const Vector3f& size, float mass)
	{
		btTransform t;
		t.setIdentity();
		t.setOrigin(btVector3(position.x, position.y, position.z));

		btBoxShape* box = new btBoxShape(btVector3(size.x, size.y, size.z));
		btVector3 inertia(0, 0, 0);
		if (mass > 0)
		{
			box->calculateLocalInertia(mass, inertia);
		}
		btMotionState* mState = new btDefaultMotionState(t);
		btRigidBody::btRigidBodyConstructionInfo cInfo(mass, mState, box);
		//cInfo.m_restitution = 0.4f;
		//cInfo.m_friction = 0.5f;
		btRigidBody* body = new btRigidBody(cInfo);
		m_impl->bWorld->addRigidBody(body);

		PhysicsObject* pObject = new PhysicsObject(body);
		return pObject;
	}

	IPhysicsObject* PhysicsSystem::createPlane(const Vector3f& position, const Vector3f& normal)
	{
		btTransform t;
		t.setIdentity();
		t.setOrigin(btVector3(position.x, position.y, position.z));

		btStaticPlaneShape* plane = new btStaticPlaneShape(btVector3(normal.x, normal.y, normal.z), 0);
		btMotionState* mState = new btDefaultMotionState(t);
		btRigidBody::btRigidBodyConstructionInfo cInfo(0, mState, plane);
		//cInfo.m_restitution = 0;
		//cInfo.m_friction = 1.5f;
		btRigidBody* body = new btRigidBody(cInfo);
		m_impl->bWorld->addRigidBody(body);

		PhysicsObject* pObject = new PhysicsObject(body);
		return pObject;
	}

	IPhysicsObject* PhysicsSystem::createSphere(Vector3f position, float radius, float mass)
	{
		btTransform t;
		t.setIdentity();
		t.setOrigin(btVector3(position.x, position.y, position.z));

		btSphereShape* sphere = new btSphereShape(radius);
		btVector3 inertia(0, 0, 0);
		if (mass > 0)
		{
			sphere->calculateLocalInertia(mass, inertia);
		}
		btMotionState* mState = new btDefaultMotionState(t);
		btRigidBody::btRigidBodyConstructionInfo cInfo(mass, mState, sphere);
		btRigidBody* body = new btRigidBody(cInfo);
		m_impl->bWorld->addRigidBody(body);

		PhysicsObject* pObject = new PhysicsObject(body);
		return pObject;
	}

	IPhysicsObject* PhysicsSystem::createCylinder()
	{
		return NULL;
	}

	IPhysicsObject* PhysicsSystem::createTriangleMesh( std::vector<float>& vertices, std::vector<unsigned int>& indices )
	{
		btTriangleMesh* triMesh = new btTriangleMesh;
		for (int i = 0; i < indices.size(); i += 3)
		{
			int pos = 3 * indices[i];
			btVector3 v1(vertices[pos], vertices[pos+1], vertices[pos+2]);
			pos = 3 * indices[i+1];
			btVector3 v2(vertices[pos], vertices[pos+1], vertices[pos+2]);
			pos = 3 * indices[i+2];
			btVector3 v3(vertices[pos], vertices[pos+1], vertices[pos+2]);
			triMesh->addTriangle(v1, v2, v3, false);
		}
		btBvhTriangleMeshShape* triMeshShape = new btBvhTriangleMeshShape(triMesh, false);
		btTransform trans;
		trans.setIdentity();     
		btDefaultMotionState* motionState = new btDefaultMotionState(trans);
		btRigidBody* body = new btRigidBody(0, motionState, triMeshShape);      
		m_impl->bWorld->addRigidBody(body);

		PhysicsObject* pObject = new PhysicsObject(body);
		return pObject;
	}

	IPhysicsVehicleObject* PhysicsSystem::createVehicle( const VehicleDescription& desc )
	{
		btVehicleRaycaster* caster = new btDefaultVehicleRaycaster(m_impl->bWorld);

		btTransform t;
		t.setIdentity();
		t.setOrigin(btVector3(desc.mVehicleInitialPosition.x, desc.mVehicleInitialPosition.y, desc.mVehicleInitialPosition.z));

		btDefaultMotionState* motionState = new btDefaultMotionState(t);

		btVector3 boxSize(
			desc.mVehicleBodySize.x/2.f,
			desc.mVehicleBodySize.y/2.f,
			desc.mVehicleBodySize.z/2.f
			);

		btBoxShape* boxShape = new btBoxShape(boxSize);
		btVector3 inertia(0,0,0);

		boxShape->calculateLocalInertia(desc.mVehicleMass, inertia);
		btRigidBody::btRigidBodyConstructionInfo bodyConstructionInfo(
			desc.mVehicleMass,
			motionState,
			boxShape,
			inertia
			);

		btRigidBody* vehicleBody = new btRigidBody(bodyConstructionInfo);
		vehicleBody->setActivationState(DISABLE_DEACTIVATION);
		m_impl->bWorld->addRigidBody(vehicleBody);

		btRaycastVehicle::btVehicleTuning tuning;
		tuning.m_suspensionStiffness = desc.mSuspensionStiffness;
		tuning.m_suspensionCompression = desc.mSuspensionCompression;
		tuning.m_suspensionDamping = desc.mSuspensionDamping;
		tuning.m_maxSuspensionTravelCm = desc.mMaxSuspensionTravelCm;
		tuning.m_frictionSlip = desc.mFrictionSlip;

		btRaycastVehicle* vehicle = new btRaycastVehicle(tuning, vehicleBody, caster);
		m_impl->m_vehicles[0] = vehicle;

		btVector3 wheelDirection(desc.mWheelDirection.x, desc.mWheelDirection.y, desc.mWheelDirection.z);

		bool isFrontWheel = true;
		vehicle->addWheel(
			btVector3(desc.mFrontLeftWheelOffset.x, desc.mFrontLeftWheelOffset.y, desc.mFrontLeftWheelOffset.z),
			wheelDirection, 
			btVector3(desc.mWheelAxle.x, desc.mWheelAxle.y, desc.mWheelAxle.z), 
			desc.mSuspensionRestLength, 
			desc.mWheelRadius, 
			tuning, 
			isFrontWheel);
		vehicle->addWheel(
			btVector3(desc.mFrontRightWheelOffset.x, desc.mFrontRightWheelOffset.y, desc.mFrontRightWheelOffset.z),
			wheelDirection, 
			btVector3(desc.mWheelAxle.x, desc.mWheelAxle.y, desc.mWheelAxle.z), 
			desc.mSuspensionRestLength, 
			desc.mWheelRadius, 
			tuning, 
			isFrontWheel);

		isFrontWheel = false;
		vehicle->addWheel(
			btVector3(desc.mRearLeftWheelOffset.x, desc.mRearLeftWheelOffset.y, desc.mRearLeftWheelOffset.z),
			wheelDirection, 
			btVector3(desc.mWheelAxle.x, desc.mWheelAxle.y, desc.mWheelAxle.z), 
			desc.mSuspensionRestLength, 
			desc.mWheelRadius, 
			tuning, 
			isFrontWheel);
		vehicle->addWheel(
			btVector3(desc.mRearRightWheelOffset.x, desc.mRearRightWheelOffset.y, desc.mRearRightWheelOffset.z),
			wheelDirection, 
			btVector3(desc.mWheelAxle.x,desc.mWheelAxle.y,desc.mWheelAxle.z),
			desc.mSuspensionRestLength,
			desc.mWheelRadius,
			tuning,
			isFrontWheel);

		m_impl->bWorld->addVehicle(vehicle);

		vehicle->setCoordinateSystem(
			desc.mVehicleCoordinateSystem.x, 
			desc.mVehicleCoordinateSystem.y,
			desc.mVehicleCoordinateSystem.z
			);

		for (int i = 0; i < vehicle->getNumWheels(); ++i)
		{
			btWheelInfo& wheel = vehicle->getWheelInfo(i);
			wheel.m_suspensionStiffness = desc.mSuspensionStiffness;
			wheel.m_wheelsDampingRelaxation = desc.mWheelsDampingRelaxation;
			wheel.m_wheelsDampingCompression = desc.mWheelsDampingCompression;
			wheel.m_frictionSlip = desc.mWheelFriction;
			wheel.m_rollInfluence = desc.mRollInfluence;
		}

		PhysicsVehicleObject* pObject = new PhysicsVehicleObject(vehicle);
		return pObject;
	}

}