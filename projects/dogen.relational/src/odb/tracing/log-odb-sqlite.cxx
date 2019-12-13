// -*- C++ -*-
//
// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#include <odb/pre.hxx>

#include "dogen.relational/odb/tracing/log-odb-sqlite.hxx"

#include <cassert>
#include <cstring>  // std::memcpy

#include <odb/schema-catalog-impl.hxx>

#include <odb/sqlite/traits.hxx>
#include <odb/sqlite/database.hxx>
#include <odb/sqlite/transaction.hxx>
#include <odb/sqlite/connection.hxx>
#include <odb/sqlite/statement.hxx>
#include <odb/sqlite/statement-cache.hxx>
#include <odb/sqlite/no-id-object-statements.hxx>
#include <odb/sqlite/container-statements.hxx>
#include <odb/sqlite/exceptions.hxx>
#include <odb/sqlite/no-id-object-result.hxx>

namespace odb
{
  // log
  //

  bool access::object_traits_impl< ::dogen::relational::tracing::log, id_sqlite >::
  grow (image_type& i,
        bool* t)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (t);

    bool grew (false);

    // run_id_
    //
    if (composite_value_traits< ::dogen::relational::tracing::run_id, id_sqlite >::grow (
          i.run_id_value, t + 0UL))
      grew = true;

    // timestamp_
    //
    if (t[1UL])
    {
      i.timestamp_value.capacity (i.timestamp_size);
      grew = true;
    }

    // component_
    //
    if (t[2UL])
    {
      i.component_value.capacity (i.component_size);
      grew = true;
    }

    // message_
    //
    if (t[3UL])
    {
      i.message_value.capacity (i.message_size);
      grew = true;
    }

    return grew;
  }

  void access::object_traits_impl< ::dogen::relational::tracing::log, id_sqlite >::
  bind (sqlite::bind* b,
        image_type& i,
        sqlite::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace sqlite;

    std::size_t n (0);

    // run_id_
    //
    composite_value_traits< ::dogen::relational::tracing::run_id, id_sqlite >::bind (
      b + n, i.run_id_value, sk);
    n += 1UL;

    // timestamp_
    //
    b[n].type = sqlite::image_traits<
      ::boost::posix_time::ptime,
      sqlite::id_text>::bind_value;
    b[n].buffer = i.timestamp_value.data ();
    b[n].size = &i.timestamp_size;
    b[n].capacity = i.timestamp_value.capacity ();
    b[n].is_null = &i.timestamp_null;
    n++;

    // component_
    //
    b[n].type = sqlite::image_traits<
      ::std::string,
      sqlite::id_text>::bind_value;
    b[n].buffer = i.component_value.data ();
    b[n].size = &i.component_size;
    b[n].capacity = i.component_value.capacity ();
    b[n].is_null = &i.component_null;
    n++;

    // message_
    //
    b[n].type = sqlite::image_traits<
      ::std::string,
      sqlite::id_text>::bind_value;
    b[n].buffer = i.message_value.data ();
    b[n].size = &i.message_size;
    b[n].capacity = i.message_value.capacity ();
    b[n].is_null = &i.message_null;
    n++;
  }

  bool access::object_traits_impl< ::dogen::relational::tracing::log, id_sqlite >::
  init (image_type& i,
        const object_type& o,
        sqlite::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace sqlite;

    bool grew (false);

    // run_id_
    //
    {
      ::dogen::relational::tracing::run_id const& v =
        o.run_id ();

      if (composite_value_traits< ::dogen::relational::tracing::run_id, id_sqlite >::init (
            i.run_id_value,
            v,
            sk))
        grew = true;
    }

    // timestamp_
    //
    {
      ::boost::posix_time::ptime const& v =
        o.timestamp ();

      bool is_null (true);
      std::size_t cap (i.timestamp_value.capacity ());
      sqlite::value_traits<
          ::boost::posix_time::ptime,
          sqlite::id_text >::set_image (
        i.timestamp_value,
        i.timestamp_size,
        is_null,
        v);
      i.timestamp_null = is_null;
      grew = grew || (cap != i.timestamp_value.capacity ());
    }

    // component_
    //
    {
      ::std::string const& v =
        o.component ();

      bool is_null (false);
      std::size_t cap (i.component_value.capacity ());
      sqlite::value_traits<
          ::std::string,
          sqlite::id_text >::set_image (
        i.component_value,
        i.component_size,
        is_null,
        v);
      i.component_null = is_null;
      grew = grew || (cap != i.component_value.capacity ());
    }

    // message_
    //
    {
      ::std::string const& v =
        o.message ();

      bool is_null (false);
      std::size_t cap (i.message_value.capacity ());
      sqlite::value_traits<
          ::std::string,
          sqlite::id_text >::set_image (
        i.message_value,
        i.message_size,
        is_null,
        v);
      i.message_null = is_null;
      grew = grew || (cap != i.message_value.capacity ());
    }

    return grew;
  }

  void access::object_traits_impl< ::dogen::relational::tracing::log, id_sqlite >::
  init (object_type& o,
        const image_type& i,
        database* db)
  {
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (db);

    // run_id_
    //
    {
      ::dogen::relational::tracing::run_id& v =
        o.run_id ();

      composite_value_traits< ::dogen::relational::tracing::run_id, id_sqlite >::init (
        v,
        i.run_id_value,
        db);
    }

    // timestamp_
    //
    {
      ::boost::posix_time::ptime& v =
        o.timestamp ();

      sqlite::value_traits<
          ::boost::posix_time::ptime,
          sqlite::id_text >::set_value (
        v,
        i.timestamp_value,
        i.timestamp_size,
        i.timestamp_null);
    }

    // component_
    //
    {
      ::std::string& v =
        o.component ();

      sqlite::value_traits<
          ::std::string,
          sqlite::id_text >::set_value (
        v,
        i.component_value,
        i.component_size,
        i.component_null);
    }

    // message_
    //
    {
      ::std::string& v =
        o.message ();

      sqlite::value_traits<
          ::std::string,
          sqlite::id_text >::set_value (
        v,
        i.message_value,
        i.message_size,
        i.message_null);
    }
  }

  const char access::object_traits_impl< ::dogen::relational::tracing::log, id_sqlite >::persist_statement[] =
  "INSERT INTO \"DOGEN\".\"LOG\" "
  "(\"RUN_ID\", "
  "\"TIMESTAMP\", "
  "\"COMPONENT\", "
  "\"MESSAGE\") "
  "VALUES "
  "(?, ?, ?, ?)";

  const char access::object_traits_impl< ::dogen::relational::tracing::log, id_sqlite >::query_statement[] =
  "SELECT "
  "\"DOGEN\".\"LOG\".\"RUN_ID\", "
  "\"DOGEN\".\"LOG\".\"TIMESTAMP\", "
  "\"DOGEN\".\"LOG\".\"COMPONENT\", "
  "\"DOGEN\".\"LOG\".\"MESSAGE\" "
  "FROM \"DOGEN\".\"LOG\"";

  const char access::object_traits_impl< ::dogen::relational::tracing::log, id_sqlite >::erase_query_statement[] =
  "DELETE FROM \"DOGEN\".\"LOG\"";

  const char access::object_traits_impl< ::dogen::relational::tracing::log, id_sqlite >::table_name[] =
  "\"DOGEN\".\"LOG\"";

  void access::object_traits_impl< ::dogen::relational::tracing::log, id_sqlite >::
  persist (database& db, const object_type& obj)
  {
    ODB_POTENTIALLY_UNUSED (db);

    using namespace sqlite;

    sqlite::connection& conn (
      sqlite::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    callback (db,
              obj,
              callback_event::pre_persist);

    image_type& im (sts.image ());
    binding& imb (sts.insert_image_binding ());

    if (init (im, obj, statement_insert))
      im.version++;

    if (im.version != sts.insert_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_insert);
      sts.insert_image_version (im.version);
      imb.version++;
    }

    insert_statement& st (sts.persist_statement ());
    if (!st.execute ())
      throw object_already_persistent ();

    callback (db,
              obj,
              callback_event::post_persist);
  }

  result< access::object_traits_impl< ::dogen::relational::tracing::log, id_sqlite >::object_type >
  access::object_traits_impl< ::dogen::relational::tracing::log, id_sqlite >::
  query (database&, const query_base_type& q)
  {
    using namespace sqlite;
    using odb::details::shared;
    using odb::details::shared_ptr;

    sqlite::connection& conn (
      sqlite::transaction::current ().connection ());

    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    image_type& im (sts.image ());
    binding& imb (sts.select_image_binding ());

    if (im.version != sts.select_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_select);
      sts.select_image_version (im.version);
      imb.version++;
    }

    std::string text (query_statement);
    if (!q.empty ())
    {
      text += " ";
      text += q.clause ();
    }

    q.init_parameters ();
    shared_ptr<select_statement> st (
      new (shared) select_statement (
        conn,
        text,
        false,
        true,
        q.parameters_binding (),
        imb));

    st->execute ();

    shared_ptr< odb::no_id_object_result_impl<object_type> > r (
      new (shared) sqlite::no_id_object_result_impl<object_type> (
        q, st, sts, 0));

    return result<object_type> (r);
  }

  unsigned long long access::object_traits_impl< ::dogen::relational::tracing::log, id_sqlite >::
  erase_query (database&, const query_base_type& q)
  {
    using namespace sqlite;

    sqlite::connection& conn (
      sqlite::transaction::current ().connection ());

    std::string text (erase_query_statement);
    if (!q.empty ())
    {
      text += ' ';
      text += q.clause ();
    }

    q.init_parameters ();
    delete_statement st (
      conn,
      text,
      q.parameters_binding ());

    return st.execute ();
  }
}

namespace odb
{
  static bool
  create_schema (database& db, unsigned short pass, bool drop)
  {
    ODB_POTENTIALLY_UNUSED (db);
    ODB_POTENTIALLY_UNUSED (pass);
    ODB_POTENTIALLY_UNUSED (drop);

    if (drop)
    {
      switch (pass)
      {
        case 1:
        {
          return true;
        }
        case 2:
        {
          db.execute ("DROP TABLE IF EXISTS \"DOGEN\".\"LOG\"");
          return false;
        }
      }
    }
    else
    {
      switch (pass)
      {
        case 1:
        {
          db.execute ("CREATE TABLE \"DOGEN\".\"LOG\" (\n"
                      "  \"RUN_ID\" TEXT NOT NULL,\n"
                      "  \"TIMESTAMP\" TEXT NULL,\n"
                      "  \"COMPONENT\" TEXT NOT NULL,\n"
                      "  \"MESSAGE\" TEXT NOT NULL)");
          return false;
        }
      }
    }

    return false;
  }

  static const schema_catalog_create_entry
  create_schema_entry_ (
    id_sqlite,
    "",
    &create_schema);
}

#include <odb/post.hxx>
