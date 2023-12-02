using namespace std;
#include<fstream>
#include<string>
#include<iostream>
#include "./headers/Day1.h"

int Day1::checkWordNumber(string text, int i) {
    if (text[i] == 'o') { //one
        string sub;
        try { sub = text.substr(i, 3); }
        catch (exception e) {} //trycatch should only trigger if substring goes out of bounds.
        if (sub == "one") { return 1; }
    }
    else if (text[i] == 't') { //two or three
        string sub;
        try { sub = text.substr(i, 3); }
        catch (exception e) {}
        if (sub == "two") { return 2; }
        try { sub = text.substr(i, 5); }
        catch (exception e) {}
        if (sub == "three") { return 3; }
    }
    else if (text[i] == 'f') { // four or five
        string sub;
        try { sub = text.substr(i, 4); }
        catch (exception e) {}
        if (sub == "four") { return 4; }
        try { sub = text.substr(i, 4); }
        catch (exception e) {}
        if (sub == "five") { return 5; }
    }
    else if (text[i] == 's') { // six or seven
        string sub;
        try { sub = text.substr(i, 3); }
        catch (exception e) {}
        if (sub == "six") { return 6; }
        try { sub = text.substr(i, 5); }
        catch (exception e) {}
        if (sub == "seven") { return 7; }
    }
    else if (text[i] == 'e') { // eight
        string sub;
        try { sub = text.substr(i, 5); }
        catch (exception e) {}
        if (sub == "eight") { return 8; }
    }
    else if (text[i] == 'n') { // nine
        string sub;
        try { sub = text.substr(i, 4); }
        catch (exception e) {}
        if (sub == "nine") { return 9; }
    }
    return 0;
}


int Day1::v() {
    string text;
    fstream file("./inputs/day1input.txt");
    int sum1 = 0;
    while (getline(file, text)) { //gets a line from the file and puts it into text.
        int a = 0;
        for (char c : text) {
            if (isdigit(c)) {
                a = atoi(&c) * 10; //wonder why isdigit is happy with just c but atoi needs &c
                break;
            }
        }
        //then do search again backwards
        for (int i = text.size() - 1; i >= 0; --i) {
            if (isdigit(text[i])) {
                a += atoi(&text[i]);
                break;
            }
        }
        sum1 += a;
    }

    //now do it again, but this time, words that are numbers count. ex) "one" == 1.
    //one two three four five six seven eight nine
    int sum2 = 0;

    file.clear();   //resets the file flags
    file.seekg(0);  //sets place in file back to beginning
    int lines = 0;
    while (getline(file, text)) {
        lines++;
        int a = 0;
        for (int i = 0; i < text.size(); ++i) {
            if (isdigit(text[i])) {
                a = atoi(&text[i]); //atoi grabs a whole number in a string from i->end of number,
                //such as "12345bca" -> 12345, rather than just 1.
                //but its fine working backwards, you'll get just 5.
                while (a >= 10) {
                    a /= 10;
                }
                a *= 10;
                break;
            }
            else { //check if its a wordnumber
                int x = checkWordNumber(text, i);
                if (x != 0) { //didnt come back with 0
                    a = x * 10; break;
                }
            }
        }
        //now work backwards to get second number.
        for (int i = text.size() - 1; i >= 0; --i) {
            if (isdigit(text[i])) {
                a += atoi(&text[i]); break;
            }
            else { //check if its a wordnumber
                int x = checkWordNumber(text, i);
                if (x) { //didnt come back with 0
                    a += x; break;
                }
            }
        }
        sum2 += a;
    }
    std::cout << "Day 1: " << sum1 << " and " << sum2 << endl;
    return lines;
};


