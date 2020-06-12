#include <string>
namespace arrays_and_strings{
    class Arr{
        public:
            bool isUnique(std::string str);
            bool check_permutation(std::string str1, std::string str2);
            int URLify(char str[]);
            bool check_pp(std::string str);
            bool one_away(std::string str1, std::string str2);
            void str_compression(std::string str);
            void rotate_matrix(int (*matrix)[4]);
            void zero_matrix(int (*matrix)[4]);
    };
}