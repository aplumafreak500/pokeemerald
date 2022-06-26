#ifdef DEBUG
#include "global.h"
#include "m4a.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "debug.h"
#include "menu.h"
#include "palette.h"
#include "random.h"
#include "string_util.h"
#include "list_menu.h"
#include "map_name_popup.h"
#include "script.h"
#include "sound.h"
#include "item.h"
#include "item_icon.h"
#include "fieldmap.h"
#include "overworld.h"
#include "event_data.h"
#include "field_weather.h"
void PlayerPC(); // was not defined in player_pc.h
#include "hall_of_fame.h"
#include "credits.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "constants/abilities.h"
#include "constants/items.h"

extern void LumaDebugMenu_AddEditPKMN_Init(u8);

bool8 DisableMovementCheck;
bool8 EnableBattleDebug;

const char AsciiStr_Buildstamp[] = "$ Luma Debug Menu for pokeemerald v0.0a built " __TIME__ " " __DATE__ " $";

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
static const u8 Str_EditStorage[] = _("Edit Storage");
static const u8 Str_AddItems[] = _("Add items");
static const u8 Str_RemoveItems[] = _("Remove items");
static const u8 Str_EditMoney[] = _("Edit ¥");
static const u8 Str_EditCoins[] = _("Edit Coin Case");
static const u8 Str_EditPokedex[] = _("Edit {0x55}{0x56}Dex");
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
static const u8 Str_NavEdit[] = _("{0x55}{0x56}Nav");
static const u8 Str_BerryCrushEdit[] = _("Berry Crush");
static const u8 Str_MysteryGiftEdit[] = _("Mystery Gift");
static const u8 Str_QuickEditPKMN[] = _("Quick Edit {PKMN}");

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
static const u8 Str_DebugSaveFailTest[] = _("Save fail test");
static const u8 Str_DebugPC[] = _("Jump to Storage System");
static const u8 Str_DebugPlayerPC[] = _("Jump to {PLAYER}'s PC");
static const u8 Str_DebugTileInfo[] = _("Tile Info");
static const u8 Str_DebugFixChecksums[] = _("Fix {PKMN} Checksums");
static const u8 Str_DebugClearStorage[] = _("Clear Storage");
static const u8 Str_DebugFillStorage[] = _("Fill Storage");
static const u8 Str_DebugNickname[] = _("Nickname");
static const u8 Str_DebugEgg[] = _("Breed");
static const u8 Str_DebugHM[] = _("Use HM");
static const u8 Str_DebugRNG[] = _("RNG");
static const u8 Str_DebugXaman[] = _("Xaman Debug Menu");

// Pokédex
static const u8 Str_NationalDex[] = _("National Dex");
static const u8 Str_NationalDexAllSeen[] = _("All seen (National)");
static const u8 Str_NationalDexAllCaught[] = _("All caught (National)");
static const u8 Str_RegionalDexAllSeen[] = _("All seen (Regional)");
static const u8 Str_RegionalDexAllCaught[] = _("All caught (Regional)");
static const u8 Str_NationalDexClearSeen[] = _("Clear seen (National)");
static const u8 Str_NationalDexClearCaught[] = _("Clear caught (National)");
static const u8 Str_RegionalDexClearSeen[] = _("Clear seen (Regional)");
static const u8 Str_RegionalDexClearCaught[] = _("Clear caught (Regional)");

// In game functions
static const u8 Str_Weather[] = _("Weather flag");
static const u8 Str_Safari[] = _("Safari");
static const u8 Str_Encounters[] = _("Wild encounters");
static const u8 Str_WeatherField[] = _("Field weather");
static const u8 Str_Music[] = _("Music");
static const u8 Str_Music2[] = _("Field music");
static const u8 Str_TrainerEncounters[] = _("Trainer encounters");
static const u8 Str_Nameplates[] = _("Show nameplates");
static const u8 Str_Music3[] = _("BGM Transitions");
static const u8 Str_RepelSteps[] = _("Repel Steps");
static const u8 Str_SaveStatus[] = _("Save Status");
static const u8 Str_MirageIsland[] = _("Mirage Island");
static const u8 Str_Lottery[] = _("Lottery");
static const u8 Str_EditTrainerID[] = _("Trainer ID");

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
static const u8 Str_TradeData[] = _("Trades");

// Groups
static const u8 Str_InGameGroup[] = _("{COLOR BLUE}In game flags");
static const u8 Str_SaveFileGroup[] = _("{COLOR BLUE}Save file utils");
static const u8 Str_GFXGroup[] = _("{COLOR BLUE}GFX");
static const u8 Str_DataGroup[] = _("{COLOR BLUE}ROM Data View");
static const u8 Str_DexGroup[] = _("{COLOR BLUE}{0x55}{0x56}Dex");
static const u8 Str_FunctionsGroup[] = _("{COLOR BLUE}Functions");
static const u8 Str_CommonGroup[] = _("{COLOR BLUE}Common");
static const u8 Str_Cancel[] = _("Cancel");
static const u8 Str_Cancel2[] = _("{COLOR BLUE}Cancel");

static const u8 Str_On[] = _("On");
static const u8 Str_Off[] = _("Off");

static void LumaDebugMenu_HandleInput(u8);
static void LumaDebugMenu_Close(u8);
static void LumaDebugMenu_Cancel(u8);
static UNUSED void LumaDebugMenu_Nop(u8);
static void LumaDebugMenu_AddPKMN(u8);
static void LumaDebugMenu_EditPKMN(u8);
static void LumaDebugMenu_EditStorage(u8);
static void LumaDebugMenu_AddItems(u8);
static void LumaDebugMenu_RemoveItems(u8);
static void LumaDebugMenu_ViewTownMap(u8);
static void LumaDebugMenu_JumpToCredits(u8);
static void LumaDebugMenu_JumpToHoF(u8);
static void LumaDebugMenu_JumpToStorageSystem(u8);
static void LumaDebugMenu_JumpToPlayerPC(u8);
static void LumaDebugMenu_ClearStorage(u8);
static void LumaDebugMenu_FillStorage(u8);
static void LumaDebugMenu_OpenXaman(u8);
static void LumaDebugMenu_WeatherFlag(u8);
static void LumaDebugMenu_Encounters(u8);
static void LumaDebugMenu_Music(u8);
static void LumaDebugMenu_TrainerEncounters(u8);
static void LumaDebugMenu_Nameplates(u8);
static void LumaDebugMenu_BGMTransitions(u8);
static void LumaDebugMenu_NationalDex(u8);
static void LumaDebugMenu_FieldMusic(u8);
static void LumaDebugMenu_RepelSteps(u8);
static void LumaDebugMenu_SaveStatus(u8);
static void LumaDebugMenu_MirageIsland(u8);
static void LumaDebugMenu_Lottery(u8);
static void LumaDebugMenu_FieldWeather(u8);
static void LumaDebugMenu_RNG(u8);
static void LumaDebugMenu_AddItems_Init(u8);
static void LumaDebugMenu_AddItems_ProcessInput(u8);
static void LumaDebugMenu_AddItems_Redraw(u8);
//static void LumaDebugMenu_EditMoneyCoins_Init(u8);
//static void LumaDebugMenu_EditMoneyCoins_ProcessInput(u8);
//static void LumaDebugMenu_EditMoneyCoins_Redraw(u8);
static void LumaDebugMenu_EditSingleFlag(u8, u8);
static void LumaDebugMenu_EditSingleFlag_ProcessInput(u8);
static void LumaDebugMenu_EditSingleVar(u8, u8);
static void LumaDebugMenu_EditSingleVar_ProcessInput(u8);
static void LumaDebugMenu_OpenRNG();
static void LumaDebugMenu_RNG_ProcessInput(u8);
static void LumaDebugMenu_RNG_Redraw(u8);

enum {
	LUMA_ACTION_NONE = 0,
	LUMA_ACTION_CANCEL,
	LUMA_ACTION_ADD_PKMN,
	LUMA_ACTION_EDIT_PKMN,
	LUMA_ACTION_EDIT_STORAGE,
	LUMA_ACTION_ADD_ITEMS,
	LUMA_ACTION_REMOVE_ITEMS,
	LUMA_ACTION_EDIT_MONEY,
	LUMA_ACTION_EDIT_COINS,
	LUMA_ACTION_EDIT_DEX,
	LUMA_ACTION_EDIT_RTC,
	LUMA_ACTION_WEATHER_EVENTS,
	LUMA_ACTION_SAFARI,
	LUMA_ACTION_ENCOUNTERS,
	LUMA_ACTION_TRAINER_ENCOUNTERS,
	LUMA_ACTION_NAMEPLATES,
	LUMA_ACTION_BGM_TRANSITIONS,
	LUMA_ACTION_BGM,
	LUMA_ACTION_FIELD_BGM,
	LUMA_ACTION_WEATHER,
	LUMA_ACTION_REPEL,
	LUMA_ACTION_SAVE_STATUS,
	LUMA_ACTION_MIRAGE_ISLAND,
	LUMA_ACTION_LOTTERY,
	LUMA_ACTION_NATIONAL_DEX,
	LUMA_ACTION_RNG,
	LUMA_ACTION_XAMAN,
	LUMA_ACTION_TOWN_MAP,
	LUMA_ACTION_CREDITS,
	LUMA_ACTION_HOF,
	LUMA_ACTION_PC,
	LUMA_ACTION_PLAYER_PC,
	LUMA_ACTION_FILL_STORAGE,
	LUMA_ACTION_CLEAR_STORAGE,
};

static const struct ListMenuItem LumaDebugMenu_Items[] = {
	{Str_CommonGroup, LIST_HEADER},
	{Str_AddPKMN, LUMA_ACTION_ADD_PKMN},
	{Str_EditPKMN, LUMA_ACTION_EDIT_PKMN},
	{Str_EditStorage, LUMA_ACTION_EDIT_STORAGE},
	{Str_AddItems, LUMA_ACTION_ADD_ITEMS},
	{Str_EditMoney, 0},
	{Str_EditCoins, 0},
	{Str_EditPokedex, 0},
	{Str_EditRTC, 0},
	{Str_InGameGroup, LIST_HEADER},
	{Str_Weather, LUMA_ACTION_WEATHER_EVENTS},
	{Str_Safari, 0},
	{Str_Encounters, LUMA_ACTION_ENCOUNTERS},
	{Str_WeatherField, LUMA_ACTION_WEATHER},
	{Str_Music, LUMA_ACTION_BGM},
	{Str_Music2, LUMA_ACTION_FIELD_BGM},
	{Str_TrainerEncounters, LUMA_ACTION_TRAINER_ENCOUNTERS},
	{Str_Nameplates, LUMA_ACTION_NAMEPLATES},
	{Str_Music3, LUMA_ACTION_BGM_TRANSITIONS},
	{Str_RepelSteps, LUMA_ACTION_REPEL},
	{Str_SaveStatus, LUMA_ACTION_SAVE_STATUS},
	{Str_MirageIsland, LUMA_ACTION_MIRAGE_ISLAND},
	{Str_Lottery, LUMA_ACTION_LOTTERY},
	{Str_EditTrainerID, 0},
	{Str_SaveFileGroup, LIST_HEADER},
	{Str_FlagEdit, 0},
	{Str_VarEdit, 0},
	{Str_StatEdit, 0},
	{Str_NameEdit, 0},
	{Str_GenderEdit, 0},
	{Str_QuickEditPKMN, 0},
	{Str_BaseEdit, 0},
	{Str_ECardEdit, 0},
	{Str_BerryEdit, 0},
	{Str_PokeblockEdit, 0},
	{Str_TVEdit, 0},
	{Str_SwarmEdit, 0},
	{Str_MailEdit, 0},
	{Str_TrendEdit, 0},
	{Str_ContestWinnerEdit, 0},
	{Str_BattleTowerEdit, 0},
	{Str_RoamerEdit, 0},
	{Str_EnigmaEdit, 0},
	{Str_PlayTimeEdit, 0},
	{Str_OptionEdit, 0},
	{Str_HoFEdit, 0},
	{Str_KeyEdit, 0},
	{Str_NavEdit, 0},
	{Str_BerryCrushEdit, 0},
	{Str_MysteryGiftEdit, 0},
	{Str_FunctionsGroup, LIST_HEADER},
	{Str_DebugBattle, 0},
	{Str_DebugContest, 0},
	{Str_DebugBattle2, 0},
	{Str_DebugGiddy, 0},
	{Str_DebugTrickHouse, 0},
	{Str_DebugWalda, 0},
	{Str_DebugWarp, 0},
	{Str_DebugXaman, LUMA_ACTION_XAMAN},
	{Str_DebugMemoryEditor, 0},
	{Str_DebugTownMap, LUMA_ACTION_TOWN_MAP},
	{Str_DebugAllBadges, 0},
	{Str_DebugClearBadges, 0},
	{Str_DebugAllLandmarks, 0},
	{Str_DebugClearLandmarks, 0},
	{Str_DebugCredits, LUMA_ACTION_CREDITS},
	{Str_DebugHoF, LUMA_ACTION_HOF},
	{Str_DebugSafariFeeders, 0},
	{Str_DebugScreen, 0},
	{Str_DebugSaveFailTest, 0},
	{Str_DebugPC, LUMA_ACTION_PC},
	{gStringVar1, LUMA_ACTION_PLAYER_PC}, /* Player's PC */
	{Str_DebugTileInfo, 0},
	{Str_DebugFixChecksums, 0},
	{Str_DebugClearStorage, LUMA_ACTION_CLEAR_STORAGE},
	{Str_DebugFillStorage, LUMA_ACTION_FILL_STORAGE},
	{Str_DebugNickname, 0},
	{Str_RemoveItems, LUMA_ACTION_REMOVE_ITEMS},
	{Str_DebugEgg, 0},
	{Str_DebugHM, 0},
	{Str_DebugRNG, 0/*LUMA_ACTION_RNG*/},
	{Str_DataGroup, LIST_HEADER},
	{Str_MonData, 0},
	{Str_TrainerData, 0},
	{Str_MoveData, 0},
	{Str_ItemData, 0},
	{Str_ContestOpponentData, 0},
	{Str_TowerOpponentData, 0},
	{Str_AbilityData, 0},
	{Str_MapData, 0},
	{Str_LocationData, 0},
	{Str_BerryData, 0},
	{Str_EncounterData, 0},
	{Str_DecorData, 0},
	{Str_TradeData, 0},
	{Str_GFXGroup, LIST_HEADER},
	{Str_MonGFX, 0},
	{Str_TrainerGFX, 0},
	{Str_ItemGFX, 0},
	{Str_DecorGFX, 0},
	{Str_OverworldGFX, 0},
	{Str_FontGFX, 0},
	{Str_DexGroup, LIST_HEADER},
	{Str_NationalDex, LUMA_ACTION_NATIONAL_DEX},
	{Str_NationalDexAllSeen, 0},
	{Str_NationalDexClearSeen, 0},
	{Str_RegionalDexAllSeen, 0},
	{Str_RegionalDexClearSeen, 0},
	{Str_NationalDexAllCaught, 0},
	{Str_NationalDexClearCaught, 0},
	{Str_RegionalDexAllCaught, 0},
	{Str_RegionalDexClearCaught, 0},
	{Str_Cancel2, LIST_HEADER},
	{Str_Cancel, LUMA_ACTION_CANCEL},
};

static void(*const LumaDebugMenu_Actions[])(u8) = {
	[LUMA_ACTION_NONE] = NULL,
	[LUMA_ACTION_CANCEL] = LumaDebugMenu_Cancel,
	[LUMA_ACTION_ADD_PKMN] = LumaDebugMenu_AddPKMN,
	[LUMA_ACTION_EDIT_PKMN] = LumaDebugMenu_EditPKMN,
	[LUMA_ACTION_EDIT_STORAGE] = LumaDebugMenu_EditStorage,
	[LUMA_ACTION_ADD_ITEMS] = LumaDebugMenu_AddItems,
	[LUMA_ACTION_REMOVE_ITEMS] = LumaDebugMenu_RemoveItems,
	[LUMA_ACTION_WEATHER_EVENTS] = LumaDebugMenu_WeatherFlag,
	[LUMA_ACTION_ENCOUNTERS] = LumaDebugMenu_Encounters,
	[LUMA_ACTION_TRAINER_ENCOUNTERS] = LumaDebugMenu_TrainerEncounters,
	[LUMA_ACTION_NAMEPLATES] = LumaDebugMenu_Nameplates,
	[LUMA_ACTION_BGM_TRANSITIONS] = LumaDebugMenu_BGMTransitions,
	[LUMA_ACTION_BGM] = LumaDebugMenu_Music,
	[LUMA_ACTION_FIELD_BGM] = LumaDebugMenu_FieldMusic,
	[LUMA_ACTION_WEATHER] = LumaDebugMenu_FieldWeather,
	[LUMA_ACTION_REPEL] = LumaDebugMenu_RepelSteps,
	[LUMA_ACTION_SAVE_STATUS] = LumaDebugMenu_SaveStatus,
	[LUMA_ACTION_MIRAGE_ISLAND] = LumaDebugMenu_MirageIsland,
	[LUMA_ACTION_LOTTERY] = LumaDebugMenu_Lottery,
	[LUMA_ACTION_NATIONAL_DEX] = LumaDebugMenu_NationalDex,
	[LUMA_ACTION_RNG] = LumaDebugMenu_RNG,
	[LUMA_ACTION_XAMAN] = LumaDebugMenu_OpenXaman,
	[LUMA_ACTION_TOWN_MAP] = LumaDebugMenu_ViewTownMap,
	[LUMA_ACTION_CREDITS] = LumaDebugMenu_JumpToCredits,
	[LUMA_ACTION_HOF] = LumaDebugMenu_JumpToHoF,
	[LUMA_ACTION_PC] = LumaDebugMenu_JumpToStorageSystem,
	[LUMA_ACTION_PLAYER_PC] = LumaDebugMenu_JumpToPlayerPC,
	[LUMA_ACTION_CLEAR_STORAGE] = LumaDebugMenu_ClearStorage,
	[LUMA_ACTION_FILL_STORAGE] = LumaDebugMenu_FillStorage,
};

static const struct ListMenuTemplate LumaDebugMenu_ListTemplate = {
	.items = LumaDebugMenu_Items,
	.totalItems = ARRAY_COUNT(LumaDebugMenu_Items),
	.maxShowed = 9,
	.windowId = 0,
	.header_X = 8,
	.item_X = 12,
	.cursor_X = 0,
	.upText_Y = 1,
	.cursorPal = 2,
	.fillValue = 1,
	.cursorShadowPal = 3,
	.lettersSpacing = 1,
	.itemVerticalPadding = 0,
	.fontId = 1,
	.cursorKind = 0,
	.scrollMultiple = LIST_NO_MULTIPLE_SCROLL,
	.moveCursorFunc = ListMenuDefaultCursorMoveFunc
};

static const struct WindowTemplate LumaDebugMenu_WindowTemplate = {
	.bg = 0,
	.tilemapLeft = 1,
	.tilemapTop = 1,
	.width = 20,
	.height = 18,
	.baseBlock = 1,
	.paletteNum = 15
};

static u16 menupos;
static u16 scrolloffset;

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

	StringExpandPlaceholders(gStringVar1, Str_DebugPlayerPC);

	if (menupos == 0)
		menupos = 1; // Skip the first header option

	menuTaskID = ListMenuInit(&menuTemplate, scrolloffset, menupos);

	CopyWindowToVram(winId, 3);
	inputTaskID = CreateTask(LumaDebugMenu_HandleInput, 3);
	inputTask = &gTasks[inputTaskID];
	inputTask->data[0] = menuTaskID;
	inputTask->data[1] = winId;
}

static void LumaDebugMenu_HandleInput(u8 taskid) {
	void (*func)(u8);
	struct Task* task = &gTasks[taskid];
	u32 input;

	input = ListMenu_ProcessInput(task->data[0]);

	ListMenuGetScrollAndRow(task->data[0], &scrolloffset, &menupos);

	switch (input) {
	default:
		if (gMain.newKeys & A_BUTTON) {
			if (LumaDebugMenu_Actions[input] != NULL) {
				PlaySE(SE_SELECT);
				func = LumaDebugMenu_Actions[input];
				func(taskid);
			}

		}
		else if (gMain.newKeys & B_BUTTON) {
			PlaySE(SE_SELECT);
			LumaDebugMenu_Cancel(taskid);
		}
		break;
	}

}

static void LumaDebugMenu_Close(u8 taskid) {
	struct Task* task = &gTasks[taskid];
	DestroyListMenuTask(task->data[0], NULL, NULL);
	ClearStdWindowAndFrame(task->data[1], TRUE);
	RemoveWindow(task->data[1]);
	DestroyTask(taskid);
}

static void LumaDebugMenu_Cancel(u8 taskid) {
	LumaDebugMenu_Close(taskid);
	EnableBothScriptContexts();
}

static void LumaDebugMenu_Nop(UNUSED u8 taskid) {
}

static void LumaDebugMenu_AddPKMN(u8 taskid) {
	LumaDebugMenu_Close(taskid);
	LumaDebugMenu_AddEditPKMN_Init(0);
}

static void LumaDebugMenu_EditPKMN(u8 taskid) {
	LumaDebugMenu_Close(taskid);
	LumaDebugMenu_AddEditPKMN_Init(1);
}

static void LumaDebugMenu_EditStorage(u8 taskid) {
	LumaDebugMenu_Close(taskid);
	LumaDebugMenu_AddEditPKMN_Init(2);
}

static void LumaDebugMenu_AddItems(u8 taskid) {
	LumaDebugMenu_Close(taskid);
	LumaDebugMenu_AddItems_Init(0);
}

static void LumaDebugMenu_RemoveItems(u8 taskid) {
	LumaDebugMenu_Close(taskid);
	LumaDebugMenu_AddItems_Init(1);
}

static void LumaDebugMenu_ViewTownMap(u8 taskid) {
	BeginNormalPaletteFade(0xffffffff, 0, 0, 16, RGB_BLACK);
	while (gPaletteFade.active)
		UpdatePaletteFade();
	LumaDebugMenu_Close(taskid);
	FieldInitRegionMap(CB2_ReturnToField);
}

static void LumaDebugMenu_JumpToCredits(u8 taskid) {
	PlayNewMapMusic(0);
	BeginNormalPaletteFade(0xffffffff, 0, 0, 16, RGB_BLACK);
	while (gPaletteFade.active)
		UpdatePaletteFade();
	LumaDebugMenu_Close(taskid);
	SetMainCallback2(CB2_StartCreditsSequence);
}

static void LumaDebugMenu_JumpToHoF(u8 taskid) {
	PlayNewMapMusic(0);
	BeginNormalPaletteFade(0xffffffff, 0, 0, 16, RGB_BLACK);
	while (gPaletteFade.active)
		UpdatePaletteFade();
	LumaDebugMenu_Close(taskid);
	SetMainCallback2(CB2_DoHallOfFameScreen);
}

static void LumaDebugMenu_JumpToStorageSystem(u8 taskid) {
	LumaDebugMenu_Close(taskid);
	ShowPokemonStorageSystemPC();
}

static void LumaDebugMenu_JumpToPlayerPC(u8 taskid) {
	LumaDebugMenu_Close(taskid);
	PlayerPC();
}

static void LumaDebugMenu_ClearStorage(u8 taskid) {
	u32 i;
	for (i = 0; i < TOTAL_BOXES_COUNT * IN_BOX_COUNT; i++) {
		ZeroBoxMonData(&gPokemonStoragePtr->boxes[0][i]);
	}
	PlaySE(SE_PIN);
	LumaDebugMenu_Close(taskid);
	EnableBothScriptContexts();
}

// Partial port of "POKéNAV D"
static void LumaDebugMenu_FillStorage(u8 taskid) {
	u32 i;
	struct BoxPokemon* mon;
	u32 data;
	for (i = 0; i < TOTAL_BOXES_COUNT * IN_BOX_COUNT; i++) {
		mon = &gPokemonStoragePtr->boxes[0][i];
		CreateBoxMon(mon, (Random() % NUM_SPECIES) + 1, (Random() % 100) + 1, 32, FALSE, 0, OT_ID_PLAYER_ID, 0);
		data = Random() % NUM_LANGUAGES;
		SetBoxMonData(mon, MON_DATA_LANGUAGE, &data);
		data = Random() % 256;
		SetBoxMonData(mon, MON_DATA_COOL, &data);
		data = Random() % 256;
		SetBoxMonData(mon, MON_DATA_CUTE, &data);
		data = Random() % 256;
		SetBoxMonData(mon, MON_DATA_TOUGH, &data);
		data = Random() % 256;
		SetBoxMonData(mon, MON_DATA_SMART, &data);
		data = Random() % 256;
		SetBoxMonData(mon, MON_DATA_BEAUTY, &data);
		data = Random() % 256;
		SetBoxMonData(mon, MON_DATA_SHEEN, &data);
		data = Random() % 256;
		SetBoxMonData(mon, MON_DATA_HP_EV, &data);
		data = Random() % 256;
		SetBoxMonData(mon, MON_DATA_ATK_EV, &data);
		data = Random() % 256;
		SetBoxMonData(mon, MON_DATA_DEF_EV, &data);
		data = Random() % 256;
		SetBoxMonData(mon, MON_DATA_SPEED_EV, &data);
		data = Random() % 256;
		SetBoxMonData(mon, MON_DATA_SPATK_EV, &data);
		data = Random() % 256;
		SetBoxMonData(mon, MON_DATA_SPDEF_EV, &data);
		data = Random() % 256;
		SetBoxMonData(mon, MON_DATA_FRIENDSHIP, &data);
		data = Random() % 256;
		SetBoxMonData(mon, MON_DATA_MET_LOCATION, &data);
		data = Random() % 15;
		SetBoxMonData(mon, MON_DATA_MET_GAME, &data);
		data = (Random() % (LAST_BALL - 1)) + 1;
		SetBoxMonData(mon, MON_DATA_POKEBALL, &data);
		data = Random() % 1;
		SetBoxMonData(mon, MON_DATA_IS_EGG, &data);
		if (i % IN_BOX_COUNT == 0) {
			PlaySE(SE_CONTEST_HEART);
			m4aMPlayImmInit(&gMPlayInfo_SE1);
			m4aMPlayPitchControl(&gMPlayInfo_SE1, 0xFFFF, (i /IN_BOX_COUNT) * 256);
		}
	}
	PlaySE(SE_PIN);
	LumaDebugMenu_Close(taskid);
	EnableBothScriptContexts();
}

static void LumaDebugMenu_OpenXaman(u8 taskid) {
	LumaDebugMenu_Close(taskid);
	Debug_ShowMainMenu();
}

static UNUSED void LumaDebugMenu_EditMoney(u8 taskid) {
	LumaDebugMenu_Close(taskid);
	// LumaDebugMenu_EditMoneyCoins(0);
}

enum {
	LUMA_FLAG_WEATHER = 0,
	LUMA_FLAG_ENCOUNTERS,
	LUMA_FLAG_MUSIC,
	LUMA_FLAG_TRAINER_ENCOUNTERS,
	LUMA_FLAG_NAMEPLATES,
	LUMA_FLAG_BGM,
	LUMA_FLAG_NATIONAL_DEX,
};

enum {
	LUMA_VAR_FIELD_MUSIC = 0,
	LUMA_VAR_REPEL,
	LUMA_VAR_SAVE_STATUS,
	LUMA_VAR_MIRAGE,
	LUMA_VAR_LOTTERY,
	LUMA_VAR_WEATHER,
};

static void LumaDebugMenu_WeatherFlag(u8 taskid) {
	LumaDebugMenu_EditSingleFlag(LUMA_FLAG_WEATHER, taskid);
}

static void LumaDebugMenu_Encounters(u8 taskid) {
	LumaDebugMenu_EditSingleFlag(LUMA_FLAG_ENCOUNTERS, taskid);
}

static void LumaDebugMenu_Music(u8 taskid) {
	LumaDebugMenu_EditSingleFlag(LUMA_FLAG_MUSIC, taskid);
}

static void LumaDebugMenu_TrainerEncounters(u8 taskid) {
	LumaDebugMenu_EditSingleFlag(LUMA_FLAG_TRAINER_ENCOUNTERS, taskid);
}

static void LumaDebugMenu_Nameplates(u8 taskid) {
	LumaDebugMenu_EditSingleFlag(LUMA_FLAG_NAMEPLATES, taskid);
}

static void LumaDebugMenu_BGMTransitions(u8 taskid) {
	LumaDebugMenu_EditSingleFlag(LUMA_FLAG_BGM, taskid);
}

static void LumaDebugMenu_NationalDex(u8 taskid) {
	LumaDebugMenu_EditSingleFlag(LUMA_FLAG_NATIONAL_DEX, taskid);
}

static void LumaDebugMenu_FieldMusic(u8 taskid) {
	LumaDebugMenu_EditSingleVar(LUMA_VAR_FIELD_MUSIC, taskid);
}

static void LumaDebugMenu_RepelSteps(u8 taskid) {
	LumaDebugMenu_EditSingleVar(LUMA_VAR_REPEL, taskid);
}

static void LumaDebugMenu_SaveStatus(u8 taskid) {
	LumaDebugMenu_EditSingleVar(LUMA_VAR_SAVE_STATUS, taskid);
}

static void LumaDebugMenu_MirageIsland(u8 taskid) {
	LumaDebugMenu_EditSingleVar(LUMA_VAR_MIRAGE, taskid);
}

static void LumaDebugMenu_Lottery(u8 taskid) {
	LumaDebugMenu_EditSingleVar(LUMA_VAR_LOTTERY, taskid);
}

static void LumaDebugMenu_FieldWeather(u8 taskid) {
	LumaDebugMenu_EditSingleVar(LUMA_VAR_WEATHER, taskid);
}

static void LumaDebugMenu_RNG(u8 taskid) {
	LumaDebugMenu_Close(taskid);
	LumaDebugMenu_OpenRNG();
}

static const struct WindowTemplate LumaDebugMenu_AddItemsWindowTemplate = {
	.bg = 0,
	.tilemapLeft = 1,
	.tilemapTop = 1,
	.width = 16,
	.height = 6,
	.baseBlock = 1,
	.paletteNum = 15
};

static u16 lastItem[2];
static const u8 Str_AddItemsHeader[] = _("{COLOR GREEN}Add items{CLEAR_TO 80}{B_BUTTON} Cancel");
static const u8 Str_RemoveItemsHeader[] = _("{COLOR GREEN}Remove items{CLEAR_TO 80}{B_BUTTON} Cancel");

// Port of Make items menu, slightly inspired by xaman
static void LumaDebugMenu_AddItems_Init(u8 addOrRemove) {
	u8 winId = AddWindow(&LumaDebugMenu_AddItemsWindowTemplate);
	u8 taskid;
	DrawStdWindowFrame(winId, FALSE);
	CopyWindowToVram(winId, 3);
	AddTextPrinterParameterized(winId, 1, addOrRemove & 1 ? Str_RemoveItemsHeader : Str_AddItemsHeader, 0, 0, 0, NULL);
	taskid = CreateTask(LumaDebugMenu_AddItems_ProcessInput, 10);
	if (!lastItem[addOrRemove & 1]) lastItem[addOrRemove & 1] = 1;
	gTasks[taskid].data[0] = winId;
	gTasks[taskid].data[1] = 0;
	gTasks[taskid].data[2] = lastItem[addOrRemove & 1];
	gTasks[taskid].data[3] = 1;
	// TODO Item icon
	gTasks[taskid].data[5] = addOrRemove & 1;
	LumaDebugMenu_AddItems_Redraw(taskid);
}

static void LumaDebugMenu_AddItems_ProcessInput(u8 taskid) {
	struct Task* task = &gTasks[taskid];
	u8 winId = task->data[0];
	u8 mode = task->data[1];
	u16 keys = gMain.newKeys;
	u16 heldKeys = gMain.newAndRepeatedKeys;
	if (keys & B_BUTTON) {
		if (mode == 0) {
			ClearStdWindowAndFrame(task->data[0], TRUE);
			lastItem[task->data[5]] = task->data[2];
			RemoveWindow(winId);
			DestroyTask(taskid);
			EnableBothScriptContexts();
			PlaySE(SE_SELECT);
			return;
		}
		else {
			task->data[1] = 0;
			FillWindowPixelRect(winId, 0x11, 0, 32, 128, 16);
			LumaDebugMenu_AddItems_Redraw(taskid);
			PlaySE(SE_SELECT);
			return;
		}
	}
	if (keys & A_BUTTON) {
		if (mode == 0) {
			task->data[1] = 1;
			FillWindowPixelRect(winId, 0x11, 0, 16, 88, 16);
			LumaDebugMenu_AddItems_Redraw(taskid);
			PlaySE(SE_SELECT);
			return;
		}
		else {
			task->data[1] = 0;
			if (task->data[5] == 0) {
				if (AddBagItem(task->data[2], task->data[3]))
					PlaySE(SE_SUCCESS);
			}
			else {
				if (RemoveBagItem(task->data[2], task->data[3]))
					PlaySE(SE_SUCCESS);
			}
			FillWindowPixelRect(winId, 0x11, 0, 32, 128, 16);
			LumaDebugMenu_AddItems_Redraw(taskid);
			return;
		}
	}
	if (heldKeys & L_BUTTON) {
		if (mode == 0) {
			task->data[2] -= 100;
			if ((s16) task->data[2] < 1)
				task->data[2] += ITEMS_COUNT;
		}
		else {
			task->data[3] -= 100;
			if ((s16) task->data[3] < 1)
				task->data[3] = 1;
		}
		LumaDebugMenu_AddItems_Redraw(taskid);
		PlaySE(SE_SELECT);
		return;
	}
	if (heldKeys & R_BUTTON) {
		if (mode == 0) {
			task->data[2] += 100;
			if (task->data[2] > ITEMS_COUNT)
				task->data[2] -= ITEMS_COUNT;
		}
		else {
			task->data[3] += 100;
			if (task->data[3] > 999)
				task->data[3] = 999;
		}
		LumaDebugMenu_AddItems_Redraw(taskid);
		PlaySE(SE_SELECT);
		return;
	}
	if (heldKeys & DPAD_LEFT) {
		if (mode == 0) {
			task->data[2] -= 10;
			if ((s16) task->data[2] < 1)
				task->data[2] += ITEMS_COUNT;
		}
		else {
			task->data[3] -= 10;
			if ((s16) task->data[3] < 1)
				task->data[3] = 1;
		}
		LumaDebugMenu_AddItems_Redraw(taskid);
		PlaySE(SE_SELECT);
		return;
	}
	if (heldKeys & DPAD_RIGHT) {
		if (mode == 0) {
			task->data[2] += 10;
			if (task->data[2] > ITEMS_COUNT)
				task->data[2] -= ITEMS_COUNT;
		}
		else {
			task->data[3] += 10;
			if (task->data[3] > 999)
				task->data[3] = 999;
		}
		LumaDebugMenu_AddItems_Redraw(taskid);
		PlaySE(SE_SELECT);
		return;
	}
	if (heldKeys & DPAD_DOWN) {
		if (mode == 0) {
			task->data[2] -= 1;
			if (task->data[2] < 1)
				task->data[2] += ITEMS_COUNT;
		}
		else {
			task->data[3] -= 1;
			if (task->data[3] < 1)
				task->data[3] = 1;
		}
		LumaDebugMenu_AddItems_Redraw(taskid);
		PlaySE(SE_SELECT);
		return;
	}
	if (heldKeys & DPAD_UP) {
		if (mode == 0) {
			task->data[2] += 1;
			if ((s16) task->data[2] > ITEMS_COUNT)
				task->data[2] -= ITEMS_COUNT;
		}
		else {
			task->data[3] += 1;
			if ((s16) task->data[3] > 999)
				task->data[3] = 999;
		}
		LumaDebugMenu_AddItems_Redraw(taskid);
		PlaySE(SE_SELECT);
		return;
	}
}

static const u8 Str_WhichItem[] = _("Which item?");
static const u8 Str_HowMany[] = _("How many?");

// Not a task callback. but we still need the taskid in order to get the menu data.
static void LumaDebugMenu_AddItems_Redraw(u8 taskid) {
	struct Task* task = &gTasks[taskid];
	u8 winId = task->data[0];
	u8 mode = task->data[1];
	u16 item = task->data[2];
	u16 count = task->data[3];
	if (mode == 0) {
		FillWindowPixelRect(winId, 0x11, 28, 32, 88, 16);
		AddTextPrinterParameterized(winId, 0, Str_WhichItem, 0, 16, 0, NULL);
		ConvertIntToDecimalStringN(gStringVar1, item, STR_CONV_MODE_LEADING_ZEROS, 3);
		AddTextPrinterParameterized(winId, 7, gStringVar1, 4, 32, 0, NULL);
		CopyItemName(item, gStringVar1);
		AddTextPrinterParameterized(winId, 1, gStringVar1, 28, 32, 0, NULL);
		// TODO Item icon
	}
	else {
		AddTextPrinterParameterized(winId, 0, Str_HowMany, 0, 16, 0, NULL);
		ConvertIntToDecimalStringN(gStringVar1, count, STR_CONV_MODE_RIGHT_ALIGN, 3);
		AddTextPrinterParameterized(winId, 7, gStringVar1, 4, 32, 0, NULL);
	}
}

static const struct WindowTemplate LumaDebugMenu_EditSingleFlagWindowTemplate = {
    .bg = 0,
    .tilemapLeft = 27,
    .tilemapTop = 1,
    .width = 2,
    .height = 2,
    .baseBlock = 361,
    .paletteNum = 15
};

extern bool8 gDisableMusic;

static void LumaDebugMenu_EditSingleFlag(u8 flag, u8 taskid) {
	bool8 flagSet;
	struct Task* task = &gTasks[taskid];
	u8 winId;

	switch (flag) {
	default:
		return;
	case LUMA_FLAG_WEATHER:
		flagSet = FlagGet(FLAG_SYS_WEATHER_CTRL);
		break;
	case LUMA_FLAG_ENCOUNTERS:
		flagSet =  ~FlagGet(FLAG_SYS_NO_ENCOUNTER);
		break;
	case LUMA_FLAG_MUSIC:
		flagSet = ~gDisableMusic;
		break;
	case LUMA_FLAG_TRAINER_ENCOUNTERS:
		flagSet = ~FlagGet(FLAG_SYS_NO_TRAINER_SEE);
		break;
	case LUMA_FLAG_NAMEPLATES:
		flagSet = ~FlagGet(FLAG_HIDE_MAP_NAME_POPUP);
		break;
	case LUMA_FLAG_BGM:
		flagSet = ~FlagGet(FLAG_DONT_TRANSITION_MUSIC);
		break;
	case LUMA_FLAG_NATIONAL_DEX:
		flagSet = IsNationalPokedexEnabled();
		break;
	}

	winId = AddWindow(&LumaDebugMenu_EditSingleFlagWindowTemplate);
	DrawStdWindowFrame(winId, FALSE);
	CopyWindowToVram(winId, 3);

	AddTextPrinterParameterized(winId, 0, flagSet & 1 ? Str_On : Str_Off, 0, 0, 0, NULL);

	task->data[2] = winId;
	task->data[3] = flag;
	task->func = LumaDebugMenu_EditSingleFlag_ProcessInput;
}

static void LumaDebugMenu_EditSingleFlag_ProcessInput(u8 taskid) {
	u16 input = gMain.newKeys;
	struct Task* task = &gTasks[taskid];
	bool8 flagSet;
	u8 winId = task->data[2];
	u8 flag = task->data[3];

	if (input & (B_BUTTON | START_BUTTON)) {
		ClearStdWindowAndFrame(task->data[2], TRUE);
		RemoveWindow(task->data[2]);
		task->func = LumaDebugMenu_HandleInput;
		PlaySE(SE_SELECT);
		return;
	}
	if (input & A_BUTTON) {
		switch (flag) {
		default:
			return;
		case LUMA_FLAG_WEATHER:
			FlagToggle(FLAG_SYS_WEATHER_CTRL);
			flagSet = FlagGet(FLAG_SYS_WEATHER_CTRL);
			break;
		case LUMA_FLAG_ENCOUNTERS:
			FlagToggle(FLAG_SYS_NO_ENCOUNTER);
			flagSet = ~FlagGet(FLAG_SYS_NO_ENCOUNTER);
			break;
		case LUMA_FLAG_MUSIC:
			gDisableMusic = gDisableMusic ? 0 : 1;
			flagSet = ~gDisableMusic;
			if (gDisableMusic & 1) StopMapMusic();
			break;
		case LUMA_FLAG_TRAINER_ENCOUNTERS:
			FlagToggle(FLAG_SYS_NO_TRAINER_SEE);
			flagSet = ~FlagGet(FLAG_SYS_NO_TRAINER_SEE);
			break;
		case LUMA_FLAG_NAMEPLATES:
			FlagToggle(FLAG_HIDE_MAP_NAME_POPUP);
			flagSet = ~FlagGet(FLAG_HIDE_MAP_NAME_POPUP);
			break;
		case LUMA_FLAG_BGM:
			FlagToggle(FLAG_DONT_TRANSITION_MUSIC);
			flagSet = ~FlagGet(FLAG_DONT_TRANSITION_MUSIC);
			break;
		case LUMA_FLAG_NATIONAL_DEX:
			flagSet = IsNationalPokedexEnabled();
			if (flagSet) DisableNationalPokedex();
			else EnableNationalPokedex();
			flagSet = ~flagSet;
			break;
		}
		FillWindowPixelRect(winId, 0x11, 0, 0, 16, 16);
		AddTextPrinterParameterized(winId, 0, flagSet & 1 ? Str_On : Str_Off, 0, 0, 0, NULL);
		PlaySE(SE_SELECT);
		return;
	}
}

static const struct WindowTemplate LumaDebugMenu_EditSingleVarWindowTemplate = {
    .bg = 0,
    .tilemapLeft = 23,
    .tilemapTop = 1,
    .width = 6,
    .height = 2,
    .baseBlock = 361,
    .paletteNum = 15
};

static u16 fieldMusic;
static u8 fieldWeather;
extern u16 gSaveFileStatus;

static void LumaDebugMenu_EditSingleVar(u8 var, u8 taskid) {
	struct Task* task = &gTasks[taskid];
	u8 winId;
	u16* varPtr = NULL;
	u8** textPtrs = NULL;

	winId = AddWindow(&LumaDebugMenu_EditSingleVarWindowTemplate);
	DrawStdWindowFrame(winId, FALSE);
	CopyWindowToVram(winId, 3);

	switch (var) {
	default:
		return;
	case LUMA_VAR_FIELD_MUSIC:
		varPtr = &fieldMusic;
		break;
	case LUMA_VAR_REPEL:
		varPtr = GetVarPointer(VAR_REPEL_STEP_COUNT);
		break;
	case LUMA_VAR_SAVE_STATUS:
		varPtr = &gSaveFileStatus;
		break;
	case LUMA_VAR_MIRAGE:
		varPtr = GetVarPointer(VAR_MIRAGE_RND_H);
		break;
	case LUMA_VAR_LOTTERY:
		varPtr = GetVarPointer(VAR_POKELOT_RND2); // Just drop the upper 16 bits, we don't need them anyway
		break;
	case LUMA_VAR_WEATHER:
		varPtr = (u16*) &fieldWeather;
		break;
	}

	// Redundant safety check
	if (varPtr == NULL) return;

	if (textPtrs != NULL) {
		// TODO
	}
	else {
		if (var == LUMA_VAR_MIRAGE) {
			ConvertIntToDecimalStringN(gStringVar1, *(u32*) varPtr, STR_CONV_MODE_LEADING_ZEROS, 10);
		}
		// Unneeded safety check
		else if (var == LUMA_VAR_WEATHER) {
			ConvertIntToDecimalStringN(gStringVar1, *(u8*) varPtr, STR_CONV_MODE_LEADING_ZEROS, 2);
		}
		else {
			ConvertIntToDecimalStringN(gStringVar1, *varPtr, STR_CONV_MODE_LEADING_ZEROS, 5);
		}
	}

	AddTextPrinterParameterized(winId, 0, gStringVar1, 0, 0, 0, NULL);

	task->data[2] = winId;
	task->data[3] = var;
	task->func = LumaDebugMenu_EditSingleVar_ProcessInput;
}

static void LumaDebugMenu_EditSingleVar_ProcessInput(u8 taskid) {
	u16 input = gMain.newKeys;
	struct Task* task = &gTasks[taskid];
	//bool8 flagSet;
	//u8 winId = task->data[2];
	//u8 var = task->data[3];

	if (input & (B_BUTTON | START_BUTTON)) {
		ClearStdWindowAndFrame(task->data[2], TRUE);
		RemoveWindow(task->data[2]);
		task->func = LumaDebugMenu_HandleInput;
		PlaySE(SE_SELECT);
		return;
	}
	/*
		FillWindowPixelRect(winId, 0x11, 0, 0, 16, 16);
		AddTextPrinterParameterized(winId, 0, gStringVar1, 0, 0, 0, NULL);
		PlaySE(SE_SELECT);
		return;
	}*/
}

// RNG Core Types

enum {
	LUMA_RNG_LCRNG = 0, // main LCRNG
	LUMA_RNG_ARNG,      // alt LCRNG
	LUMA_RNG_ARNG2,      // alt LCRNG #2
	LUMA_RNG_GC,        // Colo/XD LCRNG
	// LUMA_RNG_MT         // Mersenne Twister
	LUMA_RNG_COUNT,
};

static u32 RngValues[LUMA_RNG_COUNT];
// static u64 RngValues64[LUMA_RNG_COUNT];

static void LumaDebugMenu_SeedRNG(u8 index, u16 seed) {
	RngValues[index % LUMA_RNG_COUNT] = seed;
}

#define ISO_RANDOMIZE3(val)(1812433253 * (val) + 1) // ARNG
#define ISO_RANDOMIZE4(val)(214013 * (val) + 2531011) // CXD

static u16 LumaDebugMenu_Random(u8 index) {
	switch (index % LUMA_RNG_COUNT) {
	case LUMA_RNG_LCRNG:
	default:
		RngValues[LUMA_RNG_LCRNG] = ISO_RANDOMIZE1(RngValues[LUMA_RNG_LCRNG]);
		return RngValues[LUMA_RNG_LCRNG] >> 16;
	case LUMA_RNG_ARNG:
		RngValues[LUMA_RNG_ARNG] = ISO_RANDOMIZE3(RngValues[LUMA_RNG_ARNG]);
		return RngValues[LUMA_RNG_ARNG] >> 16;
	case LUMA_RNG_ARNG2:
		RngValues[LUMA_RNG_ARNG2] = ISO_RANDOMIZE2(RngValues[LUMA_RNG_ARNG2]);
		return RngValues[LUMA_RNG_ARNG2] >> 16;
	case LUMA_RNG_GC:
		RngValues[LUMA_RNG_GC] = ISO_RANDOMIZE4(RngValues[LUMA_RNG_GC]);
		return RngValues[LUMA_RNG_GC] >> 16;
	/*
	case LUMA_RNG_MT:
		// TODO
	*/
	}
}

#define LumaDebugMenu_Random32(x) (LumaDebugMenu_Random(x) | (LumaDebugMenu_Random(x) << 16))

// RNG Modes

enum {
	LUMA_RNG_DEFAULT = 0,
	LUMA_RNG_ABCD,    // Method 1
	LUMA_RNG_ABDE,    // Method 2
	LUMA_RNG_ACDE,    // Method 3
	LUMA_RNG_ABCE,    // Method 4
	LUMA_RNG_CHARM,   // Cute Charm
	LUMA_RNG_CHAIN,   // Shiny Chain
	LUMA_RNG_DEAB,    // Colo/XD
	LUMA_RNG_CHAN,    // Channel Jirachi
	LUMA_RNG_WALKER,  // Pokéwalker
	LUMA_RNG_G5MG,    // Gen 5 Mystery Gift Shiny
};

// RNG Restrictions

enum {
	LUMA_RNG_SHINY = 0,    // Shiny
	LUMA_RNG_ANTI,         // Antishiny
	LUMA_RNG_GENDER,       // Cute Charm
	LUMA_RNG_SYNC,         // Synchronize (or Gen 3 Safari Zone)
	LUMA_RNG_ROAMER,       // Roamer (drop IV bits)
	LUMA_RNG_REVERSE,      // Reversed PID (Unown)
	LUMA_RNG_COLO_UMBREON, // Colo Umbreon (also XD Eevee)
	LUMA_RNG_COLO_ESPEON,  // Colo Espeon
	LUMA_RNG_G3MG,         // Gen 3 Event (affects {anti,}shiny)
	LUMA_RNG_G3MG_AX,      // Gen 3 Event Antishiny
	LUMA_RNG_ABILITY,      // Ability
	LUMA_RNG_R8,           // 8-bit seed
	LUMA_RNG_R16           // 16-bit seed
};

static bool8 LumaDebugMenu_PIDIV_HasShinyParam(u8 type, u32 pid, u32 tid) {
	bool8 IsShiny;
	if (type % 3 == 0) return TRUE;
	IsShiny = IsShinyOtIdPersonality(tid, pid);
	if (type % 1 == 1) return IsShiny;
	else return !IsShiny;
}

static bool8 LumaDebugMenu_PIDIV_HasGenderParam(u8 type, u32 pid, u16 species) {
	u8 gender;
	if (type % 3 == 0) return TRUE;
	gender = GetGenderFromSpeciesAndPersonality(species, pid);
	switch(gender) {
	case MON_GENDERLESS:
		return TRUE;
	case MON_MALE:
		return type % 3 == 1;
	case MON_FEMALE:
		return type % 3 == 2;
	default:
		return FALSE;
	}
}

static u32 LumaDebugMenu_PIDIV(u32* _pid, u32* _ivs, u8 type, u8 method, u8 rflags, u32 tid, u8 gender, u8 nature, u8 ability, u16 species) {
	u32 pids = 0;
	u32 pid = 0;
	u32 ivs = 0;
	u16 a, b, c, d, e;
	u8 ShinyParam = 0;
	if (rflags & (1 << LUMA_RNG_SHINY)) {
		ShinyParam = 1;
	}
	else if (rflags & (1 << LUMA_RNG_ANTI)) {
		ShinyParam = 2;
	}
	if (rflags & (1 << LUMA_RNG_GENDER)) {
		gender = (gender & 1) + 1;
	}
	else {
		gender = 0;
	}
	do {
		do {
			do {
				do {
					switch (method) {
					case LUMA_RNG_DEFAULT:
					default:
						pid = Random32();
						ivs = Random32();
						break;
					case LUMA_RNG_DEAB:
						if (rflags & (1 << LUMA_RNG_COLO_UMBREON)) {
							tid = LumaDebugMenu_Random32(type);
							LumaDebugMenu_Random(type); // ???
							LumaDebugMenu_Random(type);
						}
						else if (rflags & (1 << LUMA_RNG_COLO_ESPEON)) {
							tid = LumaDebugMenu_Random32(type);
							for (a = 0; a < 9; a++) {
								LumaDebugMenu_Random(type); // skip Umbre, plus extra calls???
							}
						}
						ivs = LumaDebugMenu_Random32(type);
						LumaDebugMenu_Random(type); // ???
						pid = LumaDebugMenu_Random(type);
						break;
					case LUMA_RNG_CHAN:
						tid = (LumaDebugMenu_Random(type) << 16) | 40122;
						pid = LumaDebugMenu_Random32(type);
						LumaDebugMenu_Random(type); // Item
						LumaDebugMenu_Random(type); // Version
						LumaDebugMenu_Random(type); // OT Gender
						// TODO: Unsure if this is the correct way IVs are genned.

						ivs = LumaDebugMenu_Random32(type);
						break;
					case LUMA_RNG_ABCD ... LUMA_RNG_ABCE:
						if (rflags & (1 << LUMA_RNG_R16)) {
							RngValues[type] &= 0xffff;
						}
						else if (rflags & (1 << LUMA_RNG_R8)) {
							RngValues[type] &= 0xff;
						}
						a = LumaDebugMenu_Random(type);
						b = LumaDebugMenu_Random(type);
						c = LumaDebugMenu_Random(type);
						d = LumaDebugMenu_Random(type);
						e = LumaDebugMenu_Random(type);
						switch (method) {
						case LUMA_RNG_ABCD:
						default:
							pid = a | b << 16;
							ivs = c | d << 16;
							break;
						case LUMA_RNG_ACDE:
							pid = a | c << 16;
							ivs = d | e << 16;
							break;
						case LUMA_RNG_ABDE:
							pid = a | b << 16;
							ivs = d | e << 16;
							break;
						case LUMA_RNG_ABCE:
							pid = a | b << 16;
							ivs = c | e << 16;
							break;
						}
						if (rflags & ((1 << LUMA_RNG_G3MG) | (1 << LUMA_RNG_SHINY))) {
							a = pid;
							b = pid >> 16;
							a ^= (tid & 0xff) ^ (tid >> 16);
							pid = a | (a << 16);
							pid &= 0xfffffff8;
							pid |= b & 0x7;
						}
						else if (rflags & ((1 << LUMA_RNG_G3MG) | (1 << LUMA_RNG_G3MG_AX))) {
							a = pid;
							b = pid >> 16;
							a ^= (tid & 0xff) ^ (tid >> 16) ^ b;
							pid = a | (b << 16);
						}
						else if (rflags & ((1 << LUMA_RNG_G3MG) | (1 << LUMA_RNG_ANTI))) {
							while(IsShinyOtIdPersonality(tid, pid)) {
								pid++;
							}
						}
						if (rflags & (1 << LUMA_RNG_REVERSE)) {
							pid = (pid << 16) | (pid >> 16);
						}
						if (rflags & (1 << LUMA_RNG_ROAMER)) {
							ivs &= 0xff;
						}
						break;
					case LUMA_RNG_CHAIN:
						a = LumaDebugMenu_Random(type) & 7;
						b = LumaDebugMenu_Random(type) & 7;
						for (e = 0; e < 13; e++) {
							a |= (LumaDebugMenu_Random(type) & 1) << (3 + e);
						}
						b = ((a ^ (tid & 0xffff) ^ (tid >> 16)) & 0xfff8) | b;
						pid = a | b << 16;
						ivs = LumaDebugMenu_Random32(type);
						break;
					case LUMA_RNG_WALKER:
						a = tid & 0xffff;
						b = tid >> 16;
						pid = (((a ^ b) >> 8) ^ 0xff) << 24;
						if (rflags & (1 << LUMA_RNG_SYNC)) {
							pid += nature - (pid % NUM_NATURES);
						}
						if (rflags & (1 << LUMA_RNG_GENDER)) {
							if (LumaDebugMenu_PIDIV_HasGenderParam(gender, pid, species)) {
								ivs = Random32();
								break;
							}
							c = gBaseStats[species].genderRatio;
							if (rflags & (1 << LUMA_RNG_SYNC)) {
								if (gender == 1) {
									pid += (((c - (pid & 0xff)) / NUM_NATURES) + 1) * NUM_NATURES;
									if (rflags & (1 << LUMA_RNG_ABILITY)) {
										if ((nature & 1) != (pid & 1)) {
											pid += 25;
										}
									}
								}
								else {
									pid -= ((((pid & 0xff) - c) / NUM_NATURES) + 1) * NUM_NATURES;
									if (rflags & (1 << LUMA_RNG_ABILITY)) {
										if ((nature & 1) != (pid & 1)) {
											pid -= 25;
										}
									}
								}
							}
							else {
								if (gender == 1) {
									pid += c - (pid & 0xff);
									if (rflags & (1 << LUMA_RNG_ABILITY)) {
										if ((nature & 1) != (pid & 1)) {
											pid += 25;
										}
									}
								}
								else {
									pid -= (pid & 0xff) - c;
									if (rflags & (1 << LUMA_RNG_ABILITY)) {
										if ((nature & 1) != (pid & 1)) {
											pid -= 25;
										}
									}
								}
							}
							ivs = Random32();
							break;
						case LUMA_RNG_G5MG:
							a = tid << 16;
							b = tid & 0xffff;
							ivs = Random32();
							c = ivs >> 24;
							d = ivs & 1;
							e = a ^ b ^ c;
							pid = e << 16 | c;
							if ((pid & (1 << 16)) != (u32)(d << 16)) {
								pid ^= (1 << 16);
							}
							ivs = Random32();
							break;
						}
					}
					pids++;
					if ((ability % 3) == 2) break;
					if (!(rflags & (1 << LUMA_RNG_ABILITY))) break;
					if (gBaseStats[species].abilities[1] == ABILITY_NONE) break;
				} while((pid & 1) == (ability % 3));
			} while(LumaDebugMenu_PIDIV_HasGenderParam(gender, pid, species));
		if (!(rflags & (1 << LUMA_RNG_SYNC))) break;
		} while(GetNatureFromPersonality(pid) == (nature % NUM_NATURES));
	} while(LumaDebugMenu_PIDIV_HasShinyParam(ShinyParam, pid, tid));
	*_pid = pid;
	*_ivs = ivs;
	return pids;
}

static const struct WindowTemplate LumaDebugMenu_RNGWindowTemplate = {
	.bg = 0,
	.tilemapLeft = 1,
	.tilemapTop = 1,
	.width = 16,
	.height = 6,
	.baseBlock = 1,
	.paletteNum = 15
};

static const u8 Str_LCRNG[] = _("LCRNG");
static const u8 Str_ARNG[] = _("ARNG");
static const u8 Str_ARNG2[] = _("LCRNG 2");
static const u8 Str_XD[] = _("XD / Colosseum");
static const u8 Str_MT[] = _("Mersenne Twister");

static const u8 Str_Disabled[] = _("Disabled");
static const u8 Str_Method1[] = _("Method 1 (ABCD)");
static const u8 Str_Method2[] = _("Method 2 (ABDE)");
static const u8 Str_Method3[] = _("Method 3 (ACDE)");
static const u8 Str_Method4[] = _("Method 4 (ABCE)");
static const u8 Str_Channel[] = _("Channel");
static const u8 Str_XD_Spot[] = _("XD PokéSpot");
static const u8 Str_Charm[] = _("Cute Charm");
static const u8 Str_Chain[] = _("Shiny Chain");
static const u8 Str_G5MG[] = _("Gen 5 Mystery Gift");

static const u8 Str_Shiny[] = _("Shiny");
static const u8 Str_Antishiny[] = _("Antishiny");
static const u8 Str_Roamer[] = _("Roamer");
static const u8 Str_Reverse[] = _("Reversed PID");
static const u8 Str_R8[] = _("8-bit Seed");
static const u8 Str_R16[] = _("16-bit Seed");

UNUSED static const u8* RNGTypes[] = {
	Str_LCRNG,
	Str_ARNG,
	Str_ARNG2,
	Str_XD,
	Str_MT
};

UNUSED static const u8* RNGMethods[] = {
	Str_Disabled,
	Str_Method1,
	Str_Method2,
	Str_Method3,
	Str_Method4,
	Str_Channel,
	Str_XD_Spot,
	Str_Charm,
	Str_Chain,
	Str_G5MG
};

UNUSED static const u8* RNGParams[] = {
	Str_Shiny,
	Str_Antishiny,
	Str_Roamer,
	Str_Reverse,
	Str_R8,
	Str_R16,
};

static const u8 Str_Type[] = _("RNG Type");
static const u8 Str_Method[] = _("RNG Method");
static const u8 Str_Restrict[] = _("RNG Restrictions");
static const u8 Str_RestrictOff[] = _("{STR_VAR_1}");
static const u8 Str_RestrictOn[] = _("{COLOR BLUE}{STR_VAR_1}");
static const u8 Str_Seed[] = _("Seed");
static const u8 Str_Div[] = _("Div");
static const u8 Str_Mod[] = _("Mod");

static u8 HasSeededRNG;
static u32 sPID;
static u32 sIVs;

static void LumaDebugMenu_OpenRNG() {
	u8 taskId;
	u32 tid = *(u32*) &gSaveBlock2Ptr->playerTrainerId;
	u8 winId = AddWindow(&LumaDebugMenu_RNGWindowTemplate);
	DrawStdWindowFrame(winId, FALSE);
	CopyWindowToVram(winId, 3);
	taskId = CreateTask(LumaDebugMenu_RNG_ProcessInput, 10);
	if (!HasSeededRNG) {
		LumaDebugMenu_SeedRNG(LUMA_RNG_LCRNG, 0);
		HasSeededRNG = 1;
	}
	sPID = LumaDebugMenu_Random32(LUMA_RNG_LCRNG);
	sIVs = LumaDebugMenu_Random32(LUMA_RNG_LCRNG);
	gTasks[taskId].data[0] = (LUMA_RNG_DEFAULT << 8) | LUMA_RNG_LCRNG;
	gTasks[taskId].data[1] = MON_MALE << 8; // No restrict flags
	gTasks[taskId].data[2] = (winId << 8) | NATURE_HARDY;
	gTasks[taskId].data[3] = tid;
	gTasks[taskId].data[4] = tid >> 16;
	gTasks[taskId].data[5] = SPECIES_BULBASAUR;
	gTasks[taskId].data[6] = 0; // Ability slot 0 / Cursor position
	LumaDebugMenu_RNG_Redraw(taskId);
}

static void LumaDebugMenu_RNG_ProcessInput(u8 taskid) {
	u16 keys = gMain.newKeys;
	UNUSED u16 heldKeys = gMain.newAndRepeatedKeys;
	struct Task* task = &gTasks[taskid];
	u8 type = task->data[0];
	u8 method = task->data[0] >> 8;
	u8 restrictFlags = task->data[1];
	u8 gender = task->data[1] >> 8;
	u8 nature = task->data[2];
	u8 winId = task->data[2] >> 8;
	u32 tid = (task->data[4] << 16) | task->data[3];
	u16 species = task->data[5];
	u8 ability = task->data[6];
	UNUSED u8 cursorPos = task->data[6] >> 8;
	if (keys & (B_BUTTON | START_BUTTON)) {
		ClearStdWindowAndFrame(winId, TRUE);
		RemoveWindow(winId);
		DestroyTask(taskid);
		EnableBothScriptContexts();
		PlaySE(SE_SELECT);
		return;
	}
	if (keys & SELECT_BUTTON) {
		LumaDebugMenu_SeedRNG(type, 0);
		LumaDebugMenu_PIDIV(&sPID, &sIVs, type, method, restrictFlags, tid, gender, nature, ability, species);
		LumaDebugMenu_RNG_Redraw(taskid);
		PlaySE(SE_SELECT);
		return;
	}
	if (keys & A_BUTTON) {
		LumaDebugMenu_PIDIV(&sPID, &sIVs, type, method, restrictFlags, tid, gender, nature, ability, species);
		LumaDebugMenu_RNG_Redraw(taskid);
		PlaySE(SE_SELECT);
		return;
	}
}

static void LumaDebugMenu_RNG_Redraw(u8 taskid) {
	struct Task* task = &gTasks[taskid];
	UNUSED u32 pid = sPID;
	UNUSED u32 ivs = sIVs;
	u8 type = task->data[0];
	UNUSED u8 method = task->data[0] >> 8;
	UNUSED u8 restrictFlags = task->data[1];
	UNUSED u8 gender = task->data[1] >> 8;
	UNUSED u8 nature = task->data[2];
	UNUSED u8 winId = task->data[2] >> 8;
	UNUSED u32 tid = (task->data[4] << 16) | task->data[3];
	UNUSED u16 species = task->data[5];
	UNUSED u8 ability = task->data[6];
	UNUSED u8 cursorPos = task->data[6] >> 8;
	UNUSED u32 seed = RngValues[type % LUMA_RNG_COUNT];
}

void FillScreen(u16 color) {
	CpuFill32(0, (void*) VRAM, VRAM_SIZE);
	CpuFill16(color, (void*) BG_PLTT, BG_PLTT_SIZE);
}

#endif
