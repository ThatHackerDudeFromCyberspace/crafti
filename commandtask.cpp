#include "commandtask.h"

#include "font.h"
#include <map>
#include "worldtask.h"
/*
std::map<t_key, char> keyToLetter {
    {KEY_NSPIRE_A, 'A'},
    {KEY_NSPIRE_B, 'B'},
    {KEY_NSPIRE_C, 'C'},
    {KEY_NSPIRE_D, 'D'},
    {KEY_NSPIRE_E, 'E'},
    {KEY_NSPIRE_F, 'F'},
    {KEY_NSPIRE_G, 'G'},
    {KEY_NSPIRE_H, 'H'},
    {KEY_NSPIRE_I, 'I'},
    {KEY_NSPIRE_J, 'J'},
    {KEY_NSPIRE_K, 'K'},
    {KEY_NSPIRE_L, 'L'},
    {KEY_NSPIRE_M, 'M'},
    {KEY_NSPIRE_N, 'N'},
    {KEY_NSPIRE_O, 'O'},
    {KEY_NSPIRE_P, 'P'},
    {KEY_NSPIRE_Q, 'Q'},
    {KEY_NSPIRE_R, 'R'},
    {KEY_NSPIRE_S, 'S'},
    {KEY_NSPIRE_T, 'T'},
    {KEY_NSPIRE_U, 'U'},
    {KEY_NSPIRE_V, 'V'},
    {KEY_NSPIRE_W, 'W'},
    {KEY_NSPIRE_Q, 'Q'},
    {KEY_NSPIRE_Y, 'Y'},
    {KEY_NSPIRE_Z, 'Z'},
    {KEY_NSPIRE_1, '1'},
    {KEY_NSPIRE_2, '2'},
    {KEY_NSPIRE_3, '3'},
    {KEY_NSPIRE_4, '4'},
    {KEY_NSPIRE_5, '5'},
    {KEY_NSPIRE_6, '6'},
    {KEY_NSPIRE_7, '7'},
    {KEY_NSPIRE_8, '8'},
    {KEY_NSPIRE_9, '9'},
    {KEY_NSPIRE_0, '0'},
    {KEY_NSPIRE_MINUS, '_'},
    {KEY_NSPIRE_TRIG, 'I'}
};*/

CommandTask command_task;

CommandTask::CommandTask()
{
    background = newTexture(background_width, background_height, 0, false);
}

CommandTask::~CommandTask()
{
    deleteTexture(background);
}

void CommandTask::makeCurrent()
{
    if(!background_saved)
        saveBackground();

    Task::makeCurrent();
}

void CommandTask::render()
{
    drawBackground();

    const unsigned int x = ((SCREEN_WIDTH - background->width) / 2);
    const unsigned int y = ((SCREEN_HEIGHT - background->height) / 2);
    drawTextureOverlay(*background, 0, 0, *screen, x, y, background->width, background->height);

    drawString("Commands for Crafti v1.4 [C14DB]", 0xFFFF, *screen, x + background_inner_offset, y + background_inner_offset);

    char number[10];
    snprintf(number, sizeof(number), "%d", background_height/fontHeight());

    drawString( "/help - explodes\n"
                "/explode - explodes\n"
                "/hello\n"
                "tp\n"
                "/gamemode\n"
                "fdsfsd\n"
                "Answer is: ", 0xFFFF, *screen, x + background_inner_offset, y + background_inner_offset + fontHeight());
    drawString(number, 0xFFFF, *screen, x + background_inner_offset + 100, y + background_inner_offset + 100);


    // Draw Bottom Command-Typing Box
    const unsigned int bottom_height = fontHeight()*2;
    const unsigned int bottom_y = (background_height + background_offset) - (fontHeight()*2);
    drawTextureOverlay(*background, 0, 0, *screen, x, bottom_y, background->width, bottom_height);
}

void CommandTask::logic()
{
    if(key_held_down)
        key_held_down = keyPressed(KEY_NSPIRE_ESC) || keyPressed(KEY_NSPIRE_DIVIDE);
    else if(keyPressed(KEY_NSPIRE_ESC) || keyPressed(KEY_NSPIRE_DIVIDE))
    {
        world_task.makeCurrent();

        key_held_down = true;
    }
}