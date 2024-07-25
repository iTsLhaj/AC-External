#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <Windows.h>
#include <TlHelp32.h>
#include <string_view>


class Memory
{

private:

	uintptr_t process_id = 0;
	void* process_handle = nullptr;

public:

	Memory(const std::string_view processName) noexcept ;
	~Memory();

	const std::uintptr_t GetModuleBaseAddress(const std::string_view moduleName) const noexcept ;
 
	template <typename T>
	constexpr void ProcMemWrite(const std::uintptr_t& address, const T& value) const noexcept
	{

		::WriteProcessMemory(
			process_handle,
			reinterpret_cast<void*>(address),
			&value,
			sizeof(T),
			NULL
		);

	}

	template <typename T>
	constexpr const T ProcMemRead(const std::uintptr_t& address) const noexcept
	{

		T value = { };
		::ReadProcessMemory(
			process_handle,
			reinterpret_cast<const void*>(address),
			&value,
			sizeof(T),
			NULL
		);

		return value;

	}

};


#endif