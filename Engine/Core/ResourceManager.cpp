#include <filesystem>

#include "ResourceManager.h"

Nahoo::C_RESOURCEMANAGER* Nahoo::C_RESOURCEMANAGER::m_instance = nullptr;

Nahoo::C_RESOURCEMANAGER::C_RESOURCEMANAGER()
{
	m_instance = this;
}

Nahoo::C_RESOURCEMANAGER::~C_RESOURCEMANAGER()
{
}

void Nahoo::C_RESOURCEMANAGER::Initialize()
{
	GetTextFiles("../Assets/");
	
	if (m_fileNames.empty() == false)
	{
		ExtractFileData();
	}
}
Nahoo::C_RESOURCEMANAGER& Nahoo::C_RESOURCEMANAGER::GetInstance()
{
	if (m_instance == nullptr)
	{
		__debugbreak();
	}
	
	return *m_instance;
}

bool Nahoo::C_RESOURCEMANAGER::GetData(const std::string& filePath, std::vector<char>& outSprite, int& outWidth, int& outHeight)
{
	auto iter = m_resources.find(filePath);

	if (iter != m_resources.end())
	{
		outSprite = iter->second.m_sprite;
		outWidth = iter->second.m_width;
		outHeight = iter->second.m_height;
		return true;
	}
	else
	{
		return false;
	}

}

void Nahoo::C_RESOURCEMANAGER::GetTextFiles(const char* folderPath)
{
	
	for (const auto& entry : std::filesystem::directory_iterator(folderPath))
	{
		if (entry.is_regular_file() == true && entry.path().extension() == ".txt")
		{
			m_fileNames.push_back(entry.path().string());
		}
	}

}

void Nahoo::C_RESOURCEMANAGER::ExtractFileData()
{
	for (std::string fileName : m_fileNames)
	{
		S_SPRITEINFO spriteInfo{};

		FILE* file = nullptr;
		fopen_s(&file, fileName.c_str(), "rt");

		if (!file)
		{
			__debugbreak();
			return;
		}

		fseek(file, 0, SEEK_END);
		size_t fileSize = ftell(file);
		rewind(file);

		char* data = new char[fileSize + 1] {};
		fread(data, sizeof(char), fileSize, file);

		char* context{};
		char* token{};

		spriteInfo.m_sprite.reserve(fileSize);
		
		token = strtok_s(data, "\n", &context);
		spriteInfo.m_width = static_cast<int>(strlen(token));

		while (token)
		{
			spriteInfo.m_height++;
			for (int i = 0; i < spriteInfo.m_width; i++)
			{
				spriteInfo.m_sprite.emplace_back(token[i]);
			}
			token = strtok_s(nullptr, "\n", &context);
		}
		delete[] data;
		data = nullptr;

		fclose(file);
		m_resources.insert({ fileName,spriteInfo});
	}


}
