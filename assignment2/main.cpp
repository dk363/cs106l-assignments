/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <random>

std::string kYourName = "Kuangdi Xu"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
/**
  读取文件名并返回包含所有申请人姓名的集合。
  @param filename  要读取的文件名。
  文件的每一行代表一个申请人的姓名。
  @returns         从文件中读取的所有申请人姓名的集合。
  @remark 可自由更改此函数（及其下方函数）的返回类型为std::unordered_set。若进行此修改，
  请确保同时更改utils.h中的对应函数。
*/
std::set<std::string> get_applicants(std::string filename) {
  std::ifstream ifs(filename);
  if (!ifs.is_open()) {
    std::cerr << "error: could not open file";
    return std::set<std::string>{};
  }

  std::string line;
  std::set<std::string> applications;
  while (std::getline(ifs, line)) {
    applications.insert(line);
  }

  return applications;
}


std::string get_all_initials(const std::string& full_name) {
  std::string initial = "";
  bool new_word = true;

  for (char c : full_name) {
    if (std::isspace(c)) {
      new_word = true;
    } else if (new_word) {}
    initial += std::tolower(c);
    new_word = false;
  }

  return initial;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
/**
接收一组学生姓名的引用，并返回一个与给定学生姓名匹配的姓名队列。
  @param name      返回的姓名队列应与该姓名具有相同的首字母。
  @param students  学生姓名的集合。
  @return          一个包含指向每个匹配姓名指针的队列。
*/

std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  std::queue<const std::string*> ans;
  if (name.empty()) {
    return ans;
  }

  std::string name_all_initials = get_all_initials(name);

  for (const std::string &s : students) {
    if (s.empty()) {
      continue;
    }

    std::string student_all_initials = get_all_initials(s);

    if (student_all_initials == name_all_initials) {
      ans.push(&s);
    }
  }
  return ans;
}



/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
/**
接收一个指向潜在匹配对象的指针队列，并确定唯一真命天子/天女！
你可以按任意方式实现此函数，但请尝试做一些比简单pop()操作稍微复杂的事情。
  @param matches 包含潜在匹配对象的队列。
  @return        你命中注定的真爱。
若matches为空则返回"未找到匹配对象。"。
*/
std::string get_match(std::queue<const std::string*>& matches) {
  if (matches.empty()) {
    // 注意 报错要一模一样 句号也不要少
    return "NO MATCHES FOUND.";
  }

  std::size_t size = matches.size();

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, size - 1);

  int r = dist(gen);
  const std::string* result = nullptr;
  
  // deque 不支持随机访问 必须要一个一个遍历
  for (int i = 0; i < size; ++i) {
    const std::string* curr = matches.front();
    matches.pop();

    if (i == r) {
      result = curr;
    }

    matches.push(curr);
  }

  return result ? *result : "NO MATCHES FOUND.";
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
