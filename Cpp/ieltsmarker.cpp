#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <unordered_set>

using namespace std;

// int structure(vector<string> essay){

// }

// int wordChoice(vector<string> essay){

// }

// int thingsDoneWell(vector<string> essay){

// }


int spellCheck(unordered_set<string> essaySet){

    fstream file;
    string word, filename;
    vector<string> dictionary;
    int numMispelled = 0;

    filename = "dictionary.txt";
    file.open(filename.c_str());

    if (!file.is_open()){
        cerr << "There was a failure opening dictionary.txt. Please include download this file if not downloaded already" << endl;
        return -1;
    }

    while (file >> word){
        dictionary.push_back(word);
    }

    unordered_set<string> dictionarySet(dictionary.begin(), dictionary.end());

    for (auto it = begin(essaySet); it != end(essaySet); ++it){
        if (dictionarySet.find(*it) == dictionarySet.end()){
            numMispelled++;
            cout << "The word " << *it << " is likely mispelled." << endl;
        }
    }

    return numMispelled;
}

int wordOveruse(vector<string> essay){

    int count = 0;
    vector<string> commonWords;

    fstream cwFile;
    string word, filename;

    filename = "common_words.txt";
    cwFile.open(filename.c_str());

    if (!cwFile.is_open()){
        cerr << "There was a failure opening common_words.txt. Please include download this file if not downloaded already" << endl;
        return -1;
    }

    while (cwFile >> word){
        commonWords.push_back(word);
    }  
    cwFile.close();

    map<string, int> wordCount;

    for (const auto& word : essay){
        wordCount[word]++;
    }

    unordered_set<string> commonWordsSet(commonWords.begin(), commonWords.end());

    for (auto it = begin(wordCount); it != end(wordCount);){
        if (commonWordsSet.find(it->first) != commonWordsSet.end()){
            it = wordCount.erase(it);
        }
        else{
            ++it;
        }
    }

    for (auto it = begin(wordCount); it != end(wordCount); ++it){
        if (it->second >= 4){
            cout << "The word " << it->first << " was used " << it->second << " times." << endl;
            count++; 
        }
    }

    return count;
}

int wordCount(vector<string> essay){

    int count = 0;

    for (auto it = begin(essay); it != end(essay); ++it){
        count++;
    }

    return count;
}

// int ieltsScore(int structMark, int choiceMark, int tdwMark, int spellMark, int overuseMark, int countMark){

// }


vector<string> cleanWords(string essay){

    stringstream ss(essay);
    string word;
    vector<string> words;

    while(ss >> word){
        words.push_back(word);
    }

    return words;
}

int main () {

    cout << "Please input you IELTS writing: " << endl;
    string essay;
    getline(cin, essay);
    cout << "Thank you :) Marking now..." << endl;

    vector<string> essayCleaned = cleanWords(essay);
    unordered_set<string> essaySet(essayCleaned.begin(), essayCleaned.end());

    //cout << "you entered: " << essayCleaned[2] << endl;
    int count = wordOveruse(essayCleaned);
    cout << count << endl;

    int countSpelling = spellCheck(essaySet);
    cout << "Num spelling mistakes: " << countSpelling << endl;

    return 0;
}