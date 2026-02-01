#include "Document.h"

Document::Document() {
    id = -1;
    title = "";
    content = "";
    created_at = time(nullptr);
    updated_at = created_at;
    accessCount = 0;
}

Document::Document(int id, const string& title, const string& content) {
    this->id = id;
    this->title = title;
    this->content = content;
    created_at = time(nullptr);
    updated_at = created_at;
    accessCount = 0;
}

Document::~Document() {
  // nothing to free yet  
}
