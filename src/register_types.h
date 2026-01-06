/**
 * @file register_types.h
 * @brief Module initialization and registration for the GDExtension plugin.
 */

#pragma once

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

/**
 * @brief Initializes the GDExtension module at the specified initialization level.
 * 
 * This function is called by Godot Engine during plugin initialization. It registers
 * all custom classes, methods, and properties defined in this GDExtension with the
 * Godot ClassDB, making them available in the editor and at runtime.
 * 
 * @param p_level The initialization level at which classes should be registered
 *                (e.g., MODULE_INITIALIZATION_LEVEL_SCENE for scene-related classes).
 */
void initialize_example_module(ModuleInitializationLevel p_level);

/**
 * @brief Uninitializes the GDExtension module at the specified initialization level.
 * 
 * This function is called by Godot Engine during plugin cleanup. It should perform
 * any necessary cleanup operations for the module.
 * 
 * @param p_level The initialization level at which cleanup should occur.
 */
void uninitialize_example_module(ModuleInitializationLevel p_level);