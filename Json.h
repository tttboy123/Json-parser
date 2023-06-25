#pragma once
import <string>;
import <vector>;
import <map>;
namespace Seazzz
{
	namespace json
	{
		class Json//Object,Array,string,number,bool
		{
		public:
			enum Type {
				json_null = 0,
				json_bool,
				json_int,
				json_double,
				json_string,
				json_array,
				json_object,
			};//json文件类型
		//function
		public:
			Json();				
			Json(bool value);
			Json(int value);
			Json(double value);
			Json(const char* value);
			Json(const std::string& value);
			Json(const Json& other);
			Json(Type type);
			~Json();
			operator bool();
			operator int();
			operator double();
			operator std::string();
			Json& operator[](int index);
			Json& operator[](const char* key);
			Json& operator[](const std::string& key);
			void copy(const Json& other);
			void clear();
			void operator =(const Json& other);
			bool operator !=(const Json& other);
			bool operator ==(const Json& other);
			void append(const Json& other);
			std::string str()const;
			typedef std::vector<Json>::iterator iterator;
			iterator begin()
			{
				return m_value.m_array->begin();
			}
			iterator end()
			{
				return m_value.m_array->end();
			}
			bool isNull()const { return m_type == json_null; }
			bool isBool()const { return m_type == json_bool; }
			bool isInt()const { return m_type == json_int; }
			bool isDouble()const { return m_type == json_double; }
			bool isString()const { return m_type == json_string; }
			bool isArray()const { return m_type == json_array; }
			bool isMap()const { return m_type == json_object; }

			bool asBool()const;
			int asInt()const;
			double asDouble()const;
			std::string asString()const;

			bool has(int index);
			bool has(const char* key);
			bool has(const std::string& key);
			void remove(int index);
			void remove(const char* key);
			void remove(const std::string & key);
			void parse(const std::string& str);
		private:
			union Value
			{
				bool m_bool;
				int m_int;
				double m_double;
				std::string* m_string;
				std::vector<Json>* m_array;
				std::map<std::string, Json>* m_map;
			};
			Type m_type;
			Value m_value;
		};
	}
}

