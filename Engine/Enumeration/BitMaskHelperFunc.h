#pragma once
#include <type_traits>

namespace BitMask
{
	template<typename T>
	inline bool HasFlag(T originMask, T compareMask)
	{
		using U = std::underlying_type_t<T>;
		return (static_cast<U>(originMask) & static_cast<U>(compareMask)) != 0;

	}
}
