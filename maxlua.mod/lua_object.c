
#include <brl.mod/blitz.mod/blitz.h>

#include <pub.mod/lua.mod/lua-5.1.4/src/lua.h>

struct BBObjectContainer {
	BBObject * o;
};

void lua_boxobject( lua_State *L,BBObject *obj ){
	void *p;
	
	struct BBObjectContainer * uc = (struct BBObjectContainer *)GC_MALLOC_UNCOLLECTABLE(sizeof(struct BBObjectContainer));
	uc->o = obj;
	
	p=lua_newuserdata( L,4 );
	*(struct BBObjectContainer**)p=uc;
}

BBObject *lua_unboxobject( lua_State *L,int index ){
	void *p;
	p=lua_touserdata( L,index );
	struct BBObjectContainer * uc = *(struct BBObjectContainer**)p;
	return uc->o;
}

void lua_pushlightobject( lua_State *L,BBObject *obj ){
	lua_pushlightuserdata( L,obj );
}

BBObject *lua_tolightobject( lua_State *L,int index ){
	return (BBObject*)( lua_touserdata( L,index ) );
}

void lua_gcobject( lua_State *L ){
	void *p;
	p=lua_touserdata( L,1 );
	struct BBObjectContainer * uc = *(struct BBObjectContainer**)p;
	GC_FREE(uc);
}
