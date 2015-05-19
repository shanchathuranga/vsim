#include <iostream>
#include "RenderSystem.h"
#include "IKeyListener.h"
#include "context/Context.h"
#include "Entity.h"
#include "component/RenderComponent.h"
#include "component/TransformComponent.h"
#include "component/PhysicsComponent.h"
#include "component/VehiclePhysicsComponent.h"
#include "component/InputComponent.h"

class AppTerminator : public framework::IKeyListener
{
	bool m_shouldTerminate;
	
public:
	AppTerminator()
	{
		m_shouldTerminate = false;
	}

	bool shouldTerminate() const 
	{ 
		return m_shouldTerminate; 
	}

	void keyPressed( const framework::KeyEvent* evt )
	{
		if ( evt->getKeyCode() == framework::SK_ESCAPE )
		{
			m_shouldTerminate = true;
		}
	}

	void keyReleased( const framework::KeyEvent* evt )
	{
	}

};

int main(int argc, char** argv)
{
	std::vector<fire::Entity*> entities;
	AppTerminator terminator;
	vsim::getContext().getRenderSystem().getInputEventHandler().addKeyListener(&terminator);

	// Add Camera
	smoke::ICamera* camera = vsim::getContext().getRenderSystem().createCamera(smoke::CAMERA_FPS, "Main");
	camera->init(Vector3f(5,6,5), Vector3f(0,0,0), Vector3f(0,1,0));
	vsim::getContext().getRenderSystem().setActiveCamera(camera);

	// Add Floor
	smoke::OBJModel floorModel;
	floorModel.loadFromFile("D:\\CG_Resources\\TiledFloor\\TiledFloor.obj");
	smoke::IRenderObject* renderObjectFloor = vsim::getContext().getRenderSystem().createRenderObject(&floorModel);
	heat::IPhysicsObject* physicsObjectFloor = vsim::getContext().getPhysicsSystem().createPlane(Vector3f(0,0,0), Vector3f(0,1,0));

	fire::Entity* entityFloor = vsim::getContext().getEntitySystem().createEntity();
	entityFloor->addComponent(new vsim::RenderComponent(renderObjectFloor));
	entityFloor->addComponent(new vsim::TransformComponent());
	entityFloor->addComponent(new vsim::PhysicsComponent(physicsObjectFloor));
	entities.push_back(entityFloor);

	// Add Vehicle chassis
	smoke::OBJModel chassisModel;
	chassisModel.loadFromFile("D:\\CG_Resources\\Buggy\\Chassy\\buggy.obj");
	smoke::IRenderObject* vehicleChassis = vsim::getContext().getRenderSystem().createRenderObject(&chassisModel);
	smoke::OBJModel wheelModel;
	wheelModel.loadFromFile("D:\\CG_Resources\\Buggy\\Wheel\\wheel.obj");
	smoke::IRenderObject* frontLeftWheel = vsim::getContext().getRenderSystem().createRenderObject(&wheelModel);
	smoke::IRenderObject* frontRightWheel = vsim::getContext().getRenderSystem().createRenderObject(&wheelModel);
	smoke::IRenderObject* rearLeftWheel = vsim::getContext().getRenderSystem().createRenderObject(&wheelModel);
	smoke::IRenderObject* rearRightWheel = vsim::getContext().getRenderSystem().createRenderObject(&wheelModel);

	Matrix4f wheelOffset;
	wheelOffset.identity();
	vehicleChassis->addChild(std::string("front_left"), frontLeftWheel, wheelOffset);
	vehicleChassis->addChild(std::string("front_right"), frontRightWheel, wheelOffset);
	vehicleChassis->addChild(std::string("rear_left"), rearLeftWheel, wheelOffset);
	vehicleChassis->addChild(std::string("rear_right"), rearRightWheel, wheelOffset);

	heat::VehicleDescription desc;
	desc.mVehicleInitialPosition = Vector3f(0, 2, 0);
	desc.mVehicleBodySize = Vector3f(1.98f, 1.6f, 4.7f);
	desc.mVehicleCoordinateSystem = Vector3f(0, 1, 2);
	desc.mWheelDirection = Vector3f(0, -1, 0);
	desc.mWheelAxle = Vector3f(-1, 0, 0);
	desc.mFrontLeftWheelOffset = Vector3f(-1.f, -.2f, 1.7f);
	desc.mFrontRightWheelOffset = Vector3f(1.f, -.2f, 1.7f);
	desc.mRearLeftWheelOffset = Vector3f(-1.f, -.2f, -1.7f);
	desc.mRearRightWheelOffset = Vector3f(1.f, -.2f, -1.7f);
	desc.mVehicleMass = 800.f;
	desc.mSuspensionStiffness = 20.f;
	desc.mSuspensionCompression = 4.4f;
	desc.mSuspensionRestLength = 0.6f;
	desc.mMaxSuspensionTravelCm = 500.f;
	desc.mSuspensionDamping = 2.3f;
	desc.mWheelsDampingRelaxation = 2.3f;
	desc.mWheelsDampingCompression = 3.4f;
	desc.mWheelFriction = 1e30f;
	desc.mWheelRadius = 0.5f;
	desc.mFrictionSlip = 10.5f;
	desc.mRollInfluence = 0.1f;
	desc.mMaxEngineForce = 1000.f;
	desc.mMaxBreakingForce = 100.f;
	desc.mMaxSteeringAngle = 0.8f;
	heat::IPhysicsVehicleObject* physicsVehicleObject = vsim::getContext().getPhysicsSystem().createVehicle(desc);

	fire::Entity* entityVehicle = vsim::getContext().getEntitySystem().createEntity();
	entityVehicle->addComponent(new vsim::RenderComponent(vehicleChassis));
	entityVehicle->addComponent(new vsim::TransformComponent());
	entityVehicle->addComponent(new vsim::InputComponent());
	entityVehicle->addComponent(new vsim::VehiclePhysicsComponent(physicsVehicleObject));
	entities.push_back(entityVehicle);


	// Add Test Cube
	smoke::OBJModel* model = new smoke::OBJModel();
	model->loadFromFile("D:\\CG_Resources\\Crate\\Crate1.obj");
	smoke::IRenderObject* renderObject = vsim::getContext().getRenderSystem().createRenderObject(model);
	delete model;
	heat::IPhysicsObject* physicsObject = vsim::getContext().getPhysicsSystem().createBox(Vector3f(2,10,2), Vector3f(1, 1, 1), 1000.f);

	fire::Entity* entity = vsim::getContext().getEntitySystem().createEntity();
	entity->addComponent(new vsim::RenderComponent(renderObject));
	entity->addComponent(new vsim::TransformComponent());
	entity->addComponent(new vsim::PhysicsComponent(physicsObject));
	entities.push_back(entity);

	vsim::getContext().getClock().start();

	while(vsim::getContext().getRenderSystem().isContextAvailable() && !terminator.shouldTerminate())
	{
		float timeStep = vsim::getContext().getClock().tick();

		vsim::getContext().getPhysicsSystem().update(timeStep);
		//Matrix4f pos;
		//pos.setTranslation(vsim::getContext().getRenderSystem().getActiveCamera()->getPosition());
		//vsim::getContext().getRenderSystem().addToCurrentFrame(m_levels.getCurrentLevel()->getSkyBox()->getRenderObject(), pos);

		std::vector<fire::Entity*>::iterator startIter = entities.begin();
		std::vector<fire::Entity*>::iterator endIter = entities.end();
		for (; startIter != endIter; ++startIter)
		{
			fire::Entity* gameObj = *startIter;

			vsim::InputComponent* inputComp = gameObj->getComponent<vsim::InputComponent>();
			if (inputComp) inputComp->update(gameObj, *vsim::getContext().getRenderSystem().getKeyBoard());

			vsim::PhysicsComponent* pysicsComp = gameObj->getComponent<vsim::PhysicsComponent>();
			if (pysicsComp) pysicsComp->update(gameObj, vsim::getContext().getPhysicsSystem());

			vsim::VehiclePhysicsComponent* vehiclePhysicsComp = gameObj->getComponent<vsim::VehiclePhysicsComponent>();
			if (vehiclePhysicsComp) vehiclePhysicsComp->update(gameObj, vsim::getContext().getPhysicsSystem());

			vsim::RenderComponent* renderComp = gameObj->getComponent<vsim::RenderComponent>();
			if (renderComp) renderComp->update(gameObj, vsim::getContext().getRenderSystem());
		}

		vsim::getContext().getRenderSystem().update(timeStep);

	}

	return 0;
}