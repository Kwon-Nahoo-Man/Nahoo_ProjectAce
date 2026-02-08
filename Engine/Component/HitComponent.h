#pragma once

#include "Component.h"
#include "Math/Vector2.h"
#include "Actor/Actor.h"

namespace Nahoo
{

	class NAHOO_API COMP_HITCOMPONENT : public COMP_COMPONENT
	{
		RTTI_DECLARATIONS(COMP_HITCOMPONENT, COMP_COMPONENT)
	public:
		COMP_HITCOMPONENT(const C_VECTOR2& actorPosition, int width, int height);
		~COMP_HITCOMPONENT();

		virtual void Tick(float deltaTime);
		virtual void Destroy();
		virtual void OnDestroy();
		
		void setCollition(bool onOffCollision);
		bool HasCollided(COMP_HITCOMPONENT& otherComp);
		inline bool DestroyRequested() const { return m_destroyRequested; }
		inline bool GetCurrentCollision() const { return m_activateCollision; }


	private:
		bool m_activateCollision{ true };
		bool m_destroyRequested{ false };

		// 액터 기준 좌표
		C_VECTOR2 m_actorPosition = C_VECTOR2::Zero;

		// 액터 x, y 좌표의 최대를 m_x, m_y에 저장
		C_VECTOR2 m_actorMaxPosition = C_VECTOR2::Zero;
		
	};
}
