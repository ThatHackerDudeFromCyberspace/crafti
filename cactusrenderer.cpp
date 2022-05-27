#include "cactusrenderer.h"

constexpr GLFix CactusRenderer::cactus_width;

void CactusRenderer::renderSpecialBlock(const BLOCK_WDATA block, GLFix x, GLFix y, GLFix z, Chunk &c)
{
    // NOTE: CACTUS BOTTOM IS MANAGED LIKE A NORMAL BLOCK

    // Cactus offset, the offsettiness of the cactus (it isn't a full block ya know)
    const GLFix cactus_offset = (GLFix(BLOCK_SIZE) - cactus_width) * GLFix(0.5f);

    const TextureAtlasEntry &cactus_top = terrain_atlas[5][4].current;

    TextureAtlasEntry cactus_sid = terrain_atlas[6][4].current;


    // Calculate the cake's size
    const GLFix cactus_width = cactus_width;

    //////
    // GL CODE
    //////
    c.addUnalignedVertex({x, y, z + cactus_offset, cactus_sid.left, cactus_sid.bottom, TEXTURE_TRANSPARENT});
    c.addUnalignedVertex({x, y + BLOCK_SIZE, z + cactus_offset, cactus_sid.left, cactus_sid.top, TEXTURE_TRANSPARENT});
    c.addUnalignedVertex({x + BLOCK_SIZE, y + BLOCK_SIZE, z + cactus_offset, cactus_sid.right, cactus_sid.top, TEXTURE_TRANSPARENT});
    c.addUnalignedVertex({x + BLOCK_SIZE, y, z + cactus_offset, cactus_sid.right, cactus_sid.bottom, TEXTURE_TRANSPARENT});

    c.addUnalignedVertex({x + BLOCK_SIZE, y, z - cactus_offset + BLOCK_SIZE, cactus_sid.left, cactus_sid.bottom, TEXTURE_TRANSPARENT});
    c.addUnalignedVertex({x + BLOCK_SIZE, y + BLOCK_SIZE, z - cactus_offset + BLOCK_SIZE, cactus_sid.left, cactus_sid.top, TEXTURE_TRANSPARENT});
    c.addUnalignedVertex({x, y + BLOCK_SIZE, z - cactus_offset + BLOCK_SIZE, cactus_sid.right, cactus_sid.top, TEXTURE_TRANSPARENT});
    c.addUnalignedVertex({x, y, z - cactus_offset + BLOCK_SIZE, cactus_sid.right, cactus_sid.bottom, TEXTURE_TRANSPARENT});

    c.addUnalignedVertex({x + cactus_offset, y, z + BLOCK_SIZE, cactus_sid.left, cactus_sid.bottom, TEXTURE_TRANSPARENT});
    c.addUnalignedVertex({x + cactus_offset, y + BLOCK_SIZE, z + BLOCK_SIZE, cactus_sid.left, cactus_sid.top, TEXTURE_TRANSPARENT});
    c.addUnalignedVertex({x + cactus_offset, y + BLOCK_SIZE, z, cactus_sid.right, cactus_sid.top, TEXTURE_TRANSPARENT});
    c.addUnalignedVertex({x + cactus_offset, y, z, cactus_sid.right, cactus_sid.bottom, TEXTURE_TRANSPARENT});

    c.addUnalignedVertex({x - cactus_offset + BLOCK_SIZE, y, z, cactus_sid.left, cactus_sid.bottom, TEXTURE_TRANSPARENT});
    c.addUnalignedVertex({x - cactus_offset + BLOCK_SIZE, y + BLOCK_SIZE, z, cactus_sid.left, cactus_sid.top, TEXTURE_TRANSPARENT});
    c.addUnalignedVertex({x - cactus_offset + BLOCK_SIZE, y + BLOCK_SIZE, z + BLOCK_SIZE, cactus_sid.right, cactus_sid.top, TEXTURE_TRANSPARENT});
    c.addUnalignedVertex({x - cactus_offset + BLOCK_SIZE, y, z + BLOCK_SIZE, cactus_sid.right, cactus_sid.bottom, TEXTURE_TRANSPARENT});

    // Top
    c.addUnalignedVertex({x + cactus_offset, y + BLOCK_SIZE, z + cactus_offset, cactus_top.left, cactus_top.bottom, TEXTURE_TRANSPARENT});
    c.addUnalignedVertex({x + cactus_offset, y + BLOCK_SIZE, z + BLOCK_SIZE - cactus_offset, cactus_top.left, cactus_top.top, TEXTURE_TRANSPARENT});
    c.addUnalignedVertex({x + BLOCK_SIZE - cactus_offset, y + BLOCK_SIZE, z + BLOCK_SIZE - cactus_offset, cactus_top.right, cactus_top.top, TEXTURE_TRANSPARENT});
    c.addUnalignedVertex({x + BLOCK_SIZE - cactus_offset, y + BLOCK_SIZE, z + cactus_offset, cactus_top.right, cactus_top.bottom, TEXTURE_TRANSPARENT});
}

void CactusRenderer::geometryNormalBlock(const BLOCK_WDATA /*block*/, const int local_x, const int local_y, const int local_z, const BLOCK_SIDE side, Chunk &c)
{
    // Render the bottom of the block as a normal side (needs to be replaced later)
    if(side != BLOCK_BOTTOM)
        return;

    // BOTTOM DOESN'T WORK!!! afdghtresdvbhtredfsvcbgfhtresd
    renderNormalBlockSide(local_x, local_y, local_z, side, terrain_atlas[7][4].current, c);
}

AABB CactusRenderer::getAABB(const BLOCK_WDATA block, GLFix x, GLFix y, GLFix z)
{
    const GLFix cactus_offset = (GLFix(BLOCK_SIZE) - cactus_width) * GLFix(0.5f);

    return {x + cactus_offset, y, z + cactus_offset + cactus_width, x + cactus_offset + cactus_width, y + BLOCK_SIZE, z + cactus_offset + cactus_width};
}

void CactusRenderer::drawPreview(const BLOCK_WDATA /*block*/, TEXTURE &dest, int x, int y)
{
    TextureAtlasEntry &tex = terrain_atlas[6][4].resized;
    BlockRenderer::drawTextureAtlasEntry(*terrain_resized, tex, dest, x, y);
}

const char *CactusRenderer::getName(const BLOCK_WDATA /*block*/)
{
    return "Cactus";
}