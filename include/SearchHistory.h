#ifndef SEARCH_HISTORY_H
#define SEARCH_HISTORY_H

#include "DataStructures/LinkedList.h"
#include <string>

using namespace std;

// Stores a single search record
class SearchRecord {
public:
  string keyword;
  int count; // how many times this keyword was searched

  SearchRecord(const string &k);
};

// Tracks all search history and analytics
class SearchHistory {
private:
  LinkedList records; // stores SearchRecord*
  int totalSearches;

public:
  SearchHistory();
  void addSearch(const string &keyword);           // add or increment count
  void displayHistory();                           // show all searches
  void displayTopSearches(int n);                  // show top N most searched
  int getTotalSearches();                          // total search count
  string getTopSearchTerm();                       // get most searched keyword
  SearchRecord *findRecord(const string &keyword); // find existing record
};

#endif
