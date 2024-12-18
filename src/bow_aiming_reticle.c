#include "bow_aiming_reticle.h"



RECOMP_IMPORT("*", int recomp_printf(const char* fmt, ...));

// Declarations:

// Externs:
extern Vec3f* sPlayerCurBodyPartPos;
extern char gPlayerAnim_pg_punchA[];
extern u8 D_801C0778[];
extern Vec3f D_801C0994[];
extern char object_link_child_DL_017818[];
extern char gPlayerAnim_pg_punchB[];
extern u8 D_801C07AC[];
extern Vec3f sPlayerGetItemRefPos;
extern char gPlayerAnim_pg_gakkistart[];
extern char gPlayerAnim_pg_gakkiwait[];
extern char gPlayerAnim_pg_punchC[];
extern char gPlayerAnim_pg_gakkiplay[];
extern struct_80124618 D_801C0510[];
extern struct_80124618 D_801C0428[];
extern char object_link_goron_DL_00FC18[];
extern char gPlayerAnim_cl_setmask[];
extern char gPlayerAnim_cl_setmaskend[];
extern Gfx* D_801C0B20[];
extern char gPlayerAnim_pn_gurd[];
extern struct_80124618 D_801C0410[];
extern char gPlayerAnim_pn_gakkistart[];
extern char object_link_nuts_DL_00A348[];
extern char gPlayerAnim_pn_gakkiplay[];
extern char gPlayerAnim_dl_kokeru[];
extern struct_80124618 D_801C0340[];
extern struct_80124618 D_801C0368[];
extern char object_link_nuts_DL_007390[];
extern char gameplay_keep_Matanimheader_054F18[];
extern char gameplay_keep_DL_054C90[];
extern char gPlayerAnim_pn_drinkend[];
extern char gPlayerAnim_pn_tamahaki[];
extern Vec3f D_801C0A48[];
extern Vec3f D_801C0A24[];
extern Vec3f D_801C0A90[];
extern Vec3f D_801C0A6C[];
extern Gfx* gPlayerShields[];

extern const char object_link_goron_DL_010590[];
extern const char object_link_goron_DL_010368[];
extern const char object_link_goron_DL_010140[];
extern const char object_link_goron_DL_00FF18[];
extern const char object_link_goron_DL_00FCF0[];
extern const char object_link_nuts_DL_007A28[];
extern const char object_link_nuts_DL_0077D0[];
extern const char object_link_nuts_DL_007548[];
extern const char object_link_nuts_DL_007900[];
extern const char object_link_nuts_DL_0076A0[];


// Logic:
RECOMP_PATCH void Player_PostLimbDrawGameplay(PlayState* play, s32 limbIndex, Gfx** dList1, Gfx** dList2, Vec3s* rot, Actor* actor) {
    Player* player = (Player*)actor;

    if (*dList2 != NULL) {
        Matrix_MultZero(sPlayerCurBodyPartPos);
    }

    if (limbIndex == PLAYER_LIMB_LEFT_HAND) {
        Math_Vec3f_Copy(&player->leftHandWorld.pos, sPlayerCurBodyPartPos);

        if ((*dList1 != NULL) && !func_801271B0(play, player, 0) && !func_80128640(play, player, *dList1) &&
            (player->skelAnime.animation == &gPlayerAnim_pg_punchA)) {
            func_80127488(play, player, D_801C0778[(s32)player->skelAnime.curFrame]);
        }

        if (player->actor.scale.y >= 0.0f) {
            Actor* heldActor;
            MtxF sp230;

            if (!Player_IsHoldingHookshot(player) && ((heldActor = player->heldActor) != NULL)) {
                if ((player->stateFlags3 & PLAYER_STATE3_40) && (player->transformation != PLAYER_FORM_DEKU)) {
                    static Vec3f D_801C0D60 = { 398.0f, 1419.0f, 244.0f };
                    static Vec3f D_801C0D6C = { 420.0f, 1210.0f, 380.0f };
                    Vec3s* temp_s1;
                    Vec3f* var_a0 = &D_801C0D60;

                    if (player->transformation == PLAYER_FORM_HUMAN) {
                        var_a0 = &D_801C0D6C;
                    }

                    Matrix_MultVec3f(var_a0, &heldActor->world.pos);
                    Matrix_RotateZYX(0x69E8, -0x5708, 0x458E, MTXMODE_APPLY);

                    Matrix_Get(&sp230);
                    temp_s1 = &heldActor->world.rot;
                    Matrix_MtxFToYXZRot(&sp230, temp_s1, false);
                    heldActor->shape.rot = *temp_s1;
                } else if (player->stateFlags1 & PLAYER_STATE1_800) {
                    heldActor->world.rot.y = heldActor->shape.rot.y =
                        player->actor.shape.rot.y + player->leftHandWorld.rot.y;
                }
            } else {
                static f32 sMeleeWeaponLengths[PLAYER_MELEEWEAPON_MAX] = {
                    0.0f,    // PLAYER_MELEEWEAPON_NONE
                    3000.0f, // PLAYER_MELEEWEAPON_SWORD_KOKIRI
                    3000.0f, // PLAYER_MELEEWEAPON_SWORD_RAZOR
                    4000.0f, // PLAYER_MELEEWEAPON_SWORD_GILDED
                    5500.0f, // PLAYER_MELEEWEAPON_SWORD_TWO_HANDED
                    -1.0f,   // PLAYER_MELEEWEAPON_DEKU_STICK
                    2500.0f, // PLAYER_MELEEWEAPON_ZORA_FINS
                };

                if ((player->transformation == PLAYER_FORM_FIERCE_DEITY) ||
                    ((player->transformation != PLAYER_FORM_ZORA) &&
                     ((player->itemAction == PLAYER_IA_DEKU_STICK) ||
                      ((player->meleeWeaponState != PLAYER_MELEE_WEAPON_STATE_0) &&
                       (player->meleeWeaponAnimation != PLAYER_MWA_GORON_PUNCH_RIGHT) &&
                       (player->meleeWeaponAnimation != PLAYER_MWA_GORON_PUNCH_BUTT))))) {
                    if (player->itemAction == PLAYER_IA_DEKU_STICK) {
                        D_801C0994->x = player->unk_B0C * 5000.0f;
                    } else {
                        D_801C0994->x = sMeleeWeaponLengths[Player_GetMeleeWeaponHeld(player)];
                    }
                    func_80126B8C(play, player);
                }

                Matrix_Get(&player->leftHandMf);
                Matrix_MtxFToYXZRot(&player->leftHandMf, &player->leftHandWorld.rot, false);
            }
        }
    } else if (limbIndex == PLAYER_LIMB_RIGHT_HAND) {
        Actor* heldActor = player->heldActor;
        s32 pad;

        if (*dList1 != NULL) {
            if (player->rightHandType == PLAYER_MODELTYPE_RH_BOW) {
                static Gfx* D_801C0D94 = object_link_child_DL_017818;
                static Vec3f D_801C0D98 = { -35.0f, -395.0f, 0.0f };
                // Unused
                static s32 D_801C0DA4 = 0;

                OPEN_DISPS(play->state.gfxCtx);

                Matrix_Push();
                Matrix_Translate(D_801C0D98.x, D_801C0D98.y, D_801C0D98.z, MTXMODE_APPLY);
                if ((player->stateFlags3 & PLAYER_STATE3_40) && (player->unk_B28 >= 0) && (player->unk_ACC < 0xB)) {
                    Vec3f sp20C;
                    f32 temp_fv0;
                    s32 pad2;

                    Matrix_MultZero(&sp20C);
                    temp_fv0 = Math_Vec3f_DistXYZ(sPlayerCurBodyPartPos, &sp20C);
                    player->unk_B08 = temp_fv0 - 3.0f;
                    if (temp_fv0 < 3.0f) {
                        player->unk_B08 = 0.0f;
                    } else {
                        player->unk_B08 *= 1.6f;
                        if (player->unk_B08 > 1.0f) {
                            player->unk_B08 = 1.0f;
                        }
                    }
                    player->unk_B0C = -0.5f;
                }
                Matrix_Scale(1.0f, player->unk_B08, 1.0f, MTXMODE_APPLY);

                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, D_801C0D94);

                Matrix_Pop();

                CLOSE_DISPS(play->state.gfxCtx);
            } else if (player->skelAnime.animation == &gPlayerAnim_pg_punchB) {
                func_80127488(play, player, D_801C07AC[(s32)player->skelAnime.curFrame]);
            } else {
                func_801271B0(play, player, 1);
            }
        }

        if (player->actor.scale.y >= 0.0f) {
            if (player->rightHandType == PLAYER_MODELTYPE_RH_FF) {
                Matrix_Get(&player->shieldMf);
            } else if (player->rightHandType == PLAYER_MODELTYPE_RH_SHIELD) {
                // Coordinates of the shield quad collider vertices, in the right hand limb's own model space.
                static Vec3f sRightHandLimbModelShieldQuadVertices[4] = {
                    { -4500.0f, -3000.0f, -600.0f },
                    { 1500.0f, -3000.0f, -600.0f },
                    { -4500.0f, 3000.0f, -600.0f },
                    { 1500.0f, 3000.0f, -600.0f },
                };

                Matrix_Get(&player->shieldMf);
                Player_UpdateShieldCollider(play, player, &player->shieldQuad, sRightHandLimbModelShieldQuadVertices);
            } else if (player->rightHandType == PLAYER_MODELTYPE_RH_HOOKSHOT) {
                static Vec3f D_801C0DD8 = { 50.0f, 800.0f, 0.0f };

                Matrix_MultVec3f(&D_801C0DD8, &player->rightHandWorld.pos);

                if (heldActor != NULL) {
                    static Vec3f D_801C0DE4 = { 50.0f, 850.0f, 0.0f };
                    MtxF sp1BC;

                    Matrix_MultVec3f(&D_801C0DE4, &heldActor->world.pos);
                    Matrix_RotateZYX(0, -0x4000, -0x4000, MTXMODE_APPLY);
                    Matrix_Get(&sp1BC);
                    Matrix_MtxFToYXZRot(&sp1BC, &heldActor->world.rot, false);
                    heldActor->shape.rot = heldActor->world.rot;
                    if (func_800B7128(player)) {
                        Matrix_Translate(500.0f, 300.0f, 0.0f, MTXMODE_APPLY);
                        Player_DrawHookshotReticle(play, player, 77600.0f);
                    }
                }
            } 
            // This is the only part that's different from the decomp:
            // else if ((player->heldItemAction == PLAYER_IA_BOW_FIRE) ||
            //             (player->heldItemAction == PLAYER_IA_BOW_ICE) ||
            //             (player->heldItemAction == PLAYER_IA_BOW_LIGHT) || (player->heldItemAction == PLAYER_IA_BOW)) {
            else if (player->rightHandType == PLAYER_MODELTYPE_RH_BOW) {
                if (heldActor != NULL) {
                    MtxF sp44;

                    Matrix_RotateZYX(0, -15216, -17496, MTXMODE_APPLY);
                    Matrix_Get(&sp44);

                    if (func_800B7128(player) != 0) {
                        Matrix_Translate(500.0f, 300.0f, 0.0f, MTXMODE_APPLY);
                        Player_DrawHookshotReticle(play, player, 77600.0f * 32.0f);
                    }
                }
            }
            // End of changes:
            else if (player->meleeWeaponState != PLAYER_MELEE_WEAPON_STATE_0) {
                if (player->meleeWeaponAnimation == PLAYER_MWA_GORON_PUNCH_RIGHT) {
                    func_80126B8C(play, player);
                }
            }
            if ((player->getItemDrawIdPlusOne != (GID_NONE + 1)) ||
                ((func_800B7118(player) == 0) && (heldActor != NULL))) {
                if (!(player->stateFlags1 & PLAYER_STATE1_400) && (player->getItemDrawIdPlusOne != (GID_NONE + 1)) &&
                    (player->exchangeItemAction != PLAYER_IA_NONE)) {
                    Math_Vec3f_Copy(&sPlayerGetItemRefPos, &player->leftHandWorld.pos);
                } else {
                    sPlayerGetItemRefPos.x =
                        (player->bodyPartsPos[PLAYER_BODYPART_RIGHT_HAND].x + player->leftHandWorld.pos.x) * 0.5f;
                    sPlayerGetItemRefPos.y =
                        (player->bodyPartsPos[PLAYER_BODYPART_RIGHT_HAND].y + player->leftHandWorld.pos.y) * 0.5f;
                    sPlayerGetItemRefPos.z =
                        (player->bodyPartsPos[PLAYER_BODYPART_RIGHT_HAND].z + player->leftHandWorld.pos.z) * 0.5f;
                }

                if (player->getItemDrawIdPlusOne == (GID_NONE + 1)) {
                    Math_Vec3f_Copy(&heldActor->world.pos, &sPlayerGetItemRefPos);
                }
            }
        }
    } else if (limbIndex == PLAYER_LIMB_LEFT_FOREARM) {
        func_80126BD0(play, player, 0);
    } else if (limbIndex == PLAYER_LIMB_RIGHT_FOREARM) {
        func_80126BD0(play, player, 1);
    } else if (limbIndex == PLAYER_LIMB_TORSO) {
        if (player->transformation == PLAYER_FORM_GORON) {
            s32 temp_a0 = player->skelAnime.animation == &gPlayerAnim_pg_gakkistart;
            s32 temp_v1_3 = player->skelAnime.animation == &gPlayerAnim_pg_gakkiwait;

            if ((temp_a0 || temp_v1_3 || (player->skelAnime.animation == &gPlayerAnim_pg_gakkiplay))) {
                static Gfx* D_801C0DF0[] = {
                    object_link_goron_DL_010590, object_link_goron_DL_010368, object_link_goron_DL_010140,
                    object_link_goron_DL_00FF18, object_link_goron_DL_00FCF0,
                };
                Vec3f sp178[ARRAY_COUNT(D_801C0DF0)];
                s32 i;

                OPEN_DISPS(play->state.gfxCtx);

                if (temp_v1_3) {
                    f32* var_v0 = player->unk_B10;

                    for (i = 0; i < ARRAY_COUNT(sp178); i++, var_v0++) {
                        func_80124618(D_801C0510, *var_v0, &sp178[i]);
                    }
                } else {
                    if (temp_a0 != 0) {
                        func_8012536C();
                        func_80124618(D_801C0428, player->skelAnime.curFrame, &player->unk_AF0[1]);
                    }

                    for (i = 0; i < ARRAY_COUNT(sp178); i++) {
                        Math_Vec3f_Copy(&sp178[i], &player->unk_AF0[1]);
                    }
                }
                Matrix_Push();
                Matrix_Scale(player->unk_AF0[1].x, player->unk_AF0[1].y, player->unk_AF0[1].z, MTXMODE_APPLY);

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                gSPDisplayList(POLY_OPA_DISP++, object_link_goron_DL_00FC18);

                Matrix_Pop();

                for (i = 0; i < ARRAY_COUNT(sp178); i++) {
                    Matrix_Push();
                    Matrix_Scale(sp178[i].x, sp178[i].y, sp178[i].z, MTXMODE_APPLY);

                    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                    gSPDisplayList(POLY_OPA_DISP++, D_801C0DF0[i]);
                    Matrix_Pop();
                }

                CLOSE_DISPS(play->state.gfxCtx);
            }
        }
    } else if (limbIndex == PLAYER_LIMB_HEAD) {
        //! FAKE
        if (((*dList1 != NULL) && ((((void)0, player->currentMask)) != (((void)0, PLAYER_MASK_NONE)))) &&
            (((player->transformation == PLAYER_FORM_HUMAN) &&
              ((player->skelAnime.animation != &gPlayerAnim_cl_setmask) || (player->skelAnime.curFrame >= 12.0f))) ||
             ((((player->transformation != PLAYER_FORM_HUMAN) && (player->currentMask >= PLAYER_MASK_FIERCE_DEITY)) &&
               ((player->transformation + PLAYER_MASK_FIERCE_DEITY) != player->currentMask)) &&
              (player->skelAnime.curFrame >= 10.0f)))) {
            if (func_80127438(play, player, player->currentMask)) {
                s32 maskMinusOne = ((void)0, player->currentMask) - 1;

                OPEN_DISPS(play->state.gfxCtx);

                if (((void)0, player->currentMask) == PLAYER_MASK_COUPLE) {
                    Player_DrawCouplesMask(play, player);
                } else if (((void)0, player->currentMask) == PLAYER_MASK_CIRCUS_LEADER) {
                    Player_DrawCircusLeadersMask(play, player);
                } else if (((void)0, player->currentMask) == PLAYER_MASK_BLAST) {
                    Player_DrawBlastMask(play, player);
                } else if (((void)0, player->currentMask) == PLAYER_MASK_BUNNY) {
                    Player_DrawBunnyHood(play);
                } else if (((void)0, player->currentMask) == PLAYER_MASK_GREAT_FAIRY) {
                    Player_DrawGreatFairysMask(play, player);
                } else if (((void)0, player->currentMask) >= PLAYER_MASK_FIERCE_DEITY) {
                    static Vec2f D_801C0E04[PLAYER_FORM_MAX] = {
                        { 140.0f, -130.0f }, // PLAYER_FORM_FIERCE_DEITY
                        { 0.0f, -200.0f },   // PLAYER_FORM_GORON
                        { -160.0f, 0.0f },   // PLAYER_FORM_ZORA
                        { 220.0f, -200.0f }, // PLAYER_FORM_DEKU
                        { 0.0f, 0.0f },      // PLAYER_FORM_HUMAN
                    };
                    Vec2f* temp_s0_4 = &D_801C0E04[player->transformation];

                    Matrix_Push();
                    Matrix_Translate(temp_s0_4->x, temp_s0_4->z, 0.0f, MTXMODE_APPLY);
                    Matrix_Scale(1.0f, 1.0f - player->unk_B10[3], 1.0f - player->unk_B10[2], MTXMODE_APPLY);

                    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                    Matrix_Pop();

                    if (((player->skelAnime.animation == &gPlayerAnim_cl_setmask) &&
                         (player->skelAnime.curFrame >= 51.0f)) ||
                        (player->skelAnime.animation == &gPlayerAnim_cl_setmaskend)) {
                        maskMinusOne += 4;
                    }
                }

                gSPDisplayList(POLY_OPA_DISP++, D_801C0B20[maskMinusOne]);

                CLOSE_DISPS(play->state.gfxCtx);
            }
        } else if (player->transformation == PLAYER_FORM_DEKU) {
            if (player->skelAnime.animation == &gPlayerAnim_pn_gurd) {
                OPEN_DISPS(play->state.gfxCtx);

                func_80124618(D_801C0410, player->skelAnime.curFrame, player->unk_AF0);
                Matrix_Push();

                Matrix_Scale(player->unk_AF0[0].x, player->unk_AF0[0].y, player->unk_AF0[0].z, MTXMODE_APPLY);

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, object_link_nuts_DL_00A348);

                Matrix_Pop();

                CLOSE_DISPS(play->state.gfxCtx);
            } else {
                s32 temp_v1_5 = player->skelAnime.animation == &gPlayerAnim_pn_gakkistart;

                if (temp_v1_5 || (player->skelAnime.animation == &gPlayerAnim_pn_gakkiplay) ||
                    (player->skelAnime.animation == &gPlayerAnim_dl_kokeru)) {
                    static Gfx* D_801C0E2C[] = {
                        object_link_nuts_DL_007A28, object_link_nuts_DL_0077D0, object_link_nuts_DL_007548,
                        object_link_nuts_DL_007900, object_link_nuts_DL_0076A0,
                    };
                    Vec3f spF0[ARRAY_COUNT(D_801C0E2C)];
                    s32 i;
                    f32* temp;

                    OPEN_DISPS(play->state.gfxCtx);

                    if (temp_v1_5) {
                        Vec3f spD4;

                        func_80124618(D_801C0340, player->skelAnime.curFrame, &spD4);
                        player->arr_AF0[0] = spD4.x;
                        func_80124618(D_801C0368, player->skelAnime.curFrame, spF0);

                        for (i = 0; i < ARRAY_COUNT(spF0) - 1; i++) {
                            Math_Vec3f_Copy(&spF0[i + 1], spF0);
                        }

                        temp = &player->arr_AF0[1];
                        for (i = 0; i < ARRAY_COUNT(spF0); i++) {
                            *temp = spF0[0].x;
                            temp++;
                        }
                    } else {
                        temp = &player->arr_AF0[1];
                        for (i = 0; i < ARRAY_COUNT(spF0); i++) {
                            spF0[i].x = *temp;
                            spF0[i].y = *temp;
                            spF0[i].z = *temp;
                            temp++;
                        }
                    }

                    Matrix_Push();
                    Matrix_Scale(player->arr_AF0[0], player->arr_AF0[0], player->arr_AF0[0], MTXMODE_APPLY);

                    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPDisplayList(POLY_OPA_DISP++, object_link_nuts_DL_007390);

                    Matrix_Pop();

                    for (i = 0; i < ARRAY_COUNT(spF0); i++) {
                        Matrix_Push();

                        Matrix_Scale(spF0[i].x, spF0[i].y, spF0[i].z, MTXMODE_APPLY);
                        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                        //! FAKE (yes, all of them are required)
                        // https://decomp.me/scratch/AdU3G
                        if (1) {}
                        if (1) {}
                        if (1) {}
                        if (1) {}
                        if (1) {}
                        if (1) {}
                        gSPDisplayList(POLY_OPA_DISP++, D_801C0E2C[i]);

                        Matrix_Pop();
                    }

                    CLOSE_DISPS(play->state.gfxCtx);
                }
            }
        }

        if ((player->stateFlags1 & (PLAYER_STATE1_2 | PLAYER_STATE1_100)) && (player->av2.actionVar2 != 0)) {
            static Vec3f D_801C0E40[PLAYER_FORM_MAX] = {
                { 0.0f, 0.0f, 0.0f },        // PLAYER_FORM_FIERCE_DEITY
                { -578.3f, -1100.9f, 0.0f }, // PLAYER_FORM_GORON
                { -189.5f, -594.87f, 0.0f }, // PLAYER_FORM_ZORA
                { -570.0f, -812.0f, 0.0f },  // PLAYER_FORM_DEKU
                { -230.0f, -520.0f, 0.0f },  // PLAYER_FORM_HUMAN
            };
            Vec3f* temp_s0_7 = &D_801C0E40[player->transformation];

            OPEN_DISPS(play->state.gfxCtx);

            Matrix_Push();
            AnimatedMat_DrawXlu(play, Lib_SegmentedToVirtual(gameplay_keep_Matanimheader_054F18));
            Matrix_Translate(temp_s0_7->x, temp_s0_7->y, 0.0f, MTXMODE_APPLY);
            if (player->transformation == PLAYER_FORM_ZORA) {
                Matrix_Scale(0.7f, 0.7f, 0.7f, MTXMODE_APPLY);
            }

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 255, (u8)player->av2.actionVar2);
            gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_054C90);

            Matrix_Pop();

            CLOSE_DISPS(play->state.gfxCtx);
        }
        if (player->actor.scale.y >= 0.0f) {
            static Vec3f sPlayerFocusHeadLimbModelPos = { 1100.0f, -700.0f, 0.0f };
            static Vec3f D_801C0E88 = { 1600.0f, -1700.0f, -70.0f }; // unused
            Actor* spA8 = NULL;

            if (player->transformation != PLAYER_FORM_DEKU) {
                Matrix_MultVec3f(&sPlayerFocusHeadLimbModelPos, &player->actor.focus.pos);
            } else {
                static Vec3f D_801C0E94 = { 1800.0f, -300.0f, 0.0f };

                Matrix_MultVec3f(&sPlayerFocusHeadLimbModelPos, &player->actor.focus.pos);
                Matrix_MultVec3f(&D_801C0E94, sPlayerCurBodyPartPos);
                if ((player->skelAnime.animation == &gPlayerAnim_pn_drinkend) ||
                    (player->skelAnimeUpper.animation == &gPlayerAnim_pn_tamahaki) ||
                    ((player->stateFlags3 & PLAYER_STATE3_40) && ((spA8 = player->heldActor) != NULL))) {
                    if (spA8 != NULL) {
                        static Vec3f D_801C0EA0 = { 1300.0f, -400.0f, 0.0f };
                        MtxF sp68;

                        Matrix_Push();
                        Matrix_MultVec3f(&D_801C0EA0, &spA8->world.pos);
                        Matrix_RotateZYX(0, 0x4000, 0, MTXMODE_APPLY);
                        Matrix_Get(&sp68);
                        Matrix_MtxFToYXZRot(&sp68, &spA8->world.rot, false);
                        spA8->shape.rot = spA8->world.rot;
                        Matrix_Pop();
                    }
                }
            }
        }
    } else if ((limbIndex == PLAYER_LIMB_HAT) && (player->stateFlags3 & PLAYER_STATE3_100000)) {
        Vec3f sp5C;
        Vec3f sp50;

        Matrix_MultVecX(3000.0f, &sp5C);
        Matrix_MultVecX(2300.0f, &sp50);
        if (func_80126440(play, NULL, player->meleeWeaponInfo, &sp5C, &sp50)) {
            EffectBlure_AddVertex(Effect_GetByIndex(player->meleeWeaponEffectIndex[0]), &player->meleeWeaponInfo[0].tip,
                                  &player->meleeWeaponInfo[0].base);
        }
    } else if (limbIndex == PLAYER_LIMB_RIGHT_SHIN) {
        if (player->meleeWeaponState != PLAYER_MELEE_WEAPON_STATE_0) {
            if ((player->meleeWeaponAnimation == PLAYER_MWA_ZORA_PUNCH_KICK) ||
                (player->meleeWeaponAnimation == PLAYER_MWA_ZORA_JUMPKICK_START) ||
                (player->meleeWeaponAnimation == PLAYER_MWA_ZORA_JUMPKICK_FINISH)) {
                func_8012669C(play, player, D_801C0A48, D_801C0A24);
            }
        }
    } else if (limbIndex == PLAYER_LIMB_WAIST) {
        if (player->meleeWeaponState != PLAYER_MELEE_WEAPON_STATE_0) {
            if (player->meleeWeaponAnimation == PLAYER_MWA_GORON_PUNCH_BUTT) {
                Math_Vec3f_Copy(&player->unk_AF0[1], &player->meleeWeaponInfo[0].base);
                func_8012669C(play, player, D_801C0A90, D_801C0A6C);
            }
        }
    } else if (limbIndex == PLAYER_LIMB_SHEATH) {
        if ((*dList1 != NULL) && (player->transformation == PLAYER_FORM_HUMAN) &&
            (player->currentShield != PLAYER_SHIELD_NONE) &&
            ((player->sheathType == PLAYER_MODELTYPE_SHEATH_14) ||
             (player->sheathType == PLAYER_MODELTYPE_SHEATH_15))) {
            OPEN_DISPS(play->state.gfxCtx);

            gSPDisplayList(POLY_OPA_DISP++, gPlayerShields[2 * ((player->currentShield - 1) ^ 0)]);

            CLOSE_DISPS(play->state.gfxCtx);
        }

        if (player->actor.scale.y >= 0.0f) {
            if ((player->rightHandType != PLAYER_MODELTYPE_RH_SHIELD) &&
                (player->rightHandType != PLAYER_MODELTYPE_RH_FF)) {
                static Vec3f sSheathLimbModelShieldOnBackPos = { 630.0f, 100.0f, -30.0f };
                static Vec3s sSheathLimbModelShieldOnBackZyxRot = { 0, 0, 0x7FFF };

                Matrix_TranslateRotateZYX(&sSheathLimbModelShieldOnBackPos, &sSheathLimbModelShieldOnBackZyxRot);
                Matrix_Get(&player->shieldMf);
            }
        }
    } else if (player->actor.scale.y >= 0.0f) {
        Player_SetFeetPos(play, player, limbIndex);
    }

    func_8012536C();
}
