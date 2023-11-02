#pragma once

// 为了方便在Value里面使用CompOp, 避免循环依赖，所以把CompOp单独拿出来

/**
 * @brief 描述比较运算符
 * @ingroup SQLParser
 */
enum CompOp
{
  EQUAL_TO,     ///< "="
  LESS_EQUAL,   ///< "<="
  NOT_EQUAL,    ///< "<>"
  LESS_THAN,    ///< "<"
  GREAT_EQUAL,  ///< ">="
  GREAT_THAN,   ///< ">"
  LIKE,         ///< LIKE
  NOT_LIKE,     ///< NOT LIKE
  IS,           ///< 目前仅用于判断是否为 null
  IS_NOT,       ///< 目前仅用于判断是否为 null
  IN,           ///< IN
  NOT_IN,       ///< NOT IN
  EXISTS,       ///< EXISTS
  NOT_EXISTS,   ///< NOT EXISTS
  NO_OP,        ///< no condition
};