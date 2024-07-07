// Ats.cpp : DLL アプリケーション用のエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "atsplugin.h"
#include "hoan_brake.h"
#include <stdio.h>
#include <cmath>

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{

    return TRUE;
}

ATS_API int WINAPI GetPluginVersion()
{
	return ATS_VERSION;
}

ATS_API void WINAPI SetVehicleSpec(ATS_VEHICLESPEC vehicleSpec)
{
	g_svcBrake = vehicleSpec.BrakeNotches;
	g_emgBrake = g_svcBrake + 1;
}

ATS_API void WINAPI Initialize(int brake)
{
	g_speed = 0;
}

ATS_API ATS_HANDLES WINAPI Elapse(ATS_VEHICLESTATE vehicleState, int *panel, int *sound)
{
	g_speed = vehicleState.Speed;
	g_output.Brake = g_brakeNotch;
	g_output.Power = g_powerNotch;
	if (g_pilotlamp)
	{
		g_output.Reverser = g_reverser;
	}
	else
	{
		g_output.Reverser = 0;
	}
	// 保安ブレーキ
	if (GetKeyState(0x10) & 0x8000 && key_2) {
		safty_Brake_key = true;
	}
	else {
		safty_Brake_key = false;
	}
	if (safty_Brake_key && (!(safty_Brake_key_old))) {
		if (safty_Brake) {
			safty_Brake = false;
			remission_sound = true;
		}
		else {
			safty_Brake = true;
			incoming_sound = true;
		}
	}
	if (safty_Brake) {
		g_output.Brake = 7;
		if (g_reverser == 0 || g_brakeNotch == g_emgBrake) {
			g_output.Reverser = 0;
		}
		else {
			g_output.Reverser = g_reverser;
		}
		panel[37] = 1;
	}
	else {
		panel[37] = 0;
	}
	trysetsound(&sound[31], &incoming_sound);
	trysetsound(&sound[32], &remission_sound);
	safty_Brake_key_old = safty_Brake_key;
    return g_output;
}

ATS_API void WINAPI SetPower(int notch)
{
	g_powerNotch = notch;
}

ATS_API void WINAPI SetBrake(int notch)
{
	g_brakeNotch = notch;
}

ATS_API void WINAPI SetReverser(int pos)
{
	g_reverser = pos;
}

ATS_API void WINAPI KeyDown(int atsKeyCode)
{
	switch (atsKeyCode)
	{
	case ATS_KEY_D:
		key_2 = true;
		break;
	}
}

ATS_API void WINAPI KeyUp(int hornType)
{
	switch (hornType)
	{
	case ATS_KEY_D:
		key_2 = false;
		break;
	}
}

ATS_API void WINAPI HornBlow(int atsHornBlowIndex)
{
}

ATS_API void WINAPI DoorOpen()
{
	g_pilotlamp = false;
}

ATS_API void WINAPI DoorClose()
{
	g_pilotlamp = true;
}

ATS_API void WINAPI SetSignal(int signal)
{
}

ATS_API void WINAPI SetBeaconData(ATS_BEACONDATA beaconData)
{
}

ATS_API void WINAPI Load() 
{
}

ATS_API void WINAPI Dispose() 
{
}

void trysetsound(int* pSoundIndex, bool* motion) {
	if (*motion) {
		*pSoundIndex = ATS_SOUND_PLAY;
		*motion = false;
	}
	else {
		*pSoundIndex = ATS_SOUND_CONTINUE;
	}
}
