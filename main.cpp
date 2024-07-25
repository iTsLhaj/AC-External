#include "utils/memory.h"
#include <iostream>


namespace offsets {

	constexpr auto i_localPlayer = 0x0017E0A8; // 0017E254
	constexpr auto i_health = 0XEC;
	constexpr auto i_ammo = 0x140;

}

int main() {

	Memory CE{ "ac_client.exe" };
	
	const auto ModuleBaseAddress = CE.GetModuleBaseAddress("ac_client.exe");

	
	const auto LocalPlayerBaseAddress = CE.ProcMemRead<std::uintptr_t>(
		ModuleBaseAddress + offsets::i_localPlayer);
	const auto HealthBaseAddress = LocalPlayerBaseAddress + offsets::i_health;
	const auto AmmoBaseAddress = LocalPlayerBaseAddress + offsets::i_ammo;

	while (true)
	{
		CE.ProcMemWrite(
			HealthBaseAddress,
			1000
		);
		CE.ProcMemWrite(
			AmmoBaseAddress,
			42
		);
	}

}