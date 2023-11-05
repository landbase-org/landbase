#pragma once

#include <string>
#include <unordered_map>

/**
 * @description: 聚合类型
 */
enum AggreType
{
  AGGRE_NONE,
  AGGRE_MAX,
  AGGRE_MIN,
  AGGRE_COUNT,
  AGGRE_COUNT_ALL,
  AGGRE_AVG,
  AGGRE_SUM
};
static std::string aggreType2str(AggreType aggre)
{
  static std::unordered_map<AggreType, std::string> m{
      {AGGRE_NONE, "NONE"},
      {AGGRE_MAX, "MAX"},
      {AGGRE_MIN, "MIN"},
      {AGGRE_COUNT, "COUNT"},
      {AGGRE_COUNT_ALL, "COUNT"},
      {AGGRE_AVG, "AVG"},
      {AGGRE_SUM, "SUM"},
  };
  return m.at(aggre);
}