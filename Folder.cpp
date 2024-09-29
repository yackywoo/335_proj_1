#include "Folder.hpp"

/**
* @brief Construct a new Folder object
* @param name A string with alphanumeric characters.
   If the folder name is empty / none is provided, default value of "NewFolder" is used. 
* @throw If the name is invalid (eg. contains non-alphanumeric characters) an InvalidFormatException is thrown
*/
Folder::Folder(const std::string& name) : name_{"NewFolder"} {
   if (name.empty()) { return; }

   for (const char& c : name) {
      if (!std::isalnum(c)) {
         // We have found a non-alphanumeric character
         throw InvalidFormatException("Invalid folder name: " + name);
      }
   }
   
   name_ = name;
}

/**
   * @brief Get the value stored in name_
   * @return std::string 
   */
std::string Folder::getName() const {
   return name_;
}

/**
* @brief Sets the name_ member to the given parameter
* 
* @param new_foldername A string containing only alphanumeric characters
*    - If the string is invalid the folder is not renamed
* @return True if the folder was renamed sucessfully. False otherwise.
*/
bool Folder::rename(const std::string& name) {
   for (const char& c : name) {
      if (!std::isalnum(c)) { return false; }
   }
   
   name_ = name;
   return true;
}

/**
* @brief Sorts and prints the names of subfolder and file vectors lexicographically (ie. alphabetically)
* The contents of subfolders are not printed.
* Reference the following format (using 3 spaces to indent the contained filenames)
* <CURRENT_FOLDER_NAME> 
*    <SUBFOLDER1_NAME> 
*    <SUBFOLDER2_NAME> 
*    ...
*    <SUBFOLDER_N_NAME> 
*    <FILENAME_1>
*    <FILENAME_2>
*     ...
*    <FILENAME_N>
* 
* @note: This CAN be done more efficiently by maintaining sorted order in the vectors already, instead of sorting each time we print. 
*    However, we'll hold off on that for now, since we just want to get used to iterating with iterators.
*/
void Folder::display() {
   std::sort(files_.begin(), files_.end());

   std::cout << getName() << std::endl;
   for (auto it = files_.begin(); it != files_.end(); ++it) { std::cout << "   " << it->getName() << std::endl; }
}

//                       DO NOT EDIT ABOVE THIS LINE. 
//             (unless you want your work to be tested incorrectly)
//    That also means includes. Remember, all other includes go in .hpp
// =========================== YOUR CODE HERE ===========================

size_t Folder::getSize() const {
   size_t result {0};

   for (const auto& files : files_) {
      result += files.getSize();
   }

   return result;
} // getSize

bool Folder::addFile(File& new_file) {
   //no valid filename (already moved)
   if (new_file.getName() == "") {
      return false;
   }
   
   //if empty folder, skip the binary search
   if (files_.empty()) {
      files_.push_back(std::move(new_file));
      return true;
   }

   //no duplicates allowed -> sort then binary sesarch
   std::sort(files_.begin(), files_.end());

   auto i = files_.begin();
   auto j = files_.end() - 1;
   std::vector<File>::iterator mid;

   while (i <= j) {
      mid = i + std::distance(i, j) / 2;

      if (mid->getName() == new_file.getName()) {
         //prevents duplicates
         return false; 
      } else if (new_file < *mid) {
         //if on left side
         j = mid - 1;
      } else { //new_file > files_[mid]
         //on right side
         i = mid + 1;
      }
      //if this line of code was at bottom of loop then mid can be used to insert
      //mid = i + std::distance(i, j) / 2;
   }

   //if goes past while loop -> (i > j) & not duplicate, so insert
   // cant use mid to insert because mid won't be updated after breaking out while loop
   files_.insert(i, std::move(new_file));

   return true;
} // addFile

bool Folder::removeFile(const std::string& name) {
   auto i = files_.begin();
   auto j = files_.end() - 1;
   std::vector<File>::iterator mid;

   //binary search for file name
   while(i <= j) {
      mid = i + std::distance(i, j) / 2;

      if (mid->getName() == name) {
         files_.erase(mid);
         return true;
      } else if (name < mid->getName()) {
         //if on left side
         j = mid - 1;
      } else { //name > mid->getName()
         //on right side
         i = mid + 1;
      }
   }

   return false;
} // removeFile

bool Folder::moveFileTo(const std::string& name, Folder& destination) {
   // if moving to same folder
   if (this->name_ == destination.getName()) {
      return true;
   }

   if (!destination.files_.empty()) {
      //binary search destination folder for same name
      auto i2 = destination.files_.begin();
      auto j2 = destination.files_.end() - 1;
      std::vector<File>::iterator mid2;

      while(i2 <= j2) {
         mid2 = i2 + std::distance(i2, j2) / 2;

         if (mid2->getName() == name) {
            //return false cannot move if dupe name
            return false;
         } else if (name < mid2->getName()) {
            //if on left side
            j2 = mid2 - 1;
         } else { //name > mid2->getName()
            //on right side
            i2 = mid2 + 1;
         }
      }
   }

   if (!this->files_.empty()) {
      // binary search current directory for matching name
      auto i = files_.begin();
      auto j = files_.end() - 1;
      std::vector<File>::iterator mid;

      while(i <= j) {
         mid = i + std::distance(i, j) / 2;

         if (mid->getName() == name) {
            destination.files_.push_back(std::move(*mid));
            this->files_.erase(mid);
            return true;
         } else if (name < mid->getName()) {
            //if on left side
            j = mid - 1;
         } else { //name > mid->getName()
            //on right side
            i = mid + 1;
         }
      }
   }

   return false;
} // moveFileTo

bool Folder::copyFileTo(const std::string& name, Folder& destination) {

   //binary search dest. folder
   if (!destination.files_.empty()) {
      auto i2 = destination.files_.begin();
      auto j2 = destination.files_.end() - 1;
      std::vector<File>::iterator mid2;

      while(i2 <= j2) {
         mid2 = i2 + std::distance(i2, j2) / 2;

         if (mid2->getName() == name) {
            return false;
         } else if (name < mid2->getName()) {
            //if on left side
            j2 = mid2 - 1;
         } else { //name > mid2->getName()
            //on right side
            i2 = mid2 + 1;
         }
      }
   }
   
   //binary search curr folder
    if (!this->files_.empty()) {
      auto i = files_.begin();
      auto j = files_.end() - 1;
      std::vector<File>::iterator mid;

      while(i <= j) {
         mid = i + std::distance(i, j) / 2;

         if (mid->getName() == name) {
            //copy to dest. folder
            destination.files_.push_back(*mid);
            return true;
         } else if (name < mid->getName()) {
            //if on left side
            j = mid - 1;
         } else { //name > mid->getName()
            //on right side
            i = mid + 1;
         }
      }
   }

   // return false if not found current folder 
   return false;
} // copyFileTo
