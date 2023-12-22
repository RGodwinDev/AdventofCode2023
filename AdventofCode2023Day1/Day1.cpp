#include "./headers/Day1.h"

int Day1::checkWordNumber(std::string &text, int i) {
    std::string sub = "";
    if (text[i] == 'o') {                               //one
        try { sub =     text.substr(i, 3); }
        catch (std::exception e) {}                     //trycatch should only trigger if substring goes out of bounds.
        if (sub == "one") { return 1; }
    }
    else if (text[i] == 't') {                          //two or three
        try { sub =     text.substr(i, 3); }
        catch (std::exception e) {}
        if (sub == "two") { return 2; }
        try { sub =     text.substr(i, 5); }
        catch (std::exception e) {}
        if (sub == "three") { return 3; }
    }
    else if (text[i] == 'f') {                          // four or five
        try { sub =     text.substr(i, 4); }
        catch (std::exception e) {}
        if (sub == "four") { return 4; }
        try { sub =     text.substr(i, 4); }
        catch (std::exception e) {}
        if (sub == "five") { return 5; }
    }
    else if (text[i] == 's') {                          // six or seven
        try { sub =     text.substr(i, 3); }
        catch (std::exception e) {}
        if (sub == "six") { return 6; }
        try { sub =     text.substr(i, 5); }
        catch (std::exception e) {}
        if (sub == "seven") { return 7; }
    }
    else if (text[i] == 'e') {                          // eight
        try { sub =     text.substr(i, 5); }
        catch (std::exception e) {}
        if (sub == "eight") { return 8; }
    }
    else if (text[i] == 'n') {                          // nine
        try { sub =     text.substr(i, 4); }
        catch (std::exception e) {}
        if (sub == "nine") { return 9; }
    }
    return 0;
}


int Day1::day() {

    std::string text;
    std::ifstream file("./inputs/day1input.txt");
    int lines = 0;
    
    std::vector<std::string> wordNumbers;

    while (getline(file, text)) {
        lines++;
        wordNumbers.push_back(text);
    }


    int sum1 = 0, sum2 = 0;
    for(std::string wordNumber : wordNumbers){
        bool numWordFound =         false;
        int wordSum1 =              0;
        int wordSum2 =              0;
        
        //get the front number
        for (int i = 0; i < wordNumber.size(); ++i) {
            if (isdigit(wordNumber[i])) {
                wordSum1 =          atoi(&wordNumber[i]);               //atoi grabs a whole number in a string from i->end of number,
                while (wordSum1 >= 10) { wordSum1 /= 10; }              //such as "12345bca" -> 12345, rather than just 1.
                wordSum1 =          wordSum1 * 10;                      //but its fine working backwards, you'll get just 5.

                if (!numWordFound) { 
                    wordSum2 =      wordSum1; 
                }
                break;
            }
            else if(!numWordFound) {
                int x = checkWordNumber(wordNumber, i);
                if (x) { 
                    numWordFound =  true;  
                    wordSum2 =      x * 10; 
                }
            }
        }
       
        //get the back number
        numWordFound = false;
        for (int i = wordNumber.size() - 1; i >= 0; --i) {
            if (isdigit(wordNumber[i])) {
                int c =             atoi(&wordNumber[i]);
                wordSum1 +=         c;
                if(!numWordFound){ 
                    wordSum2 +=     c;
                }
                break;
            }
            else if(!numWordFound){
                int x =             checkWordNumber(wordNumber, i);
                if (x) { 
                    numWordFound =  true;  
                    wordSum2 +=     x; 
                }
            }
        }
        sum1 +=                     wordSum1;
        sum2 +=                     wordSum2;
    }

    std::cout << "Day 1:\t" << sum1 << "\tand " << sum2 << std::endl;
    return lines;
}