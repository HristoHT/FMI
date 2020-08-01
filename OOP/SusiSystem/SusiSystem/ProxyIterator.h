#pragma once
template <typename container>
class ProxyIterator {
	container& _container;
public:
	using iterator = typename container::iterator;
	ProxyIterator(container& cont) : _container(cont) { }
	typename container::iterator begin() {
		return _container.begin();
	}
	typename container::iterator end() {
		return _container.end();
	}
};

template<class container>
ProxyIterator<container> get(container vec) {
	return ProxyIterator<container>(vec);
}