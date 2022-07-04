#include <algorithm>
#include "pistonrenderer.h"


std::vector<VERTEX> piston_head_vertices() {
    TextureAtlasEntry piston_side = terrain_atlas[12][6].current;
    TextureAtlasEntry piston_front = terrain_atlas[11][6].current;
    const GLFix piston_head_size = BLOCK_SIZE / 4;

    std::vector<VERTEX> piston_vertices;

    piston_vertices.reserve(40);

    GLFix piston_head_bottom_texturemap = piston_side.top + ((piston_side.bottom - piston_side.top) * 4 / 16);

    // Piston Front
    piston_vertices.push_back({0, 0, 0, piston_front.left, piston_front.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, 0, piston_front.left, piston_front.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, 0, piston_front.right, piston_front.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, 0, piston_front.right, piston_front.bottom, TEXTURE_TRANSPARENT});

    // Piston Back
    piston_vertices.push_back({0, 0, piston_head_size, piston_front.left, piston_front.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, piston_head_size, piston_front.right, piston_front.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, piston_head_size, piston_front.right, piston_front.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, piston_head_size, piston_front.left, piston_front.top, TEXTURE_TRANSPARENT});

    // Piston Bottom
    piston_vertices.push_back({0, 0, piston_head_size, piston_side.left, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, 0, 0, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, 0, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, piston_head_size, piston_side.right, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});

    // Piston Top
    piston_vertices.push_back({0, BLOCK_SIZE, piston_head_size, piston_side.left, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, piston_head_size, piston_side.right, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, 0, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, 0, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});

    // Piston Left
    piston_vertices.push_back({0, BLOCK_SIZE, piston_head_size, piston_side.left, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, 0, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, 0, 0, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, 0, piston_head_size, piston_side.right, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});

    // Piston Right
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, piston_head_size, piston_side.left, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, piston_head_size, piston_side.right, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, 0, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, 0, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});


    // Piston Neck
    const GLFix piston_neck_size = BLOCK_SIZE * 4 / 16;
    const GLFix piston_neck_length = GLFix(BLOCK_SIZE) - piston_head_size;
    const GLFix piston_neck_offset = (GLFix(BLOCK_SIZE) - piston_neck_size) * GLFix(0.5f);

    // Piston "Neck" Top
    piston_vertices.push_back({piston_neck_offset, piston_neck_offset+piston_neck_size, piston_head_size, piston_side.right, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({piston_neck_offset, piston_neck_offset+piston_neck_size, (piston_head_size*2)+piston_neck_length, piston_side.left, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({piston_neck_offset+piston_neck_size, piston_neck_offset+piston_neck_size, (piston_head_size*2)+piston_neck_length, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({piston_neck_offset+piston_neck_size, piston_neck_offset+piston_neck_size, piston_head_size, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});

    // Piston "Neck" Bottom
    piston_vertices.push_back({piston_neck_offset+piston_neck_size, piston_neck_offset, piston_head_size, piston_side.right, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({piston_neck_offset+piston_neck_size, piston_neck_offset, (piston_head_size*2)+piston_neck_length, piston_side.left, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({piston_neck_offset, piston_neck_offset, (piston_head_size*2)+piston_neck_length, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({piston_neck_offset, piston_neck_offset, piston_head_size, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});

    // Piston "Neck" Left
    piston_vertices.push_back({piston_neck_offset, piston_neck_offset, (piston_head_size*2)+piston_neck_length, piston_side.left, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({piston_neck_offset, piston_neck_offset+piston_neck_size, (piston_head_size*2)+piston_neck_length, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({piston_neck_offset, piston_neck_offset+piston_neck_size, piston_head_size, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({piston_neck_offset, piston_neck_offset, piston_head_size, piston_side.right, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});

    // Piston "Neck" Right
    piston_vertices.push_back({piston_neck_offset+piston_neck_size, piston_neck_offset, piston_head_size, piston_side.left, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({piston_neck_offset+piston_neck_size, piston_neck_offset+piston_neck_size, piston_head_size, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({piston_neck_offset+piston_neck_size, piston_neck_offset+piston_neck_size, (piston_head_size*2)+piston_neck_length, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({piston_neck_offset+piston_neck_size, piston_neck_offset, (piston_head_size*2)+piston_neck_length, piston_side.right, piston_head_bottom_texturemap, TEXTURE_TRANSPARENT});

    return piston_vertices;
}

std::vector<VERTEX> piston_body_vertices() {
    TextureAtlasEntry piston_side = terrain_atlas[12][6].current;
    const TextureAtlasEntry piston_back = terrain_atlas[13][6].current;
    const TextureAtlasEntry piston_front = terrain_atlas[14][6].current;

    const GLFix piston_head_size = BLOCK_SIZE / 4;
    const GLFix  piston_body_size = GLFix(BLOCK_SIZE) * GLFix(12/16);

    //GLFix piston_left_texturemap = GLFix(piston_side.right) - GLFix(piston_side.right - piston_side.left) * (piston_body_size / GLFix(BLOCK_SIZE));
    //GLFix piston_right_texturemap = GLFix(piston_side.left) + GLFix(piston_side.right - piston_side.left) * (piston_body_size / GLFix(BLOCK_SIZE));
    //GLFix piston_top_texturemap = GLFix(piston_side.bottom) + GLFix(piston_side.bottom - piston_side.top) * (piston_body_size / GLFix(BLOCK_SIZE));

    const GLFix piston_body_texturemap_top = piston_side.bottom - ((piston_side.bottom - piston_side.top) * 12 / 16);
    const GLFix piston_body_texturemap_bottom = piston_side.bottom;//piston_side.top + ((piston_side.bottom - piston_side.top) * 12 / 16);

    std::vector<VERTEX> piston_vertices;

    piston_vertices.reserve(24);

    // Piston Front
    piston_vertices.push_back({0, 0, piston_head_size, piston_front.left, piston_front.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, piston_head_size, piston_front.left, piston_front.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, piston_head_size, piston_front.right, piston_front.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, piston_head_size, piston_front.right, piston_front.bottom, TEXTURE_TRANSPARENT});

    // Piston Bottom
    piston_vertices.push_back({0, 0, BLOCK_SIZE, piston_side.left, piston_body_texturemap_bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, 0, piston_head_size, piston_side.left, piston_body_texturemap_top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, piston_head_size, piston_side.right, piston_body_texturemap_top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, BLOCK_SIZE, piston_side.right, piston_body_texturemap_bottom, TEXTURE_TRANSPARENT});

    // Piston Top
    piston_vertices.push_back({0, BLOCK_SIZE, BLOCK_SIZE, piston_side.left, piston_body_texturemap_bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, piston_side.right, piston_body_texturemap_bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, piston_head_size, piston_side.right, piston_body_texturemap_top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, piston_head_size, piston_side.left, piston_body_texturemap_top, TEXTURE_TRANSPARENT});

    // Piston Left
    piston_vertices.push_back({0, BLOCK_SIZE, BLOCK_SIZE, piston_side.left, piston_body_texturemap_bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, piston_head_size, piston_side.left, piston_body_texturemap_top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, 0, piston_head_size, piston_side.right, piston_body_texturemap_top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, 0, BLOCK_SIZE, piston_side.right, piston_body_texturemap_bottom, TEXTURE_TRANSPARENT});

    // Piston Right
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, piston_side.left, piston_body_texturemap_bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, BLOCK_SIZE, piston_side.right, piston_body_texturemap_bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, piston_head_size, piston_side.right, piston_body_texturemap_top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, piston_head_size, piston_side.left, piston_body_texturemap_top, TEXTURE_TRANSPARENT});

    // Piston Back
    piston_vertices.push_back({0, 0, BLOCK_SIZE, piston_back.left, piston_back.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, BLOCK_SIZE, piston_back.right, piston_back.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, piston_back.right, piston_back.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, BLOCK_SIZE, piston_back.left, piston_back.top, TEXTURE_TRANSPARENT});

    return piston_vertices;
}

std::vector<VERTEX> piston_normal_vertices() {
    TextureAtlasEntry piston_side = terrain_atlas[12][6].current;
    TextureAtlasEntry piston_back = terrain_atlas[13][6].current;
    TextureAtlasEntry piston_front = terrain_atlas[11][6].current;

    std::vector<VERTEX> piston_vertices;

    piston_vertices.reserve(24);

    // Piston Front
    piston_vertices.push_back({0, 0, 0, piston_front.left, piston_front.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, 0, piston_front.left, piston_front.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, 0, piston_front.right, piston_front.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, 0, piston_front.right, piston_front.bottom, TEXTURE_TRANSPARENT});

    // Piston Bottom
    piston_vertices.push_back({0, 0, BLOCK_SIZE, piston_side.left, piston_side.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, 0, 0, piston_side.left, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, 0, piston_side.right, piston_side.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, BLOCK_SIZE, piston_side.right, piston_side.bottom, TEXTURE_TRANSPARENT});

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

    // Piston Back
    piston_vertices.push_back({0, 0, BLOCK_SIZE, piston_back.left, piston_back.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, 0, BLOCK_SIZE, piston_back.right, piston_back.bottom, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, piston_back.right, piston_back.top, TEXTURE_TRANSPARENT});
    piston_vertices.push_back({0, BLOCK_SIZE, BLOCK_SIZE, piston_back.left, piston_back.top, TEXTURE_TRANSPARENT});

    return piston_vertices;
}

const TerrainAtlasEntry &PistonRenderer::destructionTexture(const BLOCK_WDATA block) {
    return terrain_atlas[4][0];
}

void PistonRenderer::renderSpecialBlock(const BLOCK_WDATA block, GLFix x, GLFix y, GLFix z, Chunk &c)
{
    //////
    // GL CODE
    //////
    glPushMatrix();
    glLoadIdentity();

    glTranslatef(x + BLOCK_SIZE/2, y + BLOCK_SIZE/2, z + BLOCK_SIZE/2);

    std::vector<VERTEX> piston_vertices;

    const uint8_t piston_type = static_cast<uint8_t>((getBLOCKDATA(block) & piston_data_bits) >> piston_bit_shift);
    switch (piston_type) {
        case PISTON_NORMAL:
            piston_vertices = piston_normal_vertices();
            break;
        case PISTON_BODY:
            piston_vertices = piston_body_vertices();
            break;
        case PISTON_HEAD:
            piston_vertices = piston_head_vertices();
            break;
    }


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

void PistonRenderer::tick(const BLOCK_WDATA block, int local_x, int local_y, int local_z, Chunk &c)
{
    // Define blocks which the piston cannot move
    static const std::vector<BLOCK_WDATA> unmovableBlocks = {
        getBLOCKWDATA(BLOCK_PISTON, PISTON_BODY << piston_bit_shift),
        getBLOCKWDATA(BLOCK_PISTON, PISTON_HEAD << piston_bit_shift),
        BLOCK_BEDROCK,
        BLOCK_DOOR,
        BLOCK_FLOWER,
        BLOCK_WHEAT,
        BLOCK_MUSHROOM,
        BLOCK_REDSTONE_SWITCH,
        BLOCK_REDSTONE_TORCH
    };



    REDSTONE_STATE powered = c.isBlockPowered(local_x, local_y, local_z) ? ON : OFF;
    bool poweredFromFace = c.gettingPowerFrom(local_x, local_y, local_z, BLOCK_FRONT);

    const uint8_t piston_powered = static_cast<uint8_t>((getBLOCKDATA(block) & piston_powered_bits) >> piston_power_bit_shift);
    const PISTON_TYPE piston_type = static_cast<PISTON_TYPE>((getBLOCKDATA(block) & piston_data_bits) >> piston_bit_shift);

    if(!poweredFromFace && piston_powered != powered && piston_type != PISTON_HEAD) {
        //c.setLocalBlock(local_x, local_y, local_z, getBLOCKWDATA(getBLOCK(block), prep_data | powered << piston_power_bit_shift));


        // Piston logic stuff:
        VECTOR3 pistonHeadCoordinates;
        VECTOR3 blockToPushCoordinates;

        // Get proper piston head coordinates
        BLOCK_SIDE side = static_cast<BLOCK_SIDE>(getBLOCKDATA(block) & BLOCK_SIDE_BITS);
        switch(side)
        {
            default:
                break;
            case BLOCK_BACK:
                pistonHeadCoordinates.x = local_x;
                pistonHeadCoordinates.y = local_y;
                pistonHeadCoordinates.z = local_z+1;

                blockToPushCoordinates.x = local_x;
                blockToPushCoordinates.y = local_y;
                blockToPushCoordinates.z = local_z+2;
                break;
            case BLOCK_FRONT:
                pistonHeadCoordinates.x = local_x;
                pistonHeadCoordinates.y = local_y;
                pistonHeadCoordinates.z = local_z-1;

                blockToPushCoordinates.x = local_x;
                blockToPushCoordinates.y = local_y;
                blockToPushCoordinates.z = local_z-2;
                break;
            case BLOCK_LEFT:
                pistonHeadCoordinates.x = local_x-1;
                pistonHeadCoordinates.y = local_y;
                pistonHeadCoordinates.z = local_z;

                blockToPushCoordinates.x = local_x-2;
                blockToPushCoordinates.y = local_y;
                blockToPushCoordinates.z = local_z;
                break;
            case BLOCK_RIGHT:
                pistonHeadCoordinates.x = local_x+1;
                pistonHeadCoordinates.y = local_y;
                pistonHeadCoordinates.z = local_z;

                blockToPushCoordinates.x = local_x+2;
                blockToPushCoordinates.y = local_y;
                blockToPushCoordinates.z = local_z;
                break;
        }

        uint8_t piston_data = getBLOCKDATA(block) ^ (piston_powered << piston_power_bit_shift) | side; // Set pre-existing power bit to zero

        if (powered) {
            BLOCK_WDATA blockToPush = c.getGlobalBlockRelative(pistonHeadCoordinates.x, pistonHeadCoordinates.y, pistonHeadCoordinates.z);

            if (std::find(unmovableBlocks.begin(), unmovableBlocks.end(), blockToPush) == unmovableBlocks.end()) {
                const PISTON_TYPE piston_type = static_cast<PISTON_TYPE>((getBLOCKDATA(block) & piston_data_bits) >> piston_bit_shift);
                
                piston_data = piston_data ^ (piston_type << piston_bit_shift); // Set pre-existing piston data bits to zero
                
                c.setLocalBlock(local_x, local_y, local_z, getBLOCKWDATA(getBLOCK(block), piston_data | powered << piston_power_bit_shift | PISTON_BODY << piston_bit_shift));

                if (blockToPush != BLOCK_AIR) {
                    c.setGlobalBlockRelative(blockToPushCoordinates.x, blockToPushCoordinates.y, blockToPushCoordinates.z, blockToPush);
                }
                c.setGlobalBlockRelative(pistonHeadCoordinates.x, pistonHeadCoordinates.y, pistonHeadCoordinates.z, getBLOCKWDATA(BLOCK_PISTON, side | PISTON_HEAD << piston_bit_shift));
            } else {
                c.setLocalBlock(local_x, local_y, local_z, getBLOCKWDATA(getBLOCK(block), piston_data | powered << piston_power_bit_shift));
            }
        } else {
            const PISTON_TYPE piston_type = static_cast<PISTON_TYPE>((getBLOCKDATA(block) & piston_data_bits) >> piston_bit_shift);

            piston_data = piston_data ^ (piston_type << piston_bit_shift); // Set pre-existing piston data bits to zero
            
            c.setLocalBlock(local_x, local_y, local_z, getBLOCKWDATA(getBLOCK(block), piston_data));

            c.setGlobalBlockRelative(pistonHeadCoordinates.x, pistonHeadCoordinates.y, pistonHeadCoordinates.z, BLOCK_AIR);
        }
    }
}

void PistonRenderer::drawPreview(const BLOCK_WDATA /*block*/, TEXTURE &dest, int x, int y)
{
    TextureAtlasEntry &tex = terrain_atlas[11][6].resized;
    BlockRenderer::drawTextureAtlasEntry(*terrain_resized, tex, dest, x, y);
}

const char *PistonRenderer::getName(const BLOCK_WDATA block)
{
    const PISTON_TYPE piston_type = static_cast<PISTON_TYPE>((getBLOCKDATA(block) & piston_data_bits) >> piston_bit_shift);
    switch (piston_type) {
        case PISTON_NORMAL:
            return "Piston";
            break;
        case PISTON_BODY:
            return "Piston Body";
            break;
        case PISTON_HEAD:
            return "Piston Head";
            break;
    }
}