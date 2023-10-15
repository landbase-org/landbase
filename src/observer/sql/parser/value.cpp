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
// Created by WangYunlai on 2023/06/28.
//

#include "sql/parser/value.h"
#include "common/lang/comparator.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "storage/field/field.h"
#include <cmath>
#include <cstdio>
#include <sstream>

// 这里的顺序必须和AttrType的顺序相同
const char *ATTR_TYPE_NAME[] = {"undefined", "chars", "dates", "ints", "floats", "booleans"};

const char *attr_type_to_string(AttrType type)
{
  if (type >= UNDEFINED && type <= FLOATS) {
    return ATTR_TYPE_NAME[type];
  }
  return "unknown";
}
AttrType attr_type_from_string(const char *s)
{
  for (unsigned int i = 0; i < sizeof(ATTR_TYPE_NAME) / sizeof(ATTR_TYPE_NAME[0]); i++) {
    if (0 == strcmp(ATTR_TYPE_NAME[i], s)) {
      return (AttrType)i;
    }
  }
  return UNDEFINED;
}

int32_t convert_string_to_date(const char *str_data)
{
  int year, month, day;
  // TODO: add check to too long date str to improve the robust of code
  // Example: 20000000000000000000-001010111111111111-22222222222222222
  sscanf(str_data, "%d-%d-%d", &year, &month, &day);

  auto check_date = [&]() -> bool {
    if (year > 3999 || year < 0 || month > 12 || month < 1 || day < 0 || day > 31)
      return false;
    int m_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) {
      // leap year
      if (day <= m_days[month - 1] || (month == 2 && day == 29))
        return true;
      return false;
    } else {
      // not leap year
      if (day <= m_days[month - 1])
        return true;
      return false;
    }
  };

  if (!check_date()) {
    return -1;
  }
  int32_t ans = year * 10000 + month * 100 + day;
  return ans;
}

Value::Value(int val) { set_int(val); }

Value::Value(float val) { set_float(val); }

Value::Value(bool val) { set_boolean(val); }

Value::Value(const char *s, int len /*= 0*/) { set_string(s, len); }

void Value::set_data(char *data, int length)
{
  switch (attr_type_) {
    case CHARS: {
      set_string(data, length);
    } break;
    case INTS: {
      num_value_.int_value_ = *(int *)data;
      length_               = length;
    } break;
    case FLOATS: {
      num_value_.float_value_ = *(float *)data;
      length_                 = length;
    } break;
    case BOOLEANS: {
      num_value_.bool_value_ = *(int *)data != 0;
      length_                = length;
    } break;
    case DATES: {
      // TODO: date(aka int32_t) size is 4,
      ASSERT(length == 4, "SHOULD CHANGE TO int32_t BEFORE SET_DATE");
      set_date(*(int32_t *)data);
      length_ = length;
    } break;
    default: {
      LOG_WARN("unknown data type: %d", attr_type_);
    } break;
  }
}
void Value::set_int(int val)
{
  attr_type_            = INTS;
  num_value_.int_value_ = val;
  length_               = sizeof(val);
}

void Value::set_float(float val)
{
  attr_type_              = FLOATS;
  num_value_.float_value_ = val;
  length_                 = sizeof(val);
}
void Value::set_boolean(bool val)
{
  attr_type_             = BOOLEANS;
  num_value_.bool_value_ = val;
  length_                = sizeof(val);
}
void Value::set_string(const char *s, int len /*= 0*/)
{
  attr_type_ = CHARS;
  if (len > 0) {
    len = strnlen(s, len);
    str_value_.assign(s, len);
  } else {
    str_value_.assign(s);
  }
  length_ = str_value_.length();
}

void Value::set_date(Value::date data)
{
  // using int32_t as date , length is 4
  attr_type_             = DATES;
  num_value_.date_value_ = data;
  length_                = 4;
}

void Value::set_value(const Value &value)
{
  switch (value.attr_type_) {
    case INTS: {
      set_int(value.get_int());
    } break;
    case FLOATS: {
      set_float(value.get_float());
    } break;
    case CHARS: {
      set_string(value.get_string().c_str());
    } break;
    case BOOLEANS: {
      set_boolean(value.get_boolean());
    } break;
    case DATES: {
      set_date(value.get_date());
    } break;
    case UNDEFINED: {
      ASSERT(false, "got an invalid value type");
    } break;
  }
}

const char *Value::data() const
{
  switch (attr_type_) {
    case CHARS: {
      return str_value_.c_str();
    } break;
    case DATES: {
      return (const char *)&num_value_.date_value_;
    } break;
    default: {
      return (const char *)&num_value_;
    } break;
  }
}

std::string Value::to_string() const
{
  std::stringstream os;
  switch (attr_type_) {
    case INTS: {
      os << num_value_.int_value_;
    } break;
    case FLOATS: {
      os << common::double_to_str(num_value_.float_value_);
    } break;
    case BOOLEANS: {
      os << num_value_.bool_value_;
    } break;
    case CHARS: {
      os << str_value_;
    } break;
    case DATES: {
      os << common::date_to_string(num_value_.date_value_);
    } break;
    default: {
      LOG_WARN("unsupported attr type: %d", attr_type_);
    } break;
  }
  return os.str();
}

/**
 * @brief 比较两个Value
 *
 * @param comp_op 比较符号
 * @param other 另一个Value
 * @return bool 比较是否成功
 */
bool Value::compare(const CompOp &comp_op, const Value &other) const
{
  int cmp_result = 0;
  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
      case INTS: {
        cmp_result = common::compare_int((void *)&this->num_value_.int_value_, (void *)&other.num_value_.int_value_);
      } break;
      case FLOATS: {
        cmp_result =
            common::compare_float((void *)&this->num_value_.float_value_, (void *)&other.num_value_.float_value_);
      } break;
      case CHARS: {
        if (comp_op == LIKE || comp_op == NOT_LIKE) {
          cmp_result = common::string_match(
              (void *)this->str_value_.c_str(),
              this->str_value_.length(),
              (void *)other.str_value_.c_str(),
              other.str_value_.length()
          );
        } else {
          cmp_result = common::compare_string(
              (void *)this->str_value_.c_str(),
              this->str_value_.length(),
              (void *)other.str_value_.c_str(),
              other.str_value_.length()
          );
        }
      } break;
      case DATES: {
        cmp_result = common::compare_date((void *)&num_value_.date_value_, (void *)&other.num_value_.date_value_);
      } break;
      case BOOLEANS: {
        cmp_result = common::compare_int((void *)&this->num_value_.bool_value_, (void *)&other.num_value_.bool_value_);
      }
      default: {
        LOG_WARN("unsupported type: %d", this->attr_type_);
      }
    }
  } else if (this->attr_type_ == INTS && other.attr_type_ == FLOATS) {
    float this_data = this->num_value_.int_value_;
    cmp_result      = common::compare_float((void *)&this_data, (void *)&other.num_value_.float_value_);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == INTS) {
    float other_data = other.num_value_.int_value_;
    cmp_result       = common::compare_float((void *)&this->num_value_.float_value_, (void *)&other_data);
  } else if (this->attr_type_ == DATES && other.attr_type_ == CHARS) {
    int32_t temp = convert_string_to_date(other.data());
    if (temp == -1)
      cmp_result = -1;
    Value *change = const_cast<Value *>(&other);
    change->set_date(temp);
    cmp_result = common::compare_date((void *)&this->num_value_.date_value_, (void *)&other.num_value_.date_value_);
  } else if ((this->attr_type_ == FLOATS || this->attr_type_ == INTS) && other.attr_type_ == CHARS) {
    Value self, oppsite = *this, *other;
    self.type_cast(FLOATS);
    oppsite.type_cast(FLOATS);
    cmp_result = common::compare_float((void *)&self.num_value_.float_value_, (void *)&oppsite.num_value_.float_value_);
  } else if (this->attr_type_ == CHARS && (other.attr_type_ == INTS || other.attr_type_ == FLOATS)) {
    Value self = *this, oppsite = other;
    self.type_cast(FLOATS);
    oppsite.type_cast(FLOATS);
    cmp_result = common::compare_float((void *)&self.num_value_.float_value_, (void *)&oppsite.num_value_.float_value_);
  } else {
    LOG_WARN("not supported,Type Error");
    return false;
  }

  switch (comp_op) {
    case EQUAL_TO: return 0 == cmp_result;
    case LESS_EQUAL: return cmp_result <= 0;
    case NOT_EQUAL: return cmp_result != 0;
    case LESS_THAN: return cmp_result < 0;
    case GREAT_EQUAL: return cmp_result >= 0;
    case GREAT_THAN: return cmp_result > 0;
    case LIKE: return cmp_result == 0;
    case NOT_LIKE: return cmp_result != 0;
    default: break;
  }

  return false;  // TODO return rc?
}

int Value::get_int() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        return (int)(std::stol(str_value_));
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to number. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0;
      }
    }
    case INTS: {
      return num_value_.int_value_;
    }
    case FLOATS: {
      return (int)(num_value_.float_value_);
    }
    case BOOLEANS: {
      return (int)(num_value_.bool_value_);
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

float Value::get_float() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        return std::stof(str_value_);
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0.0;
      }
    } break;
    case INTS: {
      return float(num_value_.int_value_);
    } break;
    case FLOATS: {
      return num_value_.float_value_;
    } break;
    case BOOLEANS: {
      return float(num_value_.bool_value_);
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

std::string Value::get_string() const { return this->to_string(); }

bool Value::get_boolean() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        float val = std::stof(str_value_);
        if (val >= EPSILON || val <= -EPSILON) {
          return true;
        }

        int int_val = std::stol(str_value_);
        if (int_val != 0) {
          return true;
        }

        return !str_value_.empty();
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float or integer. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return !str_value_.empty();
      }
    } break;
    case INTS: {
      return num_value_.int_value_ != 0;
    } break;
    case FLOATS: {
      float val = num_value_.float_value_;
      return val >= EPSILON || val <= -EPSILON;
    } break;
    case BOOLEANS: {
      return num_value_.bool_value_;
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return false;
    }
  }
  return false;
}

Value::date Value::get_date() const { return num_value_.date_value_; }

/**
 * @brief 完成类型转换的函数
 *
 * @param target
 * @return true 转换成功
 * @return false 转换失败
 */
bool Value::type_cast(const AttrType target)
{
  if (attr_type_ == target)
    return true;
  std::stringstream ss;
  switch (target) {
    case INTS: {
      int temp{0};
      if (attr_type_ == FLOATS) {
        temp = static_cast<int>(round(num_value_.float_value_));
        set_int(temp);
        return true;
      } else if (attr_type_ == CHARS) {
        ss << str_value_;
        ss >> temp;
        if (ss.fail())
          temp = 0;
        set_int(temp);
        str_value_.clear();
        return true;
      }
    }
    case FLOATS: {
      float temp{0.0f};
      if (attr_type_ == INTS) {
        temp = static_cast<float>(num_value_.int_value_);
        set_float(temp);
        return true;
      } else if (attr_type_ == CHARS) {
        ss << str_value_;
        ss >> temp;
        if (ss.fail())
          temp = 0.0f;
        set_float(temp);
        return true;
      }
    }
    case CHARS: {
      std::string res;
      if (attr_type_ == INTS) {
        ss << num_value_.int_value_;
        ss >> res;
        set_string(res.c_str());
        return true;
      }
      if (attr_type_ == FLOATS) {
        ss << num_value_.float_value_;
        ss >> res;
        set_string(res.c_str());
        return true;
      }
    }
    default: {
      LOG_WARN("Typecast Failed");
      return false;
    }
  }
}