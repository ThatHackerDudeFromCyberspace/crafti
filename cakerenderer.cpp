#include "cakerenderer.h"

constexpr GLFix CakeRenderer::cake_height, CakeRenderer::cake_width;

void CakeRenderer::renderSpecialBlock(const BLOCK_WDATA block, GLFix x, GLFix y, GLFix z, Chunk &c)
{
    // NOTE: CAKE BOTTOM IS MANAGED LIKE A NORMAL BLOCK

    // Cake offset, the offsettiness of the cake (it isn't a full block ya know)
    const GLFix cake_offset = (GLFix(BLOCK_SIZE) - cake_width) * GLFix(0.5f);
    const TextureAtlasEntry &cake_top = terrain_atlas[9][7].current;
    TextureAtlasEntry cake_sid = terrain_atlas[10][7].current;


    /////
    // Get the cake data
    /////
    const uint8_t cake_bites = static_cast<uint8_t>((getBLOCKDATA(block) & cake_data_bits) >> cake_bit_shift);


    cake_sid.top = cake_sid.top + (cake_sid.bottom - cake_sid.top) * 9 / 16;
    
    // If cake not full, set "inside" to standard side
    TextureAtlasEntry cake_inside = cake_sid;

    if (cake_bites > 0) {
        // Cake inside only if cake is not full
        cake_inside = terrain_atlas[11][7].current;
        cake_inside.top = cake_inside.top + (cake_inside.bottom - cake_inside.top) * 9 / 16;
    }



    // Calculate the cake's size
    const GLFix cake_size = (cake_width / cake_max_bites) * (cake_max_bites - cake_bites);


    //////
    // GL CODE
    //////
    glPushMatrix();
    glLoadIdentity();

    glTranslatef(x, y, z);

    std::vector<VERTEX> cake_vertices;
    cake_vertices.reserve(20);

    //cake_sid.right = cake_sid.right - (cake_sid.right - cake_sid.left) * (cake_max_bites - cake_bites) / 6;

    GLFix cake_left_texturemap = cake_sid.right - (cake_sid.right - cake_sid.left) * (cake_max_bites - cake_bites) / cake_max_bites;
    GLFix cake_right_texturemap = cake_sid.left + (cake_sid.right - cake_sid.left) * (cake_max_bites - cake_bites) / cake_max_bites;

    GLFix cake_top_texturemap = cake_top.left + (cake_top.right - cake_top.left) * (cake_max_bites - cake_bites) / cake_max_bites;


    // Cake Side
    cake_vertices.push_back({0, 0, GLFix(0) + cake_offset, cake_sid.left, cake_sid.bottom, TEXTURE_TRANSPARENT});
    cake_vertices.push_back({0, GLFix(0) + cake_height, GLFix(0) + cake_offset, cake_sid.left, cake_sid.top, TEXTURE_TRANSPARENT});
    cake_vertices.push_back({GLFix(0) + cake_size, GLFix(0) + cake_height, GLFix(0) + cake_offset, cake_right_texturemap, cake_sid.top, TEXTURE_TRANSPARENT});
    cake_vertices.push_back({GLFix(0) + cake_size, 0, GLFix(0) + cake_offset, cake_right_texturemap, cake_sid.bottom, TEXTURE_TRANSPARENT});

    // Cake Side
    cake_vertices.push_back({GLFix(0) + cake_size, 0, GLFix(0) - cake_offset + BLOCK_SIZE, cake_left_texturemap, cake_sid.bottom, TEXTURE_TRANSPARENT});
    cake_vertices.push_back({GLFix(0) + cake_size, GLFix(0) + cake_height, GLFix(0) - cake_offset + BLOCK_SIZE, cake_left_texturemap, cake_sid.top, TEXTURE_TRANSPARENT});
    cake_vertices.push_back({0, GLFix(0) + cake_height, GLFix(0) - cake_offset + BLOCK_SIZE, cake_sid.right, cake_sid.top, TEXTURE_TRANSPARENT});
    cake_vertices.push_back({0, 0, GLFix(0) - cake_offset + BLOCK_SIZE, cake_sid.right, cake_sid.bottom, TEXTURE_TRANSPARENT});

    // Cake Back Side
    cake_vertices.push_back({GLFix(0) + cake_offset, 0, GLFix(0) + BLOCK_SIZE, cake_sid.left, cake_sid.bottom, TEXTURE_TRANSPARENT});
    cake_vertices.push_back({GLFix(0) + cake_offset, GLFix(0) + cake_height, 0 + BLOCK_SIZE, cake_sid.left, cake_sid.top, TEXTURE_TRANSPARENT});
    cake_vertices.push_back({GLFix(0) + cake_offset, GLFix(0) + cake_height, 0, cake_sid.right, cake_sid.top, TEXTURE_TRANSPARENT});
    cake_vertices.push_back({GLFix(0) + cake_offset, 0, 0, cake_sid.right, cake_sid.bottom, TEXTURE_TRANSPARENT});

    // Cake (Front) Inside
    cake_vertices.push_back({(GLFix(0) - cake_offset) + cake_size, 0, 0, cake_inside.left, cake_inside.bottom, TEXTURE_TRANSPARENT});
    cake_vertices.push_back({(GLFix(0) - cake_offset) + cake_size, GLFix(0) + cake_height, 0, cake_inside.left, cake_inside.top, TEXTURE_TRANSPARENT});
    cake_vertices.push_back({(GLFix(0) - cake_offset) + cake_size, GLFix(0) + cake_height, 0 + BLOCK_SIZE, cake_inside.right, cake_inside.top, TEXTURE_TRANSPARENT});
    cake_vertices.push_back({(GLFix(0) - cake_offset) + cake_size, 0, 0 + BLOCK_SIZE, cake_inside.right, cake_inside.bottom, TEXTURE_TRANSPARENT});

    // Cake Top
    cake_vertices.push_back({GLFix(0) + cake_offset, GLFix(0) + cake_height, GLFix(0) + cake_offset, cake_top.left, cake_top.bottom, TEXTURE_TRANSPARENT});
    cake_vertices.push_back({GLFix(0) + cake_offset, GLFix(0) + cake_height, GLFix(0) + BLOCK_SIZE - cake_offset, cake_top.left, cake_top.top, TEXTURE_TRANSPARENT});
    cake_vertices.push_back({GLFix(0) + cake_size - cake_offset, GLFix(0) + cake_height, GLFix(0) + BLOCK_SIZE - cake_offset, cake_top_texturemap, cake_top.top, TEXTURE_TRANSPARENT});
    cake_vertices.push_back({GLFix(0) + cake_size - cake_offset, GLFix(0) + cake_height, GLFix(0) + cake_offset, cake_top_texturemap, cake_top.bottom, TEXTURE_TRANSPARENT});

    // Rotate Cake According To Face
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
    
    for(auto&& v : cake_vertices)
    {
        VERTEX v1;
        nglMultMatVectRes(transformation, &v, &v1);
        c.addUnalignedVertex(v1.x, v1.y, v1.z, v.u, v.v, v.c);
    }

    glPopMatrix();
}

void CakeRenderer::geometryNormalBlock(const BLOCK_WDATA /*block*/, const int local_x, const int local_y, const int local_z, const BLOCK_SIDE side, Chunk &c)
{
    // Render the bottom of the block as a normal side (needs to be replaced later)
    if(side != BLOCK_BOTTOM)
        return;

    // BOTTOM DOESN'T WORK!!! afdghtresdvbhtredfsvcbgfhtresd
    renderNormalBlockSide(local_x, local_y, local_z, side, terrain_atlas[12][7].current, c);
}

AABB CakeRenderer::getAABB(const BLOCK_WDATA block, GLFix x, GLFix y, GLFix z)
{
    // Get block side
    BLOCK_SIDE side = static_cast<BLOCK_SIDE>(getBLOCKDATA(block) & BLOCK_SIDE_BITS);
    const GLFix cake_offset = (GLFix(BLOCK_SIZE) - cake_width) * GLFix(0.5f);


    /////
    // Get the cake data
    /////
    const uint8_t cake_bites = static_cast<uint8_t>((getBLOCKDATA(block) & cake_data_bits) >> cake_bit_shift);

    // Calculate the cake's size
    const GLFix cake_size = (cake_width / cake_max_bites) * (cake_max_bites - cake_bites);

    switch(side)
    {
        default:
            return {x + cake_offset, y, z + cake_offset + (cake_width - cake_size), x + cake_offset + cake_width, y + cake_height, z + cake_offset + cake_width};
            break;
        case BLOCK_BACK:
            return {x + cake_offset, y, z + cake_offset, x + cake_offset + cake_width, y + cake_height, z + cake_offset +  cake_size};
            break;
        case BLOCK_FRONT:
            return {x + cake_offset, y, z + cake_offset + (cake_width - cake_size), x + cake_offset + cake_width, y + cake_height, z + cake_offset + cake_width};
            break;
        case BLOCK_LEFT:
            return {x + cake_offset + (cake_width - cake_size), y, z + cake_offset, x + cake_offset + cake_width, y + cake_height, z + cake_offset + cake_width};
            break;
        case BLOCK_RIGHT:
            return {x + cake_offset, y, z + cake_offset, x + cake_offset + cake_size, y + cake_height, z + cake_offset + cake_width};
            break;
    }
    
}

bool CakeRenderer::action(const BLOCK_WDATA block, const int local_x, const int local_y, const int local_z, Chunk &c) {
    /////
    // Get the cake data
    /////
    const uint8_t cake_bites = static_cast<uint8_t>((getBLOCKDATA(block) & cake_data_bits) >> cake_bit_shift);

    if (cake_bites + 1 >= cake_max_bites) {
        c.setLocalBlock(local_x, local_y, local_z, getBLOCK(BLOCK_AIR));
        return true;
    }

    uint8_t pre_data = getBLOCKDATA(block) ^ (cake_bites << cake_bit_shift); // Set pre-existing cake_bites to zero

    uint8_t new_data = ((cake_bites + 1) << cake_bit_shift) | pre_data;

    c.setLocalBlock(local_x, local_y, local_z, getBLOCKWDATA(getBLOCK(block), new_data));

    return true;
}

void CakeRenderer::drawPreview(const BLOCK_WDATA /*block*/, TEXTURE &dest, int x, int y)
{
    TextureAtlasEntry &tex = terrain_atlas[12][8].resized;
    BlockRenderer::drawTextureAtlasEntry(*terrain_resized, tex, dest, x, y);
}

const char *CakeRenderer::getName(const BLOCK_WDATA /*block*/)
{
    return "Cake";
}