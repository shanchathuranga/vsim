#include "message/TransformChangeMessage.h"

namespace vsim
{
	TransformChangeMessage::TransformChangeMessage()
	{
		m_transform.identity();
	}

	TransformChangeMessage::~TransformChangeMessage()
	{

	}

	const Matrix4f& TransformChangeMessage::getTransform() const
	{
		return m_transform;
	}

	void TransformChangeMessage::setTransform( const Matrix4f& transform )
	{
		m_transform = transform;
	}
}

