template <typename T>
concept is_valid_course = requires(T t) {
  { T{"Standard C++ Programming", "1", "2023-2024 Winter"} };
  std::is_same_v<T, Course>;
};
