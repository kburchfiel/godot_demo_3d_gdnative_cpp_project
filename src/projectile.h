// This code is based off my code for player3d.h, as player3d is also a KinematicBody object.

//By Kenneth Burchfiel
//Released under the MIT license

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <Godot.hpp>
#include <KinematicBody.hpp>
#include <CollisionShape.hpp>
#include <Input.hpp>


namespace godot {

    class Projectile : public KinematicBody {
        GODOT_CLASS(Projectile, KinematicBody)

            godot::Input* _input;
        godot::CollisionShape* _collision_shape; 



    public:
        real_t projectile_speed = 50;
        real_t fall_acceleration = 75;


        Projectile();
        ~Projectile();

        void _init();

        void _ready();

        //void start(godot::Vector3 pos, godot::Vector3 dir); // Based on bullet code in:
        // https://docs.godotengine.org/en/3.5/tutorials/physics/using_kinematic_body_2d.html

        void _physics_process(float delta);

        static void _register_methods();
    };

}

#endif