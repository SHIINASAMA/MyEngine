#ifndef CARGS_CARGS_H
#define CARGS_CARGS_H

typedef void (*CARGS_MODE_CALLBACK_FUNC)(char **argv);

void CARGS_INIT(int argc, char **argv);

void CARGS_REQUEST(const char *key);

void CARGS_NOT_ESSENTIAL(const char *key, const char *default_value);

bool CARGS_GET_VALUE_BY_KEY(const char *key, const char **value);

void CARGS_SET_MODE_CALLBACK_FUNC(int argc, CARGS_MODE_CALLBACK_FUNC func);

void CARGS_SET_NO_MATCH_CALLBACK_FUNC(CARGS_MODE_CALLBACK_FUNC func);

#endif//CARGS_CARGS_H
