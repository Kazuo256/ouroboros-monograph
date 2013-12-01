
// This is a generated file.


#include <test.h>

#include <languages/lua/aux/exportmodule.h>
#include <languages/lua/luamachine.h>
#include <languages/lua/converter.h>
#include <languages/lua/header.h>
#include <opa/scriptmanager.h>
#include <opa/module.h>
#include <opa/converter.h>
#include <iostream>
#include <string>
#include <list>
#include <stdexcept>

using std::list;
using std::string;
using std::cout;
using std::endl;
using std::runtime_error;
using opa::Module;
using opa::lua::LuaMachine;
using opa::lua::State;
using opa::lua::Constant;
using opa::lua::aux::ModuleInfo;
using opa::lua::aux::ExportModule;

// Begin wrappers

namespace generated {


int wrap_function_foo (lua_State* L) {
    int args = 0;
    if ((args = lua_gettop(L)) < 2)
        return luaL_error(
            L,
            "Error: %s expected %d arguments but received only %d.\n",
            "foo",
            2,
            args
        );
    opa::lua::Converter convert(L);
    double arg_0;
    double arg_1;
    try {
        arg_0 = convert.ScriptToType<double>(1);
        arg_1 = convert.ScriptToType<double>(2);
    } catch (runtime_error e) {
        return luaL_error(
            L,
            "Error: could not convert %s's arguments (%s).\n",
            "foo",
            e.what()
        );
    }
    double result = foo(arg_0, arg_1);
    lua_settop(L, 0);
    convert.TypeToScript<double>(result);
    int stack = 1;
    return stack;
}


int wrap_getter_x (lua_State* L) {
    opa::lua::Converter convert(L);
    convert.TypeToScript<int>(x);
    return 1;
}

int wrap_setter_x (lua_State* L) {
    opa::lua::Converter convert(L);
    int value;
    try {
        value = convert.ScriptToType<int>(1);
    } catch (runtime_error e) {
        return luaL_error(
            L,
            "Error: could not convert value to %s's type (%s).\n",
            "x",
            e.what()
        );
    }
    x = value;
    lua_settop(L, 0);
    return 0;
}


} // namespace generated

namespace {

/// Forward declaration.
int init (lua_State* L_);

luaL_Reg functions[] = {
    { "foo", generated::wrap_function_foo },
    { nullptr, nullptr }
};

luaL_Reg getters[] = {
    { "x", generated::wrap_getter_x },
    { nullptr, nullptr }
};

luaL_Reg setters[] = {
    { "x", generated::wrap_setter_x },
    { nullptr, nullptr }
};

luaL_Reg member_getters[] = {
    { nullptr, nullptr }
};

luaL_Reg member_setters[] = {
    { nullptr, nullptr }
};

luaL_Reg member_functions[] = {
    { nullptr, nullptr }
};

ModuleInfo info(
    "test", init,
    {
        {"getters",getters}, {"setters",setters}, {"functions",functions},
        {"member_getters",member_getters},
        {"member_setters",member_setters},
        {"member_functions",member_functions}
    }, 
    { }
);

/// [-(1|2),+1,e]
int init (lua_State* L) {
    return ExportModule(L, &info);
}

} // unnamed namespace

extern "C" {

/// [-(1|2),+1,e]
int luaopen_test (lua_State* L) {
    return init(L);
}

} // extern "C"


namespace {

class Bootstrap final {
  public:
    Bootstrap ();
};

Bootstrap entry_point;

Bootstrap::Bootstrap () {
    cout << "Bootstrapping Lua module test" << endl;
    LuaMachine *vm = dynamic_cast<LuaMachine*>(
        SCRIPT_MANAGER()->GetMachine("Lua")
    );
    if (vm == NULL) {
        vm = new LuaMachine;
        SCRIPT_MANAGER()->Register(vm);
    }
    vm->RegisterModule(Module<int(*)(lua_State*)>("test", luaopen_test));
}

} // unnamed namespace

