#include "./headers/Day1.h"

int Day1::checkWordNumber(std::string &text, int i) {
    std::string sub = "";
    if (text[i] == 'o') { //one
        try { sub = text.substr(i, 3); }
        catch (std::exception e) {} //trycatch should only trigger if substring goes out of bounds.
        if (sub == "one") { return 1; }
    }
    else if (text[i] == 't') { //two or three
        try { sub = text.substr(i, 3); }
        catch (std::exception e) {}
        if (sub == "two") { return 2; }
        try { sub = text.substr(i, 5); }
        catch (std::exception e) {}
        if (sub == "three") { return 3; }
    }
    else if (text[i] == 'f') { // four or five
        try { sub = text.substr(i, 4); }
        catch (std::exception e) {}
        if (sub == "four") { return 4; }
        try { sub = text.substr(i, 4); }
        catch (std::exception e) {}
        if (sub == "five") { return 5; }
    }
    else if (text[i] == 's') { // six or seven
        try { sub = text.substr(i, 3); }
        catch (std::exception e) {}
        if (sub == "six") { return 6; }
        try { sub = text.substr(i, 5); }
        catch (std::exception e) {}
        if (sub == "seven") { return 7; }
    }
    else if (text[i] == 'e') { // eight
        try { sub = text.substr(i, 5); }
        catch (std::exception e) {}
        if (sub == "eight") { return 8; }
    }
    else if (text[i] == 'n') { // nine
        try { sub = text.substr(i, 4); }
        catch (std::exception e) {}
        if (sub == "nine") { return 9; }
    }
    return 0;
}


int Day1::day() {

    std::string text;
    std::fstream file("./inputs/day1input.txt");
    int lines = 0;

    int sum1 = 0;
    int sum2 = 0;
    while (getline(file, text)) {
        lines++;

        int tempsum1 = 0;
        int tempsum2 = 0;

        //sum1 cant use words for numbers but sum2 can.
        bool worded = false;

        for (int i = 0; i < text.size(); ++i) {
            if (isdigit(text[i])) {
                tempsum1 = atoi(&text[i]);                 //atoi grabs a whole number in a string from i->end of number,
                while (tempsum1 >= 10) { tempsum1 /= 10; }        //such as "12345bca" -> 12345, rather than just 1.
                tempsum1 *= 10;                            //but its fine working backwards, you'll get just 5.
                if (!worded) { tempsum2 = tempsum1; }
                break;
            }
            else if(!worded) { //check if its a wordnumber
                int x = checkWordNumber(text, i);
                if (x) { worded = true;  tempsum2 = x * 10; }
            }
        }

        worded = false;
        //now work backwards to get second number.
        for (int i = text.size() - 1; i >= 0; --i) {
            if (isdigit(text[i])) { 
                int c = atoi(&text[i]);
                tempsum1 += c;
                if(!worded){ tempsum2 += c; }
                break;
            }
            else if(!worded){ //check if its a wordnumber
                int x = checkWordNumber(text, i);
                if (x) { worded = true;  tempsum2 += x; }
            }
        }
        sum1 += tempsum1;
        sum2 += tempsum2;
    }



    std::cout << "Day 1:\t" << sum1 << "\tand " << sum2 << std::endl;
    return lines;
};


