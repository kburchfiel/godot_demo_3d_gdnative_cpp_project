//This code is based on my player3d.cpp code.

// By Kenneth Burchfiel
// Released under the MIT License

#include "enemy3d.h"
#include <SceneTree.hpp>


using namespace godot;


void Enemy3D::_register_methods() {
    register_method("_physics_process", &Enemy3D::_physics_process);
    register_method("_process", &Enemy3D::_process);
    register_method("_ready", &Enemy3D::_ready);
    register_method("enemy_shoot", &Enemy3D::enemy_shoot);
    godot::register_method("_on_ProjectileDetector_body_entered", &Enemy3D::_on_ProjectileDetector_body_entered);
    godot::register_method("_on_ShootTimer_timeout", &Enemy3D::_on_ShootTimer_timeout);
    godot::register_property("enemy_speed", &Enemy3D::enemy_speed, (real_t)5.0);
    godot::register_property("enemy_fall_acceleration", &Enemy3D::enemy_fall_acceleration, (real_t)75.0);
    godot::register_property("enemy_jump_impulse", &Enemy3D::enemy_jump_impulse, (real_t)40.0);
    godot::register_property("enemy_rotation_speed", &Enemy3D::enemy_rotation_speed, (real_t)1.0);
    godot::register_signal<Enemy3D>("hit_by_projectile", godot::Dictionary()); // Based on the player.cpp code
    //within Godot's Your First 2D Game tutorial
    godot::register_property("projectile_scene", &Enemy3D::projectile_scene, (godot::Ref<godot::PackedScene>)nullptr);
}
 
Enemy3D::Enemy3D() {
    Godot::print("Enemy constructor called.");
}

Enemy3D::~Enemy3D() {
    Godot::print("Enemy destructor called.");
}

void Enemy3D::_init() {
    Godot::print("Enemy initialized.");
    // See https://github.com/godotengine/godot-cpp/blob/3.5/src/core/GodotGlobal.cpp
}


void Enemy3D::_ready() {
    _collision_shape = get_node<godot::CollisionShape>("CollisionShape");
    _spatial = get_node<godot::Spatial>("Spatial");
    //_area = get_node<godot::Area>("Area");
    _shoot_timer = get_node<godot::Timer>("ShootTimer");
}

//The following function is based on the on_Player_body_entered function 
// within the player.cpp code in Godot's Your First 2D Game tutorial
// and on the _on_MobDetector_body_entered(_body) function within
// the Your First 3D Game tutorial (https://docs.godotengine.org/en/stable/getting_started/first_3d_game/07.killing_player.html ).
// I also needed to connect the body_entered signal of the Area component of my Enemy3D 
// node within the Enemy scene to this function (see the Your First 3D Game tutorial,
// linked to above, for an example of this process). I named this Area component
// 'ProjectileDetector.'
//The use of godot::Node* body was based on the on_Player_body_entered 
// code and on https://docs.godotengine.org/en/3.1/classes/class_area.html?highlight=area#area .
void Enemy3D::_on_ProjectileDetector_body_entered(godot::Node* _body) {
    Godot::print("_on_ProjectileDetector_body_entered called for enemy. Collided with:");
    Godot::print(_body->get_name()); // Found get_name at:
    // https://docs.godotengine.org/en/stable/classes/class_node.html
    queue_free(); // Destroys the enemy instead of simply hiding it.
    Godot::print("Destroyed enemy.");
    emit_signal("hit_by_projectile"); 
    //_collision_shape->set_deferred("disabled", true);
}


void Enemy3D::enemy_shoot() {
    // This function spawns a projectile, then sets its rotation and translation
    // equal to that of the enemy3d instance. This allows the projectile
    // to be fired in the direction the enemy is facing.
    //Thefunction is based in part on the bullet code within the 'Obtaining
    // information' section in the Using
    // 3D Transforms documentation page (link:
    // https://docs.godotengine.org/en/stable/tutorials/3d/using_transforms.html#obtaining-information )
    //Godot::print("Main test point 5");
    godot::Node* new_projectile = projectile_scene->instance();
    //Note: In order for the above line to work (without crashing the game), you'll need to create 
    // a projectile_scene property and then link your Projectile.tscn file to it within the Godot editor.
    // Otherwise, Godot won't know what to load and the game will stop, possibly without any error message.
    //godot::KinematicBody* projectile_item = projectile->get_node<godot::KinematicBody>("KinematicBody");
    godot::Transform enemy_transform = get_transform();
    //godot::Vector3 player_rotation = _player3d->get_rotation();
    //Godot::print("Enemy3d transform:");
    //Godot::print(enemy_transform);
    //Godot::print("Enemy3d transform.basis.z:");
    //Godot::print(enemy_transform.basis.z);
    godot::Transform projectile_transform = enemy_transform;
    projectile_transform = projectile_transform.translated(godot::Vector3(0, 0, 1));
    // The above line creates some distance in between the projectile and the enemy. This prevents the enemy from
    // getting hit by its own bullet immediately after firing!
    // For translated(), see:
    // https://docs.godotengine.org/en/stable/classes/class_transform.html#class-transform-method-translated
    //Godot::print("projectile_transform:");
    //Godot::print(projectile_transform);

    new_projectile->set("transform", projectile_transform);
    // The above line is based on the operations on mob performed
    // within the _on_MobTimer_timeout() function within main.cpp of the GDNative/C++
    // version of the Your First 2D Game tutorial. Link:
    // https://docs.godotengine.org/en/stable/getting_started/first_2d_game/05.the_main_game_scene.html
    // set() belongs to the Object class. See
    // https://docs.godotengine.org/en/3.5/classes/class_object.html#id4
    get_parent()->add_child(new_projectile);
    //get_parent() was added in so that the projectiles will move independently of the player's movement.
    // Thanks to jgodfrey for suggesting this (see
    // https://godotengine.org/qa/89944/bullets-move-with-player ).
}


void Enemy3D::_on_ShootTimer_timeout() {
    enemy_shoot();
}
// Previousy, I had the enemy shoot on every frame by including enemy_shoot() inside a _process()
// function. However, that made the game a bit trickier to win! Therefore, I instead created a 
// timer (ShootTimer) within my Godot project and instructed the game to call enemy_shoot() only
// when that timer runs out. By adjusting the timer's Wait Time setting (within its Inspector menu), 
// I can make the game relatively easier or harder.
// I connected this function to the ShootTimer I created within Godot by going to the Node section
// of the ShootTimer, right_clicking on the 'timeout() signal and clicking 'connect', and then
// connecting my Enemy3D script to that signal. _on_ShootTimer_timeout was already present
// within the Receiver Method option, so I didn't need to update it there.


void Enemy3D::_physics_process(float delta) {
    // Unlike the player code, this function will cause the enemy to move and rotate in the absence
    // of any player input.

    godot::Vector3 enemy_velocity(0, 0, 0); // Can't be the same name as the player's velocity variable.

    real_t enemy_rotation_amount = 1;
    real_t enemy_direction = 1;
    rotate(godot::Vector3(0, 1, 0), enemy_rotation_amount * -1 * enemy_rotation_speed / 10);
    // See https://github.com/godotengine/godot/blob/3.5/scene/3d/spatial.cpp ,
    // and https://docs.godotengine.org/en/stable/tutorials/3d/using_transforms.html
    godot::Transform transform = get_transform();
    enemy_velocity = transform.basis.z * enemy_speed * enemy_direction; 

    enemy_velocity = move_and_slide(enemy_velocity, godot::Vector3(0, 1, 0));
}

void Enemy3D::_process() {
    // enemy_shoot(); # I used to have the enemy shoot on every frame,
    // but this made the game a bit harder to beat!
}
