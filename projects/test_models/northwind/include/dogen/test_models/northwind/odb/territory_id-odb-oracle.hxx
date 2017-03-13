// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef DOGEN_NORTHWIND_ODB_TERRITORY_ID_ODB_ORACLE_HXX
#define DOGEN_NORTHWIND_ODB_TERRITORY_ID_ODB_ORACLE_HXX

// Begin prologue.
//
#include <odb/boost/version.hxx>
#if ODB_BOOST_VERSION != 2040000 // 2.4.0
#  error ODB and C++ compilers see different libodb-boost interface versions
#endif
#include <boost/shared_ptr.hpp>
#include <odb/boost/smart-ptr/pointer-traits.hxx>
#include <odb/boost/smart-ptr/wrapper-traits.hxx>
#include <odb/boost/optional/wrapper-traits.hxx>
#include <odb/boost/unordered/container-traits.hxx>
#include <odb/boost/date-time/oracle/gregorian-traits.hxx>
#include <odb/boost/date-time/oracle/posix-time-traits.hxx>
#include <odb/boost/multi-index/container-traits.hxx>
#include <odb/boost/uuid/oracle/uuid-traits.hxx>
//
// End prologue.

#include <odb/version.hxx>

#if (ODB_VERSION != 20400UL)
#error ODB runtime version mismatch
#endif

#include <odb/pre.hxx>

#include "dogen/northwind/types/territory_id.hpp"

#include "dogen/northwind/odb/territory_id-odb.hxx"

#include <odb/details/buffer.hxx>

#include <odb/oracle/version.hxx>
#include <odb/oracle/forward.hxx>
#include <odb/oracle/binding.hxx>
#include <odb/oracle/oracle-types.hxx>
#include <odb/oracle/query.hxx>

namespace odb
{
  // territory_id
  //
  template <>
  class access::composite_value_traits< ::dogen::test_models::northwind::territory_id, id_oracle >
  {
    public:
    typedef ::dogen::test_models::northwind::territory_id value_type;

    struct image_type
    {
      // value_
      //
      char value_value[512];
      ub2 value_size;
      sb2 value_indicator;
    };

    static void
    bind (oracle::bind*,
          image_type&,
          oracle::statement_kind);

    static void
    init (image_type&,
          const value_type&,
          oracle::statement_kind);

    static void
    init (value_type&,
          const image_type&,
          database*);

    static bool
    get_null (const image_type&);

    static void
    set_null (image_type&,
              oracle::statement_kind);

    static const std::size_t column_count = 1UL;
  };
}

#include "dogen/northwind/odb/territory_id-odb-oracle.ixx"

#include <odb/post.hxx>

#endif // DOGEN_NORTHWIND_ODB_TERRITORY_ID_ODB_ORACLE_HXX
