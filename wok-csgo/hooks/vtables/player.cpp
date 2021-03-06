#include "../hooks.h"

qangle_t* __fastcall hooks::player::eye_angles::fn(c_cs_player* ecx, void* edx) {
	static const auto original = m_player->get_original<T>(index);
	if (ecx != g::local)
		return original(ecx);

	static const auto return_to_anim_state_yaw = SIG("client.dll", "F3 0F 10 55 ? 51 8B 8E ? ? ? ?").get();
	static const auto return_to_anim_state_pitch = SIG("client.dll", "8B CE F3 0F 10 00 8B 06 F3 0F 11 45 ? FF 90 ? ? ? ? F3 0F 10 55 ?").get();

	if (_ReturnAddress() == return_to_anim_state_yaw
		|| _ReturnAddress() == return_to_anim_state_pitch)
		return &g::angles::real;

	return original(ecx);
}