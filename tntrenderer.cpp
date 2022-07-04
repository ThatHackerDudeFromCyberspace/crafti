#include <cstdlib>

#include "world.h"
#include "tntrenderer.h"

void TNTRenderer::tick(const BLOCK_WDATA /*block*/, int local_x, int local_y, int local_z, Chunk &c)
{
    if(c.isBlockPowered(local_x, local_y, local_z))
        explode(local_x, local_y, local_z, c);
}

void TNTRenderer::explode(const int local_x, const int local_y, const int local_z, Chunk &c)
{
    c.setGlobalBlockRelative(local_x, local_y, local_z, BLOCK_AIR);

    Particle p;
    p.size = 14;
    p.tae = terrain_atlas[1][1].current;

    // Use the center quarter of the texture
    const int tex_width = p.tae.right - p.tae.left,
              tex_height = p.tae.bottom - p.tae.top;
    p.tae.left += tex_width / 4;
    p.tae.right -= tex_width / 4;
    p.tae.top += tex_height / 4;
    p.tae.bottom -= tex_height / 4;

    // Random value between 0 and max (not including max)
    const auto randMax = [](GLFix max) { return max * (rand() & 0xFF) / 0xFF; };

    // Get the center of the block contents (chunk relative coordinates)
    const auto aabb = global_block_renderer.getAABB(getBLOCK(c.getGlobalBlockRelative(local_x, local_y, local_z)), local_x * BLOCK_SIZE, local_y * BLOCK_SIZE, local_z * BLOCK_SIZE);
    auto center = VECTOR3{(aabb.low_x + aabb.high_x) / 2, (aabb.low_y + aabb.high_y) / 2, (aabb.low_z + aabb.high_z) / 2};
    center.x -= local_x;
    center.y -= local_y;
    center.z -= local_z;

    // Spawn four particles at the center with random velocity and offset
    for(int i = 0; i < 4; ++i)
    {
        p.vel = {randMax(10) - 5, randMax(5), randMax(10) - 5};
        p.pos = center;
        p.pos.x += randMax(100) - 50;
        p.pos.y += randMax(100) - 50;
        p.pos.z += randMax(100) - 50;
        c.addParticle(p);
    }

    // Destroy everything in a sphere with a 3 block radius
    const int dist = 3;

    for(int x = -dist; x <= dist; ++x)
        for(int y = -dist; y <= dist; ++y)
            for(int z = -dist; z <= dist; ++z)
            {
                if(local_y + y + Chunk::SIZE * c.y < 1 || local_y + y + Chunk::SIZE * c.y >= World::HEIGHT*Chunk::SIZE)
                    continue;

                if(x*x + y*y + z*z > dist*dist)
                    continue;

                //Explode other TNT blocks
                auto block = getBLOCK(c.getGlobalBlockRelative(local_x + x, local_y + y, local_z + z));
                if(block == BLOCK_TNT)
                    explode(local_x + x, local_y + y, local_z + z, c);
                else if(block != BLOCK_BEDROCK && block != BLOCK_AIR)
                    c.changeGlobalBlockRelative(local_x + x, local_y + y, local_z + z, BLOCK_AIR);
            }
}
