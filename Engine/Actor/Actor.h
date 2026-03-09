#pragma once
#include <vector>
#include <string>

#include "Common/RTTI.h"
#include "Math/Vector2.h"
#include "Enumeration/Color.h"
#include "Enumeration/CollisionType.h"

namespace Nahoo
{
	class C_LEVEL;
	class COMP_HITCOMPONENT;
	class COMP_RENDER;

	class NAHOO_API C_ACTOR : public C_RTTI
	{
		RTTI_DECLARATIONS(C_ACTOR, C_RTTI)

	public:
		C_ACTOR();
		// 2차원 이미지로 받기 위해 파라미터 수정 --> 필요없이 1차원 배열을 2차원 배열처럼 쓰자
		C_ACTOR(const char* fileName, const  C_VECTOR2& position, bool collision);
		virtual ~C_ACTOR();

	public:
		// 생성자 이후에 초기화 하고싶은 내용 있으면 beginPlay에 넣기
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw(bool debugHitCompDraw = false);

		virtual void OnHit(const C_ACTOR* otherActor);

		virtual void Destroy();
		virtual void OnDestroy();
		
		// setter
		void SetPosition(const C_VECTOR2& newPosition);
		void SetActive(bool isActive);
		void SetCollision(bool activeCollision);
		inline void SetOwner(C_LEVEL* level) { m_owner = level; }

		void SetActorWidthHeight(int width, int height);

		// getter
		inline C_VECTOR2 GetPosition() const { return m_position; }
		inline C_LEVEL* GetOwner() { return m_owner; }
		inline COMP_HITCOMPONENT* GetHitComponent() const{ return m_hitComponent; }
		inline bool HasBegunPlay() const { return m_hasBegunPlay; }
		inline bool IsActive() const { return m_isActive && !m_destroyRequested; }
		inline bool DestroyRequested() const { return m_destroyRequested; }
		inline int GetSortingOrder() const { return m_sortingOrder; }
		inline const std::string& GetFilePath() const { return m_filePath; }
		inline E_COLOR GetColor() const { return m_color; }
		inline int GetActorWidth() const { return m_width; }
		inline int GetActorHeight() const { return m_height; }

	protected:
		bool m_hasBegunPlay{ false };
		bool m_isActive{ true };
		bool m_destroyRequested{ false };
		
		int m_sortingOrder{};
		int m_width{};
		int m_height{};

		std::string m_filePath{};

		C_LEVEL* m_owner{};
		C_VECTOR2 m_position = C_VECTOR2::Zero;
		E_COLOR m_color = E_COLOR::White;
		E_COLLISIONTYPE m_collisionType = E_COLLISIONTYPE::None;
		
		COMP_HITCOMPONENT* m_hitComponent{};
		COMP_RENDER* m_renderComponent{};

	private:
		void MakeComponent(bool collisionFlag);
	};

}
