/**
 * @brief A module interface for working with the collections of Zero 
 * 
 * @file collections.cppm
 * @author Alex Vergara (pyzyryab@tutanota.com)
 * @version 0.1.0
 * @date 2022-09-25
 * @copyright Copyright (c) 2022
 */

export module collections;

export import array;

export {
    const char* collections_miu_greet() {
        return "Hi from the collections module interface unit";
    }
}