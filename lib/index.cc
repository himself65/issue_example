#define NAPI_VERSION 4
#include <v8.h>
#include <node_api.h>

#define DECLARE_NAPI_PROPERTY(name, func) \
{ (name), nullptr, (func), nullptr, nullptr, nullptr, napi_default, nullptr }

#define DECLARE_NAPI_GETTER_SETTER(name, getter, setter)				 \
{ (name), nullptr, nullptr, (getter), (setter), nullptr, napi_default, nullptr }

class Test {
public:
	int val;
};

napi_value Init(napi_env env, napi_callback_info info)
{
	napi_value thiz;
	napi_get_cb_info(env, info, nullptr, nullptr, &thiz, nullptr);
	Test* t = new Test();
	napi_wrap(env, thiz, reinterpret_cast<void*>(t), nullptr, nullptr, nullptr);
	return nullptr;
}

napi_value F(napi_env env, napi_callback_info info)
{
	size_t argc = 1;
	napi_value args[1];
	napi_value thiz;
	napi_get_cb_info(env, info, &argc, args, &thiz, nullptr);
	Test* t;
	napi_unwrap(env, thiz, reinterpret_cast<void**>(&t));
	// crash here
	// t->val = 1;
	return nullptr;
}

napi_value Init(napi_env env, napi_value exports) {
	napi_value obj;
	napi_property_descriptor desc[] = {
		DECLARE_NAPI_PROPERTY("test", F)
	};
	napi_define_class(env, "KCP", NAPI_AUTO_LENGTH, Init, nullptr,
		sizeof(desc) / sizeof(*desc), desc, &obj);
	napi_set_named_property(env, exports, "KCP", obj);
	return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)