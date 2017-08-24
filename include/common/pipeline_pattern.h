/**
* @version		GrPPI v0.3
* @copyright		Copyright (C) 2017 Universidad Carlos III de Madrid. All rights reserved.
* @license		GNU/GPL, see LICENSE.txt
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You have received a copy of the GNU General Public License in LICENSE.txt
* also available in <http://www.gnu.org/licenses/gpl.html>.
*
* See COPYRIGHT.txt for copyright notices and details.
*/
#ifndef GRPPI_COMMON_PIPELINE_PATTERN_H
#define GRPPI_COMMON_PIPELINE_PATTERN_H

#include <type_traits>

namespace grppi {

/**
\brief Representation of pipeline pattern.
Represents a pipeline with multiple chained transformers.
\tparam Transformer Callable type for the first transformer.
\tparam OtherTransformers Callable types for the rest of transformers.
*/
template <typename ... Transformers>
class pipeline_t {
public:

  using transformers_type = std::tuple<Transformers...>;

  /**
  \brief Constructs a pipeline with several transformers.
  \param t Transformer for the first stage of the pipeline.
  \param others Rest of transformers for the other stages of the pipeline.
  */
  pipeline_t(Transformers && ... others) noexcept :
    transformers_{others...}
  {}

  /**
  \brief Invokes a trasnformer from the pipeline.
  \tparam I
  */
  template <std::size_t I, typename T>
  auto invoke(T && item) const {
    auto f = std::get<I>(transformers_);
    return f(std::forward<T>(item));
  }

private:
  std::tuple<Transformers...> transformers_;
};

namespace internal {

template<typename T>
struct is_pipeline : std::false_type {};

template <typename ... T>
struct is_pipeline<pipeline_t<T...>> :std::true_type {};

} // namespace internal

template <typename T>
static constexpr bool is_pipeline = internal::is_pipeline<std::decay_t<T>>();

template <typename T>
using requires_pipeline = typename std::enable_if_t<is_pipeline<T>, int>;

}

#endif