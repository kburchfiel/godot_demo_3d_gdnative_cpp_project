// This code is based on my player3d.cpp code 
// and on the bullet code shown in:
// https://docs.godotengine.org/en/3.5/tutorials/physics/using_kinematic_body_2d.html

//By Kenneth Burchfiel
//Released under the MIT license

#include "projectile.h"


using namespace godot;

//godot::Vector3 bullet_velocity(0, 0, 0); // Note that this cannot
//// be called 'velocity' because a variable with that name has
//// already been defined within player3d.cpp.


void Projectile::_register_methods() {
	register_method("_physics_process", &Projectile::_physics_process);
	//register_method("start", &Projectile::start);
	godot::register_property("projectile_speed", &Projectile::projectile_speed, (real_t)50.0);
}

void Projectile::_ready()

{

}

Projectile::Projectile() {
    //Godot::print("Projectile test point 1");
}

Projectile::~Projectile() {
    //Godot::print("Projectile test point 2");
}

void Projectile::_init() {
    //Godot::print("Projectile init!");
}

	//void Projectile::start(godot::Vector3 pos, godot::Vector3 dir) {
	//	godot::Vector3 rotation = dir;
	//	godot::Vector3 position = pos;
	//	bullet_velocity = godot::Vector3(0, 0, projectile_speed);
	//}

	
void Projectile::_physics_process(float delta) {

	godot::Transform projectile_transform = get_transform();
	//Godot::print("Projectile_Transform:");
	//Godot::print(projectile_transform);

	godot::Vector3 projectile_velocity = projectile_transform.basis.z * projectile_speed;
	// The above line is based on the bullet.speed = transform.basis.z * BULLET_SPEED GDScript code
	// found at: https://docs.godotengine.org/en/stable/tutorials/3d/using_transforms.html


	projectile_velocity.y -= fall_acceleration * delta;

	projectile_velocity = move_and_slide(projectile_velocity, godot::Vector3(0, 1, 0));

}