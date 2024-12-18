#include "modding.h"
#include "global.h"
#include "z64actor.h"
#include "z64math.h"

s32 func_801226E0(PlayState* play, s32 arg1);
s32 func_80122744(PlayState* play, struct_80122744_arg1* arg1, u32 arg2, Vec3s* arg3);
s32 func_80122760(PlayState* play, struct_80122744_arg1* arg1, f32 arg2);
void func_80122868(PlayState* play, Player* player);

// Update function
void func_801229EC(Actor* thisx, PlayState* play);


// Load mask object?
/**
 * Notes:
 *
 * player->maskObjectLoadState seems to be able to take 3 possible values
 *    0: The mask object is loaded.
 *    1: The mask object must be changed (and the DMA request has not been sent yet)
 *    2: Waiting for the DMA request to complete.
 */
void func_801229FC(Player* player);
void func_80122BA4(PlayState* play, struct_80122D44_arg1* arg1, s32 arg2, s32 alpha);
void func_80122C20(PlayState* play, struct_80122D44_arg1* arg1);
void func_80122D44(PlayState* play, struct_80122D44_arg1* arg1);
u8 Player_MaskIdToItemId(s32 maskIdMinusOne);
s32 Player_GetCurMaskItemId(PlayState* play);
void func_80122F28(Player* player);
s32 func_80122F9C(PlayState* play);
s32 func_80122FCC(PlayState* play);
void func_8012300C(PlayState* play, s32 arg1);
// Update function
void func_8012301C(Actor* thisx, PlayState* play2);
// OoT's Player_SetBootData
void func_80123140(PlayState* play, Player* player);
s32 Player_InBlockingCsMode(PlayState* play, Player* player);
s32 Player_InCsMode(PlayState* play);
s32 func_80123420(Player* player);
s32 func_80123434(Player* player);
// Unused
s32 func_80123448(PlayState* play);
// TODO: Player_IsGoronOrDeku is a temporary name until we have more info on this function.
// Hypothesis: this function checks if the current form would crouch when he tries to use the shield
s32 Player_IsGoronOrDeku(Player* player);
s32 func_801234D4(PlayState* play);
s32 func_80123590(PlayState* play, Actor* actor);
s32 func_801235DC(PlayState* play, f32 arg1, s16 arg2);
ItemId Player_GetItemOnButton(PlayState* play, Player* player, EquipSlot slot);
PlayerItemAction func_80123810(PlayState* play);
PlayerModelGroup Player_ActionToModelGroup(Player* player, PlayerItemAction itemAction);

void Player_SetModelsForHoldingShield(Player* player);
void Player_SetModels(Player* player, PlayerModelGroup modelGroup);
void Player_SetModelGroup(Player* player, PlayerModelGroup modelGroup);
void func_80123C58(Player* player);
void Player_SetEquipmentData(PlayState* play, Player* player);
void Player_UpdateBottleHeld(PlayState* play, Player* player, ItemId itemId, PlayerItemAction itemAction) ;
void Player_Untarget(Player* player);
void func_80123DC0(Player* player);
void func_80123E90(PlayState* play, Actor* actor) ;
s32 func_80123F14(PlayState* play);
s32 Player_SetBButtonAmmo(PlayState* play, s32 ammo);
s32 Player_IsBurningStickInRange(PlayState* play, Vec3f* pos, f32 xzRange, f32 yRange) ;
u8 Player_GetStrength(void);
// s32 Player_GetMask(PlayState* play);
// Unused
void Player_RemoveMask(PlayState* play) ;
s32 Player_HasMirrorShieldEquipped(PlayState* play) ;
s32 Player_IsHoldingMirrorShield(PlayState* play) ;
s32 Player_IsHoldingHookshot(Player* player) ;
s32 func_801240DC(Player* player) ;
PlayerBButtonSword Player_BButtonSwordFromIA(Player* player, PlayerItemAction itemAction) ;
PlayerBButtonSword Player_GetHeldBButtonSword(Player* player) ;
PlayerMeleeWeapon Player_MeleeWeaponFromIA(PlayerItemAction itemAction) ;
PlayerMeleeWeapon Player_GetMeleeWeaponHeld(Player* player) ;
s32 Player_IsHoldingTwoHandedWeapon(Player* player) ;
PlayerBottle Player_BottleFromIA(Player* player, PlayerItemAction itemAction) ;
PlayerBottle Player_GetBottleHeld(Player* Player) ;
PlayerExplosive Player_ExplosiveFromIA(Player* player, PlayerItemAction itemAction) ;
PlayerExplosive Player_GetExplosiveHeld(Player* player) ;
// Note this function maps PLAYER_IA_LAST_USED to PLAYER_SWORD_KOKIRI
PlayerSword Player_SwordFromIA(Player* player, PlayerItemAction itemAction) ;
s32 func_801242B4(Player* player) ;
s32 Player_GetEnvironmentalHazard(PlayState* play) ;
void Player_UpdateBunnyEars(Player* player) ;
void func_80124618(struct_80124618 arg0[], f32 curFrame, Vec3f* arg2) ;
// Note the correct pointer to pass as the jointTable is the jointTable pointer from the SkelAnime struct, not the
// buffer from the Player struct itself since that one may be misaligned.
void Player_DrawImpl(PlayState* play, void** skeleton, Vec3s* jointTable, s32 dListCount, s32 lod,
                     PlayerTransformation playerForm, s32 boots, s32 face, OverrideLimbDrawFlex overrideLimbDraw,
                     PostLimbDrawFlex postLimbDraw, Actor* actor) ;
/**
 * Adjusts player's legs to slopes and spawns flames when running on lava
 */
void Player_AdjustSingleLeg(PlayState* play, Player* player, SkelAnime* skelAnime, Vec3f* pos, Vec3s* rot,
                            s32 thighLimbIndex, s32 shinLimbIndex, s32 footLimbIndex) ;
void Player_DrawHookshotReticle(PlayState* play, Player* player, f32 hookshotDistance);
void func_80124F18(s16* arg0, f32* arg1, s16 arg2, f32 arg3, f32 arg4);
void func_80124FF0(f32 arg0, s16 arg1, Vec3f* arg2, s16 arg3, Vec3f* arg4, Vec3f* arg5, s16* arg6, f32* arg7, f32 arg8,
                   s16 arg9, s16* arg10, f32* arg11, s32 arg12);
void func_801251C4(Player* player, Vec3f* arg1);
void func_80125318(Vec3f* arg0, Vec3s* arg1);
void func_80125340(void);
void func_8012536C(void);
void Player_DrawZoraShield(PlayState* play, Player* player);
void func_80125500(PlayState* play, Player* player, s32 limbIndex, Vec3f* pos, Vec3s* rot);
s32 Player_OverrideLimbDrawGameplayCommon(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                          Actor* thisx) ;
void func_80125CE0(Player* player, struct_80124618* arg1, Vec3f* pos, Vec3s* rot);
s32 Player_OverrideLimbDrawGameplayDefault(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                           Actor* actor) ;
s32 Player_OverrideLimbDrawGameplayFirstPerson(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                               Actor* actor);
// Unused remnant of OoT
s32 Player_OverrideLimbDrawGameplayCrawling(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                            Actor* thisx) ;
s32 func_80126440(PlayState* play, ColliderQuad* collider, WeaponInfo* weaponInfo, Vec3f* newTip, Vec3f* newBase) ;
void Player_UpdateShieldCollider(PlayState* play, Player* player, ColliderQuad* collider, Vec3f quadSrc[4]) ;
void func_8012669C(PlayState* play, Player* player, Vec3f* arg2, Vec3f* arg3);
void Player_DrawGetItemImpl(PlayState* play, Player* player, Vec3f* refPos, s32 drawIdPlusOne);
void Player_DrawGetItem(PlayState* play, Player* player) ;
void func_80126AB4(Player* player, Vec3f** arg1);
void func_80126B8C(PlayState* play, Player* player);
// Zora boomerangs (?)
void func_80126BD0(PlayState* play, Player* player, s32 arg2);
s32 func_801271B0(PlayState* play, Player* player, s32 arg2);
// Player_SetMaskSegment?
s32 func_80127438(PlayState* play, Player* player, s32 currentMask);
void func_80127488(PlayState* play, Player* player, u8 alpha);
void Player_DrawCouplesMask(PlayState* play, Player* player);
void Player_DrawCircusLeadersMask(PlayState* play, Player* player);
void Player_DrawBlastMask(PlayState* play, Player* player);
void Player_DrawBunnyHood(PlayState* play);
// void func_80127B64(struct_801F58B0 arg0[], s32 count, Vec3f* arg2);
// Draws the Great Fairy's Mask particles when a stray fairy is in the room
void Player_DrawStrayFairyParticles(PlayState* play, Vec3f* arg1);
// void func_80127DA4(PlayState* play, struct_801F58B0 arg1[], struct_80128388_arg1 arg2[], s32 arg3, Vec3f* arg4,
                //    Vec3f* arg5, u32* arg6);
// void func_80128388(struct_801F58B0 arg0[], struct_80128388_arg1 arg1[], s32 arg2, Mtx** arg3);
void Player_DrawGreatFairysMask(PlayState* play, Player* player);
s32 func_80128640(PlayState* play, Player* player, Gfx* dlist);
void Player_SetFeetPos(PlayState* play, Player* player, s32 limbIndex);