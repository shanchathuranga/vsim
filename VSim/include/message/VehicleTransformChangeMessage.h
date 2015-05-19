#ifndef _VehicleTransformChangeMessage_
#define _VehicleTransformChangeMessage_

#include "Message.h"
#include "vmath.h"

namespace vsim
{
	class VehicleTransformChangeMessage : public fire::Message
	{
	public:
		VehicleTransformChangeMessage();
		~VehicleTransformChangeMessage();

		const Matrix4f& getChassisTransform() const;
		void setChassisTransform(const Matrix4f& transform);

		const Matrix4f& getWheelTransform(int wheel) const;
		void setWheelTransform(int wheel, const Matrix4f& transform);

	private:
		Matrix4f m_chassisTransform;
		Matrix4f m_wheelTransform[4];
	};
}

#endif