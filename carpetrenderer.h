#ifndef CARPETRENDERER_H
#define CARPETRENDERER_H

#include "blockrenderer.h"

class CarpetRenderer : public DumbBlockRenderer
{
public:
    virtual void renderSpecialBlock(const BLOCK_WDATA, GLFix x, GLFix y, GLFix z, Chunk &c) override;
    virtual void geometryNormalBlock(const BLOCK_WDATA, const int local_x, const int local_y, const int local_z, const BLOCK_SIDE side, Chunk &c) override;
    virtual bool isOpaque(const BLOCK_WDATA /*block*/) override { return false; }
    virtual bool isObstacle(const BLOCK_WDATA /*block*/) override { return true; }
    virtual bool isOriented(const BLOCK_WDATA /*block*/) override { return false; } // Not oriented (for extra data)
    virtual bool isFullyOriented(const BLOCK_WDATA /*block*/) override { return false; } // Torch-like orientation

    virtual bool isBlockShaped(const BLOCK_WDATA /*block*/) override { return false; }
    virtual AABB getAABB(const BLOCK_WDATA, GLFix x, GLFix y, GLFix z) override;

    virtual void drawPreview(const BLOCK_WDATA block, TEXTURE &dest, int x, int y) override;
    
    // Used for particles spawned on destruction
    virtual const TerrainAtlasEntry &destructionTexture(const BLOCK_WDATA block) override;
    
    virtual void tick(const BLOCK_WDATA block, int local_x, int local_y, int local_z, Chunk &c) override;

    virtual const char* getName(const BLOCK_WDATA) override;

protected:
    const TerrainAtlasEntry &getCarpetTexture(const BLOCK_WDATA block);

    static constexpr GLFix carpet_height = BLOCK_SIZE / 16 * 1;
    static constexpr GLFix carpet_width = BLOCK_SIZE;

    // Carpet colour enum
    enum COLOUR {
        WHITE_CARPET=0, // white
        ORANGE_CARPET=1, // orange
        MAGENTA_CARPET=2, // magenta
        LIGHT_BLUE_CARPET=3, // light blue
        YELLOW_CARPET=4, // yellow
        LIME_CARPET=5, // lime
        PINK_CARPET=6, // pink
        GRAY_CARPET=7, // gray
        LIGHT_GRAY_CARPET=8, // light gray
        CYAN_CARPET=9, // cyan
        PURPLE_CARPET=10, // purple
        BLUE_CARPET=11, // blue
        BROWN_CARPET=12, // brown
        GREEN_CARPET=13, // green
        RED_CARPET=14, // red
        BLACK_CARPET=15 // black
    };
};

#endif // CARPETRENDERER_H
