#include <iostream>
#include <unordered_set>


// Function to remove duplicates from an array of characters
std::unordered_set<char> removeDuplicates(char chars[], int length) {
    std::unordered_set<char> seen;

    // Loop through the array and add each character to the set
    // set has only unique elements so no dublicates will be added
    for (int i = 0; i < length; ++i) {
        char c = chars[i];
        seen.insert(c);
    }

    return seen;
}

int main() {
    char chars[] = { 'a', 'b', 'c', 'a', 'd', 'b', 'e' };
    int length = sizeof(chars) / sizeof(chars[0]);

    // Call the removeDuplicates function to get unique characters
    std::unordered_set<char> noDuplicates = removeDuplicates(chars, length);

    // Print the unique characters
    for (char c : noDuplicates) {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    return 0;
}
