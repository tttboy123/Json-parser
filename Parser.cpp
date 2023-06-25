#include "Parser.h"
#include <stdexcept>
using namespace Seazzz::json;

Parser::Parser()
{
	m_str = "";
	m_idx = 0;
}
void Parser::load(const string & str)
{
	m_str = str;
	m_idx = 0; 
	parse();
}
void Parser::skip_white_space()
{
	while (m_str[m_idx] == ' ' || m_str[m_idx] == '\n' || m_str[m_idx] == '\r' || m_str[m_idx] == '\t')
	{
		m_idx++;
	}
}
char Parser::get_next_char()
{
	skip_white_space();
	char ch = m_str[m_idx];
	m_idx++;
	return ch;
}
Json Parser::parse()
{
	char ch = get_next_char();
	if (ch == 'n' && get_next_char() == 'u' && get_next_char() == 'l' && get_next_char() == 'l')
		return parse_null();
	else if (ch == 't' || ch == 'f')
	{
		ch = get_next_char();
		if (ch == 'r' || ch == 'a')
		{
			ch = get_next_char();
			if (ch == 'u' || ch == 'l')
			{
				ch = get_next_char();
				if (ch == 'e')
				{
					m_idx -= 4;
					return parse_bool();
				}
				else if(ch =='s')
				{
					ch = get_next_char();
					m_idx -= 5;
					if (ch == 'e') return parse_bool();
				}
			}
		}
	}
	else if (ch >= '0' && ch <= '9')
		return parse_number();
	else if (ch == '"')
		return Json(parse_string());
	else if (ch == '[')
		return parse_array();
	else if (ch == '{')
		return parse_object();
	throw new std::logic_error("undefined");
	return NULL;
}
Json Parser::parse_null()
{
	if (m_str.compare(m_idx, 4, "null") == 0)
		return Json();
	return NULL;
}
Json Parser::parse_bool()
{
	if (m_str.compare(m_idx, 4, "true") == 0)
	{
		m_idx += 4;
		return Json(true);
	}
	else if (m_str.compare(m_idx, 5, "false") == 0)
	{
		m_idx += 5;
		return Json(false);
	}
		
	return 0;
}
Json Parser::parse_number(){
	int pos = m_idx--;
	if (m_str[m_idx] == '-')
	{
		m_idx++;
	}
	if (m_str[m_idx] < '0' || m_str[m_idx]>'9')
	{
		throw new std::logic_error("parse number error");
	}
	while (m_str[m_idx] >= '0' && m_str[m_idx] <= '9')
	{
		m_idx++;
	}
	if (m_str[m_idx] != '.')
	{
		int i = std::atoi(m_str.c_str() + pos);
		return Json(i);
	}
	m_idx++;
	if (m_str[m_idx] < '0' || m_str[m_idx]>'9')
	{
		throw new std::logic_error("parse number error");
	}
	while (m_str[m_idx] >= '0' && m_str[m_idx] <= '9')
	{
		m_idx++;
	}
	double f = std::atof(m_str.c_str() + pos);
	return Json(f);
}
string Parser::parse_string()
{
	string out;
	while (true)
	{
		char ch = m_str[m_idx++];
		if (ch == '"')
			break;
		if (ch == '\\')
		{
			ch = m_str[m_idx++];
			switch (ch)
			{
			case '\n':
				out += '\n';
				break;
			case '\r':
				out += '\r';
				break;
			case '\t':
				out += '\t';
				break;
			case '\b':
				out += '\b';
				break;
			case'\f':
				out += '\f';
				break;
			case'"':
				out += "\\\"";
				break;
			case'\\':
				out += "\\\\";
				break;
			case'u':
				out += "\\u";
				break;
			default:
				break;
			}
		}
		else {
			out += ch;
		}
	}
	return out;
}
Json Parser::parse_array()
{
	Json arr(Json::json_array);
	char ch = get_next_char();
	if (ch == ']')
	{
		return arr;
	}
	m_idx--;
	while (true)
	{
		arr.append(parse());
		ch = get_next_char();
		if (ch == ']')
			break;
		m_idx++;
	}
}
Json Parser::parse_object()
{
	Json obj = Json::json_object;
	char ch = get_next_char();
	if (ch == '}')
		return obj;
	m_idx--;
	while (true)
	{
		ch = get_next_char();
		if (ch != '"')
		{
			throw new std::logic_error("AAAAAAAAAAAAAAAAA");
		}
		string key = parse_string();
		ch = get_next_char();
		if (ch!= ':')
		{
			throw new std::logic_error("AAAAAAAAAAAAAAAAA");
		}
		obj[key] = parse();
		if (ch == '}')
			break;
		if (ch != ',')
			throw new std::logic_error("AAAAAAAAAAAAAAAAAAA");
		m_idx++;

	}
}