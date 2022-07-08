#include <cstdlib>

#include "redstoneblockrenderer.h"

void RedstoneBlockRenderer::geometryNormalBlock(const BLOCK_WDATA /*block*/, const int local_x, const int local_y, const int local_z, const BLOCK_SIDE side, Chunk &c)
{
    BlockRenderer::renderNormalBlockSide(local_x, local_y, local_z, side, terrain_atlas[10][1].current, c);
}

void RedstoneBlockRenderer::drawPreview(const BLOCK_WDATA /*block*/, TEXTURE &dest, int x, int y)
{
    BlockRenderer::drawTextureAtlasEntry(*terrain_resized, terrain_atlas[4][13].resized, dest, x, y);
}

PowerState RedstoneBlockRenderer::powersSide(const BLOCK_WDATA /*block*/, BLOCK_SIDE /*side*/)
{
    return PowerState::StronglyPowered;
}

const TerrainAtlasEntry &RedstoneBlockRenderer::destructionTexture(const BLOCK_WDATA /*block*/) {
    return terrain_atlas[10][1];
}

const char *RedstoneBlockRenderer::getName(const BLOCK_WDATA)
{
    return "Redstone Block";
}
