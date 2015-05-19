#include "message/VehicleTransformChangeMessage.h"

namespace vsim
{

	VehicleTransformChangeMessage::VehicleTransformChangeMessage()
	{
		m_chassisTransform.identity();
		for (int i=0; i<4; i++)
		{
			m_wheelTransform[i].identity();
		}
	}

	VehicleTransformChangeMessage::~VehicleTransformChangeMessage()
	{

	}

	const Matrix4f& VehicleTransformChangeMessage::getChassisTransform() const
	{
		return m_chassisTransform;
	}

	void VehicleTransformChangeMessage::setChassisTransform( const Matrix4f& transform )
	{
		m_chassisTransform = transform;
	}

	const Matrix4f& VehicleTransformChangeMessage::getWheelTransform( int wheel ) const
	{
		return m_wheelTransform[wheel];
	}

	void VehicleTransformChangeMessage::setWheelTransform( int wheel, const Matrix4f& transform )
	{
		m_wheelTransform[wheel] = transform;
	}

}