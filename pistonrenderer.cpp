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


    
    // Piston coordinate stuff
    VECTOR3 pistonHeadCoordinates;
    VECTOR3 blockToPushCoordinates;

    // Get proper piston head coordinates
    BLOCK_SIDE side = static_cast<BLOCK_SIDE>(getBLOCKDATA(block) & BLOCK_SIDE_BITS);
    bool poweredProperly = true;

    // Calculate piston-side-dependent variables
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

            poweredProperly = (
                c.gettingPowerFrom(local_x-1, local_y, local_z, BLOCK_RIGHT)
                || c.gettingPowerFrom(local_x+1, local_y, local_z, BLOCK_LEFT)
                || c.gettingPowerFrom(local_x, local_y-1, local_z, BLOCK_TOP)
                || c.gettingPowerFrom(local_x, local_y+1, local_z, BLOCK_BOTTOM)
                || c.gettingPowerFrom(local_x, local_y, local_z-1, BLOCK_BACK)
            );
            break;
        case BLOCK_FRONT:
            pistonHeadCoordinates.x = local_x;
            pistonHeadCoordinates.y = local_y;
            pistonHeadCoordinates.z = local_z-1;

            blockToPushCoordinates.x = local_x;
            blockToPushCoordinates.y = local_y;
            blockToPushCoordinates.z = local_z-2;

            poweredProperly = (
                c.gettingPowerFrom(local_x-1, local_y, local_z, BLOCK_RIGHT)
                || c.gettingPowerFrom(local_x+1, local_y, local_z, BLOCK_LEFT)
                || c.gettingPowerFrom(local_x, local_y-1, local_z, BLOCK_TOP)
                || c.gettingPowerFrom(local_x, local_y+1, local_z, BLOCK_BOTTOM)
                || c.gettingPowerFrom(local_x, local_y, local_z+1, BLOCK_FRONT)
            );
            break;
        case BLOCK_LEFT:
            pistonHeadCoordinates.x = local_x-1;
            pistonHeadCoordinates.y = local_y;
            pistonHeadCoordinates.z = local_z;

            blockToPushCoordinates.x = local_x-2;
            blockToPushCoordinates.y = local_y;
            blockToPushCoordinates.z = local_z;

            poweredProperly = (
                c.gettingPowerFrom(local_x+1, local_y, local_z, BLOCK_LEFT)
                || c.gettingPowerFrom(local_x, local_y-1, local_z, BLOCK_TOP)
                || c.gettingPowerFrom(local_x, local_y+1, local_z, BLOCK_BOTTOM)
                || c.gettingPowerFrom(local_x, local_y, local_z-1, BLOCK_BACK)
                || c.gettingPowerFrom(local_x, local_y, local_z+1, BLOCK_FRONT)
            );
            break;
        case BLOCK_RIGHT:
            pistonHeadCoordinates.x = local_x+1;
            pistonHeadCoordinates.y = local_y;
            pistonHeadCoordinates.z = local_z;

            blockToPushCoordinates.x = local_x+2;
            blockToPushCoordinates.y = local_y;
            blockToPushCoordinates.z = local_z;

            poweredProperly = (
                c.gettingPowerFrom(local_x-1, local_y, local_z, BLOCK_RIGHT)
                || c.gettingPowerFrom(local_x, local_y-1, local_z, BLOCK_TOP)
                || c.gettingPowerFrom(local_x, local_y+1, local_z, BLOCK_BOTTOM)
                || c.gettingPowerFrom(local_x, local_y, local_z-1, BLOCK_BACK)
                || c.gettingPowerFrom(local_x, local_y, local_z+1, BLOCK_FRONT)
            );
            break;
    }

    // Get the piston's powered-state and its type
    const uint8_t piston_powered = static_cast<uint8_t>((getBLOCKDATA(block) & piston_powered_bits) >> piston_power_bit_shift);
    const PISTON_TYPE piston_type = static_cast<PISTON_TYPE>((getBLOCKDATA(block) & piston_data_bits) >> piston_bit_shift);

    // If the piston's power state has changed and it isn't a piston_head
    if(piston_powered != poweredProperly && piston_type != PISTON_HEAD) {

        // Get the piston's data and prepare it by resetting its powered state
        uint8_t piston_data = getBLOCKDATA(block) ^ (piston_powered << piston_power_bit_shift); // Set pre-existing power bit to zero

        // If it is powered "properly" (not by the face)
        if (poweredProperly) {
            // Get the block to push
            BLOCK_WDATA blockToPush = c.getGlobalBlockRelative(pistonHeadCoordinates.x, pistonHeadCoordinates.y, pistonHeadCoordinates.z);

            // If the block to push isn't an unmovable block
            if (std::find(unmovableBlocks.begin(), unmovableBlocks.end(), getBLOCK(blockToPush)) == unmovableBlocks.end() && std::find(unmovableBlocks.begin(), unmovableBlocks.end(), blockToPush) == unmovableBlocks.end()) {
                piston_data = piston_data ^ (piston_type << piston_bit_shift); // Set pre-existing piston type bits to zero

                // Set the block to the piston body
                c.setLocalBlock(local_x, local_y, local_z, getBLOCKWDATA(getBLOCK(block), piston_data | poweredProperly << piston_power_bit_shift | PISTON_BODY << piston_bit_shift));

                // If the block isn't air, then "push" the block (pushing air causes bugs)
                if (blockToPush != BLOCK_AIR) {
                    c.setGlobalBlockRelative(blockToPushCoordinates.x, blockToPushCoordinates.y, blockToPushCoordinates.z, blockToPush);
                }

                // Set the corresponding block to the piston head
                c.setGlobalBlockRelative(pistonHeadCoordinates.x, pistonHeadCoordinates.y, pistonHeadCoordinates.z, getBLOCKWDATA(BLOCK_PISTON, side | PISTON_HEAD << piston_bit_shift));
            } else {
                // If the block isn't powered properly, simply update the powereyness of the piston without extending it
                c.setLocalBlock(local_x, local_y, local_z, getBLOCKWDATA(getBLOCK(block), piston_data | poweredProperly << piston_power_bit_shift));
            }
        } else if (piston_type != PISTON_NORMAL) { // If the piston is no longer powered...
            // Reset the piston data's piston type
            piston_data = piston_data ^ (piston_type << piston_bit_shift); // Set pre-existing piston data bits to zero

            // Update the piston type
            c.setLocalBlock(local_x, local_y, local_z, getBLOCKWDATA(getBLOCK(block), piston_data));

            // Remove the piston head
            c.setGlobalBlockRelative(pistonHeadCoordinates.x, pistonHeadCoordinates.y, pistonHeadCoordinates.z, BLOCK_AIR);
        }
    }
}

void PistonRenderer::removedBlock(const BLOCK_WDATA block, int local_x, int local_y, int local_z, Chunk &c) {
    // Check the piston type
    const PISTON_TYPE piston_type = static_cast<PISTON_TYPE>((getBLOCKDATA(block) & piston_data_bits) >> piston_bit_shift);

    // If the piston isn't a "normal" piston
    if (piston_type != PISTON_NORMAL) {
        // Get side-dependant variable thingies
        BLOCK_SIDE side = static_cast<BLOCK_SIDE>(getBLOCKDATA(block) & BLOCK_SIDE_BITS);
        // Piston coordinate stuff
        VECTOR3 pistonHeadCoordinates;
        VECTOR3 pistonBodyCoordinates;

        switch(side)
        {
            default:
                break;
            case BLOCK_BACK:
                pistonHeadCoordinates.x = local_x;
                pistonHeadCoordinates.y = local_y;
                pistonHeadCoordinates.z = local_z+1;

                pistonBodyCoordinates.x = local_x;
                pistonBodyCoordinates.y = local_y;
                pistonBodyCoordinates.z = local_z-1;
                break;
            case BLOCK_FRONT:
                pistonHeadCoordinates.x = local_x;
                pistonHeadCoordinates.y = local_y;
                pistonHeadCoordinates.z = local_z-1;

                pistonBodyCoordinates.x = local_x;
                pistonBodyCoordinates.y = local_y;
                pistonBodyCoordinates.z = local_z+1;
                break;
            case BLOCK_LEFT:
                pistonHeadCoordinates.x = local_x-1;
                pistonHeadCoordinates.y = local_y;
                pistonHeadCoordinates.z = local_z;

                pistonBodyCoordinates.x = local_x+1;
                pistonBodyCoordinates.y = local_y;
                pistonBodyCoordinates.z = local_z;
                break;
            case BLOCK_RIGHT:
                pistonHeadCoordinates.x = local_x+1;
                pistonHeadCoordinates.y = local_y;
                pistonHeadCoordinates.z = local_z;

                pistonBodyCoordinates.x = local_x-1;
                pistonBodyCoordinates.y = local_y;
                pistonBodyCoordinates.z = local_z;
                break;
        }

        // Set the piston's head/body to air, thereby removing it depending on which type the destroyed one is
        switch (piston_type) {
            case PISTON_BODY:
                c.setLocalBlock(pistonHeadCoordinates.x, pistonHeadCoordinates.y, pistonHeadCoordinates.z, getBLOCK(BLOCK_AIR));
                break;
            case PISTON_HEAD:
                c.setLocalBlock(pistonBodyCoordinates.x, pistonBodyCoordinates.y, pistonBodyCoordinates.z, getBLOCK(BLOCK_AIR));
                break;
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
    // Mainly just for debug as PISTON_BODY and PISTON_HEAD should never end up in the inventory
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