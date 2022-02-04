#include "characters/alien.h"

#define TIME(v) 60 * (1.f / (v))
#define ALIEN_SPEED 2.5f
typedef enum {GO_DOWN, GO_UP} Goto;

Alien enemy = NULL;
struct Alien
{
    Base *super;
    float speed;
    bool destroyed;
};

Alien alien_init(IW_Texture *skin)
{
    Alien self = memory_allocate(sizeof *self);
    Frame *frame = frame_init(skin, &(Vector2){GetScreenWidth()-256, 100}, &WHITE);
    self->super = base_init("Alien", MONSTER, frame);
    self->speed = ALIEN_SPEED;
    self->destroyed = false;

    return self;
}

void alien_update(Alien self)
{
    static Goto _goto;
    if (self->destroyed)
        return alien_del(self);
    float *y = &self->super->frame->pos.y;
    unsigned height = self->super->frame->get_texture_height(self->super->frame);
    if (*y + 85 < 1.f)
        _goto = GO_UP;
    if (*y + 86 > GetScreenHeight()-86)
        _goto = GO_DOWN;
    
    switch (_goto)
    {
    case GO_UP:
        *y += TIME(60) * self->speed;
        break;

    case GO_DOWN:
        *y -= TIME(60) * self->speed;
        break;
    default:
        fprintf(stderr, "Undefined address %s: %s", __FILE__, __LINE__);
        break;
    }
}

void alien_draw(Alien self)
{
    assert(self);
    DrawText("Alien", 500, 350, 36, RED);
    Texture2D skin = *self->super->frame->get_texture(self->super->frame);
    DrawTextureRec(skin, self->super->frame->rectangle, self->super->frame->pos, WHITE);
}

void alien_del(Alien self)
{
    self->super->del(self->super);
    memory_release(self);
}

void alien_set_destroy(Alien self, bool status)
{
    self->destroyed = status;
}

Rectangle alien_get_rec(Alien self)
{
    return self->super->frame->rectangle;
}