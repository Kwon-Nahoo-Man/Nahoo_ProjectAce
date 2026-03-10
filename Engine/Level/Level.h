#pragma once

#include <vector>

#include "Common/Common.h"
#include "Common/RTTI.h"
#include "Enumeration/DebugShow.h"

namespace Nahoo
{
	class C_ACTOR;
	class C_UICLASS;
	class COMP_HITCOMPONENT;
	class C_QUADTREE;
	class C_EFFECTMANAGER;
	
	class NAHOO_API C_LEVEL : public C_RTTI
	{
		RTTI_DECLARATIONS(C_LEVEL, C_RTTI)

	public:
		C_LEVEL(bool quadTreeFlag = false);
		virtual ~C_LEVEL();

	public:

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		void AddNewActor(C_ACTOR* newActor);
		void AddNewUI(C_UICLASS* newUI);
		void ProcessClasses();

		// getter
		inline C_EFFECTMANAGER* GetEffectManager() const { return m_effectManager; }

	protected:
		// 디버그 Toggle
		void SetDebugDraw(E_DEBUGSHOW changeValue);

		void ProcessAddActor();
		void ProcessAddUI();

		void ProcessDeleteActor();
		void ProcessDeleteUI();

		void ProcessQuadTree();

	protected:
		E_DEBUGSHOW m_debugShow = E_DEBUGSHOW::None;

		std::vector<C_ACTOR*> m_actors{};
		std::vector<C_ACTOR*> m_addRequestedActors{};

		std::vector<COMP_HITCOMPONENT*> m_actorHitComps{};

		// Todo: UI만을 관리하는 클래스 따로 구현해서 그곳에서 UI를 add,delete
		std::vector<C_UICLASS*> m_UIs{};
		std::vector<C_UICLASS*> m_addRequestedUIs{};

		C_QUADTREE* m_quadTree{};
		C_EFFECTMANAGER* m_effectManager{};

	private:

	};

}
