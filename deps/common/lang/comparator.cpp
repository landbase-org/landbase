/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by wangyunlai on 2021/6/11.
//

#include "common/defs.h"
#include <algorithm>
#include <regex>
#include <string.h>

namespace common {

int compare_int(void *arg1, void *arg2)
{
  int v1 = *(int *)arg1;
  int v2 = *(int *)arg2;

  if (v1 > v2) {
    return 1;
  } else if (v1 < v2) {
    return -1;
  } else {
    return 0;
  }
}

int compare_float(void *arg1, void *arg2)
{
  float v1  = *(float *)arg1;
  float v2  = *(float *)arg2;
  float cmp = v1 - v2;
  if (cmp > EPSILON) {
    return 1;
  }
  if (cmp < -EPSILON) {
    return -1;
  }
  return 0;
}

int compare_string(void *arg1, int arg1_max_length, void *arg2, int arg2_max_length)
{
  const char *s1     = (const char *)arg1;
  const char *s2     = (const char *)arg2;
  int         maxlen = std::min(arg1_max_length, arg2_max_length);
  int         result = strncmp(s1, s2, maxlen);
  if (0 != result) {
    return result;
  }

  if (arg1_max_length > maxlen) {
    return s1[maxlen] - 0;
  }

  if (arg2_max_length > maxlen) {
    return 0 - s2[maxlen];
  }
  return 0;
}

// TODO: 参考 oceanbase 的实现
/**
 * @brief
 * like 操作符用于在 WHERE 子句中搜索符合一定格式的字段。
 * '%'用于匹配零个到多个任意字符（英文单引号“'”除外），
 * '_'用于匹配一个任意字符（英文单引号“'”除外）。
 * 只考虑char类型的字段即可。
 *
 * @param arg1
 * @param arg1_max_length
 * @param arg2
 * @param arg2_max_length
 * @return int 0 代表匹配成功，其他代表失败
 */
int string_match(void *arg1, int arg1_max_length, void *arg2, int arg2_max_length)
{
  const char *s1 = (const char *)arg1;
  const char *s2 = (const char *)arg2;

  std::string regex_str;

  // % -> [^']*  _ -> [^']{1}
  for (int i = 0; i < arg2_max_length; ++i) {
    switch (s2[i]) {
      case '%': {
        regex_str += "[^']*";
      } break;
      case '_': {
        regex_str += "[^']{1}";
      } break;
      default: {
        regex_str += s2[i];
      }
    }
  }

  std::regex pattern(regex_str);
  bool       ok = std::regex_match(s1, pattern);
  return ok ? 0 : -1;
}

int compare_date(void *arg1, void *arg2)
{
  int32_t left  = *static_cast<int32_t *>(arg1);
  int32_t right = *static_cast<int32_t *>(arg2);

  if (left > right) {
    return 1;
  } else if (left < right) {
    return -1;
  } else {
    return 0;
  }
}

}  // namespace common
