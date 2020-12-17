#ifndef GUARD_DEBUG_H
#define GUARD_DEBUG_H
#if DEBUG
extern bool8 DisableMovementCheck;
extern bool8 EnableBattleDebug;
extern const u8 GitHash[];

void OpenLumaDebugMenu();
void OpenStartDebugMenu();
void Debug_ShowMainMenu(void);
#endif
#endif
