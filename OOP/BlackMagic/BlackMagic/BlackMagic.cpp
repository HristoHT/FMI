#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "BlackMagic.h"

template <class value, class It2, class value2 = typename It2::value_type>
bool checkIterators(value value_to_check, It2 it2, std::function<value2(value)> fn) {
	return *(it2) == fn(value_to_check);
}

bool isInt(const std::string& number)
{
	return !number.empty() && std::find_if(number.begin(),
		number.end(), [](unsigned char c) { return !std::isdigit(c); }) == number.end();
}

int toInt(const std::string& number) {
	if (isInt(number)) {
		return std::stoi(number);
	}

	throw std::string("Incorect input!Try again!");
}

std::function<int(int)> increment_function = [](int x) -> int { return x + 5; };
std::function<std::string(int)> change_function = [](int x) -> std::string { return std::to_string(x) + std::string(" this is a string"); };
std::function<bool(int)> even_function = [](int x) ->bool { return !(x % 2); };
std::function<bool(std::string)> is_first_char_even_function = [](std::string x) ->bool { return !(toInt(std::to_string(x[0])) % 2); };

template <class something>
std::function<something(something)> id = [](something v) -> something { return v; };


TEST_CASE("VECTOR | MAP ADAPTOR")
{
	std::vector<int> vec = { 1, 2, 3, 4, 5 };
	MapAdaptor<int, int> increment{ increment_function };
	MapAdaptor<int, std::string> change{ change_function };
	Range<MappedIterator<std::vector<int>::iterator, int>> range = vec | increment;

	MappedIterator<std::vector<int>::iterator, int> increaseIt = range.begin();
	for (size_t i = 0; i < vec.size(); i++) {
		CHECK(checkIterators(*(vec.begin() + i), increaseIt, increment_function));
		++increaseIt;
	}

	Range<MappedIterator<std::vector<int>::iterator, std::string>> range2 = vec | change;
	MappedIterator<std::vector<int>::iterator, std::string> increaseIt2 = range2.begin();
	for (size_t i = 0; i < vec.size(); i++) {
		CHECK(checkIterators(*(vec.begin() + i), increaseIt2, change_function));
		++increaseIt2;
	}

}

TEST_CASE("VECTOR | FILTER ADAPTOR")
{
	std::vector<int> vec = { 1, 2, 3, 4, 5 };
	FilterAdaptor<int> iseven{ even_function };

	Range<FilteredIterator<std::vector<int>::iterator>> range = vec | iseven;

	FilteredIterator<std::vector<int>::iterator> It = range.begin();
	for (size_t i = 0; i < vec.size(); i++) {
		if (!even_function(i)) {
			CHECK(
				*(vec.begin() + i)
				==
				*It
			);
			++It;
		}
	}
}

TEST_CASE("VECTOR + VECTOR")
{
	std::vector<int> vec = { 1, 2, 3, 4, 5 };

	Range<MergeIterator<std::vector<int>::iterator>> range = vec + vec;
	MergeIterator<std::vector<int>::iterator> it = range.begin();
	for (size_t i = 0; i < 2 * vec.size() - 1; i++) {
		CHECK(vec[i % vec.size()] == *it);
		++it;
	}
}

TEST_CASE("RANGE + RANGE")
{
	std::vector<int> vec = { 1, 2, 3, 4, 5 };

	Range<MergeIterator<std::vector<int>::iterator>> range = vec + vec;
	Range<MergeIterator<MergeIterator<std::vector<int>::iterator>>> range2 = range + range;
	MergeIterator<MergeIterator<std::vector<int>::iterator>> it = range2.begin();

	for (size_t i = 0; i < 4 * vec.size() - 3; i++) {
		CHECK(vec[i % vec.size()] == *it);
		++it;
	}
}

TEST_CASE("RANGE + CONTAINER")
{
	std::vector<int> vec = { 1, 2, 3, 4, 5 };

	Range<MergeIterator<std::vector<int>::iterator>> range = vec + vec;
	Range<MergeIterator2<MergeIterator<std::vector<int>::iterator>, std::vector<int>::iterator>> range2 = range + vec;

	MergeIterator2<MergeIterator<std::vector<int>::iterator>, std::vector<int>::iterator> it = range2.begin();

	for (size_t i = 0; i < 3 * vec.size() - 2; i++) {
		CHECK(vec[i % vec.size()] == *it);
		++it;
	}
}

TEST_CASE("CONTAINER | FILTER ADAPTOR | MAP ADAPTOR")
{
	std::vector<int> vec = { 1, 2, 3, 4, 5 };
	MapAdaptor<int, int> increment{ increment_function };
	MapAdaptor<int, std::string> change{ change_function };
	FilterAdaptor<int> iseven{ even_function };
	Range<MappedIterator<FilteredIterator<std::vector<int>::iterator>, int>> range = vec | iseven | increment;

	MappedIterator<FilteredIterator<std::vector<int>::iterator>, int> increaseIt = range.begin();
	for (size_t i = 0; i < vec.size(); i++) {
		if (even_function(vec[i])) {
			CHECK(checkIterators(*(vec.begin() + i), increaseIt, increment_function));
			++increaseIt;
		}
	}

	Range<MappedIterator<FilteredIterator<std::vector<int>::iterator>, std::string>> range2 = vec | iseven | change;
	MappedIterator<FilteredIterator<std::vector<int>::iterator>, std::string> increaseIt2 = range2.begin();
	for (size_t i = 0; i < vec.size(); i++) {
		if (even_function(vec[i])) {
			CHECK(checkIterators(*(vec.begin() + i), increaseIt2, change_function));
			++increaseIt2;
		}
	}
}

TEST_CASE("CONTAINER | MAP ADAPTOR | FILTER ADAPTOR")
{
	std::vector<int> vec = { 1, 2, 3, 4, 5 };
	MapAdaptor<int, int> increment{ increment_function };
	MapAdaptor<int, std::string> change{ change_function };
	FilterAdaptor<int> iseven{ even_function };
	FilterAdaptor<std::string> is_first_even{ is_first_char_even_function };

	Range<FilteredIterator<MappedIterator<std::vector<int>::iterator, int>>> range = vec | increment | iseven;
	FilteredIterator<MappedIterator<std::vector<int>::iterator, int>> increaseIt = range.begin();
	for (size_t i = 0; i < vec.size(); i++) {
		if (even_function(increment_function(vec[i]))) {
			CHECK(checkIterators(*(vec.begin() + i), increaseIt, increment_function));
			++increaseIt;
		}
	}

	Range<FilteredIterator<MappedIterator<MappedIterator<std::vector<int>::iterator, int>, std::string>>> range2 = vec | increment | change | is_first_even;
	FilteredIterator < MappedIterator< MappedIterator< std::vector<int>::iterator, int>, std::string>> increaseIt2 = range2.begin();
	for (size_t i = 0; i < vec.size(); i++) {
		if (is_first_char_even_function(change_function(increment_function(vec[i])))) {
			CHECK(change_function(increment_function(vec[i])) == *increaseIt2);
			++increaseIt2;
		}
	}
}

TEST_CASE("OPERATOR ~")
{
	std::vector<int> vec = { 1, 2, 3, 4, 5 }, vec2 = ~(vec + vec);

	for (size_t i = 0; i < 2 * vec.size() - 1; i++) {
		CHECK(vec[i % vec.size()] == vec2[i]);
	}
}

TEST_CASE("FIND_ALL_IF")
{
	std::vector<int> vec = { 1, 2, 3, 4, 5 },
		vecEven = find_all_if(vec, even_function),
		vec2 = ~(vec + vec),
		vec2Even = find_all_if(vec2 + vec2, even_function);

	CHECK(vecEven.size() == 2);
	CHECK(vec2Even.size() == 8);
}

TEST_CASE("FIND_ALL_IF")
{
	std::vector<int> vec = { 1, 2, 3, 4, 5 }, vec2 = ~(vec + vec);

	CHECK(find_if(vec, [](int x)->bool { return x == 2; }) == 2);
	CHECK(find_if(vec + vec, [](int x)->bool { return x == 2; }) == 2);
	//CHECK(find_if(~(vec+vec), [](int x)->bool { return x == 2; }) == 2);
}

class ico
{
public:
	ico(int y);

	int get();
private:
	int x;
};

ico::ico(int y) : x(y)
{
}
int ico::get() {
	return x;
}

TEST_CASE("MY CLASS ")
{
	std::vector<ico*> vec = { new ico(1), new ico(2), new ico(3) }, vec2 = ~(vec + vec);

	FilterAdaptor<ico*> is_ico_even{ [](ico* ptr) -> bool { return !(ptr->get() % 2); } };

	std::vector<ico*>::iterator vecIt = vec2.begin();

	for (size_t i = 0; i < 2 * vec.size() - 1; i++) {
		if (!(vec[i % vec.size()]->get() % 2))
			CHECK(vec[i % vec.size()] == vec2[i]);
	}
}

class Line
{
	std::string _line;
public:
	Line() : _line("") {}

	std::string& string() {
		return _line;
	}

	std::string string() const {
		return _line;
	}
};

std::istream& operator>>(std::istream& input, Line& l) {
	std::getline(input, l.string());
	return input;
}

std::ostream& operator<<(std::ostream& out, const Line& l) {
	out << l.string();
	return out;
}

int main()
{
	// пускане на тестовете
	doctest::Context().run();

	std::ifstream file("test.txt", std::ios::in);

	MapAdaptor<Line, std::vector<std::string>> splitOnSpace{ [](Line l) -> std::vector<std::string> {
		std::vector<std::string> vec;
		std::string currentWord = "", str = l.string();

		for (char ch : str) {
			if ((ch == ' ' || ch == '\n') && currentWord != "")
				vec.push_back(currentWord);
			else currentWord += ch;
		}
		if (currentWord != "")
			vec.push_back(currentWord);

		return vec;
	} };

	FilterAdaptor<std::vector<std::string>> noEmpty{ [](std::vector<std::string > vec) -> bool {
		return vec.size();
	} };
	
	FilterAdaptor<int> even{ [](int x) -> bool {
		return !(x % 2);
	} };

	std::vector<int> a = { 1, 2, 3, 4, 5 }, b = { 6, 7, 8, 9, 10 };

	for (int x : a + b + a | even)
		std::cout << x << " \n";

	/*for (std::vector<std::string> l : file | Line() | splitOnSpace | noEmpty) {
		std::cout << l[0] << std::endl;
	}*/

	std::ofstream fileOut("test2.txt", std::ios::out);


	/*for (std::vector<std::string> x : file | Line() | fileOut | splitOnSpace | noEmpty) {
		std::cout << x[0] << std::endl;
	}*/

}
