#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class SpellChecker {
private:
    vector<string> dictionary;
    vector<string> misspelledWords; // sửa tên từ 'missspelledWords' thành 'misspelledWords'

public:
    SpellChecker() {};

    // Hàm chuyển chữ hoa thành chữ thường
    static string toLower(string word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        return word;
    }

    // Hàm xóa các ký tự đặc biệt
    static string removePunctuation(string word) { // sửa tên hàm từ 'removePunctiation' thành 'removePunctuation'
        word.erase(remove_if(word.begin(), word.end(), [](char c) {
            return ispunct(c);
        }), word.end());
        return word;
    }

    // Hàm load từ điển từ file
    void Dictionary(string filePath) {
        ifstream dFile(filePath);
        if (!dFile.is_open()) { // kiểm tra xem file có mở được không
            cerr << "Không thể mở file từ điển: " << filePath << endl;
            return;
        }

        string word;
        while (dFile >> word) {
            dictionary.push_back(toLower(word));
        }
    }

    // Hàm kiểm tra lỗi chính tả
    void checkMiss(string filePath) {
        ifstream textFile(filePath);
        if (!textFile.is_open()) { // kiểm tra xem file có mở được không
            cerr << "Không thể mở file văn bản: " << filePath << endl;
            return;
        }

        string line;
        while (getline(textFile, line)) {
            string word;
            istringstream iss(line);
            while (iss >> word) {
                string lowerCaseWord = toLower(word);
                lowerCaseWord = removePunctuation(lowerCaseWord);

                if (find(dictionary.begin(), dictionary.end(), lowerCaseWord) == dictionary.end()) {
                    misspelledWords.push_back(word);
                }
            }
        }
    }

    // In ra lỗi chính tả
    void printMiss() const {
        cout << "Cac tu sai loi chinh ta la : " << endl;
        for (const string& word : misspelledWords) {
            cout << " " << word << endl;
        }
    }

    // Hàm lưu lại các từ sai chính tả (hoặc từ điển tùy theo yêu cầu)
    void saveMisspelledWords(string filePath) const {
        ofstream outputMisspelledFile(filePath);
        if (!outputMisspelledFile.is_open()) {
            cerr << "Khong  the mo file de luu loi chinh ta : " << filePath << endl;
            return;
        }
        for (const string& word : misspelledWords) {
            outputMisspelledFile << word << endl;
        }
    }
};

int main() {
    SpellChecker S;
    cout << "Day la  bai7b" << endl;
    S.Dictionary("dictionary.txt");
    S.checkMiss("input.txt");
    S.printMiss();
    S.saveMisspelledWords("output.txt"); // lưu các từ sai chính tả thay vì từ điển
    return 0;
}
