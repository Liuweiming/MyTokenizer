#pragma once
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
template <typename Container> // T should be an container.
class Spliter
{
public:
	using con_type = typename Container;
	using elem_type = typename Container::value_type;
	using ref_type = typename Container::iterator;
	using con_ref_type = typename Container::const_iterator;
	enum SplitType {split_with_char, split_with_sub};
public:
	Spliter()
	{}
	Spliter(const con_type &del, SplitType typ = split_with_char) : delim(del), type(typ)
	{}
	~Spliter()
	{}
	void setDelim(const con_type &deli)
	{
		delim = deli;
	}
	void setType(SplitType typ)
	{
		type = typ;
	}
	const con_type &getDelim()
	{
		return delim;
	}
	SplitType getType()
	{
		return type;
	}
	std::vector<ref_type> spliteRef(con_type &con, SplitType type) const
	{
		return Spliter<con_type>::spliteRef(con, type, delim);
	}
	std::vector<con_type> spliteRes(const con_type &con, SplitType type) const
	{
		return Spliter<con_type>::spliteRes(con, type, delim);
	}
	std::vector<ref_type> spliteRef(con_type &con) const
	{
		return Spliter<con_type>::spliteRef(con, type, delim);
	}
	std::vector<con_type> spliteRes(const con_type &con) const
	{
		return Spliter<con_type>::spliteRes(con, type, delim);
	}
	static std::vector<ref_type> spliteRef(con_type &con, SplitType type, const con_type &delim)
	{
		std::vector<ref_type> ret;
		auto begin = con.begin();
		ret.push_back(begin);
		if (type == split_with_char)
		{
			while ((begin = std::find_first_of(begin, con.end(), delim.begin(), delim.end())) != con.end())
			{
				ret.push_back(begin);
				++begin;
				ret.push_back(begin);
			}
		}
		else
		{
			while ((begin = std::search(begin, con.end(), delim.begin(), delim.end())) != con.end())
			{
				ret.push_back(begin);
				begin += delim.size();
				ret.push_back(begin);
			}
		}
		ret.push_back(con.end());
		return std::move(ret);
	}
	static std::vector<con_ref_type> spliteRef(const con_type &con, SplitType type, const con_type &delim)
	{
		std::vector<con_ref_type> ret;
		auto begin = con.begin();
		ret.push_back(begin);
		if (type == split_with_char)
		{
			while ((begin = std::find_first_of(begin, con.end(), delim.begin(), delim.end())) != con.end())
			{
				ret.push_back(begin);
				++begin;
				ret.push_back(begin);
			}
		}
		else
		{
			while ((begin = std::search(begin, con.end(), delim.begin(), delim.end())) != con.end())
			{
				ret.push_back(begin);
				begin += delim.size();
				ret.push_back(begin);
			}
		}
		ret.push_back(con.end());
		return std::move(ret);
	}
	static std::vector<con_type> spliteRes(const con_type &con, SplitType type, const con_type &delim)
	{
		auto split_ref = spliteRef(con, type, delim);
		assert(split_ref.size() >= 2);
		std::vector<con_type> ret;
		auto beg = split_ref.begin();
		for (; beg != split_ref.end(); beg += 2)
		{
			auto p = beg + 1;
			ret.push_back(con_type(*beg, *p));
		}
		return std::move(ret);
	}
private:
	con_type delim = con_type();
	SplitType type = split_with_char;
	
	/*template<typename Container>
	class StringSpliter
	{
	public:
		using con_type = typename Container;
		using elem_type = typename Container::value_type;
		using ref_type = typename Container::iterator;
		using con_ref_type = typename Container::const_iterator;
	public:
		static std::vector<ref_type> spliteRef(con_type &con, SplitType type, const con_type &delim)
		{
			std::vector<ref_type> ret;
			auto begin = con.begin();
			ret.push_back(begin);
			if (type == split_with_char)
			{
				while ((begin = std::find_first_of(begin, con.end(), delim.begin(), delim.end())) != con.end())
				{
					ret.push_back(begin);
					++begin;
					ret.push_back(begin);
				}
			}
			else
			{
				while ((begin = std::search(begin, con.end(), delim.begin(), delim.end())) != con.end())
				{
					ret.push_back(begin);
					begin += delim.size();
					ret.push_back(begin);
				}
			}
			ret.push_back(end);
			return std::move(ret);
		}
		static std::vector<con_ref_type> spliteRef(const con_type &con, SplitType type, const con_type &delim)
		{
			std::vector<con_ref_type> ret;
			auto begin = con.begin();
			auto end = con.end();
			ret.push_back(begin);
			if (type == split_with_char)
			{
				while(begin != end)
				{
					if (std::find(delim.begin(), delim.end(), *begin) != delim.end())
					{
						ret.push_back(begin);
						++begin;
						ret.push_back(begin);
					}
					else
					{
						++begin;
					}
				}
			}
			ret.push_back(end);
			return std::move(ret);
		}
	};
	template<typename E>
	class StringSpliter<std::basic_string<typename E>>
	{
	public:
		using con_type = std::basic_string<typename E>;
		using ref_type = typename con_type::iterator;
		using con_ref_type = typename con_type::const_iterator;
	public:
		static std::vector<ref_type> spliteRef(con_type &con, SplitType type, const con_type &delim)
		{
			std::vector<ref_type> ret;
			auto begin = con.begin();
			auto end = con.end();
			ret.push_back(begin);
			if (type == split_with_char)
			{
				std::size_t pos = 0;
				std::size_t p = 0;
				while ((p = con.find_first_of(delim, pos)) != con_type::npos)
				{
					ret.push_back(begin + p);
					++p;
					ret.push_back(begin + p);
					pos = p;
				}
			}
			else
			{
				std::size_t pos = 0;
				std::size_t p = 0;
				while ((p = con.find(delim, pos)) != con_type::npos)
				{
					ret.push_back(begin + p);
					p += delim.size();
					ret.push_back(begin + p);
					pos = p;
				}
			}
			ret.push_back(end);
			return std::move(ret);
		}
		static std::vector<con_ref_type> spliteRef(const con_type &con, SplitType type, const con_type &delim)
		{
			std::vector<con_ref_type> ret;
			auto begin = con.begin();
			auto end = con.end();
			ret.push_back(begin);
			if (type == split_with_char)
			{
				std::size_t pos = 0;
				std::size_t p = 0;
				while ((p = con.find_first_of(delim, pos)) != con_type::npos)
				{
					ret.push_back(begin + p);
					++p;
					ret.push_back(begin + p);
					pos = p;
				}
			}
			else
			{
				std::size_t pos = 0;
				std::size_t p = 0;
				while ((p = con.find(delim, pos)) != con_type::npos)
				{
					ret.push_back(begin + p);
					p += delim.size();
					ret.push_back(begin + p);
					pos = p;
				}
			}
			ret.push_back(end);
			return std::move(ret);
		}
	};*/
};

