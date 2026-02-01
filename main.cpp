#include "include/DataStructures/Array.h"
#include "include/InputValidation.h"
#include "include/SearchEngine.h"
#include "include/UI.h"
#include <cstdlib> // For system()
#include <iostream>

using namespace std;
using namespace InputValidation;

int main() {
#ifdef _WIN32
  system("title Mini Search Engine Pro");
  system("mode con: cols=120 lines=40");
#endif

  UI::printWelcome();

  SearchEngine engine;

  Array dummyDocs(5);

  dummyDocs.push_back(
      {"System Architecture",
       "This engine uses a Hybrid Data Structure approach: Arrays for storage, "
       "Linked Lists for indexing, and BSTs for analytics. Each component is "
       "modular specifically designed to optimize different aspects of search: "
       "Indexing (speed), Storage (access), and Ranking (relevance)."});

  dummyDocs.push_back(
      {"Custom Array Implementation",
       "To ensure complete control over memory and performance, we implemented "
       "a manual 'Array' class. This class manages raw "
       "pointers "
       "and dynamic memory allocation (new/delete) to store data. It supports "
       "generic types "
       "Resize operations happen automatically when capacity is reached "
       "(doubling strategy), "
       "ensuring amortized O(1) insertion time. We use this to buffer initial "
       "documents."});

  dummyDocs.push_back({"LinkedList Indexing",
                       "The Inverted Index is the core of the search engine, "
                       "mapping words to documents. "
                       "We use a Singly Linked List for this purpose. Each "
                       "node in the list represents "
                       "a unique word found in the corpus. Attached to each "
                       "word node is another "
                       "sub-list (or array) of Document IDs where that word "
                       "appears. This allows for "
                       "efficient insertion of new words and documents without "
                       "reallocating massive blocks of memory."});

  dummyDocs.push_back(
      {"BST Analytics",
       "A Binary Search Tree (BST) is used to maintain sorted order of "
       "documents "
       "based on analytics metrics like Access Count or Frequency. The BST "
       "property "
       "(left < root < right) allows us to perform In-Order Traversal to print "
       "documents in sorted order efficiently (O(n)). Searching for a specific "
       "document's "
       "rank or updating its stats operates in O(log n) time on average."});

  dummyDocs.push_back(
      {"Queue Buffer",
       "A FIFO (First-In-First-Out) Queue is implemented to manage the "
       "indexing pipeline. "
       "When documents are added in bulk or from high-throughput sources, they "
       "are first "
       "enqueued. A background process (simulated here) dequeues them one by "
       "one to "
       "update the Inverted Index and Index Tree. This decouples ingestion "
       "from processing, "
       "preventing system lockups during heavy write operations."});

  dummyDocs.push_back({"Stack History",
                       "A LIFO (Last-In-First-Out) Stack tracks user search "
                       "queries and actions. "
                       "This provides two main benefits: 1) Efficient access "
                       "to the 'Recents' list, "
                       "as the latest search is always on top (O(1)). 2) Undo "
                       "functionality, where "
                       "the last action (like adding a document) can be popped "
                       "off the stack and reversed "
                       "immediately."});

  for (int i = 0; i < dummyDocs.size(); i++) {
    DocData doc = dummyDocs.get(i);
    engine.addDocument(doc.title, doc.content, false);
  }

  UI::printSuccess("Loaded " + to_string(dummyDocs.size()) +
                   " Educational Documents via Custom Array.");
  InputValidation::pause();

  int choice;
  string input;
  int id;

  do {
    UI::clearScreen();
    UI::printHeader();

    UI::printDashboard(engine.getNextDocID() - 1, engine.getTotalSearchCount(),
                       engine.getTopSearchTerm());

    choice = getValidInt("   >> Enter choice (0-17): ", 0, 17);

    cout << endl;

    switch (choice) {
    case 1: {
      UI::printPageHeader("ADD NEW DOCUMENT");
      string title = getValidString("   >> Enter title: ");
      if (title == "0")
        break;

      string content = getValidString("   >> Enter content: ");
      if (content == "0")
        break;

      UI::showLoading(" Adding Document");
      engine.addDocument(title, content);
      break;
    }
    case 2: {
      UI::printPageHeader("REMOVE DOCUMENT");
      id = getValidInt("   >> Enter document ID to remove: ");
      if (id == 0)
        break;

      UI::showLoading(" Removing Document");
      engine.removeDocument(id);
      break;
    }
    case 3: {
      UI::printPageHeader("UPDATE DOCUMENT");
      id = getValidInt("   >> Enter document ID to update: ");
      if (id == 0)
        break;

      string newContent = getValidString("   >> Enter new content: ");
      if (newContent == "0")
        break;

      UI::showLoading(" Updating Document");
      engine.updateDocument(id, newContent);
      break;
    }
    case 4:
      UI::printPageHeader("ALL DOCUMENTS");
      engine.displayAllDocuments();
      break;
    case 5: {
      UI::printPageHeader("KEYWORD SEARCH");
      input = getValidString("   >> Enter keyword: ");
      if (input == "0")
        break;

      UI::showLoading(" Searching");
      engine.search(input);
      break;
    }
    case 6: {
      UI::printPageHeader("MULTI-KEYWORD SEARCH");
      input = getValidString("   >> Enter keywords (space-separated): ");
      if (input == "0")
        break;

      UI::showLoading(" Searching");
      engine.searchMultiple(input);
      break;
    }
    case 7: {
      UI::printPageHeader("PREFIX SEARCH");
      input = getValidString("   >> Enter prefix: ");
      if (input == "0")
        break;

      UI::showLoading(" Searching");
      engine.searchPrefix(input);
      break;
    }
    case 8: {
      UI::printPageHeader("RANK BY FREQUENCY");
      input = getValidString("   >> Enter keyword: ");
      if (input == "0")
        break;

      UI::showLoading(" Ranking Results");
      engine.searchRanked(input);
      break;
    }
    case 9: {
      UI::printPageHeader("RANK BY RECENCY");
      input = getValidString("   >> Enter keyword: ");
      if (input == "0")
        break;

      UI::showLoading(" Ranking Results");
      engine.searchRankedByRecency(input);
      break;
    }
    case 10: {
      UI::printPageHeader("RANK BY ACCESS COUNT");
      input = getValidString("   >> Enter keyword: ");
      if (input == "0")
        break;

      UI::showLoading(" Ranking Results");
      engine.searchRankedByAccess(input);
      break;
    }
    case 11:
      UI::printPageHeader("SEARCH HISTORY");
      engine.displaySearchHistory();
      break;
    case 12: {
      UI::printPageHeader("TOP SEARCHES");
      int n = getValidInt("   >> How many top searches? ", 0);
      if (n == 0)
        break;

      engine.displayTopSearches(n);
      break;
    }
    case 13:
      UI::printPageHeader("SORTED DOCUMENTS (BST)");
      engine.displaySortedDocuments();
      break;
    case 14: {
      UI::printPageHeader("ADD TO QUEUE");
      string title = getValidString("   >> Enter title: ");
      if (title == "0")
        break;
      string content = getValidString("   >> Enter content: ");
      if (content == "0")
        break;
      engine.addToQueue(title, content);
      break;
    }
    case 15:
      UI::printPageHeader("PROCESS QUEUE");
      engine.processQueue();
      break;
    case 16:
      UI::printPageHeader("UNDO LAST ACTION");
      engine.undoLastAction();
      break;
    case 17: {
      UI::printPageHeader("VIEW SPECIFIC DOCUMENT");
      id = getValidInt("   >> Enter Document ID: ");
      if (id == 0)
        break;

      Document *doc = engine.findDocumentById(id);
      if (doc) {
        UI::printFullDocument(doc->title, doc->content, doc->id);
      } else {
        UI::printError("Document not found!");
      }
      break;
    }
    case 0:
      UI::printSuccess("Goodbye! Thanks for using Mini Search Engine Pro.");
      break;
    default:
      UI::printError("Invalid choice. Please select an option from 0-17.");
    }

    if (choice != 0) {
      InputValidation::pause();
    }

  } while (choice != 0);

  return 0;
}
