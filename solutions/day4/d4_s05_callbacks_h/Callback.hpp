/*
 * Callback.hpp
 */

#ifndef CALLBACK_HPP_
#define CALLBACK_HPP_

#include <boost/shared_ptr.hpp>

/**
 * Base class for all types of callbacks.
 */
template<class ParamT>
class CallbackBase {
public:
	virtual ~CallbackBase() {
	}
	
	virtual void call(ParamT t) = 0;
};

/**
 * Callback class that takes a function pointer
 */
template<class ParamT>
class FunctionCallback: public CallbackBase<ParamT> {
public:
	FunctionCallback(void(*fp)(ParamT)) :
			fp(fp) {
	}
	
	virtual ~FunctionCallback() {
	}
	
	virtual void call(ParamT t) {
		fp(t);
	}
private:
	void (*fp)(ParamT);
};

/**
 * Callback class that takes a functor
 */
template<class ParamT, class FunctorT>
class FunctorCallback: public CallbackBase<ParamT> {
public:
	FunctorCallback(FunctorT& fp) :
			fp(fp) {
	}
	
	virtual ~FunctorCallback() {
	}
	
	virtual void call(ParamT t) {
		fp(t);
	}
private:
	FunctorT& fp;
};

/**
 * Callback class that takes an object and a method callback
 */
template<class ParamT, class ClassT>
class MethodCallback: public CallbackBase<ParamT> {
public:
	MethodCallback(void(ClassT::*mp)(ParamT), ClassT* obj) :
			mp(mp), obj(obj) {
	}
	
	virtual ~MethodCallback() {
	}
	
	virtual void call(ParamT t) {
		(obj->*mp)(t);
	}
private:
	void (ClassT::*mp)(ParamT);
	ClassT* obj;
};

/**
 * Central callback class that offers a constructor
 * for each type of callback.
 */
template<class ParamT>
class Callback {
public:
	Callback(void(*fp)(ParamT)) :
			callbackPtr(new FunctionCallback<ParamT>(fp)) {
	}
	
	template<class FunctorT>
	Callback(FunctorT& fp) :
			callbackPtr(new FunctorCallback<ParamT, FunctorT>(fp)) {
	}
	
	template<class ClassT>
	Callback(void(ClassT::*mp)(ParamT), ClassT* obj) :
			callbackPtr(new MethodCallback<ParamT, ClassT>(mp, obj)) {
	}
	
	void operator()(ParamT t) {
		callbackPtr->call(t);
	}
private:
	boost::shared_ptr<CallbackBase<ParamT> > callbackPtr;
};

#endif /* CALLBACK_HPP_ */
