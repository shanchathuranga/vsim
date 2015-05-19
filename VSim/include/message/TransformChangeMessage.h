#ifndef _TransformChangeMessage_
#define _TransformChangeMessage_
#include "Message.h"
#include "vmath.h"

namespace vsim
{
	class TransformChangeMessage : public fire::Message
	{
	public:
		TransformChangeMessage();
		~TransformChangeMessage();
		const Matrix4f& getTransform() const;
		void setTransform(const Matrix4f& transform);

	private:
		Matrix4f m_transform;
	};
}

#endif