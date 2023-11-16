//implementation of record class
#include "Record.h"

// title setter
void Record::set_title(string t) {
    title = t;
}
// author setter
void Record::set_author(string a) {
    author = a;
}
// ISBN setter
void Record::set_ISBN(string i) {
    ISBN = i;
}
// year setter
void Record::set_year(string y) {
    year = y;
}
// edition setter
void Record::set_edition(string e) {
    edition = e;
}
// title getter
string Record::get_title() const {
    return title;
}
// author getter
string Record::get_author() const {
    return author;
}
// ISBN getter
string Record::get_ISBN() const {
    return ISBN;
}
// year getter
string Record::get_year() const {
    return year;
}
// edition getter
string Record::get_edition() const {
    return edition;
}
// input operator
std::istream& operator>>(std::istream& is, Record& rec) {
    // extracts title, author, ISBN, year, edition from the Book.txt
    string empty_line, title, author, ISBN, year, edition;
    std::getline(is, empty_line);
    std::getline(is, title);
    std::getline(is, author);
    std::getline(is, ISBN);
    std::getline(is, year);
    std::getline(is, edition);
    //sets those values into 'Record& rec'
    rec.set_title(title);
    rec.set_author(author);
    rec.set_ISBN(ISBN);
    rec.set_year(year);
    rec.set_edition(edition);
    return is;
}
// output operator 
std::ostream& operator<<(std::ostream& os,  Record& rec) {
    //loads all record values into 'os' and prints output
    os << rec.get_title() << endl << rec.get_author() << endl << rec.get_ISBN() << endl << rec.get_year() << endl << rec.get_edition() << endl;
    return os;
}
// equals operator
bool operator==(const Record& r1, const Record& r2) {
    //checks if both books have the same title, author, ISBN
    return ( (r1.get_title() == r2.get_title() ) && (r1.get_author() == r2.get_author() ) && (r1.get_ISBN() == r2.get_ISBN() ) );
}