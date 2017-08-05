/* Copyright 2017 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef ALPHABET_H
#define ALPHABET_H

#include <cassert>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <unordered_map>

class Alphabet {
public:
  Alphabet(const char *spec_file_path) {
    std::ifstream in(spec_file_path, std::ios::in);
    ReadFromFile(in);
    in.close();
  }

  bool IsBlankLabel(int label) const {
    // If label is not contained in this vocabulary
    // it must be a blank label
    return label == size;
  }

  bool IsSpaceLabel(int label) {
    return label_to_str[label].size() == 1 && label_to_str[label][0] == ' ';
  }

  std::string GetStringFromLabel(int label) {
    assert(label < size);
    return label_to_str[label];
  }

  int GetLabelFromString(std::string c) {
    return str_to_label[c];
  }

  int GetSize() const {
    return size;
  }

private:
  int size;
  std::unordered_map<int, std::string> label_to_str;
  std::unordered_map<std::string, int> str_to_label;

  void ReadFromFile(std::istream& is) {
    int label = 0;
    for (std::string line; std::getline(is, line); ++label) {
      label_to_str[label] = line;
      str_to_label[line] = label;
    }
    size = label;
  }

};

#endif //ALPHABET_H
