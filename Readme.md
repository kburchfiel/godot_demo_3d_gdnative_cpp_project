# Cube Combat: My Godot C++ 3D Demo Project (Using Godot 3.5 and GDNative)

![](https://raw.githubusercontent.com/kburchfiel/godot_demo_3d_gdnative_cpp_project/master/project_images/winning_game.gif)

![](https://raw.githubusercontent.com/kburchfiel/godot_demo_3d_gdnative_cpp_project/master/project_images/losing_game.gif)

I created this project in order to learn how to develop 3D Godot games using GDNative and C++. I hope that you will find the project helpful in designing your own Godot C++ games.

The game itself is very simple: The cube that you control must shoot another cube that is trying to shoot it. You can move with the arrow keys, 'jump' with the space bar, and fire projectiles by pressing 'E' or 'D'. There's no formal 'New Game' or 'Game Over' screen, but you can launch a new game simply by closing the window and restarting the .exe file.

To quickly see the project in action, download the .exe and .dll files from the project folder. (Currently, these work only on Windows desktops.) More information on compiling the project can be found within the 'Instructions' section.

Note that this project is based on the 3.5 release of Godot, as a stable release of Godot 4.0 was not yet available. Therefore, it uses GDNative rather than GDExtension. I may create a similar project using GDExtension in the future.

Although it would have been faster to create this game using GDScript, I found this to be a fun way to practice using C++.

(You can find a blog post I wrote on this program [here](https://kburchfiel3.wordpress.com/2023/07/25/using-c-to-create-a-simple-3d-game-in-godot/). 

# Resources:

The following resources proved very helpful in creating this project:

[Godot Docs--Branch for Version 3.5](https://docs.godotengine.org/en/3.5/index.html) (Since this project uses Godot 3.5, the 3.5 branch will generally be more useful than the default branch that superseded it.

* [GDNative C++ Documentation](https://docs.godotengine.org/en/3.5/tutorials/scripting/gdnative/gdnative_cpp_example.html) (Going through this tutorial was very helpful in understanding how to integrate GDNative script into a Godot project) 

* [GDNative C Documentation](https://docs.godotengine.org/en/3.5/tutorials/scripting/gdnative/gdnative_c_example.html) (Godot recommends reading this before going through the C++ documentation.) 

* [Version 3.5 of godot-cpp](https://github.com/godotengine/godot-cpp/tree/3.5) and [the godot-headers folder that corresponds to this version of godot-cpp](https://github.com/godotengine/godot-headers/tree/63d04316d3236ad139f3eb9e6cf20f5719a61e05) (essential for developing C++ code within GDNative)

* [Your First 2D Game tutorial](https://docs.godotengine.org/en/3.5/getting_started/first_2d_game/index.html) (this tutorial provides both C++ and GDScript code excerpts, which helped me learn how to 'translate' GDScript into C++ code. In order to get this tutorial to run correctly, see my notes at [this forum link](https://godotforums.org/d/32246-notes-on-getting-the-your-first-2d-game-tutorial-to-work-with-c-code).)

* [Completed Version of the Your First 2D Game Tutorial using GDNative and C++](https://github.com/godotengine/gdnative-demos/tree/master/cpp/dodge_the_creeps) (This project was invaluable in getting the Your First 2D Game tutorial to work correctly.)

* [Your First 3D Game tutorial](https://docs.godotengine.org/en/3.5/getting_started/first_3d_game/index.html) (provides 3D-compatible GDScript which I could use as a basis for 3D C++ code)

* [Godot API](https://docs.godotengine.org/en/3.5/classes/index.html)

* [Godot Engine source code](https://github.com/godotengine/godot/tree/3.5)

As an example of how to cross-reference these documents (e.g. in order to convert GDScript to GDNative C++ script):

* Information on the move_and_slide() function can be found within the Godot API on the [KinematicBody page](https://docs.godotengine.org/en/3.5/classes/class_kinematicbody.html?highlight=move_and_slide#class-kinematicbody-method-move-and-slide). 

* This function can also be found within the Godot source code [here](https://github.com/godotengine/godot/blob/3.5/scene/3d/physics_body.cpp). (Thank you [kidscancode](https://godotengine.org/qa/138386/how-does-move_and_slide-use-move_and_collide-under-the-hood) for helping me find it.)
 
* It’s also referenced within the compiled version of godot-cpp at include\gen\KinematicBody.hpp and src\gen\KinematicBody.cpp.

# Instructions:

In order to get this project running on your own computer, you'll need to first download and compile version 3.5 of godot-cpp and its corresponding godot-headers folder. (See above for links.) After compiling them (see the [GDNative tutorial](https://docs.godotengine.org/en/3.5/tutorials/scripting/gdnative/gdnative_cpp_example.html) for instructions on doing so), copy and paste them into a 'godot-cpp' folder, which should be at the same level as the 'project' and 'src' folders.

Once you have done so, you can then use scons to compile the code stored in the src folder, which should in turn allow you to run the Godot project successfully. For instance, since I'm using Windows, I compile my updated code by entering the following lines in x64 Native Tools Command Prompt for VS 2022:

1. cd "C:\Users\kburc\D1V1\Godot\test_3d_project_using_gdnative" (This is my project file, e.g. the one that contains godot-cpp, src (which contains my code), and SConstruct.)
2. 'scons platform = windows'

If you have any trouble getting the code to run, make sure to reference the links shared within the Resources section above.

# Methodology:

My initial approach was to first create a version of this project using GDScript, then port this code into C++. In order to get the port to work successfully, I relied heavily on the links shown within the 'resources' list. For instance, I could compare the GDScript and GDNative C++ code snippets within the [Your First 2D Game tutorial](https://docs.godotengine.org/en/3.5/getting_started/first_2d_game/index.html) to better understand how to convert 3D GDScript code into equivalent C++ code.

However, once I became more familiar with C++ GDNative programming, I sometimes skipped the GDScript step and coded directly in C++, using the Godot engine code and Godot documentation (among other resources) as references.

In order to share the project on GitHub, I simply opened my project folder within Visual Studio Code and used the Git extension to push my changes to my project page (https://github.com/kburchfiel/godot_demo_3d_gdnative_cpp_project).

There are plenty of ways to improve this project, but now that I've created a working concept, I'd like to spend some time with Unreal Engine so that I can determine which engine I'd like to place most of my focus on in the future.
