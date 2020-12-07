#ifdef DEBUG
#include "global.h"
#include "debug.h"
#include "main.h"
#include "menu.h"
#include "list_menu.h"
#include "map_name_popup.h"
#include "script.h"

bool8 DisableMovementCheck;
bool8 EnableBattleDebug;

// #include "data/git.h"

// Start Menu Debug
static const u8 Str_Battle[] = _("Battle");
static const u8 Str_SoundTest[] = _("Sound Test");
static const u8 Str_DebugStart[] = _("Debug Start");
static const u8 Str_WipeSave[] = _("Wipe backup data");
static const u8 Str_EReaderTest[] = _("E-Reader test");
static const u8 Str_EReaderTest2[] = _("E-Reader emu");
static const u8 Str_RTCReset[] = _("RTC Reset");
static const u8 Str_BerryFix[] = _("Berry Program Update");
static const u8 Str_Back[] = _("Back");

// Field Menu Debug

// Main functions
static const u8 Str_AddPKMN[] = _("Add {PKMN}");
static const u8 Str_EditPKMN[] = _("Edit {PKMN}");
static const u8 Str_AddItems[] = _("Add items");
static const u8 Str_EditMoney[] = _("Edit ¥");
static const u8 Str_EditCoins[] = _("Edit Coin Case");
static const u8 Str_EditPokedex[] = _("Edit {55}{56}Dex");
static const u8 Str_EditRTC[] = _("Edit RTC");

// GFX
static const u8 Str_MonGFX[] = _("{PKMN} GFX");
static const u8 Str_TrainerGFX[] = _("Trainer GFX");
static const u8 Str_ItemGFX[] = _("Item GFX");
static const u8 Str_DecorGFX[] = _("Decor GFX");
static const u8 Str_OverworldGFX[] = _("OW GFX");
static const u8 Str_FontGFX[] = _("Fonts");

// Save file
static const u8 Str_FlagEdit[] = _("Flag edit");
static const u8 Str_VarEdit[] = _("Var edit");
static const u8 Str_StatEdit[] = _("Stat edit");
static const u8 Str_NameEdit[] = _("Name edit");
static const u8 Str_GenderEdit[] = _("Gender edit");
static const u8 Str_BaseEdit[] = _("Secret Base edit");
static const u8 Str_ECardEdit[] = _("E-Card Trainer edit");
static const u8 Str_BerryEdit[] = _("Berry edit");
static const u8 Str_PokeblockEdit[] = _("{POKEBLOCK} edit");
static const u8 Str_TVEdit[] = _("TV edit");
static const u8 Str_SwarmEdit[] = _("Swarm edit");
static const u8 Str_MailEdit[] = _("Mailbox edit");
static const u8 Str_TrendEdit[] = _("Trend edit");
static const u8 Str_ContestWinnerEdit[] = _("Contest winners");
static const u8 Str_BattleTowerEdit[] = _("Battle Tower");
static const u8 Str_RoamerEdit[] = _("Roaming {PKMN}");
static const u8 Str_EnigmaEdit[] = _("Enigma Berry");
static const u8 Str_PlayTimeEdit[] = _("Play Time");
static const u8 Str_OptionEdit[] = _("Options");
static const u8 Str_HoFEdit[] = _("Hall of Fame");
static const u8 Str_KeyEdit[] = _("XOR Key");
static const u8 Str_NavEdit[] = _("{55}{56}Nav");
static const u8 Str_BerryCrushEdit[] = _("Berry Crush");
static const u8 Str_MysteryGiftEdit[] = _("Mystery Gift");

// Utils
static const u8 Str_DebugBattle[] = _("Debug battle");
static const u8 Str_DebugContest[] = _("Debug Contest");
static const u8 Str_DebugBattle2[] = _("Debug Battle Tent");
static const u8 Str_DebugGiddy[] = _("Giddy");
static const u8 Str_DebugTrickHouse[] = _("Trick House");
static const u8 Str_DebugWalda[] = _("Walda");
static const u8 Str_DebugWarp[] = _("Warp");
static const u8 Str_DebugMemoryEditor[] = _("Memory Editor");
static const u8 Str_DebugTownMap[] = _("View Town Map");
static const u8 Str_DebugAllBadges[] = _("All badges");
static const u8 Str_DebugClearBadges[] = _("Clear badges");
static const u8 Str_DebugAllLandmarks[] = _("Landmarks visited");
static const u8 Str_DebugClearLandmarks[] = _("Landmarks clear");
static const u8 Str_DebugCredits[] = _("Jump to credits");
static const u8 Str_DebugHoF[] = _("Jump to HoF");
static const u8 Str_DebugSafariFeeders[] = _("Safari Feeders");
static const u8 Str_DebugScreen[] = _("Screen");

// Pokedex
static const u8 Str_NationalDex[] = _("National Dex: ");
static const u8 Str_NationalDexAllSeen[] = _("All seen (National)");
static const u8 Str_NationalDexAllCaught[] = _("All caught (National)");
static const u8 Str_RegionalDexAllSeen[] = _("All seen (Regional)");
static const u8 Str_RegionalDexAllCaught[] = _("All caught (Regional)");
static const u8 Str_NationalDexClearSeen[] = _("Clear seen (National)");
static const u8 Str_NationalDexClearCaught[] = _("Clear caught (National)");
static const u8 Str_RegionalDexClearSeen[] = _("Clear seen (Regional)");
static const u8 Str_RegionalDexClearCaught[] = _("Clear caught (Regional)");

// In game functions
static const u8 Str_Weather[] = _("Weather flag: ");
static const u8 Str_Safari[] = _("Safari: ");
static const u8 Str_SafariBalls[] = _("  Safari Balls: ");
static const u8 Str_SafariSteps[] = _("  Safari Steps: ");
static const u8 Str_Encounters[] = _("Wild encounters: ");
static const u8 Str_WeatherField[] = _("Field weather: ");
static const u8 Str_Music[] = _("Music: ");
static const u8 Str_Music2[] = _("Field music: ");
static const u8 Str_TrainerEncounters[] = _("Trainer encounters: ");
static const u8 Str_Nameplates[] = _("Show nameplates: ");
static const u8 Str_Music3[] = _("BGM Transitions: ");
static const u8 Str_RepelSteps[] = _("Repel Steps: ");
static const u8 Str_SaveStatus[] = _("Save Status: ");
static const u8 Str_MirageIsland[] = _("Mirage Island: ");
static const u8 Str_Lottery[] = _("Lottery: ");

// Data
static const u8 Str_MonData[] = _("{PKMN}");
static const u8 Str_TrainerData[] = _("Trainers");
static const u8 Str_MoveData[] = _("Moves");
static const u8 Str_ItemData[] = _("Items");
static const u8 Str_ContestOpponentData[] = _("Contest Opponents");
static const u8 Str_TowerOpponentData[] = _("Battle Tower Opponents");
static const u8 Str_AbilityData[] = _("Abilities");
static const u8 Str_MapData[] = _("Maps");
static const u8 Str_LocationData[] = _("Locations");
static const u8 Str_BerryData[] = _("Berries");
static const u8 Str_EncounterData[] = _("Encounters");
static const u8 Str_DecorData[] = _("Decorations");

// Groups
static const u8 Str_InGameGroup[] = _("{COLOR BLUE}In game flags");
static const u8 Str_SaveFileGroup[] = _("{COLOR BLUE}Save file utils");
static const u8 Str_GFXGroup[] = _("{COLOR BLUE}GFX");
static const u8 Str_DataGroup[] = _("{COLOR BLUE}ROM Data View");
static const u8 Str_DexGroup[] = _("{COLOR BLUE}{55}{56}Dex");
static const u8 Str_FunctionsGroup[] = _("{COLOR BLUE}Functions");
static const u8 Str_CommonGroup[] = _("{COLOR BLUE}Common");
static const u8 Str_Cancel[] = _("Cancel");

static void LumaDebugMenu_HandleInput(u8);
static void LumaDebugMenu_Close(u8);
static void LumaDebugMenu_Cancel(u8);

static const struct ListMenuItem LumaDebugMenu_Items[] = {
	{Str_Cancel, 0},
};

static void(*const LumaDebugMenu_Actions[])(u8) = {
	LumaDebugMenu_Cancel,
};

static const struct ListMenuTemplate LumaDebugMenu_ListTemplate = {
	.items = LumaDebugMenu_Items,
	.totalItems = ARRAY_COUNT(LumaDebugMenu_Items),
	.maxShowed = 7,
	.windowId = 0,
	.header_X = 0,
	.item_X = 8,
	.cursor_X = 0,
	.upText_Y = 1,
	.cursorPal = 2,
	.fillValue = 1,
	.cursorShadowPal = 3,
	.lettersSpacing = 1,
	.itemVerticalPadding = 0,
	.fontId = 1,
	.cursorKind = 0,
	.scrollMultiple = LIST_MULTIPLE_SCROLL_DPAD
};

static const struct WindowTemplate LumaDebugMenu_WindowTemplate = {
	.bg = 0,
	.tilemapLeft = 1,
	.tilemapTop = 1,
	.width = 11,
	.height = 14,
	.baseBlock = 1,
	.paletteNum = 15
};

void OpenLumaDebugMenu() {
	struct ListMenuTemplate menuTemplate;
	struct Task* inputTask;
	u8 winId;
	u8 menuTaskID;
	u8 inputTaskID;

	HideMapNamePopUpWindow();
	LoadMessageBoxAndBorderGfx();
	winId = AddWindow(&LumaDebugMenu_WindowTemplate);
	DrawStdWindowFrame(winId, FALSE);

	menuTemplate = LumaDebugMenu_ListTemplate;
	menuTemplate.windowId = winId;
	menuTaskID = ListMenuInit(&menuTemplate, 0, 0);

	CopyWindowToVram(winId, 3);
	inputTaskID = CreateTask(LumaDebugMenu_HandleInput, 3);
	inputTask = &(gTasks[inputTaskID]);
	inputTask->data[0] = menuTaskID;
	inputTask->data[1] = winId;
}

static void LumaDebugMenu_HandleInput(u8 taskid) {
	void (*func)(u8);
	struct Task* task = &(gTasks[taskid]);
	u32 input = ListMenu_ProcessInput(task->data[0]);

	if (gMain.newKeys & A_BUTTON) {
		PlaySE(SE_SELECT);
		if (LumaDebugMenu_Actions[input] != NULL) {
			func = LumaDebugMenu_Actions[input];
			func(taskid);
		}
	}
	else if (gMain.newKeys & B_BUTTON) {
		PlaySE(SE_SELECT);
		LumaDebugMenu_Close(taskid);
	}
}

static void LumaDebugMenu_Close(u8 taskid) {
	struct Task* task = &(gTasks[taskid]);
	DestroyListMenuTask(task->data[0], NULL, NULL);
	ClearStdWindowAndFrame(task->data[1], TRUE);
	RemoveWindow(task->data[1]);
	DestroyTask(taskid);
	EnableBothScriptContexts();
}

static void LumaDebugMenu_Cancel(u8 taskid) {
	LumaDebugMenu_Close(taskid);
}

#endif
