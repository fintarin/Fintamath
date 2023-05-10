#!/usr/bin/env python3

import sys
import re
from typing import Generator, TextIO

source_file_prefix = "SF:"
data_prefix = "DA:"
branch_data_prefix = "BRDA:"

condition_keywords = [
    " if ",
    " for ",
    " while ",
]
condition_operators = [
    " && ",
    " || ",
    " ? ",
]


def get_data_line_nums(source_file: TextIO) -> Generator[int, None, None]:
  for line_num, line in enumerate(source_file, 1):
    if not line:
      continue

    line = re.sub("\s+", "", line)

    if line != "{" and line != "}" and line != "};" and line.find(",//") == -1:
      yield line_num


def get_branch_data_line_nums(source_file: TextIO) -> Generator[int, None, None]:
  open_brackets_num = int(0)

  for line_number, line in enumerate(source_file, 1):
    if not line:
      continue

    line = re.sub("(\".*?\")|(\'.*?\')", "", line)

    if open_brackets_num > 0:
      open_brackets_num += get_brackets_diff(line)
      yield line_number
      continue

    condition_found = False

    for condition_keyword in condition_keywords:
      if line.find(condition_keyword) != -1:
        open_brackets_num += get_brackets_diff(line)

        if re.search("^.*if.+[^!<>=]=[^;=]+$", line) == None:
          condition_found = True

        break

    if condition_found:
      yield line_number
      continue

    for condition_keyword in condition_operators:
      if line.find(condition_keyword) != -1:
        condition_found = True
        break

    if condition_found:
      yield line_number
      continue


def get_brackets_diff(line: str) -> int:
  return line.count("(") - line.count(")")


def get_data_line_nums_from_file(source_file_name: str) -> set[int]:
  with open(source_file_name) as source_file:
    return set(get_data_line_nums(source_file))


def get_branch_data_line_nums_from_file(source_file_name: str) -> set[int]:
  with open(source_file_name) as source_file:
    return set(get_branch_data_line_nums(source_file))


def filter_lcov_info(lcov_file: TextIO) -> Generator[str, None, None]:
  source_data_line_nums = set[int]()
  source_branch_data_line_nums = set[int]()

  for lcov_line in lcov_file:
    if lcov_line.startswith(source_file_prefix):
      source_file_name = lcov_line[len(source_file_prefix): -1]
      source_data_line_nums = get_data_line_nums_from_file(source_file_name)
      source_branch_data_line_nums = get_branch_data_line_nums_from_file(source_file_name)
    else:
      prefix_len = int(0)
      source_line_nums = set[int]()

      if lcov_line.startswith(data_prefix):
        prefix_len = len(data_prefix)
        source_line_nums = source_data_line_nums
      elif lcov_line.startswith(branch_data_prefix):
        prefix_len = len(branch_data_prefix)
        source_line_nums = source_branch_data_line_nums

      if prefix_len > 0:
        source_line_num = int(lcov_line[prefix_len:].split(",")[0])
        if source_line_num not in source_line_nums:
          continue

    yield lcov_line


def print_filtered_lcov_info(lcov_file_name: str, out_file: TextIO) -> None:
  with open(lcov_file_name, encoding="utf-8", errors="backslashreplace") as lcov_file:
    for line in filter_lcov_info(lcov_file):
      print(line, end="", file=out_file)


if __name__ == "__main__":
  print_filtered_lcov_info(sys.argv[1], sys.stdout)
