#pragma once
#include <vector>

#include "Component/Component.h"
#include "Math/Vector2.h"

namespace Nahoo
{
	class  NAHOO_API COMP_RENDER : public COMP_COMPONENT
	{
		RTTI_DECLARATIONS(COMP_RENDER, COMP_COMPONENT)
	public:

		COMP_RENDER() = default;
		~COMP_RENDER() = default;

		COMP_RENDER(const COMP_RENDER&) = delete;
		const COMP_RENDER& operator=(const COMP_RENDER&) = delete;

		void BeginPlay() override;
		void Destroy() override;
		
		void Draw();

		bool SetRenderInfo(const std::string& filePath, E_COLOR color, int sortingOrder);
		void SetActive(bool isActive);

		bool IsActive() const;


	private:
		bool m_isActive{ false };

		E_COLOR m_color = E_COLOR::White;
		int m_sortingOrder{};
		std::string m_fileName{};
		
		int m_width{};
		int m_height{};
		std::vector<char>* m_sprite{};




	};

}
