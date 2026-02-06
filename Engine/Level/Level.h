#pragma once

#include <vector>

#include "Common/Common.h"
#include "Common/RTTI.h"

namespace Nahoo
{
	class C_ACTOR;
	class COMP_HITCOMPONENT;
	
	class NAHOO_API C_LEVEL : public C_RTTI
	{
		RTTI_DECLARATIONS(C_LEVEL, C_RTTI)

	public:
		C_LEVEL();
		virtual ~C_LEVEL();

	public:

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		void AddNewActor(C_ACTOR* newActor);
		void ProcessActors();

	protected:
		void ProcessAddActor();
		void ProcessDeleteActor();

	protected:
		std::vector<C_ACTOR*> m_actors{};
		std::vector<C_ACTOR*> m_addRequestedActors{};

		std::vector<COMP_HITCOMPONENT*> m_actorHitComps{};

	private:


	};

}
