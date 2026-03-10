#pragma once

#include <vector>
#include <string>

#include "Common/Common.h"
#include "Math/Vector2.h"
#include "Enumeration/Color.h"

namespace Nahoo
{
	class C_EFFECT;
	//class C_LEVEL;

	class NAHOO_API C_EFFECTMANAGER
	{
	public:
		C_EFFECTMANAGER();
		~C_EFFECTMANAGER();

		C_EFFECTMANAGER(const C_EFFECTMANAGER&) = delete;
		const C_EFFECTMANAGER& operator=(const C_EFFECTMANAGER&) = delete;

		// Todo: 임시로 Effect Type을 int로 설정.
		// 0: 총알 파괴 이펙트, 1: 비행기 파괴 이펙트, 2: 총 강화 아이템 이펙트, 3: special attack 아이템 effect
		// Enum이나 다른 구별 가능한 것으로 데이터에서 effect 종류 별 필요한 sprite file names를 불러오는 것 해야함
		void SpawnEffect(int effectType, const C_VECTOR2& position, float frameDuration, E_COLOR color, int sortingOrder);
		void Tick(float deltaTime);
		void Draw();

		// setter
		//inline void SetOwner(C_LEVEL* owner) { m_owner = owner; }

	private:

		// Check: Effect 종류 별 출력을 위한 임시 함수. 나중에 데이터에서 종류 별 파일 이름 불러오는 것 구현해야함
		void SetFileNameBulletDestroy(std::vector<std::string>& outFileNames);
		void SetFileNamePlaneDestroy(std::vector<std::string>& outFileNames);
		void SetFileNamePowerItem(std::vector<std::string>& outFileNames);
		void SetFileNameSpecialAttackItem(std::vector<std::string>& outFileNames);


	private:
		//C_LEVEL* m_owner{};
		std::vector<C_EFFECT*> m_effectPool{};




	};






}
