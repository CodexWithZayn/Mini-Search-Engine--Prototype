#include "UI.h"
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <thread>

void UI::clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

int UI::visibleLength(string text) {
  int length = 0;
  bool inEscape = false;
  for (char c : text) {
    if (c == '\033') {
      inEscape = true;
    } else if (inEscape && c == 'm') {
      inEscape = false;
    } else if (!inEscape) {
      length++;
    }
  }
  return length;
}

string UI::centerText(string text, int width) {
  int len = visibleLength(text);
  if (len >= width)
    return text;
  int padding = (width - len) / 2;

  return string(padding, ' ') + text + string(width - len - padding, ' ');
}

void UI::printMenuRow(string text, int width) {

  int len = visibleLength(text);
  int padding = width - len;
  if (padding < 0)
    padding = 0;

  cout << CYAN << " | " << RESET << text << string(padding, ' ') << CYAN << " |"
       << RESET << endl;
}

void UI::printMenuDualOption(string opt1, string opt2, int width) {
  int half = width / 2;
  int len1 = visibleLength(opt1);
  int len2 = visibleLength(opt2);

  int pad1 = half - len1;
  if (pad1 < 0)
    pad1 = 0;

  int pad2 = (width - half) - len2;
  if (pad2 < 0)
    pad2 = 0;

  cout << CYAN << " | " << RESET << opt1 << string(pad1, ' ') << opt2
       << string(pad2, ' ') << CYAN << " |" << RESET << endl;
}

void UI::printSeparator(string color) {
  cout << color << string(75, '-') << RESET << endl;
}

void UI::printWelcome() {
  clearScreen();
  cout << "\n\n";
  cout << CYAN << "      Search Engine Prototype" << RESET << endl;
  cout << BLUE << "      Powered by AI Algorithms & Data Structures" << RESET
       << endl;
  cout << "\n";
  cout << BOLD << MAGENTA << "      Welcome to the Future of Searching!"
       << RESET << endl;
  cout << "\n\n";
  cout << YELLOW << "      Loading System..." << RESET << endl;
  showLoading("");
  clearScreen();
}

void UI::printHeader() {
  cout << CYAN
       << " ==================================================================="
          "========"
       << RESET << endl;
  cout << BOLD << WHITE
       << UI::centerText("MINI SEARCH ENGINE PRO - Prototype", 75) << RESET
       << endl;
  cout << CYAN
       << " ==================================================================="
          "========"
       << RESET << endl;
}

void UI::printPageHeader(string pageTitle) {
  clearScreen();
  cout << CYAN
       << " ==================================================================="
          "========"
       << RESET << endl;
  cout << BOLD << YELLOW << "   [ " << pageTitle << " ]" << RESET;
  cout << CYAN << "   (Enter '0' to Cancel)" << RESET << endl;
  cout << CYAN
       << " ==================================================================="
          "========"
       << RESET << endl;
  cout << endl;
}

string boxOpt(int id, string title, string color = WHITE) {
  // Symmetric brackets: [ 1 ] vs [ 11 ]
  string idStr = to_string(id);
  string gap = (id < 10) ? "   " : "  ";

  return string(CYAN) + "[" + RESET + BOLD + WHITE + " " + idStr + " " + RESET +
         CYAN + "]" + RESET + gap + color + title + RESET;
}

void UI::printMenu() {
  int width = 70; // Inner width
  cout << endl;
  cout << CYAN << " +-" << string(width, '-') << "-+" << RESET << endl;
  cout << CYAN << " | " << BOLD << MAGENTA
       << UI::centerText("M  A  I  N    M  E  N  U", width) << RESET << CYAN
       << " |" << RESET << endl;
  cout << CYAN << " +-" << string(width, '-') << "-+" << RESET << endl;

  printMenuRow(BOLD + BLUE + string(" DOCUMENT OPERATIONS ") + RESET, width);
  printMenuDualOption(boxOpt(1, "Create New Entry", GREEN),
                      boxOpt(2, "Remove Entry", RED), width);
  printMenuDualOption(boxOpt(3, "Update Entry", WHITE),
                      boxOpt(4, "View Full Index", WHITE), width);
  printMenuRow("", width);

  printMenuRow(BOLD + BLUE + string(" SEARCH ENGINE ") + RESET, width);
  printMenuDualOption(boxOpt(5, "Keyword Search", YELLOW),
                      boxOpt(6, "Multi-Term Search", YELLOW), width);
  printMenuRow(boxOpt(7, "Auto-Complete", YELLOW), width);
  printMenuRow("", width);

  printMenuRow(BOLD + BLUE + string(" ANALYTICS ") + RESET, width);
  printMenuDualOption(boxOpt(8, "Frequency Rank", MAGENTA),
                      boxOpt(9, "Recency Rank", MAGENTA), width);
  printMenuDualOption(boxOpt(10, "Access Rank   ", MAGENTA),
                      boxOpt(11, "Search Ledger ", MAGENTA), width);
  printMenuRow(boxOpt(12, "Trend Analysis", MAGENTA), width);

  cout << CYAN << " +-" << string(width, '-') << "-+" << RESET << endl;
  printMenuRow(boxOpt(0, "Shut Down System", RED), width);
  cout << CYAN << " +-" << string(width, '-') << "-+" << RESET << endl;
}

void UI::printDashboard(int totalDocs, int totalSearches, string topSearch) {
  int width = 70;

  cout << endl;
  cout << BLUE << "  STATS: " << WHITE << "Docs: " << BOLD << GREEN << totalDocs
       << RESET << " | " << WHITE << "Searches: " << BOLD << GREEN
       << totalSearches << RESET << " | " << WHITE << "Top: " << BOLD << YELLOW
       << (topSearch.empty() ? "N/A" : topSearch) << RESET << endl;
  cout << endl;

  cout << CYAN << " +-" << string(width, '-') << "-+" << RESET << endl;
  cout << CYAN << " | " << BOLD << MAGENTA
       << UI::centerText("D  A  S  H  B  O  A  R  D", width) << RESET << CYAN
       << " |" << RESET << endl;
  cout << CYAN << " +-" << string(width, '-') << "-+" << RESET << endl;

  printMenuRow(BOLD + BLUE + string(" DOCUMENT OPERATIONS ") + RESET, width);
  printMenuDualOption(boxOpt(1, "Create New Entry", GREEN),
                      boxOpt(2, "Remove Entry", RED), width);
  printMenuDualOption(boxOpt(3, "Update Entry", WHITE),
                      boxOpt(4, "View Full Index", WHITE), width);
  printMenuRow("", width);

  printMenuRow(BOLD + BLUE + string(" SEARCH ") + RESET, width);
  printMenuDualOption(boxOpt(5, "Keyword Search", YELLOW),
                      boxOpt(6, "Multi-Term Search", YELLOW), width);
  printMenuRow(boxOpt(7, "Auto-Complete", YELLOW), width);
  printMenuRow("", width);

  printMenuRow(BOLD + BLUE + string(" ANALYTICS ") + RESET, width);
  printMenuDualOption(boxOpt(8, "Frequency Rank", MAGENTA),
                      boxOpt(9, "Recency Rank", MAGENTA), width);
  printMenuDualOption(boxOpt(10, "Access Rank", MAGENTA),
                      boxOpt(11, "Search Ledger", MAGENTA), width);
  printMenuRow(boxOpt(12, "Trend Analysis", MAGENTA), width);
  printMenuRow("", width);

  printMenuRow(BOLD + BLUE + string(" DATA STRUCTURES ") + RESET, width);
  printMenuDualOption(boxOpt(13, "BST Sorted", CYAN),
                      boxOpt(14, "Add to Queue", CYAN), width);
  printMenuDualOption(boxOpt(15, "Process Queue", CYAN),
                      boxOpt(16, "Undo (Stack)", CYAN), width);
  printMenuRow(boxOpt(17, "View Specific Document", CYAN), width);

  cout << CYAN << " +-" << string(width, '-') << "-+" << RESET << endl;
  printMenuRow(boxOpt(0, "Shut Down System", RED), width);
  cout << CYAN << " +-" << string(width, '-') << "-+" << RESET << endl;
}

void UI::printFullDocument(string title, string content, int id) {
  clearScreen();
  cout << endl;
  string border = CYAN;

  cout << border
       << " +=================================================================="
          "======+"
       << RESET << endl;
  cout << border << " | " << BOLD << WHITE << "DOC ID: " << left << setw(4)
       << id << RESET << border << " | " << BOLD << YELLOW << left << setw(60)
       << title.substr(0, 60) << RESET << border << " |" << RESET << endl;
  cout << border
       << " +=================================================================="
          "======+"
       << RESET << endl;
  cout << endl;

  cout << endl;
  cout
      << border
      << "   ------------------------------------------------------------------"
      << RESET << endl;

  int lineWidth = 70;
  string word;
  int currentLineLen = 0;
  cout << "   ";

  for (char c : content) {
    if (c == ' ') {
      if (currentLineLen + word.length() > lineWidth) {
        cout << endl << "   " << word << " ";
        currentLineLen = word.length() + 1;
      } else {
        cout << word << " ";
        currentLineLen += word.length() + 1;
      }
      word = "";
    } else {
      word += c;
    }
  }
  if (currentLineLen + word.length() > lineWidth) {
    cout << endl << "   " << word;
  } else {
    cout << word;
  }
  cout << endl;

  cout
      << border
      << "   ------------------------------------------------------------------"
      << RESET << endl;
  cout << endl;

  cout << border
       << " +=================================================================="
          "======+"
       << RESET << endl;
  cout << endl;

  cout << CYAN << "   (Press Enter to return to menu)" << RESET << endl;
}

void UI::printSimpleBox(string title, string content, string color) {
  cout << endl;
  cout << color
       << " +------------------------------------------------------------------"
          "--------+"
       << RESET << endl;
  cout << color << " | " << BOLD << left << setw(70) << title << RESET << color
       << " |" << RESET << endl;
  cout << color
       << " +------------------------------------------------------------------"
          "--------+"
       << RESET << endl;
  cout << "   " << content << endl;
  cout << color
       << " +------------------------------------------------------------------"
          "--------+"
       << RESET << endl;
}

void UI::printResultCard(string title, string content, int id,
                         string highlightKeyword) {
  string border = CYAN;
  if (!highlightKeyword.empty())
    border = MAGENTA;

  cout << endl;
  cout << border << " +-" << BOLD << WHITE << "[ ID: " << setw(4) << id << " ]"
       << border << string(56, '-') << "+" << RESET << endl;

  cout << border << " | " << BOLD << YELLOW << left << setw(70)
       << title.substr(0, 70) << RESET << border << " |" << RESET << endl;

  cout << border
       << " +------------------------------------------------------------------"
          "--------+"
       << RESET << endl;

  cout << " | ";
  if (highlightKeyword.empty()) {
    cout << left << setw(70) << content.substr(0, 70);
  } else {
    string lowerContent = "";
    for (char c : content)
      lowerContent += tolower(c);

    string lowerKeyword = "";
    for (char c : highlightKeyword)
      lowerKeyword += tolower(c);

    size_t found = lowerContent.find(lowerKeyword);
    if (found != string::npos) {
      size_t start = (found > 20) ? found - 20 : 0;
      string snippet = content.substr(start, 70);

      size_t snippetFound = found - start;
      cout << snippet.substr(0, snippetFound);
      cout << BOLD << MAGENTA
           << snippet.substr(snippetFound, highlightKeyword.length()) << RESET;
      cout << snippet.substr(snippetFound + highlightKeyword.length());

      int printedLen = snippet.length();
      if (printedLen < 70)
        cout << string(70 - printedLen, ' ');
    } else {
      cout << left << setw(70) << content.substr(0, 70);
    }
  }
  cout << border << " |" << RESET << endl;

  cout << border
       << " +------------------------------------------------------------------"
          "--------+"
       << RESET << endl;
}

void UI::printSuccess(string msg) {
  cout << GREEN << " [SUCCESS] " << msg << RESET << endl;
}

void UI::printError(string msg) {
  cout << RED << " [ERROR] " << msg << RESET << endl;
}

void UI::printWarning(string msg) {
  cout << YELLOW << " [WARNING] " << msg << RESET << endl;
}

void UI::showLoading(string msg) {
  if (!msg.empty())
    cout << YELLOW << msg << " " << RESET;

  cout << "[";
  for (int i = 0; i < 20; i++) {
    cout << GREEN << "=" << RESET;
    cout.flush();
    this_thread::sleep_for(chrono::milliseconds(30));
  }
  cout << "] Done!" << endl;
  this_thread::sleep_for(chrono::milliseconds(200));
}

void UI::printTableStart() {
  cout << endl;
  cout << WHITE
       << " -------------------------------------------------------------------"
          "------"
       << RESET << endl;
  cout << BOLD << WHITE << " | " << left << setw(4) << "ID" << " | " << setw(63)
       << "Title" << " |" << RESET << endl;
  cout << WHITE
       << " -------------------------------------------------------------------"
          "------"
       << RESET << endl;
}

void UI::printTableRow(string col1, string col2) {
  cout << " | " << left << setw(4) << col1 << " | " << CYAN << setw(63)
       << col2.substr(0, 63) << RESET << " |" << endl;
}

void UI::printTableEnd() {
  cout << WHITE
       << " -------------------------------------------------------------------"
          "------"
       << RESET << endl;
}
