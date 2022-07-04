#ifndef PISTONRENDERER_H
#define PISTONRENDERER_H

#include "blockrenderer.h"

class PistonRenderer : public DumbBlockRenderer
{
public:
    virtual void renderSpecialBlock(const BLOCK_WDATA, GLFix x, GLFix y, GLFix z, Chunk &c) override;
    virtual void geometryNormalBlock(const BLOCK_WDATA, const int local_x, const int local_y, const int local_z, const BLOCK_SIDE side, Chunk &c) override;
    virtual bool isOpaque(const BLOCK_WDATA /*block*/) override { return false; }
    virtual bool isObstacle(const BLOCK_WDATA /*block*/) override { return true; }
    virtual bool isOriented(const BLOCK_WDATA /*block*/) override { return true; } // Oriented
    virtual bool isFullyOriented(const BLOCK_WDATA /*block*/) override { return false; } // Torch-like orientation

    virtual bool isBlockShaped(const BLOCK_WDATA /*block*/) override { return false; }
    virtual AABB getAABB(const BLOCK_WDATA, GLFix x, GLFix y, GLFix z) override;

    virtual void drawPreview(const BLOCK_WDATA block, TEXTURE &dest, int x, int y) override;

    virtual bool action(const BLOCK_WDATA block, const int local_x, const int local_y, const int local_z, Chunk &c) override;

    virtual const char* getName(const BLOCK_WDATA) override;

protected:
    static constexpr GLFix piston_height = BLOCK_SIZE;
    static constexpr GLFix piston_width = BLOCK_SIZE;
    const GLFix pistion_block_size = 0;

    /// Bitmap stuff
    static constexpr uint8_t piston_bit_shift = 4; // The amount to shift piston data by to give it room for the orientation or other additional data
    static constexpr uint8_t piston_data_bits = 0b111 << piston_bit_shift; // Piston uses 3 bits of data, however, orientation data is stored in the first three bits, so the piston data has to be shifted by 3 (or more)

    static constexpr uint8_t piston_max_bites = 6; // Maximum bites of piston you can have until it is eaten (after 4 bites, piston will dissapear)
};

#endif // PISTONRENDERER_H
