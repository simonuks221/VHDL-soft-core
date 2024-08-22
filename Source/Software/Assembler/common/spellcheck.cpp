#include <algorithm>
#include <iostream>
#include "spellcheck.hpp"

std::array<std::array<unsigned int, SpellCheck::max_word_length>, SpellCheck::max_word_length> SpellCheck::distance_matrix;

int SpellCheck::find_best_match(std::string_view input, std::span<std::string_view> dictionary) {
    unsigned int smallest_distance = max_word_length + max_word_length;
    unsigned int smallest_member_idx = 0;
    for(unsigned int i = 0; i < dictionary.size(); i++) {
        unsigned int distance = find_distance(input, dictionary[i]);
        if(distance < smallest_distance) {
            smallest_member_idx = i;
            smallest_distance = distance;
        }
    }
    if(smallest_distance > word_recognition_threshold) {
        /* Failed to find a close enough word */
        return -1;
    }
    return smallest_member_idx;
}

void SpellCheck::initialise_table(void) {
    /* Initialise first row an collumn to a sequence */
    for(unsigned int i = 0; i < max_word_length; i++) {
        distance_matrix[i][0] = i;
        distance_matrix[0][i] = i;
    }
}

unsigned int SpellCheck::find_distance(std::string_view input_a, std::string_view input_b) {
    unsigned int length_a = input_a.length();
    unsigned int length_b = input_b.length();
    if((length_a >= max_word_length) || (length_b >= max_word_length)) {
        /* Too big to find distance to, return max distance possible */
        return max_word_length + max_word_length;
    }
    /* Check if table is initialised */
    static bool table_initialised = false;
    if(!table_initialised) {
        initialise_table();
        table_initialised = true;
    }
    /* Populate table */
    for(unsigned int i_a = 1; i_a <= length_a; i_a++) {
        for(unsigned int i_b = 1; i_b <= length_b; i_b++) {
            if(input_a[i_a - 1] == input_b[i_b - 1]) {
                /* Characters match, lowest possible distance */
                distance_matrix[i_a][i_b] = distance_matrix[i_a - 1][i_b - 1];
            } else {
                distance_matrix[i_a][i_b] = 1 + std::min({distance_matrix[i_a -1][i_b], distance_matrix[i_a][i_b - 1], distance_matrix[i_a - 1][i_b - 1]});
            }
        }
    }
    /* Lowest distance is at last element */
    return distance_matrix[length_a][length_b];
}