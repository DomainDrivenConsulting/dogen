// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef DOGEN_NORTHWIND_ODB_ORDER_DETAILS_KEY_ODB_PGSQL_HXX
#define DOGEN_NORTHWIND_ODB_ORDER_DETAILS_KEY_ODB_PGSQL_HXX

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
#include <odb/boost/date-time/pgsql/gregorian-traits.hxx>
#include <odb/boost/date-time/pgsql/posix-time-traits.hxx>
#include <odb/boost/multi-index/container-traits.hxx>
#include <odb/boost/uuid/pgsql/uuid-traits.hxx>
//
// End prologue.

#include <odb/version.hxx>

#if (ODB_VERSION != 20400UL)
#error ODB runtime version mismatch
#endif

#include <odb/pre.hxx>

#include "dogen/northwind/types/order_details_key.hpp"

#include "dogen/test_models/northwind/types/order_id-odb-pgsql.hxx"
#include "dogen/test_models/northwind/types/product_id-odb-pgsql.hxx"

#include "dogen/northwind/odb/order_details_key-odb.hxx"

#include <odb/details/buffer.hxx>

#include <odb/pgsql/version.hxx>
#include <odb/pgsql/forward.hxx>
#include <odb/pgsql/binding.hxx>
#include <odb/pgsql/pgsql-types.hxx>
#include <odb/pgsql/query.hxx>

namespace odb
{
  // order_details_key
  //
  template <>
  class access::composite_value_traits< ::dogen::test_models::northwind::order_details_key, id_pgsql >
  {
    public:
    typedef ::dogen::test_models::northwind::order_details_key value_type;

    struct image_type
    {
      // product_id_
      //
      composite_value_traits< ::dogen::test_models::northwind::product_id, id_pgsql >::image_type product_id_value;

      // order_id_
      //
      composite_value_traits< ::dogen::test_models::northwind::order_id, id_pgsql >::image_type order_id_value;
    };

    static bool
    grow (image_type&,
          bool*);

    static void
    bind (pgsql::bind*,
          image_type&,
          pgsql::statement_kind);

    static bool
    init (image_type&,
          const value_type&,
          pgsql::statement_kind);

    static void
    init (value_type&,
          const image_type&,
          database*);

    static bool
    get_null (const image_type&);

    static void
    set_null (image_type&,
              pgsql::statement_kind);

    static const std::size_t column_count = 2UL;
  };
}

#include "dogen/northwind/odb/order_details_key-odb-pgsql.ixx"

#include <odb/post.hxx>

#endif // DOGEN_NORTHWIND_ODB_ORDER_DETAILS_KEY_ODB_PGSQL_HXX
