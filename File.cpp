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

File::File(const std::string& filename, const std::string& content, int* icon) {
   // if not empty, validate file name
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
      } 
      
      // Setting data members
      if (extension_exist == false) {
         filename_ = filename + ".txt";
      } else {
         filename_ = filename;
      }
   } else {
      //if empty then default
      filename_ = "NewFile.txt";
   }

   contents_ = content;
   icon_ = icon;
} // Constructor

size_t File::getSize() const {
   // every char within the string = 1 byte
   return contents_.size();
} // getSize

File::File(const File& copyMe) : filename_(copyMe.filename_), contents_(copyMe.contents_) {
   if (copyMe.icon_ != nullptr) {
      //deep copy icon_
      icon_ = new int [ICON_DIM];
      for (auto i = 0 ; i < ICON_DIM ; ++i) {
         icon_[i] = copyMe.icon_[i];
      }
   } else {
      icon_ = nullptr;
   }
} // Copy Constructor

File& File::operator=(const File& copyMe) {
   if (this != &copyMe) {
      delete [] this->icon_;

      this->filename_ = copyMe.filename_;
      this->contents_ = copyMe.contents_;
      if (copyMe.icon_ != nullptr) {
         this->icon_ = new int [ICON_DIM];
         for (auto i = 0 ; i < ICON_DIM ; ++i) {
            this->icon_[i] = copyMe.icon_[i];
         }
      } else {
         this->icon_ = nullptr;
      }
   }
   return *this;
} // Copy Assignment

File::File(File&& moveMe) : filename_(std::move(moveMe.filename_)), contents_(std::move(moveMe.contents_)), icon_(moveMe.icon_) {
   moveMe.icon_ = nullptr;
} // Move Constructor

File& File::operator=(File&& moveMe) {
   if (this != &moveMe) {
      delete [] this->icon_;

      this->filename_ = std::move(moveMe.filename_);
      this->contents_ = std::move(moveMe.contents_);
      this->icon_ = moveMe.icon_;

      moveMe.icon_ = nullptr;
   }

   return *this;
}

File::~File() {
   delete [] icon_;
} // Destructor