#include <string_view>
#include <array>
#include <span>

/* Based on Damerau–Levenshtein distance */
class SpellCheck {
    private:
        SpellCheck() = default;
        ~SpellCheck() = default;

        static constexpr unsigned int max_word_length = 20;
        static constexpr unsigned int word_recognition_threshold = 5;

        static std::array<std::array<unsigned int, max_word_length>, max_word_length> distance_matrix;

        static void initialise_table(void);
        static unsigned int find_distance(std::string_view input_a, std::string_view input_b);
    public:
        /* Returns -1 on error, else index of best match */
        static int find_best_match(std::string_view input, std::span<std::string_view> disctionary);
};