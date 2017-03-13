// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#include <odb/pre.hxx>

#include "dogen/northwind/odb/employee_territories_key-odb-oracle.hxx"

#include <cassert>
#include <cstring>  // std::memcpy

#include <odb/schema-catalog-impl.hxx>

#include <odb/oracle/traits.hxx>
#include <odb/oracle/database.hxx>
#include <odb/oracle/transaction.hxx>
#include <odb/oracle/connection.hxx>
#include <odb/oracle/statement.hxx>
#include <odb/oracle/statement-cache.hxx>
#include <odb/oracle/container-statements.hxx>
#include <odb/oracle/exceptions.hxx>

namespace odb
{
  // employee_territories_key
  //

  void access::composite_value_traits< ::dogen::test_models::northwind::employee_territories_key, id_oracle >::
  bind (oracle::bind* b,
        image_type& i,
        oracle::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (b);
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace oracle;

    std::size_t n (0);
    ODB_POTENTIALLY_UNUSED (n);

    // employee_id_
    //
    composite_value_traits< ::dogen::test_models::northwind::employee_id, id_oracle >::bind (
      b + n, i.employee_id_value, sk);
    n += 1UL;

    // territory_id_
    //
    composite_value_traits< ::dogen::test_models::northwind::territory_id, id_oracle >::bind (
      b + n, i.territory_id_value, sk);
    n += 1UL;
  }

  void access::composite_value_traits< ::dogen::test_models::northwind::employee_territories_key, id_oracle >::
  init (image_type& i,
        const value_type& o,
        oracle::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace oracle;

    // employee_id_
    //
    {
      ::dogen::test_models::northwind::employee_id const& v =
        o.employee_id ();

      composite_value_traits< ::dogen::test_models::northwind::employee_id, id_oracle >::init (
        i.employee_id_value,
        v,
        sk);
    }

    // territory_id_
    //
    {
      ::dogen::test_models::northwind::territory_id const& v =
        o.territory_id ();

      composite_value_traits< ::dogen::test_models::northwind::territory_id, id_oracle >::init (
        i.territory_id_value,
        v,
        sk);
    }
  }

  void access::composite_value_traits< ::dogen::test_models::northwind::employee_territories_key, id_oracle >::
  init (value_type& o,
        const image_type&  i,
        database* db)
  {
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (db);

    // employee_id_
    //
    {
      ::dogen::test_models::northwind::employee_id& v =
        o.employee_id ();

      composite_value_traits< ::dogen::test_models::northwind::employee_id, id_oracle >::init (
        v,
        i.employee_id_value,
        db);
    }

    // territory_id_
    //
    {
      ::dogen::test_models::northwind::territory_id& v =
        o.territory_id ();

      composite_value_traits< ::dogen::test_models::northwind::territory_id, id_oracle >::init (
        v,
        i.territory_id_value,
        db);
    }
  }
}

#include <odb/post.hxx>
