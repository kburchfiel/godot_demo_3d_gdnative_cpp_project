//This code is based on the gdexample.h file 
// shown within the Godot GDNative example here:
// https://docs.godotengine.org/en/stable/tutorials/scripting/gdnative/gdnative_cpp_example.html

// By Kenneth Burchfiel
// Released under the MIT License

#ifndef PLAYER3D_H
#define PLAYER3D_H

#include <Godot.hpp>
//#include <Spatial.hpp> //Located at godot-cpp\include\gen
#include <KinematicBody.hpp> // This script will be attached to a KinematicBody 
// entity, so I changed Sprite.hpp to KinematicBody.hpp.
// I added the following two items based on the code shown in the 'coding the player' 
// section of the Your First 2D Game tutorial. 
// Link: https://docs.godotengine.org/en/stable/getting_started/first_2d_game/03.coding_the_player.html
#include <CollisionShape.hpp> // Located at godot-cpp\include\gen
#include <Input.hpp>
#include <Area.hpp> // Needed to include this so that Godot recognized godot::Area as valid
#include <PackedScene.hpp> // From 
// https://docs.godotengine.org/en/stable/getting_started/first_2d_game/05.the_main_game_scene.html
#include "projectile.h"




namespace godot {

    class Player3D : public KinematicBody {
        GODOT_CLASS(Player3D, KinematicBody)

        // godot::KinematicBody* _kinematic_body;
        godot::Input* _input; // from 'Coding the Player' section of the Your First 2D Game Tutorial
        godot::CollisionShape* _collision_shape; // Also from that section of the tutorial (but with the 2D removed)
        godot::Spatial* _spatial;
        


    public:
        real_t speed = 5; // Also from the 'Your First 2D Game' tutorial
        real_t fall_acceleration = 75;
        real_t jump_impulse = 40;
        real_t player_rotation_speed = 1.0;
        real_t projectile_distance_from_player = 5.0;
        godot::Ref<godot::PackedScene> projectile_scene;

        Player3D(); // These were present in the GDNative tutorial but not in the
        // C++ code shown in the Your First 2D Game tutorial. However, removing them produced an
        // error message, so I added them back in.
        ~Player3D();


        void _init(); // our initializer called by Godot


        // Don't forget to add the following methods to the register_methods() component
        // of your player3d.cpp script. Otherwise, you'll likely end up with a 'Method not found'
        // error within the Godot console.
        void _ready(); // From 'Coding the Player' section of Your First 2D Game tutorial.
        // See https://docs.godotengine.org/en/stable/getting_started/first_2d_game/03.coding_the_player.html

        void shoot(); // Based on:
        // https://docs.godotengine.org/en/3.5/tutorials/physics/using_kinematic_body_2d.html

        void _physics_process(float delta); // My project uses _physics_process
        //for the kinematic body, so I replaced _process with _physics_process here.

        void _on_ProjectileDetector_body_entered(godot::Node* _body);

        static void _register_methods();
    };

}

#endif