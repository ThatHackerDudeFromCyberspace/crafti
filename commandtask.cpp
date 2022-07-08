#include "commandtask.h"

#include "font.h"
#include <map>
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

    const unsigned int x = (background_offset / 2);
    const unsigned int y = (background_offset / 2);
    drawTextureOverlay(*background, 0, 0, *screen, x, y, background->width, background->height);

    drawString("Commands for Crafti v1.4 [C14DB]", 0xFFFF, *screen, x + background_inner_offset, y + background_inner_offset);

    char number[10];
    snprintf(number, sizeof(number), "%d", background_height/fontHeight());

    commandOutput = {
        {command[0], "1"},
        {"there", "2"},
        {"testing", "3"},
        {"stuff", "4"},
        {"there", "5"},
        {"should", "6"},
        {"be", "7"},
        {"a", "8"},
        {"maximum", "9"},
        {"number", "10"},
        {"of", "11"}
    };

    for (size_t i = 0; i < commandOutput.size(); i++) {
        drawString(commandOutput[i][0], 0xFFFF, *screen, x+background_inner_offset, y + background_inner_offset + (fontHeight() * (i+2)));
        drawString(commandOutput[i][1], 0xFFFF, *screen, x+background_inner_offset+(background_width/2), y + background_inner_offset + (fontHeight() * (i+2)));
    }

    drawString(number, 0xFFFF, *screen, x + background_inner_offset + 100, y + background_inner_offset + 100);


    // Draw Bottom Command-Typing Box
    const unsigned int bottom_height = fontHeight()*2;
    const unsigned int bottom_y = (background_height + background_offset/2) - (fontHeight()*2);
    drawTextureOverlay(*background, 0, 0, *screen, x, bottom_y, background->width, bottom_height);

    // Convert the vector to a char array
    char charConverted[command.size()];

    for (int i = 0; i < command.size(); i++) {
        charConverted[i] = command[i];
    }

    drawString(charConverted, 0xFFFF, *screen, x + background_inner_offset, bottom_y + (fontHeight()/2));
}

void CommandTask::logic()
{
    if(key_held_down)
        key_held_down = keyPressed(KEY_NSPIRE_ESC) || keyPressed(KEY_NSPIRE_DIVIDE) || keyPressed(KEY_NSPIRE_A);
    else if(keyPressed(KEY_NSPIRE_ESC) || keyPressed(KEY_NSPIRE_DIVIDE))
    {
        world_task.makeCurrent();

        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_A)) {
        command.push_back('a');

        key_held_down = true;
    }
}