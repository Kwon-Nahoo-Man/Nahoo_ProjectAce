#pragma once

#include "Common/Common.h"
#include <unordered_map>
#include <vector>
#include <string>

namespace Nahoo
{
	class C_RESOURCEMANAGER
	{
		struct S_SPRITEINFO
		{
			std::vector<char> m_sprite{};
			int m_width{};
			int m_height{};

		};

	public:
		C_RESOURCEMANAGER();
		~C_RESOURCEMANAGER();


		C_RESOURCEMANAGER(const C_RESOURCEMANAGER&) = delete;
		const C_RESOURCEMANAGER& operator=(const C_RESOURCEMANAGER&) = delete;

		static C_RESOURCEMANAGER& GetInstance();

		void Initialize();
		bool GetData(const std::string& filePath, std::vector<char>*& outSprite, int& outWidth, int& outHeight);

	private:
		void GetTextFiles(const char* folderPath);
		void ExtractFileData();


	private:

		static C_RESOURCEMANAGER* m_instance;
		std::vector<std::string> m_fileNames;
		std::unordered_map<std::string, S_SPRITEINFO> m_resources{};

	};





}
