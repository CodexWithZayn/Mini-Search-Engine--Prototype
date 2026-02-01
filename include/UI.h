#ifndef UI_H
#define UI_H

#include "Colors.h"
#include <iostream>
#include <string>

using namespace std;

class UI {
public:
  static void clearScreen();
  static void printHeader();
  static void printWelcome(); // ASCII Art
  static void printMenu();
  static void printDashboard(int totalDocs, int totalSearches,
                             string topSearch);

  // New UI Elements
  static void printFullDocument(string title, string content, int id);
  static void printResultCard(string title, string content, int id,
                              string highlightKeyword = "");
  static void printSimpleBox(string title, string content,
                             string color = CYAN); // Renamed for clarity

  static void printSuccess(string msg);
  static void printError(string msg);
  static void printWarning(string msg);
  static void showLoading(string msg);
  static void printSeparator(string color = CYAN);
  static void
  printPageHeader(string pageTitle); // Clears and shows header + title

  // Table formatting
  static void printTableStart();
  static void printTableRow(string col1, string col2);
  static void printTableEnd();

  // Helpers
  static int visibleLength(string text); // Returns length ignoring ANSI codes
  static string centerText(string text, int width);

  static void printMenuRow(string text, int width = 74); // Helper for menu rows
  static void printMenuDualOption(string opt1, string opt2,
                                  int width = 74); // Helper for 2-column menu
};

#endif
