#include "File.hpp"
      
std::string File::getName() const {
   return filename_;
}

std::string File::getContents() const {
   return contents_;
}

void File::setContents(const std::string& new_contents) {
   contents_ = new_contents;
}

int* File::getIcon() const {
   return icon_;
}

void File::setIcon(int* new_icon) {
   if (icon_) { delete[] icon_; }
   icon_ = new_icon;
} 

std::ostream& operator<< (std::ostream& os, const File& target) {
   os << "Name: " << target.getName() << std::endl;
   os << "Size: " << target.getSize() << " bytes" << std::endl;
   os << "Contents: " << target.getContents(); 
   return os;
}

bool File::operator<(const File& rhs) const {
   return getName() < rhs.getName();
}

//                       DO NOT EDIT ABOVE THIS LINE. 
//             (unless you want your work to be tested incorrectly)
//    That also means includes. Remember, all other includes go in .hpp

// However, you may notice an operator overload you don't recognize (<<)
// Try calling the following once you've implemented a constructor & getSize():
//    File a; 
//    std::cout << a << std::endl;

// =========================== YOUR CODE HERE ===========================

File::File(const std::string& filename, const std::string& contents, int* icon) : contents_(contents), icon_(icon) {
   // if not empty filename, validate file name
   if (filename.length() > 0) {
      bool extension_exist = false;
      
      for (const auto& letters : filename) {
         if (!isalnum(letters) && extension_exist == false) {
            // check if non alnum char is period char (allow first period char found)
            if (letters == '.') {
               extension_exist = true;
            } else {
               throw (InvalidFormatException("Invalid character in filename: " + filename));
            }
         } else if (!isalnum(letters) && extension_exist == true) {
            // if non alnum and ext exists then immediate error (prevents duplicate periods & non-alnum chars)
            throw (InvalidFormatException("Invalid character in filename: " + filename));
         }
      } // exits this loop then -> valid filename that may or may not have extension
      
      // Setting data members, adding extension if missing
      if (extension_exist == false) {
         filename_ = filename + ".txt";
      } else {
         filename_ = filename;
      }
   } else {
      //if empty filename then default
      filename_ = "NewFile.txt";
   }
} // Constructor

size_t File::getSize() const {
   // every char within the string = 1 byte
   return contents_.size();
} // getSize


File::File(const File& rhs) : filename_(rhs.filename_), contents_(rhs.contents_) {
   if (rhs.icon_ != nullptr) {
      //deep copy rhs.icon_ to this->icon_ if rhs has an icon 
      this->icon_ = new int [ICON_DIM];
      std::copy(rhs.icon_, rhs.icon_ + ICON_DIM, this->icon_);
   } else {
      this->icon_ = nullptr;
   }
} // Copy Constructor

File& File::operator=(const File& rhs) {
   if (this != &rhs) {
      delete [] this->icon_;

      //deep copy rhs datamembers to this->datamembers
      this->filename_ = rhs.filename_;
      this->contents_ = rhs.contents_;
      if (rhs.icon_ != nullptr) {
         this->icon_ = new int [ICON_DIM];
         std::copy(rhs.icon_, rhs.icon_ + ICON_DIM, this->icon_);
      } else {
         this->icon_ = nullptr;
      }
   }
   return *this;
} // Copy Assignment

File::File(File&& rhs) : filename_(std::move(rhs.filename_)), contents_(std::move(rhs.contents_)), icon_(rhs.icon_) {
   rhs.icon_ = nullptr;
} // Move Constructor

File& File::operator=(File&& rhs) {
   if (this != &rhs) {
      delete [] this->icon_;

      this->filename_ = std::move(rhs.filename_);
      this->contents_ = std::move(rhs.contents_);
      this->icon_ = rhs.icon_;

      rhs.icon_ = nullptr;
   }

   return *this;
} // Move Assignment

File::~File() {
   delete [] icon_;
} // Destructor