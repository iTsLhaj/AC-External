#include "memory.h"


Memory::Memory(const std::string_view processName) noexcept
{

	::PROCESSENTRY32 entry = { };
	entry.dwSize = sizeof(::PROCESSENTRY32);

	const auto processSnapshot = CreateToolhelp32Snapshot(
		TH32CS_SNAPPROCESS, 0
	);

	do {

		if (!processName.compare(entry.szExeFile)) {
			process_id = entry.th32ProcessID;
			process_handle = OpenProcess(
				PROCESS_ALL_ACCESS,
				FALSE,
				process_id
			);
			break;
		}

	} while (::Process32Next(processSnapshot, &entry));

	if (processSnapshot)
		CloseHandle(processSnapshot);

}

Memory::~Memory()
{

	if (process_handle)
		CloseHandle(process_handle);

}

const std::uintptr_t Memory::GetModuleBaseAddress(const std::string_view moduleName) const noexcept
{

	::MODULEENTRY32 entry = { };
	entry.dwSize = sizeof(::MODULEENTRY32);

	const auto moduleSnapshot = CreateToolhelp32Snapshot(
		TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32,
		process_id
	);

	std::uintptr_t moduleBaseAddress = 0;

	do {

		if (!moduleName.compare(entry.szModule)) {
			moduleBaseAddress = reinterpret_cast<uintptr_t>(entry.modBaseAddr);
			break;
		}

	} while (::Module32Next(moduleSnapshot, &entry));

	return moduleBaseAddress;

}
