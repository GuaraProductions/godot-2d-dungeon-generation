/**
 * @file gdexample.h
 * @brief Example class demonstrating GDExtension functionality.
 */

#pragma once

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

namespace godot {

/**
 * @class GDExample
 * @brief Example class demonstrating basic GDExtension features.
 * 
 * GDExample is a demonstration class that shows how to create a custom GDExtension
 * class with properties, methods, and process callbacks. It extends Sprite2D and
 * includes examples of animation, timing, and method binding.
 * 
 * @extends Sprite2D
 */
class GDExample : public Sprite2D {
	GDCLASS(GDExample, Sprite2D)

private:
	/// Accumulated time passed since start.
	double time_passed;
	
	/// Time at which to emit a signal or event.
	double time_emit;
	
	/// Amplitude value for animations or calculations.
	double amplitude;

protected:
	/**
	 * @brief Binds methods and properties to be accessible from GDScript.
	 */
	static void _bind_methods();

public:
	/**
	 * @brief Default constructor.
	 */
	GDExample();
	
	/**
	 * @brief Destructor.
	 */
	~GDExample();
	
	/**
	 * @brief Sets the amplitude value.
	 * @param p_amplitude New amplitude value.
	 */
	void set_amplitude(const double p_amplitude);
	
	/**
	 * @brief Gets the current amplitude value.
	 * @return Current amplitude.
	 */
	double get_amplitude();
	
	/**
	 * @brief Example test method demonstrating basic functionality.
	 * 
	 * This is a test method that can be called from GDScript to verify
	 * the extension is working correctly.
	 */
	void teste_um();
	
	/**
	 * @brief Example method that adds two numbers.
	 * 
	 * Demonstrates how to create methods with parameters and return values
	 * that can be called from GDScript.
	 * 
	 * @param a First number (integer).
	 * @param b Second number (float).
	 * @return Sum of a and b as an integer.
	 */
	int somar_dois_numeros(int a, float b);

	/**
	 * @brief Called every frame to update the sprite.
	 * 
	 * This method is called by Godot Engine every frame and can be used
	 * to implement continuous animations, logic updates, and other per-frame operations.
	 * 
	 * @param delta Time elapsed since the previous frame in seconds.
	 */
	void _process(double delta) override;
};

} // namespace godot
