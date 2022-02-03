#include "main.h"

void draw_background(const Frame *self)
{
    static float scrolling = 0.f;
    scrolling -= 1.f;
    const float max = -self->_texture->_texture2D.width * 4.5f;
    if (scrolling <= max)
        scrolling = 0;
    DrawTextureEx(*self->get_texture(self), (Vector2){scrolling, self->position.y},
                  0.f, 4.5f, WHITE);
    DrawTextureEx(*self->get_texture(self), (Vector2){self->get_texture_width(self) * 4.5f 
                  + scrolling, self->position.y}, 0.f, 4.5f, WHITE);
}

int main(int argc, char const *argv[])
{
    // Windows size.
    const unsigned screenWidth = 1080;
    const unsigned screenHeight = 500;

    // The first thing. Init the window.
    InitWindow(screenWidth, screenHeight, APP_NAME);
    SetTargetFPS(60);

    IW_Texture *texture = texture_init("resources/spaceship-draft.png");
    Frame *frame = frame_init(texture, &(Vector2){100, (float)screenWidth / 3.5f}, &WHITE);
    Player *player = player_init(base_init("djose1164", PLAYER, frame));
    Alien *alien = player_init(base_init("Alien", MONSTER, frame_init(                 
        texture_init("resources/enemy.png"), &(Vector2){screenWidth - 300, 100}, &WHITE
    )));
    struct Update update = {
        .num = 2,
        .objcs = (void **){&player, &alien},
        .update_arr = (void **){&player->update, &alien->update}
        };
    struct Cleanup cleanup = {
        .num = 2,
        .objcs = (void **){&player, &alien},
        .del_arr = (void **){&player->del, &alien->del},
    };

    void *frames[] = {player, alien};
    Frame *background = frame_init(texture_init("./resources/space_with_stars.png"), &(Vector2){0, 0}, &WHITE);
    background->draw = draw_background;
    Screen *current = screen_init(string_init("Testing"), player, background, frames, &update, &cleanup);

    while (!WindowShouldClose())
    {
        current->update(current);
        BeginDrawing();
        ClearBackground(BLACK);
        current->render(current);
        EndDrawing();
    }

    current->del(current);
    CloseWindow();
    memory_check_counter();
    return 0;
}
