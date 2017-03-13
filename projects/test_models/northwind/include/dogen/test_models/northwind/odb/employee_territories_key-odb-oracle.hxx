// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef DOGEN_NORTHWIND_ODB_EMPLOYEE_TERRITORIES_KEY_ODB_ORACLE_HXX
#define DOGEN_NORTHWIND_ODB_EMPLOYEE_TERRITORIES_KEY_ODB_ORACLE_HXX

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

#include "dogen/northwind/types/employee_territories_key.hpp"

#include "dogen/test_models/northwind/types/employee_id-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/territory_id-odb-oracle.hxx"

#include "dogen/northwind/odb/employee_territories_key-odb.hxx"

#include <odb/details/buffer.hxx>

#include <odb/oracle/version.hxx>
#include <odb/oracle/forward.hxx>
#include <odb/oracle/binding.hxx>
#include <odb/oracle/oracle-types.hxx>
#include <odb/oracle/query.hxx>

namespace odb
{
  // employee_territories_key
  //
  template <>
  class access::composite_value_traits< ::dogen::test_models::northwind::employee_territories_key, id_oracle >
  {
    public:
    typedef ::dogen::test_models::northwind::employee_territories_key value_type;

    struct image_type
    {
      // employee_id_
      //
      composite_value_traits< ::dogen::test_models::northwind::employee_id, id_oracle >::image_type employee_id_value;

      // territory_id_
      //
      composite_value_traits< ::dogen::test_models::northwind::territory_id, id_oracle >::image_type territory_id_value;
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

    static const std::size_t column_count = 2UL;
  };
}

#include "dogen/northwind/odb/employee_territories_key-odb-oracle.ixx"

#include <odb/post.hxx>

#endif // DOGEN_NORTHWIND_ODB_EMPLOYEE_TERRITORIES_KEY_ODB_ORACLE_HXX
