#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <string>
#include <ctime>

using namespace std;

class Document {
public:
    int id;
    string title;
    string content;
    time_t created_at;
    time_t updated_at;
    int accessCount;

    Document();
    Document(int id, const string& title, const string& content);
    ~Document();
};

#endif