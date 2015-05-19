#ifndef _VehicleDrivingDataChangeMessage_
#define _VehicleDrivingDataChangeMessage_

#include "Message.h"

namespace vsim
{
	class VehicleDrivingDataChangeMessage : public fire::Message
	{
	public:
		enum SteerDirection
		{
			NONE,
			LEFT,
			RIGHT
		};
		VehicleDrivingDataChangeMessage();
		~VehicleDrivingDataChangeMessage();

		VehicleDrivingDataChangeMessage::SteerDirection getSteerDirection() const;
		void setSteerDirection(VehicleDrivingDataChangeMessage::SteerDirection direction);

		bool getGasPadelPressed() const;
		void setGasPadelPressed(bool pressed);

		bool getBreakPadelPressed() const;
		void setBreakPadelPressed(bool pressed);

	private:
		VehicleDrivingDataChangeMessage::SteerDirection m_direction;
		bool m_pressGasPadel;
		float m_pressBreakPadel;
	};
}

#endif