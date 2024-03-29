//This code is based on my player3d.h code.

// By Kenneth Burchfiel
// Released under the MIT License

#ifndef ENEMY3D_H
#define ENEMY3D_H

#include <Godot.hpp>
//#include <Spatial.hpp> //Located at godot-cpp\include\gen
#include <KinematicBody.hpp> // This script will be attached to a KinematicBody 
// entity, so I changed Sprite.hpp to KinematicBody.hpp.
// I added the following two items based on the code shown in the 'coding the enemy' 
// section of the Your First 2D Game tutorial. 
// Link: https://docs.godotengine.org/en/stable/getting_started/first_2d_game/03.coding_the_enemy.html
#include <CollisionShape.hpp> // Located at godot-cpp\include\gen
#include <Input.hpp>
#include <PackedScene.hpp> // From 
// https://docs.godotengine.org/en/stable/getting_started/first_2d_game/05.the_main_game_scene.html
#include <Area.hpp> 
#include "projectile.h"
#include <Timer.hpp> // See https://docs.godotengine.org/en/3.5/getting_started/first_2d_game/05.the_main_game_scene.html





namespace godot {

    class Enemy3D : public KinematicBody {
        GODOT_CLASS(Enemy3D, KinematicBody)

        // godot::KinematicBody* _kinematic_body;
        godot::CollisionShape* _collision_shape;
        godot::Spatial* _spatial;
        //godot::Area* _area;
        godot::Timer* _shoot_timer;
        


    public:
        godot::Ref<godot::PackedScene> projectile_scene;
        real_t enemy_speed = 5; // Also from the 'Your First 2D Game' tutorial
        real_t enemy_fall_acceleration = 75;
        real_t enemy_jump_impulse = 40;
        real_t enemy_rotation_speed = 1.0;
        int shoot_rate = 0;

        Enemy3D(); //These were present in the GDNative tutorial but not in the
        // C++ code shown in the Your First 2D Game tutorial. However, removing them produced an
        // error message, so I added them back in.
        ~Enemy3D();

        void _init(); // our initializer called by Godot

        void _ready(); // From 'Coding the Player' section of Your First 2D Game tutorial.
        // See https://docs.godotengine.org/en/stable/getting_started/first_2d_game/03.coding_the_enemy.html

        void enemy_shoot();

        void _physics_process(float delta); // My project uses _physics_process
        //for the kinematic body, so I replaced _process with _physics_process here.

        void _process();

        void _on_ProjectileDetector_body_entered(godot::Node* _body);

        void _on_ShootTimer_timeout();

        static void _register_methods();
    };

}

#endif