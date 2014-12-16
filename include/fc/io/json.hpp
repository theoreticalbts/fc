#pragma once
#include <fc/variant.hpp>
#include <fc/filesystem.hpp>

namespace fc
{
   class ostream;
   class buffered_istream;

   /**
    *  Provides interface for json serialization.
    *
    *  json strings are always UTF8
    */
   class json
   {
      public:
         enum parse_type
         {
            legacy_parser         = 0,
            strict_parser         = 1,
            relaxed_parser        = 2
         };

         static ostream& to_stream( ostream& out, const fc::string& );
         static ostream& to_stream( ostream& out, const variant& v );
         static ostream& to_stream( ostream& out, const variants& v );
         static ostream& to_stream( ostream& out, const variant_object& v );

         static variant  from_stream( buffered_istream& in, parse_type ptype = legacy_parser );

         static variant  from_string( const string& utf8_str, parse_type ptype = legacy_parser );
         static string   to_string( const variant& v );
         static string   to_pretty_string( const variant& v );

         static bool     is_valid( const std::string& json_str, parse_type ptype = legacy_parser );

         template<typename T>
         static void     save_to_file( const T& v, const fc::path& fi, bool pretty = true )
         {
            save_to_file( variant(v), fi, pretty );
         }

         static void     save_to_file( const variant& v, const fc::path& fi, bool pretty = true );
         static variant  from_file( const fc::path& p, parse_type ptype = legacy_parser );

         template<typename T>
         static T from_file( const fc::path& p, parse_type ptype = legacy_parser )
         {
            return json::from_file(p, ptype).as<T>();
         }

         template<typename T>
         static string   to_string( const T& v ) 
         {
            return to_string( variant(v) );
         }

         template<typename T>
         static string   to_pretty_string( const T& v ) 
         {
            return to_pretty_string( variant(v) );
         }

         template<typename T>
         static void save_to_file( const T& v, const std::string& p, bool pretty = true ) 
         {
            save_to_file( variant(v), fc::path(p), pretty );
         } 
   };

} // fc
