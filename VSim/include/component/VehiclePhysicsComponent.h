#ifndef _VehiclePhysicsComponent_
#define _VehiclePhysicsComponent_

#include "Component.h"
#include "IPhysicsVehicleObject.h"
#include "Entity.h"
#include "PhysicsSystem.h"

namespace vsim
{
	class VehiclePhysicsComponent : public fire::Component
	{
	public:
		VehiclePhysicsComponent(heat::IPhysicsVehicleObject* physicsVehicleObject);
		~VehiclePhysicsComponent();

		const std::string& getComponentName() const;
		static const std::string& getComponentNameStatic();

		void update(fire::Entity* entity, heat::PhysicsSystem& physicsSystem);

	private:
		heat::IPhysicsVehicleObject* m_physicsVehicleObject;
	};
}

#endif