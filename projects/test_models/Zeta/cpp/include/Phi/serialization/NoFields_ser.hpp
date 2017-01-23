#ifndef PHI_SERIALIZATION_NOFIELDS_SER_HPP
#define PHI_SERIALIZATION_NOFIELDS_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/serialization/split_free.hpp>
#include "Phi/types/NoFields.hpp"

BOOST_SERIALIZATION_SPLIT_FREE(Phi::NoFields)
namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar, const Phi::NoFields& v, unsigned int version);

template<typename Archive>
void load(Archive& ar, Phi::NoFields& v, unsigned int version);

} }

#endif
