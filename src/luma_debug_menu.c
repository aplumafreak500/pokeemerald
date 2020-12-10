#ifdef DEBUG
#include "global.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "debug.h"
#include "main.h"
#include "menu.h"
#include "palette.h"
#include "text.h"
#include "string_util.h"
#include "list_menu.h"
#include "map_name_popup.h"
#include "script.h"
#include "sound.h"
#include "field_weather.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "constants/species.h"
#include "constants/moves.h"
#include "constants/items.h"
#include "constants/battle.h"
#include "constants/region_map_sections.h"

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
static const u8 Str_DebugFixChecksums[] = _("Fix {0x55}{0x56} Checksums");
static const u8 Str_DebugClearStorage[] = _("Clear Storage");
static const u8 Str_DebugFillStorage[] = _("Fill Storage");
static const u8 Str_DebugNickname[] = _("Nickname");
static const u8 Str_DebugEgg[] = _("Breed");
static const u8 Str_DebugHM[] = _("Use HM");
static const u8 Str_DebugRNG[] = _("RNG");

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
static const u8 Str_EditTrainerID[] = _("Trainer ID: ");
static const u8 Str_EditSecretID[] = _("Secret ID: ");

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

static const u8 Str_On[] = _("On");
static const u8 Str_Off[] = _("Off");
static const u8 Str_HexPrefix[] = _("0x");

static void LumaDebugMenu_HandleInput(u8);
static void LumaDebugMenu_Close(u8);
static void LumaDebugMenu_Cancel(u8);
static void LumaDebugMenu_Nop(u8);
static void LumaDebugMenu_AddPKMN(u8);
static void LumaDebugMenu_AddEditPKMN_Init(u8);
static void LumaDebugMenu_EditPKMN_SetDefaults();
static void LumaDebugMenu_EditPKMN_PopulateData();
static void LumaDebugMenu_EditPKMN_Redraw();
static void LumaDebugMenu_AddEditPKMN_ProcessInput(u8);

static const struct ListMenuItem LumaDebugMenu_Items[] = {
	{Str_CommonGroup, LIST_HEADER},
	{Str_AddPKMN, 0},
	{Str_InGameGroup, LIST_HEADER},
	{Str_SaveFileGroup, LIST_HEADER},
	{Str_FunctionsGroup, LIST_HEADER},
	{Str_DataGroup, LIST_HEADER},
	{Str_GFXGroup, LIST_HEADER},
	{Str_DexGroup, LIST_HEADER},
};

static void(*const LumaDebugMenu_Actions[])(u8) = {
	LumaDebugMenu_AddPKMN,
	NULL
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
	.scrollMultiple = LIST_NO_MULTIPLE_SCROLL
};

static const struct WindowTemplate LumaDebugMenu_WindowTemplate = {
	.bg = 0,
	.tilemapLeft = 1,
	.tilemapTop = 1,
	.width = 13,
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

	if (menupos == 0) menupos = 1;

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

	ListMenuGetScrollAndRow(taskid, &scrolloffset, &menupos);

	input = ListMenu_ProcessInput(task->data[0]);

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

static void LumaDebugMenu_Nop(u8 taskid) {
}

static void LumaDebugMenu_AddPKMN(u8 taskid) {
	LumaDebugMenu_Close(taskid);
	LumaDebugMenu_AddEditPKMN_Init(0);
}

static const u8 Str_Species[] = _("Species");
static const u8 Str_Personality[] = _("PID");
static const u8 Str_TrainerID[] = _("TID");
static const u8 Str_OT[] = _("OT");
static const u8 Str_Nick[] = _("Nickname");
static const u8 Str_Gender[] = _("Gender");
static const u8 Str_Nature[] = _("Nature");
static const u8 Str_Egg[] = _("Egg");
static const u8 Str_Egg2[] = _("Egg2");
static const u8 Str_HasSpecies[] = _("Present");
static const u8 Str_Language[] = _("Language");
static const u8 Str_Game[] = _("Origin Game");
static const u8 Str_Item[] = _("Held Item");
static const u8 Str_Level[] = _("Level");
static const u8 Str_EXP[] = _("Experience");
static const u8 Str_Ability[] = _("Ability");
static const u8 Str_Friendship[] = _("Friendship");
static const u8 Str_MetLevel[] = _("Met Level");
static const u8 Str_MetLocation[] = _("Met Location");
static const u8 Str_Ball[] = _("Ball");
static const u8 Str_PKrus[] = _("{PK}Rus");
static const u8 Str_HP[] = _("HP");
static const u8 Str_Atk[] = _("Atk");
static const u8 Str_Def[] = _("Def");
static const u8 Str_Spe[] = _("Spe");
static const u8 Str_SpA[] = _("SpA");
static const u8 Str_SpD[] = _("SpD");
static const u8 Str_Atk2[] = _("Attack");
static const u8 Str_Def2[] = _("Defense");
static const u8 Str_Spe2[] = _("Speed");
static const u8 Str_SpA2[] = _("Sp. Atk");
static const u8 Str_SpD2[] = _("Sp. Def");
static const u8 Str_EV[] = _("EV");
static const u8 Str_IV[] = _("IV");
static const u8 Str_Current[] = _("Current");
static const u8 Str_Status[] = _("Status");
static const u8 Str_Cool[] = _("Cool");
static const u8 Str_Cute[] = _("Cute");
static const u8 Str_Tough[] = _("Tough");
static const u8 Str_Beauty[] = _("Beauty");
static const u8 Str_Smart[] = _("Smart");
static const u8 Str_Sheen[] = _("Sheen");
static const u8 Str_Fateful[] = _("Fateful");
static const u8 Str_Fateful2[] = _("Fateful2");
static const u8 Str_Ribbon[] = _("Ribbon");
static const u8 Str_ChampRibbon[] = _("Champion");
static const u8 Str_WinRibbon[] = _("Winning");
static const u8 Str_VictoryRibbon[] = _("Victory");
static const u8 Str_ArtistRibbon[] = _("Artist");
static const u8 Str_EffortRibbon[] = _("Effort");
static const u8 Str_GiftRibbon[] = _("Gift");
static const u8 Str_Move[] = _("Move");

static const u8 Str_None[] = _("---");
static const u8 Str_Psn[] = _("PSN");
static const u8 Str_Par[] = _("PAR");
static const u8 Str_Brn[] = _("BRN");
static const u8 Str_Slp[] = _("SLP");
static const u8 Str_Frz[] = _("FRZ");
static const u8 Str_Psn2[] = _("PSN2");

struct EditPokemonStruct {
	const u8* text;
	u32 mode;
	u32 min;
	u32 max;
	u32 initial;
	u16 SetMonDataParam;
	u16 digitCount;
};

enum {
	LUMA_EDIT_NULL,
	LUMA_EDIT_NORMAL,
	LUMA_EDIT_READONLY,
	LUMA_EDIT_STRING,
	LUMA_EDIT_BOOL,
	LUMA_EDIT_HEX,
};

static const struct EditPokemonStruct LumaDebugMenu_EditPKMN_Options[] = {
	{Str_Species, LUMA_EDIT_NORMAL, 0, NUM_SPECIES - 1, SPECIES_TREECKO, MON_DATA_SPECIES, 3},
	{Str_Personality, LUMA_EDIT_HEX, 0, 0xffffffff, 0, MON_DATA_PERSONALITY, 8},
	{Str_TrainerID, LUMA_EDIT_NORMAL, 0, 0xffff, 0, MON_DATA_OT_ID, 5},
	{NULL, LUMA_EDIT_NORMAL, 0, 0xffff, 0, MON_DATA_OT_ID, 5}, // SID
	{Str_OT, LUMA_EDIT_STRING, 0, 0, 0, MON_DATA_OT_NAME, PLAYER_NAME_LENGTH}, // We can't set a default here because the saveblock pointer cam change.
	{NULL, LUMA_EDIT_NORMAL, 0, 1, 0, MON_DATA_OT_GENDER, 1},
	{Str_Nick, LUMA_EDIT_STRING, 0, 0, 0, MON_DATA_NICKNAME, POKEMON_NAME_LENGTH},
	{Str_Gender, LUMA_EDIT_READONLY, 0, 2, 0, MON_DATA_PERSONALITY, 1},
	{Str_Nature, LUMA_EDIT_READONLY, 0, 24, 0, MON_DATA_PERSONALITY, 2},
	{Str_Egg, LUMA_EDIT_BOOL, 0, 1, 0, MON_DATA_IS_EGG, 1},
	{Str_Egg2, LUMA_EDIT_BOOL, 0, 1, 0, MON_DATA_SANITY_IS_EGG, 1},
	{Str_HasSpecies, LUMA_EDIT_BOOL, 0, 1, 0, MON_DATA_SANITY_HAS_SPECIES, 1},
	{Str_Language, LUMA_EDIT_NORMAL, 0, NUM_LANGUAGES - 1, GAME_LANGUAGE, MON_DATA_LANGUAGE, 2},
	{Str_Game, LUMA_EDIT_NORMAL, 0, 15, GAME_VERSION, MON_DATA_MET_GAME, 2},
	{Str_Item, LUMA_EDIT_NORMAL, 0, ITEMS_COUNT - 1, 0, MON_DATA_HELD_ITEM, 3},
	{Str_Level, LUMA_EDIT_READONLY, 1, 100, 10, MON_DATA_LEVEL, 3},
	{Str_EXP, LUMA_EDIT_NORMAL, 0, 1640000, 1000, MON_DATA_EXP, 7},
	{Str_Ability, LUMA_EDIT_NORMAL, 0, 1, 0, MON_DATA_ABILITY_NUM, 1},
	{Str_Friendship, LUMA_EDIT_NORMAL, 0, 255, 0, MON_DATA_FRIENDSHIP, 3},
	{Str_MetLevel, LUMA_EDIT_NORMAL, 0, 100, 10, MON_DATA_MET_LEVEL, 3}, // 0 instead of 1 because 0 means hatched from an Egg
	{Str_MetLocation, LUMA_EDIT_NORMAL, 0, 255, MAPSEC_LITTLEROOT_TOWN, MON_DATA_MET_LOCATION, 3},
	{Str_Ball, LUMA_EDIT_NORMAL, ITEM_MASTER_BALL, LAST_BALL, ITEM_POKE_BALL, MON_DATA_POKEBALL, 2},
	{Str_PKrus, LUMA_EDIT_NORMAL, 0, 3, 0, MON_DATA_POKERUS, 1}, // 4 different "strains"
	{NULL, LUMA_EDIT_NORMAL, 1, 4, 1, MON_DATA_POKERUS, 1}, // "default" days until cured
	{NULL, LUMA_EDIT_NORMAL, 0, 7, 0, MON_DATA_POKERUS, 1}, // Days until cured
	// Current stats
	{Str_HP, LUMA_EDIT_NORMAL, 0, 0x7fff, 0, MON_DATA_HP, 3},
	{NULL, LUMA_EDIT_READONLY, 0, 0x7fff, 0, MON_DATA_MAX_HP, 3},
	{Str_Atk, LUMA_EDIT_READONLY, 0, 0x7fff, 0, MON_DATA_ATK, 3},
	{Str_Def, LUMA_EDIT_READONLY, 0, 0x7fff, 0, MON_DATA_DEF, 3},
	{Str_Spe, LUMA_EDIT_READONLY, 0, 0x7fff, 0, MON_DATA_SPEED, 3},
	{Str_SpA, LUMA_EDIT_READONLY, 0, 0x7fff, 0, MON_DATA_SPATK, 3},
	{Str_SpD, LUMA_EDIT_READONLY, 0, 0x7fff, 0, MON_DATA_SPDEF, 3},
	// IVs
	{Str_HP, LUMA_EDIT_NORMAL, 0, 15, 0, MON_DATA_HP_IV, 2},
	{Str_Atk2, LUMA_EDIT_NORMAL, 0, 15, 0, MON_DATA_ATK_IV, 2},
	{Str_Def2, LUMA_EDIT_NORMAL, 0, 15, 0, MON_DATA_DEF_IV, 2},
	{Str_Spe2, LUMA_EDIT_NORMAL, 0, 15, 0, MON_DATA_SPEED_IV, 2},
	{Str_SpA2, LUMA_EDIT_NORMAL, 0, 15, 0, MON_DATA_SPATK_IV, 2},
	{Str_SpD2, LUMA_EDIT_NORMAL, 0, 15, 0, MON_DATA_SPDEF_IV, 2},
	// EVs
	{Str_HP, LUMA_EDIT_NORMAL, 0, 255, 0, MON_DATA_HP_EV, 3},
	{Str_Atk2, LUMA_EDIT_NORMAL, 0, 255, 0, MON_DATA_ATK_EV, 3},
	{Str_Def2, LUMA_EDIT_NORMAL, 0, 255, 0, MON_DATA_DEF_EV, 3},
	{Str_Spe2, LUMA_EDIT_NORMAL, 0, 255, 0, MON_DATA_SPEED_EV, 3},
	{Str_SpA2, LUMA_EDIT_NORMAL, 0, 255, 0, MON_DATA_SPATK_EV, 3},
	{Str_SpD2, LUMA_EDIT_NORMAL, 0, 255, 0, MON_DATA_SPDEF_EV, 3},
	// Contest Stats
	{Str_Cool, LUMA_EDIT_NORMAL, 0, 255, 0, MON_DATA_COOL, 3},
	{Str_Cute, LUMA_EDIT_NORMAL, 0, 255, 0, MON_DATA_CUTE, 3},
	{Str_Beauty, LUMA_EDIT_NORMAL, 0, 255, 0, MON_DATA_BEAUTY, 3},
	{Str_Smart, LUMA_EDIT_NORMAL, 0, 255, 0, MON_DATA_SMART, 3},
	{Str_Tough, LUMA_EDIT_NORMAL, 0, 255, 0, MON_DATA_TOUGH, 3},
	{Str_Sheen, LUMA_EDIT_NORMAL, 0, 255, 0, MON_DATA_SHEEN, 3},
	{Str_Status, LUMA_EDIT_NORMAL, 0, 6, 0, MON_DATA_STATUS, 1},
	{NULL, LUMA_EDIT_NORMAL, 0, 7, 0, MON_DATA_STATUS, 1}, // sleep timer
	{NULL, LUMA_EDIT_NORMAL, 0, 15, 0, MON_DATA_STATUS, 2}, // badly poisoned timer
	// Ribbons
	{Str_ChampRibbon, LUMA_EDIT_BOOL, 0, 1, 0, MON_DATA_CHAMPION_RIBBON, 1},
	{Str_WinRibbon, LUMA_EDIT_BOOL, 0, 1, 0, MON_DATA_WINNING_RIBBON, 1},
	{Str_VictoryRibbon, LUMA_EDIT_BOOL, 0, 1, 0, MON_DATA_VICTORY_RIBBON, 1},
	{Str_ArtistRibbon, LUMA_EDIT_BOOL, 0, 1, 0, MON_DATA_ARTIST_RIBBON, 1},
	{Str_EffortRibbon, LUMA_EDIT_BOOL, 0, 1, 0, MON_DATA_EFFORT_RIBBON, 1},
	{Str_Cool, LUMA_EDIT_NORMAL, 0, 3, 0, MON_DATA_COOL_RIBBON, 1},
	{Str_Cute, LUMA_EDIT_NORMAL, 0, 3, 0, MON_DATA_CUTE_RIBBON, 1},
	{Str_Beauty, LUMA_EDIT_NORMAL, 0, 3, 0, MON_DATA_BEAUTY_RIBBON, 1},
	{Str_Smart, LUMA_EDIT_NORMAL, 0, 3, 0, MON_DATA_SMART_RIBBON, 1},
	{Str_Tough, LUMA_EDIT_NORMAL, 0, 3, 0, MON_DATA_TOUGH_RIBBON, 1},
	{Str_GiftRibbon, LUMA_EDIT_HEX, 0, 127, 0, MON_DATA_GIFT_RIBBON_1, 3},
	{Str_Fateful, LUMA_EDIT_BOOL, 0, 1, 0, MON_DATA_OBEDIENCE, 1},
	{Str_Fateful2, LUMA_EDIT_NORMAL, 0, 15, 0, MON_DATA_FATEFUL_ENCOUNTER, 2},
	{Str_Move, LUMA_EDIT_NORMAL, 0, MOVES_COUNT, MOVE_POUND, MON_DATA_MOVE1, 3},
	{Str_Move, LUMA_EDIT_NORMAL, 0, MOVES_COUNT, 0, MON_DATA_MOVE2, 3},
	{Str_Move, LUMA_EDIT_NORMAL, 0, MOVES_COUNT, 0, MON_DATA_MOVE3, 3},
	{Str_Move, LUMA_EDIT_NORMAL, 0, MOVES_COUNT, 0, MON_DATA_MOVE4, 3},
	{NULL, LUMA_EDIT_NORMAL, 0, 99, 40, MON_DATA_PP1, 2},
	{NULL, LUMA_EDIT_NORMAL, 0, 99, 40, MON_DATA_PP2, 2},
	{NULL, LUMA_EDIT_NORMAL, 0, 99, 40, MON_DATA_PP3, 2},
	{NULL, LUMA_EDIT_NORMAL, 0, 99, 40, MON_DATA_PP4, 2},
	{NULL, LUMA_EDIT_NORMAL, 0, 3, 0, MON_DATA_PP_BONUSES, 1},
	{NULL, LUMA_EDIT_NORMAL, 0, 3, 0, MON_DATA_PP_BONUSES, 1},
	{NULL, LUMA_EDIT_NORMAL, 0, 3, 0, MON_DATA_PP_BONUSES, 1},
	{NULL, LUMA_EDIT_NORMAL, 0, 3, 0, MON_DATA_PP_BONUSES, 1},
};

#define LUMA_EDIT_OPTION_COUNT ARRAY_COUNT(LumaDebugMenu_EditPKMN_Options)

struct EditPokemonRam {
	struct Pokemon mon;
	struct Pokemon* monBeingEdited;
	u16 index;
	u16 mode;
	u32 data[LUMA_EDIT_OPTION_COUNT];
};

static EWRAM_DATA struct EditPokemonRam LumaDebugMenu_EditPKMN_Data;
static u8 LumaDebugMenu_EditPKMN_CurrentPage;
static u8 LumaDebugMenu_EditPKMN_CurrentlySelectedOption;
static u32 LumaDebugMenu_EditPKMN_editingVal;

static const struct WindowTemplate LumaDebugMenu_HeaderWindowTemplate = {
	.bg = 0,
	.tilemapLeft = 1,
	.tilemapTop = 1,
	.width = 28,
	.height = 2,
	.baseBlock = 1,
	.paletteNum = 15
};

static const struct WindowTemplate LumaDebugMenu_FullScreenWindowTemplate = {
	.bg = 0,
	.tilemapLeft = 1,
	.tilemapTop = 5,
	.width = 28,
	.height = 14,
	.baseBlock = 57,
	.paletteNum = 15
};

static const u8 Str_AddPKMN_Header[] = _("{COLOR GREEN}Create Pokémon");
static const u8 Str_EditPKMN_Header[] = _("{COLOR GREEN}Edit Pokémon");
static const u8 Str_AddEditPKMN_Header2[] = _("{START_BUTTON} Confirm {DPAD_LEFTRIGHT} Page");

static u8 LumaDebugMenu_EditPKMN_headerWindowId;
static u8 LumaDebugMenu_EditPKMN_menuWindowId;

static void LumaDebugMenu_AddEditPKMN_Init(u8 mode) {
	struct Pokemon* mons;
	LumaDebugMenu_EditPKMN_Data.mode = mode;
	switch (mode) {
	case 0:
	default:
		mons = &gEnemyParty[0];
		ZeroMonData(mons);
		ZeroMonData(&LumaDebugMenu_EditPKMN_Data.mon);
		LumaDebugMenu_EditPKMN_Data.monBeingEdited = mons;
		break;
	case 1:
		mons = &gPlayerParty[0];
		CopyMon(&LumaDebugMenu_EditPKMN_Data.mon, mons, sizeof(struct Pokemon));
		LumaDebugMenu_EditPKMN_Data.monBeingEdited = mons;
		break;
	case 2:
		mons = (struct Pokemon*) &gPokemonStoragePtr->boxes[0][0];
		CopyMon(&LumaDebugMenu_EditPKMN_Data.mon, mons, sizeof(struct BoxPokemon));
		CalculateMonStats(&LumaDebugMenu_EditPKMN_Data.mon);
		LumaDebugMenu_EditPKMN_Data.monBeingEdited = mons;
		break;
	}
	// Set default data
	if (mode == 0) {
		LumaDebugMenu_EditPKMN_SetDefaults();
	}
	// Populate the editor data
	LumaDebugMenu_EditPKMN_PopulateData();
	// Draw the editor menu
	LoadMessageBoxAndBorderGfx();
	LumaDebugMenu_EditPKMN_headerWindowId = AddWindow(&LumaDebugMenu_HeaderWindowTemplate);
	DrawStdWindowFrame(LumaDebugMenu_EditPKMN_headerWindowId, FALSE);
	CopyWindowToVram(LumaDebugMenu_EditPKMN_headerWindowId, 3);
	AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_headerWindowId, 1, mode == 0 ? Str_AddPKMN_Header : Str_EditPKMN_Header, 0, 0, 0, NULL);
	AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_headerWindowId, 0, Str_AddEditPKMN_Header2, 105, 0, 0, NULL);
	LumaDebugMenu_EditPKMN_menuWindowId = AddWindow(&LumaDebugMenu_FullScreenWindowTemplate);
	DrawStdWindowFrame(LumaDebugMenu_EditPKMN_menuWindowId, FALSE);
	CopyWindowToVram(LumaDebugMenu_EditPKMN_menuWindowId, 3);
	LumaDebugMenu_EditPKMN_Redraw();
	CreateTask(LumaDebugMenu_AddEditPKMN_ProcessInput, 10);
}

static void LumaDebugMenu_EditPKMN_SetDefaults() {
	struct Pokemon* mons = &LumaDebugMenu_EditPKMN_Data.mon;
	u32 data, i, j, k;
	CreateMon(mons, LumaDebugMenu_EditPKMN_Options[0].initial, LumaDebugMenu_EditPKMN_Options[15].initial, 32, 0, 0, 0, 0);
	data = (LumaDebugMenu_EditPKMN_Options[23].initial & 0xc0) << 6;
	data |= (LumaDebugMenu_EditPKMN_Options[22].initial & 0x30) << 4;
	data |= (LumaDebugMenu_EditPKMN_Options[24].initial & 0xf);
	SetMonData(mons, MON_DATA_POKERUS, &data);
	for (i = 0; i < LUMA_EDIT_OPTION_COUNT; i++) {
		switch (i) {
		default:
			SetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, &LumaDebugMenu_EditPKMN_Options[i].initial);
			break;
		// All these should already be set (or will be set later)
		case 0 ... 8: // Species, PID, nick, etc.
		case 11: // Sanity bit
		case 15 ... 16: // Level and EXP
		case 22 ... 37: // Pokerus, stats
		case 70 ... 76: // PP
			break;
		case 50: // Status
			j = LumaDebugMenu_EditPKMN_Options[i].initial;
			switch (j) {
			case 0:
			default:
				data = 0;
				break;
			case 1:
				data = STATUS1_POISON;
				break;
			case 2:
				data = STATUS1_PARALYSIS;
				break;
			case 3:
				data = STATUS1_BURN;
				break;
			case 4:
				data = 3;
				break;
			case 5:
				data = STATUS1_FREEZE;
				break;
			case 6:
				data = STATUS1_TOXIC_POISON;
				break;
			}
			SetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, &data);
			break;
		case 51: // Sleep counter
			if (LumaDebugMenu_EditPKMN_Options[50].initial == 4) {
				data = LumaDebugMenu_EditPKMN_Options[i].initial;
				SetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, &data);
			}
			break;
		case 52: // Toxic counter
			if (LumaDebugMenu_EditPKMN_Options[50].initial == 4) {
				data = LumaDebugMenu_EditPKMN_Options[i].initial << 8 | STATUS1_TOXIC_POISON;
				SetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, &data);
			}
			break;
		case 63: // Gift ribbons
			data = LumaDebugMenu_EditPKMN_Options[i].initial;
			for (j = 0; j < 7; j++) {
				k = data & 1;
				SetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam + j, &k);
				data >>= 1;
			}
			break;
		case 77: // PP Up count (74 through 76 are set too)
			data = 0;
			for (j = 0; j < 4; j++) {
				data <<= 2;
				data |= (LumaDebugMenu_EditPKMN_Options[74 + j].initial & 3);
			}
			SetMonData(mons, LumaDebugMenu_EditPKMN_Options[74].SetMonDataParam, &data);
			break;
		}
	}
	MonRestorePP(mons);
}

static void LumaDebugMenu_EditPKMN_PopulateData() {
	struct Pokemon* mons = &LumaDebugMenu_EditPKMN_Data.mon;
	u32 data, i, j;
	for (i = 0; i < LUMA_EDIT_OPTION_COUNT; i++) {
		switch (i) {
		default:
			LumaDebugMenu_EditPKMN_Data.data[i] = GetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, NULL);
			break;
		case 2: // TID
			data = GetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, NULL);
			LumaDebugMenu_EditPKMN_Data.data[i] = data & 0xffff;
			break;
		case 3: // SID
			data = GetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, NULL);
			LumaDebugMenu_EditPKMN_Data.data[i] = (data & 0xffff0000) >> 16;
			break;
		case 4: // OT
			LumaDebugMenu_EditPKMN_Data.data[i] = (u32) &mons->box.otName;
			break;
		case 6: // Nickname
			LumaDebugMenu_EditPKMN_Data.data[i] = (u32) &mons->box.nickname;
			break;
		case 7: // Gender
			data = GetMonGender(mons);
			if (data == MON_FEMALE) data = 1;
			else if (data == MON_GENDERLESS) data = 2;
			LumaDebugMenu_EditPKMN_Data.data[i] = data;
			break;
		case 8: // Nature
			LumaDebugMenu_EditPKMN_Data.data[i] = GetNature(mons);
			break;
		case 22: // Pokerus strain
			data = GetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, NULL);
			data &= 0x30;
			data >>= 4;
			LumaDebugMenu_EditPKMN_Data.data[i] = data;
			break;
		case 23: // Pokerus days when spread
			data = GetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, NULL);
			data &= 0xc0;
			data >>= 6;
			LumaDebugMenu_EditPKMN_Data.data[i] = data;
			break;
		case 24: // Pokerus days left
			data = GetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, NULL);
			data &= 0xf;			LumaDebugMenu_EditPKMN_Data.data[i] = data;
			break;
		case 50: // Status
			data = GetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, NULL);
			if (data & STATUS1_SLEEP) data = 4;
			else if (data & STATUS1_POISON) data = 1;
			else if (data & STATUS1_BURN) data = 3;
			else if (data & STATUS1_FREEZE) data = 5;
			else if (data & STATUS1_PARALYSIS) data = 2;
			else if (data & STATUS1_TOXIC_POISON) data = 6;
			else data = 0;
			LumaDebugMenu_EditPKMN_Data.data[i] = data;
			break;
		case 51: // Sleep counter
			data = GetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, NULL);
			data &= STATUS1_SLEEP;
			LumaDebugMenu_EditPKMN_Data.data[i] = data;
			break;
		case 52: // Toxic counter
			data = GetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, NULL);
			data >>= 8;
			LumaDebugMenu_EditPKMN_Data.data[i] = data;
			break;
		case 63: // Gift ribbons
			data = 0;
			for (j = 0; j < 7; j++) {
				data |= GetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam + j, NULL);
				data <<= 1;
			}
			LumaDebugMenu_EditPKMN_Data.data[i] = data;
			break;
		case 74 ... 77: // PP Up count
			data = GetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, NULL);
			j = (i - 74) * 2;
			data >>= j;
			LumaDebugMenu_EditPKMN_Data.data[i] = data & 3;
			break;
		}
	}
}

static const u8 Str_Page[] = _("Page: {STR_VAR_1}");
static const u8 Str_Slot[] = _("Slot: {STR_VAR_1}");

static const u8 Str_StringVars[] = _("{STR_VAR_1}{STR_VAR_3}");
static const u8 Str_Spacer1[] = _(": {CLEAR_TO 100}");
static const u8 Str_CursorColor[] = _("{COLOR GREEN}");
static const u8 Str_Cursor2Color[] = _("{COLOR LIGHT_GREEN}{SHADOW GREEN}");
static const u8 Str_Cursor3Color[] = _("{COLOR RED}");

static const u8 LumaDebugMenu_Pages[13][7] = {
	{ 0, 16,  2,  1,  6,  4, 0xff},
	{50, 18, 22,  9, 11, 10, 0xff},
	{66, 67, 68, 69, 14, 17, 0xff},
	{25, 27, 28, 29, 30, 31, 0xff},
	{44, 45, 46, 47, 48, 49, 0xff},
	{58, 59, 60, 61, 62, 56, 0xff},
	{53, 54, 55, 57, 63, 64, 0xff},
	{12, 13, 19, 20, 21, 65, 0xff},
	// Below entries are unused.
	{ 3,  5, 70, 71, 72, 73, 0xff},
	{ 7,  8, 74, 75, 76, 77, 0xff},
	{15, 23, 24, 26, 51, 52, 0xff},
	{32, 33, 34, 35, 36, 37, 0xff},
	{38, 39, 40, 41, 42, 43, 0xff},
};

static EWRAM_DATA u8 LumaDebugMenu_NameBuffer[16];

static void LumaDebugMenu_EditPKMN_Redraw() {
	u32 i, x, y;
	u8* bufferPosition;
	const u8* page = LumaDebugMenu_Pages[LumaDebugMenu_EditPKMN_CurrentPage];
	const struct EditPokemonStruct* data;
	u8 index;
	ConvertIntToDecimalStringN(gStringVar1, LumaDebugMenu_EditPKMN_CurrentPage + 1, STR_CONV_MODE_LEFT_ALIGN, 2);
	StringExpandPlaceholders(gStringVar2, Str_Page);
	AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 0, gStringVar2, x, y, 0, NULL);
	x = 100;
	ConvertIntToDecimalStringN(gStringVar1, LumaDebugMenu_EditPKMN_Data.index + 1, STR_CONV_MODE_LEFT_ALIGN, 2);
	StringExpandPlaceholders(gStringVar2, Str_Slot);
	AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 0, gStringVar2, x, y, 0, NULL);
	x = 0;
	y += 16;
	// TODO: Redraw the window (Menu_BlankWindowRect in RS, what's Emerald's equivalent?)
	for (i = 0; i < 6; i++) {
		bufferPosition = gStringVar2;
		index = page[i];
		if (index == 0xff) break;
		if (i == LumaDebugMenu_EditPKMN_CurrentlySelectedOption) {
			// Color the currently selected option red
			bufferPosition = StringCopy(bufferPosition, Str_CursorColor);
		}
		data = &LumaDebugMenu_EditPKMN_Options[index];
		switch (index) {
		default:
			switch (data->mode) {
			case LUMA_EDIT_NORMAL:
			default:
				ConvertIntToDecimalStringN(gStringVar1, LumaDebugMenu_EditPKMN_Data.data[index], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
				break;
			case LUMA_EDIT_HEX:
				ConvertUIntToHexStringN(gStringVar1, LumaDebugMenu_EditPKMN_Data.data[index], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
				break;
			case LUMA_EDIT_NULL:
				break;
			case LUMA_EDIT_BOOL:
				StringCopy(gStringVar1, LumaDebugMenu_EditPKMN_Data.data[index] ? Str_On : Str_Off);
				break;
			case LUMA_EDIT_STRING:
				StringCopy(gStringVar1, (u8*) LumaDebugMenu_EditPKMN_Data.data[index]);
				break;
			}
			if (data->text != NULL) {
				bufferPosition = StringCopy(bufferPosition, data->text);
				bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
			}
			if (data->mode == LUMA_EDIT_HEX) {
				bufferPosition = StringCopy(bufferPosition, Str_HexPrefix);
			}
			*gStringVar3 = EOS;
			StringExpandPlaceholders(bufferPosition, Str_StringVars);
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 7, gStringVar2, x, y, 0, NULL);
			y+= 16;
			break;
		}
		// TODO: Add non-default cases
	}
}

static void LumaDebugMenu_AddEditPKMN_ProcessInput(u8 taskid) {
	u16 keys = gMain.newKeys;
	u16 heldKeys = gMain.newAndRepeatedKeys;
	struct Task* task = &gTasks[taskid];
	struct Pokemon* mons;

	if (keys & DPAD_LEFT) {
		if (LumaDebugMenu_EditPKMN_CurrentPage > 0) {
			LumaDebugMenu_EditPKMN_CurrentPage--;
		}
		else {
			LumaDebugMenu_EditPKMN_CurrentPage = 7;
		}
		LumaDebugMenu_EditPKMN_Redraw();
		PlaySE(SE_SELECT);
		return;
	}
	if (keys & DPAD_RIGHT) {
		if (LumaDebugMenu_EditPKMN_CurrentPage < 7) {
			LumaDebugMenu_EditPKMN_CurrentPage++;
		}
		else {
			LumaDebugMenu_EditPKMN_CurrentPage = 0;
		}
		LumaDebugMenu_EditPKMN_Redraw();
		PlaySE(SE_SELECT);
		return;
	}
	if (keys & DPAD_UP) {
		if (LumaDebugMenu_EditPKMN_CurrentlySelectedOption > 0) {
			LumaDebugMenu_EditPKMN_CurrentlySelectedOption--;
		}
		else {
			LumaDebugMenu_EditPKMN_CurrentlySelectedOption = 5;
		}
		LumaDebugMenu_EditPKMN_Redraw();
		PlaySE(SE_SELECT);
		return;
	}
	if (keys & DPAD_DOWN) {
		if (LumaDebugMenu_EditPKMN_CurrentlySelectedOption < 5) {
			LumaDebugMenu_EditPKMN_CurrentlySelectedOption++;
		}
		else {
			LumaDebugMenu_EditPKMN_CurrentlySelectedOption = 0;
		}
		LumaDebugMenu_EditPKMN_Redraw();
		PlaySE(SE_SELECT);
		return;
	}
	if (keys & L_BUTTON) {
		// This check is much simpler than the one below it...
		if (LumaDebugMenu_EditPKMN_Data.index <= 0) return;
		LumaDebugMenu_EditPKMN_Data.index--;
		if (LumaDebugMenu_EditPKMN_Data.mode == 2) {
			// We can technically select slot 404 of box 1 (actually box 13 slot 14) but it's still valid behavior provided the max index was set properly above.
			mons = (struct Pokemon*) &gPokemonStoragePtr->boxes[0][LumaDebugMenu_EditPKMN_Data.index];
			LumaDebugMenu_EditPKMN_Data.monBeingEdited = mons;
			CopyMon(&LumaDebugMenu_EditPKMN_Data.mon, mons, sizeof(struct BoxPokemon));
			CalculateMonStats(&LumaDebugMenu_EditPKMN_Data.mon);
		}
		else {
			mons = &gPlayerParty[LumaDebugMenu_EditPKMN_Data.index];
			LumaDebugMenu_EditPKMN_Data.monBeingEdited = mons;
			CopyMon(&LumaDebugMenu_EditPKMN_Data.mon, mons, sizeof(struct Pokemon));
		}
		LumaDebugMenu_EditPKMN_PopulateData();
		LumaDebugMenu_EditPKMN_Redraw();
		PlaySE(SE_SELECT);
		return;
	}
	if (keys & R_BUTTON) {
		u32 max_index;
		switch (LumaDebugMenu_EditPKMN_Data.mode) {
		case 0:
		default:
			return;
		case 1:
			max_index = PARTY_SIZE;
			break;
		case 2:
			max_index = TOTAL_BOXES_COUNT * IN_BOX_COUNT;
			break;
		}
		if (LumaDebugMenu_EditPKMN_Data.index <= max_index) return;
		LumaDebugMenu_EditPKMN_Data.index++;
		if (LumaDebugMenu_EditPKMN_Data.mode == 2) {
			mons = (struct Pokemon*) &gPokemonStoragePtr->boxes[0][LumaDebugMenu_EditPKMN_Data.index];
			LumaDebugMenu_EditPKMN_Data.monBeingEdited = mons;
			CopyMon(&LumaDebugMenu_EditPKMN_Data.mon, mons, sizeof(struct BoxPokemon));
			CalculateMonStats(&LumaDebugMenu_EditPKMN_Data.mon);
		}
		else {
			mons = &gPlayerParty[LumaDebugMenu_EditPKMN_Data.index];
			LumaDebugMenu_EditPKMN_Data.monBeingEdited = mons;
			CopyMon(&LumaDebugMenu_EditPKMN_Data.mon, mons, sizeof(struct Pokemon));
		}
		LumaDebugMenu_EditPKMN_PopulateData();
		LumaDebugMenu_EditPKMN_Redraw();
		PlaySE(SE_SELECT);
		return;
	}
	if (keys & B_BUTTON) {
		ClearStdWindowAndFrame(LumaDebugMenu_EditPKMN_headerWindowId, TRUE);
		RemoveWindow(LumaDebugMenu_EditPKMN_headerWindowId);
		ClearStdWindowAndFrame(LumaDebugMenu_EditPKMN_menuWindowId, TRUE);
		RemoveWindow(LumaDebugMenu_EditPKMN_menuWindowId);
		DestroyTask(taskid);
		PlaySE(SE_SELECT);
		return;
	}
	if (keys & SELECT_BUTTON) {
		// TODO: Re-randomize the PID and IVs
		return;
	}
	if (keys & A_BUTTON) {
		// TODO: Go into "edit" mode
		return;
	}
	if (keys & START_BUTTON) {
		// TODO: Add mon to party
		return;
	}
}

#endif
