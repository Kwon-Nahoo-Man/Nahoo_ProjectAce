#pragma once
#include "Common/RTTI.h"


namespace Nahoo
{
	class C_ACTOR;
	class NAHOO_API COMP_COMPONENT : public C_RTTI
	{
		RTTI_DECLARATIONS(COMP_COMPONENT, C_RTTI)

	public:
		void SetOwner(C_ACTOR* owner);
		inline const C_ACTOR* GetOwner() const { return m_owner; }
		inline C_ACTOR* GetOwner() { return m_owner; }

	protected:
		C_ACTOR* m_owner{};

	};
}

