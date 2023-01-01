//This code is based on the gdexample.h file 
// shown within the Godot GDNative example here:
// https://docs.godotengine.org/en/stable/tutorials/scripting/gdnative/gdnative_cpp_example.html

// By Kenneth Burchfiel
// Released under the MIT License

// Use Ctrl + K + C and Ctrl + K + U to comment and uncomment code in Visual Studio, respectively.

#include "player3d.h"

using namespace godot;

godot::Vector3 velocity(0, 0, 0); // Replaces the GDScript var velocity = Vector3.ZERO

void Player3D::_register_methods() {
    register_method("_physics_process", &Player3D::_physics_process);
    register_method("_ready", &Player3D::_ready);
    // The following items are based on the register_methods function within:
    // https://github.com/godotengine/gdnative-demos/blob/master/cpp/dodge_the_creeps/src/player.cpp
    // These lines allow us to modify the specified properties within the Godot editor itself.
    godot::register_property("speed", &Player3D::speed, (real_t)5.0);
    godot::register_property("fall_acceleration", &Player3D::fall_acceleration, (real_t)75.0);
    godot::register_property("jump_impulse", &Player3D::jump_impulse, (real_t)40.0);



}
// Since my character uses _physics_process to move rather than _process,
// I changed _process to _physics_process here.

Player3D::Player3D() {
    Godot::print("Test point 1");
}

Player3D::~Player3D() {
    Godot::print("Test point 2");
    // add your cleanup here
}

void Player3D::_init() {
    // initialize any variables here
    Godot::print("Here is a message printed using C++!");
    // See https://github.com/godotengine/godot-cpp/blob/3.5/src/core/GodotGlobal.cpp
}


// Player::ready() is based on the ready() code shown in the Your First 2D Game tutorial.
//I replaced the items shown within that code with the items that my player uses (e.g.
// KinematicBody and CollisionShape).
void Player3D::_ready() {
    _collision_shape = get_node<godot::CollisionShape>("CollisionShape");
    // These need
    // to be named after actual Godot classes rather than what you have named those items.
    // e.g. use 'KinematicBody' here instead of 'Player,' even if your KinematicBody object
    // is named 'Player.'
    // These items also need to be declared within your corresponding .h file; otherwise, you 
    // will get an 'undeclared identifier' error.
    _input = godot::Input::get_singleton();

}


void Player3D::_physics_process(float delta) {
    // Godot::print("Test point 3");
    // I used both the 'Your First 2D Game' C++ code 
    // (https://docs.godotengine.org/en/stable/getting_started/first_2d_game/03.coding_the_player.html ) 
    // and the GDScript code provided in the 'Your First 3D Game'
    // tutorial to create this C++ code.

    godot::Vector3 velocity(0, 0, 0); // Similar code appeared within
    // the first line of Player::process within the Your First 2D Game
    // tutorial.
    // Godot::print("Test point 4");

    godot::Vector3 direction(0, 0, 0);
        // Replaces var direction = Vector3.ZERO
    // The following two lines come directly from the movement
    // code shown at:
    // https://docs.godotengine.org/en/stable/getting_started/first_2d_game/03.coding_the_player.html
    // I am using 'direction' instead of 'velocity' because the Your First
    // 3D Game tutorial's GDScript defines velocity as the product
    // of the 'direction' and 'speed' variables.
    //Godot::print("Test point 5");


    direction.x = _input->get_action_strength("move_right") - _input->get_action_strength("move_left");
    direction.z = _input->get_action_strength("move_back") - _input->get_action_strength("move_forward");
    // changed from direction.y to direction.z since y refers to vertical movement rather than 
    // forward/back movement.

    // godot::vector3 position = get_position(); # probably not needed 
    // here because we're using move_and_slide

    if (direction.length() > 0) {
        // Godot::print("test point 6");
        direction = direction.normalized() * speed;
    }

    // Godot::print("test point 7");
    velocity.x = direction.x * speed;
    velocity.z = direction.z * speed;
    // Godot::print("test point 7.5");
    velocity.y -= fall_acceleration * delta;
    // vector3.up corresponds to a vector of (0, 1, 0). see 
    // https://docs.godotengine.org/en/stable/classes/class_vector3.html
    // Godot::print("test point 8");

    // the following if statement is based on the corresponding gdscript
    // statement seen at:
    // https://docs.godotengine.org/en/stable/getting_started/first_3d_game/06.jump_and_squash.html
    
    //if (_input->is_action_just_pressed("jump")) {
    //    Godot::print("Player jumped");
    //        //velocity.y += jump_impulse;
    //}
    //
    
    
    if (is_on_floor() && _input->is_action_just_pressed("jump")) {
        // Godot::print("Player jumped");
        velocity.y += jump_impulse;
    }

    velocity = move_and_slide(velocity, godot::Vector3(0,1,0));
    //// i'm guessing that this function applies the velocity to the character,
    //// even though the character wasn't explicitly mentioned in this function.

    }