#pragma once
#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iterator>
#include <fstream>

/*
template <class I>
class Range
{
public:

	Range(I begin = nullptr, I end = nullptr) {
		setBegin(begin);
		setEnd(end);
	}

	Range(const Range<I>& other) {
		_copy(other);
	}

	Range& operator= (const Range<I>& other) {
		_copy(other);
		return *this;
	}

	I begin() const
	{
		return _begin;
	}

	I end() const
	{
		return _end;
	}
private:
	I _begin;
	I _end;

	void setBegin(I begin) {
		_begin = begin;
	}

	void setEnd(I end) {
		_end = end;
	}

	void _copy(const Range<I>& other) {
		if (this != &other) {
			setBegin(other.begin());
			setEnd(other.end());
		}
	}
};
*/

template <class I>
class Range
{
private:
	void _copy(const Range<I>& other) {
		if (this != &other) {
			setBegin(other.begin());
			setEnd(other.end());
		}
	}
public:

	I begin()
	{
		return _begin;
	}

	I end()
	{
		return _end;
	}

	I operator+ (int x) {
		try {
			return _begin + x;
		}
		catch (...) {
			std::cout << "Error in operator+ of Range class" << std::endl;
		}
	}

	I _begin;
	I _end;
};

template <class I, class function_return_type>
class MappedIterator
{
public:

	I original;
	using value_type = function_return_type;

	std::function<function_return_type(typename I::value_type)> op;

	MappedIterator& operator++()
	{
		++original;
		return *this;
	}

	bool operator!=(const MappedIterator& other)
	{
		return original != other.original;
	}

	bool operator==(const MappedIterator& other)
	{
		return original == other.original;
	}

	function_return_type operator*()
	{
		return op(*original);
	}

};

template <class It>
class FilteredIterator
{
public:

	It original, original_end;
	using value_type = typename It::value_type;

	FilteredIterator(const It& _original,
		const It& _original_end,
		std::function<bool(value_type)> _pred) :original(_original), original_end(_original_end), pred(_pred)
	{
		ensurePredicate();
	}

	std::function<bool(value_type)> pred;

	FilteredIterator& operator++()
	{
		if (original == original_end)
		{
			throw std::out_of_range("End of range reached!");
		}

		++original;
		ensurePredicate();

		return *this;
	}

	bool operator!=(const FilteredIterator& other)
	{
		return original != other.original;
	}

	bool operator==(const FilteredIterator& other)
	{
		return original == other.original;
	}

	value_type operator*()
	{
		if (original == original_end)
		{
			throw std::out_of_range("Reading end of range!");
		}
		return *original;
	}

private:
	void ensurePredicate()
	{
		while (original != original_end && !pred(*original))
		{
			++original;
		}
	}

};

template <class It>
class MergeIterator {
public:
	typename It _begin1, _end1, _begin2, _end2, original;
	bool go_to_second_part = false;

	using value_type = typename It::value_type;
	using iterator_type = It;

	/*MergeIterator(const It& b1, const It& e1,
		const It& b2, const It& e2, bool second_part) :
		_begin1(b1), _begin2(b2), _end1(e1), _end2(e2), go_to_second_part(second_part) {
		original = _begin1;
		if (_begin1 == _end1) original = _begin2;
	}*/

	MergeIterator& operator++() {
		if (_begin1 != _end1 && ++_begin1 == _end1) {
			go_to_second_part = true;
			original = _begin2;
		}
		else ++original;

		return *this;
	}

	bool operator!=(const MergeIterator& other) {
		//Не съм много сигурен дали това е вярно
		if (go_to_second_part != other.go_to_second_part) return true;
		else return original != other.original;
	}

	bool operator==(const MergeIterator& other) {
		return !operator!=(other);
	}

	value_type operator*() {
		return *original;
	}
};

template <class It, class It2>
class MergeIterator2 {
public:
	typename It _begin1, _end1, original;
	typename It2 _begin2, _end2, original2;
	bool go_to_second_part = false;

	using value_type = typename It::value_type;
	using iterator_type = It;

	/*MergeIterator2(const It& b1, const It& e1,
		const It2& b2, const It2& e2, bool second_part) :
		_begin1(b1), _begin2(b2), _end1(e1), _end2(e2), go_to_second_part(second_part) {
		original = _begin1;
		original2 = _begin2;
	}*/

	MergeIterator2& operator++() {
		if (_begin1 != _end1 && ++_begin1 == _end1) {
			go_to_second_part = true;
			//original = _begin2;
		}
		else if (go_to_second_part) ++original2;
		else ++original;

		return *this;
	}

	bool operator!=(const MergeIterator2& other) {
		//Не съм много сигурен дали това е вярно
		if (go_to_second_part != other.go_to_second_part) return true;
		else if (!go_to_second_part)return original != other.original;
		else if (go_to_second_part) return original2 != other.original2;
	}

	bool operator==(const MergeIterator2& other) {
		return !operator!=(other);
	}

	value_type operator*() {
		if (go_to_second_part) return *original2;
		else return *original;
	}
};


template <class value_type, class function_return_type>
class MapAdaptor
{
public:
	std::function<function_return_type(value_type)> op;

	template<class It>
	using adapted_it = MappedIterator<It, function_return_type>;

	template<class It>
	Range<MappedIterator<It, function_return_type>> adapt(Range<It> range)
	{

		Range<adapted_it<It>> newrange = { adapted_it<It>({ range.begin(), op }), adapted_it<It>({ range.end(), op }) };
		return newrange;
	}

};

template <class value_type>
class FilterAdaptor
{
public:
	std::function<bool(value_type)> pred;

	template<class It>
	using adapted_it = FilteredIterator<It>;

	template<class It>
	Range<FilteredIterator<It>> adapt(Range<It> range)
	{
		Range<adapted_it<It>> newrange = { adapted_it<It>({ range.begin(),range.end(),pred }), adapted_it<It>({ range.end(),range.end(),pred }) };
		return newrange;
	}
};

//Оператор | за РЕЙНДЖ и АДАПТОР---------------
template<class It>
Range<FilteredIterator<It>> operator | (Range<It> range, FilterAdaptor<typename It::value_type> adaptor) {
	return adaptor.adapt(range);
}


template<class It, class return_type>
Range<MappedIterator<It, return_type>> operator | (Range<It> range, MapAdaptor<typename It::value_type, return_type> adaptor) {
	return adaptor.adapt(range);
}
//----------------------------------------------


//Operator | за КОНТЕЙНЕР и АДАПТОР ------------------
template<class container, class It = typename container::iterator>
Range<FilteredIterator<It>> operator | (container& cont, FilterAdaptor<typename It::value_type> adaptor) {
	Range<It> range{ cont.begin(), cont.end() };
	return adaptor.adapt(range);
}

template<class container, class return_type, class It = typename container::iterator>
Range<MappedIterator<It, return_type>> operator | (container& cont, MapAdaptor<typename It::value_type, return_type> adaptor) {
	Range<It> range{ cont.begin(), cont.end() };
	return adaptor.adapt(range);
}
//--------------------------------------------------

//Оператор + за КОНТАЙНЕР и КОНТАЙНЕР --------------------
template <class container, class It = typename container::iterator>
Range<MergeIterator<It>>
operator+(container& cont1, container& cont2) {
	return Range<MergeIterator<It>> {
		MergeIterator<It>{cont1.begin(), cont1.end(), cont2.begin(), cont2.end(), cont1.begin(), false},
			MergeIterator<It>{cont1.end(), cont1.end(), cont2.end(), cont2.end(), cont2.end(), true}
	};
}
//-------------------------------------------------------

//Оператор + за РЕЙНДЖ и РЕЙНДЖ --------------------
template <class It>
Range<MergeIterator<It>>
operator+(Range<It> cont1, Range<It> cont2) {
	return Range<MergeIterator<It>> {
		MergeIterator<It>{cont1.begin(), cont1.end(), cont2.begin(), cont2.end(), cont1.begin(), false},
			MergeIterator<It>{cont1.end(), cont1.end(), cont2.end(), cont2.end(), cont2.end(), true}
	};
}
//--------------------------------------------------

//Оператор + за КОНТЕЙНЕР и РЕЙНДЖ --------------------
template <class It, class container>
Range<MergeIterator2<It, typename container::iterator>>
operator+(Range<It> range, container& cont) {
	return Range<MergeIterator2<It, typename container::iterator>> {
		MergeIterator2<It, typename container::iterator>{range.begin(), range.end(), range.begin(), cont.begin(), cont.end(), cont.begin(), false},
			MergeIterator2<It, typename container::iterator>{range.end(), range.end(), range.end(), cont.end(), cont.end(), cont.end(), true}
	};
}
//--------------------------------------------------

//РЕЙНДЖ към ВЕКТОР от елементите на рейнджа
template<class It>
std::vector<typename It::value_type>
operator ~ (Range<It> range) {
	std::vector<typename It::value_type> vec;

	for (typename It::value_type x : range)
		vec.push_back(x);

	return vec;
}
//--------------------------------------------------


template<class It>
std::vector<typename It::value_type>
find_all_if(Range<It> vec, std::function<bool(typename It::value_type)> pred) {
	return ~Range<FilteredIterator<It>>{
		FilteredIterator<It>{vec.begin(), vec.end(), pred},
			FilteredIterator<It>{vec.end(), vec.end(), pred}
	};
}

template<class container>
std::vector<typename container::iterator::value_type>
find_all_if(container& vec, std::function<bool(typename container::iterator::value_type)> pred) {
	return ~Range<FilteredIterator<typename container::iterator>>{
		FilteredIterator<typename container::iterator>{vec.begin(), vec.end(), pred},
			FilteredIterator<typename container::iterator>{vec.end(), vec.end(), pred}
	};
}

template<class It>
typename It::value_type
find_if(Range<It> range, std::function<bool(typename It::value_type)> pred) {
	for (typename It::value_type x : range)
		if (pred(x)) return x;
	return 0;
}

template<class container>
typename container::iterator::value_type
find_if(container& vec, std::function<bool(typename container::iterator::value_type)> pred) {
	for (typename container::iterator::value_type x : vec)
		if (pred(x)) return x;
	return 0;
}

template<class value_type>
Range<std::istream_iterator<value_type>>
operator | (std::istream& stream, value_type x) {
	std::istream_iterator<value_type> end, in(stream);
	return Range<std::istream_iterator<value_type>>{ in, end };
}

template<class It>
Range<std::ostream_iterator<typename It::value_type>>
operator | (Range<It> range, std::ostream& stream) {
	std::ostream_iterator<typename It::value_type> out_it(stream, "\n"), out_it_begin(stream, "\n");
	It begin = range.begin();
	while (begin != range.end()) {
		*out_it = *begin;
		out_it++;
		begin++;
	}
	return Range<std::ostream_iterator<typename It::value_type>>{ out_it_begin, out_it };
}

