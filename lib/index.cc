#define NAPI_VERSION 4
#include <v8.h>
#include <node_api.h>

#define DECLARE_NAPI_PROPERTY(name, func) \
{ (name), nullptr, (func), nullptr, nullptr, nullptr, napi_default, nullptr }

#define DECLARE_NAPI_GETTER_SETTER(name, getter, setter)				 \
{ (name), nullptr, nullptr, (getter), (setter), nullptr, napi_default, nullptr }

napi_value Init(napi_env env, napi_callback_info info)
{
	return nullptr;
}

napi_value Test(napi_env env, napi_callback_info info)
{
	size_t argc = 1;
	napi_value args[1];
	napi_value thiz;
	napi_get_cb_info(env, info, &argc, args, &thiz, nullptr);
	if (argc < 1) {
		napi_throw_error(env, nullptr, "Must have two parameter at least.");
	}
	napi_valuetype valuetype;
	napi_typeof(env, args[0], &valuetype);
	if (valuetype != napi_number) {
		napi_throw_type_error(env, nullptr, "Wrong argument type on args, number expected.");
	}
	// crash here
	int* number = (int *)0x7f7f7f7f;
	napi_get_value_int32(env, args[0], number);
	napi_value res;
	napi_get_boolean(env, true, &res);
	return res;
}

napi_value Init(napi_env env, napi_value exports) {
	napi_value obj;
	napi_property_descriptor desc[] = {
		DECLARE_NAPI_PROPERTY("test", Test)
	};
	napi_define_class(env, "KCP", NAPI_AUTO_LENGTH, Init, nullptr,
		sizeof(desc) / sizeof(*desc), desc, &obj);
	napi_set_named_property(env, exports, "KCP", obj);
	return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)