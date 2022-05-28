#include "cactusrenderer.h"

constexpr GLFix CactusRenderer::cactus_height, CactusRenderer::cactus_width;

void CactusRenderer::renderSpecialBlock(const BLOCK_WDATA block, GLFix x, GLFix y, GLFix z, Chunk &c)
{
    // NOTE: CACTUS BOTTOM IS MANAGED LIKE A NORMAL BLOCK


    // Cactus offset, the offsettiness of the cactus (it isn't a full block ya know)
    const GLFix cactus_offset = (GLFix(BLOCK_SIZE) - cactus_width) * GLFix(0.5f);
    const TextureAtlasEntry &cactus_top = terrain_atlas[5][4].current;
    TextureAtlasEntry cactus_sid = terrain_atlas[6][4].current;

    cactus_sid.top = cactus_sid.top + (cactus_sid.bottom - cactus_sid.top) * 9 / 16;


    //////
    // GL CODE
    //////
    glPushMatrix();
    glLoadIdentity();

    glTranslatef(x + BLOCK_SIZE/2, y + BLOCK_SIZE/2, z + BLOCK_SIZE/2);

    std::vector<VERTEX> cactus_vertices;
    cactus_vertices.reserve(20);

    //cactus_sid.right = cactus_sid.right - (cactus_sid.right - cactus_sid.left) * (cactus_max_bites - cactus_bites) / 6;

    GLFix cactus_left_texturemap = cactus_sid.left;
    GLFix cactus_right_texturemap = cactus_sid.right;

    GLFix cactus_top_texturemap = cactus_top.right;


    // Cactus Side
    cactus_vertices.push_back({0, 0, GLFix(0) + cactus_offset, cactus_sid.left, cactus_sid.bottom, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({0, GLFix(0) + cactus_height, GLFix(0) + cactus_offset, cactus_sid.left, cactus_sid.top, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({GLFix(0) + cactus_width, GLFix(0) + cactus_height, GLFix(0) + cactus_offset, cactus_right_texturemap, cactus_sid.top, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({GLFix(0) + cactus_width, 0, GLFix(0) + cactus_offset, cactus_right_texturemap, cactus_sid.bottom, TEXTURE_TRANSPARENT});

    // Cactus Side
    cactus_vertices.push_back({GLFix(0) + cactus_width, 0, GLFix(0) - cactus_offset + BLOCK_SIZE, cactus_left_texturemap, cactus_sid.bottom, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({GLFix(0) + cactus_width, GLFix(0) + cactus_height, GLFix(0) - cactus_offset + BLOCK_SIZE, cactus_left_texturemap, cactus_sid.top, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({0, GLFix(0) + cactus_height, GLFix(0) - cactus_offset + BLOCK_SIZE, cactus_sid.right, cactus_sid.top, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({0, 0, GLFix(0) - cactus_offset + BLOCK_SIZE, cactus_sid.right, cactus_sid.bottom, TEXTURE_TRANSPARENT});

    // Cactus Back Side
    cactus_vertices.push_back({GLFix(0) + cactus_offset, 0, GLFix(0) + BLOCK_SIZE, cactus_sid.left, cactus_sid.bottom, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({GLFix(0) + cactus_offset, GLFix(0) + cactus_height, 0 + BLOCK_SIZE, cactus_sid.left, cactus_sid.top, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({GLFix(0) + cactus_offset, GLFix(0) + cactus_height, 0, cactus_sid.right, cactus_sid.top, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({GLFix(0) + cactus_offset, 0, 0, cactus_sid.right, cactus_sid.bottom, TEXTURE_TRANSPARENT});

    // Cactus (Front) Inside
    cactus_vertices.push_back({(GLFix(0) - cactus_offset) + cactus_width, 0, 0, cactus_sid.left, cactus_sid.bottom, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({(GLFix(0) - cactus_offset) + cactus_width, GLFix(0) + cactus_height, 0, cactus_sid.left, cactus_sid.top, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({(GLFix(0) - cactus_offset) + cactus_width, GLFix(0) + cactus_height, 0 + BLOCK_SIZE, cactus_sid.right, cactus_sid.top, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({(GLFix(0) - cactus_offset) + cactus_width, 0, 0 + BLOCK_SIZE, cactus_sid.right, cactus_sid.bottom, TEXTURE_TRANSPARENT});

    // Cactus Top
    cactus_vertices.push_back({GLFix(0) + cactus_offset, GLFix(0) + cactus_height, GLFix(0) + cactus_offset, cactus_top.left, cactus_top.bottom, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({GLFix(0) + cactus_offset, GLFix(0) + cactus_height, GLFix(0) + BLOCK_SIZE - cactus_offset, cactus_top.left, cactus_top.top, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({GLFix(0) + cactus_width - cactus_offset, GLFix(0) + cactus_height, GLFix(0) + BLOCK_SIZE - cactus_offset, cactus_top_texturemap, cactus_top.top, TEXTURE_TRANSPARENT});
    cactus_vertices.push_back({GLFix(0) + cactus_width - cactus_offset, GLFix(0) + cactus_height, GLFix(0) + cactus_offset, cactus_top_texturemap, cactus_top.bottom, TEXTURE_TRANSPARENT});

    // Rotate Cactus According To Face
    BLOCK_SIDE side = static_cast<BLOCK_SIDE>(getBLOCKDATA(block) & BLOCK_SIDE_BITS);


    switch(side)
    {
        default:
            break;
        case BLOCK_BACK:
            nglRotateY(270);
            break;
        case BLOCK_FRONT:
            nglRotateY(90);
            break;
        case BLOCK_LEFT:
            nglRotateY(180);
            break;
        case BLOCK_RIGHT:
            nglRotateY(0);
            break;
    }

    glTranslatef(-BLOCK_SIZE / 2, -BLOCK_SIZE / 2, -BLOCK_SIZE / 2);

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

AABB CactusRenderer::getAABB(const BLOCK_WDATA block, GLFix x, GLFix y, GLFix z)
{
    // Get block side
    BLOCK_SIDE side = static_cast<BLOCK_SIDE>(getBLOCKDATA(block) & BLOCK_SIDE_BITS);
    const GLFix cactus_offset = (GLFix(BLOCK_SIZE) - cactus_width) * GLFix(0.5f);

    return {x + cactus_offset, y, z + cactus_offset, x + cactus_offset + cactus_width, y + cactus_height, z + cactus_offset + cactus_width};
}

void CactusRenderer::drawPreview(const BLOCK_WDATA /*block*/, TEXTURE &dest, int x, int y)
{
    TextureAtlasEntry &tex = terrain_atlas[7][4].resized;
    BlockRenderer::drawTextureAtlasEntry(*terrain_resized, tex, dest, x, y);
}

const char *CactusRenderer::getName(const BLOCK_WDATA /*block*/)
{
    return "Cactus";
}