#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <unordered_map>
#include <type_traits>
#include <fstream>
#include <sstream>
#include "course.h"

Syllabus::Syllabus() : requiredAttendanceRate("80% or above"), requiredSubmissionRate("80% or above")
{
    lessonName = getString("What is the name of this course? ");
    lessonTeacher = getString("Who will teach this course? ");
    lessonCount = getInteger("How many lessons will there be? ");
    credits = getInteger("How many credits is it worth? ");
    endOfTermExam = getString("Is there an end of term exam? ");
    std::cout << "\n";
}

Syllabus::Syllabus(const std::string& inputLessonName, const std::string& inputLessonTeacher, const int& inputLessonCount, const int& inputCredits, const std::string& inputEndOfTermExam,
    const std::string& inputRequiredAttendanceRate, const std::string& inputRequiredSubmissionRate)
    : lessonName(inputLessonName), lessonTeacher(inputLessonTeacher), lessonCount(inputLessonCount), credits(inputCredits), endOfTermExam(inputEndOfTermExam),
    requiredAttendanceRate(inputRequiredAttendanceRate), requiredSubmissionRate(inputRequiredSubmissionRate) {}

const std::string Syllabus::getLessonName() const { return lessonName; }

void Syllabus::changeLessonName() { changeVariable(lessonName, "change the \"Lesson Name\""); }

void Syllabus::changeLessonTeacher() { changeVariable(lessonTeacher, "change \"Lesson Teacher\""); }

void Syllabus::changeLessonCount() { changeVariable(lessonCount, "change \"Lesson Count\""); }

void Syllabus::changeCredits() { changeVariable(credits, "change \"Credits\""); }

void Syllabus::changeEndOfTermExam() { changeVariable(endOfTermExam, "change \"End Of Term Exam\" conditions"); }

void Syllabus::changeRequiredSubmissionRate() { changeVariable(requiredSubmissionRate, "change \"Required Submission Rate\""); }

void Syllabus::printSyllabus() const
{
    std::cout << "| COURSE NAME: " << lessonName
        << "\n| LESSON COUNT: " << lessonCount << "\tCREDITS: " << credits << "\tTEACHER: " << lessonTeacher
        << "\n|\n| END OF TERM EXAM: " << endOfTermExam << "\n| REQUIRED ATTENDANCE RATE: " << requiredAttendanceRate
        << "\n| REQUIRED SUBMISSION RATE: " << requiredSubmissionRate << "\n";
}

Syllabus::~Syllabus() {}

Textbook::Textbook() : textbookName("None"), extraNotes("None") {}

Textbook::Textbook(const std::string& inputTextbook, const std::string& inputExtraNotes) : textbookName(inputTextbook), extraNotes(inputExtraNotes) {}

void Textbook::deleteTextbook()
{
    textbookName = "None";
    extraNotes = "\0";
}

void Textbook::addTextbook() { changeVariable(textbookName, "add a \"Textbook\""); }

void Textbook::changeTextbookName() { changeVariable(textbookName, "change \"Textbook Name\""); }

void Textbook::addExtraNotes() { changeVariable(extraNotes, "add \"Extra Notes\""); }

void Textbook::changeExtraNotes() { changeVariable(extraNotes, "change \"Extra Notes\""); }

void Textbook::deleteExtraNotes() { extraNotes = "\0"; }

void Textbook::printTextbook() const
{
    std::cout << "| TEXTBOOK: " << textbookName << "\n";
    if (!extraNotes.empty())
    {
        std::cout <<  "| EXTRA NOTES: " << extraNotes << "\n";
    }
}

Textbook::~Textbook() {}

Course::Course() : Syllabus::Syllabus(), Textbook::Textbook() {}

Course::Course(const int yearInput, const int semesterInput) : year(yearInput), semester(semesterInput) {}

Course::Course(const int yearInput, const int semesterInput,
    const std::string& inputLessonName, const std::string& inputLessonTeacher, const int& inputLessonCount, const int& inputCredits, const std::string& inputEndOfTermExam,
    const std::string& inputRequiredAttendanceRate, const std::string& inputRequiredSubmissionRate,
    const std::string& inputTextbook, const std::string& inputExtraNotes)
    : year(yearInput), semester(semesterInput),
    Syllabus::Syllabus(inputLessonName, inputLessonTeacher, inputLessonCount, inputCredits, inputEndOfTermExam, inputRequiredAttendanceRate, inputRequiredSubmissionRate),
    Textbook::Textbook(inputTextbook, inputExtraNotes) {}

void Course::printCourse() const
{
    printSyllabus();
    printTextbook();
    std::cout << "\n";
}

Course::~Course() {}

void ModifyCourse::selectModification()
{
    while(true)
    {
        userSelection = getInteger("MODIFICATION SELECTION\n\n1.) Modify Syllabus\n2.) Modify Textbook\n3.) Return\n\nMAKE YOUR SELECTION: ");
        std::cout << "\n";
        switch (userSelection)
        {
        case 1:
            {
                modifySyllabus();
                break;
            }

        case 2:
            {
                modifyTextbook();
                break;
            }

        case 3:
            {
                return;
            }
        
        default:
            {
                std::cout << "<<<UNKNOWN COMMAND>>>\n\n";
                break;
            }
        }
    }
}

void ModifyCourse::modifySyllabus()
{
    while (true)
    {
        userSelection = getInteger("MODIFY THE SYLLABUS\n\n1.) Change Lesson Name\n2.) Change Teachers\n3.) Change Amount of Lessons\n4.) Change Credits\n5.) Change End of Term Exam\n6.) Change Submission Rate\n7.) Return\n\nMAKE YOUR SELECTION: ");
        std::cout << "\n";
        Course& modifySelectedCourse = ptrToModifySemesterMap[year - 1][semester - 1].at(modifyLesson);
        switch (userSelection)
        {
        case 1:
            {
                modifySelectedCourse.changeLessonName();
                break;
            }

        case 2:
            {
                modifySelectedCourse.changeLessonTeacher();
                break;
            }
        
        case 3:
            {
                modifySelectedCourse.changeLessonCount();
                break;
            }
        
        case 4:
            {
                modifySelectedCourse.changeCredits();
                break;
            }
        
        case 5:
            {
                modifySelectedCourse.changeEndOfTermExam();
                break;
            }
        
        case 6:
            {
                modifySelectedCourse.changeRequiredSubmissionRate();
                break;
            }
        
        case 7:
            {
                return;
            }
        
        default:
            {
                std::cout << "<<<UNKNOWN COMMAND>>>\n\n";
                userSelection = -1;
                break;
            }
        }
    }
}

void ModifyCourse::modifyTextbook()
{
    while (true)
    {
        userSelection = getInteger("MODIFY THE TEXTBOOK\n\n1.) Change Textbook\n2.) Delete Textbook\n3.) Change Notes\n4.) Delete Notes\n5.) Return\n\nMAKE YOUR SELECTION: ");
        std::cout << "\n";
        Course& modifySelectedCourse = ptrToModifySemesterMap[year - 1][semester - 1].at(modifyLesson);
        switch (userSelection)
        {
        case 1:
            {
                modifySelectedCourse.changeTextbookName();
                break;
            }

        case 2:
            {
                modifySelectedCourse.deleteTextbook();
                break;
            }
        
        case 3:
            {
                modifySelectedCourse.changeExtraNotes();
                break;
            }
        
        case 4:
            {
                modifySelectedCourse.deleteExtraNotes();
                break;
            }
        
        case 5:
            {
                return;
            }
        
        default:
            {
                std::cout << "<<<UNKNOWN COMMAND>>>\n\n";
                userSelection = -1;
                break;
            }
        }
    }
}

ModifyCourse::ModifyCourse(std::vector<std::vector<std::unordered_map<std::string, Course>>>& ptrToSemesterMap) : ptrToModifySemesterMap(ptrToSemesterMap)
{
    if (getUserConfirmation("Modify Course[Y/N]: ") == false) return;

    while (true)
    {
        getYearSemester(year, semester);
        printSemesterCourses(ptrToSemesterMap, year, semester);
        if (findCourse(ptrToModifySemesterMap, year, semester, modifyLesson))
        {
            std::cout << "Modify " << modifyLesson;
            if (getUserConfirmation("\nProceed[Y/N]: ") == true) selectModification();
            break;
        }
        else
        {
            return;
        }
    }
}

ModifyCourse& ModifyCourse::Get(std::vector<std::vector<std::unordered_map<std::string, Course>>>& ptrToSemesterMap)
{
    static ModifyCourse Instance(ptrToSemesterMap);
    return Instance;
}

ModifyCourse::~ModifyCourse() {}

DeleteCourse::DeleteCourse(std::vector<std::vector<std::unordered_map<std::string, Course>>>& ptrToSemesterMap)
{
    if (getUserConfirmation("You have chosen to delete a course\nProceed[Y/N]: ") == false) return;

    while(true)
    {
        getYearSemester(year, semester);
        printSemesterCourses(ptrToSemesterMap, year, semester);
        if (findCourse(ptrToSemesterMap, year, semester, deleteLesson))
        {
            std::cout << "Delete " << deleteLesson;
            if (getUserConfirmation("\nProceed[Y/N]: ")) 
            {
                ptrToSemesterMap[year - 1][semester - 1].erase(deleteLesson);
                return;
            }
            else
            {
                continue;
            }
        }
        else
        {
            return;
        }
    }
}

DeleteCourse& DeleteCourse::Get(std::vector<std::vector<std::unordered_map<std::string, Course>>>& ptrToSemesterMap)
{
    static DeleteCourse Instance(ptrToSemesterMap);
    return Instance;
}

DeleteCourse::~DeleteCourse() {}

void CSV::readCSV(std::vector<std::vector<std::unordered_map<std::string, Course>>>& ptrToSemesterMap)
{
    std::ifstream courseSurfer;
    courseSurfer.open("course_table.csv");
    if (courseSurfer.is_open())
    {
        std::string rowLine;
        std::vector<std::string> rowArray;
        int row = 0;
        while (std::getline(courseSurfer, rowLine))
        {
            if (row == 0)
            {
                row++;
                continue;
            }
            
            rowArray.clear();
            std::stringstream ss(rowLine);
            std::string insertToArray;
            while (std::getline(ss, insertToArray, ','))
            {
                rowArray.push_back(insertToArray);
            }

            Course initializeCourse(std::stoi(rowArray[0]), std::stoi(rowArray[1]), rowArray[2], rowArray[3], std::stoi(rowArray[4]), std::stoi(rowArray[5]), rowArray[6], rowArray[7], rowArray[8], rowArray[9], rowArray[10]);
            ptrToSemesterMap[initializeCourse.year - 1][initializeCourse.semester - 1].emplace(initializeCourse.lessonName, std::move(initializeCourse));
            row++;
        }
    }
    else
    {
        std::cout << "<<<CANNOT OPEN FILE>>>\n\n";
    }
}

void CSV::storeCSV(std::vector<std::vector<std::unordered_map<std::string, Course>>>& ptrToSemesterMap)
{
    std::ofstream storeFile("course_table.csv");
    storeFile << "Year,Semester,Course Name,Course Teacher,Lesson Amount,Credits,End of Term Exam,Required Attendance Rate,Required Submission Rate,Textbook Name,Extra Notes\n";
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (const auto& [name, courses] : ptrToSemesterMap[i][j])
            {
                storeFile << courses.year << ",";
                storeFile << courses.semester << ",";
                storeFile << courses.lessonName << ",";
                storeFile << courses.lessonTeacher << ",";
                storeFile << courses.lessonCount << ",";
                storeFile << courses.credits << ",";
                storeFile << courses.endOfTermExam << ",";
                storeFile << courses.requiredAttendanceRate << ",";
                storeFile << courses.requiredSubmissionRate << ",";
                storeFile << courses.textbookName << ",";
                storeFile << courses.extraNotes << "\n";
            }
        }
    }

    storeFile.close();
}

CSV& CSV::Get()
{
    static CSV Instance;
    return Instance;
}

CSV::~CSV() {}

std::string getString(const std::string& printStatement)
{
    bool alert;
    std::string stringInput;
    do
    {
        alert = false;
        std::cout << printStatement;
        std::getline(std::cin, stringInput);
        int spaceCount = 0;
        int stringLength = stringInput.length();
        for (int i = 0; i < stringLength; i++)
        {
            if (isspace(stringInput.at(i)))
            {
                spaceCount++;
            }
        }
        
        if (spaceCount == stringLength) alert = true;
    }
    while (alert == true);
    
    return stringInput;
}

int getInteger(const std::string& printStatement)
{
    std::string integerInput;
    bool alert, isNegativeInteger;
    do
    {
        alert = false;
        isNegativeInteger = false;
        integerInput = getString(printStatement);
        for (int i = 0; i < integerInput.length(); i++)
        {
            if (!isdigit(integerInput[i]))
            {
                if (integerInput[0] == '-')
                {
                    isNegativeInteger = true;
                    continue;
                }
                alert = true;
                break;
            }
        }
    } while (alert == true);

    int returnInteger;
    if (isNegativeInteger == false)
    {
        return returnInteger = std::stoi(integerInput);
    }
    else
    {
        integerInput.erase(0);
        returnInteger = std::stoi(integerInput);
        return returnInteger * (-1);
    }
}

bool getUserConfirmation(const std::string& printStatement)
{
    char userAnswer;
    do
    {
        std::cout << printStatement;
        std::cin >> userAnswer;
        std::cout << "\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    while (userAnswer != 'Y' && userAnswer != 'y' && userAnswer != 'N' && userAnswer != 'n');

    if (userAnswer == 'Y' || userAnswer == 'y')
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<typename T>
void changeVariable(T &destination, const std::string& printStatement)
{
    std::cout << "You have chosen to " + printStatement + "\n";
    if (getUserConfirmation("Proceed[Y/N]: ") == false) return;
    
    T newUserInput;
    if constexpr (std::is_same_v<T, int>)
    {
        newUserInput = getInteger("Input your new value here: ");
    }
    else if constexpr (std::is_same_v<T, std::string>)
    {
        newUserInput = getString("Input your new value here: ");
    }
    
    destination = newUserInput;
    std::cout << "\n";
}

void getYearSemester(int& year, int& semester)
{
    do
    {
        do
        {
            year = getInteger("Select your year: ");
        }
        while (year < 1 || year > 4);

        std::cout << "\n1.) First semester\n2.) Second semester\n";
        do
        {
            semester = getInteger("Select your semester: ");
        }
        while (semester != 1 && semester != 2);
            
        std::cout << "\nYou have chosen YEAR " << year << " SEMESTER " << semester << "\n";
    }
    while (getUserConfirmation("Proceed[Y/N]: ") == false);
}

void initializeCourse(std::vector<std::vector<std::unordered_map<std::string, Course>>>& ptrToSemesterList)
{
    int year, semester;
    getYearSemester(year, semester);

    Course newCourse(year, semester);
    ptrToSemesterList[year - 1][semester - 1].emplace(newCourse.getLessonName(), std::move(newCourse));

    std::cout << "<<<NEW COURSE ADDED>>>\n\n";
    newCourse.printCourse();
}

void printSemesterCourses(std::vector<std::vector<std::unordered_map<std::string, Course>>>& ptrToSemesterMap, int& year, int& semester)
{
    for (int i = year - 1; i < year; i++)
    {
        for (int j = semester - 1; j < semester; j++)
        {
            std::cout << "| YEAR: " << year << "\tSEMESTER: " << semester << "\n\n";
            for (const auto& [name, courses] : ptrToSemesterMap[i][j])
            {
                courses.printCourse();
            }
        }
    }
}

bool findCourse(std::vector<std::vector<std::unordered_map<std::string, Course>>>& ptrToSemesterMap, int& year, int& semester, std::string& searchLessonName)
{
    do
    {
        searchLessonName = getString("Input your course name: ");
        std::cout << "\n";

        auto& semesterCourses = ptrToSemesterMap[year - 1][semester - 1];
        if (semesterCourses.find(searchLessonName) != semesterCourses.end())
        {
            semesterCourses.at(searchLessonName).printCourse();
            return true;
        }
    }
    while (getUserConfirmation("Course not found\nTry Again[Y/N]: "));

    return false;
}
