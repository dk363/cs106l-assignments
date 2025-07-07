/*
 * CS106L Assignment 1: SimpleEnroll
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 *
 * Welcome to Assignment 1 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 * Students must implement: parse_csv, write_courses_offered,
 * write_courses_not_offered
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const std::string COURSES_OFFERED_PATH = "student_output/courses_offered.csv";
const std::string COURSES_NOT_OFFERED_PATH = "student_output/courses_not_offered.csv";

/**
 * Represents a course a student can take in ExploreCourses.
 * You must fill in the types of the fields in this struct.
 * Hint: Remember what types C++ streams work with?!
 */
struct Course {
  /* STUDENT TODO */ 
  std::string title;
  /* STUDENT TODO */ 
  std::string number_of_units;
  /* STUDENT TODO */ 
  std::string quarter;
};

/**
 * (STUDENT TODO) Look at how the main function (at the bottom of this file)
 * calls `parse_csv`, `write_courses_offered`, and `write_courses_not_offered`.
 * Modify the signatures of these functions so that they work as intended, and then delete this
 * comment!
 */

/**
 * Note:
 * We need to #include utils.cpp _after_ we declare the Course struct above
 * so that the code inside utils.cpp knows what a Course is.
 * Recall that #include literally copies and pastes file contents.
 */
#include "utils.cpp"

/**
 * This function should populate the `courses` vector with structs of type
 * `Course`. We want to create these structs with the records in the courses.csv
 * file, where each line is a record!
 *
 * Hints:
 * 1) Take a look at the split function we provide in utils.cpp
 * 2) Each LINE is a record! *this is important, so we're saying it again :>)*
 * 3) The first line in the CSV defines the column names, so you can ignore it!
 *
 * @param filename The name of the file to parse.
 * @param courses  A vector of courses to populate.
 */
void parse_csv(std::string filename, std::vector<Course>& courses) {
  std::ifstream ifs(filename);
  if (!ifs.is_open()) {
    std::cerr << "error: could not open file";
    return;
  }
  std::string header_line;
  std::getline(ifs, header_line);

  std::string line;
  while (std::getline(ifs, line)) {
    std::vector<std::string> tokens = split(line, ',');
    if (tokens.size() >= 3) {
      Course course;
      course.title = tokens[0];
      course.number_of_units = tokens[1];
      course.quarter = tokens[2];
      courses.push_back(course);
    }
  }
  /* (STUDENT TODO) Your code goes here... */
}

/**
 * 该函数有两个要求：
 *
 * 1）将“已开设”的课程写入文件
 *    "student_output/courses_offered.csv"
 *
 * 2）从 `all_courses` 向量中删除这些“已开设”的课程。
 *    重要：请在写入文件之后再进行删除操作！
 *
 * 提示：
 * 1）记录下你需要删除的课程！
 * 2）使用我们提供的 delete_elem_from_vector 函数来删除！
 * 3）记得在输出文件的开头写入 CSV 的列标题！
 *    可以参考 courses.csv 文件中的格式。
 *
 * @param all_courses 一个包含所有课程的向量，由 `parse_csv` 函数生成。
 *                    此向量会在函数中被修改 —— 删除所有“已开设”的课程。
 */
void write_courses_offered(std::vector<Course>& all_courses) {
  std::ofstream ofs("student_output/courses_offered.csv");
  ofs << "Title,Number of Units,Quarter\n";

  std::vector<Course> to_delete;
  for (const Course& course : all_courses) {
    if (course.quarter != "null") {
      ofs << course.title << ',' << course.number_of_units << ',' << course.quarter << '\n';
      to_delete.push_back(course);
    }
  }

  for (const Course& course : to_delete) {
    delete_elem_from_vector(all_courses, course);
  }
  /* (STUDENT TODO) Your code goes here... */
}

/**
 * 此函数将“未开设”的课程写入文件
 * "student_output/courses_not_offered.csv"。
 *
 * 该函数总是在 `write_courses_offered` 函数之后被调用。
 *
 * 由于在 `write_courses_offered` 函数中你已经从 `all_courses` 中删除了已开设的课程，
 * 所以此时传入的 `unlisted_courses` 向量自然只包含“未开设”的课程。
 *
 * 提示：这个函数的实现应该与 `write_courses_offered` 非常相似。
 *
 * @param unlisted_courses 一个只包含未开设课程的向量。
 */
void write_courses_not_offered(std::vector<Course> unlisted_courses) {
  std::ofstream ofs("student_output/courses_not_offered.csv");
  ofs << "Title,Number of Units,Quarter\n";

  std::vector<Course> to_add;
  for (const Course& course : unlisted_courses) {
    ofs << course.title << ',' << course.number_of_units << ',' << course.quarter << '\n';
  }
  /* (STUDENT TODO) Your code goes here... */
}

int main() {
  /* Makes sure you defined your Course struct correctly! */
  static_assert(is_valid_course<Course>, "Course struct is not correctly defined!");

  std::vector<Course> courses;
  parse_csv("courses.csv", courses);

  /* Uncomment for debugging... */
  // print_courses(courses);

  write_courses_offered(courses);
  write_courses_not_offered(courses);

  return run_autograder();
}