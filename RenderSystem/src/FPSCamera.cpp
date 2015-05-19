#include "FPSCamera.h"

namespace smoke
{
	const float m_moveSpeed = 0.005f;
	const float m_lookSpeed = 5.f;

	FPSCamera::FPSCamera(const std::string& name, const KeyBoard& keyBoard, RenderWindow& renderWindow) :
		m_keyBoard(keyBoard), m_renderWindow(renderWindow), m_isInit(false)
	{
		m_name = name;
	}

	void FPSCamera::init( const Vector3f& eye,const Vector3f& look,const Vector3f& up )
	{
		m_pos = eye;
		m_view = look;
		m_up = up;
		m_isInit = true;
	}

	CameraType FPSCamera::getType() const
	{
		return CAMERA_FPS;
	}

	void FPSCamera::update(Matrix4f& mat)
	{
		int winCenterX = m_renderWindow.getWidth()/2;
		int winCenterY = m_renderWindow.getHeight()/2;
		int mouseX = 0;
		int mouseY = 0;

		m_renderWindow.getMousePosition(mouseX, mouseY);

		int deltaX = winCenterX - mouseX;
		int deltaY = winCenterY - mouseY;

		//if (deltaX == 0 && deltaY == 0) return;

		m_renderWindow.setMousePosition(winCenterX, winCenterY);

		float angleY = (float)( (winCenterX - mouseX) ) / 1000;		
		float angleZ = (float)( (winCenterY - mouseY) ) / 1000;

		m_view.y += angleZ * m_lookSpeed;

		if ((m_view.y - m_pos.y) > 8)
			m_view.y = m_pos.y + 8;
		if ((m_view.y - m_pos.y) <-8)
			m_view.y = m_pos.y - 8;

		rotate(-angleY);

		if (m_keyBoard.isKeyDown(framework::SK_W))
		{
			move(m_moveSpeed, true);
		}
		else if (m_keyBoard.isKeyDown(framework::SK_S))
		{
			move(-m_moveSpeed, true);
		}
		if (m_keyBoard.isKeyDown(framework::SK_A))
		{
			move(-m_moveSpeed, false);
		}
		else if (m_keyBoard.isKeyDown(framework::SK_D))
		{
			move(m_moveSpeed, false);
		}

		mat = Matrix4f::createLookAt(m_pos, m_view, m_up);
	}

	void FPSCamera::rotate( float angle )
	{
		Vector3f direction = m_view - m_pos;

		m_view.z = (float)(m_pos.z + sin(angle)*direction.x + cos(angle)*direction.z);
		m_view.x = (float)(m_pos.x + cos(angle)*direction.x - sin(angle)*direction.z);
	}

	void FPSCamera::move( float speed, bool side )
	{
		Vector3f direction = m_view - m_pos;
		if (side)
		{
			m_pos.x  = m_pos.x  + direction.x * speed;
			m_pos.z  = m_pos.z  + direction.z * speed;
			m_view.x = m_view.x + direction.x * speed;
			m_view.z = m_view.z + direction.z * speed;
		}
		else
		{
			Vector3f right = direction.crossProduct(m_up);
			m_pos.x  = m_pos.x  + right.x * speed;
			m_pos.z  = m_pos.z  + right.z * speed;
			m_view.x = m_view.x + right.x * speed;
			m_view.z = m_view.z + right.z * speed;
		}
	}

	Vector3f FPSCamera::getPosition() const
	{
		return m_pos;
	}

	Vector3f FPSCamera::getDirection() const
	{
		Vector3f direction = m_view - m_pos;
		direction.normalize();
		return direction;
	}

	std::string& FPSCamera::getName()
	{
		return m_name;
	}

}