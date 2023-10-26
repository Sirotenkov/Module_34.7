#include <string>

template<typename ty>
concept ComplexConcept = requires(ty t) {
	{t.toString()} -> std::same_as<std::string>;
	{t.hash()} -> std::convertible_to<long>;

} && !std::has_virtual_destructor<ty>::value;

class foo {
public:
	std::string toString() { return {}; }
	int hash() { return {}; }
};

// В классе объявлен виртуальный деструктор, поэтому ограничение, накладываемое концептом, не выполнено
// Это подсвечивает IDE и компилятор выдаёт соответствующее сообщение
// Если убрать слово virtual, т.е. сделать деструктор не виртуальным, то ограничение концепта будет выполнено
// и программа отработает без ошибок

class bar {
public:
	virtual ~bar() {}
	std::string toString() { return {}; }
	int hash() { return {}; }
};

static_assert(ComplexConcept<foo>);
static_assert(ComplexConcept<bar>);

int main() {
	return 0;
}
