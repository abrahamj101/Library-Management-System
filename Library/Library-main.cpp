#include "Library.h"
#include "Record.h"
#include "TemplatedDLList.h"
#include <iostream>
#include <limits>
#include <string>
#include <sstream>

using namespace std;

int main() {

    Library library_db;
   // Loop until option to exit
   int option = -1;
   while (option != 6) {
       // Print menue
       cout << "\t1. Search / Add record" << endl;
       cout << "\t2. Delete record" << endl;
       cout << "\t3. Print database" << endl;
       cout << "\t4. Import database" << endl;
       cout << "\t5. Export database" << endl;
       cout << "\t6. Quit" << endl;
       cout << "Enter option: ";
       cin >> option;
       if (cin.fail()) {
           cin.clear();
           cin.ignore(numeric_limits<streamsize>::max(), '\n');
           option = -1;
       }
       switch (option) {
           case 1: // Search / Add record
           {
               // Get the title and search for it in the database
               string title;
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
               cout << endl;
               title = library_db.prompt_title();
               vector<Record> matches = library_db.search(title);

               // No records, prompt to add
               if (matches.size() == 0) {
                   char add_title;
                   cout << "Title not found.  Would you like to add it?" << endl;
                   add_title = library_db.prompt_yes_no();
                   if (add_title == 'Y') {
                       Record new_book = library_db.prompt_record();
                       // Attempt to add; book not added if already in database
                       if (!library_db.add_record(new_book)) {
                           cout << "Book already in database" << endl;
                       }
                   }
                   cout << endl;
               }
               // Title found, display editions and ask to add if still not found
               else {
                   vector<string> options;
                   for (auto x: matches) {
                       // Add author to the edition
                       options.push_back(x.get_edition() + " by " + x.get_author());
                   }
                   options.push_back("Add new record");
                   int display_option = library_db.prompt_menu(options);
                   if (display_option == options.size() - 1) {
                       Record new_book = library_db.prompt_record();
                       // Attempt to add; book not added if already in database
                       if (!library_db.add_record(new_book)) {
                           cout << "Book already in database" << endl;
                       }
                       cout << endl;
                   }
                   // Display the selected book
                   else {
                       cout << endl;
                       cout << matches.at(display_option) << endl << endl;
                   }
               }
               break;
           }
           case 2: // Delete record
           {
               // Get the title and search for it in the database
               string title;
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
               cout << endl;
               title = library_db.prompt_title();
               vector<Record> matches = library_db.search(title);

               // No records
               if (matches.size() == 0) {
                   cout << "Title not found." << endl;
               }
               // Records found.  Prompt for edition to delete
               else {
                   cout << "Select edition to delete or exit" << endl;
                   vector<string> options;
                   for (auto x: matches) {
                       // Add the author to the edition
                       options.push_back(x.get_edition() + " by " + x.get_author());
                   }
                   options.push_back("Exit");
                   int display_option = library_db.prompt_menu(options);
                   if (display_option == options.size() - 1) {
                       // Exit
                   }
                   else {
                       // Delete the record from the database
                       library_db.remove_record(matches.at(display_option));
                       cout << "Record deleted" << endl;
                   }
               }
               cout << endl;
               break;
           }
           case 3: // Print database
               cout << endl;
               library_db.print_database();
               break;
           case 4: // Import database
           {
               string filename;
               cout << endl;
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
               cout << "Enter name of file to import from: ";
               cin >> filename;
               int count = library_db.import_database(filename);
               cout << "Imported " << count << " records" << endl << endl;
               break;
           }
           case 5: // Export database
           {
               string filename;
               cout << endl;
               cin.ignore(numeric_limits<streamsize>::max(),'\n');
               cout << "Enter name of file to export to: ";
               cin >> filename;
               int count = library_db.export_database(filename);
               cout << "Exported " << count << " records" << endl << endl;
               break;
           }
           case 6: // Exit
               cout << "Exiting" << endl;
               break;
           default: // Invalid option
               cout << "Invalid option" << endl << endl;
               break;
       }
   }
   return 0;
}
// g++ -std=c++17 library-main.cpp Library.cpp Record.cpp -o library