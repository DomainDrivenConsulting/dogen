// -*- C++ -*-
//
// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef DOGEN_RELATIONAL_ODB_TRACING_TRANSFORM_COMPONENTS_KEY_ODB_SQLITE_HXX
#define DOGEN_RELATIONAL_ODB_TRACING_TRANSFORM_COMPONENTS_KEY_ODB_SQLITE_HXX

// Begin prologue.
//
#include <odb/boost/version.hxx>
#if ODB_BOOST_VERSION != 2046500 // 2.5.0-b.15
#  error ODB and C++ compilers see different libodb-boost interface versions
#endif
#include <boost/shared_ptr.hpp>
#include <odb/boost/smart-ptr/pointer-traits.hxx>
#include <odb/boost/smart-ptr/wrapper-traits.hxx>
#include <odb/boost/optional/wrapper-traits.hxx>
#include <odb/boost/unordered/container-traits.hxx>
#include <odb/boost/date-time/sqlite/gregorian-traits.hxx>
#include <odb/boost/date-time/sqlite/posix-time-traits.hxx>
#include <odb/boost/multi-index/container-traits.hxx>
#include <odb/boost/uuid/sqlite/uuid-traits.hxx>
//
// End prologue.

#include <odb/version.hxx>

#if (ODB_VERSION != 20465UL)
#error ODB runtime version mismatch
#endif

#include <odb/pre.hxx>

#include "dogen.relational/types/tracing/transform_components_key.hpp"

#include "dogen.relational/odb/tracing/transform_id-odb-sqlite.hxx"

#include "dogen.relational/odb/tracing/transform_components_key-odb.hxx"

#include <odb/details/buffer.hxx>

#include <odb/sqlite/version.hxx>
#include <odb/sqlite/forward.hxx>
#include <odb/sqlite/binding.hxx>
#include <odb/sqlite/sqlite-types.hxx>
#include <odb/sqlite/query.hxx>

namespace odb
{
  // transform_components_key
  //
  template <>
  class access::composite_value_traits< ::dogen::relational::tracing::transform_components_key, id_sqlite >
  {
    public:
    typedef ::dogen::relational::tracing::transform_components_key value_type;

    struct image_type
    {
      // parent_id_
      //
      composite_value_traits< ::dogen::relational::tracing::transform_id, id_sqlite >::image_type parent_id_value;

      // component_id_
      //
      composite_value_traits< ::dogen::relational::tracing::transform_id, id_sqlite >::image_type component_id_value;
    };

    static bool
    grow (image_type&,
          bool*);

    static void
    bind (sqlite::bind*,
          image_type&,
          sqlite::statement_kind);

    static bool
    init (image_type&,
          const value_type&,
          sqlite::statement_kind);

    static void
    init (value_type&,
          const image_type&,
          database*);

    static bool
    get_null (const image_type&);

    static void
    set_null (image_type&,
              sqlite::statement_kind);

    static const std::size_t column_count = 2UL;
  };
}

#include "dogen.relational/odb/tracing/transform_components_key-odb-sqlite.ixx"

#include <odb/post.hxx>

#endif // DOGEN_RELATIONAL_ODB_TRACING_TRANSFORM_COMPONENTS_KEY_ODB_SQLITE_HXX