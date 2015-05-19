#ifndef _ICamera_
#define _ICamera_

#include "vmath.h"
#include <string>

namespace smoke
{
	enum CameraType
	{
		CAMERA_FPS,
		CAMERA_3RD_PERSON,
		CAMERA_FREE
	};
	class ICamera
	{
	public:
		virtual void init(const Vector3f& eye, const Vector3f& look, const Vector3f& up) = 0;
		virtual CameraType getType() const = 0;
		virtual void update(Matrix4f& mat) = 0;
		virtual std::string& getName() = 0;

		virtual Vector3f getPosition() const = 0;
		virtual Vector3f getDirection() const = 0;
	};
}

#endif