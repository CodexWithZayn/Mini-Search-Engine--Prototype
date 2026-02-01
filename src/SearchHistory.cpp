#include "SearchHistory.h"
#include "UI.h"
#include <iostream>

using namespace std;

SearchRecord::SearchRecord(const string &k) : keyword(k), count(1) {}

SearchHistory::SearchHistory() : totalSearches(0) {}

SearchRecord *SearchHistory::findRecord(const string &keyword) {
  Node *cur = records.head;
  while (cur) {
    SearchRecord *rec = (SearchRecord *)cur->data;
    if (rec->keyword == keyword) {
      return rec;
    }
    cur = cur->next;
  }
  return nullptr;
}

void SearchHistory::addSearch(const string &keyword) {
  totalSearches++;

  // Check if keyword already exists
  SearchRecord *existing = findRecord(keyword);
  if (existing) {
    existing->count++;
  } else {
    // Add new record
    SearchRecord *newRec = new SearchRecord(keyword);
    records.addNode(newRec);
  }
}

void SearchHistory::displayHistory() {
  UI::printHeader();
  cout << "\n"
       << BOLD << YELLOW << "   SEARCH HISTORY (Total: " << totalSearches << ")"
       << RESET << "\n";
  UI::printSeparator(CYAN);

  Node *cur = records.head;
  if (!cur) {
    cout << "No searches yet.\n";
    return;
  }

  while (cur) {
    SearchRecord *rec = (SearchRecord *)cur->data;
    cout << "  " << CYAN << "\"" << rec->keyword << "\"" << RESET
         << " - searched " << GREEN << rec->count << RESET << " time(s)\n";
    cur = cur->next;
  }
  UI::printSeparator(CYAN);
}

void SearchHistory::displayTopSearches(int n) {
  cout << "\n"
       << BOLD << YELLOW << "   TOP " << n << " SEARCHES" << RESET << "\n";
  UI::printSeparator(CYAN);

  if (!records.head) {
    cout << "No searches yet.\n";
    return;
  }

  // Copy records to array for sorting
  int size = records.size;
  SearchRecord **arr = new SearchRecord *[size];

  Node *cur = records.head;
  int i = 0;
  while (cur) {
    arr[i++] = (SearchRecord *)cur->data;
    cur = cur->next;
  }

  // Bubble sort by count (descending)
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (arr[j]->count < arr[j + 1]->count) {
        SearchRecord *temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }

  // Display top n
  int limit = (n < size) ? n : size;
  for (int i = 0; i < limit; i++) {
    cout << "  " << YELLOW << (i + 1) << ". " << RESET << "\""
         << arr[i]->keyword << "\" - " << GREEN << arr[i]->count << RESET
         << " time(s)\n";
  }

  delete[] arr;
  UI::printSeparator(CYAN);
}

int SearchHistory::getTotalSearches() { return totalSearches; }

string SearchHistory::getTopSearchTerm() {
  if (!records.head)
    return "";

  Node *cur = records.head;
  SearchRecord *maxRec = (SearchRecord *)cur->data;

  while (cur) {
    SearchRecord *rec = (SearchRecord *)cur->data;
    if (rec->count > maxRec->count) {
      maxRec = rec;
    }
    cur = cur->next;
  }
  return maxRec->keyword;
}
