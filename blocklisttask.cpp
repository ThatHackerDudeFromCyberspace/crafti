#include "blocklisttask.h"

#include <algorithm>

#include "blockrenderer.h"
#include "font.h"
#include "inventory.h"
#include "terrain.h"
#include "texturetools.h"
#include "worldtask.h"

#include "textures/scrollbar.h"

BlockListTask block_list_task;

static const BLOCK_WDATA user_selectable[] = {
    BLOCK_STONE,
    BLOCK_COBBLESTONE,
    BLOCK_DIRT,
    BLOCK_GRASS,
    BLOCK_SAND,
    BLOCK_WOOD,
    BLOCK_LEAVES,
    BLOCK_PLANKS_NORMAL,
    BLOCK_PLANKS_DARK,
    BLOCK_PLANKS_BRIGHT,
    BLOCK_WALL,
    BLOCK_GLASS,
    BLOCK_DOOR,
    BLOCK_COAL_ORE,
    BLOCK_GOLD_ORE,
    BLOCK_IRON_ORE,
    BLOCK_DIAMOND_ORE,
    BLOCK_REDSTONE_ORE,
    BLOCK_IRON,
    BLOCK_GOLD,
    BLOCK_DIAMOND,
    BLOCK_GLOWSTONE,
    BLOCK_NETHERRACK,
    BLOCK_TNT,
    BLOCK_SPONGE,
    BLOCK_FURNACE,
    BLOCK_CRAFTING_TABLE,
    BLOCK_BOOKSHELF,
    BLOCK_PUMPKIN,
    getBLOCKWDATA(BLOCK_WATER, RANGE_WATER),
    getBLOCKWDATA(BLOCK_LAVA, RANGE_LAVA),
    getBLOCKWDATA(BLOCK_FLOWER, 0),
    getBLOCKWDATA(BLOCK_FLOWER, 1),
    getBLOCKWDATA(BLOCK_MUSHROOM, 0),
    getBLOCKWDATA(BLOCK_MUSHROOM, 1),
    getBLOCKWDATA(BLOCK_WHEAT, 0),
    BLOCK_SPIDERWEB,
    BLOCK_TORCH,
    getBLOCKWDATA(BLOCK_CAKE, 0),
    BLOCK_REDSTONE_LAMP,
    BLOCK_REDSTONE_SWITCH,
    BLOCK_PRESSURE_PLATE,
    BLOCK_REDSTONE_WIRE,
    BLOCK_REDSTONE_TORCH,
    getBLOCKWDATA(BLOCK_WOOL, 0),
    getBLOCKWDATA(BLOCK_WOOL, 1),
    getBLOCKWDATA(BLOCK_WOOL, 2),
    getBLOCKWDATA(BLOCK_WOOL, 3),
    getBLOCKWDATA(BLOCK_WOOL, 4),
    getBLOCKWDATA(BLOCK_WOOL, 5),
    getBLOCKWDATA(BLOCK_WOOL, 6),
    getBLOCKWDATA(BLOCK_WOOL, 7),
    getBLOCKWDATA(BLOCK_WOOL, 8),
    getBLOCKWDATA(BLOCK_WOOL, 9),
    getBLOCKWDATA(BLOCK_WOOL, 10),
    getBLOCKWDATA(BLOCK_WOOL, 11),
    getBLOCKWDATA(BLOCK_WOOL, 12),
    getBLOCKWDATA(BLOCK_WOOL, 13),
    getBLOCKWDATA(BLOCK_WOOL, 14),
    getBLOCKWDATA(BLOCK_WOOL, 15),

    BLOCK_CACTUS,
    getBLOCKWDATA(BLOCK_SLAB, 0),
    getBLOCKWDATA(BLOCK_SLAB, 1),
    getBLOCKWDATA(BLOCK_SLAB, 2),
    getBLOCKWDATA(BLOCK_SLAB, 3),
    getBLOCKWDATA(BLOCK_SLAB, 4),
    getBLOCKWDATA(BLOCK_SLAB, 5),
    getBLOCKWDATA(BLOCK_SLAB, 6),
    getBLOCKWDATA(BLOCK_SLAB, 7),

    getBLOCKWDATA(BLOCK_CARPET, 0),
    getBLOCKWDATA(BLOCK_CARPET, 1),
    getBLOCKWDATA(BLOCK_CARPET, 2),
    getBLOCKWDATA(BLOCK_CARPET, 3),
    getBLOCKWDATA(BLOCK_CARPET, 4),
    getBLOCKWDATA(BLOCK_CARPET, 5),
    getBLOCKWDATA(BLOCK_CARPET, 6),
    getBLOCKWDATA(BLOCK_CARPET, 7),
    getBLOCKWDATA(BLOCK_CARPET, 8),
    getBLOCKWDATA(BLOCK_CARPET, 9),
    getBLOCKWDATA(BLOCK_CARPET, 10),
    getBLOCKWDATA(BLOCK_CARPET, 11),
    getBLOCKWDATA(BLOCK_CARPET, 12),
    getBLOCKWDATA(BLOCK_CARPET, 13),
    getBLOCKWDATA(BLOCK_CARPET, 14),
    getBLOCKWDATA(BLOCK_CARPET, 15),

    getBLOCKWDATA(BLOCK_STAIRS, 0 << 3), // Stairs
    getBLOCKWDATA(BLOCK_STAIRS, 1 << 3),
    getBLOCKWDATA(BLOCK_STAIRS, 2 << 3),
    getBLOCKWDATA(BLOCK_STAIRS, 3 << 3),
    getBLOCKWDATA(BLOCK_STAIRS, 4 << 3),
    getBLOCKWDATA(BLOCK_STAIRS, 5 << 3),
    getBLOCKWDATA(BLOCK_STAIRS, 6 << 3),
    getBLOCKWDATA(BLOCK_STAIRS, 7 << 3)
};

//The values have to stay somewhere
unsigned int BlockListTask::blocklist_top;
//Black texture as background
TEXTURE *BlockListTask::blocklist_background;

int BlockListTask::screen_offset_y;

constexpr int user_selectable_count = sizeof(user_selectable) / sizeof(*user_selectable);

BlockListTask::BlockListTask()
{
    screen_offset_y = 0;
    blocklist_top = (SCREEN_HEIGHT - blocklist_height - current_inventory.height()) / 2;

    static_assert(field_width * fields_x <= SCREEN_WIDTH, "fields_x too high");
    //static_assert(fields_x * fields_y >= sizeof(user_selectable)/sizeof(*user_selectable), "Not enough fields");
    if (blocklist_height + current_inventory.height() > SCREEN_WIDTH)
        printf("fields_y too high\n");

    blocklist_background = newTexture(blocklist_width, blocklist_height, 0, false);
}

BlockListTask::~BlockListTask()
{
    deleteTexture(blocklist_background);
}

void BlockListTask::makeCurrent()
{
    if (!background_saved)
        saveBackground();

    Task::makeCurrent();

    moveScreenOffset();
}

inline int divrnd(int num, int den)
{
    return (num + (den - 1)) / den;
}

void BlockListTask::render()
{
    drawBackground();

    drawTextureOverlay(*blocklist_background, 0, 0, *screen, blocklist_left, blocklist_top, blocklist_background->width, blocklist_background->height);

    int block_nr = screen_offset_y * fields_x;
    int screen_x, screen_y = blocklist_top + pad_y;
    // For each row
    for (int y = screen_offset_y; y < fields_y + screen_offset_y; y++, screen_y += field_height)
    {
        screen_x = blocklist_left + pad_x;
        // For each cell
        for (int x = 0; x < fields_x; x++, screen_x += field_width)
        {
            //BLOCK_DOOR is twice as high, so center it manually
            if (getBLOCK(user_selectable[block_nr]) == BLOCK_DOOR)
                global_block_renderer.drawPreview(user_selectable[block_nr], *screen, screen_x + pad_x, screen_y + pad_y_door);
            else
                global_block_renderer.drawPreview(user_selectable[block_nr], *screen, screen_x + pad_x, screen_y + pad_y);

            // Increment cell count and exit loop once entire block list is rendered
            block_nr++;
            if (block_nr == user_selectable_count)
                goto end;
        }
    }

end:

    //Draw the selection indicator
    screen_x = blocklist_left + pad_x + field_width * (current_selection % fields_x);
    screen_y = blocklist_top + pad_y + field_height * (current_selection / fields_x - screen_offset_y);
    drawTexture(*inv_selection_p, *screen, 0, 0, inv_selection_p->width, inv_selection_p->height, screen_x + pad_x - 11, screen_y + pad_y - 10, inv_selection_p->width, inv_selection_p->height);

    //Draw the scrollbar on the right
    screen_x = blocklist_left + blocklist_width;
    screen_y = blocklist_top;
    drawTexture(scrollbar, *screen, 0, 11 * 2, scrollbar.width, 11, screen_x, screen_y, 11, 11); // Up arrow

    screen_y += blocklist_height - 11;
    drawTexture(scrollbar, *screen, 0, 11 * 3, scrollbar.width, 11, screen_x, screen_y, 11, 11); // Down arrow
    
    screen_y = blocklist_top + 11;
    drawTexture(scrollbar, *screen, 0, 11 * 1, scrollbar.width, 11, screen_x, screen_y, 11, blocklist_height - 22); // Scrollbar background
    
    int rows = divrnd(user_selectable_count, fields_x);
    int scrollbar_height = ((blocklist_height - 22) * fields_y) / rows;
    int scrollbar_pos = ((blocklist_height - 22) * screen_offset_y) / rows;

    screen_y += scrollbar_pos;
    drawTexture(scrollbar, *screen, 0, 11 * 0, scrollbar.width, 11, screen_x, screen_y, 11, scrollbar_height); // Scrollbar foreground

    current_inventory.draw(*screen);
    drawStringCenter(global_block_renderer.getName(user_selectable[current_selection]), 0xFFFF, *screen, SCREEN_WIDTH / 2, SCREEN_HEIGHT - current_inventory.height() - fontHeight());
}

void BlockListTask::moveScreenOffset()
{
    // Clamp how much grater current row is from max onscreen fields
    if (current_selection >= fields_x * (fields_y + screen_offset_y))
        screen_offset_y = std::max((current_selection / fields_x) - fields_y + 1, 0);
    // Clamp screen_offset_y to current row
    else if (current_selection <= fields_x * (screen_offset_y))
        screen_offset_y = std::min((current_selection / fields_x), screen_offset_y);
}

void BlockListTask::logic()
{
    if (key_held_down)
        key_held_down = keyPressed(KEY_NSPIRE_ESC) || keyPressed(KEY_NSPIRE_PERIOD) || keyPressed(KEY_NSPIRE_2) || keyPressed(KEY_NSPIRE_8) || keyPressed(KEY_NSPIRE_4) || keyPressed(KEY_NSPIRE_6) || keyPressed(KEY_NSPIRE_1) || keyPressed(KEY_NSPIRE_3) || keyPressed(KEY_NSPIRE_5) || keyPressed(KEY_NSPIRE_UP) || keyPressed(KEY_NSPIRE_DOWN) || keyPressed(KEY_NSPIRE_LEFT) || keyPressed(KEY_NSPIRE_RIGHT) || keyPressed(KEY_NSPIRE_CLICK) || keyPressed(KEY_NSPIRE_ENTER) || keyPressed(KEY_NSPIRE_W) || keyPressed(KEY_NSPIRE_A) || keyPressed(KEY_NSPIRE_S) || keyPressed(KEY_NSPIRE_D) || keyPressed(KEY_NSPIRE_Z) || keyPressed(KEY_NSPIRE_C);
    else if (keyPressed(KEY_NSPIRE_ESC) || keyPressed(KEY_NSPIRE_PERIOD))
    {
        world_task.makeCurrent();

        key_held_down = true;
    }
    else if(keyPressed(KEY_NSPIRE_2) || keyPressed(KEY_NSPIRE_DOWN) || keyPressed(KEY_NSPIRE_S))
    {
        const int rows = ((user_selectable_count + fields_x - 1) / fields_x);
        // Increment current cell by row size and overflow
        current_selection += fields_x;

        if (current_selection >= user_selectable_count)
        {
            if (current_selection > rows * fields_x)
                current_selection %= fields_x;
            else
                current_selection = user_selectable_count - 1;
        }

        moveScreenOffset();

        key_held_down = true;
    }
    else if (keyPressed(KEY_NSPIRE_8) || keyPressed(KEY_NSPIRE_UP) || keyPressed(KEY_NSPIRE_W))
    {
        // (Here, there is a fast path, and a slow path for if the inventory size is not full)
        // Decrement current cell  by row size and underflow

        if (current_selection >= fields_x)
            current_selection -= fields_x;
        else
        {
            // Floor off extra cells in last row and add current x (??)
            current_selection = ((user_selectable_count - 1) / fields_x) * fields_x + (current_selection % fields_x);
            if (current_selection >= user_selectable_count)
                current_selection = user_selectable_count - 1;
        }

        moveScreenOffset();

        key_held_down = true;
    }
    else if (keyPressed(KEY_NSPIRE_4) || keyPressed(KEY_NSPIRE_LEFT) || keyPressed(KEY_NSPIRE_A))
    {
        // If cell x is at 0, then send cursor to other side
        if (current_selection % fields_x == 0)
        {
            current_selection += fields_x - 1;
            // And if there is less than the usual row size in the last row, then move back the cursor
            if (current_selection >= user_selectable_count)
                current_selection = user_selectable_count - 1;
        }
        // Otherwise, just decrement the selection
        else
            current_selection--;

        key_held_down = true;
    }
    else if (keyPressed(KEY_NSPIRE_6) || keyPressed(KEY_NSPIRE_RIGHT) || keyPressed(KEY_NSPIRE_D))
    {
        // If cell x is at the end of the row, move the cell back to the beginning of the row
        if (current_selection % fields_x == fields_x - 1 || current_selection >= user_selectable_count - 1)
            current_selection -= current_selection % fields_x;
        // Otherwise, increment the cell
        else
            current_selection++;

        key_held_down = true;
    }
    else if (keyPressed(KEY_NSPIRE_1) || keyPressed(KEY_NSPIRE_Z)) //Switch inventory slot
    {
        current_inventory.previousSlot();

        key_held_down = true;
    }
    else if (keyPressed(KEY_NSPIRE_3) || keyPressed(KEY_NSPIRE_C))
    {
        current_inventory.nextSlot();

        key_held_down = true;
    }
    else if (keyPressed(KEY_NSPIRE_5) || keyPressed(KEY_NSPIRE_CLICK) || keyPressed(KEY_NSPIRE_ENTER))
    {
        current_inventory.currentSlot() = user_selectable[current_selection];

        key_held_down = true;
    }
}
