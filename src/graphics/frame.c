#include "graphics/frame.h"

Frame *frame_init(const IW_Texture *texture, const Vector2 *position,
                    Color *color)
{
    puts("Creating frame...");
    Frame *self = memory_allocate(self, sizeof *self);
    self->_texture = texture;
    self->position = *position;
    self->color = *color;
    
    self->rectangle.width = (float)texture->get_width(texture)/3;
    self->rectangle.height = (float)texture->get_height(texture);
    self->rectangle.x = 0.0f;
    self->rectangle.y = 0.0f;

    self->bind_texture = frame_bind_texture;
    self->del_texture = frame_del_texture;
    self->del = frame_del;
    self->get_texture = frame_get_texture;
    self->get_texture_width = frame_get_texture_width;
    self->get_texture_height = frame_get_texture_height;
    self->draw = frame_draw;
    self->check_margins = frame_check_margins;
    puts("Creating frame...Done!");

    return self;
}

static void frame_del(Frame *self)
{
    if (self->object_super)
        self->object_super->del((Object *)self);
    if (self->_texture)
        self->del_texture(self);
    memory_release(self);
}

static void frame_bind_texture(Frame *const self, const IW_Texture *texture)
{
    if (self->_texture)
        frame_del_texture(self);
    self->_texture = texture;
}

static void frame_del_texture(Frame *const self)
{
    self->_texture->del(self->_texture);
}

static void frame_draw(const Frame *self)
{
    frame_check_margins(self);
    DrawTextureRec(*self->get_texture(self), self->rectangle, self->position, self->color);
}

static  Texture2D *frame_get_texture(const Frame *self)
{
    return &self->_texture->_texture2D;
}

static unsigned frame_get_texture_width(const Frame *self)
{
    return self->_texture->get_width(self->_texture);
}
static unsigned frame_get_texture_height(const Frame *self)
{
    return self->_texture->get_height(self->_texture);
}

static void frame_check_margins(const Frame *self)
{
    // TODO: update after screen implementation.
    float *frame_x = &self->position.x;
    float *frame_y = &self->position.y;
    const unsigned width = self->get_texture_width(self) /4;
    unsigned screen_width = GetScreenWidth();
    unsigned screen_height = GetScreenHeight();

        printf("x: %.3f  screen_width: %d (width/3)+x: %.3f width: %d\n", *frame_x, 
               screen_width, (float)*frame_x+self->get_texture_width(self), self->get_texture_width(self));
    // Check x-axis.
    if (*frame_x +  width> screen_width)
        *frame_x = (float)screen_width - width;
    else if (*frame_x < 1.0f)
        *frame_x = 1.0f;
    
    // Check y-axis.
    if (*frame_y+self->get_texture_height(self) > screen_height)
        *frame_y = (float)screen_height - self->get_texture_height(self);
    else if (*frame_y < 1)
        *frame_y = 1.0f;
}