#include "commandtask.h"

#include "font.h"
#include "worldtask.h"

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

    const unsigned int x = (SCREEN_WIDTH - background->width) / 2;
    const unsigned int y = (SCREEN_HEIGHT - background->height) / 2;
    drawTextureOverlay(*background, 0, 0, *screen, x, y, background->width, background->height);

    drawString("Commands for Crafti v1.4 [C14DB]", 0xFFFF, *screen, x, y);
}

void CommandTask::logic()
{
    if(key_held_down)
        key_held_down = keyPressed(KEY_NSPIRE_ESC);
    else if(keyPressed(KEY_NSPIRE_ESC))
    {
        world_task.makeCurrent();

        key_held_down = true;
    }
}