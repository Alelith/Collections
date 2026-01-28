/**
 * @mainpage Collections Library Documentation
 * 
 * @section intro_sec Introduction
 * A comprehensive C++ template library providing efficient 
 * implementations of fundamental data structures and utility functions
 * for modern C++ applications.
 * 
 * @section features_sec Features
 * - Dynamic vector with automatic memory management
 * - Single and double linked list implementations
 * - Stack and queue containers with deque support
 * - Character validation and string comparison utilities
 * - Type conversion functions for numeric and string types
 * - STL-compatible iterators and container interfaces
 * - Exception-safe operations with RAII principles
 * - Move semantics support for optimal performance
 * 
 * @section architecture_sec Architecture
 * The library is organized into three main modules: linear data
 * structures (vectors, lists, stacks, queues), tree structures
 * (binary trees), and standard utility functions (type checking and
 * conversion). All container classes are implemented as templates to
 * support generic programming with any data type.
 * 
 * @section implementation_sec Implementation
 * Data structures use template-based implementations with separate
 * header (.hpp) and template implementation (.tpp) files. Memory
 * management follows RAII principles with proper copy/move semantics.
 * All containers provide STL-compatible interfaces including iterators,
 * type aliases, and standard member functions.
 * 
 * @section dependencies_sec Dependencies
 * - C++11 or higher (for move semantics and auto type deduction)
 * - Standard C++ Library (iostream, string, stdexcept)
 * 
 * @section install_sec Installation
 * Include super_lib.hpp in your project to access all library
 * components. The library is header-only for template classes.
 * Compile utility functions from src/ directory and link with your
 * application.
 * 
 * @section usage_sec Usage
 * Include the main header: #include "super_lib.hpp"
 * Create containers: Vector<int> vec; LinkedList<string> list;
 * Use utility functions: isAlphabetic('a'); intToString(42);
 * 
 * @section license_sec License
 * This library is provided as-is for educational and commercial use.
 */

/**
 * @file super_lib.hpp
 * @brief Main header file aggregating all library components
 * 
 * @author Lilith Estévez Boeta
 * @date 2025-01-28
 */

#ifndef SUPER_LIB_HPP
#define SUPER_LIB_HPP

#include "standard_functions/check.hpp"
#include "standard_functions/conversion.hpp"

#include "linear/deque.hpp"
#include "linear/double_linked_list.hpp"
#include "linear/linked_list.hpp"
#include "linear/queue.hpp"
#include "linear/stack.hpp"
#include "linear/vector.hpp"

#endif
