#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// Function to wrap text to fit within a specified line width
// Pass string by reference to avoid making a copy of the entire string
void textWrap(const string& text, int lineWidth) {
    vector<string> words; // Vector to store individual words
    string word; // Variable to store each word read from the text
    istringstream iss(text); // Input string stream to split the text into words

    // Split the text into words and store them in the 'words' vector
    while (iss >> word) {
        words.push_back(word);
    }

    int currentLineWidth = 0; // Variable to keep track of the current line width

    // Iterate over each word in the 'words' vector
    for (const string& w : words) {
        // Check if adding the length of the current word exceeds the line width
        if (currentLineWidth + w.length() + (currentLineWidth > 0 ? 1 : 0) <= lineWidth) {
            // If not the beginning of the line then add a space
            if (currentLineWidth > 0) {
                cout << " ";
                currentLineWidth++;
            }
            // Print the current word and update the line width
            cout << w;
            currentLineWidth += w.length();
        }
        else {
            // Start a new line then print the current word and update the line width
            cout << endl;
            cout << w;
            currentLineWidth = w.length(); // Update currentLineWidth to include the length of the word
        }
    }
    // Print a newline character to end the last line
    cout << endl;
}

int main() {
    string text = "Short words like a, to, is, and the are used frequently in English.";
    int lineWidth = 10; // Line width
    textWrap(text, lineWidth); // Call the textWrap function
    return 0;
}
