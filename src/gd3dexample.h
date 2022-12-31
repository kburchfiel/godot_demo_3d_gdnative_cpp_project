//This code is based on the gdexample.h file 
// shown within the Godot GDNative example here:
// https://docs.godotengine.org/en/stable/tutorials/scripting/gdnative/gdnative_cpp_example.html

// By Kenneth Burchfiel
// Released under the MIT License

#ifndef GD3DEXAMPLE_H
#define GD3DEXAMPLE_H

#include <Godot.hpp>
#include <Spatial.hpp> //Located at godot-cpp\include\gen
#include <KinematicBody.hpp> // This script will be attached to a KinematicBody 
// entity, so I changed Sprite.hpp to KinematicBody.hpp.
// I added the following two items based on the code shown in the 'coding the player' 
// section of the Your First 2D Game tutorial. 
// Link: https://docs.godotengine.org/en/stable/getting_started/first_2d_game/03.coding_the_player.html
#include <CollisionShape.hpp> // Located at godot-cpp\include\gen
#include <Input.hpp>




namespace godot {

    class GD3DExample : public Spatial {
        GODOT_CLASS(GD3DExample, Spatial)

        godot::KinematicBody* _kinematic_body;
        godot::Input* _input; // from 'Coding the Player' section of the Your First 2D Game Tutorial
        godot::CollisionShape* _collision_shape; // Also from that section of the tutorial (but with the 2D removed)
        


    public:
        real_t speed = 5; // Also from the 'Your First 2D Game' tutorial
        real_t fall_acceleration = 75;
        real_t jump_impulse = 40;

        GD3DExample(); //These were present in the GDNative tutorial but not in the
        // C++ code shown in the Your First 2D Game tutorial. However, removing them produced an
        // error message, so I added them back in.
        ~GD3DExample();

        void _init(); // our initializer called by Godot

        void _ready(); // From 'Coding the Player' section of Your First 2D Game tutorial.
        // See https://docs.godotengine.org/en/stable/getting_started/first_2d_game/03.coding_the_player.html

        void _physics_process(float delta); // My project uses _physics_process
        //for the kinematic body, so I replaced _process with _physics_process here.

        static void _register_methods();
    };

}

#endif