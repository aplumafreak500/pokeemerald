#ifndef GUARD_POKEMON_ANIMATION_H
#define GUARD_POKEMON_ANIMATION_H

u8 GetSpeciesBackAnimSet(u16 species);
void LaunchAnimationTaskForFrontSprite(struct Sprite *sprite, u8 frontAnimId);
void StartMonSummaryAnimation(struct Sprite *sprite, u8 frontAnimId);
void LaunchAnimationTaskForBackSprite(struct Sprite *sprite, u8 backAnimSet);
void SetSpriteCB_MonAnimDummy(struct Sprite *sprite);

// Pokémon back animation sets
#define BACK_ANIM_NONE                         0
#define BACK_ANIM_H_VIBRATE                    1
#define BACK_ANIM_H_SLIDE                      2
#define BACK_ANIM_H_SPRING                     3
#define BACK_ANIM_H_SPRING_REPEATED            4
#define BACK_ANIM_SHRINK_GROW                  5
#define BACK_ANIM_GROW                         6
#define BACK_ANIM_CIRCLE_COUNTERCLOCKWISE      7
#define BACK_ANIM_H_SHAKE                      8
#define BACK_ANIM_V_SHAKE                      9
#define BACK_ANIM_V_SHAKE_H_SLIDE              10
#define BACK_ANIM_V_STRETCH                    11
#define BACK_ANIM_H_STRETCH                    12
#define BACK_ANIM_GROW_STUTTER                 13
#define BACK_ANIM_V_SHAKE_LOW                  14
#define BACK_ANIM_TRIANGLE_DOWN                15
#define BACK_ANIM_CONCAVE_ARC_LARGE            16
#define BACK_ANIM_CONVEX_DOUBLE_ARC            17
#define BACK_ANIM_CONCAVE_ARC_SMALL            18
#define BACK_ANIM_DIP_RIGHT_SIDE               19
#define BACK_ANIM_SHRINK_GROW_VIBRATE          20
#define BACK_ANIM_JOLT_RIGHT                   21
#define BACK_ANIM_SHAKE_FLASH_YELLOW           22
#define BACK_ANIM_SHAKE_GLOW_RED               23
#define BACK_ANIM_SHAKE_GLOW_GREEN             24
#define BACK_ANIM_SHAKE_GLOW_BLUE              25
#define BACK_ANIM_SHAKE_GLOW_BLACK             26
#define BACK_ANIM_SHAKE_GLOW_WHITE             27
#define BACK_ANIM_SHAKE_GLOW_PURPLE            28

// Pokémon animation function ids (for front and back)
// Each front anim uses 1, and each back anim uses a set of 3
#define ANIM_V_SQUISH_AND_BOUNCE                0
#define ANIM_CIRCULAR_STRETCH_TWICE             1
#define ANIM_H_VIBRATE                          2
#define ANIM_H_SLIDE                            3
#define ANIM_V_SLIDE                            4
#define ANIM_BOUNCE_ROTATE_TO_SIDES             5
#define ANIM_V_JUMPS_H_JUMPS                    6
#define ANIM_ROTATE_TO_SIDES                    7
#define ANIM_ROTATE_TO_SIDES_TWICE              8
#define ANIM_GROW_VIBRATE                       9
#define ANIM_ZIGZAG_FAST                        10
#define ANIM_SWING_CONCAVE                      11
#define ANIM_SWING_CONCAVE_FAST                 12
#define ANIM_SWING_CONVEX                       13
#define ANIM_SWING_CONVEX_FAST                  14
#define ANIM_H_SHAKE                            15
#define ANIM_V_SHAKE                            16
#define ANIM_CIRCULAR_VIBRATE                   17
#define ANIM_TWIST                              18
#define ANIM_SHRINK_GROW                        19
#define ANIM_CIRCLE_C_CLOCKWISE                 20
#define ANIM_GLOW_BLACK                         21
#define ANIM_H_STRETCH                          22
#define ANIM_V_STRETCH                          23
#define ANIM_RISING_WOBBLE                      24
#define ANIM_V_SHAKE_TWICE                      25
#define ANIM_TIP_MOVE_FORWARD                   26
#define ANIM_H_PIVOT                            27
#define ANIM_V_SLIDE_WOBBLE                     28
#define ANIM_H_SLIDE_WOBBLE                     29
#define ANIM_V_JUMPS_BIG                        30
#define ANIM_SPIN_LONG                          31
#define ANIM_GLOW_ORANGE                        32
#define ANIM_GLOW_RED                           33
#define ANIM_GLOW_BLUE                          34
#define ANIM_GLOW_YELLOW                        35
#define ANIM_GLOW_PURPLE                        36
#define ANIM_BACK_AND_LUNGE                     37
#define ANIM_BACK_FLIP                          38
#define ANIM_FLICKER                            39
#define ANIM_BACK_FLIP_BIG                      40
#define ANIM_FRONT_FLIP                         41
#define ANIM_TUMBLING_FRONT_FLIP                42
#define ANIM_FIGURE_8                           43
#define ANIM_FLASH_YELLOW                       44
#define ANIM_SWING_CONCAVE_FAST_SHORT           45
#define ANIM_SWING_CONVEX_FAST_SHORT            46
#define ANIM_ROTATE_UP_SLAM_DOWN                47
#define ANIM_DEEP_V_SQUISH_AND_BOUNCE           48
#define ANIM_H_JUMPS                            49
#define ANIM_H_JUMPS_V_STRETCH                  50
#define ANIM_ROTATE_TO_SIDES_FAST               51
#define ANIM_ROTATE_UP_TO_SIDES                 52
#define ANIM_FLICKER_INCREASING                 53
#define ANIM_TIP_HOP_FORWARD                    54
#define ANIM_PIVOT_SHAKE                        55
#define ANIM_TIP_AND_SHAKE                      56
#define ANIM_VIBRATE_TO_CORNERS                 57
#define ANIM_GROW_IN_STAGES                     58
#define ANIM_V_SPRING                           59
#define ANIM_V_REPEATED_SPRING                  60
#define ANIM_SPRING_RISING                      61
#define ANIM_H_SPRING                           62
#define ANIM_H_REPEATED_SPRING_SLOW             63
#define ANIM_H_SLIDE_SHRINK                     64
#define ANIM_LUNGE_GROW                         65
#define ANIM_CIRCLE_INTO_BG                     66
#define ANIM_RAPID_H_HOPS                       67
#define ANIM_FOUR_PETAL                         68
#define ANIM_V_SQUISH_AND_BOUNCE_SLOW           69
#define ANIM_H_SLIDE_SLOW                       70
#define ANIM_V_SLIDE_SLOW                       71
#define ANIM_BOUNCE_ROTATE_TO_SIDES_SMALL       72
#define ANIM_BOUNCE_ROTATE_TO_SIDES_SLOW        73
#define ANIM_BOUNCE_ROTATE_TO_SIDES_SMALL_SLOW  74
#define ANIM_ZIGZAG_SLOW                        75
#define ANIM_H_SHAKE_SLOW                       76
#define ANIM_V_SHAKE_SLOW                       77
#define ANIM_TWIST_TWICE                        78
#define ANIM_CIRCLE_C_CLOCKWISE_SLOW            79
#define ANIM_V_SHAKE_TWICE_SLOW                 80
#define ANIM_V_SLIDE_WOBBLE_SMALL               81
#define ANIM_V_JUMPS_SMALL                      82
#define ANIM_SPIN                               83
#define ANIM_TUMBLING_FRONT_FLIP_TWICE          84
#define ANIM_DEEP_V_SQUISH_AND_BOUNCE_TWICE     85
#define ANIM_H_JUMPS_V_STRETCH_TWICE            86
#define ANIM_V_SHAKE_BACK                       87
#define ANIM_V_SHAKE_BACK_SLOW                  88
#define ANIM_V_SHAKE_H_SLIDE_SLOW               89
#define ANIM_V_STRETCH_BOTH_ENDS_SLOW           90
#define ANIM_H_STRETCH_FAR_SLOW                 91
#define ANIM_V_SHAKE_LOW_TWICE                  92
#define ANIM_H_SHAKE_FAST                       93
#define ANIM_H_SLIDE_FAST                       94
#define ANIM_H_VIBRATE_FAST                     95
#define ANIM_H_VIBRATE_FASTEST                  96
#define ANIM_V_SHAKE_BACK_FAST                  97
#define ANIM_V_SHAKE_LOW_TWICE_SLOW             98
#define ANIM_V_SHAKE_LOW_TWICE_FAST             99
#define ANIM_CIRCLE_C_CLOCKWISE_LONG            100
#define ANIM_GROW_STUTTER_SLOW                  101
#define ANIM_V_SHAKE_H_SLIDE                    102
#define ANIM_V_SHAKE_H_SLIDE_FAST               103
#define ANIM_TRIANGLE_DOWN_SLOW                 104
#define ANIM_TRIANGLE_DOWN                      105
#define ANIM_TRIANGLE_DOWN_TWICE                106
#define ANIM_GROW                               107
#define ANIM_GROW_TWICE                         108
#define ANIM_H_SPRING_FAST                      109
#define ANIM_H_SPRING_SLOW                      110
#define ANIM_H_REPEATED_SPRING_FAST             111
#define ANIM_H_REPEATED_SPRING                  112
#define ANIM_SHRINK_GROW_FAST                   113
#define ANIM_SHRINK_GROW_SLOW                   114
#define ANIM_V_STRETCH_BOTH_ENDS                115
#define ANIM_V_STRETCH_BOTH_ENDS_TWICE          116
#define ANIM_H_STRETCH_FAR_TWICE                117
#define ANIM_H_STRETCH_FAR                      118
#define ANIM_GROW_STUTTER_TWICE                 119
#define ANIM_GROW_STUTTER                       120
#define ANIM_CONCAVE_ARC_LARGE_SLOW             121
#define ANIM_CONCAVE_ARC_LARGE                  122
#define ANIM_CONCAVE_ARC_LARGE_TWICE            123
#define ANIM_CONVEX_DOUBLE_ARC_SLOW             124
#define ANIM_CONVEX_DOUBLE_ARC                  125
#define ANIM_CONVEX_DOUBLE_ARC_TWICE            126
#define ANIM_CONCAVE_ARC_SMALL_SLOW             127
#define ANIM_CONCAVE_ARC_SMALL                  128
#define ANIM_CONCAVE_ARC_SMALL_TWICE            129
#define ANIM_H_DIP                              130
#define ANIM_H_DIP_FAST                         131
#define ANIM_H_DIP_TWICE                        132
#define ANIM_SHRINK_GROW_VIBRATE_FAST           133
#define ANIM_SHRINK_GROW_VIBRATE                134
#define ANIM_SHRINK_GROW_VIBRATE_SLOW           135
#define ANIM_JOLT_RIGHT_FAST                    136
#define ANIM_JOLT_RIGHT                         137
#define ANIM_JOLT_RIGHT_SLOW                    138
#define ANIM_SHAKE_FLASH_YELLOW_FAST            139
#define ANIM_SHAKE_FLASH_YELLOW                 140
#define ANIM_SHAKE_FLASH_YELLOW_SLOW            141
#define ANIM_SHAKE_GLOW_RED_FAST                142
#define ANIM_SHAKE_GLOW_RED                     143
#define ANIM_SHAKE_GLOW_RED_SLOW                144
#define ANIM_SHAKE_GLOW_GREEN_FAST              145
#define ANIM_SHAKE_GLOW_GREEN                   146
#define ANIM_SHAKE_GLOW_GREEN_SLOW              147
#define ANIM_SHAKE_GLOW_BLUE_FAST               148
#define ANIM_SHAKE_GLOW_BLUE                    149
#define ANIM_SHAKE_GLOW_BLUE_SLOW               150
#define ANIM_SHAKE_GLOW_BLACK_SLOW              151
#define ANIM_SHAKE_GLOW_WHITE_SLOW              152
#define ANIM_SHAKE_GLOW_PURPLE_SLOW             153

#endif // GUARD_POKEMON_ANIMATION_H
