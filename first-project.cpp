#include <iostream>
#include <vector>

//Typedef: a keyword which helps ordering huge datasets.
typedef std::vector<std::pair<std::string, int>> pairlist_t;

//Creating namespaces
namespace First 
{
    int x = 5;
}

namespace Second
{
    int x = 20;
}

int main()
{
    using namespace First;
    pairlist_t pairlist;

    /*
    int x; //Declaration
    x = 6; //Assignment
    */

    int w = 10;
    int y = 8;

    int sum = x + y + w;


        //Different types of variables:
        //1. Int (Short for integer, a whole number);
        int age = 12;
        int year = 2049;
        int days = 28;
        //2. Double (For storing decimal data);
        double price = 10.99; 
        double gpa = 6.9; 
        double temperature = 37.25;
        //3. Char (Stores a single character);
        char grade = 'A'; 
        char initial = 'W'; 
        char currency = '$';
        //4. Boolean (Determines true/false);
        bool studentauth = true; 
        bool nuclearw = false; 
        bool genauth = false;
        //5. String (An object demostrating a sequence of text)
        std::string name = "Jonathan"; 
        std::string city = "New York"; 
        std::string country = "Italy"; 

        //6. Calculating a circle's area and circumference:
        //Note: The keyword 'const' sets the variable fixed,
        //and does not allow someone else to modify it.
        const double PI = 3.141592;
        const int SPEED_LIGHT = 299654798;
        const int RESOLUTION = 1920 * 1080;
        int radius = 33;
        double circumference = 2 * PI * radius;

    

    //Output Section
    std::cout << "Hello " << name << '\n';
    std::cout << "The circumferance of your circle is: " << circumference << '\n';
    std::cout << x << '\n';
    
    return 0; //Code with no mistake/error.
}