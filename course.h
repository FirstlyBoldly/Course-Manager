#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <unordered_map>
#include <type_traits>
#include <fstream>
#include <sstream>

class Syllabus
{
private:
    int lessonCount;
    int credits;
    std::string lessonName;
    std::string lessonTeacher;
    std::string endOfTermExam;
    std::string requiredSubmissionRate;
    std::string requiredAttendanceRate;
    friend class CSV;

public:
    Syllabus();

    Syllabus(const std::string& inputLessonName, const std::string& inputLessonTeacher, const int& inputLessonCount, const int& inputCredits, const std::string& inputEndOfTermExam,
        const std::string& inputRequiredAttendanceRate, const std::string& inputRequiredSubmissionRate);

    const std::string getLessonName() const;

    void changeLessonName();

    void changeLessonTeacher();

    void changeLessonCount();

    void changeCredits();

    void changeEndOfTermExam();

    void changeRequiredSubmissionRate();

    void printSyllabus() const;

    virtual ~Syllabus();
};

class Textbook
{
private:
    std::string textbookName;
    std::string extraNotes;
    friend class CSV;

public:
    Textbook();

    Textbook(const std::string& inputTextbook, const std::string& inputExtraNotes);

    void deleteTextbook();

    void addTextbook();

    void changeTextbookName();

    void addExtraNotes();

    void changeExtraNotes();

    void deleteExtraNotes();

    void printTextbook() const;

    virtual ~Textbook();
};

class Course : public Syllabus, public Textbook
{
private:
    int year, semester;
    friend class CSV;

public:
    Course();

    Course(const int yearInput, const int semesterInput,
        const std::string& inputLessonName, const std::string& inputLessonTeacher, const int& inputLessonCount, const int& inputCredits, const std::string& inputEndOfTermExam,
        const std::string& inputRequiredAttendanceRate, const std::string& inputRequiredSubmissionRate,
        const std::string& inputTextbook, const std::string& inputExtraNotes);
    Course(const int yearInput, const int semesterInput);

    void printCourse() const;

    ~Course();
};

class ModifyCourse
{
private:
    int year, semester, userSelection;
    std::string modifyLesson;
    std::vector<std::vector<std::unordered_map<std::string, Course>>>& ptrToModifySemesterMap;
    ModifyCourse(std::vector<std::vector<std::unordered_map<std::string, Course>>>& ptrToSemesterMap);

    void selectModification();

    void modifySyllabus();

    void modifyTextbook();

public:
    static ModifyCourse& Get(std::vector<std::vector<std::unordered_map<std::string, Course>>>& ptrToSemesterMap);

    ~ModifyCourse();
};

class DeleteCourse
{
private:
    int year, semester;
    std::string deleteLesson;
    DeleteCourse(std::vector<std::vector<std::unordered_map<std::string, Course>>>& ptrToSemesterMap);

public:
    static DeleteCourse& Get(std::vector<std::vector<std::unordered_map<std::string, Course>>>& ptrToSemesterMap);

    ~DeleteCourse();
};

class CSV
{
private:
    std::fstream courseSurfer;

public:
    static CSV& Get();
    void readCSV(std::vector<std::vector<std::unordered_map<std::string, Course>>>& ptrToSemesterMap);
    void storeCSV(std::vector<std::vector<std::unordered_map<std::string, Course>>>& ptrToSemesterMap);
    ~CSV();
};

std::string getString(const std::string& printStatement);
int getInteger(const std::string& printStatement);
bool getUserConfirmation(const std::string& printStatement);
template<typename T> void changeVariable(T &destination, const std::string& printStatement);
void getYearSemester(int& year, int& semester);
void initializeCourse(std::vector<std::vector<std::unordered_map<std::string, Course>>>& ptrToSemesterList);
void printSemesterCourses(std::vector<std::vector<std::unordered_map<std::string, Course>>>& ptrToSemesterMap, int& year, int& semester);
bool findCourse(std::vector<std::vector<std::unordered_map<std::string, Course>>>& ptrToSemesterMap, int& year, int& semester, std::string& searchLessonName);
