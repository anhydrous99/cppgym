//
// Created by constexpr_dog on 5/21/2020.
//

#include "BiPedalWalkerCPP.h"


BipedalWalkerCPP::BipedalWalkerCPP() : _seed((std::random_device())()), world({0, -10}) {
    _ran_generator = std::mt19937(_seed);

    hull_poly_vertices[0].Set(-30 / SCALE, 9 / SCALE);
    hull_poly_vertices[1].Set(6 / SCALE, 9 / SCALE);
    hull_poly_vertices[2].Set(34 / SCALE, 1 / SCALE);
    hull_poly_vertices[3].Set(34 / SCALE, -8 / SCALE);
    hull_poly_vertices[4].Set(-30 / SCALE, -8 / SCALE);
    hull_poly_shape.Set(hull_poly_vertices, 5);
    hull_fd.shape = &hull_poly_shape;
    hull_fd.density = 5.0;
    hull_fd.friction = 0.1;
    hull_fd.restitution = 0.0;
    hull_fd.filter.categoryBits = 0x0020;
    hull_fd.filter.maskBits = 0x001;

    leg_poly_shape.SetAsBox(LEG_W / 2, LEG_H / 2);
    leg_fd.shape = &leg_poly_shape;
    leg_fd.density = 1.0;
    leg_fd.restitution = 0.0;
    leg_fd.filter.categoryBits = 0x0020;
    leg_fd.filter.maskBits = 0x00;

    lower_poly_shape.SetAsBox(0.8 * LEG_W / 2, LEG_H / 2);
    lower_fd.shape = &lower_poly_shape;
    lower_fd.density = 1.0;
    lower_fd.restitution = 0.0;
    lower_fd.filter.categoryBits = 0x0020;
    lower_fd.filter.maskBits = 0x001;

    poly_vertices[0].Set(0, 0);
    poly_vertices[1].Set(1, 0);
    poly_vertices[2].Set(1, -1);
    poly_vertices[3].Set(0, -1);
    polygon_shape.Set(poly_vertices, 4);
    polygon_fd.shape = &polygon_shape;
    polygon_fd.friction = FRICTION;

    edge_vertices[0].Set(0, 0);
    edge_vertices[1].Set(1, 1);
    edge_shape.Set(edge_vertices[0], edge_vertices[1]);
    edge_fd.shape = &edge_shape;
    edge_fd.friction = FRICTION;
    edge_fd.filter.categoryBits = 0x0001;
}
