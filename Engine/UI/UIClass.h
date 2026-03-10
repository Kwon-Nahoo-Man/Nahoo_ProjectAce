#pragma once
#include <vector>

#include "Common/RTTI.h"
#include "Math/Vector2.h"
#include "Enumeration/Color.h"

namespace Nahoo
{
	class C_LEVEL;
	class NAHOO_API C_UICLASS : public C_RTTI
	{
		RTTI_DECLARATIONS(C_UICLASS, C_RTTI)

	public:
		C_UICLASS() = default;
		C_UICLASS(const char* fileName, const C_VECTOR2& position);
		virtual ~C_UICLASS();

	public:
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		virtual void Destroy();
		virtual void OnDestroy();

		// setter
		void SetPosition(const C_VECTOR2& newPosition);
		inline void SetActive(bool isActive) { m_isActive = isActive; }
		inline void SetOwner(C_LEVEL* level) { m_owner = level; }
		inline void SetColor(E_COLOR color) { m_color = color; }

		
		// getter
		inline const C_VECTOR2& GetPosition() { return m_position; }
		inline C_LEVEL* GetOwner() { return m_owner; }
		inline bool HasBegunPlay() const { return m_hasBegunPlay; }
		inline bool IsActive() const { return m_isActive && !m_destroyRequested; }
		inline bool DestroyRequested() const { return m_destroyRequested; }
		inline int GetSortingOrder() const { return m_sortingOrder; }
		inline int GetActorWidth() const { return m_width; }
		inline int GetActorHeight() const { return m_height; }


	protected:
		int m_sortingOrder{};
		E_COLOR m_color = E_COLOR::White;
		std::vector<char>m_sprite{};
		int m_width{};
		int m_height{};

	private:

		bool m_hasBegunPlay{ false };
		bool m_isActive{ true };
		bool m_destroyRequested{ false };
		C_LEVEL* m_owner{};
		C_VECTOR2 m_position = C_VECTOR2::Zero;


	};
}



