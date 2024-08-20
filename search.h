
/* 

Project 2 – Search
This program operates as a mini search engine. The user inputs a search term with possible operators and the program reads a file, complies the neccesary tokenized text, and forms an inverted index where the tokens are the keys and sets of compatible URLs are the values. Upon searching, the program displays a count of the number of URLs which contain the search term as well as a list of the URLs.

Written by: Tomasz Kmiotek
U. of Illinois at Chicago (UIC)

The creative component of this project is a function that will remove all stop words given a set of tokens. This is done to decrease the size of the inverted index. In order to use this function, un-comment the function call on line 108 in the "gatherTokens" function.

*/

#pragma once

#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <sstream> 
#include <fstream>

using namespace std;

// **** CREATIVE COMPONENT**** Function to remove all stop words from a set of tokens, takes the set of tokens as a parameter and returns void. Updates the tokens set via pass by reference - un-comment line 109 to use
void removeStop(set<string> &tokens){

  set<string> stopWords = 
  
  {"a","about","above","after","again","against","all","am","an","and","any","are","aren't","as","at","be","because","been","before","being","below","between","both"
  ,"but","by","can't","cannot","could","couldn't","did","didn't","do","does","doesn't","doing","don't","down","during","each","few","for","from","further","had","hadn't"
  ,"has","hasn't","have","haven't","having","he","he'd","he'll","he's","her","here","here's","hers","herself","him","himself","his","how","how's","i","i'd","i'll","i'm"
  ,"i've","if","in","into","is","isn't","it","it's","its","itself","let's","me","more","most","mustn't","my","myself","no","nor","not","of","off","on","once","only","or"
  ,"other","ought","our","ours","ourselves","out","over","own","same","shan't","she","she'd","she'll","she's","should","shouldn't","so","some","such","than","that","that's"
  ,"the","their","theirs","them","themselves","then","there","there's","these","they","they'd","they'll","they're","they've","this","those","through","to","too","under"
  ,"until","up","very","was","wasn't","we","we'd","we'll","we're","we've","were","weren't","what","what's","when","when's","where","where's","which","while","who","who's"
  ,"whom","why","why's","with","won't","would","wouldn't","you","you'd","you'll","you're","you've","your","yours","yourself","yourselves"};

  for( auto i: stopWords){
    
    tokens.erase(i); // get rid of stop words
  
  }   
} // end removeStop

// This function takes a string as a parameter and returns it stripped of all punctuation at the start and end of the string. It works by first checking if the token contains any letters and if we find one, we set the boolean "word" to true. This loop also converts the string to all lower case letters. Next we loop through the token until the first non-punctuation and then erase any punctuation that was found before that.Then  we loop starting from the back of the token until we find any char that is not punctuation and then we erase any punctuation that was found before. Finnaly we return the cleaned token if word is true, and the empty string if word is false (meaning we found no letters)
string cleanToken(string s) {

  bool word = false;

  for(unsigned int i = 0; i != s.size(); i++){ 

    if( isalpha(s[i])){ // check if we have a letter in the token
      word = true;
    }
    s[i] = tolower(s[i]);
  }

  for(unsigned int i = 0; i != s.size(); i++){ 
    
    if( !ispunct(s[i])){
      
      s.erase(0, i); // strips all punctuation from the front of the token
      break;         
    } 
  }  
  
  for(int i = s.size() - 1; i != -1; i--){
  
    if( !ispunct(s[i])){
      
      s.erase(i + 1, s.size()); // strips all punctuation from the back of the token
      break;         
    } 
  }  

  if(word == true) {return s;}
  else {return "";} 
  
} // end cleanToken()
     

// This function takes a string and returns a set of all unique tokens in the string. It works by creating a string stream from the text and then storing each space-seperated string into a temp variable. This temp is then added into the text (which has been cleared) and then we call the cleanToken function to clean the string stored in text. After it is cleaned, as long as it is not a empty string, we insert it into the set "tokens". 
set<string> gatherTokens(string text) {
  
    set<string> tokens;
  
    string cleanText;
    string tempText;
  
    stringstream stream(text);
    text = "";
    
    while (getline(stream, tempText, ' ')) {

      if(tempText != ""){ // check if text is an actual word
        text = tempText; 
        cleanText = cleanToken(text);
      }

      if(cleanText != ""){ // if if the cleaned version is still a real string
        tokens.insert(cleanText);
        text = "";

      } else {continue;}
 
    }   

    //removeStop(tokens); //**** CREATIVE COMPONENT **** - Un-comment this if you wish to remove all stop words in the set of tokens
    return tokens;  
  
} // end gatherTokens()


// This function takes a file and creates an inverted index with the tokenized strings as the keys and sets of urls are the values. Returns the amount of links in the data file. It works by first calling getline once to store the url and then getline again to store the text. Next the text is sent to the gatherTokens function which returns the text as a set of tokenized strings. We then loop through these tokens. If the token is already in the index , we add the current url to the set for that token. If it is not, we create a new key value pair. Finnaly we clear the tokens and urls sets and loop to the next url text pair. 
int buildIndex(string filename, map<string, set<string>>& index) {

  string link,text;
  
  set<string> tokens;
  set<string> urls;
  set<string> newUrls;
  
  int linkCount = 0;

  ifstream infile(filename);

  if(!infile.is_open()) {return 0;} // if file fails to open

  while(getline(infile,link)){

    getline(infile, text); 
    tokens = gatherTokens(text); // return text in the form of tokens from gatherTokens()
    linkCount++;

    urls.insert(link);

    for (auto i : tokens){

      if (index.count(i)){ // check if the token is already a key in our map
      
        newUrls = index[i];
        newUrls.insert(link);

        index[i] = newUrls; // replace the old value with a new set containing additional links to the token
        
      } else {

        index.insert({i, urls}); // if the token is new create a new key value pair
      }    
    }
 
    tokens.clear(); // reset everything for the next url and text 
    urls.clear();      
   } 
  
  return linkCount;
  
} // end buildIndex


// inserter function that looks for matches from user searches to the index and then inserts them into a set, takes the index and a string as parameters, returns a set of matches
set<string> insert(map<string, set<string>> index, string word){

  set<string> result;
      
  for(auto i: index){

    if(i.first == word){

      for(auto k: i.second){

        result.insert(k);  // insert matches 
        
      }
    }    
  }  
  
 return result; 
  
} // end insert()


// This function takes 2 sets and returns their intersection as a new set, takes parameters of 2 sets, a string, and the inverted index, returns a set of intersections
set<string> intersection(set<string> result, set<string> nxtSet, string word, map<string, set<string>> index){

  word = cleanToken(word);
  set<string> inBoth;

  nxtSet = insert(index, word);          

  for( auto i: result){

    for( auto j: nxtSet){

      if( i == j){

        inBoth.insert(i); // if its in both sets, it is part of the intersection
        
      }
    }
  }    

  return inBoth;
  
} // end intersection()


// finds the union of two sets. Takes 2 sets, a search word, and the index as parameters and returns a set of the union of set 1 and set 2
set<string> setUnion(set<string> result, set<string> nxtSet, string word, map<string, set<string>> index){

 set<string> combined;
 word = cleanToken(word);

 nxtSet = insert(index, word);

 for(auto i: result){

   for(auto j: nxtSet){

     result.insert(j);
     result.insert(i); // since it is union, make sure both are in the set
        
   }
 }

 combined = result;
 return combined;
   
} //end setUnion()


// finds the differnce of two sets. Takes 2 sets, a search word, and the index as parameters and returns a set of all urls which are in set 1 but not set 2
set <string> setDifference(set<string> result, set<string> nxtSet, string word, map<string, set<string>> index){

  set<string> notIn = result;
  word = cleanToken(word);
  
  nxtSet = insert(index, word);

  for( auto i: result){

    for( auto j: nxtSet){

      if( i == j){

        notIn.erase(i); // if it is in both, it is not part of the intersection

        }
      }
    }
  return notIn;
  
} // end setDifference()


// This function takes a user query and returns a set containing all the urls that match the users query. This works by first checking if there is more than one word in the user query. If there is only one, we simply find all matches to the url. If there is more than one, we enter a while loop with a string stream to parse the user input. Depending on what the user inputs, we call functions that perform different set operations on the sets of urls that are being collected. The set "result" is updated evertime we call a function and then when the string stream runs out we return this final updated set.
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
  
  set<string> result;
  set<string> nxtSet;
  
  bool oneWord = true;
  string word;

  for(int i = 0 ; i != sentence.size(); i++){ 

   if(isspace(sentence[i])){ // check if it one word or multiple

    oneWord = false;
      
    }
  }

  if(oneWord == true){ // If it is a one word input, we dont have to worry about operators

    word = cleanToken(sentence);

    result = insert(index, word);
           
  }
    
  else{

    stringstream s(sentence);

    getline(s,word, ' ');
    word = cleanToken(word);
    result = insert(index, word); // gathers the tokens of the first word for comparison to further words

    while(getline(s, word, ' ')){
      
      if(word[0] == '+'){
        
        result = intersection(result, nxtSet, word, index); 
        
      }
      else if (word[0] == '-'){

        result = setDifference(result, nxtSet, word, index);
   
      }
      else {

        result = setUnion(result, nxtSet, word, index);
        
      }     
    }
  }
  
  return result; 
} // end findQueryMatches()


// This function is what controls the actual calling of functions and takes user input. The way it works is it calls the buildIndex function to build the inveted index, then it proceeds to enter a while loop to get user input (the search terms). Upon receiving a search term, the function sends this query to the findQueryMatches function for proccesing and then displays the number of URLs found as well as the URLs themselves.
void searchEngine(string filename) {

  int indexNum = 0;
  string query;
  set<string> result;
  map<string, set<string>> index;

  indexNum = buildIndex(filename, index);

  if(indexNum != 0){ // Make sure the index was built

    cout << "Stand by while building index..." << endl;
    cout << "Indexed " << indexNum << " pages containing " << index.size() << " unique terms" << endl;

    while(query != " "){ // Loop to keep asking user for input
      
      cout << endl << "Enter query sentence (press enter to quit): ";

      getline(cin, query);

      if(query == ""){
        cout << "Thank you for searching!";
        return;
      }

      else{

        result = findQueryMatches(index, query); // Get all matches

        cout << "Found " <<  result.size() << " matching pages" << endl;

        for( auto i: result){

          cout << i << endl; // print all URls
          
        }
      }    
    }
  }
  else {cout << "Invalid Filename";} 
} // end searchEngine