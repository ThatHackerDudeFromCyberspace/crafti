#ifndef COMMANDTASK_H
#define COMMANDTASK_H

#include "task.h"
#include "gl.h"
#include <vector>

class CommandTask : public Task
{
public:
    CommandTask();
    virtual ~CommandTask();

    virtual void makeCurrent() override;

    virtual void render() override;
    virtual void logic() override;

private:
    char* vectorToChar(std::vector<char> vectorToConvert);
    static constexpr int background_offset = 10, background_width = SCREEN_WIDTH - background_offset, background_height = SCREEN_HEIGHT - background_offset, background_inner_offset = 10;
    
    std::vector<char> command = {'/'};
    std::vector<std::vector<char*>> commandOutput;

    TEXTURE *background;
};

extern CommandTask command_task;

#endif // COMMANDTASK_H
