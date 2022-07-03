#include "pistonrenderer.h"

constexpr GLFix PistonRenderer::piston_height, PistonRenderer::piston_width;

void PistonRenderer::renderSpecialBlock(const BLOCK_WDATA block, GLFix x, GLFix y, GLFix z, Chunk &c)
{
    // NOTE: PISTON BOTTOM IS MANAGED LIKE A NORMAL BLOCK

    // Piston offset, the offsettiness of the piston (it isn't a full block ya know)
    const GLFix piston_offset = (GLFix(BLOCK_SIZE) - piston_width) * GLFix(0.5f);
    const TextureAtlasEntry &piston_top = terrain_atlas[9][7].current;
    TextureAtlasEntry piston_sid = terrain_atlas[10][7].current;


    /////
    // Get the piston data
    /////
    const uint8_t piston_bites = 0;


    piston_sid.top = piston_sid.top + (piston_sid.bottom - piston_sid.top) * 9 / 16;
    
    // If piston not full, set "inside" to standard side
    TextureAtlasEntry piston_inside = piston_sid;

    if (piston_bites > 0) {
        // Piston inside only if piston is not full
        piston_inside = terrain_atlas[11][7].current;
        piston_inside.top = piston_inside.top + (piston_inside.bottom - piston_inside.top) * 9 / 16;
    }



    // Calculate the piston's size
    const GLFix piston_size = (piston_width / piston_max_bites) * (piston_max_bites - piston_bites);


    //////
    // GL CODE
    //////
    glPushMatrix();
    glLoadIdentity();

    glTranslatef(x + BLOCK_SIZE/2, y + BLOCK_SIZE/2, z + BLOCK_SIZE/2);

    std::vector<VERTEX> piston_vertices;
    piston_vertices.reserve(20);

    // Get "texturemap" thingies for piston
    GLFix piston_left_texturemap = piston_sid.right - (piston_sid.right - piston_sid.left) * (piston_max_bites - piston_bites) / piston_max_bites;
    GLFix piston_right_texturemap = piston_sid.left + (piston_sid.right - piston_sid.left) * (piston_max_bites - piston_bites) / piston_max_bites;
    GLFix piston_top_texturemap = piston_top.left + (piston_top.right - piston_top.left) * (piston_max_bites - piston_bites) / piston_max_bites;


    // Piston Side
    piston_vertices.push_back({0, 0, GLFix(0) + piston_offset, piston_sid.left, piston_sid.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, GLFix(0) + piston_height, GLFix(0) + piston_offset, piston_sid.left, piston_sid.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({GLFix(0) + piston_size, GLFix(0) + piston_height, GLFix(0) + piston_offset, piston_right_texturemap, piston_sid.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({GLFix(0) + piston_size, 0, GLFix(0) + piston_offset, piston_right_texturemap, piston_sid.bottom, TEXTURE_TRANSPARENT});

    // Piston Side
    piston_vertices.push_back({GLFix(0) + piston_size, 0, GLFix(0) - piston_offset + BLOCK_SIZE, piston_left_texturemap, piston_sid.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({GLFix(0) + piston_size, GLFix(0) + piston_height, GLFix(0) - piston_offset + BLOCK_SIZE, piston_left_texturemap, piston_sid.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, GLFix(0) + piston_height, GLFix(0) - piston_offset + BLOCK_SIZE, piston_sid.right, piston_sid.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, 0, GLFix(0) - piston_offset + BLOCK_SIZE, piston_sid.right, piston_sid.bottom, TEXTURE_TRANSPARENT});

    // Piston Back Side
    piston_vertices.push_back({GLFix(0) + piston_offset, 0, GLFix(0) + BLOCK_SIZE, piston_sid.left, piston_sid.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({GLFix(0) + piston_offset, GLFix(0) + piston_height, 0 + BLOCK_SIZE, piston_sid.left, piston_sid.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({GLFix(0) + piston_offset, GLFix(0) + piston_height, 0, piston_sid.right, piston_sid.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({GLFix(0) + piston_offset, 0, 0, piston_sid.right, piston_sid.bottom, TEXTURE_TRANSPARENT});

    // Piston (Front) Inside
    piston_vertices.push_back({(GLFix(0) - piston_offset) + piston_size, 0, 0, piston_inside.left, piston_inside.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({(GLFix(0) - piston_offset) + piston_size, GLFix(0) + piston_height, 0, piston_inside.left, piston_inside.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({(GLFix(0) - piston_offset) + piston_size, GLFix(0) + piston_height, 0 + BLOCK_SIZE, piston_inside.right, piston_inside.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({(GLFix(0) - piston_offset) + piston_size, 0, 0 + BLOCK_SIZE, piston_inside.right, piston_inside.bottom, TEXTURE_TRANSPARENT});

    // Piston Top
    piston_vertices.push_back({GLFix(0) + piston_offset, GLFix(0) + piston_height, GLFix(0) + piston_offset, piston_top.left, piston_top.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({GLFix(0) + piston_offset, GLFix(0) + piston_height, GLFix(0) + BLOCK_SIZE - piston_offset, piston_top.left, piston_top.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({GLFix(0) + piston_size - piston_offset, GLFix(0) + piston_height, GLFix(0) + BLOCK_SIZE - piston_offset, piston_top_texturemap, piston_top.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({GLFix(0) + piston_size - piston_offset, GLFix(0) + piston_height, GLFix(0) + piston_offset, piston_top_texturemap, piston_top.bottom, TEXTURE_TRANSPARENT});

    // Rotate Piston According To Face
    BLOCK_SIDE side = static_cast<BLOCK_SIDE>(getBLOCKDATA(block) & BLOCK_SIDE_BITS);

    // Rotate GL stuff
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

    for(auto&& v : piston_vertices)
    {
        VERTEX v1;
        nglMultMatVectRes(transformation, &v, &v1);
        c.addUnalignedVertex(v1.x, v1.y, v1.z, v.u, v.v, v.c);
    }

    glPopMatrix();
}

void PistonRenderer::geometryNormalBlock(const BLOCK_WDATA /*block*/, const int local_x, const int local_y, const int local_z, const BLOCK_SIDE side, Chunk &c)
{
    // Render the bottom of the block as a normal side (needs to be replaced later)
    if(side != BLOCK_BOTTOM)
        return;

    // BOTTOM DOESN'T WORK!!! afdghtresdvbhtredfsvcbgfhtresd
    renderNormalBlockSide(local_x, local_y, local_z, side, terrain_atlas[12][7].current, c);
}

AABB PistonRenderer::getAABB(const BLOCK_WDATA block, GLFix x, GLFix y, GLFix z)
{
    // Get block side
    BLOCK_SIDE side = static_cast<BLOCK_SIDE>(getBLOCKDATA(block) & BLOCK_SIDE_BITS);
    const GLFix piston_offset = (GLFix(BLOCK_SIZE) - piston_width) * GLFix(0.5f);


    /////
    // Get the piston data
    /////
    const uint8_t piston_bites = 0;

    // Calculate the piston's size
    const GLFix piston_size = (piston_width / piston_max_bites) * (piston_max_bites - piston_bites);

    switch(side)
    {
        default:
            return {x + piston_offset, y, z + piston_offset + (piston_width - piston_size), x + piston_offset + piston_width, y + piston_height, z + piston_offset + piston_width};
            break;
        case BLOCK_BACK:
            return {x + piston_offset, y, z + piston_offset, x + piston_offset + piston_width, y + piston_height, z + piston_offset +  piston_size};
            break;
        case BLOCK_FRONT:
            return {x + piston_offset, y, z + piston_offset + (piston_width - piston_size), x + piston_offset + piston_width, y + piston_height, z + piston_offset + piston_width};
            break;
        case BLOCK_LEFT:
            return {x + piston_offset + (piston_width - piston_size), y, z + piston_offset, x + piston_offset + piston_width, y + piston_height, z + piston_offset + piston_width};
            break;
        case BLOCK_RIGHT:
            return {x + piston_offset, y, z + piston_offset, x + piston_offset + piston_size, y + piston_height, z + piston_offset + piston_width};
            break;
    }
    
}

bool PistonRenderer::action(const BLOCK_WDATA block, const int local_x, const int local_y, const int local_z, Chunk &c) {
    /////
    // Get the piston data
    /////
    const uint8_t piston_bites = 0;

    if (piston_bites + 1 >= piston_max_bites) {
        c.setLocalBlock(local_x, local_y, local_z, getBLOCK(BLOCK_AIR));
        return true;
    }

    // Prepare data
    uint8_t prep_data = getBLOCKDATA(block) ^ (piston_bites << piston_bit_shift); // Set pre-existing piston_bites to zero

    uint8_t new_data = ((piston_bites + 1) << piston_bit_shift) | prep_data;

    c.setLocalBlock(local_x, local_y, local_z, getBLOCKWDATA(getBLOCK(block), new_data));

    return true;
}

void PistonRenderer::drawPreview(const BLOCK_WDATA /*block*/, TEXTURE &dest, int x, int y)
{
    TextureAtlasEntry &tex = terrain_atlas[12][8].resized;
    BlockRenderer::drawTextureAtlasEntry(*terrain_resized, tex, dest, x, y);
}

const char *PistonRenderer::getName(const BLOCK_WDATA /*block*/)
{
    return "Piston";
}