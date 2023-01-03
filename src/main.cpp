// This code is based on the main.cpp code shown in the GDNative C++ version
// of the Your First 2D Game project and on some other items, including:
// the bullet code within the 'Obtaining information' section in the Using
// 3D Transforms documentation page (link:
// https://docs.godotengine.org/en/stable/tutorials/3d/using_transforms.html#obtaining-information )
// 
// 

//By Kenneth Burchfiel
//Released under the MIT license

#include "main.h"
#include "projectile.h"
#include <SceneTree.hpp>

using namespace godot;

void Main::_register_methods()
// I believe all of the functions defined within this code need 
// to be present within register_methods(); otherwise, your project
// might crash without any error message (as I found at one point)
{
    //Godot::print("Main test point 1");
    register_method("shoot", &Main::shoot);
    //Godot::print("Main test point 1b");
    register_method("_ready", &Main::_ready);
    register_method("_process", &Main::_process);
    //Godot::print("Main test point 1c");
    godot::register_property("projectile_scene", &Main::projectile_scene, (godot::Ref<godot::PackedScene>)nullptr);
    //Godot::print("Main test point 1d");
}

void Main::_ready() {
    _player3d = get_node<Player3D>("Player3D");
    //Godot::print("Main test point 2");
    _input = godot::Input::get_singleton();
}

//Main::Main() {
//    Godot::print("Main test point 3");
//}

//Main::~Main() {
//    Godot::print("Main test point 4");
//    // add your cleanup here
//}

void Main::shoot() {
    // This function spawns a projectile, then sets its rotation and translation
    // equal to that of the _player3d instance. This allows the projectile
    // to be fired in the direction the player is facing.
    //Godot::print("Main test point 5");
    godot::Node* new_projectile = projectile_scene->instance();
    //godot::KinematicBody* projectile_item = projectile->get_node<godot::KinematicBody>("KinematicBody");
    godot::Transform player_transform = _player3d->get_transform();
    //godot::Vector3 player_rotation = _player3d->get_rotation();
    Godot::print("Player transform:");
    Godot::print(player_transform);
    //player_transform.basis.z is always 0, 0, 1
    godot::Transform projectile_transform = player_transform;
    //projectile_transform.origin.z += 3; 
    // The above line creates some distance in between the projectile and the player.
    Godot::print("projectile_transform:");
    Godot::print(projectile_transform);

    new_projectile->set("transform", projectile_transform);
    // The above line is based on the operations on mob performed
    // within the _on_MobTimer_timeout() function within main.cpp of the GDNative/C++
    // version of the Your First 2D Game tutorial. Link:
    // https://docs.godotengine.org/en/stable/getting_started/first_2d_game/05.the_main_game_scene.html
    // set() belongs to the Object class. See
    // https://docs.godotengine.org/en/3.5/classes/class_object.html#id4
    add_child(new_projectile);


}

void Main::_process() {
    //Godot::print("Main test point 6");
    if (_input->is_action_just_pressed("shoot")) {
        shoot();
    //is_action_just_pressed will only fire one projectile per keypress. See
    // https://docs.godotengine.org/en/stable/classes/class_input.html#class-input-method-is-action-just-pressed
    }

}