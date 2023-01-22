// Based on the main.h file within the completed GDNative/C++ 
// version of the Your First 2D Game tutorial

//By Kenneth Burchfiel
//Released under the MIT license

#ifndef MAIN_H
#define MAIN_H

#include <Godot.hpp>
#include <Node.hpp>
#include <PackedScene.hpp>
#include <Input.hpp>

#include "player3d.h"
#include "projectile.h"
#include "enemy3d.h"



namespace godot {

	class Main : public godot::Node {
		GODOT_CLASS(Main, godot::Node)

		Player3D* _player3d;
		Enemy3D* _enemy3d;
		godot::Input* _input;


	public:
		godot::Ref<godot::PackedScene> projectile_scene; // Based on: 
		// https://docs.godotengine.org/en/stable/getting_started/first_2d_game/05.the_main_game_scene.html
		// This resource taught me how to link my projectile scene
		// to my player scene within the Godot editor so that the player can generate
		// new projectiles when a button is pressed.


		//Main(); // These constructors and destructors weren't present
		// in the main.hpp file within the GDNative/C++ version
		// of the Your First 2D Game tutorial, so I commented
		// them out here.

		//~Main();

		void _init() {}
		void _ready();
		void _process();
		void shoot();
		void enemy_shoot();
		static void _register_methods();

	};

}

#endif // MAIN_H