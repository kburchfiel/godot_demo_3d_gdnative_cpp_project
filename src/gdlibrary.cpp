// This code is based on the code shown in Godot's GDNative example, 
// which can be found at:
// https://docs.godotengine.org/en/stable/tutorials/scripting/gdnative/gdnative_cpp_example.html

// Don't forget to update the following #include statements after adding in new classes.
#include "player3d.h"
#include "projectile.h"
#include "main.h"
#include "enemy3d.h"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options * o) {
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options * o) {
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void* handle) {
    godot::Godot::nativescript_init(handle);

    godot::register_class<godot::Player3D>();

    godot::register_class<godot::Projectile>();

    godot::register_class<godot::Main>();

    godot::register_class<godot::Enemy3D>();

}