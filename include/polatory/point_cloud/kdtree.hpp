// Copyright (c) 2016, GSI and The Polatory Authors.

#pragma once

#include <memory>
#include <utility>
#include <vector>

#include <polatory/geometry/point3d.hpp>

namespace polatory {
namespace point_cloud {

class kdtree {
public:
  using indices_and_distances = std::pair<std::vector<size_t>, std::vector<double>>;

  kdtree(const geometry::points3d& points, bool use_exact_search);

  ~kdtree();

  indices_and_distances knn_search(const geometry::point3d& point, size_t k) const;

  indices_and_distances radius_search(const geometry::point3d& point, double radius) const;

private:
  class impl;

  std::unique_ptr<impl> pimpl_;
};

}  // namespace point_cloud
}  // namespace polatory
