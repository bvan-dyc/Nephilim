#pragma once

using FNepUpdateEventTypeID = uint64;

namespace FNepUpdateEventTypeIDHelper
{
	template<typename T>
	static FNepUpdateEventTypeID GetUpdateEventTypeID()
	{
		return typeid(T).hash_code();
	}
}
