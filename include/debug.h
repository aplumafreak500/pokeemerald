#ifndef GUARD_DEBUG_H
#define GUARD_DEBUG_H
#if DEBUG
extern bool8 DisableMovementCheck;
extern bool8 EnableBattleDebug;

void OpenLumaDebugMenu();
void OpenStartDebugMenu();
void Debug_ShowMainMenu();
void FillScreen(u16);
#else
#define FillScreen(color)
#endif
extern const char BuildDateTime[];
extern const char GitHash[];
#endif
