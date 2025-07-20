#include <iostream>
#include <chrono>
#include <vector>

using namespace std;

void delay(int milliseconds) {
    auto start = chrono::high_resolution_clock::now();
    while (true) {
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        if (duration >= milliseconds / 4) // Decreased delay time by 1/4th
            break;
    }
}

void showProgressBar() {
    const int barWidth = 24; // Decreased bar width by 40%
    const string loadingText = "Loading...";
    const vector<char> symbols = { '|', '/', '-', '\\' }; // Different symbols

    int symbolIndex = 0; // Index for accessing symbols vector
    system("CLS");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    for (int i = 0; i <= barWidth; ++i) {
        cout << "\r";
        cout << string(47, ' '); // Print 40 spaces before loading text
        cout << loadingText << " [";
        for (int j = 0; j < barWidth; ++j) {
            if (j < i) {
                cout << "=";
            } else if (j == i) {
                cout << symbols[symbolIndex++ % symbols.size()]; // Change symbol
            } else {
                cout << " ";
            }
        }
        cout << "] " << (i * 100) / barWidth << "%";
        cout.flush();
        delay(350); // Decreased delay time by 1/4th
    }
    cout << endl;
}

int main() {
    showProgressBar();
    return 0;
}
