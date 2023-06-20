// This code is based on the main.cpp code shown in the GDNative C++ version
// of the Your First 2D Game project and on some other items, including
// the bullet code within the 'Obtaining information' section in the Using
// 3D Transforms documentation page (link:
// https://docs.godotengine.org/en/stable/tutorials/3d/using_transforms.html#obtaining-information )
// 
// 

//By Kenneth Burchfiel
//Released under the MIT license

#include "main.h"
// #include "projectile.h"
// #include "enemy3d.h"
#include <SceneTree.hpp>

using namespace godot;

void Main::_register_methods()
// I believe all of the functions defined within this code need 
// to be present within register_methods(); otherwise, your project
// might crash without any error message (as I found at one point)
{
    //Godot::print("Main test point 1");
    //register_method("shoot", &Main::shoot);
    //register_method("enemy_shoot", &Main::enemy_shoot);
    //Godot::print("Main test point 1b");
    register_method("_ready", &Main::_ready);
    register_method("_process", &Main::_process);
    //Godot::print("Main test point 1c");
    //godot::register_property("projectile_scene", &Main::projectile_scene, (godot::Ref<godot::PackedScene>)nullptr);
    //Godot::print("Main test point 1d");
}

void Main::_ready() {
    _player3d = get_node<Player3D>("Player3D");
    _enemy3d = get_node<Enemy3D>("Enemy3D");
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

void Main::_process() {
    //Godot::print("Main test point 6");
    }