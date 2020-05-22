//
// Created by constexpr_dog on 5/21/2020.
//

#ifndef CPPGYM_BIPEDALWALKERCPP_H
#define CPPGYM_BIPEDALWALKERCPP_H

#include <random>
#include <cstdint>
#include <box2d/b2_world.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_edge_shape.h>
#include <box2d/b2_polygon_shape.h>

#define FPS 50
#define SCALE 30.0f
#define MOTORS_TORQUE 80
#define SPEED_HIP 4
#define SPEED_KNEE 6
#define LIDAR_RANGE = 160 / SCALE
#define INITIAL_RANDOM = 5
#define LEG_DOWN -8 / SCALE
#define LEG_W 8 / SCALE
#define LEG_H 34 / SCALE
#define VIEWPORT_W 600
#define VIEWPORT_H 400
#define TERRAIN_STEP 14 / SCALE
#define TERRAIN_LENGTH 200
#define TERRAIN_HEIGHT VEWPORT_H / SCALE / 4
#define TERRAIN_GRASS 10
#define TERRAIN_STARTPAD 20
#define FRICTION 2.5

class BipedalWalkerCPP {
    b2World world;
    std::mt19937 _ran_generator;
    uint32_t _seed;

    b2Vec2 hull_poly_vertices[5];
    b2PolygonShape hull_poly_shape;
    b2FixtureDef hull_fd;

    b2PolygonShape leg_poly_shape;
    b2FixtureDef leg_fd;

    b2PolygonShape lower_poly_shape;
    b2FixtureDef lower_fd;

    b2Vec2 poly_vertices[4];
    b2PolygonShape polygon_shape;
    b2FixtureDef polygon_fd;

    b2Vec2 edge_vertices[2];
    b2EdgeShape edge_shape;
    b2FixtureDef edge_fd;

public:
    BipedalWalkerCPP();
};

#endif //CPPGYM_BIPEDALWALKERCPP_H
