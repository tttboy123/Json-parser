#include "Json.h"
#include "Parser.h"
import <stdexcept>;
import <sstream>;
using namespace Seazzz::json;
Json::Json() :m_type(json_null)//空类型赋值
{
	
}
Json::Json(bool value) :m_type(json_bool)//bool赋值
{
	m_value.m_bool = value;
}
Json::Json(int value) :m_type(json_int)//int赋值
{
	m_value.m_int = value;
}
Json::Json(double value) : m_type(json_double)//double赋值
{
	m_value.m_double = value;
}
Json::Json(const char* value) : m_type(json_string)//string赋值
{
	m_value.m_string = new std::string(value);
}
Json::Json(const std::string& value) :m_type(json_string) //string赋值
{
	m_value.m_string = new std::string(value);
}
Json::Json(const Json& other) 
{
	//浅拷贝提高效率 将Json文件赋值。
	m_type = other.m_type;
	switch (m_type)
	{
	case json_null:
		break;
	case json_bool:
		m_value.m_bool = other.m_value.m_bool;
	case json_int:
		m_value.m_int = other.m_value.m_int;
	case json_double:
		m_value.m_double = other.m_value.m_double;
	case json_string:
		m_value.m_string = other.m_value.m_string;
	case json_array:
		m_value.m_array = other.m_value.m_array;
	case json_object:
		m_value.m_map = other.m_value.m_map;
	default:
		break;
	}
	//深拷贝，问题少
	//////m_type = other.m_type;
	//switch (m_type)
	//{
	//case json_null:
	//	break;
	//case json_bool:
	//	m_value.m_bool = other.m_value.m_bool;
	//case json_int:
	//	m_value.m_int = other.m_value.m_int;
	//case json_double:
	//	m_value.m_double = other.m_value.m_double;
	//case json_string:
	//{
	//	m_value.m_string = new std::string("");
	//	m_value.m_string = other.m_value.m_string;
	//}
	//case json_array:
	//{
	//	m_value.m_array = new std::vector<Json>();
	//	m_value.m_array = other.m_value.m_array;

	//}
	//case json_object:
	//{
	//	m_value.m_map = new std::map<std::string, Json>();
	//	m_value.m_map = other.m_value.m_map;
	//	
	//}
	//	
	//default:
	//	break;
	//}
}
//Json 初始化为所有变量赋值
Json::Json(Type type) : m_type(type)
{
	switch (m_type)
	{
	case json_null:
		break;
	case json_bool:
		m_value.m_bool = false;
	case json_int:
		m_value.m_int = 0;
	case json_double:
		m_value.m_double = 0.0;
	case json_string:
		m_value.m_string = new std::string("");
	case json_array:
		m_value.m_array = new std::vector<Json>();
	case json_object:
		m_value.m_map = new std::map<std::string, Json>();
	default:
		break;
	}
}
Json::~Json()
{
	
}
//重载操作bool类型
Json::operator bool()
{
	if (m_type!= json_bool)
	{
		throw new std::logic_error("type error, not bool");
	}
	return m_value.m_bool;
}
Json::operator int() 
{
	if (m_type != json_int)
	{
		throw new std::logic_error("type error, not int");
	}
	return m_value.m_int;
}
Json::operator double() 
{
	if (m_type != json_double)
	{
		throw new std::logic_error("type error, not double");
	}
	return m_value.m_double;
}
Json::operator std::string()
{
	if (m_type != json_string)
	{
		throw new std::logic_error("type error, not string");
	}
	return *(m_value.m_string);

}
Json & Json:: operator[](int index) 
{
	if (m_type != json_array)
	{
		m_type = json_array;
		m_value.m_array = new std::vector<Json>();
	}
	if (index < 0)
	{
		throw new std::logic_error("array index > 0");
	}
	int size = (m_value.m_array)->size();
	if (index >= size)
	{
		for (int i = size; i <= index; i++)
		{
			(m_value.m_array)->push_back(Json());
		}
		return (m_value.m_array)->at(index);
	}
}
void Json::clear()//浅拷贝遇到问题，需要先释放内存
{
	switch (m_type)
	{
	case json_null:
		break;
	case json_bool:
		m_value.m_bool = false;
	case json_int:
		m_value.m_int = 0;
	case json_double:
		m_value.m_double = 0.0;
	case json_string:
		{
		delete m_value.m_string;
		break;
		}
	case json_array:
	{
		for (auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end(); it++)
		{
			it->clear();
		}
		delete m_value.m_array;
		break;
	}
	case json_object:
	{
		for (auto it = (m_value.m_map)->begin(); it != (m_value.m_map)->end(); it++)
		{
			(it->second).clear();
		}
		delete m_value.m_array;
		break;
	}
	default :
		break;
	}
	m_type = json_null;
}
void Json::copy(const Json& other)
{
	m_type = other.m_type;
	switch (m_type)
	{
	case json_null:
		break;
	case json_bool:
		m_value.m_bool = other.m_value.m_bool;
	case json_int:
		m_value.m_int = other.m_value.m_int;
	case json_double:
		m_value.m_double = other.m_value.m_double;
	case json_string:
		m_value.m_string = other.m_value.m_string;
	case json_array:
		m_value.m_array = other.m_value.m_array;
	case json_object:
		m_value.m_map = other.m_value.m_map;
	default:
		break;
	}
}
void Json::operator =(const Json& other)
{
	copy(other);
}
bool Json::operator ==(const Json& other) 
{
	if (m_type != other.m_type)
		return false;
		
	switch (m_type)
	{
	case json_null:
		return true;
	case json_bool:
		return m_value.m_bool == other.m_value.m_bool;
	case json_int:
		return m_value.m_int == other.m_value.m_int;
	case json_double:
		return m_value.m_double == other.m_value.m_double;
	case json_string:
		return *(m_value.m_string) == *(other.m_value.m_string);
	
	case json_array:
	{
		int size1 = (other.m_value.m_array)->size();
		int size = (m_value.m_array)->size();
		if (size1 != size)
			return false;
		auto it1 = (other.m_value.m_array)->begin();
		for (auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end(); it++)
		{
			if (it != it1)
				return false;
			it1++;
		}
		return true;
		
	}
	case json_object:
		return m_value.m_map == other.m_value.m_map;
	default:
		break;
	}
return false;
}
bool Json::operator !=(const Json& other)
{
	return !((*this) == other);
}
Json& Json:: operator[](const char* key) 
{
	std::string name(key);
	return (*(this))[name];
}
Json& Json:: operator[](const std::string& key)
{
	if (m_type != json_object)
	{
		clear();
		m_type = json_object;
		m_value.m_map = new std::map<std::string, Json>();
	}
	return(*(m_value.m_map))[key];
}
void Json::append(const Json& other)//为数组添加元素
{
	if (m_type != json_array)
	{
		clear();
		m_type = json_array;
		m_value.m_array = new std::vector<Json>();
	}
	(m_value.m_array)->push_back(other);

}
std::string Json::str()const 
{
	std::stringstream ss;
	switch (m_type)
	{
	case json_null:
		ss << "NULL";
		break;
	case json_bool:
		if (m_value.m_bool)
		{
			ss << "true";
		}
		else
		{
			ss << "false";
		}
		break;
	case json_int:
		ss << m_value.m_int;
		break;
	case json_double:
		ss << m_value.m_double;
		break;
	case json_string:
		ss << '\"' << *(m_value.m_string) << '\"';
		break;
	case json_array:
		ss << "[";
		ss << '\"';
		for (auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end(); it++)
		{
			if (it == (m_value.m_array)->begin())
			{
				ss<<it->str();
			}
			else ss << "," << it->str();
		}
		ss << '\"';
		ss << "]";
		break;
	case json_object:
		ss << "{";
		 
		for (auto it1 = (m_value.m_map)->begin(); it1 != (m_value.m_map)->end(); it1++)
		{
			ss << '\"' << it1->first << "," << it1->second.str() << ";";
		}
		ss << "}";
		break;
	default:
		break;
	}
	return ss.str();
}

bool Json::asBool()const
{
	if (m_type != json_bool)
		throw new std::logic_error("type error.");
	return m_value.m_bool;
}
int Json::asInt()const
{
	if (m_type != json_int)
	throw new std::logic_error("type error.");
	return m_value.m_int;
}
double Json::asDouble()const {
	if (m_type != json_double)
		throw new std::logic_error("type error.");
	return m_value.m_double;
}
std::string Json::asString()const
{
	if (m_type != json_string)
		throw new std::logic_error("type error.");
	return *(m_value.m_string);
}

bool Json::has(int index)
{
	if (m_type != json_array)
		return false;
	int size = (m_value.m_array)->size();
	return (index >= 0 && index <= size);
}
bool Json::has(const char* key)
{
	std::string name(key);
	return has(name);

}

bool Json::has(const std::string& key)
{
	if (m_type != json_object)
	{
		return false;
	}
	return ((m_value.m_map)->find(key) != m_value.m_map->end());

}
void Json::remove(int index) {
	if (m_type != json_array)
		return ;
	int size = (m_value.m_array)->size();
	if (index || index >= size)
		return;
	(m_value.m_array)->at(index).clear();
	(m_value.m_array)->erase((m_value.m_array)->begin() + index);
}
void Json::remove(const char* key)
{
	std::string name(key);
	remove(name);
}
void Json::remove(const std::string& key)
{
	auto it = m_value.m_map->find(key);
	if (it == m_value.m_map->end())
		return;
	(*(m_value.m_map))[key].clear();
	(m_value.m_map)->erase(key);
}
void Json::parse(const std::string& str)
{
	Parser p;
	p.load(str);


}