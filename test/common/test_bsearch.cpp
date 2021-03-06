// Copyright (c) 2016, GSI and The Polatory Authors.

#include <vector>

#include <gtest/gtest.h>

#include <polatory/common/bsearch.hpp>

using polatory::common::bsearch_eq;
using polatory::common::bsearch_ge;
using polatory::common::bsearch_gt;
using polatory::common::bsearch_le;
using polatory::common::bsearch_lt;

TEST(bsearch, trivial) {
  std::vector<int> v = { 1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 6 };
  const int Zero = 0;
  const int Three = 3;
  const int Five = 5;
  const int Seven = 7;


  auto lt = bsearch_lt(v.begin(), v.end(), Zero);
  EXPECT_EQ(v.end(), lt);

  auto le = bsearch_le(v.begin(), v.end(), Zero);
  EXPECT_EQ(v.end(), le);

  auto gt = bsearch_gt(v.begin(), v.end(), Zero);
  EXPECT_EQ(v.begin(), gt);

  auto ge = bsearch_ge(v.begin(), v.end(), Zero);
  EXPECT_EQ(v.begin(), ge);

  auto eq = bsearch_eq(v.begin(), v.end(), Zero);
  EXPECT_EQ(v.end(), eq);


  lt = bsearch_lt(v.begin(), v.end(), Three);
  EXPECT_EQ(v.begin() + 2, lt);

  le = bsearch_le(v.begin(), v.end(), Three);
  EXPECT_EQ(v.begin() + 6, le);

  gt = bsearch_gt(v.begin(), v.end(), Three);
  EXPECT_EQ(v.begin() + 7, gt);

  ge = bsearch_ge(v.begin(), v.end(), Three);
  EXPECT_EQ(v.begin() + 3, ge);

  eq = bsearch_eq(v.begin(), v.end(), Three);
  EXPECT_EQ(Three, *eq);


  lt = bsearch_lt(v.begin(), v.end(), Five);
  EXPECT_EQ(v.begin() + 9, lt);

  le = bsearch_le(v.begin(), v.end(), Five);
  EXPECT_EQ(v.begin() + 9, le);

  gt = bsearch_gt(v.begin(), v.end(), Five);
  EXPECT_EQ(v.begin() + 10, gt);

  ge = bsearch_ge(v.begin(), v.end(), Five);
  EXPECT_EQ(v.begin() + 10, ge);

  eq = bsearch_eq(v.begin(), v.end(), Five);
  EXPECT_EQ(v.end(), eq);


  lt = bsearch_lt(v.begin(), v.end(), Seven);
  EXPECT_EQ(v.begin() + 10, lt);

  le = bsearch_le(v.begin(), v.end(), Seven);
  EXPECT_EQ(v.begin() + 10, le);

  gt = bsearch_gt(v.begin(), v.end(), Seven);
  EXPECT_EQ(v.end(), gt);

  ge = bsearch_ge(v.begin(), v.end(), Seven);
  EXPECT_EQ(v.end(), ge);

  eq = bsearch_eq(v.begin(), v.end(), Seven);
  EXPECT_EQ(v.end(), eq);
}
