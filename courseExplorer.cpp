#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <unordered_map>
#include <type_traits>
#include <fstream>
#include <sstream>
#include "course.h"

int main()
{
    std::vector<std::vector<std::unordered_map<std::string, Course>>> semesterList(4, std::vector<std::unordered_map<std::string, Course>>(2));
    CSV::Get().readCSV(semesterList);
    while (true)
    {
        int userSelection = getInteger("WELCOME\nTHIS IS THE OPERATING TERMINAL OF THE COURSE MANAGER\n\n1.) Add Course\n2.) Modify Course\n3.) Delete Course\n4.) Print Courses\n5.) <<<EXIT>>>\n\nMAKE YOUR SELECTION: ");
        std::cout << "\n";
        switch (userSelection)
        {
        case 1:
            {
                if (getUserConfirmation("Do you wish to add a new course[Y/N]: ")) initializeCourse(semesterList);
                break;
            }
        
        case 2:
            {
                ModifyCourse::Get(semesterList);
                break;
            }
        
        case 3:
            {
                DeleteCourse::Get(semesterList);
                break;
            }
        
        case 4:
            {           
                int year, semester;
                getYearSemester(year, semester);
                printSemesterCourses(semesterList, year, semester);
                break;
            }
        
        case 5:
            {
                if (getUserConfirmation("You have chosen to exit[Y/N]: "))
                {
                    CSV::Get().storeCSV(semesterList);
                    return 0;
                }
            }
        
        default:
            {
                std::cout << "<<<UNKNOWN COMMAND>>>\n\n";
                break;
            }
        }
    }

    return 0;
}
