#pragma once

#include "Common/Common.h"

namespace UTIL
{
	class NAHOO_API C_TIMER
	{
	public:
		C_TIMER(float targetTime);

		void Tick(float deltaTime);

		void Reset();

		bool IsTimeOut() const;

		void SetTargetTime(float targetTime);

	private:

		float m_elapsedTime{};

		float m_targetTime{};

	};

}
