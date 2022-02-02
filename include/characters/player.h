/**
 * @file player.h
 * @author Jose S. Daniel (djose1164@gmail.com)
 * @brief Preliminar object-base. This will follow the OOP style.
 * @version 0.1
 * @date 2021-04-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef PLAYER_H
#define PLAYER_H

#include "characters/base.h"
#include "item/weapon.h"
// #include "core/physics.h"
#include "utils/utils.h"
#include "utils/list.h"
#include <stddef.h>
#include <raylib.h>

typedef struct Player Player;
struct Player
{
    Living *base_super;
    char *profession;
    Laser laser;
    bool attacking;

    Player *(*init)(const char *name, const char *texture);
    void (*set_texture)(Player *const self, const char *texture);
    void (*set_name)(Player *const self, const char *name);
    void (*update)(const Player *self);
    void (*draw)(const Player *self);
    void (*del)(Player *self);
};

Player *player_init(const Living *living);

/**
 * @brief To eliminate an existing player.
 * 
 * @param self The player to remove.
 */
void player_del(Player *self);

void player_set_name(Player *const self, const char *name);

void player_goto(Player *self);


/****************************************************************************/
/*                                   Private Functions.                     */
/****************************************************************************/

/**
 * @brief Set the given `texture` for the player `self`.
 * 
 * @param self Pointer to player.
 * @param texture Texture to set.
 */
static void player_set_texture(Player *const self, IW_Texture *texture);

static void player_bindfuncs(Player *const self);

static void player_update(Player *const self);

static void player_draw(const Player *self);

static void player_handle_input(Player *const self);

static void player_attack(Player *self);

#endif // PLAYER_H
