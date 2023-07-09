#ifndef UTILS_HPP
#define UTILS_HPP

#include "Defs.hpp"

bool isNum(std::string str);
bool isIp(std::string str);
bool isDir(const std::string &path);
void errorExit(const std::string &);

std::vector<std::string> split_string(const std::string &, const std::string &);
std::string getExtension(const std::string &);
std::string ft_strcut(const std::string &, char);
std::vector<std::string> ft_vectorcut(const std::vector<std::string> &, char);
std::string vectorJoin(const std::vector<std::string> &, char);
bool is_valid_path(const std::string &);
std::string getFileContent(const std::string &);
off_t getFileLength(const std::string &);
void handleSignals(int);
void warnMsg(const std::string &);
void updateMsg(const std::string &);

#endif