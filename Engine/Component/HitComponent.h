#pragma once

#include "Component.h"
#include "Math/Vector2.h"
#include "Actor/Actor.h"
#include "Enumeration/CollisionType.h"

namespace Nahoo
{

	class NAHOO_API COMP_HITCOMPONENT : public COMP_COMPONENT
	{
		RTTI_DECLARATIONS(COMP_HITCOMPONENT, COMP_COMPONENT)
	public:
		COMP_HITCOMPONENT(const C_VECTOR2& actorPosition, int width, int height);
		~COMP_HITCOMPONENT();

		virtual void Tick(float deltaTime) override;
		virtual void Destroy() override;
		virtual void OnDestroy() override;
		
		void SetCollision(bool onOffCollision);
		bool HasCollided(COMP_HITCOMPONENT& otherComp);

		void SetCollisionType(E_COLLISIONTYPE collisionType);
		void DeleteCollisionType(E_COLLISIONTYPE collisionType);


	public:

		//getter
		inline E_COLLISIONTYPE GetCollisionType() const { return m_collisionType; }
		inline bool DestroyRequested() const { return m_destroyRequested; }
		inline bool GetCurrentCollision() const { return m_activateCollision; }
		inline const C_VECTOR2& GetActorPosition() const { return m_actorPosition; }
		inline const C_VECTOR2& GetActorWidthHeight() const { return m_actorWidthHeight; }

	private:
		bool m_activateCollision{ true };
		bool m_destroyRequested{ false };
		E_COLLISIONTYPE m_collisionType{ E_COLLISIONTYPE::None };

		// 액터 기준 좌표
		C_VECTOR2 m_actorPosition = C_VECTOR2::Zero;

		// 액터의 width를 x, height를 y에 저장
		C_VECTOR2 m_actorWidthHeight = C_VECTOR2::Zero;
		
	};
}
