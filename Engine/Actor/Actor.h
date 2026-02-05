#pragma once

#include "Common/RTTI.h"
#include "Math/Vector2.h"
#include "Math/Color.h"

namespace Nahoo
{
	class C_LEVEL;

	class NAHOO_API C_ACTOR : public C_RTTI
	{
		RTTI_DECLARATIONS(C_ACTOR, C_RTTI)

	public:
		C_ACTOR();
		C_ACTOR(const char* image, C_VECTOR2 position, E_COLOR color);
		virtual ~C_ACTOR();

	public:
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		void SetPosition(const C_VECTOR2& newPosition);
		inline C_VECTOR2 GetPosition() const { return m_position; }

		inline void SetOwner(C_LEVEL* level) { m_owner = level; }
		inline C_LEVEL* GetOwner() { return m_owner; }

		inline bool HasBegunPlay() const { return m_hasBegunPlay; }
		inline bool IsActive() const { return m_isActive && !m_destroyRequested; }
		inline bool DestroyRequested() const { return m_destroyRequested; }
		inline int GetSortingOrder() const { return m_sortingOrder; }


	protected:
		bool m_hasBegunPlay{ false };
		bool m_isActive{ true };
		bool m_destroyRequested{ false };
		char* m_image = nullptr;
		int m_sortingOrder{};

	private:
		C_LEVEL* m_owner{};
		C_VECTOR2 m_position = C_VECTOR2::Zero;
		E_COLOR m_color = E_COLOR::White;

	};

}
