#ifndef REDSTONERENDERER_H
#define REDSTONERENDERER_H

#include "blockrenderer.h"

class RedstoneBlockRenderer : public NormalBlockRenderer
{
public:
    virtual void geometryNormalBlock(const BLOCK_WDATA block, const int local_x, const int local_y, const int local_z, const BLOCK_SIDE side, Chunk &c) override;
    virtual void drawPreview(const BLOCK_WDATA, TEXTURE &dest, int x, int y) override;
     // Used for particles spawned on destruction
    virtual const TerrainAtlasEntry &destructionTexture(const BLOCK_WDATA block) override;

    virtual PowerState powersSide(const BLOCK_WDATA /*block*/, BLOCK_SIDE /*side*/) override;

    virtual const char* getName(const BLOCK_WDATA) override;
};

#endif // REDSTONERENDERER_H
