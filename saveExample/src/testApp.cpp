#include "testApp.h"

/****************** TUPLE FOR EACH ************************************/
template<size_t N>
struct for_each_impl {
	template<typename Func, typename Tuple>
	void operator()(Func func, Tuple const& arg) {
		for_each_impl<N-1>()(func, arg );
		return func( std::get<N-1>( arg ) );
	}
};

template<>
struct for_each_impl<1> {
	template<typename Func, typename Tuple>
	void operator()(Func func, Tuple const& arg) {
		func( std::get<0>( arg ) );
	}
};

template<typename Func, typename ... Args>
void for_each( Func func, std::tuple<Args...>const& tup ) {
	for_each_impl< sizeof...(Args)>()( func, tup );
}

/*******************************************************************/
/*
class Component {
public:
	virtual void registerComponent(Component& c) = 0;
};

class Styler;
class CssLoader;

class Addresser: public Component {
public:
	void registerComponent(Styler& c) {
		cout << "S STYLER" << endl;
	}

	void registerComponent(CssLoader& c) {
		cout << "CSS LOADER" << endl;
	}
	
	void registerComponent(Component& c){
		cout << "UNKNOWN COMPONENT" << endl;
	};
};

class Styler: public Component {
public:
	void registerComponent(Component& c) {
cout << "UNKNOWN COMPONENT" << endl;
	}
};

class CssLoader: public Component {
public:
	void registerComponent(Component& c) {
cout << "UNKNOWN COMPONENT" << endl;
	}
	
	void registerComponent(Styler& l){
		cout << "Styler" << endl;
	}
};


template<class TupleType, size_t N, size_t N2>
struct do_iterate {
	static void call(TupleType& t) {
		if(N != N2)
			std::get<N>(t).registerComponent(std::get<N2>(t));
		do_iterate<TupleType, N-1, N2>::call(t);
	}
};

template<class TupleType, size_t N>
struct do_iterate<TupleType, 0, N> {
	static void call(TupleType& t) {
		std::get<0>(t).registerComponent(std::get<N>(t));
		do_iterate<TupleType, std::tuple_size<TupleType>::value-1, N-1>::call(t);
	}
};

template<class TupleType>
struct do_iterate<TupleType, 0, 0> {
	static void call(TupleType& t) {
	}
};

template<class TupleType>
void iterate_tuple(TupleType t) {
	do_iterate<TupleType, std::tuple_size<TupleType>::value-1, std::tuple_size<TupleType>::value-1>::call(t);
}

class Compositor {
public:
	template <class... Components>
	void registerComponents(Components... components) {

		std::tuple<Components...> tuple(components...);

		iterate_tuple<std::tuple<Components...> >(tuple);

	}


private:
	class ComponentRegistryHelperBase {

	};

	template <class Type>
	class ComponentRegistryHelper: public ComponentRegistryHelperBase {
		Type& object;
	};
};



class Test: private Compositor, public Addresser, public Styler, public CssLoader {
public:
	Test() {
		registerComponents<Addresser, Styler, CssLoader>(*this, *this, *this);
	}
};
*
*/

#include <tuple>

template <typename T, typename S, int i = std::tuple_size<T>::value - 1>
struct tuple_index
{
    enum
    {
        value = std::is_same<typename std::tuple_element<i, T>::type, S>::value ? i :
            tuple_index<T, S, i-1>::value
    };
};

template <typename T, typename S>
struct tuple_index<T, S, -1>
{
    enum { value = -1 };
};


template <class... Components>
class Compositor{
public:
	
	std::tuple<Components...> components;
	
	template<class ComponentType>
	ComponentType& getComponent(){
		return std::get< tuple_index<std::tuple<Components...>, ComponentType>::value >(components);
	}
};

class Component1{
public:
	void blah(){
		cout << value << endl;
	}
	std::string value;
};

class Component2{
	
};

class BoxTest: public Component1, public Compositor<Component1, Component2>{
public:
	BoxTest(){
		value = "hello";
	}
};

//--------------------------------------------------------------
void testApp::setup() {
	BoxTest test;
	test.getComponent<Component1>().blah();
	
/*
	root.addChild(&child);
	ofxBox* box = root.getChild(0);
	cout << box << endl;
	box->findByAddress(".test");
*/
}

//--------------------------------------------------------------
void testApp::update() {

}

//--------------------------------------------------------------
void testApp::draw() {
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo) {

}
