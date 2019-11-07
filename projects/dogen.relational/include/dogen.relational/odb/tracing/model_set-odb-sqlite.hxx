// -*- C++ -*-
//
// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef DOGEN_RELATIONAL_ODB_TRACING_MODEL_SET_ODB_SQLITE_HXX
#define DOGEN_RELATIONAL_ODB_TRACING_MODEL_SET_ODB_SQLITE_HXX

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

#include "dogen.relational/types/tracing/model_set.hpp"

#include "dogen.relational/odb/tracing/model_set_id-odb-sqlite.hxx"

#include "dogen.relational/odb/tracing/model_set-odb.hxx"

#include <odb/details/buffer.hxx>

#include <odb/sqlite/version.hxx>
#include <odb/sqlite/forward.hxx>
#include <odb/sqlite/binding.hxx>
#include <odb/sqlite/sqlite-types.hxx>
#include <odb/sqlite/query.hxx>

namespace odb
{
  // model_set
  //
  template <typename A>
  struct query_columns< ::dogen::relational::tracing::model_set, id_sqlite, A >
  {
    // id
    //
    struct id_class_
    {
      id_class_ ()
      {
      }

      // value
      //
      typedef
      sqlite::query_column<
        sqlite::value_traits<
          ::std::string,
          sqlite::id_text >::query_type,
        sqlite::id_text >
      value_type_;

      static const value_type_ value;
    };

    static const id_class_ id;

    // qualified_name
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::std::string,
        sqlite::id_text >::query_type,
      sqlite::id_text >
    qualified_name_type_;

    static const qualified_name_type_ qualified_name;
  };

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::model_set, id_sqlite, A >::id_class_::value_type_
  query_columns< ::dogen::relational::tracing::model_set, id_sqlite, A >::id_class_::
  value (A::table_name, "\"ID\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::model_set, id_sqlite, A >::id_class_
  query_columns< ::dogen::relational::tracing::model_set, id_sqlite, A >::id;

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::model_set, id_sqlite, A >::qualified_name_type_
  query_columns< ::dogen::relational::tracing::model_set, id_sqlite, A >::
  qualified_name (A::table_name, "\"QUALIFIED_NAME\"", 0);

  template <typename A>
  struct pointer_query_columns< ::dogen::relational::tracing::model_set, id_sqlite, A >:
    query_columns< ::dogen::relational::tracing::model_set, id_sqlite, A >
  {
  };

  template <>
  class access::object_traits_impl< ::dogen::relational::tracing::model_set, id_sqlite >:
    public access::object_traits< ::dogen::relational::tracing::model_set >
  {
    public:
    struct image_type
    {
      // id_
      //
      composite_value_traits< ::dogen::relational::tracing::model_set_id, id_sqlite >::image_type id_value;

      // qualified_name_
      //
      details::buffer qualified_name_value;
      std::size_t qualified_name_size;
      bool qualified_name_null;

      std::size_t version;
    };

    using object_traits<object_type>::id;

    static bool
    grow (image_type&,
          bool*);

    static void
    bind (sqlite::bind*,
          image_type&,
          sqlite::statement_kind);

    static bool
    init (image_type&,
          const object_type&,
          sqlite::statement_kind);

    static void
    init (object_type&,
          const image_type&,
          database*);

    typedef sqlite::no_id_object_statements<object_type> statements_type;

    typedef sqlite::query_base query_base_type;

    static const std::size_t column_count = 2UL;
    static const std::size_t id_column_count = 0UL;
    static const std::size_t inverse_column_count = 0UL;
    static const std::size_t readonly_column_count = 0UL;
    static const std::size_t managed_optimistic_column_count = 0UL;

    static const std::size_t separate_load_column_count = 0UL;
    static const std::size_t separate_update_column_count = 0UL;

    static const bool versioned = false;

    static const char persist_statement[];
    static const char query_statement[];
    static const char erase_query_statement[];

    static const char table_name[];

    static void
    persist (database&, const object_type&);

    static result<object_type>
    query (database&, const query_base_type&);

    static unsigned long long
    erase_query (database&, const query_base_type&);

    public:
  };

  // model_set
  //
}

#include "dogen.relational/odb/tracing/model_set-odb-sqlite.ixx"

#include <odb/post.hxx>

#endif // DOGEN_RELATIONAL_ODB_TRACING_MODEL_SET_ODB_SQLITE_HXX