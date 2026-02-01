# Mini Search Engine Pro

A powerful, efficient, and modular search engine implemented in C++ from scratch. This project demonstrates advanced usage of hybrid data structures including custom Arrays, Linked Lists, Binary Search Trees (BST), Queues, and Stacks to optimize indexing, storage, and retrieval.

## 🚀 Features

- **Advanced Search Capabilities:**
  - **Keyword Search:** Find documents containing specific words.
  - **Multi-Keyword Search:** Search for documents matching multiple terms.
  - **Prefix Search:** Find words starting with a specific prefix.

- **Smart Ranking System:**
  - Rank results by **Frequency** (relevance).
  - Rank results by **Recency** (latest updates).
  - Rank results by **Access Count** (popularity).

- **Document Management:**
  - **Add, Remove, Update** documents dynamically.
  - **Queue System:** Buffer high-throughput document additions.
  - **Undo:** Revert the last action immediately.

- **Analytics & History:**
  - View **Search History** (Stack-based).
  - View **Top Searches**.
  - **Sorted View:** View documents sorted by metrics using BST.

## 🛠️ Data Structures Used

This project avoids STL containers where possible to demonstrate low-level memory management and custom implementations:

- **Custom Array:** For raw storage with amortized O(1) insertion.
- **Singly Linked List:** For the Inverted Index (mapping words to Document IDs).
- **Binary Search Tree (BST):** For maintaining sorted analytics data.
- **Queue (FIFO):** For managing the document indexing pipeline.
- **Stack (LIFO):** For search history and undo functionality.

## 📦 Build & Run

### Prerequisites

- C++ Compiler (g++ recommended)
- Make (optional, for easy building)

### Compiling

To build the project, simply run:

```bash
make
```

Or manually:

```bash
g++ -Iinclude -Iinclude/DataStructures -Wall main.cpp src/Document.cpp src/Index.cpp src/SearchEngine.cpp src/Tokenizer.cpp src/DataStructures/IndexNode.cpp src/DataStructures/LinkedList.cpp -o main.exe
```

### Running

After compiling, execute the binary:

```bash
./main.exe
```

## 📝 Usage

1. Follow the on-screen dashboard to select operations.
2. Use the number keys (0-17) to navigate the menu.
3. Choose option `0` to exit safely.

## 📂 Project Structure

```
├── include/          # Header files
├── src/              # Source implementations
├── main.cpp          # Entry point
├── Makefile          # Build configuration
└── README.md         # Project documentation
```

---

_Created for educational purposes to demonstrate Data Structure algorithms._
