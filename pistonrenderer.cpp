#include "pistonrenderer.h"

constexpr GLFix PistonRenderer::piston_height, PistonRenderer::piston_width;

void PistonRenderer::renderSpecialBlock(const BLOCK_WDATA block, GLFix x, GLFix y, GLFix z, Chunk &c)
{
    TextureAtlasEntry piston_side = terrain_atlas[12][6].current;
    TextureAtlasEntry piston_back = terrain_atlas[13][6].current;
    TextureAtlasEntry piston_front = terrain_atlas[11][6].current;


    /////
    // Get the piston data
    /////
    const uint8_t piston_type = static_cast<uint8_t>((getBLOCKDATA(block) & piston_data_bits) >> piston_bit_shift);


    //////
    // GL CODE
    //////
    glPushMatrix();
    glLoadIdentity();

    glTranslatef(x + BLOCK_SIZE/2, y + BLOCK_SIZE/2, z + BLOCK_SIZE/2);

    std::vector<VERTEX> piston_vertices;
    // piston_vertices.reserve(24);

    // // Piston Front
    // piston_vertices.push_back({0, 0, 0, piston_front.left, piston_front.bottom, TEXTURE_TRANSPARENT});
    // piston_vertices.push_back({0, BLOCK_SIZE, 0, piston_front.left, piston_front.top, TEXTURE_TRANSPARENT});
    // piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, 0, piston_front.right, piston_front.top, TEXTURE_TRANSPARENT});
    // piston_vertices.push_back({BLOCK_SIZE, 0, 0, piston_front.right, piston_front.bottom, TEXTURE_TRANSPARENT});

    // // Piston Bottom
    // piston_vertices.push_back({0, 0, BLOCK_SIZE, piston_side.left, piston_side.bottom, TEXTURE_TRANSPARENT});
    // piston_vertices.push_back({0, 0, 0, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});
    // piston_vertices.push_back({BLOCK_SIZE, 0, 0, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    // piston_vertices.push_back({BLOCK_SIZE, 0, BLOCK_SIZE, piston_side.right, piston_side.bottom, TEXTURE_TRANSPARENT});

    // // Piston Top
    // piston_vertices.push_back({0, BLOCK_SIZE, BLOCK_SIZE, piston_side.left, piston_side.bottom, TEXTURE_TRANSPARENT});
    // piston_vertices.push_back({0, BLOCK_SIZE, 0, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});
    // piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, 0, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    // piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, piston_side.right, piston_side.bottom, TEXTURE_TRANSPARENT});

    // // Piston Left
    // piston_vertices.push_back({0, BLOCK_SIZE, BLOCK_SIZE, piston_side.left, piston_side.bottom, TEXTURE_TRANSPARENT});
    // piston_vertices.push_back({0, BLOCK_SIZE, 0, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});
    // piston_vertices.push_back({0, 0, 0, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    // piston_vertices.push_back({0, 0, BLOCK_SIZE, piston_side.right, piston_side.bottom, TEXTURE_TRANSPARENT});

    // // Piston Right
    // piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, piston_side.left, piston_side.bottom, TEXTURE_TRANSPARENT});
    // piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, 0, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});
    // piston_vertices.push_back({BLOCK_SIZE, 0, 0, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    // piston_vertices.push_back({BLOCK_SIZE, 0, BLOCK_SIZE, piston_side.right, piston_side.bottom, TEXTURE_TRANSPARENT});

    // // Piston Back
    // piston_vertices.push_back({0, 0, BLOCK_SIZE, piston_back.left, piston_back.bottom, TEXTURE_TRANSPARENT});
    // piston_vertices.push_back({0, BLOCK_SIZE, BLOCK_SIZE, piston_back.left, piston_back.top, TEXTURE_TRANSPARENT});
    // piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, piston_back.right, piston_back.top, TEXTURE_TRANSPARENT});
    // piston_vertices.push_back({BLOCK_SIZE, 0, BLOCK_SIZE, piston_back.right, piston_back.bottom, TEXTURE_TRANSPARENT});


    piston_vertices.reserve(24);

    // Piston Front
    piston_vertices.push_back({0, 0, 0, piston_front.left, piston_front.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, 0, piston_front.left, piston_front.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, 0, piston_front.right, piston_front.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, 0, piston_front.right, piston_front.bottom, TEXTURE_TRANSPARENT});

    // Piston Back
    piston_vertices.push_back({0, 0, BLOCK_SIZE, piston_back.left, piston_back.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, BLOCK_SIZE, piston_back.right, piston_back.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, piston_back.right, piston_back.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, BLOCK_SIZE, piston_back.left, piston_back.top, TEXTURE_TRANSPARENT});

    // Piston Bottom
    piston_vertices.push_back({0, 0, BLOCK_SIZE, piston_side.left, piston_side.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, BLOCK_SIZE, piston_side.right, piston_side.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, 0, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, 0, 0, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});

    // Piston Top
    piston_vertices.push_back({0, BLOCK_SIZE, BLOCK_SIZE, piston_side.left, piston_side.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, piston_side.right, piston_side.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, 0, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, 0, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});

    // Piston Left
    piston_vertices.push_back({0, BLOCK_SIZE, BLOCK_SIZE, piston_side.left, piston_side.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, 0, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, 0, 0, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, 0, BLOCK_SIZE, piston_side.right, piston_side.bottom, TEXTURE_TRANSPARENT});

    // Piston Right
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, piston_side.left, piston_side.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, BLOCK_SIZE, piston_side.right, piston_side.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, 0, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, 0, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});


    // Rotate Piston According To Face
    BLOCK_SIDE side = static_cast<BLOCK_SIDE>(getBLOCKDATA(block) & BLOCK_SIDE_BITS);

    // Rotate GL stuff
    switch(side)
    {
        default:
            break;
        case BLOCK_BACK:
            nglRotateY(180);
            break;
        case BLOCK_FRONT:
            nglRotateY(0);
            break;
        case BLOCK_LEFT:
            nglRotateY(90);
            break;
        case BLOCK_RIGHT:
            nglRotateY(270);
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
    return;
}

AABB PistonRenderer::getAABB(const BLOCK_WDATA block, GLFix x, GLFix y, GLFix z)
{
    // Get block side
    BLOCK_SIDE side = static_cast<BLOCK_SIDE>(getBLOCKDATA(block) & BLOCK_SIDE_BITS);
    const GLFix piston_offset = (GLFix(BLOCK_SIZE) - piston_width) * GLFix(0.5f);


    /////
    // Get the piston data
    /////
    const uint8_t piston_bites = static_cast<uint8_t>((getBLOCKDATA(block) & piston_data_bits) >> piston_bit_shift);

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
    const uint8_t piston_bites = static_cast<uint8_t>((getBLOCKDATA(block) & piston_data_bits) >> piston_bit_shift);

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
    TextureAtlasEntry &tex = terrain_atlas[11][6].resized;
    BlockRenderer::drawTextureAtlasEntry(*terrain_resized, tex, dest, x, y);
}

const char *PistonRenderer::getName(const BLOCK_WDATA /*block*/)
{
    return "Piston";
}