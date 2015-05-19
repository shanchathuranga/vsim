#ifndef _FPSCamera_
#define _FPSCamera_

#include "ICamera.h"
#include "KeyBoard.h"
#include "RenderWindow.h"

namespace smoke
{
	class FPSCamera : public ICamera
	{
	public:
		void init(const Vector3f& eye,const Vector3f& look,const Vector3f& up);
		CameraType getType() const;
		void update(Matrix4f& mat);
		std::string& getName();

		Vector3f getPosition() const;
		Vector3f getDirection() const;

	private:
		friend class RenderSystem;
		FPSCamera(const std::string& name, const KeyBoard& keyBoard, RenderWindow& renderWindow);
		void rotate(float angle);
		void move(float speed, bool side);

		const KeyBoard& m_keyBoard;
		RenderWindow& m_renderWindow;
		bool m_isInit;

		std::string m_name;
		Vector3f m_pos;
		Vector3f m_view;
		Vector3f m_up;
	};
}

#endif