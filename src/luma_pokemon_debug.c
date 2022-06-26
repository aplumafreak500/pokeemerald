#ifdef DEBUG
// Port of Watanabe Debug Menu -> Create Pokémon Menu
/* TODO Known Bugs and Todo List:
	* None as of right now
Things that are not implemented yet, or bugs that are caused by unimplemented features:
	* Fade into and out of this menu instead of drawing it over the overworld. (Possible custom GFX?)
	* PP are not recalculated when editing PP Up count or moves.
	* Alternate values aren't drawn until you scroll over to them in edit mode.
	* Only one of the sleep and toxic counter should be visible and editable at one time, but only if the status is sleep or toxic respectively. (This does not take the separate indexes for these two values into consideration.)
	* Language, Origin Game, Met Location, Ball, and Nature (the unused separate index) should be drawn with their names next to them.
	* If the Pokérus Strain is 0, the Days indexes should not be accessible.
	* Setting "Egg" from Off to On should also update "Egg2", but setting "Egg2" to Off should NOT update "Egg". Also, setting "Egg" to Off should NOT update "Egg2".
	* Add a "Bad Egg" index as an alternate value for "Present".
	* In edit mode, pressing Select should reset that value; in mode 0, to default; else to that of the mon being edited.
	* While not in edit mode, pressing Select when the cursor is selecting the PID or IVs, re-randomize them both according to "Method 1". When selecting Species, toggle that species' Pokédex flags, else copy to gEnemyParty then open up the Summary Screen. Set the PSS callback back to this menu.
	* If the mon being created would be Shiny, draw a star next to the nickname.
	* Dynamic max values:
		* PP (With max PP for that move including PP Up boosts)
		* Current HP (with max HP)
		* EXP (with EXP at level 100 for that species)
	* Binary and octal display modes
	* A comfirmation prompt
	* Draw the mon's icon next to the species
	* An actual cursor (instead of just highlighting the selected option)
*/
#include "global.h"
#include "main.h"
#include "sound.h"
#include "string_util.h"
#include "menu.h"
#include "pokemon.h"
#include "pokemon_summary_screen.h"
#include "pokemon_storage_system.h"
#include "item.h"
#include "script.h"
#include "random.h"
#include "data.h"
#include "region_map.h"
#include "battle_main.h"
#include "constants/songs.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/battle.h"

static void LumaDebugMenu_EditPKMN_SetDefaults();
static void LumaDebugMenu_EditPKMN_PopulateData();
static void LumaDebugMenu_EditPKMN_Redraw();
static void LumaDebugMenu_AddEditPKMN_ProcessInput(u8);
static void LumaDebugMenu_EditPKMN_EditModeProcessInput(u8);
static void LumaDebugMenu_EditPKMN_EditModeRedraw(u32, u8);
static u8 LumaDebugMenu_AddEditPKMN_GiveToPlayer();

const char AsciiStr_Buildstamp_CreatePokemon[] = "$ Luma Debug Menu - Create Pokémon Menu v0.0a built " __TIME__ " " __DATE__ " $";

static const u8 Str_Species[] = _("Species");
static const u8 Str_Personality[] = _("PID");
static const u8 Str_TrainerID[] = _("TID");
static const u8 Str_SecretID[] = _("SID");
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
static const u8 Str_Fateful2[] = _("Unused Ribbons");
static const u8 Str_CoolRibbon[] = _("Cool Ribbons");
static const u8 Str_CuteRibbon[] = _("Cute Ribbons");
static const u8 Str_ToughRibbon[] = _("Tough Ribbons");
static const u8 Str_BeautyRibbon[] = _("Beauty Ribbons");
static const u8 Str_SmartRibbon[] = _("Smart Ribbons");
static const u8 Str_ChampRibbon[] = _("Champion Ribbon");
static const u8 Str_WinRibbon[] = _("Winning Ribbon");
static const u8 Str_VictoryRibbon[] = _("Victory Ribbon");
static const u8 Str_ArtistRibbon[] = _("Artist Ribbon");
static const u8 Str_EffortRibbon[] = _("Effort Ribbon");
static const u8 Str_GiftRibbon[] = _("Gift Ribbons");
static const u8 Str_Move[] = _("Move");
static const u8 Str_PP[] = _("PP");
static const u8 Str_PPUp[] = _("PP Up");

static const u8 Str_None[] = _("---");
static const u8 Str_Psn[] = _("PSN");
static const u8 Str_Par[] = _("PAR");
static const u8 Str_Brn[] = _("BRN");
static const u8 Str_Slp[] = _("SLP");
static const u8 Str_Frz[] = _("FRZ");
static const u8 Str_Psn2[] = _("PSN2");

static const u8 Str_Genderless[] = _("-");
static const u8 Str_Male[] = _("♂");
static const u8 Str_Female[] = _("♀");

static const u8 Str_On[] = _("On");
static const u8 Str_Off[] = _("Off");
static const u8 Str_HexPrefix[] = _("0x");

static const u8* GenderIndexes[3] = {
	Str_Male,
	Str_Female,
	Str_Genderless
};

static UNUSED const u8* StatusIndexes[7] = {
	Str_None,
	Str_Psn,
	Str_Par,
	Str_Brn,
	Str_Slp,
	Str_Frz,
	Str_Psn2
};

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
	LUMA_EDIT_NULL = 0,
	LUMA_EDIT_NORMAL,
	LUMA_EDIT_READONLY,
	LUMA_EDIT_STRING,
	LUMA_EDIT_BOOL,
	LUMA_EDIT_HEX,
};

static const struct EditPokemonStruct LumaDebugMenu_EditPKMN_Options[] = {
	{Str_Species, LUMA_EDIT_NORMAL, 0, NUM_SPECIES, SPECIES_TREECKO, MON_DATA_SPECIES, 4},
	{Str_Personality, LUMA_EDIT_HEX, 0, 0xffffffff, 0, MON_DATA_PERSONALITY, 8},
	{Str_TrainerID, LUMA_EDIT_NORMAL, 0, 0xffff, 0, MON_DATA_OT_ID, 5},
	{Str_SecretID, LUMA_EDIT_NORMAL, 0, 0xffff, 0, MON_DATA_OT_ID, 5}, // SID
	{Str_OT, LUMA_EDIT_STRING, 0, 0, 0, MON_DATA_OT_NAME, PLAYER_NAME_LENGTH}, // We can't set a default here because the saveblock pointer can change.
	{Str_Gender, LUMA_EDIT_NORMAL, 0, 1, 0, MON_DATA_OT_GENDER, 1},
	{Str_Nick, LUMA_EDIT_STRING, 0, 0, 0, MON_DATA_NICKNAME, POKEMON_NAME_LENGTH},
	{Str_Gender, LUMA_EDIT_READONLY, 0, 2, 0, MON_DATA_PERSONALITY, 1},
	{Str_Nature, LUMA_EDIT_READONLY, 0, 24, 0, MON_DATA_PERSONALITY, 2},
	{Str_Egg, LUMA_EDIT_BOOL, 0, 1, 0, MON_DATA_IS_EGG, 1},
	{Str_Egg2, LUMA_EDIT_BOOL, 0, 1, 0, MON_DATA_SANITY_IS_EGG, 1},
	{Str_HasSpecies, LUMA_EDIT_BOOL, 0, 1, 1, MON_DATA_SANITY_HAS_SPECIES, 1},
	{Str_Language, LUMA_EDIT_NORMAL, 0, NUM_LANGUAGES - 1, GAME_LANGUAGE, MON_DATA_LANGUAGE, 2},
	{Str_Game, LUMA_EDIT_NORMAL, 0, 49, GAME_VERSION, MON_DATA_MET_GAME, 2}, // 45 = Shield
	{Str_Item, LUMA_EDIT_NORMAL, 0, ITEMS_COUNT - 1, 0, MON_DATA_HELD_ITEM, 3},
	{Str_Level, LUMA_EDIT_NORMAL, 0, 100, 10, MON_DATA_LEVEL, 3},
	{Str_EXP, LUMA_EDIT_NORMAL, 0, 1640000, 1000, MON_DATA_EXP, 7},
	{Str_Ability, LUMA_EDIT_NORMAL, 0, 2, 0, MON_DATA_ABILITY_NUM, 1},
	{Str_Friendship, LUMA_EDIT_NORMAL, 0, 255, 0, MON_DATA_FRIENDSHIP, 3},
	{Str_MetLevel, LUMA_EDIT_NORMAL, 0, 100, 10, MON_DATA_MET_LEVEL, 3}, // 0 instead of 1 because 0 means hatched from an Egg
	{Str_MetLocation, LUMA_EDIT_NORMAL, 0, 65535, MAPSEC_LITTLEROOT_TOWN, MON_DATA_MET_LOCATION, 5},
	{Str_Ball, LUMA_EDIT_NORMAL, 0, LAST_BALL, ITEM_POKE_BALL, MON_DATA_POKEBALL, 2},
	{Str_PKrus, LUMA_EDIT_NORMAL, 0, 3, 0, MON_DATA_POKERUS, 1}, // 4 different "strains"
	{Str_PKrus, LUMA_EDIT_NORMAL, 1, 4, 1, MON_DATA_POKERUS, 1}, // "default" days until cured
	{Str_PKrus, LUMA_EDIT_NORMAL, 0, 7, 0, MON_DATA_POKERUS, 1}, // Days until cured
	// Current stats
	{Str_HP, LUMA_EDIT_NORMAL, 0, 999, 0, MON_DATA_HP, 3},
	{Str_HP, LUMA_EDIT_READONLY, 0, 999, 0, MON_DATA_MAX_HP, 3},
	{Str_Atk, LUMA_EDIT_READONLY, 0, 999, 0, MON_DATA_ATK, 3},
	{Str_Def, LUMA_EDIT_READONLY, 0, 999, 0, MON_DATA_DEF, 3},
	{Str_Spe, LUMA_EDIT_READONLY, 0, 999, 0, MON_DATA_SPEED, 3},
	{Str_SpA, LUMA_EDIT_READONLY, 0, 999, 0, MON_DATA_SPATK, 3},
	{Str_SpD, LUMA_EDIT_READONLY, 0, 999, 0, MON_DATA_SPDEF, 3},
	// IVs
	{Str_HP, LUMA_EDIT_NORMAL, 0, 31, 0, MON_DATA_HP_IV, 2},
	{Str_Atk2, LUMA_EDIT_NORMAL, 0, 31, 0, MON_DATA_ATK_IV, 2},
	{Str_Def2, LUMA_EDIT_NORMAL, 0, 31, 0, MON_DATA_DEF_IV, 2},
	{Str_Spe2, LUMA_EDIT_NORMAL, 0, 31, 0, MON_DATA_SPEED_IV, 2},
	{Str_SpA2, LUMA_EDIT_NORMAL, 0, 31, 0, MON_DATA_SPATK_IV, 2},
	{Str_SpD2, LUMA_EDIT_NORMAL, 0, 31, 0, MON_DATA_SPDEF_IV, 2},
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
	{Str_Slp, LUMA_EDIT_NORMAL, 0, 7, 0, MON_DATA_STATUS, 1}, // sleep timer
	{Str_Psn2, LUMA_EDIT_NORMAL, 0, 15, 0, MON_DATA_STATUS, 2}, // badly poisoned timer
	// Ribbons
	{Str_ChampRibbon, LUMA_EDIT_BOOL, 0, 1, 0, MON_DATA_CHAMPION_RIBBON, 1},
	{Str_WinRibbon, LUMA_EDIT_BOOL, 0, 1, 0, MON_DATA_WINNING_RIBBON, 1},
	{Str_VictoryRibbon, LUMA_EDIT_BOOL, 0, 1, 0, MON_DATA_VICTORY_RIBBON, 1},
	{Str_ArtistRibbon, LUMA_EDIT_BOOL, 0, 1, 0, MON_DATA_ARTIST_RIBBON, 1},
	{Str_EffortRibbon, LUMA_EDIT_BOOL, 0, 1, 0, MON_DATA_EFFORT_RIBBON, 1},
	{Str_CoolRibbon, LUMA_EDIT_NORMAL, 0, 3, 0, MON_DATA_COOL_RIBBON, 1},
	{Str_CuteRibbon, LUMA_EDIT_NORMAL, 0, 3, 0, MON_DATA_CUTE_RIBBON, 1},
	{Str_BeautyRibbon, LUMA_EDIT_NORMAL, 0, 3, 0, MON_DATA_BEAUTY_RIBBON, 1},
	{Str_SmartRibbon, LUMA_EDIT_NORMAL, 0, 3, 0, MON_DATA_SMART_RIBBON, 1},
	{Str_ToughRibbon, LUMA_EDIT_NORMAL, 0, 3, 0, MON_DATA_TOUGH_RIBBON, 1},
	{Str_GiftRibbon, LUMA_EDIT_HEX, 0, 127, 0, MON_DATA_MARINE_RIBBON, 2},
	{Str_Fateful, LUMA_EDIT_BOOL, 0, 1, 0, MON_DATA_EVENT_LEGAL, 1},
	{Str_Fateful2, LUMA_EDIT_NORMAL, 0, 3, 0, MON_DATA_UNUSED_RIBBONS, 1},
	{Str_Move, LUMA_EDIT_NORMAL, 0, MOVES_COUNT - 1, MOVE_POUND, MON_DATA_MOVE1, 3},
	{Str_Move, LUMA_EDIT_NORMAL, 0, MOVES_COUNT - 1, 0, MON_DATA_MOVE2, 3},
	{Str_Move, LUMA_EDIT_NORMAL, 0, MOVES_COUNT - 1, 0, MON_DATA_MOVE3, 3},
	{Str_Move, LUMA_EDIT_NORMAL, 0, MOVES_COUNT - 1, 0, MON_DATA_MOVE4, 3},
	{Str_PP, LUMA_EDIT_NORMAL, 0, 99, 40, MON_DATA_PP1, 2},
	{Str_PP, LUMA_EDIT_NORMAL, 0, 99, 40, MON_DATA_PP2, 2},
	{Str_PP, LUMA_EDIT_NORMAL, 0, 99, 40, MON_DATA_PP3, 2},
	{Str_PP, LUMA_EDIT_NORMAL, 0, 99, 40, MON_DATA_PP4, 2},
	{Str_PPUp, LUMA_EDIT_NORMAL, 0, 3, 0, MON_DATA_PP_BONUSES, 1},
	{Str_PPUp, LUMA_EDIT_NORMAL, 0, 3, 0, MON_DATA_PP_BONUSES, 1},
	{Str_PPUp, LUMA_EDIT_NORMAL, 0, 3, 0, MON_DATA_PP_BONUSES, 1},
	{Str_PPUp, LUMA_EDIT_NORMAL, 0, 3, 0, MON_DATA_PP_BONUSES, 1},
};

#define LUMA_EDIT_OPTION_COUNT ARRAY_COUNT(LumaDebugMenu_EditPKMN_Options)

struct EditPokemonRam {
	struct Pokemon mon;
	struct Pokemon* monBeingEdited;
	u16 index;
	u16 mode;
	u32 data[LUMA_EDIT_OPTION_COUNT];
};

static EWRAM_DATA struct EditPokemonRam LumaDebugMenu_EditPKMN_Data = {{{0}, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0, {0}};
static u8 LumaDebugMenu_EditPKMN_CurrentPage;
static u8 LumaDebugMenu_EditPKMN_CurrentlySelectedOption;

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

static const u8 Str_DefaultOTName[8] = _("Debug-E");

static u8 LumaDebugMenu_EditPKMN_headerWindowId;
static u8 LumaDebugMenu_EditPKMN_menuWindowId;

/*
	Mode List:
	* 0 - Add to party
	* 1 - Edit party
	* 2 - Edit PC Box
	* 3 - Edit enemy party (usable as a sandbox)
	* 4 - Edit enemy party for debug battle
	* 5 - Edit party for debug battle
	* 6 - Add to enemy party (Unused)
	* 7 - Testing mode (Don't alter parties)
	* 8 - Testing mode (use first mon as template)
*/
void LumaDebugMenu_AddEditPKMN_Init(u8 mode) {
	struct Pokemon* mons;
	LumaDebugMenu_EditPKMN_Data.mode = mode;
	switch (mode) {
	case 0:
	case 6:
		mons = &gEnemyParty[0];
		ZeroMonData(mons); // Is this really necessary?
		ZeroMonData(&LumaDebugMenu_EditPKMN_Data.mon);
		LumaDebugMenu_EditPKMN_Data.monBeingEdited = mons;
		LumaDebugMenu_EditPKMN_Data.index = 0;
		break;
	case 1:
	case 5: // used in Debug Battle
		mons = &gPlayerParty[LumaDebugMenu_EditPKMN_Data.index];
		if (mode == 1) CopyMon(&LumaDebugMenu_EditPKMN_Data.mon, mons, sizeof(struct Pokemon));
		LumaDebugMenu_EditPKMN_Data.monBeingEdited = mons;
		break;
	case 2:
		mons = (struct Pokemon*) &gPokemonStoragePtr->boxes[0][LumaDebugMenu_EditPKMN_Data.index];
		CopyMon(&LumaDebugMenu_EditPKMN_Data.mon, mons, sizeof(struct BoxPokemon));
		CalculateMonStats(&LumaDebugMenu_EditPKMN_Data.mon);
		LumaDebugMenu_EditPKMN_Data.monBeingEdited = mons;
		break;
	case 3:
	case 4: // used in Debug Battle
		mons = &gEnemyParty[LumaDebugMenu_EditPKMN_Data.index];
		if (mode == 3) CopyMon(&LumaDebugMenu_EditPKMN_Data.mon, mons, sizeof(struct Pokemon));
		LumaDebugMenu_EditPKMN_Data.monBeingEdited = mons;
		break;
	case 7:
	case 8:
	default:
		if (mode == 8) CopyMon(&LumaDebugMenu_EditPKMN_Data.mon, &gPlayerParty[0], sizeof(struct Pokemon));
		else ZeroMonData(&LumaDebugMenu_EditPKMN_Data.mon);
		LumaDebugMenu_EditPKMN_Data.monBeingEdited = &LumaDebugMenu_EditPKMN_Data.mon;
		LumaDebugMenu_EditPKMN_Data.index = 0;
		break;
	}
	// Set default data
	if (mode == 0 || mode == 6 || mode == 7) {
		SetMonData(&LumaDebugMenu_EditPKMN_Data.mon, MON_DATA_OT_NAME, Str_DefaultOTName);
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

static u8 LumaDebugMenu_EditPKMN_NameBuffer[16];

static void LumaDebugMenu_EditPKMN_SetNewMonData(bool8 setMoves) {
	struct Pokemon* mons = &LumaDebugMenu_EditPKMN_Data.mon;
	u32 data, i, j, k;
	// Buffer the OT name
	StringCopyN(LumaDebugMenu_EditPKMN_NameBuffer, mons->box.otName, PLAYER_NAME_LENGTH);
	data = (LumaDebugMenu_EditPKMN_Data.data[3] << 16) | LumaDebugMenu_EditPKMN_Data.data[2];
	CreateMon(mons, LumaDebugMenu_EditPKMN_Data.data[0], LumaDebugMenu_EditPKMN_Data.data[15], 32, 1, LumaDebugMenu_EditPKMN_Data.data[1], OT_ID_PRESET, data);
	SetMonData(mons, MON_DATA_OT_NAME, LumaDebugMenu_EditPKMN_NameBuffer);
	data = ((LumaDebugMenu_EditPKMN_Data.data[23] - 1) & 3) << 6;
	data |= (LumaDebugMenu_EditPKMN_Data.data[22] & 3) << 4;
	data |= (LumaDebugMenu_EditPKMN_Data.data[24] & 0xf);
	SetMonData(mons, MON_DATA_POKERUS, &data);
	for (i = 0; i < LUMA_EDIT_OPTION_COUNT; i++) {
		switch (i) {
		default:
			SetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, &LumaDebugMenu_EditPKMN_Data.data[i]);
			break;
		// All these should already be set (or will be set later)
		case 0 ... 4: // PID, TID, OT
		case 6 ... 8: // Nickname, gender, nature
		case 15: // Level
		case 22 ... 24: // Pokérus
		case 26 ... 31: // Current stats
		case 74 ... 76: // PP Up counts
			break;
		// Only set after initial generation
		case 5: // OT Gender
		case 18: // Friendship (will always default to the base friendship of the default species)
		case 20: // Met location
		case 25: // Current HP
			if (!setMoves) {
				SetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, &LumaDebugMenu_EditPKMN_Data.data[i]);
			}
			break;
		case 17: // Ability
			if (setMoves) {
				if (gBaseStats[LumaDebugMenu_EditPKMN_Data.data[0]].abilities[1]) {
					data = LumaDebugMenu_EditPKMN_Data.data[1] & 1;
					SetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, &data);
				}
				break;
			}
			SetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, &LumaDebugMenu_EditPKMN_Data.data[i]);
			break;
		case 37: // IVs
			if (setMoves) {
				data = Random32();
				SetMonData(mons, MON_DATA_IVS, &data);
				break;
			}
			SetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, &LumaDebugMenu_EditPKMN_Data.data[i]);
			break;
		case 50: // Status
			j = LumaDebugMenu_EditPKMN_Data.data[i];
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
			if (LumaDebugMenu_EditPKMN_Data.data[50] == 4) {
				data = LumaDebugMenu_EditPKMN_Data.data[i];
				SetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, &data);
			}
			break;
		case 52: // Toxic counter
			if (LumaDebugMenu_EditPKMN_Data.data[i] == 6) {
				data = LumaDebugMenu_EditPKMN_Data.data[i] << 8 | STATUS1_TOXIC_POISON;
				SetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, &data);
			}
			break;
		case 63: // Gift ribbons
			data = LumaDebugMenu_EditPKMN_Data.data[i];
			for (j = 0; j < 7; j++) {
				k = data & 1;
				SetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam + j, &k);
				data >>= 1;
			}
			break;
		case 69: // Moves
			if (setMoves) {
				GiveMonInitialMoveset(mons);
				break;
			}
			SetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, &LumaDebugMenu_EditPKMN_Data.data[i]);
			break;
		case 77: // PP Up count (74 through 76 are set too)
			data = 0;
			for (j = 0; j < 4; j++) {
				data <<= 2;
				data |= (LumaDebugMenu_EditPKMN_Data.data[74 + j] & 3);
			}
			SetMonData(mons, LumaDebugMenu_EditPKMN_Options[74].SetMonDataParam, &data);
			break;
		}
	}
	if (setMoves) MonRestorePP(mons);
	CalculateMonStats(mons);
}

static void LumaDebugMenu_EditPKMN_SetMonData() {
	struct Pokemon* mons = &LumaDebugMenu_EditPKMN_Data.mon;
	u32 data, i, j, k;
	data = ((LumaDebugMenu_EditPKMN_Data.data[23] - 1) & 3) << 6;
	data |= (LumaDebugMenu_EditPKMN_Data.data[22] & 3) << 4;
	data |= (LumaDebugMenu_EditPKMN_Data.data[24] & 0xf);
	SetMonData(mons, MON_DATA_POKERUS, &data);
	for (i = 0; i < LUMA_EDIT_OPTION_COUNT; i++) {
		switch (i) {
		default:
			SetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, &LumaDebugMenu_EditPKMN_Data.data[i]);
			break;
		case 0 ... 4: // PID and TID, leave alone. 0 is species, which we handle in a different function
		case 6 ... 8: // Nickname (4) and OT name, set by the actual editor; 7-8 are gender and nature (readonly)
		case 15: // Level (set by CalculateMonStats)
		case 22 ... 24: // Pokérus (set above)
		case 26 ... 30: // Current stats (readonly). 31 calls CalculateMonStats
		case 74 ... 76: // PP Up counts (77 sets all at once)
			break;
		case 31: // Stats (and level)
			CalculateMonStats(mons);
			break;
		case 50: // Status
			j = LumaDebugMenu_EditPKMN_Data.data[i];
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
			if (LumaDebugMenu_EditPKMN_Data.data[50] == 4) {
				data = LumaDebugMenu_EditPKMN_Data.data[i];
				SetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, &data);
			}
			break;
		case 52: // Toxic counter
			if (LumaDebugMenu_EditPKMN_Data.data[i] == 6) {
				data = LumaDebugMenu_EditPKMN_Data.data[i] << 8 | STATUS1_TOXIC_POISON;
				SetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, &data);
			}
			break;
		case 63: // Gift ribbons
			data = LumaDebugMenu_EditPKMN_Data.data[i];
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
				data |= (LumaDebugMenu_EditPKMN_Data.data[77 - j] & 3);
			}
			SetMonData(mons, LumaDebugMenu_EditPKMN_Options[74].SetMonDataParam, &data);
			break;
		}
	}
}

static void LumaDebugMenu_EditPKMN_SetDefaults() {
	u32 i;
	for (i = 0; i < LUMA_EDIT_OPTION_COUNT; i++) {
		switch (i) {
		default:
			LumaDebugMenu_EditPKMN_Data.data[i] = LumaDebugMenu_EditPKMN_Options[i].initial;
			break;
		case 1: // PID
			LumaDebugMenu_EditPKMN_Data.data[i] = Random32();
			break;
		case 2: // TID
			LumaDebugMenu_EditPKMN_Data.data[i] = (*(u32*) &gSaveBlock2Ptr->playerTrainerId) & 0xffff;
			break;
		case 3: // SID
			LumaDebugMenu_EditPKMN_Data.data[i] = (*(u32*) &gSaveBlock2Ptr->playerTrainerId) >> 16;
			break;
		case 16: // EXP
			LumaDebugMenu_EditPKMN_Data.data[i] = gExperienceTables[gBaseStats[LumaDebugMenu_EditPKMN_Options[0].initial].growthRate][LumaDebugMenu_EditPKMN_Options[15].initial];
			break;
		}
	}
	LumaDebugMenu_EditPKMN_SetNewMonData(1);
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
			LumaDebugMenu_EditPKMN_Data.data[i] = data >> 16;
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
		case 22: // Pokérus strain
			data = GetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, NULL);
			data &= 0x30;
			data >>= 4;
			LumaDebugMenu_EditPKMN_Data.data[i] = data;
			break;
		case 23: // Pokérus days when spread
			data = GetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, NULL);
			data &= 0xc0;
			data >>= 6;
			LumaDebugMenu_EditPKMN_Data.data[i] = data + 1;
			break;
		case 24: // Pokérus days left
			data = GetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam, NULL);
			data &= 0xf;
			LumaDebugMenu_EditPKMN_Data.data[i] = data;
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
				data <<= 1;
				data |= GetMonData(mons, LumaDebugMenu_EditPKMN_Options[i].SetMonDataParam - 1 + (7 - j), NULL);
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
static const u8 Str_Cursor2Color[] = _("{COLOR DARK_GRAY}{HIGHLIGHT LIGHT_BLUE}");
static const u8 Str_CursorColorOff[] = _("{HIGHLIGHT WHITE}{COLOR GREEN}");
static const u8 Str_JpnCharset[] = _("{JPN}");

static const u8 LumaDebugMenu_Pages[13][7] = {
	{ 0, 16,  2,  1,  6,  4, 0xff},
	{50, 18, 22,  9, 11, 10, 0xff},
	{66, 67, 68, 69, 14, 17, 0xff},
	{32, 33, 34, 35, 36, 37, 0xff},
	{44, 45, 46, 47, 48, 49, 0xff},
	{58, 59, 60, 61, 62, 56, 0xff},
	{53, 54, 55, 57, 63, 64, 0xff},
	{12, 13, 19, 20, 21, 65, 0xff},
	// Below entries are unused.
	{ 3,  5, 70, 71, 72, 73, 0xff},
	{ 7,  8, 74, 75, 76, 77, 0xff},
	{15, 23, 24, 26, 51, 52, 0xff},
	{25, 27, 28, 29, 30, 31, 0xff},
	{38, 39, 40, 41, 42, 43, 0xff},
};

static const u8 LumaDebugMenu_EditPKMN_AltIndexes[14][6][3] = {
	{
		{   7, 0xff, 0xff},
		{  15, 0xff, 0xff},
		{   3,    5, 0xff},
		{   8, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
	},
	{
		{  51,   52, 0xff},
		{0xff, 0xff, 0xff},
		{  23,   24, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
	},
	{
		{  70,   74, 0xff},
		{  71,   75, 0xff},
		{  72,   76, 0xff},
		{  73,   77, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
	},
	{
		{  38,   25,   26},
		{  39,   27, 0xff},
		{  40,   28, 0xff},
		{  41,   29, 0xff},
		{  42,   30, 0xff},
		{  43,   31, 0xff},
	},
	{
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
	},
	{
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
	},
	{
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
	},
	{
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
	},
	// Below entries are unused
	{
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{  74, 0xff, 0xff},
		{  75, 0xff, 0xff},
		{  76, 0xff, 0xff},
		{  77, 0xff, 0xff},
	},
	{
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
	},
	{
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
	},
	{
		{  26, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
	},
	{
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
		{0xff, 0xff, 0xff},
	}
};

extern const u8* const gVersionNames[];
extern const u8* const gLanguageNames[];

static void LumaDebugMenu_EditPKMN_Redraw() {
	u32 i;
	u32 x = 0;
	u32 y = 0;
	u8* bufferPosition;
	const u8* page = LumaDebugMenu_Pages[LumaDebugMenu_EditPKMN_CurrentPage];
	const struct EditPokemonStruct* data;
	u8 index;
	ConvertIntToDecimalStringN(gStringVar1, LumaDebugMenu_EditPKMN_CurrentPage + 1, STR_CONV_MODE_LEFT_ALIGN, 2);
	StringExpandPlaceholders(gStringVar2, Str_Page);
	AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 0, gStringVar2, x, y, 0, NULL);
	if (LumaDebugMenu_EditPKMN_Data.mode >= 1 && LumaDebugMenu_EditPKMN_Data.mode <= 5) {
		x = 100;
		ConvertIntToDecimalStringN(gStringVar1, LumaDebugMenu_EditPKMN_Data.index + 1, STR_CONV_MODE_LEFT_ALIGN, 2);
		StringExpandPlaceholders(gStringVar2, Str_Slot);
		AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 0, gStringVar2, x, y, 0, NULL);
		x = 0;
	}
	y += 16;
	for (i = 0; i < 6; i++) {
		bufferPosition = gStringVar2;
		index = page[i];
		if (index == 0xff) break;
		if (i == LumaDebugMenu_EditPKMN_CurrentlySelectedOption) {
			// Color the currently selected option green
			bufferPosition = StringCopy(bufferPosition, Str_CursorColor);
		}
		data = &LumaDebugMenu_EditPKMN_Options[index];
		switch (index) {
		default:
			switch (data->mode) {
			case LUMA_EDIT_NORMAL:
			case LUMA_EDIT_READONLY:
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
				StringCopyN(gStringVar1, (u8*) LumaDebugMenu_EditPKMN_Data.data[index], data->digitCount);
				// Pokémon names can sometimes be unterminated, so add an extra terminator here
				gStringVar1[data->digitCount] = EOS;
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
		case 0: // Species
			ConvertIntToDecimalStringN(gStringVar1, LumaDebugMenu_EditPKMN_Data.data[index], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
			if (data->text != NULL) {
				bufferPosition = StringCopy(bufferPosition, data->text);
				bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
			}
			*gStringVar3 = EOS;
			StringExpandPlaceholders(bufferPosition, Str_StringVars);
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 7, gStringVar2, x, y, 0, NULL);
			x = 140;
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 1, gSpeciesNames[LumaDebugMenu_EditPKMN_Data.data[index]], x, y, 0, NULL);
			x = 204;
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 7, GenderIndexes[LumaDebugMenu_EditPKMN_Data.data[7]], x, y, 0, NULL);
			x = 0;
			y+= 16;
			break;
		case 1: // PID
			ConvertUIntToHexStringN(gStringVar1, LumaDebugMenu_EditPKMN_Data.data[index], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
			if (data->text != NULL) {
				bufferPosition = StringCopy(bufferPosition, data->text);
				bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
			}
			bufferPosition = StringCopy(bufferPosition, Str_HexPrefix);
			*gStringVar3 = EOS;
			StringExpandPlaceholders(bufferPosition, Str_StringVars);
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 7, gStringVar2, x, y, 0, NULL);
			x = 165;
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 1, gNatureNamePointers[LumaDebugMenu_EditPKMN_Data.data[8]], x, y, 0, NULL);
			x = 0;
			y+= 16;
			break;
		case 5: // OT Gender
		case 7: // Gender
			StringCopy(gStringVar1, GenderIndexes[LumaDebugMenu_EditPKMN_Data.data[index]]);
			if (data->text != NULL) {
				bufferPosition = StringCopy(bufferPosition, data->text);
				bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
			}
			*gStringVar3 = EOS;
			StringExpandPlaceholders(bufferPosition, Str_StringVars);
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 7, gStringVar2, x, y, 0, NULL);
			y += 16;
			break;
		case 13: // Origin Game
			ConvertIntToDecimalStringN(gStringVar1, LumaDebugMenu_EditPKMN_Data.data[index], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
			if (data->text != NULL) {
				bufferPosition = StringCopy(bufferPosition, data->text);
				bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
			}
			*gStringVar3 = EOS;
			StringExpandPlaceholders(bufferPosition, Str_StringVars);
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 7, gStringVar2, x, y, 0, NULL);
			x = 130;
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 1, gVersionNames[LumaDebugMenu_EditPKMN_Data.data[index]], x, y, 0, NULL);
			x = 0;
			y+= 16;
			break;
		case 14: // Held Item
			ConvertIntToDecimalStringN(gStringVar1, LumaDebugMenu_EditPKMN_Data.data[index], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
			if (data->text != NULL) {
				bufferPosition = StringCopy(bufferPosition, data->text);
				bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
			}
			*gStringVar3 = EOS;
			StringExpandPlaceholders(bufferPosition, Str_StringVars);
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 7, gStringVar2, x, y, 0, NULL);
			x = 145;
			CopyItemName(LumaDebugMenu_EditPKMN_Data.data[index], gStringVar1);
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 1, gStringVar1, x, y, 0, NULL);
			x = 0;
			y+= 16;
			break;
		case 17: // Ability
			StringCopy(gStringVar1, gAbilityNames[GetAbilityBySpecies(LumaDebugMenu_EditPKMN_Data.data[0], LumaDebugMenu_EditPKMN_Data.data[index])]);
			if (data->text != NULL) {
				bufferPosition = StringCopy(bufferPosition, data->text);
				bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
			}
			*gStringVar3 = EOS;
			StringExpandPlaceholders(bufferPosition, Str_StringVars);
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 7, gStringVar2, x, y, 0, NULL);
			y += 16;
			break;
		case 20: // Met Location
			ConvertIntToDecimalStringN(gStringVar1, LumaDebugMenu_EditPKMN_Data.data[index], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
			if (data->text != NULL) {
				bufferPosition = StringCopy(bufferPosition, data->text);
				bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
			}
			*gStringVar3 = EOS;
			StringExpandPlaceholders(bufferPosition, Str_StringVars);
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 7, gStringVar2, x, y, 0, NULL);
			x = 130;
			GetMapName_HandleVersion(gStringVar1, LumaDebugMenu_EditPKMN_Data.data[index], LumaDebugMenu_EditPKMN_Data.data[13]);
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 1, gStringVar1, x, y, 0, NULL);
			x = 0;
			y+= 16;
			break;
		case 21: // Ball
			ConvertIntToDecimalStringN(gStringVar1, LumaDebugMenu_EditPKMN_Data.data[index], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
			if (data->text != NULL) {
				bufferPosition = StringCopy(bufferPosition, data->text);
				bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
			}
			*gStringVar3 = EOS;
			StringExpandPlaceholders(bufferPosition, Str_StringVars);
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 7, gStringVar2, x, y, 0, NULL);
			x = 130;
			CopyItemName(LumaDebugMenu_EditPKMN_Data.data[index], gStringVar1);
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 1, gStringVar1, x, y, 0, NULL);
			x = 0;
			y+= 16;
			break;
		case 66 ... 69: // Moves
			ConvertIntToDecimalStringN(gStringVar1, LumaDebugMenu_EditPKMN_Data.data[index], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
			if (data->text != NULL) {
				bufferPosition = StringCopy(bufferPosition, data->text);
				*bufferPosition = CHAR_SPACE;
				bufferPosition++;
				*bufferPosition = CHAR_1 + (index - 66);
				bufferPosition++;
				bufferPosition = StringCopy(bufferPosition, Str_Spacer1);
			}
			*gStringVar3 = EOS;
			StringExpandPlaceholders(bufferPosition, Str_StringVars);
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 7, gStringVar2, x, y, 0, NULL);
			x = 120;
			ConvertIntToDecimalStringN(gStringVar1, LumaDebugMenu_EditPKMN_Data.data[70 + (index - 66)], STR_CONV_MODE_LEADING_ZEROS, 2);
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 7, gStringVar1, x, y, 0, NULL);
			x = 135;
			ConvertIntToDecimalStringN(gStringVar1, LumaDebugMenu_EditPKMN_Data.data[74 + (index - 66)], STR_CONV_MODE_LEADING_ZEROS, 1);
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 7, gStringVar1, x, y, 0, NULL);
			x = 145;
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 1, gMoveNames[LumaDebugMenu_EditPKMN_Data.data[index]], x, y, 0, NULL);
			x = 0;
			y+= 16;
			break;
		}
		/* TODO: Add non-default cases:
			* Experience (level)
			* TID (SID)
			* PID (Nature, is shiny)
			* Status (status name, sleep/toxic counter)
			* Pokérus (counters)
			* IVs (label override, EVs, current, current HP)
			* EVs (label override, IVs, current, current HP)
			* Stats (label override, current HP, IVs, EVs)
			* Language (language name)
			* Nature (nature name)
		*/
	}
}

static u32 LumaDebugMenu_EditPKMN_editingVal[4];

static void LumaDebugMenu_AddEditPKMN_ProcessInput(u8 taskid) {
	u16 keys = gMain.newKeys;
	struct Task* task = &gTasks[taskid];
	struct Pokemon* mons;

	if (keys & DPAD_LEFT) {
		if (LumaDebugMenu_EditPKMN_CurrentPage > 0) {
			LumaDebugMenu_EditPKMN_CurrentPage--;
		}
		else {
			LumaDebugMenu_EditPKMN_CurrentPage = 12;
		}
		FillWindowPixelBuffer(LumaDebugMenu_EditPKMN_menuWindowId, 0x11);
		LumaDebugMenu_EditPKMN_Redraw();
		PlaySE(SE_SELECT);
		return;
	}
	if (keys & DPAD_RIGHT) {
		if (LumaDebugMenu_EditPKMN_CurrentPage < 12) {
			LumaDebugMenu_EditPKMN_CurrentPage++;
		}
		else {
			LumaDebugMenu_EditPKMN_CurrentPage = 0;
		}
		FillWindowPixelBuffer(LumaDebugMenu_EditPKMN_menuWindowId, 0x11);
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
		switch (LumaDebugMenu_EditPKMN_Data.mode) {
		case 2:
			// We can technically select slot 404 of box 1 (actually box 13 slot 14) but it's still valid behavior provided the max index was set properly above.
			mons = (struct Pokemon*) &gPokemonStoragePtr->boxes[0][LumaDebugMenu_EditPKMN_Data.index];
			LumaDebugMenu_EditPKMN_Data.monBeingEdited = mons;
			CopyMon(&LumaDebugMenu_EditPKMN_Data.mon, mons, sizeof(struct BoxPokemon));
			CalculateMonStats(&LumaDebugMenu_EditPKMN_Data.mon);
			break;
		case 1:
		case 5:
			mons = &gPlayerParty[LumaDebugMenu_EditPKMN_Data.index];
			LumaDebugMenu_EditPKMN_Data.monBeingEdited = mons;
			CopyMon(&LumaDebugMenu_EditPKMN_Data.mon, mons, sizeof(struct Pokemon));
			break;
		case 3:
		case 4:
			mons = &gEnemyParty[LumaDebugMenu_EditPKMN_Data.index];
			LumaDebugMenu_EditPKMN_Data.monBeingEdited = mons;
			CopyMon(&LumaDebugMenu_EditPKMN_Data.mon, mons, sizeof(struct Pokemon));
			break;
		default:
			break;
		}
		LumaDebugMenu_EditPKMN_PopulateData();
		FillWindowPixelBuffer(LumaDebugMenu_EditPKMN_menuWindowId, 0x11);
		LumaDebugMenu_EditPKMN_Redraw();
		PlaySE(SE_SELECT);
		return;
	}
	if (keys & R_BUTTON) {
		u32 max_index;
		switch (LumaDebugMenu_EditPKMN_Data.mode) {
		case 0:
		case 6 ... 8:
		default:
			return;
		case 1:
		case 3 ... 5:
			max_index = PARTY_SIZE;
			break;
		case 2:
			max_index = TOTAL_BOXES_COUNT * IN_BOX_COUNT;
			break;
		}
		if (LumaDebugMenu_EditPKMN_Data.index >= max_index - 1) return;
		LumaDebugMenu_EditPKMN_Data.index++;
		switch (LumaDebugMenu_EditPKMN_Data.mode) {
		case 2:
			mons = (struct Pokemon*) &gPokemonStoragePtr->boxes[0][LumaDebugMenu_EditPKMN_Data.index];
			LumaDebugMenu_EditPKMN_Data.monBeingEdited = mons;
			CopyMon(&LumaDebugMenu_EditPKMN_Data.mon, mons, sizeof(struct BoxPokemon));
			CalculateMonStats(&LumaDebugMenu_EditPKMN_Data.mon);
			break;
		case 1:
		case 5:
			mons = &gPlayerParty[LumaDebugMenu_EditPKMN_Data.index];
			LumaDebugMenu_EditPKMN_Data.monBeingEdited = mons;
			CopyMon(&LumaDebugMenu_EditPKMN_Data.mon, mons, sizeof(struct Pokemon));
			break;
		case 3:
		case 4:
			mons = &gEnemyParty[LumaDebugMenu_EditPKMN_Data.index];
			LumaDebugMenu_EditPKMN_Data.monBeingEdited = mons;
			CopyMon(&LumaDebugMenu_EditPKMN_Data.mon, mons, sizeof(struct Pokemon));
			break;
		}
		LumaDebugMenu_EditPKMN_PopulateData();
		FillWindowPixelBuffer(LumaDebugMenu_EditPKMN_menuWindowId, 0x11);
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
		EnableBothScriptContexts();
		PlaySE(SE_SELECT);
		return;
	}
	if (keys & SELECT_BUTTON) {
		// TODO: Re-randomize the PID and IVs, or if OT is selected, toggle OT gender
		return;
	}
	if (keys & A_BUTTON) {
		u32 i;
		u8 index = LumaDebugMenu_Pages[LumaDebugMenu_EditPKMN_CurrentPage][LumaDebugMenu_EditPKMN_CurrentlySelectedOption];
		if (LumaDebugMenu_EditPKMN_Options[index].mode != LUMA_EDIT_NULL && LumaDebugMenu_EditPKMN_Options[index].mode != LUMA_EDIT_READONLY) {
			LumaDebugMenu_EditPKMN_editingVal[0] = LumaDebugMenu_EditPKMN_Data.data[index];
			if (LumaDebugMenu_EditPKMN_Options[index].mode == LUMA_EDIT_STRING) {
				StringCopyN(LumaDebugMenu_EditPKMN_NameBuffer, (u8*) LumaDebugMenu_EditPKMN_editingVal[0], 16);
				LumaDebugMenu_EditPKMN_NameBuffer[LumaDebugMenu_EditPKMN_Options[index].digitCount] = EOS;
			}
			for (i = 1; i < 3; i++) {
				if (LumaDebugMenu_EditPKMN_AltIndexes[LumaDebugMenu_EditPKMN_CurrentPage][LumaDebugMenu_EditPKMN_CurrentlySelectedOption][i - 1] == 0xff) break;
				LumaDebugMenu_EditPKMN_editingVal[i] = LumaDebugMenu_EditPKMN_Data.data[LumaDebugMenu_EditPKMN_AltIndexes[LumaDebugMenu_EditPKMN_CurrentPage][LumaDebugMenu_EditPKMN_CurrentlySelectedOption][i - 1]];
			}
			task->data[0] = 0;
			task->data[1] = 0;
			LumaDebugMenu_EditPKMN_EditModeRedraw(task->data[0], task->data[1]);
			task->func = LumaDebugMenu_EditPKMN_EditModeProcessInput;
			PlaySE(SE_SELECT);
		}
		return;
	}
	if (keys & START_BUTTON) {
		LumaDebugMenu_EditPKMN_SetMonData();
		// TODO: Add a confirmation prompt
		if (LumaDebugMenu_AddEditPKMN_GiveToPlayer() != MON_CANT_GIVE)
			PlaySE(SE_EXP_MAX);
		else PlaySE(SE_BOO);
		return;
	}
}

static const u32 powersOf10[10] = {
	1,
	10,
	100,
	1000,
	10000,
	100000,
	1000000,
	10000000,
	100000000,
	1000000000,
};

static void LumaDebugMenu_EditPKMN_EditModeProcessInput(u8 taskid) {
	u16 keys = gMain.newKeys;
	u16 heldKeys = gMain.newAndRepeatedKeys;
	struct Task* task = &gTasks[taskid];
	u32 i, min, max;
	u32 z = 0;

	u16 digit = task->data[0];
	u16 editIndex = task->data[1];

	u32 x = 100;
	u32 y = LumaDebugMenu_EditPKMN_CurrentlySelectedOption * 2 * 8 + 16;

	u8 index;

	const struct EditPokemonStruct* data;
	const u8* page = LumaDebugMenu_Pages[LumaDebugMenu_EditPKMN_CurrentPage];

	if (editIndex != 0 && LumaDebugMenu_EditPKMN_AltIndexes[LumaDebugMenu_EditPKMN_CurrentPage][LumaDebugMenu_EditPKMN_CurrentlySelectedOption][editIndex - 1] != 0xff) {
		index = LumaDebugMenu_EditPKMN_AltIndexes[LumaDebugMenu_EditPKMN_CurrentPage][LumaDebugMenu_EditPKMN_CurrentlySelectedOption][editIndex - 1];
	}
	else {
		index = page[LumaDebugMenu_EditPKMN_CurrentlySelectedOption];
	}

	data = &LumaDebugMenu_EditPKMN_Options[index];

	switch (index) {
	default:
		min = data->min;
		max = data->max;
		break;
	}

	if (keys & B_BUTTON) {
		FillWindowPixelRect(LumaDebugMenu_EditPKMN_menuWindowId, 0x11, x, y, 124, 16);
		LumaDebugMenu_EditPKMN_Redraw();
		task->func = LumaDebugMenu_AddEditPKMN_ProcessInput;
		PlaySE(SE_SELECT);
		return;
	}

	if (keys & (A_BUTTON | START_BUTTON)) {
		// TODO: This works just as well... but for sanity's sake, call SetMonData properly
		if (data->mode == LUMA_EDIT_STRING)
			StringCopyN((u8*) LumaDebugMenu_EditPKMN_Data.data[index], LumaDebugMenu_EditPKMN_NameBuffer, data->digitCount);
		else {
			index = page[LumaDebugMenu_EditPKMN_CurrentlySelectedOption]; // Level/EXP mismatch hotfix 1
#define indexBeingEdited min
			for (i = 0; i < 4; i++) {
				if (i == 4) break;
				if (i != 0)
					indexBeingEdited = LumaDebugMenu_EditPKMN_AltIndexes[LumaDebugMenu_EditPKMN_CurrentPage][LumaDebugMenu_EditPKMN_CurrentlySelectedOption][i - 1];
				else indexBeingEdited = index;
				if (indexBeingEdited == 0xff)
					continue;
				if (LumaDebugMenu_EditPKMN_Data.data[indexBeingEdited] == LumaDebugMenu_EditPKMN_editingVal[i])
					continue;
				data = &LumaDebugMenu_EditPKMN_Options[indexBeingEdited];
				if (data->mode == LUMA_EDIT_READONLY)
					continue;
				LumaDebugMenu_EditPKMN_Data.data[indexBeingEdited] = LumaDebugMenu_EditPKMN_editingVal[i];
				switch (indexBeingEdited) {
				default:
					LumaDebugMenu_EditPKMN_SetMonData();
					LumaDebugMenu_EditPKMN_PopulateData();
					break;
				case 0:
					LumaDebugMenu_EditPKMN_SetMonData();
					SetMonData(&LumaDebugMenu_EditPKMN_Data.mon, data->SetMonDataParam, &LumaDebugMenu_EditPKMN_editingVal[i]);
					SetMonData(&LumaDebugMenu_EditPKMN_Data.mon, MON_DATA_NICKNAME, gSpeciesNames[LumaDebugMenu_EditPKMN_editingVal[i]]);
					// Clear moves
					SetMonData(&LumaDebugMenu_EditPKMN_Data.mon, MON_DATA_MOVE1, &z);
					SetMonData(&LumaDebugMenu_EditPKMN_Data.mon, MON_DATA_MOVE2, &z);
					SetMonData(&LumaDebugMenu_EditPKMN_Data.mon, MON_DATA_MOVE3, &z);
					SetMonData(&LumaDebugMenu_EditPKMN_Data.mon, MON_DATA_MOVE4, &z);
					SetMonData(&LumaDebugMenu_EditPKMN_Data.mon, MON_DATA_PP1, &z);
					SetMonData(&LumaDebugMenu_EditPKMN_Data.mon, MON_DATA_PP2, &z);
					SetMonData(&LumaDebugMenu_EditPKMN_Data.mon, MON_DATA_PP3, &z);
					SetMonData(&LumaDebugMenu_EditPKMN_Data.mon, MON_DATA_PP4, &z);
					GiveMonInitialMoveset(&LumaDebugMenu_EditPKMN_Data.mon);
					// preserve level
					SetMonData(&LumaDebugMenu_EditPKMN_Data.mon, MON_DATA_EXP, &gExperienceTables[gBaseStats[LumaDebugMenu_EditPKMN_editingVal[i]].growthRate][LumaDebugMenu_EditPKMN_Data.data[15]]);
					CalculateMonStats(&LumaDebugMenu_EditPKMN_Data.mon);
					// preserve sanity bit
					SetMonData(&LumaDebugMenu_EditPKMN_Data.mon, MON_DATA_SANITY_HAS_SPECIES, &LumaDebugMenu_EditPKMN_Data.data[11]);
					LumaDebugMenu_EditPKMN_PopulateData();
					break;
				case 1 ... 3:
					LumaDebugMenu_EditPKMN_SetNewMonData(0);
					LumaDebugMenu_EditPKMN_PopulateData();
					break;
				case 15:
					LumaDebugMenu_EditPKMN_SetMonData();
					SetMonData(&LumaDebugMenu_EditPKMN_Data.mon, MON_DATA_EXP, &gExperienceTables[gBaseStats[LumaDebugMenu_EditPKMN_Data.data[0]].growthRate][LumaDebugMenu_EditPKMN_editingVal[i]]);
					CalculateMonStats(&LumaDebugMenu_EditPKMN_Data.mon);
					LumaDebugMenu_EditPKMN_PopulateData();
					break;
				case 16:
				case 32 ... 43:
					LumaDebugMenu_EditPKMN_SetMonData();
					SetMonData(&LumaDebugMenu_EditPKMN_Data.mon, data->SetMonDataParam, &LumaDebugMenu_EditPKMN_editingVal[i]);
					CalculateMonStats(&LumaDebugMenu_EditPKMN_Data.mon);
					LumaDebugMenu_EditPKMN_PopulateData();
					/* Level/EXP hotfix #2 */
					if (indexBeingEdited == 16) {
#define j max
						for (j = 0; j < 2; j++) {
							if (LumaDebugMenu_EditPKMN_AltIndexes[LumaDebugMenu_EditPKMN_CurrentPage][LumaDebugMenu_EditPKMN_CurrentlySelectedOption][j] == 15) {
								LumaDebugMenu_EditPKMN_editingVal[j + 1] = LumaDebugMenu_EditPKMN_Data.data[LumaDebugMenu_EditPKMN_AltIndexes[LumaDebugMenu_EditPKMN_CurrentPage][LumaDebugMenu_EditPKMN_CurrentlySelectedOption][j]]; // Re-enter the recalculated level.
							}
						}
					}
#undef j
					break;
				}
			}
#undef indexBeingEdited
		}
		FillWindowPixelRect(LumaDebugMenu_EditPKMN_menuWindowId, 0x11, x, y, data->digitCount * 8, 16);
		LumaDebugMenu_EditPKMN_Redraw();
		task->func = LumaDebugMenu_AddEditPKMN_ProcessInput;
		PlaySE(SE_SELECT);
		return;
	}
	if (heldKeys & DPAD_UP) {
		if (index == 1) { // PID does have a min/max, but they cover the entire 32-bit value range.
			LumaDebugMenu_EditPKMN_editingVal[editIndex] += (1 << (4 * digit));
			LumaDebugMenu_EditPKMN_EditModeRedraw(digit, editIndex);
			PlaySE(SE_SELECT);
			return;
		}
		switch (data->mode) {
		case LUMA_EDIT_NORMAL:
		default:
			if (LumaDebugMenu_EditPKMN_editingVal[editIndex] + powersOf10[digit] > max)
				LumaDebugMenu_EditPKMN_editingVal[editIndex] = data->min;
			else
				LumaDebugMenu_EditPKMN_editingVal[editIndex] += powersOf10[digit];
			break;
		case LUMA_EDIT_NULL:
		case LUMA_EDIT_READONLY:
			return;
		case LUMA_EDIT_BOOL:
			if (LumaDebugMenu_EditPKMN_editingVal[editIndex]) return;
			LumaDebugMenu_EditPKMN_editingVal[editIndex] = TRUE;
			break;
		case LUMA_EDIT_HEX:
			if (LumaDebugMenu_EditPKMN_editingVal[editIndex] + (1 << (4 * digit)) > max)
				LumaDebugMenu_EditPKMN_editingVal[editIndex] = data->min;
			else
				LumaDebugMenu_EditPKMN_editingVal[editIndex] += (1 << (4 * digit));
			break;
		case LUMA_EDIT_STRING:
			LumaDebugMenu_EditPKMN_NameBuffer[digit]++;
			LumaDebugMenu_EditPKMN_NameBuffer[digit] &= 0xff;
			if (LumaDebugMenu_EditPKMN_NameBuffer[digit] >= CHAR_DYNAMIC) {
				LumaDebugMenu_EditPKMN_NameBuffer[digit] = EOS;
			}
			else if (LumaDebugMenu_EditPKMN_NameBuffer[digit] >= CHAR_DYNAMIC && LumaDebugMenu_EditPKMN_NameBuffer[digit] < EOS) {
				LumaDebugMenu_EditPKMN_NameBuffer[digit] = 0;
			}
			break;
		}
		LumaDebugMenu_EditPKMN_EditModeRedraw(digit, editIndex);
		PlaySE(SE_SELECT);
		return;
	}
	if (heldKeys & DPAD_DOWN) {
		if (index == 1) {
			LumaDebugMenu_EditPKMN_editingVal[editIndex] -= (1 << (4 * digit));
			LumaDebugMenu_EditPKMN_EditModeRedraw(digit, editIndex);
			PlaySE(SE_SELECT);
			return;
		}
		switch (data->mode) {
		case LUMA_EDIT_NORMAL:
		default:
			if ((s32) (LumaDebugMenu_EditPKMN_editingVal[editIndex] - powersOf10[digit]) < (s32) min)
				LumaDebugMenu_EditPKMN_editingVal[editIndex] = data->max;
			else
				LumaDebugMenu_EditPKMN_editingVal[editIndex] -= powersOf10[digit];
			break;
		case LUMA_EDIT_NULL:
		case LUMA_EDIT_READONLY:
			return;
		case LUMA_EDIT_BOOL:
			if (!LumaDebugMenu_EditPKMN_editingVal[editIndex]) return;
			LumaDebugMenu_EditPKMN_editingVal[editIndex] = FALSE;
			break;
		case LUMA_EDIT_HEX:
			if ((s32) (LumaDebugMenu_EditPKMN_editingVal[editIndex] - (1 << (4 * digit))) < (s32) min)
				LumaDebugMenu_EditPKMN_editingVal[editIndex] = data->max;
			else
				LumaDebugMenu_EditPKMN_editingVal[editIndex] -= (1 << (4 * digit));
			break;
		case LUMA_EDIT_STRING:
			LumaDebugMenu_EditPKMN_NameBuffer[digit]--;
			LumaDebugMenu_EditPKMN_NameBuffer[digit] &= 0xff;
			if (LumaDebugMenu_EditPKMN_NameBuffer[digit] >= CHAR_DYNAMIC && LumaDebugMenu_EditPKMN_NameBuffer[digit] < EOS) {
				LumaDebugMenu_EditPKMN_NameBuffer[digit] = CHAR_DYNAMIC - 1;
			}
			break;
		}
		LumaDebugMenu_EditPKMN_EditModeRedraw(digit, editIndex);
		PlaySE(SE_SELECT);
		return;
	}
	if (keys & DPAD_LEFT) {
		if (data->mode == LUMA_EDIT_STRING) {
			if ((s16) (digit - 1) < 0) {
				if ((editIndex != 0 && LumaDebugMenu_EditPKMN_AltIndexes[LumaDebugMenu_EditPKMN_CurrentPage][LumaDebugMenu_EditPKMN_CurrentlySelectedOption][editIndex - 2] != 0xff) || editIndex == 1) {
					LumaDebugMenu_EditPKMN_EditModeRedraw(data->digitCount, editIndex);
					digit = LumaDebugMenu_EditPKMN_Options[LumaDebugMenu_EditPKMN_AltIndexes[LumaDebugMenu_EditPKMN_CurrentPage][LumaDebugMenu_EditPKMN_CurrentlySelectedOption][editIndex]].digitCount - 1;
					editIndex--;
				}
				else return;
			}
			else digit--;
		}
		else {
			if (digit >= data->digitCount - 1) {
				if ((editIndex != 0 && LumaDebugMenu_EditPKMN_AltIndexes[LumaDebugMenu_EditPKMN_CurrentPage][LumaDebugMenu_EditPKMN_CurrentlySelectedOption][editIndex - 2] != 0xff) || editIndex == 1) {
					LumaDebugMenu_EditPKMN_EditModeRedraw(data->digitCount, editIndex);
					digit = 0;
					editIndex--;
				}
				else return;
			}
			else digit++;
		}
		LumaDebugMenu_EditPKMN_EditModeRedraw(digit, editIndex);
		task->data[0] = digit;
		task->data[1] = editIndex;
		PlaySE(SE_SELECT);
		return;
	}
	if (keys & DPAD_RIGHT) {
		if (data->mode == LUMA_EDIT_STRING) {
			if (digit >= data->digitCount - 1) {
				if (editIndex + 1 < 4 && LumaDebugMenu_EditPKMN_AltIndexes[LumaDebugMenu_EditPKMN_CurrentPage][LumaDebugMenu_EditPKMN_CurrentlySelectedOption][editIndex] != 0xff) {
					LumaDebugMenu_EditPKMN_EditModeRedraw(data->digitCount, editIndex);
					digit = 0;
					editIndex++;
				}
				else return;
			}
			else digit++;
		}
		else {
			if ((s16) (digit - 1) < 0) {
				if (editIndex + 1 < 4 && LumaDebugMenu_EditPKMN_AltIndexes[LumaDebugMenu_EditPKMN_CurrentPage][LumaDebugMenu_EditPKMN_CurrentlySelectedOption][editIndex] != 0xff && LumaDebugMenu_EditPKMN_Options[LumaDebugMenu_EditPKMN_AltIndexes[LumaDebugMenu_EditPKMN_CurrentPage][LumaDebugMenu_EditPKMN_CurrentlySelectedOption][editIndex]].mode != LUMA_EDIT_READONLY) {
					LumaDebugMenu_EditPKMN_EditModeRedraw(data->digitCount, editIndex);
					digit = LumaDebugMenu_EditPKMN_Options[LumaDebugMenu_EditPKMN_AltIndexes[LumaDebugMenu_EditPKMN_CurrentPage][LumaDebugMenu_EditPKMN_CurrentlySelectedOption][editIndex]].digitCount - 1;
					editIndex++;
				}
				else return;
			}
			else digit--;
		}
		LumaDebugMenu_EditPKMN_EditModeRedraw(digit, editIndex);
		task->data[0] = digit;
		task->data[1] = editIndex;
		PlaySE(SE_SELECT);
		return;
	}
	// TODO: Select resets the value to default
}

static void LumaDebugMenu_EditPKMN_EditModeRedraw(u32 digit, u8 editIndex) {
	u32 x = 100;
	u32 y = LumaDebugMenu_EditPKMN_CurrentlySelectedOption * 2 * 8 + 16;
	u32 i = 0;
	u8* bufferPosition = gStringVar2;
	const u8* page = LumaDebugMenu_Pages[LumaDebugMenu_EditPKMN_CurrentPage];
	const struct EditPokemonStruct* data;
	u8 index;
	u32 digitToHighlight;

	if (editIndex != 0 && LumaDebugMenu_EditPKMN_AltIndexes[LumaDebugMenu_EditPKMN_CurrentPage][LumaDebugMenu_EditPKMN_CurrentlySelectedOption][editIndex - 1] != 0xff) {
		index = LumaDebugMenu_EditPKMN_AltIndexes[LumaDebugMenu_EditPKMN_CurrentPage][LumaDebugMenu_EditPKMN_CurrentlySelectedOption][editIndex - 1];
		x += 5 * 8 * editIndex;
	}
	else {
		index = page[LumaDebugMenu_EditPKMN_CurrentlySelectedOption];
	}

	data = &LumaDebugMenu_EditPKMN_Options[index];

	switch (index) {
	default:
		switch (data->mode) {
		case LUMA_EDIT_NORMAL:
		default:
			FillWindowPixelRect(LumaDebugMenu_EditPKMN_menuWindowId, 0x11, x, y, data->digitCount * 8, 16);
			ConvertIntToDecimalStringN(gStringVar1, LumaDebugMenu_EditPKMN_editingVal[editIndex], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
			break;
		case LUMA_EDIT_HEX:
			FillWindowPixelRect(LumaDebugMenu_EditPKMN_menuWindowId, 0x11, x, y, data->digitCount * 8, 16);
			ConvertUIntToHexStringN(gStringVar1, LumaDebugMenu_EditPKMN_editingVal[editIndex], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
			bufferPosition = StringCopy(bufferPosition, Str_CursorColor);
			bufferPosition = StringCopy(bufferPosition, Str_HexPrefix);
			break;
		case LUMA_EDIT_NULL:
			return; // Haha, don't even make the effort...
		case LUMA_EDIT_BOOL:
			FillWindowPixelRect(LumaDebugMenu_EditPKMN_menuWindowId, 0x11, x, y, 24, 16);
			bufferPosition = StringCopy(bufferPosition, Str_Cursor2Color);
			bufferPosition = StringCopy(bufferPosition, LumaDebugMenu_EditPKMN_editingVal[editIndex] ? Str_On : Str_Off);
			*bufferPosition = EOS;
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 7, gStringVar2, x, y, 0, NULL);
			return;
		case LUMA_EDIT_STRING:
			FillWindowPixelRect(LumaDebugMenu_EditPKMN_menuWindowId, 0x11, x, y, data->digitCount * 8, 16);
			StringCopyN(gStringVar1, LumaDebugMenu_EditPKMN_NameBuffer, data->digitCount);
			break;
		}
		break;
	case 0: // Species
		// Same as the default case, except we draw more data here
		FillWindowPixelRect(LumaDebugMenu_EditPKMN_menuWindowId, 0x11, x, y, data->digitCount * 8, 16);
		ConvertIntToDecimalStringN(gStringVar1, LumaDebugMenu_EditPKMN_editingVal[editIndex], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
		if (editIndex == 0) {
			x = 140;
			FillWindowPixelRect(LumaDebugMenu_EditPKMN_menuWindowId, 0x11, x, y, 72, 16);
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 1, gSpeciesNames[LumaDebugMenu_EditPKMN_editingVal[editIndex]], x, y, 0, NULL);
			x = 204;
			i = GetGenderFromSpeciesAndPersonality(LumaDebugMenu_EditPKMN_editingVal[editIndex], LumaDebugMenu_EditPKMN_Data.data[1]);
			if (i == MON_FEMALE) i = 1;
			else if (i == MON_GENDERLESS) i = 2;
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 7, GenderIndexes[i], x, y, 0, NULL);
			x = 100; // Reset for the actual species number
		}
		break;
	case 5: // OT Gender
	case 7: // Gender
		if (editIndex != 0 && page[LumaDebugMenu_EditPKMN_CurrentlySelectedOption] == 0)
			x = 204;
		FillWindowPixelRect(LumaDebugMenu_EditPKMN_menuWindowId, 0x11, x, y, 8, 16);
		bufferPosition = StringCopy(bufferPosition, Str_Cursor2Color);
		bufferPosition = StringCopy(bufferPosition, GenderIndexes[LumaDebugMenu_EditPKMN_editingVal[editIndex]]);
		*bufferPosition = EOS;
		AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 7, gStringVar2, x, y, 0, NULL);
		return;
	case 13: // Origin Game
		FillWindowPixelRect(LumaDebugMenu_EditPKMN_menuWindowId, 0x11, x, y, data->digitCount * 8, 16);
		ConvertIntToDecimalStringN(gStringVar1, LumaDebugMenu_EditPKMN_editingVal[editIndex], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
		if (editIndex == 0) {
			x = 130;
			// TODO: Fill all the way to the end?
			FillWindowPixelRect(LumaDebugMenu_EditPKMN_menuWindowId, 0x11, x, y, 120, 16);
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 1, gVersionNames[LumaDebugMenu_EditPKMN_editingVal[editIndex]], x, y, 0, NULL);
			x = 100;
		}
		break;
	case 14: // Held Item
		FillWindowPixelRect(LumaDebugMenu_EditPKMN_menuWindowId, 0x11, x, y, data->digitCount * 8, 16);
		ConvertIntToDecimalStringN(gStringVar1, LumaDebugMenu_EditPKMN_editingVal[editIndex], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
		if (editIndex == 0) {
			x = 145;
			// TODO: Fill all the way to the end?
			FillWindowPixelRect(LumaDebugMenu_EditPKMN_menuWindowId, 0x11, x, y, 120, 16);
			CopyItemName(LumaDebugMenu_EditPKMN_editingVal[editIndex], gStringVar2);
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 1, gStringVar2, x, y, 0, NULL);
			x = 100;
		}
		break;
	case 17: // Ability
		if (editIndex != 0 && page[LumaDebugMenu_EditPKMN_CurrentlySelectedOption] == 0)
			x = 204;
		// TODO: Fill all the way to the end?
		FillWindowPixelRect(LumaDebugMenu_EditPKMN_menuWindowId, 0x11, x, y, 120, 16);
		bufferPosition = StringCopy(bufferPosition, Str_Cursor2Color);
		bufferPosition = StringCopy(bufferPosition, gAbilityNames[GetAbilityBySpecies(LumaDebugMenu_EditPKMN_Data.data[0], LumaDebugMenu_EditPKMN_editingVal[editIndex])]);
		*bufferPosition = EOS;
		AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 7, gStringVar2, x, y, 0, NULL);
		return;
	case 20: // Met Location
		FillWindowPixelRect(LumaDebugMenu_EditPKMN_menuWindowId, 0x11, x, y, data->digitCount * 8, 16);
		ConvertIntToDecimalStringN(gStringVar1, LumaDebugMenu_EditPKMN_editingVal[editIndex], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
		if (editIndex == 0) {
			x = 130;
			// TODO: Fill all the way to the end?
			FillWindowPixelRect(LumaDebugMenu_EditPKMN_menuWindowId, 0x11, x, y, 120, 16);
			GetMapName_HandleVersion(gStringVar2, LumaDebugMenu_EditPKMN_editingVal[editIndex], LumaDebugMenu_EditPKMN_Data.data[13]);
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 1, gStringVar2, x, y, 0, NULL);
			x = 100;
		}
		break;
	case 21: // Ball
		FillWindowPixelRect(LumaDebugMenu_EditPKMN_menuWindowId, 0x11, x, y, data->digitCount * 8, 16);
		ConvertIntToDecimalStringN(gStringVar1, LumaDebugMenu_EditPKMN_editingVal[editIndex], STR_CONV_MODE_LEADING_ZEROS, data->digitCount);
		if (editIndex == 0) {
			x = 130;
			// TODO: Fill all the way to the end?
			FillWindowPixelRect(LumaDebugMenu_EditPKMN_menuWindowId, 0x11, x, y, 120, 16);
			CopyItemName(LumaDebugMenu_EditPKMN_editingVal[editIndex], gStringVar2);
			AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 1, gStringVar2, x, y, 0, NULL);
			x = 100;
		}
		break;
	}

	bufferPosition = StringCopy(bufferPosition, Str_CursorColor);
	digitToHighlight = data->mode == LUMA_EDIT_STRING ? digit : data->digitCount - digit - 1;
	for (i = 0; i < data->digitCount; i++) {
		if (i == digitToHighlight) {
			bufferPosition = StringCopy(bufferPosition, Str_Cursor2Color);
		}
		*bufferPosition = gStringVar1[i];
		bufferPosition++;
		if (i == digitToHighlight) {
			bufferPosition = StringCopy(bufferPosition, Str_CursorColorOff);
		}
	}
	*bufferPosition = EOS;
	AddTextPrinterParameterized(LumaDebugMenu_EditPKMN_menuWindowId, 7, gStringVar2, x, y, 0, NULL);
	/* TODO Re-print the following data once edited:
		* Experience (level)
		* TID (SID)
		* PID (Gender, nature, is shiny)
		* Status (sleep/toxic counter)
		* Pokérus (counters)
		* Moves (move name, PP, PP Up)
		* Held item (item name)
		* Ability (ability name)
		* IVs (EVs, current, current HP)
		* EVs (IVs, current, current HP)
		* Stats (current HP, IVs, EVs)
		* Language (language name)
		* Ball (item name)
	*/
}

// This is basically a copy of GiveMonToPlayer, except without setting the OT details to the player's.
static u8 LumaDebugMenu_AddEditPKMN_GiveToPlayer() {
	u32 i;
	struct Pokemon* mon = &LumaDebugMenu_EditPKMN_Data.mon;
	switch (LumaDebugMenu_EditPKMN_Data.mode) {
	case 0:
		for (i = 0; i < PARTY_SIZE; i++) {
			if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL) == 0)
				break;
		}

		if (i >= PARTY_SIZE)
			return SendMonToPC(mon);

		CopyMon(&gPlayerParty[i], mon, sizeof(*mon));
		gPlayerPartyCount = i + 1;
		return MON_GIVEN_TO_PARTY;
	case 1:
	case 3 ... 5:
		CopyMon(LumaDebugMenu_EditPKMN_Data.monBeingEdited, mon, sizeof(struct Pokemon));
		return MON_GIVEN_TO_PARTY;
	case 2:
		CopyMon(LumaDebugMenu_EditPKMN_Data.monBeingEdited, mon, sizeof(struct BoxPokemon));
		return MON_GIVEN_TO_PC;
	case 6:
		for (i = 0; i < PARTY_SIZE; i++) {
			if (GetMonData(&gEnemyParty[i], MON_DATA_SPECIES, NULL) == 0)
				break;
		}

		if (i >= PARTY_SIZE)
			return MON_CANT_GIVE;

		CopyMon(&gEnemyParty[i], mon, sizeof(*mon));
		gEnemyPartyCount = i + 1;
		return MON_GIVEN_TO_PARTY;
	case 7:
	case 8:
	default:
		return MON_CANT_GIVE;
	}
}
#endif
