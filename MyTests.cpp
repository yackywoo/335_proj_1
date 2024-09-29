#include "File.hpp"
#include "Folder.hpp"
#include "InvalidFormatException.hpp"
#include <iostream>
#include <cassert>
#include <vector>


int main () {
    std::cout << "========< EMPTY CONSTRUCTOR TEST >========" << std::endl;
    //default constructor test
    
    File testfile;
    assert(testfile.getName() == "NewFile.txt");
    assert(testfile.getContents() == "");
    assert(testfile.getIcon() == nullptr);
    std::cout << testfile << std::endl;

    std::cout << "========< NON-EMPTY CONSTRUCTOR TEST >========" << std::endl;
    //parameter constructor test

    int* thing = nullptr; 
    File otherfile ("abc.123", "12345678901", thing); //works, 11 bytes string
    std::cout << otherfile << std::endl;

    std::cout << "========< INVALID NAME TEST >========" << std::endl;
    //filename validation testing

    std::vector<std::string> badnames {"bad.name.here", "!badnamehere", "badnamehere!", "b$ad.namehere", "badnamehe.re4!"};
    for (auto i = 0 ; i < badnames.size() ; ++i) {
        try {
            File(badnames[i],"",nullptr);
            std::cout << "badname worked" << std::endl;
        } catch (InvalidFormatException) {
            std::cerr << "badname didn't work" << std::endl;
        }
    }
    
    std::cout << "========< COPY CONSTRUCTOR TEST >========" << std::endl;
    //copy constructor test
    
    File copycat(otherfile);
    std::cout << copycat << std::endl;
    assert(copycat.getName() == otherfile.getName());
    assert(copycat.getContents() == otherfile.getContents());
    assert(copycat.getIcon() == otherfile.getIcon());
    assert(copycat.getSize() == otherfile.getSize());

    std::cout << "========< COPY ASSIGNMENT TEST >========" << std::endl;
    //copy assignment test

    copycat = testfile;
    std::cout << copycat << std::endl;
    assert(copycat.getName() == testfile.getName());
    assert(copycat.getContents() == testfile.getContents());
    assert(copycat.getIcon() == testfile.getIcon());
    assert(copycat.getSize() == testfile.getSize());

    std::cout << "========< MOVE CONSTRUCTOR TEST >========" << std::endl;
    //move constructor test

    File movetest (std::move(otherfile));
    std::cout << movetest << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << otherfile << std::endl;
    assert(otherfile.getName() == "");
    assert(otherfile.getContents() == "");
    assert(otherfile.getIcon() == nullptr);
    assert(otherfile.getSize() == 0);

    std::cout << "========< MOVE ASSIGNMENT TEST >========" << std::endl;
    //move assignment test

    otherfile = std::move(movetest);
    std::cout << movetest << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << otherfile << std::endl;
    assert(movetest.getName() == "");
    assert(movetest.getContents() == "");
    assert(movetest.getIcon() == nullptr);
    assert(movetest.getSize() == 0);

    std::cout << "========================================" << std::endl;
    std::cout << "===========< FOLDER TESTING >===========" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;

    //otherfile -> abc.123
    //testfile -> empty file

    std::cout << "===========< CONSTRUCTOR TESTING >===========" << std::endl;
    Folder myFolder;
    std::string name = myFolder.getName();
    std::cout << name << std::endl;
    myFolder.display();

    Folder otherFolder("OldFolder");
    std::string name1 = otherFolder.getName();
    std::cout << name1 << std::endl;
    otherFolder.display();

    std::cout << "===========< INSERT TESTING >===========" << std::endl;
    File a ("a");
    File b ("b");
    File c ("c");
    File d ("d");
    File e ("e");
    File f ("f");
    myFolder.addFile(a);
    myFolder.addFile(b);
    myFolder.addFile(c);
    myFolder.addFile(d);
    myFolder.addFile(e);
    myFolder.addFile(f);
    myFolder.display();

    std::cout << "===========< REMOVE TESTING >===========" << std::endl;
    std::cout << std::boolalpha;
    std::cout << myFolder.removeFile("d.txt") << std::endl;
    std::cout << myFolder.removeFile("f.txt") << std::endl;
    std::cout << myFolder.removeFile("a.txt") << std::endl;
    std::cout << myFolder.removeFile("a") << std::endl;
    std::cout << myFolder.removeFile("b.tx") << std::endl;
    std::cout << myFolder.removeFile("") << std::endl;
    myFolder.display();

    std::cout << "===========< MOVE TESTING >===========" << std::endl;
    myFolder.moveFileTo("b.txt", otherFolder);
    File g ("g");
    File z ("z");
    File m ("m");
    File Q ("Q");
    otherFolder.addFile(g);
    otherFolder.addFile(Q);
    otherFolder.addFile(z);
    otherFolder.addFile(m);
    myFolder.display();
    otherFolder.display();
    std::cout << "----------------------------------------" << std::endl;
    std::cout << otherFolder.moveFileTo("Q.txt", myFolder) << std::endl; //move back to other folder, true
    std::cout << otherFolder.moveFileTo("m.txt", otherFolder) << std::endl; //move to self, true
    std::cout << otherFolder.moveFileTo("r", myFolder) << std::endl; //move fake file, false
    std::cout << "----------------------------------------" << std::endl;
    myFolder.display();
    otherFolder.display();
    
    std::cout << "===========< COPY TESTING >===========" << std::endl;
}