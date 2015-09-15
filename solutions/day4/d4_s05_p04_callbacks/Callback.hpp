#ifndef CALLBACK_HPP_
#define CALLBACK_HPP_


template<class ParamT>
class CallbackBase {
public:
	virtual ~CallbackBase() {
	}
	
	virtual void call(ParamT t) = 0;
};

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


#endif /* CALLBACK_HPP_ */
