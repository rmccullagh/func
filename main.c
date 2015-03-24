#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "Var.h"

#define PARAM_PARSE_SUCCESS 0
#define PARAM_PARSE_FAILURE 1

struct FuncArgItem {
	struct FuncArgItem* next;
	char* name;
	size_t name_len;
	Type type;
};

struct argInfo {
	size_t count;
	struct FuncArgItem* arg_list;
};

struct _Function {
	char* name;
	size_t name_len;
	struct argInfo* arg_info;
};

struct _functionArgStackInfo {
	size_t num_args;
};

struct _functionArgStack {
	Var* arg;
	struct _functionArgStack* next;
};

/*
 * _function_info contains the defined function arguments (implementation defined)
 * _fuinction_ex_args contains runtime arguments passed into the API by the user
 */
int func_parse_params(struct _Function* _function_info, struct _functionArgStack* _function_ex_args, char* format, ...)
{
	size_t require_arg_count = _function_info->arg_info->count;
	
	size_t runtime_arg_count = 0;
	
	struct _functionArgStack* fargs = _function_ex_args;

	va_list vl;
	char **p;
	
	va_start(vl, format);
	
	p = va_arg(vl, char**);
	
	printf("Found a string argument: %s\n", *p);

	*p = "RYAN";

	va_end(vl);


	printf("Parsing function: %s\n", _function_info->name);
	printf("Required arguments: %zu\n", require_arg_count);

	return PARAM_PARSE_SUCCESS;
}


#define INTERNAL_FUNC_PARAMS struct _Function* _finfo, struct _functionArgStack* _fargstack

#define CREATE_FUNCTION(name) void name(INTERNAL_FUNC_PARAMS)

#define FETCH_FUNC_ARGS() _finfo, _fargstack

#define FAST_FUNC_CALL(name, _finfo, _fargstack) name(_finfo, _fargstack)

#define FETCH_FUNC_NAME() _finfo->name


/*
 * array_init
 * struct _Function contains arg_info 
 * which has the required argument count (defined by the programmer)
 * it also has every type of info one would want about the required argument used for reflection
 * the name, the name length, and the type
 */
CREATE_FUNCTION(array_init) {
	
	printf("Function executing: %s\n", FETCH_FUNC_NAME());

	char* str = "str";
	
	/* str will actually hold the value that was passed into the function at run time */
	/* e.g. (ryan mccullagh) */
	if(func_parse_params(FETCH_FUNC_ARGS(), "%s", &str) != PARAM_PARSE_SUCCESS) {
		
		return;
	}

	printf("%s\n", str);
}

int main()
{
	size_t nbytes = sizeof(struct FuncArgItem);

	printf("%zu\n", nbytes);

	/* the argument linked list */
	/* it is important to realize that these represent a reflection of the function 
	 * not the arguments passed to the function at runtime
	 */
	struct FuncArgItem* arg1 = malloc(sizeof(struct FuncArgItem));
	arg1->next = NULL;
	arg1->name = malloc(strlen("string") + 1);
	memcpy(arg1->name, "string", strlen("string") + 1);
	arg1->name_len = strlen("string");
	arg1->type = IS_STRING;
	
	/* the argument container */
	struct argInfo* arg_info = malloc(sizeof(struct argInfo));
	arg_info->count = 1;
	arg_info->arg_list = arg1;

	/* the function info */	
	struct _Function* fentry = malloc(sizeof(struct _Function));
	fentry->name = malloc(strlen("array_init") + 1);
	memcpy(fentry->name, "array_init", strlen("array_init") + 1);
	fentry->name_len = strlen("array_init");
	fentry->arg_info = arg_info;

	/* these represent the arguments passed to the actual function */
	struct _functionArgStackInfo fexinfo;
	fexinfo.num_args = 1;

	struct _functionArgStack* arg_stack = malloc(sizeof(struct _functionArgStack));
	arg_stack->arg = var_string("ryan mccullagh");
	arg_stack->next = NULL;

	FAST_FUNC_CALL(array_init, fentry, arg_stack);

	return 0;
}
