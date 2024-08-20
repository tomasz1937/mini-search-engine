/* 

This program operates as a mini search engine. The user inputs a search term with possible operators and the program reads a file, complies the neccesary tokenized text, and forms a   inverted index where the tokens are the keys and sets of compatible URLs are the values. Upon searching, the program displays a count of the number of URLs which contain the search     term as well as a list of the URLs.

Written by: Tomasz Kmiotek

*/

#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <sstream> 
#include <fstream>
#include "search.h"

using namespace std;

int main() {

  // Tests for milestone 1 - testing to make sure punctuation is correctly removed
  /*
  cout << cleanToken("this.....");
  cout << cleanToken(",,,,th666is.....");
  cout << cleanToken("..t}h{is...");
  cout << cleanToken("(((((this****");
  cout << cleanToken(",,,t,,h...i...s.");
  cout << cleanToken("this");
  cout << cleanToken("((((t))))his.");
  cout << cleanToken("OK.this..");
  */

  // Tests for milestone 2 - testing to see if the function returns a set of properly cleaned tokens
  /*
  set<string> test;
  test = gatherTokens("..This is the string I am g..oing to test. There is repeats as well, stri]]ngs, string,,");

  for( auto i: test){
    cout << i << endl;
  }

  set<string> test2;
  test = gatherTokens("Another string string , that will be TESTED. tested it will... be");

  for( auto i: test2){
    cout << i << endl;
  }
  */

  // Tests for milestone 3 - testing to see if the inverted index has been built properly
  /*
  map<string, set<string>> indexTest;
  buildIndex("tiny.txt", indexTest);

  for( auto i: indexTest){
    cout << i.first << " ";

    for( auto j: i.second){
      cout << j << ", ";
    }
    cout << endl;
  }

  buildIndex("cplusplus.txt", indexTest);

  for( auto i: indexTest){
    cout << i.first << " ";

    for( auto j: i.second){
      cout << j << ", ";
    }
    cout << endl;
  }
  */

  // Tests for milestone 4 - testing if a search of the index will return the proper URLs
  /*
  map<string, set<string>> indexTest;
  buildIndex("tiny.txt", indexTest);
  set<string>resultTest;

  resultTest = findQueryMatches(indexTest, "red");

  for( auto i: resultTest){
    cout << i << endl;
  }
  resultTest = findQueryMatches(indexTest, "red +green");

  for( auto i: resultTest){
    cout << i << endl;
  }
  resultTest = findQueryMatches(indexTest, "red +green -blue");

  for( auto i: resultTest){
    cout << i << endl;
  }
  resultTest = findQueryMatches(indexTest, "-blue");

  for( auto i: resultTest){
    cout << i << endl;
  }
  resultTest = findQueryMatches(indexTest, "-blue +green");

  for( auto i: resultTest){
    cout << i << endl;
  }
  */

  // Tests for milstone 5 - testing if the proper messages appear 
  /*
  searchEngine("invalid.txt"); // should output "Invalid Filename"
  searchEngine("cplusplus.txt"); // user inputs "enter" see if the program ends or not, also testing to see if proper exit messages appears
  */
  
  searchEngine("stackoverflow.txt");

  return 0;
}