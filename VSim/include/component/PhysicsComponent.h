#ifndef _PhysicsComponent_
#define _PhysicsComponent_

#include "Entity.h"
#include "PhysicsSystem.h"
#include "Component.h"
#include "IPhysicsObject.h"

namespace vsim
{
	class PhysicsComponent : public fire::Component
	{
	public:
		PhysicsComponent(heat::IPhysicsObject* physicsObject);
		~PhysicsComponent();
		const std::string& getComponentName() const;
		static const std::string& getComponentNameStatic();

		void update(fire::Entity* entity, heat::PhysicsSystem& physicsSystem);

	private:
		heat::IPhysicsObject* m_physicsObject;
		Matrix4f m_transform;
	};
}

#endif