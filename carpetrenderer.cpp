#include "carpetrenderer.h"

constexpr GLFix CarpetRenderer::carpet_height, CarpetRenderer::carpet_width;

// Get carpet texture function
const TerrainAtlasEntry &CarpetRenderer::getCarpetTexture(const BLOCK_WDATA block) {
    TerrainAtlasEntry &tae = terrain_atlas[0][4];

    switch (static_cast<COLOUR>(getBLOCKDATA(block))) {
        case WHITE_CARPET:
            tae = terrain_atlas[0][4];
            break;
        case ORANGE_CARPET:
            tae = terrain_atlas[2][13];
            break;
        case MAGENTA_CARPET:
            tae = terrain_atlas[2][12];
            break;
        case LIGHT_BLUE_CARPET:
            tae = terrain_atlas[2][11];
            break;
        case YELLOW_CARPET:
            tae = terrain_atlas[2][10];
            break;
        case LIME_CARPET:
            tae = terrain_atlas[2][9];
            break;
        case PINK_CARPET:
            tae = terrain_atlas[2][8];
            break;
        case GRAY_CARPET:
            tae = terrain_atlas[2][7];
            break;
        case LIGHT_GRAY_CARPET:
            tae = terrain_atlas[1][14];
            break;
        case CYAN_CARPET:
            tae = terrain_atlas[1][13];
            break;
        case PURPLE_CARPET:
            tae = terrain_atlas[1][12];
            break;
        case BLUE_CARPET:
            tae = terrain_atlas[1][11];
            break;
        case BROWN_CARPET:
            tae = terrain_atlas[1][10];
            break;
        case GREEN_CARPET:
            tae = terrain_atlas[1][9];
            break;
        case RED_CARPET:
            tae = terrain_atlas[1][8];
            break;
        case BLACK_CARPET:
            tae = terrain_atlas[1][7];
            break;
        default:
            tae = terrain_atlas[0][4];
            break;
    }

    return tae;
}

// Get texture depending on carpet texture
const TerrainAtlasEntry &CarpetRenderer::destructionTexture(const BLOCK_WDATA block) {
    return getCarpetTexture(block);
}

void CarpetRenderer::renderSpecialBlock(const BLOCK_WDATA block, GLFix x, GLFix y, GLFix z, Chunk &c)
{
    const TextureAtlasEntry &carpet_top = getCarpetTexture(block).current;
    TextureAtlasEntry carpet_sid = getCarpetTexture(block).current;

    // Carpet is only 1/16th in size
    carpet_sid.top = carpet_sid.top + (carpet_sid.bottom - carpet_sid.top) * (1 / 16);


    //////
    // GL CODE
    //////

    glPushMatrix();
    glLoadIdentity();

    glTranslatef(x, y, z);

    std::vector<VERTEX> carpet_vertices;
    carpet_vertices.reserve(20);


    // Carpet Side
    carpet_vertices.push_back({0, 0, 0, carpet_sid.left, carpet_sid.bottom, TEXTURE_TRANSPARENT});
    carpet_vertices.push_back({0, GLFix(0) + carpet_height, 0, carpet_sid.left, carpet_sid.top, TEXTURE_TRANSPARENT});
    carpet_vertices.push_back({GLFix(0) + carpet_width, GLFix(0) + carpet_height, 0, carpet_sid.right, carpet_sid.top, TEXTURE_TRANSPARENT});
    carpet_vertices.push_back({GLFix(0) + carpet_width, 0, 0, carpet_sid.right, carpet_sid.bottom, TEXTURE_TRANSPARENT});

    // Carpet Side
    carpet_vertices.push_back({GLFix(0) + carpet_width, 0, GLFix(0) - 0 + BLOCK_SIZE, carpet_sid.left, carpet_sid.bottom, TEXTURE_TRANSPARENT});
    carpet_vertices.push_back({GLFix(0) + carpet_width, GLFix(0) + carpet_height, GLFix(0) - 0 + BLOCK_SIZE, carpet_sid.left, carpet_sid.top, TEXTURE_TRANSPARENT});
    carpet_vertices.push_back({0, GLFix(0) + carpet_height, GLFix(0) - 0 + BLOCK_SIZE, carpet_sid.right, carpet_sid.top, TEXTURE_TRANSPARENT});
    carpet_vertices.push_back({0, 0, GLFix(0) - 0 + BLOCK_SIZE, carpet_sid.right, carpet_sid.bottom, TEXTURE_TRANSPARENT});

    // Carpet Back Side
    carpet_vertices.push_back({0, 0, GLFix(0) + BLOCK_SIZE, carpet_sid.left, carpet_sid.bottom, TEXTURE_TRANSPARENT});
    carpet_vertices.push_back({0, GLFix(0) + carpet_height, 0 + BLOCK_SIZE, carpet_sid.left, carpet_sid.top, TEXTURE_TRANSPARENT});
    carpet_vertices.push_back({0, GLFix(0) + carpet_height, 0, carpet_sid.right, carpet_sid.top, TEXTURE_TRANSPARENT});
    carpet_vertices.push_back({0, 0, 0, carpet_sid.right, carpet_sid.bottom, TEXTURE_TRANSPARENT});

    // Carpet (Front) Inside
    carpet_vertices.push_back({(GLFix(0) - 0) + carpet_width, 0, 0, carpet_sid.left, carpet_sid.bottom, TEXTURE_TRANSPARENT});
    carpet_vertices.push_back({(GLFix(0) - 0) + carpet_width, GLFix(0) + carpet_height, 0, carpet_sid.left, carpet_sid.top, TEXTURE_TRANSPARENT});
    carpet_vertices.push_back({(GLFix(0) - 0) + carpet_width, GLFix(0) + carpet_height, 0 + BLOCK_SIZE, carpet_sid.right, carpet_sid.top, TEXTURE_TRANSPARENT});
    carpet_vertices.push_back({(GLFix(0) - 0) + carpet_width, 0, 0 + BLOCK_SIZE, carpet_sid.right, carpet_sid.bottom, TEXTURE_TRANSPARENT});

    // Carpet Top
    carpet_vertices.push_back({0, GLFix(0) + carpet_height, 0, carpet_top.left, carpet_top.bottom, TEXTURE_TRANSPARENT});
    carpet_vertices.push_back({0, GLFix(0) + carpet_height, GLFix(0) + BLOCK_SIZE - 0, carpet_top.left, carpet_top.top, TEXTURE_TRANSPARENT});
    carpet_vertices.push_back({GLFix(0) + carpet_width - 0, GLFix(0) + carpet_height, GLFix(0) + BLOCK_SIZE - 0, carpet_top.right, carpet_top.top, TEXTURE_TRANSPARENT});
    carpet_vertices.push_back({GLFix(0) + carpet_width - 0, GLFix(0) + carpet_height, 0, carpet_top.right, carpet_top.bottom, TEXTURE_TRANSPARENT});

    for(auto&& v : carpet_vertices)
    {
        VERTEX v1;
        nglMultMatVectRes(transformation, &v, &v1);
        c.addUnalignedVertex(v1.x, v1.y, v1.z, v.u, v.v, v.c);
    }

    glPopMatrix();
}

void CarpetRenderer::geometryNormalBlock(const BLOCK_WDATA block, const int local_x, const int local_y, const int local_z, const BLOCK_SIDE side, Chunk &c)
{
    // Render the bottom of the block as a normal side (needs to be replaced later)
    if(side != BLOCK_BOTTOM)
        return;

    // BOTTOM DOESN'T WORK!!! afdghtresdvbhtredfsvcbgfhtresd
    renderNormalBlockSide(local_x, local_y, local_z, side, getCarpetTexture(block).current, c);
}

AABB CarpetRenderer::getAABB(const BLOCK_WDATA /*block*/, GLFix x, GLFix y, GLFix z)
{
    return {x + 0, y, z + 0, x + 0 + carpet_width, y + carpet_height, z + 0 + carpet_width};
}

void CarpetRenderer::drawPreview(const BLOCK_WDATA block, TEXTURE &dest, int x, int y)
{
    TextureAtlasEntry tex = getCarpetTexture(block).resized;
    BlockRenderer::drawTextureAtlasEntry(*terrain_resized, tex, dest, x, y);
}

const char *CarpetRenderer::getName(const BLOCK_WDATA block)
{
    switch (static_cast<COLOUR>(getBLOCKDATA(block))) {
        case WHITE_CARPET:
            return "White Carpet";
            break;
        case ORANGE_CARPET:
            return "Orange Carpet";
            break;
        case MAGENTA_CARPET:
            return "Magenta Carpet";
            break;
        case LIGHT_BLUE_CARPET:
            return "Light Blue Carpet";
            break;
        case YELLOW_CARPET:
            return "Yellow Carpet";
            break;
        case LIME_CARPET:
            return "Lime Carpet";
            break;
        case PINK_CARPET:
            return "Pink Carpet";
            break;
        case GRAY_CARPET:
            return "Gray Carpet";
            break;
        case LIGHT_GRAY_CARPET:
            return "Light Gray Carpet";
            break;
        case CYAN_CARPET:
            return "Cyan Carpet";
            break;
        case PURPLE_CARPET:
            return "Purple Carpet";
            break;
        case BLUE_CARPET:
            return "Blue Carpet";
            break;
        case BROWN_CARPET:
            return "Brown Carpet";
            break;
        case GREEN_CARPET:
            return "Green Carpet";
            break;
        case RED_CARPET:
            return "Red Carpet";
            break;
        case BLACK_CARPET:
            return "Black Carpet";
            break;
        default:
            return "Carpet";
            break;
    }
}