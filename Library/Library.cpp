#include "Library.h"
#include "TemplatedDLList.h"
#include <fstream>
#include <string>   

// Searches for a title in the database and returns vector of matching records
std::vector<Record> Library::search(std::string title)
{   
    //make the title records vector
    std::vector<Record> title_records_vector = {};
    //convert title to lowercase
    std::string lowercase_title = "";//title;
    for(int i = 0; i < title.length(); ++i){
        lowercase_title += std::tolower(title[i]); //lowercase_title[i] = std::tolower(title[i]);
    }
    //determine the index (first letter) of which linkedlist in DB to get
    int index = lowercase_title[0] - 'a'; 
    if(index > 25 || index < 0){ 
        return title_records_vector;
    }
    //retrieve the linkedlist which has title starting letter and returns if DLL is empty
    DLList<Record>& letter_dll = book_db.at(index);
    if(letter_dll.is_empty()){
        return title_records_vector;
    }
    //search thru the DLL and add records that have the same title
    DLListNode<Record>* record_ptr = letter_dll.first_node();
    while(record_ptr != letter_dll.after_last_node()){
        if(record_ptr->obj.get_title() == title){
            title_records_vector.push_back(record_ptr->obj);
        }
        record_ptr = record_ptr->next;
    }
    //return vector with all records of same title
    return title_records_vector;
}

// Imports records from a file.  Does not import duplicates.
// Returns the number of records added to the database
int Library::import_database(std::string filename)
{
    Record curr_book;  //makes a new temporary record object
    int add_count = 0;

    std::ifstream input_file(filename);  
    if(input_file.is_open()){  
        while (input_file >> curr_book){ //extracts details from .txt and adds the record into DB

            //checks for valid details
            if( (curr_book.get_title() == "") ||
            (curr_book.get_author() == "") ||
            (curr_book.get_ISBN().length() < 17) || 
            (curr_book.get_year() == "") ||
            (curr_book.get_edition() == "") )
            {continue;}

            if(add_record(curr_book)) //increments count if successfully added record to DB
                add_count++;
        }
        //close file and returns # books added to DB
        input_file.close();
    }  
    
    return add_count;
}

// Exports the current database to a file
// Returns the number of records exported
int Library::export_database(std::string filename)
{
    //open the output file for writing
    std::ofstream output_file(filename);
    //checks if cannot open and throws error
    if(!output_file.is_open()){
        throw std::runtime_error("File Cannot Open");
    }
    //set export counter
    int successful_export_count = 0;
    //goes thru entire DB
    for(int i = 0; i < book_db.size(); i++){
        DLList<Record> letter_dll = book_db[i];
        DLListNode<Record>* curr_dll_node_ptr = letter_dll.first_node();
        Record curr_dll_rec_node = curr_dll_node_ptr->obj;
        while(curr_dll_node_ptr != letter_dll.after_last_node()){   //while (output_file << curr_dll_rec_node){ 
            //extracts details of entire record and adds to .txt output_file
            output_file << curr_dll_rec_node; //operator<<(output_file, curr_dll_rec_node);
            std::cout<<endl;
            successful_export_count++;
            //updates to next node and next node's object (Record)
            curr_dll_node_ptr = curr_dll_node_ptr->next;
            curr_dll_rec_node = curr_dll_node_ptr->obj;
        }

    }
    //close file and returns # books added to DB
    output_file.close();
    return successful_export_count;
}

// Prints out every book in the library
void Library::print_database()
{
    //goes thru entire DB
    for(int i = 0; i < book_db.size(); i++){
        DLList<Record> letter_dll = book_db[i];
        DLListNode<Record>* curr_dll_node_ptr = letter_dll.first_node();
        Record curr_dll_rec_node = curr_dll_node_ptr->obj;
        while(curr_dll_node_ptr != letter_dll.after_last_node()){   //while (output_file << curr_dll_rec_node){ 
            //extracts details of entire record and adds to .txt output_file
            std::cout << curr_dll_rec_node << endl;
            //updates to next node and next node's object (Record)
            curr_dll_node_ptr = curr_dll_node_ptr->next;
            curr_dll_rec_node = curr_dll_node_ptr->obj;
        }

    }
}

// // Adds record to database, avoid complete duplicates
bool Library::add_record(const Record book)
{
    // Finds which linkedlist to search
    int index = std::tolower(book.get_title()[0]) - 'a'; 
    DLList<Record>& letter_dll = book_db.at(index);
    DLListNode<Record>* curr_ptr = letter_dll.first_node();
    Record curro = curr_ptr->obj;

    if( (book.get_title() == "") ||
    (book.get_author() == "") ||
    (book.get_ISBN() == "") || 
    (book.get_year() == "") ||
    (book.get_edition() == "") ) 
    {return false;}

     // duplicate check
     while (curr_ptr != letter_dll.after_last_node()){
        if (book.get_title() < curr_ptr->obj.get_title()){
            letter_dll.insert_before(*curr_ptr, book);
            return true;
        }
        else if (book.get_title() == curr_ptr->obj.get_title()){
            if (book.get_author() < curr_ptr->obj.get_author()){
                letter_dll.insert_before(*curr_ptr, book);
                return true;
            }
            else if (book.get_author() == curr_ptr->obj.get_author()) 
            {
                if (book.get_ISBN() < curr_ptr->obj.get_ISBN()){
                    letter_dll.insert_before(*curr_ptr, book);
                    return true;
                }
                else if (book.get_ISBN() == curr_ptr->obj.get_ISBN()) {
                    return false;
                }
            }
        }
        curr_ptr = curr_ptr->next;
    }
    book_db.at(index).insert_last(book);
    return true;
}


// Deletes a record from the database
void Library::remove_record(Record book)
{
    //finds the correct linkedlist, where book to delete is located
    std::string lowercase_title = book.get_title();
    for(int i = 0; i < book.get_title().length(); ++i){
        lowercase_title[i] = std::tolower(book.get_title()[i]);
    }
    int index = lowercase_title[0] - 'a'; 
    DLList<Record>& letter_dll = book_db.at(index);
    //making pointer
    DLListNode<Record>* curr_node = letter_dll.first_node();
    //deletes every instance of book in DLL
    while(curr_node != letter_dll.after_last_node()){

        if( operator==(curr_node->obj , book) )
        {
            //updating internal DLL pointers
            curr_node->prev->next = curr_node->next;
            curr_node->next->prev = curr_node->prev;
            DLListNode<Record>* next_node = curr_node->next; 
            //deletes bookNode (matching to curr_node) from DLL
            delete curr_node;
            curr_node = next_node;
        }
        else
        {
            //if details differ, move to the next node
            curr_node = curr_node->next;
        }
    }
}

// Prompts user for yes or no and returns choice Y or N
char Library::prompt_yes_no()
{
    return prompt_string("Yes or no? (Y/N): ").at(0);
}

// Given a vector of menu options returns index of choice
int Library::prompt_menu(std::vector<std::string> prompts)
{
    // Print out prompt statements
    for (int i = 0; i < prompts.size(); i++)
    {
        std::cout << "\t" << (i + 1) << ". " << prompts.at(i) << std::endl;
    }

    return (std::stoi(prompt_string("Enter option: ")) - 1);
}

// Prompts user for a new record
Record Library::prompt_record()
{
    std::string title = prompt_title();
    std::string author = prompt_string("Enter author: ");
    std::string ISBN = prompt_string("Enter ISBN: ");
    std::string year = prompt_string("Enter year: ");
    std::string edition = prompt_string("Enter edition: ");

    Record rtn;
    rtn.set_title(title);
    rtn.set_author(author);
    rtn.set_ISBN(ISBN);
    rtn.set_year(year);
    rtn.set_edition(edition);

    return rtn;
}

// Prompts for a valid title
std::string Library::prompt_title()
{
    return prompt_string("Enter title (starts with capital letter): ");
}

// Prompts for a valid string
std::string Library::prompt_string(std::string prompt)
{
    std::cout << prompt;
    std::string answer;
    std::getline(std::cin, answer);

    return answer;
}