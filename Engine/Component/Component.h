#pragma once
#include "Common/RTTI.h"


namespace Nahoo
{
	class C_ACTOR;
	class NAHOO_API COMP_COMPONENT : public C_RTTI
	{
		RTTI_DECLARATIONS(COMP_COMPONENT, C_RTTI)

	public:

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Destroy();
		virtual void OnDestroy();

		void SetOwner(C_ACTOR* owner);
		inline const C_ACTOR* GetOwner() const { return m_owner; }
		inline bool HasBegaunPlay() const { return m_hasBeganPlay; }
		inline C_ACTOR* GetOwner() { return m_owner; }

	protected:
		C_ACTOR* m_owner{};
		bool m_destroyRequested{ false };
		bool m_hasBeganPlay{ false };
	};
}

