#ifndef COMMANDTASK_H
#define COMMANDTASK_H

#include "task.h"

#include "gl.h"

class CommandTask : public Task
{
public:
    CommandTask();
    virtual ~CommandTask();

    virtual void makeCurrent() override;

    virtual void render() override;
    virtual void logic() override;

private:
    static constexpr int background_width = SCREEN_WIDTH - 20, background_height = SCREEN_HEIGHT - 20, background_inner_offset = 10;
    TEXTURE *background;
};

extern CommandTask command_task;

#endif // COMMANDTASK_H
