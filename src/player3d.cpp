//This code is based on the gdexample.cpp file 
// shown within the Godot GDNative example here:
// https://docs.godotengine.org/en/stable/tutorials/scripting/gdnative/gdnative_cpp_example.html

// By Kenneth Burchfiel
// Released under the MIT License

#include "player3d.h"

using namespace godot;

godot::Vector3 velocity(0, 0, 0); // Replaces the GDScript var velocity = Vector3.ZERO

void Player3D::_register_methods() {
    register_method("_physics_process", &Player3D::_physics_process);
    register_method("_ready", &Player3D::_ready);
    // The following items are based on the register_methods function within:
    // https://github.com/godotengine/gdnative-demos/blob/master/cpp/dodge_the_creeps/src/player.cpp
    godot::register_method("_on_ProjectileDetector_body_entered", &Player3D::_on_ProjectileDetector_body_entered);
    register_method("shoot", &Player3D::shoot);
    // The following lines allow us to modify the specified properties within the Godot editor itself.
    godot::register_property("speed", &Player3D::speed, (real_t)5.0);
    godot::register_property("projectile_distance_from_player", &Player3D::projectile_distance_from_player, (real_t)5.0);
    godot::register_property("fall_acceleration", &Player3D::fall_acceleration, (real_t)75.0);
    godot::register_property("jump_impulse", &Player3D::jump_impulse, (real_t)40.0);
    godot::register_property("player_rotation_speed", &Player3D::player_rotation_speed, (real_t)1.2);
    godot::register_property("projectile_scene", &Player3D::projectile_scene, (godot::Ref<godot::PackedScene>)nullptr);
    //Godot::print("Main test point 1d");
    godot::register_signal<Player3D>("hit_by_projectile", godot::Dictionary()); // Based on the player.cpp code
    //within Godot's Your First 2D Game tutorial



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

// The following items need
// to be named after actual Godot classes rather than what you have named those items.
// e.g. use 'KinematicBody' here instead of 'Player,' even if your KinematicBody object
// is named 'Player.'
// These items also need to be declared within your corresponding .h file; otherwise, you 
// will get an 'undeclared identifier' error.

    _collision_shape = get_node<godot::CollisionShape>("CollisionShape");
    _spatial = get_node<godot::Spatial>("Spatial");
    _input = godot::Input::get_singleton();
}


//void Player3D::shoot() {
//    // Based on the C++ on_MobTimer_timeout() function
//    // shown in https://docs.godotengine.org/en/stable/getting_started/first_2d_game/05.the_main_game_scene.html
//    godot::Node* projectile = projectile_scene->instance();
//    //godot::KinematicBody* projectile_item = projectile->get_node<godot::KinematicBody>("KinematicBody");
//
//    //Projectile projectile = Projectile::new();
//    // For more information on Spatial.new(),
//    // See src\gen\Spatial.cpp within the compiled
//    // version of godot-cpp.
//    //projectile_item = projectile.get_node<godot::KinematicBody>("KinematicBody");
//    //godot::Transform projectile_transform = get_transform();
//    //projectile_item ->set_transform(projectile_transform);
//
//    add_child(projectile);
//    
//    //godot::Vector3 dir(0, 0, 0);
//    //godot::Vector3 pos(0, 0, 0);
//    //projectile->start(pos, dir);
//
//}

//The following function is based on the corresponding function within enemy3d.cpp.
void Player3D::_on_ProjectileDetector_body_entered(godot::Node* _body) {
    Godot::print("_on_ProjectileDetector_body_entered called for player. Collided with:");
    Godot::print(_body->get_name()); // Found get_name at:
    // https://docs.godotengine.org/en/stable/classes/class_node.html
    queue_free(); // Destroys the player instead of simply hiding it.
    Godot::print("Player got destroyed.");
    emit_signal("hit_by_projectile");
    //_collision_shape->set_deferred("disabled", true);
}


void Player3D::shoot() {
    // This function is based on the enemy_shoot() function
    // within enemy3d.cpp.
    Godot::print("Test Point B");
    godot::Node* new_projectile = projectile_scene->instance();
    godot::Transform player_transform = get_transform();
    //If we were accessing the player3d object from main(),
    // we'd need to use _player3d->get_transform(), but since
    // we're already within the Player3D code, we can simply
    // use get_transform().
    //godot::Vector3 player_rotation = _player3d->get_rotation();
    Godot::print("Player transform:");
    Godot::print(player_transform);
    godot::Transform projectile_transform = player_transform;
    projectile_transform = projectile_transform.translated(godot::Vector3(0, 0, projectile_distance_from_player));
    // Increase the z value if needed to prevent your player from getting hit by its own projectile.
    Godot::print("projectile_transform:");
    Godot::print(projectile_transform);

    new_projectile->set("transform", projectile_transform);
    // The above line is based on the operations on mob performed
    // within the _on_MobTimer_timeout() function within main.cpp of the GDNative/C++
    // version of the Your First 2D Game tutorial. Link:
    // https://docs.godotengine.org/en/stable/getting_started/first_2d_game/05.the_main_game_scene.html
    // set() belongs to the Object class. See
    // https://docs.godotengine.org/en/3.5/classes/class_object.html#id4
    //add_child(new_projectile); // Would cause the player's movement to influence the projectiles' movement
    get_parent()->add_child(new_projectile); // Allows the player and projectiles to move independently
    // 
    // 

}





void Player3D::_physics_process(float delta) {
    // Godot::print("Test point 3");
    // I used both the 'Your First 2D Game' C++ code 
    // (https://docs.godotengine.org/en/stable/getting_started/first_2d_game/03.coding_the_player.html ) 
    // and the GDScript code provided in the 'Your First 3D Game'
    // tutorial to create this C++ code.

    if (_input->is_action_just_pressed("shoot")) {
        Godot::print("Test Point A");
        shoot();
        //is_action_just_pressed will only fire one projectile per keypress. See
        // https://docs.godotengine.org/en/stable/classes/class_input.html#class-input-method-is-action-just-pressed
    }


    godot::Vector3 velocity(0, 0, 0); // Similar code appeared within
    // the first line of Player::process within the Your First 2D Game
    // tutorial.
    // Godot::print("Test point 4");

    // In this project, the left/right keys will control the player's rotation whereas the up/down keys will control
    // the player's movement. See
    // https://docs.godotengine.org/en/stable/tutorials/2d/2d_movement.html#rotation-movement for a (2D) example.
    // The following lines are based on the movement code shown at https://docs.godotengine.org/en/stable/getting_started/first_2d_game/03.coding_the_player.html ,
    // except that I'm using the right and left arrow keys to represent rotation instead of the x axis direction.
    real_t rotation_amount = _input->get_action_strength("rotate_right") - _input->get_action_strength("rotate_left");
    // This code was based on the original 
    real_t player_direction = _input->get_action_strength("move_back") - _input->get_action_strength("move_forward");
    // changed from direction.y to direction.z since y refers to vertical movement rather than 
    // forward/back movement.

    rotate(godot::Vector3(0, 1, 0), rotation_amount * -1 * player_rotation_speed / 10);
    // See https://github.com/godotengine/godot/blob/3.5/scene/3d/spatial.cpp ,
    // and https://docs.godotengine.org/en/stable/tutorials/3d/using_transforms.html

    // Note that it's best not to use Godot's rotation property directly--see 
    // https://docs.godotengine.org/en/3.2/tutorials/3d/using_transforms.html#say-no-to-euler-angles

    // I changed the above line from spatial-> rotate to rotate so that the rotations would apply
    // to the whole Player3D object rather than to just the spatial component of the object. This was crucial
    // for getting my projectile initialization code to work, since it relied on the transform state
    // of the Player3D class. If the Player3D class's rotation was unmodified, the projectile would 
    // not have the correct rotation and direction. (See
    // https://godotforums.org/d/32351-having-trouble-making-an-object-travel-the-way-a-player-is-facing-using-c )


    godot::Transform transform = get_transform();
    // Based on https://github.com/godotengine/godot/blob/3.5/scene/3d/spatial.cpp
    // and https://docs.godotengine.org/en/3.2/tutorials/3d/using_transforms.html#obtaining-information

    // Since transform.basis.z represents a Vector3 instance, we can set the player's velocity (another Vector3 instance)
    // by multiplying the player's transform.basis.z by the player's speed, player_direction, and -1. 
    // (The -1 ensures that the player will move forward rather than backward when the up arrow is pressed.)
    // This code was based on https://docs.godotengine.org/en/3.2/tutorials/3d/using_transforms.html#obtaining-information
    velocity = transform.basis.z * speed * player_direction * -1; // 

    velocity.y -= fall_acceleration * delta;
    // vector3.up corresponds to a vector of (0, 1, 0). see 
    // https://docs.godotengine.org/en/stable/classes/class_vector3.html

    // the following if statement is based on the corresponding gdscript
    // statement seen at:
    // https://docs.godotengine.org/en/stable/getting_started/first_3d_game/06.jump_and_squash.html

    if (is_on_floor() && _input->is_action_just_pressed("jump")) {
        // Godot::print("Player jumped");
        velocity.y += jump_impulse;
    }

    velocity = move_and_slide(velocity, godot::Vector3(0, 1, 0));

}
