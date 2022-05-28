#include "cactusrenderer.h"

constexpr GLFix CactusRenderer::cactus_width;

void CactusRenderer::renderSpecialBlock(const BLOCK_WDATA /*block*/, GLFix x, GLFix y, GLFix z, Chunk &c)
{
    // Cactus offset, the offsettiness of the cactus (it isn't a full block ya know)
    const GLFix cactus_offset = (GLFix(BLOCK_SIZE) - cactus_width) * GLFix(0.5f);

    const TextureAtlasEntry &cactus_top = terrain_atlas[5][4].current;
    TextureAtlasEntry cactus_sid = terrain_atlas[6][4].current;

    //////
    // GL CODE
    //////
    glPushMatrix();
    glLoadIdentity();
    
    glTranslatef(x, y, z);

    std::vector<VERTEX> cactus_vertices;
    cactus_vertices.reserve(20);


    // Cactus Side
    cactus_vertices.push_back({0, 0, cactus_offset, cactus_sid.left, cactus_sid.bottom, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({0, BLOCK_SIZE, cactus_offset, cactus_sid.left, cactus_sid.top, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({cactus_width, BLOCK_SIZE, cactus_offset, cactus_sid.right, cactus_sid.top, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({cactus_width, 0, cactus_offset, cactus_sid.right, cactus_sid.bottom, TEXTURE_TRANSPARENT});

    // Cactus Side
    cactus_vertices.push_back({cactus_width, 0, GLFix(0) - cactus_offset + BLOCK_SIZE, cactus_sid.left, cactus_sid.bottom, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({cactus_width, BLOCK_SIZE, GLFix(0) - cactus_offset + BLOCK_SIZE, cactus_sid.left, cactus_sid.top, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({0, BLOCK_SIZE, GLFix(0) - cactus_offset + BLOCK_SIZE, cactus_sid.right, cactus_sid.top, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({0, 0, GLFix(0) - cactus_offset + BLOCK_SIZE, cactus_sid.right, cactus_sid.bottom, TEXTURE_TRANSPARENT});

    // Cactus Back Side
    cactus_vertices.push_back({cactus_offset, 0, BLOCK_SIZE, cactus_sid.left, cactus_sid.bottom, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({cactus_offset, BLOCK_SIZE, BLOCK_SIZE, cactus_sid.left, cactus_sid.top, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({cactus_offset, BLOCK_SIZE, 0, cactus_sid.right, cactus_sid.top, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({cactus_offset, 0, 0, cactus_sid.right, cactus_sid.bottom, TEXTURE_TRANSPARENT});

    // Cactus (Front) Inside
    cactus_vertices.push_back({(GLFix(0) - cactus_offset) + cactus_width, 0, 0, cactus_sid.left, cactus_sid.bottom, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({(GLFix(0) - cactus_offset) + cactus_width, BLOCK_SIZE, 0, cactus_sid.left, cactus_sid.top, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({(GLFix(0) - cactus_offset) + cactus_width, BLOCK_SIZE, BLOCK_SIZE, cactus_sid.right, cactus_sid.top, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({(GLFix(0) - cactus_offset) + cactus_width, 0, BLOCK_SIZE, cactus_sid.right, cactus_sid.bottom, TEXTURE_TRANSPARENT});

    // Cactus Top
    cactus_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, cactus_top.left, cactus_top.bottom, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE - BLOCK_SIZE, cactus_top.left, cactus_top.top, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({cactus_width - BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE - BLOCK_SIZE, cactus_top.right, cactus_top.top, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({cactus_width - BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, cactus_top.right, cactus_top.bottom, TEXTURE_TRANSPARENT});

    for(auto&& v : cactus_vertices)
    {
        VERTEX v1;
        nglMultMatVectRes(transformation, &v, &v1);
        c.addUnalignedVertex(v1.x, v1.y, v1.z, v.u, v.v, v.c);
    }

    glPopMatrix();
}

void CactusRenderer::geometryNormalBlock(const BLOCK_WDATA /*block*/, const int local_x, const int local_y, const int local_z, const BLOCK_SIDE side, Chunk &c)
{
    // Render the bottom of the block as a normal side (needs to be replaced later)
    if(side != BLOCK_BOTTOM)
        return;

    // BOTTOM DOESN'T WORK!!! afdghtresdvbhtredfsvcbgfhtresd
    renderNormalBlockSide(local_x, local_y, local_z, side, terrain_atlas[12][7].current, c);
}

AABB CactusRenderer::getAABB(const BLOCK_WDATA /*block*/, GLFix x, GLFix y, GLFix z)
{
    const GLFix cactus_offset = (GLFix(BLOCK_SIZE) - cactus_width) * GLFix(0.5f);

    return {x + cactus_offset, y, z + cactus_offset, x + cactus_offset + cactus_width, y + BLOCK_SIZE, z + cactus_offset + cactus_width};
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