// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef DOGEN_NORTHWIND_ODB_ORDER_DETAILS_ODB_HXX
#define DOGEN_NORTHWIND_ODB_ORDER_DETAILS_ODB_HXX

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
#include <odb/boost/multi-index/container-traits.hxx>
//
// End prologue.

#include <odb/version.hxx>

#if (ODB_VERSION != 20400UL)
#error ODB runtime version mismatch
#endif

#include <odb/pre.hxx>

#include "dogen/northwind/types/order_details.hpp"

#include "dogen/test_models/northwind/types/order_details_key-odb.hxx"
#include "dogen/test_models/northwind/types/order_id-odb.hxx"
#include "dogen/test_models/northwind/types/product_id-odb.hxx"

#include <memory>
#include <cstddef>
#include <utility>

#include <odb/core.hxx>
#include <odb/traits.hxx>
#include <odb/callback.hxx>
#include <odb/wrapper-traits.hxx>
#include <odb/pointer-traits.hxx>
#ifdef BOOST_TR1_MEMORY_HPP_INCLUDED
#  include <odb/tr1/wrapper-traits.hxx>
#  include <odb/tr1/pointer-traits.hxx>
#endif
#include <odb/container-traits.hxx>
#include <odb/no-op-cache-traits.hxx>
#include <odb/result.hxx>
#include <odb/simple-object-result.hxx>

#include <odb/details/unused.hxx>
#include <odb/details/shared-ptr.hxx>

namespace odb
{
  // order_details
  //
  template <>
  struct class_traits< ::dogen::test_models::northwind::order_details >
  {
    static const class_kind kind = class_object;
  };

  template <>
  class access::object_traits< ::dogen::test_models::northwind::order_details >
  {
    public:
    typedef ::dogen::test_models::northwind::order_details object_type;
    typedef ::boost::shared_ptr< ::dogen::test_models::northwind::order_details > pointer_type;
    typedef odb::pointer_traits<pointer_type> pointer_traits;

    static const bool polymorphic = false;

    typedef ::dogen::test_models::northwind::order_details_key id_type;

    static const bool auto_id = false;

    static const bool abstract = false;

    static id_type
    id (const object_type&);

    typedef
    no_op_pointer_cache_traits<pointer_type>
    pointer_cache_traits;

    typedef
    no_op_reference_cache_traits<object_type>
    reference_cache_traits;

    static void
    callback (database&, object_type&, callback_event);

    static void
    callback (database&, const object_type&, callback_event);
  };
}

#include "dogen/northwind/odb/order_details-odb.ixx"

#include <odb/post.hxx>

#endif // DOGEN_NORTHWIND_ODB_ORDER_DETAILS_ODB_HXX
