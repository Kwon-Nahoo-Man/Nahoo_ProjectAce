#pragma once
#include <vector>
#include <string>

#include "Util/Timer.h"
#include "Common/RTTI.h"
#include "Math/Vector2.h"
#include "Enumeration/Color.h"

namespace Nahoo
{
	class NAHOO_API C_EFFECT : public C_RTTI
	{
		RTTI_DECLARATIONS(C_EFFECT, C_RTTI)
	public:
		C_EFFECT() = default;
		~C_EFFECT() = default;

		C_EFFECT(const C_EFFECT&) = delete;
		const C_EFFECT& operator=(const C_EFFECT&) = delete;

		// getter
		bool IsActive() const { return m_isActive; }
		
		void InitializeEffect(std::vector<std::string>& fileNames, const C_VECTOR2& position, float frameDuration, E_COLOR color, int sortingOrder);
		virtual void Tick(float deltaTime);
		void Draw();
		void Disappear();

	
	private:
		bool UpdateSprite();


	private:

		bool m_isActive{ false };

		E_COLOR m_color = E_COLOR::White;
		int m_sortingOrder{};

		int m_currentIndex{};
		int m_maxIndex{};
		int m_width{};
		int m_height{};
		C_VECTOR2 m_position{};
		C_VECTOR2 m_positionOrigin{};

		std::vector<char>* m_sprite{};
		std::vector<std::string> m_fileNames{};

		UTIL::C_TIMER m_timer{};

	};




}
