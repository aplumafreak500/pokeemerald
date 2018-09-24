#ifndef GUARD_SECRET_BASE_H
#define GUARD_SECRET_BASE_H

// Exported type declarations

// Exported RAM declarations

// Exported ROM declarations
void sub_80E9578(void);
void sub_80E980C(void);
void sub_80EB18C(struct SecretBaseRecord *dest);
void sub_80E9914(void);
u8 *GetSecretBaseMapName(u8 *dest);
const u8 *GetSecretBaseTrainerLoseText(void);
void sub_80E8EE0(struct MapEvents const *events);
void sub_80E9238(u8 flagIn);
bool8 CurrentMapIsSecretBase(void);
void sub_80EA3E4(u8 taskId);

#endif //GUARD_SECRET_BASE_H
