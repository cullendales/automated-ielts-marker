#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <unordered_set>
#include <utility>
#include <cctype>

using namespace std;

int structure(const string& essay){

    stringstream ss(essay);
    string line;
    int paraCount = 0;
    bool para = false;

    while (getline(ss, line)) {
        bool isEmpty = true;
        for (char c : line) {
            if (!isspace(c)) {
                isEmpty = false;
                break;
            }
        }    
        if (!isEmpty) {
            if (!para) {
                paraCount++;
                para = true;
            }
        } 
        else { para = false; }
    }

    if (paraCount < 4){ cout << "You only wrote " << paraCount << " paragraphs. This is not enough to obtain a high IELTS score. Please ensure you write 4 in the future." << endl; }
    else if (paraCount == 4) { cout << "Great paragraph structure. 4 paragraphs is perfect. Great job!" << endl; }
    else { cout << "You wrote " << paraCount << " paragraphs. Please only write 4 paragraphs in the future." << endl; }

    return paraCount;
}

int wordChoice(const vector<string>& essay){

    int count = 0;

    map<string, vector<string>> simpleWords = {
        {"bad", {"poor", "subpar", "unacceptable", "inferior"}},
        {"good", {"excellent", "outstanding", "superb", "remarkable"}},
        {"happy", {"joyful", "content", "delighted", "cheerful"}},
        {"sad", {"unhappy", "sorrowful", "mournful", "dejected"}},
        {"big", {"large", "huge", "immense", "massive"}},
        {"small", {"tiny", "minuscule", "petite", "compact"}},
        {"smart", {"intelligent", "clever", "brilliant", "wise"}},
        {"dumb", {"foolish", "unwise", "ignorant", "obtuse"}},
        {"nice", {"pleasant", "agreeable", "friendly", "kind"}},
        {"mean", {"cruel", "unkind", "harsh", "malicious"}},
        {"pretty", {"beautiful", "gorgeous", "stunning", "lovely"}},
        {"ugly", {"unattractive", "unsightly", "hideous", "unpleasant"}},
        {"fast", {"quick", "speedy", "swift", "rapid"}},
        {"slow", {"sluggish", "lethargic", "unhurried", "delayed"}},
        {"easy", {"simple", "effortless", "straightforward", "uncomplicated"}},
        {"hard", {"difficult", "challenging", "tough", "demanding"}},
        {"rich", {"wealthy", "affluent", "prosperous", "well-off"}},
        {"poor", {"impoverished", "destitute", "underprivileged", "needy"}},
        {"fun", {"enjoyable", "entertaining", "amusing", "delightful"}},
        {"boring", {"dull", "tedious", "monotonous", "uninteresting"}},
        {"strong", {"powerful", "robust", "mighty", "sturdy"}},
        {"weak", {"frail", "feeble", "fragile", "delicate"}},
        {"tired", {"exhausted", "weary", "fatigued", "drained"}},
        {"angry", {"furious", "irate", "incensed", "livid"}},
        {"scared", {"afraid", "frightened", "terrified", "alarmed"}},
        {"surprised", {"astonished", "amazed", "shocked", "astounded"}},
        {"interesting", {"fascinating", "captivating", "intriguing", "engaging"}},
        {"hardworking", {"diligent", "industrious", "dedicated", "assiduous"}}
    };

    map<string, vector<string>> veryWords = {
        {"bad", {"terrible", "awful", "dreadful", "horrendous"}},
        {"good", {"excellent", "superb", "outstanding", "remarkable"}},
        {"happy", {"ecstatic", "joyful", "elated", "thrilled"}},
        {"sad", {"heartbroken", "miserable", "sorrowful", "devastated"}},
        {"big", {"huge", "immense", "massive", "enormous"}},
        {"small", {"tiny", "minuscule", "microscopic", "petite"}},
        {"smart", {"brilliant", "genius", "intelligent", "sharp"}},
        {"dumb", {"foolish", "ignorant", "mindless", "dim-witted"}},
        {"nice", {"charming", "pleasant", "gracious", "delightful"}},
        {"mean", {"cruel", "malicious", "vindictive", "vicious"}},
        {"pretty", {"gorgeous", "stunning", "beautiful", "radiant"}},
        {"ugly", {"hideous", "unsightly", "repulsive", "grotesque"}},
        {"fast", {"rapid", "swift", "quick", "speedy"}},
        {"slow", {"sluggish", "lethargic", "plodding", "delayed"}},
        {"easy", {"effortless", "simple", "painless", "straightforward"}},
        {"hard", {"challenging", "arduous", "demanding", "formidable"}},
        {"rich", {"wealthy", "affluent", "prosperous", "well-off"}},
        {"poor", {"destitute", "impoverished", "needy", "penniless"}},
        {"fun", {"exciting", "enjoyable", "amusing", "delightful"}},
        {"boring", {"tedious", "monotonous", "dreary", "mind-numbing"}},
        {"strong", {"powerful", "formidable", "sturdy", "robust"}},
        {"weak", {"fragile", "frail", "feeble", "delicate"}},
        {"tired", {"exhausted", "weary", "fatigued", "drained"}},
        {"angry", {"furious", "irate", "incensed", "livid"}},
        {"scared", {"terrified", "petrified", "alarmed", "fearful"}},
        {"surprised", {"astonished", "astounded", "amazed", "shocked"}},
        {"interesting", {"fascinating", "captivating", "intriguing", "engrossing"}},
        {"hardworking", {"diligent", "industrious", "dedicated", "assiduous"}},
        {"clean", {"spotless", "immaculate", "pristine", "untarnished"}},
        {"dirty", {"filthy", "grimy", "squalid", "unclean"}}
    };

    for (auto it = begin(essay); it != end(essay); ++it){
        if (*it == "very"){
            ++it;
            if (veryWords.find(*it) != veryWords.end()){
                count++;
                cout << "You used the word: \"Very " << *it << "\" - some better choices are: ";
                for (const string& syn : veryWords[*it]){
                    cout << syn << ", ";
                }
                cout << endl;
            }
            else --it;
        }
        else if (simpleWords.find(*it) != simpleWords.end()){
            count++;
            cout << "You used the word \"" << *it << "\" - some better choices are: ";
            for (const string& syn : simpleWords[*it]){
                cout << syn << ", ";
            }
            cout << endl;
        }
    }
    return count;
}

float thingsDoneWell(const unordered_set<string>& essaySet){

    fstream file;
    string word, filename;
    vector<string> conjunctions;
    vector<string> goodVocab;
    float goodWordCount = 0;

    filename = "conjunctions.txt";
    file.open(filename.c_str());

    if (!file.is_open()){
        cerr << "There was a failure opening conjunctions.txt. Please include download this file if not downloaded already" << endl;
        return -1;
    }

    while(file >> word){
        conjunctions.push_back(word);
    }
    file.close();

    unordered_set<string> conjunctionsSet(conjunctions.begin(), conjunctions.end());

    filename = "good_vocab.txt";
    file.open(filename.c_str());

    if (!file.is_open()){
        cerr << "There was a failure opening good_vocab.txt. Please include download this file if not downloaded already" << endl;
        return -1;
    }

    while (file >> word){
        goodVocab.push_back(word);
    }
    file.close();

    unordered_set<string> goodVocabSet(goodVocab.begin(), goodVocab.end());

    for (auto it = begin(essaySet); it != end(essaySet); ++it){
        if (conjunctionsSet.find(*it) != conjunctionsSet.end()){
            goodWordCount += 1.5;
        }
        if (goodVocabSet.find(*it) != goodVocabSet.end()){
            goodWordCount += 1;
        }
    }

    return goodWordCount;
}

int spellCheck(const unordered_set<string>& essaySet){

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
    file.close();

    unordered_set<string> dictionarySet(dictionary.begin(), dictionary.end());

    for (auto it = begin(essaySet); it != end(essaySet); ++it){
        if (dictionarySet.find(*it) == dictionarySet.end()){        
            numMispelled++;
            cout << "The word " << *it << " is likely mispelled." << endl;
        }
    }

    return numMispelled;
}

int wordOveruse(vector<string> essay, map<string, int> wordCount){

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

int wordCount(const vector<string>& essay){

    int count = 0;

    for (auto it = begin(essay); it != end(essay); ++it){
        count++;
    }

    return count;
}

int ieltsScore(int numWordsValue, int numMisspelled, int overuseScore, int structureScore, int goodNum, int scoreWc){

    float score = 0;

    if (numWordsValue < 4){
        score = 5;
        cout << "Please write more in the future. You must write a minimum of 250 words." << endl;
    }
    else if (numWordsValue == 4){
        score = 6;
        cout << "You almost wrote enough. Please write more in the future. You must write a minimum of 250 words." << endl;
    }
    else if (numWordsValue == 6){
        score = 6.75;
    }
    else { 
        score = 6.5; 
        cout << "You wrote too much. More is not better. Please try to write only 250 - 300 words in the future." << endl;
    }

    if (numMisspelled >= 2 && numMisspelled <= 3){ score -= 0.25; }

    else if (numMisspelled > 3 && numMisspelled < 6){
        score -= 0.5;
        cout << "You made " << numMisspelled << "spelling mistakes. Please check your spelling more carefully after finishing your essay." << endl;
    }
    else if (numMisspelled > 6){
        score -= 1;
        cout << "You made " << numMisspelled << "spelling mistakes. Please check your spelling more carefully after finishing your essay." << endl;
    }

    if (overuseScore == 2){
        score -= 0.25;
    }
    else if (overuseScore >= 3 && overuseScore <= 4){
        score -= 0.5;
    }
    else if (overuseScore > 4){
        score -= 0.75;
    }

    if (structureScore < 4){
        score -= 1;
    }
    else if (structureScore > 4){
        score -= 0.75;
    }

    if (goodNum >= 5 && goodNum <= 6){
        score += 0.25;
    }
    else if (goodNum > 6 or goodNum <= 7){
        score += 0.5;
    }
    else if (goodNum > 7) {
        score += 0.75;
    }

    if (scoreWc < 2){
        score += 0.25;
    }
    else if (scoreWc > 6){
        score -= 0.25;
        cout << "You reused many simple words in your essay. Please try to use more advanced vocabulary in your essay for a higher score." << endl;
    }

    return score;
}

pair<vector<string>, int> cleanWords(const string& essay){

    stringstream ss(essay);
    string word;
    vector<string> words;

    int paraCount = structure(essay);

    while(ss >> word){
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        int len = word.size();
        for (int i = 0; i < len; i++){
            if (ispunct(word[i])){
                word.erase(i--, 1);
                len = word.size();
            }
        } 
        words.push_back(word);
    }

    return {words, paraCount};
}

int main () {

    fstream file;
    string filename, essay, line;

    cout << "Please input the name of your txt file for marking (ie. ielts.txt): ";
    cin >> filename;
    cout << endl;

    file.open(filename.c_str());

    if (!file.is_open()){
        cout << "There was an error opening your file: " << filename << endl;
        return 1;
    }

    while (getline(file, line)){
        essay += line + "\n";
    }

    auto cleanRes = cleanWords(essay);
    vector<string> essayCleaned = cleanRes.first;
    int paraCount = cleanRes.second;

    unordered_set<string> essaySet(essayCleaned.begin(), essayCleaned.end());

    map<string, int> wordCounter;

    for (const auto& word : essayCleaned){
        wordCounter[word]++;
    }

    int numWords = wordCount(essayCleaned);
    cout << "num words: " << numWords << endl;

    int count = wordOveruse(essayCleaned, wordCounter);
    cout << count << endl;

    int countSpelling = spellCheck(essaySet);
    cout << "Num spelling mistakes: " << countSpelling << endl;

    float countWell = thingsDoneWell(essaySet);
    cout << "Num done well = " << countWell << endl;

    int badCount = wordChoice(essayCleaned);
    cout << "num bad: " << badCount << endl;

    return 0;
}